// #################################################################################################
//  com.aworx.lox.android  - ALox Logging Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################


/** ************************************************************************************************
 *  This is the Java package for extension classes of the <em>%ALox Logging Library</em>
 *  to support ALox on Android devices.
 *
 *  Developed by A-Worx GmbH and published under the MIT license.
 **************************************************************************************************/
package com.aworx.lox.android;

import com.aworx.lib.enums.Phase;
import com.aworx.lib.strings.AString;
import com.aworx.lox.core.ScopeInfo;
import com.aworx.lox.core.Domain;
import com.aworx.lox.core.textlogger.TextLogger;
import com.aworx.lox.Verbosity;

/** ************************************************************************************************
 * A logger that logs all messages to the Android LogCat (**using * android.util.Log.e()/w()...**)
 * There are two options to use the LogCat "Tag" concept together with the ALox "Log Domain"
 * concept. See public field #logTag for more information.
 *
 * The name of the \e Logger defaults to "LOGCAT". In the Eclipse IDE, log lines are double-clickable
 * to jump directly to the source code that generated the log.
 **************************************************************************************************/
public class AndroidLogCatLogger extends TextLogger
{
    /**
     * The log tag that is passed to LogCat. If this is set to null, the ALox domain name
     * is passed instead. The advantage of having one fixed LogCat tag value for all ALox messages is
     * that you can filter that tag within your IDE's LogCat view to see exclusively ALox messages.
     * On the other hand, if the ALox domain name is used as the LogCat category, than you can use the
     * LogCat view to filter ALox messages.
     * Default value is "ALox". If you set this to null to switch to the other mode, you might want
     * to also change the format string to NOT redundantly include the domain name, which then is
     * presented by LogCat (e.g. change it to "at (%SF) %SM():%A3[%TC +%TL]: ".
    */
    public        String                logTag                                              ="ALox";

    /**
     * Flag to indicate whether ALox Verbosity.Verbose should be logged using
     * <em>android.util.Log.d</em> or <em>android.util.Log.v</em>.
     * Defaults to true, hence LogCat debug messages are used.
     */
    public        boolean               verboseIsDebug                                       = true;


    // #############################################################################################
    // Constructors
    // #############################################################################################

    /** ********************************************************************************************
     * Creates an AndroidLogCatLogger with the given name.
     * @param name        The name of the \e Logger.
     **********************************************************************************************/
    public AndroidLogCatLogger(    String    name )
    {
        super( name, "LOGCAT", false);
        constructor();
    }

    /** ********************************************************************************************
     * Creates an AndroidLogCatLogger with name "LOGCAT".
     **********************************************************************************************/
    public AndroidLogCatLogger()
    {
        super( null, "LOGCAT", false );
        constructor();
    }

    /** ********************************************************************************************
     * Sets the format string to be right for LogCat.
     **********************************************************************************************/
    public void constructor()
    {
        // disable redundant info (LogCat logs this already) and have an "at " before the file name
        // to enable "clickable" LogCat lines
        metaInfo.format= new AString( "at (%SF) %SM():%A3[%TC +%TL][%D]: ");
    }


    /** ********************************************************************************************
     *  The implementation of the abstract method of parent class TextLogger. Logs messages to
     *  android LogCat (which might be an IDE window)
     *
     * @param domain        The <em>Log Domain</em>.
     * @param verbosity     The verbosity. This has been checked to be active already on this stage
     *                      and is provided to be able to be logged out only.
     * @param msg           The log message.
     * @param caller        Information about the scope of the <em>Log Statement</em>..
     * @param lineNumber    The line number of a multi-line message, starting with 0. For single
     *                      line messages this is -1.
     **********************************************************************************************/
    @Override protected void logText( Domain        domain,     Verbosity verbosity,
                                      AString       msg,
                                      ScopeInfo     caller,     int          lineNumber )
    {
        // log it out
        String logCat=      logTag == null ? domain.toString() : logTag;
        String logCatMsg=   msg.toString();

             if ( verbosity == Verbosity.ERROR )   { android.util.Log.e( logCat, logCatMsg );  }
        else if ( verbosity == Verbosity.WARNING ) { android.util.Log.w( logCat, logCatMsg );  }
        else if ( verbosity == Verbosity.INFO )    { android.util.Log.i( logCat, logCatMsg );  }
        else {    if (verboseIsDebug)              { android.util.Log.d( logCat, logCatMsg );  }
                  else                             { android.util.Log.v( logCat, logCatMsg );  } }
    }

    /** ********************************************************************************************
     * Abstract method to be implemented by descendants. This message is called only when multi-line
     * messages are logged. It is called exactly once before a series of #logText calls of a
     * multi-line message and exactly once after such series.<br>
     * This is useful if the writing of text includes the acquisition of system resources
     * (e.g. opening a file).
     *
     * @param phase  Indicates the beginning or end of a multi-line operation.
     **********************************************************************************************/
    @Override protected void notifyMultiLineOp ( Phase phase )  {}



} // class ConsoleLogger
