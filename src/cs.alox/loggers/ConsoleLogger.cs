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


namespace com.aworx.lox.loggers    {


/** ************************************************************************************************
 * <summary>
 *  A logger that logs all messages to the VStudio IDE output window (*using
 *  System.Diagnostics.Debug.WriteLine()*) and/or to the application console (using
 *  *Console.WriteLine()*).
 *
 *  The name of the logger defaults to "CONSOLE".
 *
 *  The constructor sets the level of the root domain, and as such the level of all 'unknown'
 *  domains that inherit from root domain to 'All'. This is because this class represents a logger
 *  that logs into the developer's IDE, and hence just wants to fetch all log domains that the
 *  app and its library uses - unless explicitly set differently in the bootstrap code.  By default,
 *  root domains of loggers have domain level 'Off'.
 * </summary>
 **************************************************************************************************/
public class ConsoleLogger : TextLogger
{
    // #############################################################################################
    // Empty method stubs for release version (with no release logging)
    // #############################################################################################
    #if !(ALOX_DEBUG || ALOX_REL_LOG)
            public ConsoleLogger( String name= "CONSOLE" ){}
    #else

    #if AWORX_VSTUDIO
        /** ****************************************************************************************
         * <summary>
         *  Enables logging to the debug window of Visual Studio.
         *  Available only if AWORX_VSTUDIO is set. Logs to the VStudio output window, when 
         *  Application is debugged.
         *  Defaults to true in ALOX_DEBUG configuration, to false in ALOX_REL_LOG configuration.
         * </summary>
         ******************************************************************************************/
        public    bool            EnableVSDebugConsole
                                                                #if ALOX_DEBUG
                                                                        = true;
                                                                #else
                                                                        = false;
                                                                #endif
    #endif // AWORX_VSTUDIO

        /** ****************************************************************************************
         * <summary>
         *  Enables logging to the application console (std. out).
         *  Defaults to true in ALOX_DEBUG configuration, to false in ALOX_REL_LOG configuration.
         * </summary>
         ******************************************************************************************/
    public        bool            EnableAppConsole
                                                                #if ALOX_DEBUG
                                                                        = true;
                                                                #else
                                                                        = false;
                                                                #endif

    /** ********************************************************************************************
     * <summary> Creates a ConsoleLogger. </summary>
     * <param name="name"> (Optional) The name of the logger, defaults to "CONSOLE" </param>
     **********************************************************************************************/
    public ConsoleLogger( String name= "CONSOLE" )
    : base( name )
    {
        // set default domain level to all: As a app console logger/IDE logger we want to
        // fetch all we can
        RootDomain.SetLevel( Log.DomainLevel.All, false );
    }

    /** ********************************************************************************************
     * <summary>
     *  The implementation of the abstract method of parent class TextLogger. Logs messages to the
     *  application console and/or the VStudio output window.
     * </summary>
     * <param name="domain">     The log domain name. </param>
     * <param name="level">      The log level. This has been checked to be active already on this
     *                           stage and is provided to be able to be logged out only. </param>
     * <param name="msg">        The log message. </param>
     * <param name="indent">     the indentation in the output. Defaults to 0. </param>
     * <param name="caller">     Once compiler generated and passed forward to here. </param>
     * <param name="lineNumber"> The line number of a multi-line message, starting with 0. For
     *                           single line messages this is -1. </param>
     **********************************************************************************************/
    override protected void doTextLog(  AString        domain,     Log.Level     level,
                                        AString        msg,        int            indent,
                                        CallerInfo     caller,     int            lineNumber)
    {
        // check
        #if AWORX_VSTUDIO
            if ( !EnableVSDebugConsole && !EnableAppConsole )
                return;
        #else
            if ( !EnableAppConsole )
                return;
        #endif


        // write to console(s)
        #if !ALOX_NO_CONSOLE
            #if !(ALOX_WP71 || ALOX_WP8)
                if ( EnableAppConsole ) { Console.WriteLine( msg.Buffer(), 0, msg.Length() );    }
            #else
                if ( EnableAppConsole ) { Console.WriteLine( msg.ToString() );                   }
            #endif
        #endif

        // write to visual studio debug window
        #if AWORX_VSTUDIO
            if ( EnableVSDebugConsole ) { System.Diagnostics.Debug.WriteLine( msg.ToString() );  }
        #endif

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
} // class ConsoleLogger
} // namespace

