// #################################################################################################
//  com.aworx.util - Classes we need
//
//  (c) 2013-2015 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
package com.aworx.util;

/** ************************************************************************************************
 * The simple, default error handler, just writing the messageto the console.
 **************************************************************************************************/
class ConsoleErrorHandler implements AWXUErrorHandler
{
    /** ********************************************************************************************
     * Writes an error message to the console.
     * @param msg   The error message.
     **********************************************************************************************/
    @Override
    public void error  ( String msg )            { System.out.println( "AWXU Error: "   + msg );    }

    /** ********************************************************************************************
     * Writes a warning message to the console.
     * @param msg   The error message.
     **********************************************************************************************/
    @Override
    public void warning( String msg )            { System.out.println( "AWXU Warning: " + msg );    }
}

/** ************************************************************************************************
 * Static methods and fields A-Worx Utility library.
 **************************************************************************************************/
public final class AWXU
{
    // #############################################################################################
    // Error handler interface
    // #############################################################################################

        /** The error handler singleton. Defaults to ConsoleErrorHandler()             */
        private static  AWXUErrorHandler    errorHandler                    = new ConsoleErrorHandler();

        /** Provides mutual exclusive access to some inner AWXU data.         */
        private static  ThreadLock          tlock                           = new ThreadLock();

        /**
         *    Flag, which if set to true, causes calls to #error to halt program execution.
         *  Can be set at runtime by just overwriting the value.
         *    If !NDEBUG this 'assert(false)'. If NDEBUG, this defaults to false.
         *  */
        public  static  boolean             haltOnError                     = true;

        /**
         *    Flag, which if set to true, causes calls to #warning to halt program execution.
         *  Can be set at runtime by just overwriting the value.
         *    If !NDEBUG this 'assert(false)'. If NDEBUG, this defaults to false.
         *  */
        public  static  boolean             haltOnWarning                   = true;

        /** ****************************************************************************************
         *  Returns true, if an error handler singleton was set. In this case, an internal mutex remains
         *  locked. A subsequent call to error or #warning will release the mutex. Alternatively,
         *  #abortErrorHandler has to be called. The reason for this design is, that the assembly of a
         *  merely complex error string should happen only if an error handler is available. The usual way
         *  to use the error handler is:<br>if ( AWXU.acquireErrorHandler() ) AWXU.error( ... );<br> In the case
         *  that no error handler is available, false is returned and the internal mutex is not acquired
         *  and must not be released.
         * @return true if successful.
         ******************************************************************************************/
        public  static boolean acquireErrorHandler()
        {
            tlock.acquire();
                if ( errorHandler != null )
                    return true; // keep lock acquired!
            tlock.release();
            return false;
        }


        /** ****************************************************************************************
         *  Forwards the given error message to the current error handler in place. The default error handler
         *  of AWXU will print the message on the process console. Furthermore, in debug execution
         *  the flag HaltOnError is checked. If this is set the program halts or suspends into the debugger
         *  (platform and language specific).
         *
         * @param msg The error message.
         ******************************************************************************************/
        public  static void error( String msg )
        {

                assert errorHandler != null :    "Error handler not acquired prior to invokeing Error()";
                assert tlock.isAcquired(null) :    "Error handler not acquired prior to invokeing Error()";

                errorHandler.error( msg );
            tlock.release();

            assert !tlock.isAcquired(null) :  "Error handler acquired more than once?";
            assert !AWXU.haltOnError :  msg;
        }

        /** ****************************************************************************************
         *     Forwards the given message to the current error handler in place. The default error handler
         *  of AWXU will print the message on the process console. Furthermore, in debug execution
         *  the flag HaltOnWarning is checked. If this is set the program halts or suspends into the debugger
         *  (platform and language specific).
         *
         * @param msg The warning message.
         ******************************************************************************************/
        public  static void warning( String msg )
        {
                assert errorHandler != null :    "Error handler not acquired prior to invokeing Warning()";
                assert tlock.isAcquired(null) :    "Error handler not acquired prior to invokeing Warning()";

                errorHandler.warning( msg );
            tlock.release();

            assert !tlock.isAcquired(null) :  "Error handler acquired more than once?";
            assert !AWXU.haltOnWarning:  msg;
        }

