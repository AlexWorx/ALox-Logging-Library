// #################################################################################################
//  com.aworx.util - Classes we need
//
//  (c) 2013-2015 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
package com.aworx.util;


/** ************************************************************************************************
 * This class allows *mutual exclusive access* to resources shared by different threads.
 * In other words, access to certain data that is accessed by different threads, can
 * be protected if each thread (aka critical section code) uses the same ThreadLock to control the
 * access to such data.
 *
 * If a acquire() is not followed by a corresponding release(), other threads will not be able to
 * gain control to this object and will wait endlessly (deadlock situation). To avoid this, it
 * is a good practice to embed pairs of acquire()/release() calls into try/finally statements as
 * follows:
 *
 *     try { tl.acquire(); ...critical section code .... } finally { tl.release() }
 *
 * ThreadLock uses an internal counter to allow multiple calls to acquire() and to be freed only
 * when a same amount of release() calls are performed. This behavior can be switched off by a
 * constructor parameter. If switched off, each recursive acquire() call will not be counted and
 * each call to release() will instantly free the mutex. This mode is not very recommended,
 * the standard use is recursive mode.
 *
 * Furthermore, ThreadLock allows to disable locking using setUnsafe(). The objective here is to
 * gain execution speed, as thread synchronization causes relatively expensive system calls.
 * Nevertheless, it is sometimes obvious that the same code may run in a thread safe mode
 * one time and without thread locking the next time. Therefore, for performance critical
 * code, it is quite useful to be able to control this behavior.
 *
 * Caution: Use this class with great care. Deadlocks are not easy to detect and debug. Use this
 * class only if standard synchronization of the Java language seems too limited and mechanisms
 * like the class uses internally would need to be implemented.
 **************************************************************************************************/
public class ThreadLock
{
    // #############################################################################################
    // Public fields
    // #############################################################################################

    /**
     * This is a threshold that causes acquire() to send a warning to the AWXU error handler if acquiring
     * the access takes longer than the given number of milliseconds.
     * To disable such messages, set this value to 0. Default is 1 second.
     */
    public    int           waitWarningTimeLimitInMillis                        = 1000;

    /**
     * Limit of recursions. If limit is reached or a multiple of it, an error is passed to
     * the AWXU error handler. Defaults is 10.
     */
    public    int           recursionWarningThreshold                           = 10;

    // #############################################################################################
    // Protected fields
    // #############################################################################################

    /**  Flag if recursion support is on. If not, nested locks are not counted. */
    protected boolean       recursiveMode;

    /**  Counter for the number of acquire() calls of the current thread. */
    protected int           lockCount;

    /**  The current owner of the ThreadLock. */
    protected Thread        owner;

    /**  The internal object to lock on. */
    protected Object        mutex;

    /**  The internal object to measure the time */
    protected Ticks         waitTime                                            = new Ticks();

    // #############################################################################################
    // Constructors
    // #############################################################################################

    /** ********************************************************************************************
     * Create a ThreadLock that allows recursion.
     **********************************************************************************************/
    public ThreadLock()
    {
        constructor( true, false);
    }

    /** ********************************************************************************************
     * Create a ThreadLock that allows recursion. A warning will be given (AWXU Error) when the
     * given recursion level is reached (and each multiple of it).
     *
     * @param recursiveMode Flag if recursion support is on. If not, nested locks are not counted.
     **********************************************************************************************/
    public ThreadLock( boolean recursiveMode )
    {
        constructor( recursiveMode, false);
    }

    /** ********************************************************************************************
     * Create a ThreadLock that allows recursion. A warning will be given (AWXU Error) when the
     * given recursion level is reached (and each multiple of it). In addition the lock can be
     * initialized to be unsafe, which means the locking critical sections is disabled.
     *
     * @param recursiveMode Flag if recursion support is on. If not, nested locks are not counted.
     * @param setUnsafeMode True to set this unsafe. Please don't!
     **********************************************************************************************/
    public ThreadLock( boolean recursiveMode, boolean setUnsafeMode  )
    {
        constructor( recursiveMode, setUnsafeMode);
    }

