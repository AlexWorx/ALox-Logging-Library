// #################################################################################################
//  com.aworx.lox.loggers - ALox Logging Library
//
//  Copyright 2013-2019 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
package com.aworx.lox.loggers;

import com.aworx.lib.lang.Phase;
import com.aworx.lib.strings.AString;
import com.aworx.lox.detail.textlogger.PlainTextLogger;


/** ************************************************************************************************
 * A logger that logs all messages to an in-memory buffer of type AString. The name of the \e Logger
 * defaults to "MEMORY".
 **************************************************************************************************/
public class MemoryLogger extends PlainTextLogger
{
    /**
     *  The logging Buffer. This can be accessed publicly and hence used as preferred. Especially,
     *  the whole log can easily be cleared using
     *  \ref com.aworx.lib.strings.AString.clear() "AString.clear".
     *  In multi-threaded environments, \c Lox interfaces' mutex should be acquired
     *  before accessing this buffer. The initial size of the buffer is 8kb.
     */
    public    AString               memoryLog                            = new AString( 8192 );

    /** ********************************************************************************************
     * Creates a MemoryLogger with the name "MEMORY".
     **********************************************************************************************/
    public    MemoryLogger()
    {
        super( null, "MEMORY", false );
    }

    /** ********************************************************************************************
     * Creates a MemoryLogger with the given name.
     * @param name  The name of the \e Logger. Defaults to "MEMORY".
     **********************************************************************************************/
    public    MemoryLogger( String name )
    {
        super( name, "MEMORY", false );
    }

    /** ********************************************************************************************
     * Creates a MemoryLogger with the given name.
     * @param name              (Optional) The name of the \e Logger.
     *                          Defaults to "MEMORY".
     * @param pruneESCSequences (Optional) Sets the member #pruneESCSequences.
     *                          Defaults to true.
     **********************************************************************************************/
    public    MemoryLogger( String name, boolean pruneESCSequences )
    {
        super( name, "MEMORY", false );
        this.pruneESCSequences= pruneESCSequences;
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
        // append new line if buffer has already lines stored
        if ( phase == Phase.BEGIN  && memoryLog.isNotEmpty() )
            memoryLog.newLine();
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
    @Override
    protected boolean logSubstring( AString buffer, int start, int length )
    {
        memoryLog._NC( buffer, start, length );
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


} // class MemoryLogger
