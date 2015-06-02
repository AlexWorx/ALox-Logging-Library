// #################################################################################################
//  com.aworx.util - Classes we need
//
//  (c) 2013-2015 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################

using System;
using System.Text;
using System.Threading;

namespace com.aworx.util  {

/** ************************************************************************************************
 * <summary>
 *  Interface for AWXU error handler. The AWXU error handler is invoked on internal AWXU errors
 *  caused by illegal arguments or other wrong AWXU use. By default is a simple implementation is
 *  installed that just uses standard output to print the error and warning messages to the application's
 *  console. Applications may implement their own AWXUErrorHandler and attach this to
 *  AWXU using AWXU.ReplaceErrorHandler. Of-course, the AWXUErrorHanlder may be used also
 *  by software based on AWXU. For the use, see documentation of
 *  AWXU.AcquireErrorHandler, AWXU.Error, AWXU.Warning and AWXU.AbortErrorHandler.
 * </summary>
 **************************************************************************************************/
public interface AWXUErrorHandler
{
    /** ********************************************************************************************
     * <summary> Report an AWXU error. </summary>
     * <param name="msg">   The error message. </param>
     **********************************************************************************************/
    void error  ( string msg );

    /** ********************************************************************************************
     * <summary> Report an AWXU warning. </summary>
     * <param name="msg">   The warning message. </param>
     **********************************************************************************************/
    void warning( string msg );
}

/** ************************************************************************************************
 * <summary> The simple, default error handler, just writing the message to the console. </summary>
 **************************************************************************************************/
class ConsoleErrorHandler : AWXUErrorHandler
{
    /** ********************************************************************************************
     * <summary>  Writes an error message to the console. </summary>
     * <param name="msg"> The error message. </param>
     **********************************************************************************************/
    public virtual void error  ( string msg )    { Console.WriteLine( "AWXU Error: " + msg );    }

    /** ********************************************************************************************
     * <summary>  Writes a warning message to the console. </summary>
     * <param name="msg"> The error message. </param>
     **********************************************************************************************/
    public virtual void warning( string msg )    { Console.WriteLine( "AWXU Warning: " + msg );    }
}


/** ************************************************************************************************
 * <summary> Static methods and fields A-Worx Utility library. </summary>
 **************************************************************************************************/
public static class AWXU
{
    // #############################################################################################
    // Error handler interface
    // #############################################################################################

        /** <summary> The error handler singleton. Defaults to ConsoleErrorHandler()            </summary> */
        private static            AWXUErrorHandler    errorHandler              =new ConsoleErrorHandler();

        /** <summary> Provides mutual exclusive access to some inner AWXU data.        </summary> */
        private static            ThreadLock             tlock                  =new ThreadLock();

        /** <summary>
         *    Flag, which if set to true, causes calls to #Error to halt program execution.
         *  Can be set at runtime by just overwriting the value.
         *    If !NDEBUG this 'assert(false)'. If NDEBUG, this defaults to false.
         * </summary> */
        public static bool        HaltOnError                                   =true;

        /** <summary>
         *    Flag, which if set to true, causes calls to #Warning to halt program execution.
         *  Can be set at runtime by just overwriting the value.
         *    If !NDEBUG this 'assert(false)'. If NDEBUG, this defaults to false.
         * </summary> */
        public static bool        HaltOnWarning                                 =true;

        /** ****************************************************************************************
         * <summary>
         *     Returns true, if an error handler singleton was set. In this case, an internal mutex remains
         *  locked. A subsequent call to #Error or #Warning will release the mutex. Alternatively,
         *  #AbortErrorHandler has to be called. The reason for this design is, that the assembly of a
         *  merely complex error string should happen only if an error handler is available. The usual way
         *  to use the error handler is:<br>if ( AWXU.AcquireErrorHandler() ) AWXU.Error( ... );<br> In the case
         *  that no error handler is available, false is returned and the internal mutex is not acquired
         *  and must not be released.
         * </summary>
         * <returns> true if successful. </returns>
         ******************************************************************************************/
        public static bool AcquireErrorHandler()
        {
            tlock.Acquire();
                if ( errorHandler != null )
                    return true; // keep lock acquired!
            tlock.Release();
            return false;
        }