    /** ********************************************************************************************
     * Used by the Constructors to create an instance.
     *
     * @param recursiveMode Flag if recursion support is on. If not, nested locks are not counted.
     * @param setUnsafeMode True to set this unsafe. Please don't!
     **********************************************************************************************/
    @SuppressWarnings ("hiding")
    void constructor( boolean recursiveMode, boolean setUnsafeMode )
    {
        // save parameters
        this.recursiveMode=             recursiveMode;

        // set defaults
        setUnsafe( setUnsafeMode );
    }

    // #############################################################################################
    // Interface
    // #############################################################################################

    /** ********************************************************************************************
     * Thread which invokes this method gets registered  as the current owner of this object, until
     * the same thread releases the ownership invoking release(). In the case that this object is
     * already owned by another thread, the invoking thread is suspended until ownership can be
     * gained. Multiple (nested) calls to this method are counted and the object is only released
     * when the same number of release() calls have been made.
     **********************************************************************************************/
    public void acquire()
    {
        // are we in unsafe mode?
        if ( mutex == null )
        {
            // we are still increasing the lockCount
            lockCount=  recursiveMode     ? lockCount + 1
                                        : 1;

            // reached warning limit
            if ( lockCount  <= 0  )
            {
                if ( AWXU.acquireErrorHandler() )
                    AWXU.error( "ThreadLock.acquire() unsafe mode: Counter invalid (<= 0): This should never happen. Set lock to safe mode!" );
            }

            else if ( lockCount % recursionWarningThreshold == 0  && AWXU.acquireErrorHandler() )
                AWXU.warning( "ThreadLock.acquire() Warning: Recursion depth " + lockCount + ". To prevent this, change ThreadSafe.recursionWarningThreshold or fix your code." );

            // end of unsafe version of this method
            return;
        }

        // get start time
        if ( waitWarningTimeLimitInMillis > 0)
            waitTime.set();

        // get current thread
        Thread thisThread= Thread.currentThread();

        // synchronize on mutex
        synchronized ( mutex )
        {
            // we already own the thread
            if( owner == thisThread )
            {
                // we are still increasing the lockCount
                lockCount=  recursiveMode     ? lockCount + 1
                                            : 1;
                // reached warning limit
                if ( lockCount % recursionWarningThreshold == 0  && AWXU.acquireErrorHandler() )
                    AWXU.warning( "ThreadLock.acquire() Warning: Recursion depth " + lockCount + ". To prevent this, change ThreadSafe.recursionWarningThreshold or fix your code." );

                return;
            }

            // we do not own this thread, wait until lock is free


            boolean hasWarned= false;
            while( owner != null )
            {
                try
                {
                    // wait unconditional
                    if ( waitWarningTimeLimitInMillis <= 0 || hasWarned )
                        mutex.wait();

                    // wait with time limit
                    else
                    {
                        waitTime.set();
                            mutex.wait( waitWarningTimeLimitInMillis );
                        long time=   waitTime.age().inMillis();
                        if ( time >= waitWarningTimeLimitInMillis )
                        {
                            hasWarned= true;
                            if ( AWXU.acquireErrorHandler() )
                                AWXU.warning(     "ThreadLock.acquire() took " + time +  " ms, which exceeds given limit of " + waitWarningTimeLimitInMillis
                                               +" ms. Change your codes critical section length if possible. Thread ID/Name: " + thisThread.getId() + "/" + thisThread.getName() );
                        }

                    }
                }
                catch(Exception e) {} // ignore spurious wakeups
            }


            // take control
            owner=        thisThread;
            lockCount=    1;

        } // synchronized

    }

    /** ********************************************************************************************
     * Releases ownership of this object. If acquire() was called multiple times before, the same
     * number of calls to this method have to be performed to release ownership.
     **********************************************************************************************/
    public void release()
    {
        // are we in unsafe mode?
        if ( mutex == null )
        {
            // not locked
            if( recursiveMode && lockCount == 0  && AWXU.acquireErrorHandler() )
                AWXU.error( "ThreadLock.release() without having the lock (in unsafe mode). This must never happen, check your code, set lock to safe mode!" );

            // we are still decreasing the lockCount
            lockCount=  recursiveMode     ? lockCount - 1
                                        : 0;

            // end of unsafe version of this method
            return;
        }

        // synchronize on mutex
        synchronized ( mutex )
        {
            // not locked
            if( lockCount == 0 && AWXU.acquireErrorHandler() )
                AWXU.error( "ThreadLock.release() without having the lock. This must never happen, check your code!" );


            // decreasing the lockCount
            lockCount=  recursiveMode     ? lockCount - 1
                                        : 0;

            // release and notify next waiting thread
            if( lockCount == 0 )
            {
                owner= null;
                mutex.notify();
            }
        } // synchronized
    }

