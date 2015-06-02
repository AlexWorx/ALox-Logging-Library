// #################################################################################################
//  com.aworx.util - Classes we need
//
//  (c) 2013-2015 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################

using System;
using System.Text;
using System.Threading;
using com.aworx.lox;

namespace com.aworx.util  {


/** ************************************************************************************************
 * <summary>
 *  This class allows *mutual exclusive access* to resources shared by different threads.
 *  In other words, access to certain data that is accessed by different threads, can
 *  be protected if each thread (aka critical section code) uses the same ThreadLock to control the
 *  access to such data.
 *
 *  If an Acquire is not followed by a corresponding Release, other threads will not be able to
 *  gain control to this object and will wait endlessly (deadlock situation). To avoid this,
 *  it is a good practice to embed pairs of Acquire()/Release() calls into try/finally statements
 *  as follows:
 *
 *      try { tl.Acquire(); ...critical section code .... } finally { tl.Release() }
 *
 * ThreadLock uses an internal counter to allow multiple calls to Acquire() and to be freed only
 * when a same amount of Release() calls are performed. This behavior can be switched off by a
 * constructor parameter. If switched off, each recursive Acquire() call will not be counted and
 * each call to Release() will instantly free the mutex. This mode is not very recommended,
 * the standard use is recursive mode.
 *
 * Furthermore, ThreadLock allows to disable locking using setUnsafe(). The objective here is to
 * gain execution speed, as thread synchronization causes relatively expensive system calls.
 * Nevertheless, it is sometimes obvious that the same code may run in a thread safe mode
 * one time and without thread locking the next time. Therefore, for performance critical
 * code, it is quite useful to be able to control this behaviour.
 *
 *  Caution: Use this class with great care. Deadlocks are not easy to detect and debug. Use
 *  this class only if standard synchronization of the Java language seems too limited and mechanisms
 *  like the class uses internally would need to be implemented.
 * </summary>
 **************************************************************************************************/
public class ThreadLock
{
    // #############################################################################################
    // Public fields
    // #############################################################################################

    /** <summary>
     *    This is a threshold that causes Acquire() to send a warning to the AWXU error handler if acquiring the
     *    access takes longer than the given number of milliseconds.
     *    To disable such messages, set this value to 0. Default is 1 second.
     * </summary> */
    public    int               waitWarningTimeLimitInMillis                                =1000;

    /** <summary>
     *    Limit of recursions. If limit is reached or a multiple of it, an error is passed to
     *    the AWXU error handler. Defaults is 10.
     * </summary> */
    public    int               RecursionWarningThreshold                                   =10;

    // #############################################################################################
    // Protected fields
    // #############################################################################################

    /** <summary> Flag if recursion support is on. If not, nested locks are not counted. </summary> */
    protected bool              recursiveMode;

    /** <summary> Counter for the number of Acquire() calls of the current thread. </summary> */
    protected int               lockCount;

    /** <summary> The current owner of the ThreadLock. </summary> */
    protected Thread            owner;

    /** <summary> The internal object to lock on. </summary> */
    protected Object            mutex;

    /**  The internal object to measure the time */
    protected Ticks             waitTime                                                    =new Ticks();


    // #############################################################################################
    // Constructors
    // #############################################################################################

    /** ********************************************************************************************
     * <summary>
     *  Create a ThreadLock that allows recursion. A warning will be given (AWXU Error) when the
     *  given recursion level is reached (and each multiple of it). In addition the lock can be
     *  initialized to be unsafe, which means the locking critical sections is disabled.
     * </summary>
     * <param name="recursiveMode">    (Optional) Flag if recursion support is on. If not, nested locks
     *                                 are not counted. </param>
     * <param name="setUnsafeMode">    (Optional) True to set this unsafe. Please don't! </param>
     **********************************************************************************************/
    public ThreadLock( bool recursiveMode= true, bool setUnsafeMode = false  )
    {
        // save parameters
        this.recursiveMode=             recursiveMode;

        // set safeness
        SetUnsafe( setUnsafeMode );
    }

