// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2018 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################

using System.Diagnostics;
using cs.aworx.lib.strings;
using System.IO;
using cs.aworx.lib.lang;
using cs.aworx.lib.threads;

/** ************************************************************************************************
 * This namespace of \b %ALib holds classes and functions that are interfacing with the operating
 * system.
 *
 * As .Net provides standardized system-related classes this namespace is quite empty in the
 * C# version of the AWorx Library.
 **************************************************************************************************/
namespace cs.aworx.lib.system
{

/** ************************************************************************************************
 * Information about processes.
 * \note
 *   In the C# Version of ALib, this class is very reduced, because standard .Net classes
 *   provide enough functionality.
 **************************************************************************************************/
public class ProcessInfo
{
    // #############################################################################################
    // static members
    // #############################################################################################
        /** The process name, retrieved once on request  */
        private static         AString          currentProcessName                           = null;

    // #############################################################################################
    // Interface
    // #############################################################################################

        /** ****************************************************************************************
         * Receives the name of the current process. Evaluated only once, can't change.
         * @return The name of the process.
         ******************************************************************************************/
        public static AString GetCurrentProcessName()
        {
            if( currentProcessName == null  )
            {
                AString pName= new AString( System.AppDomain.CurrentDomain.FriendlyName );
                if ( pName.EndsWith( ".exe", Case.Ignore ) )
                    pName.DeleteEnd( 4 );
                currentProcessName= pName;
            }

            return currentProcessName;
        }
} // class ProcessInfo


} // namespace / EOF