    /** ********************************************************************************************
     *  Identifies if the provided thread is the actual owner of this ThreadLock. If the parameter is
     *  omitted, then it is tested if the current thread owns this lock.
     *  Note: This method is provided mainly for debugging and implementing debug assertions into the code.
     *  It is *not* considered a good practice to use this method for implementing software logic.
     *  In contrast the software should be designed in a way, that it is always clear who owns a ThreadLock
     *  or at least that acquiring a thread lock can be performed instead.
     * @param thread    The thread to test current ownership of this. If null, the ownership is evaluated
     *                  for the current thread.
     * @return True if this is acquired by the given (or current) thread, false if not.
     **********************************************************************************************/
    public boolean isAcquired( Thread thread )
    {
        if ( isUnsafe() )
            return lockCount > 0 ;

        if ( owner == null )
            return false;

        return  owner == ( thread != null ? thread : Thread.currentThread() ) ;
    }



    /** ********************************************************************************************
     * If parameter is true, the whole locking system is disabled. The only objective here is to to
     * gain execution speed, as thread synchronization causes relatively expensive system calls. Use
     * this method only if you are 100% sure that your (otherwise) critical section are executed in
     * a single threaded environment. And: "relative expensive" means: they are not really
     * expensive. This only for the rare case that your critical section is very, very frequently
     * executed.
     *
     * @param setUnsafe true to set unsafe, false to set to safe mode.
     **********************************************************************************************/
    public void setUnsafe( boolean setUnsafe )
    {
        // are we in unsafe mode?
        if ( mutex == null )
        {
            // already locked? AWXU Error
            if( lockCount != 0 && AWXU.acquireErrorHandler() )
                AWXU.error(     "ThreadLock::SetUnsafe(): Cannot switch safeness mode while already locked. Current mode: unsafe, requested mode: "
                             +  ( setUnsafe ? "unsafe." : "safe." ) );

            //  switch on?
            if( ! setUnsafe )
                mutex= new Object();

            // end of unsafe version of this method
            return;
        }

        // synchronize on mutex
        synchronized ( mutex )
        {
            // already locked? AWXU Error
            if( owner != null && AWXU.acquireErrorHandler())
            {
                AWXU.error(     "ThreadLock::SetUnsafe(): Cannot switch safeness mode while already locked. Current mode: safe, requested mode: "
                             +  ( setUnsafe ? "unsafe." : "safe." )
                             +  " Owner: " + owner.getName() );
            }

            //  switch off?
            if( setUnsafe )
                mutex= null;
        }

    }

    /** ********************************************************************************************
     * Query if this instance was set to unsafe mode.
     *
     * @return  True if unsafe, false if not.
     **********************************************************************************************/
    public boolean isUnsafe()
    {
        return ( mutex == null );
    }

    /** ********************************************************************************************
     *  Returns a  String that represents this object.
     *  This method should only be used for debugging purposes as it is not determined that the values
     *  returned are consistent and not changed in the next moment. If the thread that currently acquired
     *  this ThreadLock is deleted during the execution of this method, the method might even crash
     *  (OK, not in the Java version!) while accessing the owner thread's name property. Use with care,
     *  for debug and only if you know what your are doing.
     *
     * @return  A String that represents this instance.
     **********************************************************************************************/
    @Override
    public String toString()
    {
        Thread owner= this.owner;
        return      ( owner != null ? owner.toString() : "null")
                 +  ", locks=" + lockCount
                 +  ", unsafe mode= " + ( mutex==null)
                 +  ", recursive=" +recursiveMode;
    }



}// class ThreadLock