        /** ****************************************************************************************
         *     Releases the internal mutex which gets acquired calling #acquireErrorHandler. This method
         *  can be used to avoid calling #warning or #error.
         ******************************************************************************************/
        public  static void abortErrorHandler()
        {
                assert errorHandler != null :    "Error handler not acquired prior to invokeing AbortErrorHandler()";
                assert tlock.isAcquired(null) :    "Error handler not acquired prior to invokeing AbortErrorHandler()";
            tlock.release();
            assert !tlock.isAcquired(null) :  "Error handler acquired more than once?";
        }

        /** ****************************************************************************************
         *     Replaces the current (if any) error handler singleton by the one provided. If a different
         *  error handler was set before, the former one, will be returned (e.g. for deletion).
         *  If null is provided, the error handler will be unset.
         *
         * @param newErrorHandler The error handler to set.
         * @return The former error handler.
         ******************************************************************************************/
        public  static AWXUErrorHandler replaceErrorHandler( AWXUErrorHandler newErrorHandler )
        {
            tlock.acquire();
                AWXUErrorHandler oldEH= errorHandler;
                errorHandler= newErrorHandler;
            tlock.release();
            return oldEH;
        }


    // #############################################################################################
    // Other static interface methods
    // #############################################################################################

        /** ****************************************************************************************
         * This is calling Thread.sleep() and catching any exception. If the AWXU Error handler is set,
         * its warning() method is invoked should an exception be thrown.
         * Variants of this method are #sleepMicros and #sleepNanos.
         *
         * @param millisecs Sleep time in milliseconds.
         ******************************************************************************************/
        public  static void sleepMillis( int millisecs )
        {
            if ( millisecs > 0 )
            {
                try
                {
                    Thread.sleep( millisecs );
                }
                catch( InterruptedException e )
                {
                    if ( errorHandler != null )
                        errorHandler.warning( "AWXU.sleep() caught exception" );
                }
            }
        }

        /** ****************************************************************************************
         * This is calling Thread.sleep() and catching any exception. If the AWXU Error handler 
         * is set, its warning() method is invoked should an exception be thrown.
         * Variants of this method are #sleepMillis and #sleepNanos.
         * @param microsecs Sleep time in microseconds.
         ******************************************************************************************/
        public  static void sleepMicros( long microsecs )
        {
            if ( microsecs > 0 )
            {
                long millisecs= microsecs / 1000;
                int nanos=        ((int) ( microsecs % 1000L ))  * 1000;
                try
                {
                    Thread.sleep( millisecs, nanos );
                }
                catch( InterruptedException e )
                {
                    if ( errorHandler != null )
                        errorHandler.warning( "AWXU.sleep() caught exception" );
                }
            }
        }

        /** ****************************************************************************************
         * This is calling Thread.sleep() and catching any exception. If the AWXU Error handler 
         * is set, its warning() method is invoked should an exception be thrown.
         * Variants of this method are #sleepMillis and #sleepNanos.
         *
         * @param nanosecs Sleep time in nanoseconds.
         ******************************************************************************************/
        public  static void sleepNanos( long nanosecs )
        {
            if ( nanosecs > 0 )
            {
                long millisecs= nanosecs / 1000000;
                int  nanos=        (int) ( nanosecs % 1000000L );

                try
                {
                    Thread.sleep( millisecs, nanos );
                }
                catch( InterruptedException e )
                {
                    if ( errorHandler != null )
                        errorHandler.warning( "AWXU.sleep() caught exception" );
                }
            }
        }

}// class AWXU