    // #############################################################################################
    // Interface
    // #############################################################################################


    /** ********************************************************************************************
     * <summary>
     *  Thread which invokes this method gets registered  as the current owner of this object, until the
     *  same thread releases the ownership invoking Release().
     *  In the case that this object is already owned by another thread, the invoking thread is suspended
     *  until ownership can be gained.
     *  Multiple (nested) calls to this method are counted and the object is only released when the same
     *  number of Release() calls have been made.
     * </summary>
     **********************************************************************************************/
    public void Acquire()
        {
            // are we in unsafe mode?
            if ( mutex == null )
            {
                // we are still increasing the lockCount
                lockCount=recursiveMode ? lockCount + 1
                                        : 1;

                // reached warning limit
                if ( lockCount <= 0 )
                {
                    if ( AWXU.AcquireErrorHandler() )
                        AWXU.Error( "ThreadLock.Acquire() unsafe mode: Counter invalid (<= 0): This should never happen. Set lock to safe mode!" );
                }

                else if ( lockCount % RecursionWarningThreshold == 0  && AWXU.AcquireErrorHandler() )
                    AWXU.Warning( "ThreadLock.Acquire() Warning: Recursion depth " + lockCount + ". To prevent this, change ThreadSafe.recursionWarningThreshold or fix your code!");

            // end of unsafe version of this method
            return;
        }

        // get current thread
        Thread thisThread= Thread.CurrentThread;

        // synchronize on mutex
        lock ( mutex )
        {
            // we already own the thread
            if( owner == thisThread )
            {
                // we are still increasing the lockCount
                lockCount=  recursiveMode     ? lockCount + 1
                                            : 1;
                // reached warning limit
                if ( lockCount % RecursionWarningThreshold == 0  && AWXU.AcquireErrorHandler() )
                    AWXU.Warning( "ThreadLock.Acquire() Warning: Recursion depth " + lockCount + ". To prevent this, change ThreadSafe.recursionWarningThreshold or fix your code!");

                return;
            }

            // we do not own this thread, wait until lock is free
            bool hasWarned= false;
            while( owner != null )
            {
                try
                {
                    // wait unconditional
                    if ( waitWarningTimeLimitInMillis <= 0 || hasWarned )
                        Monitor.Wait( mutex );

                    // wait with time limit
                    else
                    {
                        waitTime.Set();
                            Monitor.Wait( mutex, waitWarningTimeLimitInMillis );
                        long time=   waitTime.Age().InMillis();
                        if ( time >= waitWarningTimeLimitInMillis )
                        {
                            hasWarned= true;
                            if ( AWXU.AcquireErrorHandler() )
                                AWXU.Warning(    "ThreadLock.Acquire() took " + time +  " ms, which exceeds given limit of " + waitWarningTimeLimitInMillis
                                              +  " ms. Change your codes critical section length if possible. Thread ID/Name: "  + thisThread.ManagedThreadId + "/" + thisThread.Name );
                        }

                    }
                }
                catch(Exception ) {} // ignore spurious wakeups
            }

            // take control
            owner=        thisThread;
            lockCount=    1;

        } // synchronized
    }

    /** ********************************************************************************************
     * <summary>
     *  Releases ownership of this object. If Acquire() was called multiple times before, the same
     *  number of calls to this method have to be performed to release ownership.
     * <summary>
     **********************************************************************************************/
    public void Release()
    {
        // are we in unsafe mode?
        if ( mutex == null )
        {
            // not locked
            if( recursiveMode && lockCount == 0 && AWXU.AcquireErrorHandler() )
                 AWXU.Error( "ThreadLock.Release() without having the lock (in unsafe mode). This must never happen, check your code, set lock to safe mode!" );

            // we are still decreasing the lockCount
            lockCount=  recursiveMode   ? lockCount - 1
                                        : 0;

            // end of unsafe version of this method
            return;
        }

        // synchronize on mutex
        lock ( mutex )
        {
            // not locked
            if( lockCount == 0 && AWXU.AcquireErrorHandler() )
                AWXU.Error( "ThreadLock.Release() without having the lock. This must never happen, check your code!" );

            // decreasing the lockCount
            lockCount=  recursiveMode   ? lockCount - 1
                                        : 0;

            // release and notify next waiting thread
            if( lockCount == 0 )
            {
                owner= null;
                Monitor.Pulse( mutex );
            }
        } // synchronized
    }

