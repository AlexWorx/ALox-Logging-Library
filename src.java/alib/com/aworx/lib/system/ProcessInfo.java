// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2018 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################

/** ************************************************************************************************
 * This package of \b %ALib holds classes and functions that are interfacing with the operating
 * system.
 *
 * As Java provides standardized system-related classes this namespace is quite empty in the
 * Java version of the AWorx Library.
 **************************************************************************************************/
package com.aworx.lib.system;

import com.aworx.lib.strings.AString;

/** ************************************************************************************************
 * Information about processes.
 * \note
 *   In the Java Version of \b %ALib, this class is very reduced, because java core classes provide
 *   enough functionality.
 **************************************************************************************************/
public class ProcessInfo
{
    // #############################################################################################
    // static functionality
    // #############################################################################################
        /** The process name, retrieved once on request  */
        private static          AString          processName                                 = null;

   // #############################################################################################
   // Interface
   // #############################################################################################

        /** ****************************************************************************************
         * Receives the name of the current process. Evaluated only once, can't change.
         * \note In the Java version of \b %ALib, this is the name of the class whose \c main() method
         *       was started.
         * @return The name of the process.
         ******************************************************************************************/
        public static AString getCurrentProcessName()
        {
            if( processName == null  )
            {
                StackTraceElement[] stack=          Thread.currentThread ().getStackTrace ();
                AString pName=   new AString( stack[stack.length - 1].getClassName () );
                int dotPos=    pName.lastIndexOf( '.' );
                if (dotPos >= 0)
                    pName.deleteStart( dotPos + 1 );

                processName= pName;
            }
            return processName;
        }


}
