// #################################################################################################
//  com.aworx.util - Classes we need
//
//  (c) 2013-2015 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
package com.aworx.util;

/** ************************************************************************************************
 * Interface for AWXU error handler. The AWXU error handler is invoked on internal AWXU errors
 * caused by illegal arguments or other wrong AWXU use. By default is a simple implementation is
 * installed that just uses the console to print the error and warning messages to the application's
 * standard output. Applications may implement their own AWXUErrorHandler and attach this to
 * AWXU using AWXU.replaceErrorHandler. Of-course, the AWXUErrorHanlder may be used also
 * by software based on AWXU. For the use, see documentation of AWXU.AcquireErrorHandler,
 * AWXU.error, AWXU.Warning and AWXU.AbortErrorHandler.
 **************************************************************************************************/
public interface AWXUErrorHandler
{
    /** ********************************************************************************************
     * Report an AWXU Error.
     * @param msg   The error message.
     **********************************************************************************************/
    public void error  ( String msg );

    /** ********************************************************************************************
     * Report an AWXU Warning.
     * @param msg   The error message.
     **********************************************************************************************/
    public void warning( String msg );
}
