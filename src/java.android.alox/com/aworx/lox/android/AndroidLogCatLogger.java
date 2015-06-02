// #################################################################################################
//  com.aworx.lox.android  - ALox Logging Library
//
//  (c) 2013-2015 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
package com.aworx.lox.android;

import com.aworx.util.AString;
import com.aworx.lox.core.CallerInfo;
import com.aworx.lox.core.TextLogger;
import com.aworx.lox.Log;

/** ************************************************************************************************
 * A logger that logs all messages to the Android LogCat (**using * android.util.Log.e()/w()...**)
 * There are two options to use the LogCat "Tag" concept together with the ALox "Log Domain"
 * concept. See public field #logTag for more information.
 *
 * The name of the logger defaults to "LOGCAT". In the Eclipse IDE, log lines are double-clickable
 * to jump directly to the source code that generated the log.
 *
 *
 * The constructor sets the level of the root domain, and as such the level of all 'unknown'
 * domains that inherit from root domain to 'All'. This is because this class represents a logger
 * that logs into the developer's IDE, and hence just wants to fetch all log domains that the
 * app and its library uses unless explicitly set differently in the bootstrap code.  By default,
 * root domains of loggers have domain level 'Off'.
 **************************************************************************************************/
public class AndroidLogCatLogger extends TextLogger
{
    /** The log tag that is passed to LogCat. If this is set to null, the ALox domain name
        is passed instead. The advantage of having one fixed LogCat tag value for all ALox messages is
        that you can filter that tag within your IDE's LogCat view to see exclusively ALox messages.
        On the other hand, if the ALox domain name is used as the LogCat category, than you can use the
        LogCat view to filter ALox messages.
        Default value is "ALox". If you set this to null to switch to the other mode, you might want
        to also change the format string to NOT redundantly include the domain name, which then is
        presented by LogCat (e.g. "at (%CF) %CM():%A3[%TE +%TI]: ".
    */
    public        String                logTag                                  ="ALox";

    /** Flag to indicate whether ALox Log.Level.Verbose should be logged using android.util.Log.d
        or android.util.Log.v. Defaults to true, hence LogCat debug messages are used.   */
    public        boolean               verboseIsDebug                          = true;

    /** A temporary buffer for assembling the caller info string*/
    protected    AString                consoleBuffer                           =new AString(256);


    // #############################################################################################
    // Constructors
    // #############################################################################################

    /**
     *  Creates an AndroidLogCatLogger with the given name.
     *     @param name        The name of the logger.
     */
    public AndroidLogCatLogger(    String    name )     { super( name );        constructor(); }

    /** Creates an AndroidLogCatLogger with name "LOGCAT".*/
    public AndroidLogCatLogger()                        { super( "LOGCAT" );    constructor(); }

    /** Sets the format string to be right for LogCat. Also sets the root domain level (the default level)
     *  for unknown domains) to ALL */
    public void constructor()
    {
        // disable redundant info (LogCat logs this already) and have an "at " before the file name
        // to enable "clickable" LogCat lines
        lineFormatter.format= new AString( "at (%CF) %CM():%A3[%TE +%TI][%O]: ");

        // set default domain level to all: As a app console logger/IDE logger we want to fetch all we can
        rootDomain.setLevel( Log.DomainLevel.ALL, false );
    }


    /** ********************************************************************************************
     *  The implementation of the abstract method of parent class TextLogger. Logs messages to
     *  android LogCat (which might be an IDE window)
     *
     * @param domain        The log domain name. If not starting with a slash ('/')
     *                      this is appended to any default domain name that might have been specified
     *                      for the source file.
     * @param level         The log level. This has been checked to be active already on this stage
     *                      and is provided to be able to be logged out only.
     * @param msg           The log message.
     * @param indent        the indentation in the output. Defaults to 0.
     * @param caller        Once compiler generated and passed forward to here.
     * @param lineNumber    The line number of a multi-line message, starting with 0. For single line
     *                      messages this is -1.
     **********************************************************************************************/
    @Override protected void doTextLog( AString        domain,        Log.Level    level,
                                        AString        msg,        int            indent,
                                        CallerInfo    caller,     int            lineNumber )
    {
        // log it out
        String logCat=        logTag == null ? domain.toString() : logTag;
        String logCatMsg=    msg.toString();
             if ( level == Log.Level.ERROR )        {    android.util.Log.e( logCat, logCatMsg );    }
        else if ( level == Log.Level.WARNING )      {    android.util.Log.w( logCat, logCatMsg );    }
        else if ( level == Log.Level.INFO )         {    android.util.Log.i( logCat, logCatMsg );    }
        else {    if (verboseIsDebug)               {    android.util.Log.d( logCat, logCatMsg );    }
                else                                {    android.util.Log.v( logCat, logCatMsg );    } }
    }

    /** ********************************************************************************************
     *  Abstract method to be implemented by descendants. This message is called only when multi-line
     *  messages are logged. It is called exactly once before a series of doLog() calls of a multi-line
     *  message and exactly once after such series.<br>
     *  This is useful if the writing of text includes the acquisition of system resources (e.g. opening
     *  a file).
     *
     * @param isStart       If true, indicates the begin of a multi-line message, the end otherwise.
     **********************************************************************************************/
    @Override protected void notifyMultiLineOp (boolean isStart)
    {
    }


//#endif // ALOX_DEBUG || ALOX_REL_LOG

} // class ConsoleLogger
