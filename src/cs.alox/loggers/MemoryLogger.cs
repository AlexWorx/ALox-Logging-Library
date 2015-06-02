// #################################################################################################
//  com.aworx.lox.loggers - ALox Logging Library
//
//  (c) 2013-2015 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
using System;
using System.Runtime.CompilerServices;
using com.aworx.lox.core;
using com.aworx.util;

namespace com.aworx.lox.loggers {


/** ************************************************************************************************
 * <summary>
 *  A logger that logs all messages to a in-memory buffer of type AString. The name of the logger
 *  defaults to "MEMORY".
 * </summary>
 **************************************************************************************************/
public class MemoryLogger : TextLogger
{
    // #############################################################################################
    // Empty method stubs for release version (with no release logging)
    // #############################################################################################
    #if !(ALOX_DEBUG || ALOX_REL_LOG)
        public MemoryLogger( String name= "Memory" ){}
        public        AString            Buffer                            = new AString( 0 );
    #else
    /**
     * <summary>
     *  The logging Buffer. This can be accessed publicly and hence used as you prefer. Especially,
     *  the whole log can easily be cleared using the AString.Clear(). However, in
     *  multi-threaded environments, locking to the Log interface's mutex should be performed before
     *  accessing this Buffer. The initial size of the buffer is 8kb.
     * </summary>
     */
    public        AString            Buffer                            = new AString( 8192 );


    /** ********************************************************************************************
     * <summary>    Creates a MemoryLogger with the given name. </summary>
     * <param name="name">    (Optional) The name of the logger. Defaults to "MEMORY". </param>
     **********************************************************************************************/
    public MemoryLogger( String    name= "MEMORY" )
    : base( name )
    {
    }

    /** ********************************************************************************************
     * <summary>
     *  The implementation of the abstract method of parent class TextLogger. Logs messages to the
     *  Buffer field.
     * </summary>
     * <param name="domain">        The log domain name. </param>
     * <param name="level">         The log level. This has been checked to be active already on this
     *                              stage and is provided to be able to be logged out only. </param>
     * <param name="msg">           The log message. </param>
     * <param name="indent">        the indentation in the output. Defaults to 0. </param>
     * <param name="caller">        Once compiler generated and passed forward to here. </param>
     * <param name="lineNumber">    The line number of a multi-line message, starting with 0. For
     *                               single line messages this is -1. </param>
     **********************************************************************************************/
    override protected void doTextLog(     AString        domain,        Log.Level    level,
                                        AString        msg,        int            indent,
                                        CallerInfo    caller,     int            lineNumber)
    {
        // append new line if buffer has already lines stored
        if ( Buffer.Length() > 0 )
            Buffer.NewLine();

        // append message
        Buffer.Append( msg );
    }

    /** ********************************************************************************************
     * <summary> Empty implementation, not needed for this class <summary>
     * <param name="isStart">    If true, indicates the begin of a multi-line message, the end of
     *                             it otherwise. </param>
     **********************************************************************************************/
    override protected void notifyMultiLineOp (bool isStart)
    {
    }
    #endif // ALOX_DEBUG || ALOX_REL_LOG
}
} // namespace
