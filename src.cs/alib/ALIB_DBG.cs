// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################

using System.Runtime.CompilerServices;
using System;
using System.Diagnostics;
using System.Text;
using System.Threading;
using cs.aworx.lib.threads;
using cs.aworx.lib.config;
using cs.aworx.lib.time;
using cs.aworx.lib.strings;
using cs.aworx.lib.lang;


namespace cs.aworx.lib {

/** ************************************************************************************************
 * This class contains static shortcuts to to methods of class
 * \ref cs::aworx::lib::lang::Report "Report".
 * All invocations of the static methods get "pruned" (removed) from release compilations due to
 * the method annotation <c>"[Conditional( "DEBUG" )]"</c>
 **************************************************************************************************/
public static class ALIB_DBG
{
        /** ****************************************************************************************
         * Invokes \ref cs::aworx::lib::lang::Report::DoReport "Report.DoReport".
         * This method is pruned from release code.
         *
         * @param type  The msg type.
         * @param msg   The msg to be passed to the
         *              \ref cs::aworx::lib::lang::ReportWriter "ReportWriter".
         * @param optMsg2  An optional additional report object.
         * @param optMsg3  An optional additional report object.
         * @param optMsg4  An optional additional report object.
         * @param cln (Optional) Caller info, compiler generated. Please omit.
         * @param csf (Optional) Caller info, compiler generated. Please omit.
         * @param cmn (Optional) Caller info, compiler generated. Please omit.
         ******************************************************************************************/
        [Conditional( "DEBUG" )]
        public static void REPORT( int type, String msg,
                                   Object optMsg2 =null, Object optMsg3 =null, Object optMsg4 =null,
        [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
        {
            Report.GetDefault().DoReport( type, msg,  optMsg2, optMsg3, optMsg4, csf,cln,cmn );
        }

        /** ****************************************************************************************
         * Invokes \ref cs::aworx::lib::lang::Report::DoReport "Report.DoReport".
         * This method is pruned from release code.
         *
         * @param msg  The msg to be passed to the
         *             \ref cs::aworx::lib::lang::ReportWriter "ReportWriter".
         * @param optMsg2  An optional additional report object.
         * @param optMsg3  An optional additional report object.
         * @param optMsg4  An optional additional report object.
         * @param cln (Optional) Caller info, compiler generated. Please omit.
         * @param csf (Optional) Caller info, compiler generated. Please omit.
         * @param cmn (Optional) Caller info, compiler generated. Please omit.
         ******************************************************************************************/
        [Conditional( "DEBUG" )]
        public static void ERROR( String msg ,
                                  Object optMsg2 =null, Object optMsg3 =null, Object optMsg4 =null,
        [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
        {
            Report.GetDefault().DoReport( 0, msg,  optMsg2, optMsg3, optMsg4, csf,cln,cmn );
        }

        /** ****************************************************************************************
         * Invokes \ref cs::aworx::lib::lang::Report::DoReport "Report.DoReport".
         * This method is pruned from release code.
         *
         * @param msg  The msg to be passed to the
         *             \ref cs::aworx::lib::lang::ReportWriter "ReportWriter".
         * @param optMsg2  An optional additional report object.
         * @param optMsg3  An optional additional report object.
         * @param optMsg4  An optional additional report object.
         * @param cln (Optional) Caller info, compiler generated. Please omit.
         * @param csf (Optional) Caller info, compiler generated. Please omit.
         * @param cmn (Optional) Caller info, compiler generated. Please omit.
         ******************************************************************************************/
        [Conditional( "DEBUG" )]
        public static void WARNING( String msg,
                                    Object optMsg2 =null, Object optMsg3 =null, Object optMsg4 =null,
        [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
        {
            Report.GetDefault().DoReport( 1, msg,  optMsg2, optMsg3, optMsg4, csf,cln,cmn );
        }

        /** ****************************************************************************************
         * If given condition is false, method
         * \ref cs::aworx::lib::lang::Report::DoReport "Report.DoReport" gets invoked with the standard message
         * "Internal Error".
         * This method is pruned from release code.
         *
         * @param cond The condition that has to be met to prevent
         *             \ref cs::aworx::lib::lang::ReportWriter "ReportWriter" call.
         * @param cln (Optional) Caller info, compiler generated. Please omit.
         * @param csf (Optional) Caller info, compiler generated. Please omit.
         * @param cmn (Optional) Caller info, compiler generated. Please omit.
         ******************************************************************************************/
        [Conditional( "DEBUG" )]
        public static void ASSERT( bool cond,
        [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
        {
            if ( !cond )
                Report.GetDefault().DoReport( 0, "Internal Error",  null,null,null, csf,cln,cmn );
        }


        /** ****************************************************************************************
         * If given condition is false, method
         * \ref cs::aworx::lib::lang::Report::DoReport "Report.DoReport" gets invoked with the given message.
         * This method is pruned from release code.
         *
         * @param cond The condition that has to be met to prevent
         *             \ref cs::aworx::lib::lang::ReportWriter "ReportWriter" call.
         * @param msg  The msg to be passed to the
         *             \ref cs::aworx::lib::lang::ReportWriter "ReportWriter".
         * @param optMsg2  An optional additional report object.
         * @param optMsg3  An optional additional report object.
         * @param optMsg4  An optional additional report object.
         * @param cln (Optional) Caller info, compiler generated. Please omit.
         * @param csf (Optional) Caller info, compiler generated. Please omit.
         * @param cmn (Optional) Caller info, compiler generated. Please omit.
         ******************************************************************************************/
        [Conditional( "DEBUG" )]
        public static void ASSERT_ERROR( bool cond, String msg,
                                        Object optMsg2 =null, Object optMsg3 =null, Object optMsg4 =null,
        [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
        {
            if ( !cond )
                Report.GetDefault().DoReport( 0, msg,  optMsg2, optMsg3, optMsg4, csf,cln,cmn );
        }

        /** ****************************************************************************************
         * If given condition is false, method
         * \ref cs::aworx::lib::lang::Report::DoReport "Report.DoReport" gets invoked with the given message.
         * This method is pruned from release code.
         *
         * @param cond The condition that has to be met to prevent
         *             \ref cs::aworx::lib::lang::ReportWriter "ReportWriter" call.
         * @param msg  The msg to be passed to the
         *             \ref cs::aworx::lib::lang::ReportWriter "ReportWriter".
         * @param optMsg2  An optional additional report object.
         * @param optMsg3  An optional additional report object.
         * @param optMsg4  An optional additional report object.
         * @param cln (Optional) Caller info, compiler generated. Please omit.
         * @param csf (Optional) Caller info, compiler generated. Please omit.
         * @param cmn (Optional) Caller info, compiler generated. Please omit.
         ******************************************************************************************/
        [Conditional( "DEBUG" )]
        public static void ASSERT_WARNING( bool cond, String msg,
                                           Object optMsg2 =null, Object optMsg3 =null, Object optMsg4 =null,
        [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
        {
            if ( !cond )
                Report.GetDefault().DoReport( 1, msg,  optMsg2, optMsg3, optMsg4, csf,cln,cmn );
        }
}// class ALIB_DBG



} // namespace / EOF
