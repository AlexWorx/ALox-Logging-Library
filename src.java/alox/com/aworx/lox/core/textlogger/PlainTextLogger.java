// #################################################################################################
//  com.aworx.lox.loggers - ALox Logging Library
//
//  Copyright 2013-2018 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
package com.aworx.lox.core.textlogger;

import com.aworx.lib.lang.Phase;
import com.aworx.lib.strings.AString;
import com.aworx.lib.strings.util.Spaces;
import com.aworx.lox.Verbosity;
import com.aworx.lox.core.Domain;
import com.aworx.lox.core.ScopeInfo;


/** ************************************************************************************************
 * A text logger that either removes or ignores (just writes through) \b %ALox ESC sequences.
 * Implements abstract method #logText and introduces two new abstract methods
 * #logSubstring and #notifyLogOp.
 **************************************************************************************************/
public abstract class PlainTextLogger extends TextLogger
{
    /**
     * If this field is set to \c true (the default), all \ref com.aworx.lox.ESC "ESC" color and
     * style codes get removed when logging into this Logger. \c ESC.TAB is processed.
     *
     * It might be useful, to set this to false, e.g. in the case, the contents of the
     * Logger is (later) written into a different logger (e.g. as a multi line message)
     * which is capable of interpreting the escape sequences of class ESC.
     */
    public      boolean             pruneESCSequences                                   = true;

    /** ********************************************************************************************
     * Creates a PlainTextLogger
     * @param name            The name of the \e Logger. If empty, it defaults to the type name.
     * @param typeName        The type of the \e Logger.
     * @param usesStdStreams  Denotes whether this logger writes to the
     *                        <em>standard output streams</em>.
     **********************************************************************************************/
    protected PlainTextLogger( String name, String typeName, boolean usesStdStreams )
    {
        super( name, typeName, usesStdStreams );
    }

    /** ********************************************************************************************
     * Abstract method to be implemented by descendants. This method is called when a new
     * log message is started. It is called exactly once before a series of logSubstring()
     * calls and exactly once after such series. If either the start or one of the calls
     * to #logSubstring returns \c false, the second invocation that would indicate the end of
     * a log message is omitted.
     *
     * Implementing this method allows the acquisition of system resources (e.g. opening a file).
     *
     * @param phase  Indicates the beginning or end of a log operation.
     * @return If \c false is returned, the log line is aborted without an invocation of
     *         \ref notifyLogOp "notifyLogOp(Phase.END)".
     **********************************************************************************************/
    abstract protected boolean notifyLogOp( Phase phase );

    /** ********************************************************************************************
     * Abstract method to be implemented by descendants. Has to write the given region of
     * the given AString to the destination.
     *
     * @param buffer   The string to write a portion of.
     * @param start    The start of the portion in \p buffer to write out.
     * @param length   The length of the portion in \p buffer to write out.
     * @return If \c false is returned, the log line is aborted without an invocation of
     *         \ref notifyLogOp "notifyLogOp(Phase.END)".
     **********************************************************************************************/
    abstract protected boolean logSubstring( AString buffer, int start, int length );

    /** ********************************************************************************************
     * The implementation of the abstract method of parent class TextLogger.
     * Loops over the log text, removes or ignores ESC sequences (all but ESC.TAB) and invokes
     * abstract methods of descendants as follows:
     * - \ref notifyLogOp "notifyLogOp(true)"
     * -   #logSubstring()
     * -   ...
     * - \ref notifyLogOp "notifyLogOp(Phase.END)"
     *
     *
     * @param domain        The <em>Log Domain</em>.
     * @param verbosity     The verbosity. This has been checked to be active already on this stage
     *                      and is provided to be able to be logged out only.
     * @param msg           The log message.
     * @param scope         Information about the scope of the <em>Log Statement</em>..
     * @param lineNumber    The line number of a multi-line message, starting with 0. For single
     *                      line messages this is -1.
     **********************************************************************************************/
    @Override
    protected void logText( Domain        domain,     Verbosity verbosity,
                            AString       msg,
                            ScopeInfo     scope,      int       lineNumber )
     {
        if ( !notifyLogOp( Phase.BEGIN ) )
            return;

        // loop over message, print the parts between the escape sequences
        {
            int  msgLength=  msg.length();
            int  start=      0;
            int  end;
            int  column=     0;
            while( start < msgLength )
            {
                boolean foundESC=  true;
                end=    msg.indexOf( '\033', start );
                if( end < 0 )
                {
                    foundESC= false;
                    end=      msgLength ;
                }

                if ( end > start )
                {
                    if (!logSubstring( msg,  start, end - start ) )
                        return;
                    column+= end - start;
                }

                // interpret escape sequence
                if ( foundESC )
                {
                    char c=  msg.buffer()[++end];
                    // auto tab or end of meta info part
                    if ( c == 't' || c == 'A' )
                    {
                        end++;
                        c=  msg.buffer()[end++];
                        int extraSpace=  c >= '0' && c <= '9' ? ( c - '0' )
                                                              : ( c - 'A' ) + 10;

                        int tabStop= autoSizes.next( column, extraSpace );

                        if ( tabStop > column )
                        {
                            AString spaces= Spaces.get();
                            int spacesLength= spaces.length();
                            int qty= tabStop - column;
                            while ( qty > 0 )
                            {
                                int size= qty < spacesLength ? qty : spacesLength;
                                if(!logSubstring( spaces, 0, size ) ) return;
                                qty-= size;
                            }
                            column= tabStop;
                        }

                    }

                    // prune or ignore all others
                    else
                    {
                        if ( !pruneESCSequences )
                            if(!logSubstring( msg, end - 1, 3 )) return;
                        end+= 2;
                    }
                }

                // next
                start= end;

            } // write loop

            com.aworx.lib.ALIB_DBG.ASSERT_WARNING( start == msgLength, "Loop error when pruning ESC codes" );
        }

        notifyLogOp( Phase.END );

    }

} // class PlainTextLogger
