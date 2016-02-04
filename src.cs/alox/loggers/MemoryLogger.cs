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
using cs.aworx.lox.core;
using cs.aworx.lib.strings;
using cs.aworx.lib.enums;

namespace cs.aworx.lox.loggers {


/** ************************************************************************************************
 *  A logger that logs all messages to an in-memory buffer of type AString. The name of the logger
 *  defaults to "MEMORY".
 **************************************************************************************************/
public class MemoryLogger : PlainTextLogger
{
    // #############################################################################################
    // Empty method stubs for release version (with no release logging)
    // #############################################################################################
    #if !(ALOX_DBG_LOG || ALOX_REL_LOG)
        public MemoryLogger( String name= "Memory" ){}
        public  AString             MemoryLog                            = new AString( 0 );
    #else
    /**
     *  The logging Buffer. This can be accessed publicly and hence used as preferred. Especially,
     *  the whole log can easily be cleared using
     *  \ref cs::aworx::lib::strings::AString::Clear "AString.Clear".
     *  In multi-threaded environments, \c Lox interfaces' mutex should be acquired
     *  before accessing this buffer. The initial size of the buffer is 8kb.
     */
    public      AString             MemoryLog                            = new AString( 8192 );

    /** ********************************************************************************************
     * Creates a MemoryLogger with the given name.
     * @param name              (Optional) The name of the logger. Defaults to "MEMORY".
     * @param pruneESCSequences (Optional) Sets the member \ref PruneESCSequences.
     *                          Defaults to true.
     **********************************************************************************************/
    public MemoryLogger( String name= null, bool pruneESCSequences= true  )
    : base( name, "MEMORY" )
    {
        this.PruneESCSequences= pruneESCSequences;
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
        // append new line if buffer has already lines stored
        if ( phase == Phase.Begin && MemoryLog.IsNotEmpty() )
            MemoryLog.NewLine();
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
        MemoryLog._NC( buffer, start, length );
        return true;
    }

    /** ********************************************************************************************
     * Empty, not needed here
     * @param phase  Indicates the beginning or end of a multi-line operation.
     **********************************************************************************************/
    override
    protected void notifyMultiLineOp( Phase phase )  {}

    #endif // ALOX_DBG_LOG || ALOX_REL_LOG
}
} // namespace
