// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
package com.aworx.lib;


import com.aworx.lib.lang.Report;

/** ************************************************************************************************
 * This class contains static debug shortcuts to to methods of class
 * \ref com::aworx::lib::lang::Report "Report".
 * All invocations of the static methods get "pruned" (removed) from release compilations if
 * used with \b %ALox default configuration of \b Proguard. See \b %ALox documentation on
 * project setup and pruning for more information.
 **************************************************************************************************/
public final class ALIB_DBG
{
    // #############################################################################################
    // ReportWriter debug interface
    // #############################################################################################

        /** ****************************************************************************************
         * Invokes
         * \ref com::aworx::lib::lang::Report::doReport "Report.doReport".
         * This method is pruned from release code.
         *
         * @param type  The msg type.
         * @param msg   The msg to be passed to the \ref com::aworx::lib::lang::ReportWriter "ReportWriter".
         ******************************************************************************************/
        public static void REPORT( int type, Object... msg )
        {
            Report.getDefault().doReport( type, msg );
        }

        /** ****************************************************************************************
         * Invokes
         * \ref com::aworx::lib::lang::Report::doReport "Report.doReport".
         * This method is pruned from release code.
         *
         *  @param msg  The msg to be passed to the \ref com::aworx::lib::lang::ReportWriter "ReportWriter".
         ******************************************************************************************/
        public static void ERROR( Object... msg )
        {
            Report.getDefault().doReport( 0, msg );
        }

        /** ****************************************************************************************
         * Invokes
         * \ref com::aworx::lib::lang::Report::doReport "Report.doReport".
         * This method is pruned from release code.
         *
         *  @param msg  The msg to be passed to the
         *              \ref com::aworx::lib::lang::ReportWriter "ReportWriter".
         ******************************************************************************************/
        public static void WARNING( Object... msg )
        {
            Report.getDefault().doReport( 1, msg );
        }

        /** ****************************************************************************************
         * If given condition is false, method
         * \ref com::aworx::lib::lang::Report::doReport "Report.doReport" gets invoked with the standard message
         * "Internal Error".
         * This method is pruned from release code.
         *
         * @param cond The condition that has to be met to prevent
         *             \ref com::aworx::lib::lang::ReportWriter "ReportWriter" call.
         ******************************************************************************************/
        public static void ASSERT( boolean cond )
        {
            if ( !cond )
                Report.getDefault().doReport( 0, "Internal Error" );
        }


        /** ****************************************************************************************
         * If given condition is false, method
         * \ref com::aworx::lib::lang::Report::doReport "Report.doReport" gets invoked with the given message.
         * This method is pruned from release code.
         *
         * @param cond The condition that has to be met to prevent
         *             \ref com::aworx::lib::lang::ReportWriter "ReportWriter" call.
         * @param msg  The msg to be passed to the \ref com::aworx::lib::lang::ReportWriter "ReportWriter".
         ******************************************************************************************/
        public static void ASSERT_ERROR( boolean cond, Object... msg )
        {
            if ( !cond )
                Report.getDefault().doReport( 0, msg );
        }

        /** ****************************************************************************************
         * If given condition is false, method
         * \ref com::aworx::lib::lang::Report::doReport "Report.doReport" gets invoked with the given message.
         * This method is pruned from release code.
         *
         * @param cond The condition that has to be met to prevent
         *             \ref com::aworx::lib::lang::ReportWriter "ReportWriter" call.
         * @param msg  The msg to be passed to the \ref com::aworx::lib::lang::ReportWriter "ReportWriter".
         ******************************************************************************************/
        public static void ASSERT_WARNING( boolean cond, Object... msg )
        {
            if ( !cond )
                Report.getDefault().doReport( 1, msg );
        }
}// class ALIB