        /** ****************************************************************************************
         * <summary>
         *     Forwards the given message to the current error handler in place. The default error handler
         *  of AWXU will print the message on the process console. Furthermore, in debug execution
         *  the flag HaltOnError is checked. If this is set the program halts or suspends into the debugger
         *  (platform and language specific).
         * </summary>
         * <param name="msg"> The error message. </param>
         ******************************************************************************************/
        public static void Error( string msg )
        {
                System.Diagnostics.Debug.Assert( errorHandler != null,  "Error handler not acquired prior to invokeing Error()" );
                System.Diagnostics.Debug.Assert( tlock.IsAcquired(),    "Error handler not acquired prior to invokeing Error()" );

                errorHandler.error( msg );
            tlock.Release();

            System.Diagnostics.Debug.Assert( !tlock.IsAcquired(),      "Error handler acquired more than once?" );
            System.Diagnostics.Debug.Assert( !AWXU.HaltOnError,          msg );
        }

        /** ****************************************************************************************
         * <summary>
         *     Forwards the given message to the current error handler in place. The default error handler
         *  of AWXU will print the message on the process console. Furthermore, in debug execution
         *  the flag HaltOnWarning is checked. If this is set the program halts or suspends into the debugger
         *  (platform and language specific).
         * </summary>
         * <param name="msg"> The warning message. </param>
         ******************************************************************************************/
        public static void Warning( string msg )
        {
                System.Diagnostics.Debug.Assert( errorHandler != null,  "Error handler not acquired prior to invokeing Warning()" );
                System.Diagnostics.Debug.Assert( tlock.IsAcquired(),    "Error handler not acquired prior to invokeing Warning()" );

                errorHandler.warning( msg );
            tlock.Release();

            System.Diagnostics.Debug.Assert( !tlock.IsAcquired(),      "Error handler acquired more than once?" );
            System.Diagnostics.Debug.Assert( !AWXU.HaltOnWarning,      msg );
        }

        /** ****************************************************************************************
         * <summary>
         *     Releases the internal mutex which gets acquired calling #AcquireErrorHandler. This method
         *  can be used to avoid calling #Warning or #Error.
         * </summary>
         ******************************************************************************************/
        public static void AbortErrorHandler()
        {
                System.Diagnostics.Debug.Assert( errorHandler != null,  "Error handler not acquired prior to invokeing AbortErrorHandler()" );
                System.Diagnostics.Debug.Assert( tlock.IsAcquired(),    "Error handler not acquired prior to invokeing AbortErrorHandler()" );
            tlock.Release();
            System.Diagnostics.Debug.Assert( !tlock.IsAcquired(),      "Error handler acquired more than once?" );
        }

        /** ****************************************************************************************
         * <summary>
         *     Replaces the current (if any) error handler singleton by the one provided. If a different
         *  error handler was set before, the former one, will be returned (e.g. for deletion).
         *  If null is provided, the error handler will be unset.
         * </summary>
         * <param name="newErrorHandler"> The error handler to set. </param>
         * <returns> The former error handler. </returns>
         ******************************************************************************************/
        public static AWXUErrorHandler ReplaceErrorHandler( AWXUErrorHandler newErrorHandler )
        {
            tlock.Acquire();
                AWXUErrorHandler oldEH= errorHandler;
                errorHandler= newErrorHandler;
            tlock.Release();
            return oldEH;
        }


    // #############################################################################################
    // Other static interface methods
    // #############################################################################################

        /** ****************************************************************************************
         * <summary>
         *    This is calling Thread.Sleep(). This is for compatibility with other platform
         *    versions of A-Worx Utility Classes.
         *    Variants of this method are #SleepMicros and #SleepNanos.
         * </summary>
         * <param name="millisecs">    Sleep time in milliseconds. </param>
         ******************************************************************************************/
        public static void SleepMillis(int millisecs)
        {
            if ( millisecs > 0 )
                Thread.Sleep( millisecs );
        }

        /** ****************************************************************************************
         * <summary>
         *    This is calling Thread.Sleep(). This is for compatibility with other platform
         *    versions of A-Worx Utility Classes.
         *    Variants of this method are #SleepMillis and #SleepNanos.
         * </summary>
         * <param name="microsecs">    Sleep time in microseconds. </param>
         ******************************************************************************************/
        public static void SleepMicros( long microsecs )
        {
            if ( microsecs > 0 )
                Thread.Sleep( TimeSpan.FromTicks( microsecs * 10L ) );
        }

        /** ****************************************************************************************
         * <summary>
         *    This is calling Thread.Sleep(). This is for compatibility with other platform
         *    versions of A-Worx Utility Classes.
         *    Variants of this method are #SleepMillis and #SleepMicros.
         * </summary>
         * <param name="nanosecs">    Sleep time in microseconds. </param>
         ******************************************************************************************/
        public static void SleepNanos( long nanosecs )
        {
            if ( nanosecs > 0 )
                Thread.Sleep( TimeSpan.FromTicks( nanosecs / 100L ) );
        }

}// class AWXU



} // namespace / EOF