    /** ********************************************************************************************
     * <summary>
     *    Identifies if the provided thread is the actual owner of this ThreadLock. If the parameter is
     *    omitted, then it is tested if the current thread owns this lock.
     *    Note: This method is provided mainly for debugging and implementing debug assertions into the code.
     *    It is *not* considered a good practice to use this method for implementing software logic.
     *    In contrast the software should be designed in a way, that it is always clear who owns a ThreadLock
     *    or at least that acquiring a thread lock can be performed instead.
     * </summary>
     * <param name="thread"> The thread to test current ownership of this. If omitted the ownership is
     *                          identified for the current thread.</param>
     * <returns> True if this is acquired by the given (or current) thread, false if not. </returns>
     **********************************************************************************************/
    public bool IsAcquired( Thread thread= null )
    {
        if ( IsUnsafe() )
            return lockCount > 0 ;

        if ( owner == null )
            return false;

        return  owner == ( thread != null ? thread : Thread.CurrentThread ) ;
    }


    /** ********************************************************************************************
     * <summary>
     *  If parameter is true, the whole locking system is disabled. The only objective here is to
     *  to gain execution speed, as thread synchronization causes relatively expensive system calls.
     *  Use this method only if you are 100% sure that your (otherwise) critical section are executed
     *  in a single threaded environment. And: "relative expensive" means: they are not really expensive.
     *  This only for the rare case that your critical section is very, very frequently executed.
     * </summary>
     * <param name="setUnsafe">    If true, ThreadLock is set unsafe, safe otherwise.</param>
     *************************************************************************************************/
    public void SetUnsafe( bool setUnsafe )
    {
        // are we in unsafe mode?
        if ( mutex == null )
        {
            // already locked? AWXU Error
            if( lockCount != 0  && AWXU.AcquireErrorHandler() )
                AWXU.Error(      "ThreadLock::SetUnsafe(): Cannot switch safeness mode while already locked. Current mode: unsafe, requested mode: "
                            +    ( setUnsafe ? "unsafe." : "safe." ) );

            //  switch on?
            if( ! setUnsafe )
                mutex= new Object();

            // end of unsafe version of this method
            return;
        }

        // synchronize on mutex
        lock ( mutex )
        {
            // already locked? AWXU Error
            if( owner != null  && AWXU.AcquireErrorHandler() )
                AWXU.Error(      "ThreadLock::SetUnsafe(): Cannot switch safeness mode while already locked. Current mode: safe, requested mode: "
                             +   ( setUnsafe ? "unsafe." : "safe." ) );

            //  switch off?
            if( setUnsafe )
                mutex= null;
        }

    }

    /** ********************************************************************************************
     * <summary>    Query if this instance was set to unsafe mode. </summary>
     * <returns>    True if unsafe, false if not. </returns>
     **********************************************************************************************/
    public bool IsUnsafe()
    {
        return ( mutex == null );
    }

    /** ********************************************************************************************
     * <summary>
     *    Returns a  String that represents this object.
     *    This method should only be used for debugging purposes as it is not determined that the values
     *  returned are consistent and not changed in the next moment. If the thread that currently acquired
     *  this ThreadLock is deleted during the execution of this method, the method might even crash
     *  (OK, not in the C# version!) while accessing the owner thread's name property. Use with care,
     *  for debug and only if you know what your are doing.
     * </summary>
     * <returns> A String that represents this object. </returns>
     **********************************************************************************************/
    public override String ToString()
    {
        Thread owner= this.owner;
        return         ( owner != null ? owner.ToString() : "null")
                 +    ", locks=" + lockCount
                 +    ", unsafe mode= " + ( mutex==null)
                 +    ", recursive=" +recursiveMode;
    }



}// class ThreadLock


} // namespace / EOF
