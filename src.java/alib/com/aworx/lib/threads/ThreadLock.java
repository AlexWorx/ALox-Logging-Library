// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################


/**
 *  This namespace of the A-Worx Library holds classes that are providing an interface into
 *  multi threaded programming. The design of the AWorx Library classes implementation of
 *  languages other than Java, try to mimic the  basic thread interface of the Java language.
 *  Therefore this namespace is quite empty in the Java Version of the AWorx Library.
 */
package com.aworx.lib.threads;

import com.aworx.lib.lang.LockMode;
import com.aworx.lib.lang.Safeness;
import com.aworx.lib.strings.CString;
import com.aworx.lib.time.Ticks;

/** ************************************************************************************************
 * This class allows *mutual exclusive access* to resources shared by different threads.
 * In other words, access to certain data that is accessed by different threads, can
 * be protected if each thread (aka critical section code) uses the same ThreadLock to control the
 * access to such data.
 *
 * If an acquire() is not followed by a corresponding release(), other threads will not be able to
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
 *
 * \note For information on debugging deadlocks with this class, see field #createOwnerStackTrace.
 **************************************************************************************************/
public class ThreadLock
{
    // #############################################################################################
    // Public fields
    // #############################################################################################

    /**
     * This is a threshold that causes acquire() to send a warning to
     * \ref com.aworx.lib.lang.ReportWriter "ReportWriter" if acquiring
     * the access takes longer than the given number of milliseconds.
     * To disable such messages, set this value to 0. Default is 1 second.
     */
    public    int           waitWarningTimeLimitInMillis                        = 1000;

    /**
     * Limit of recursions. If limit is reached or a multiple of it, an error message is passed to
     * \ref com.aworx.lib.lang.ReportWriter "ReportWriter". Defaults is 10.
     */
    public    int           recursionWarningThreshold                           = 10;

    /**  If set to true, whenever acquired, the stack trace of the acquirement is stored.
     *   Can be set to \c true for debugging deadlocks. Stack trace will be reported when
     *   #waitWarningTimeLimitInMillis is exceeded. */
    protected boolean       createOwnerStackTrace                                           = false;

    // #############################################################################################
    // Protected fields
    // #############################################################################################

    /**  Flag if recursion support is on. If not, nested locks are not counted. */
    protected LockMode      lockMode;

    /**  Counter for the number of acquire() calls of the current thread. */
    protected int           cntAcquirements;

    /**  The current owner of the ThreadLock. */
    protected Thread        owner;

    /**  Used for dumping stack trace of location of owner. For performance reasons, created
     *   only if public field #createOwnerStackTrace was set to \c true. */
    protected Exception     ownerException;

    /**  The internal object to lock on. */
    protected Object        mutex;

    /**  The internal object to measure the time */
    protected Ticks         waitTime                                                  = new Ticks();

    // #############################################################################################
    // Constructors
    // #############################################################################################

    /** ********************************************************************************************
     * Create a ThreadLock that allows recursion.
     **********************************************************************************************/
    public ThreadLock()
    {
        constructor( LockMode.RECURSIVE, Safeness.SAFE);
    }

    /** ********************************************************************************************
     * Create a ThreadLock that allows recursion. A warning will be given (ALIB Error) when the
     * given recursion level is reached (and each multiple of it).
     *
     * @param lockMode  (Optional) Flag if recursion support is on (the default).
     *                  If not, nested locks are not counted.
     **********************************************************************************************/
    public ThreadLock( LockMode lockMode )
    {
        constructor( lockMode, Safeness.SAFE);
    }

    /** ********************************************************************************************
     * Create a ThreadLock that allows recursion. A warning will be given (ALIB Error) when the
     * given recursion level is reached (and each multiple of it). In addition the lock can be
     * initialized to be unsafe, which means the locking critical sections is disabled.
     *
     * @param lockMode  (Optional) Flag if recursion support is on (the default).
     *                  If not, nested locks are not counted.
     * @param safeness  (Optional) Defaults to \c Safeness.Safe.
     *                  See #setSafeness for more information.
     **********************************************************************************************/
    public ThreadLock( LockMode lockMode, Safeness safeness  )
    {
        constructor( lockMode, safeness);
    }

    /** ********************************************************************************************
     * Used by the Constructors to create an instance.
     *
     * @param lockMode  (Optional) Flag if recursion support is on (the default).
     *                  If not, nested locks are not counted.
     * @param safeness  See #setSafeness for more information.
     **********************************************************************************************/
    @SuppressWarnings ("hiding")
    void constructor( LockMode lockMode, Safeness safeness  )
    {
        // save parameters
        this.lockMode=   lockMode;

        // set defaults
        setSafeness( safeness );
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
            // we are still increasing the cntAcquirements
            cntAcquirements=  lockMode == LockMode.RECURSIVE ? cntAcquirements + 1
                                                       : 1;

            // reached warning limit
            if ( cntAcquirements  <= 0  )
            {
                com.aworx.lib.ALIB_DBG.ERROR( "Unsafe mode: Counter invalid (<= 0): This should never happen. Set lock to safe mode!" );
            }

            else if ( cntAcquirements % recursionWarningThreshold == 0 )
                com.aworx.lib.ALIB_DBG.WARNING( "Recursion depth " + cntAcquirements + ". To prevent this, change ThreadSafe.recursionWarningThreshold or fix your code." );

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
                // we are still increasing the cntAcquirements
                cntAcquirements=  lockMode  == LockMode.RECURSIVE  ? cntAcquirements + 1
                                                             : 1;
                // reached warning limit
                if ( cntAcquirements % recursionWarningThreshold == 0 )
                    com.aworx.lib.ALIB_DBG.WARNING( "Recursion depth " + cntAcquirements + ". To prevent this, change ThreadSafe.recursionWarningThreshold or fix your code." );

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
                            com.aworx.lib.ALIB_DBG.WARNING(   "Timeout (" + waitWarningTimeLimitInMillis
                                               +" ms). Change your codes critical section length if possible."
                                               +" This thread: " + thisThread.getId() + "/" + thisThread.getName()
                                               +", owner: " + (owner == null ? "null" : owner.getId() + "/" + owner.getName() )
                                               +". Stack trace follows!" );

                            {
                                StackTraceElement[] stack= (new Exception()).getStackTrace();
                                String stackStr="";
                                for ( int i= 0 ; i < stack.length ; ++i )
                                {
                                    stackStr= stackStr + "  ("+ stack[i].getFileName()   + ":"
                                                              + stack[i].getLineNumber() + ") "
                                                              + stack[i].getClassName()  + "."
                                                              + stack[i].getMethodName() + "()"
                                                              + CString.NEW_LINE_CHARS;
                                }
                                com.aworx.lib.ALIB_DBG.WARNING(   stackStr );
                            }

                            if( ownerException != null )
                            {
                                StackTraceElement[] stack= ownerException.getStackTrace();
                                String stackStr="";
                                for ( int i= 0 ; i < stack.length ; ++i )
                                {
                                    stackStr= stackStr + "  ("+ stack[i].getFileName()   + ":"
                                                              + stack[i].getLineNumber() + ") "
                                                              + stack[i].getClassName()  + "."
                                                              + stack[i].getMethodName() + "()"
                                                              + CString.NEW_LINE_CHARS;
                                }
                                com.aworx.lib.ALIB_DBG.WARNING(   stackStr );

                            }
                            else
                            {
                                com.aworx.lib.ALIB_DBG.WARNING(  "No stacktrace of acquirement available. To enable stack traces, "
                                             + "set field createOwnerStackTrace temporarily to true!" );
                            }

                        }

                    }
                }
                catch(@SuppressWarnings ("unused") Exception e) {/* void */} // ignore spurious wakeups
            }


            // take control
            owner=        thisThread;
            if ( createOwnerStackTrace )
                ownerException= new Exception();

            cntAcquirements=    1;

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
            if( lockMode == LockMode.RECURSIVE && cntAcquirements == 0 )
                com.aworx.lib.ALIB_DBG.ERROR( "Release without having the lock (in unsafe mode). This must never happen, check your code, set lock to safe mode!" );

            // we are still decreasing the cntAcquirements
            cntAcquirements=  lockMode  == LockMode.RECURSIVE  ? cntAcquirements - 1
                                                         : 0;
            // end of unsafe version of this method
            return;
        }

        // synchronize on mutex
        synchronized ( mutex )
        {
            // not locked
            if( cntAcquirements == 0 )
                com.aworx.lib.ALIB_DBG.ERROR( "Release without having the lock. This must never happen, check your code!" );


            // decreasing the cntAcquirements
            cntAcquirements=  lockMode  == LockMode.RECURSIVE  ? cntAcquirements - 1
                                                         : 0;

            // release and notify next waiting thread
            if( cntAcquirements == 0 )
            {
                owner= null;
                ownerException= null;
                mutex.notify();
            }
        } // synchronized
    }


    /** ****************************************************************************************
     * Returns \c true if the next invocation of #release will release the lock.
     * Returns \c false, if recursive acquirements have been performed.
     *
     * @return \c true if locked exactly once.
     ******************************************************************************************/
    public boolean willRelease()
    {
        return cntAcquirements == 1;
    }

    /** ********************************************************************************************
     * Returns the number of acquirements of this ThreadLock. The negative number (still
     * providing the number of acquirements) is returned if the owning thread is not the same
     * as the given one.
     *
     * \note This method is provided mainly for debugging and implementing debug assertions
     *       into the code. It is *not* considered a good practice to use this method for
     *       implementing  software logic.
     *       In contrast the software should be designed in a way, that it is always
     *       clear who owns a ThreadLock or at least that acquiring a thread lock can be
     *       performed instead.
     *
     * @param thread The thread to test current ownership of this.
     *               Defaults to the current (invoking) thread.
     * @return The number of (recursive) acquirements, negative if acquired by a different
     *         thread than provided.
     **********************************************************************************************/
    public int dbgCountAcquirements( Thread thread )
    {
        if ( getSafeness() == Safeness.UNSAFE )
            return cntAcquirements;

        if ( owner == null )
            return 0;

        return  ( owner == ( thread != null ? thread : Thread.currentThread() ) )
                ?  cntAcquirements
                : -cntAcquirements;
    }

    /** ********************************************************************************************
     *  If parameter is true, the whole locking system is disabled. The only objective here is to
     *  to gain execution speed, as thread synchronization causes relatively expensive system calls.
     *  Use this method only if you are 100% sure that your (otherwise) critical section are
     *  executed in a single threaded environment. And: "relative expensive" means: they are not
     *  really expensive. This is provided only for the rare case that your critical section is
     *  very, very frequently executed.
     *
     * @param safeness  Determines if this object should use a mutex (\c Safeness.Safe)
     *                  or just do nothing (\c Safeness.Unsafe).
     **********************************************************************************************/
    public void setSafeness( Safeness safeness )
    {
        // are we in unsafe mode?
        if ( mutex == null )
        {
            // already locked? ALIB Error
            if( cntAcquirements != 0 )
            {
                com.aworx.lib.ALIB_DBG.ERROR( "Cannot switch safeness mode while already locked. Current mode: unsafe, requested mode: "
                             +  safeness.toString() );
                return;
            }

            //  switch on?
            if( safeness == Safeness.SAFE )
                mutex= new Object();

            // end of unsafe version of this method
            return;
        }

        // synchronize on mutex
        synchronized ( mutex )
        {
            // already locked? ALIB Error
            if( owner != null )
            {
                com.aworx.lib.ALIB_DBG.ERROR(   "Cannot switch safeness mode while already locked. Current mode: safe, requested mode: "
                            + safeness.toString()
                            + " Owner: " + owner.getName() );
                return;
            }

            //  switch off?
            if( safeness == Safeness.UNSAFE )
                mutex= null;
        }
    }

    /** ********************************************************************************************
     * Query if this instance was set to unsafe mode.
     *
     * @return A value of type com.aworx.lib.lang.Safeness "Safeness"
     **********************************************************************************************/
    public Safeness getSafeness()
    {
        return mutex == null ? Safeness.UNSAFE : Safeness.SAFE;
    }

    /** ****************************************************************************************
     *  Query if this instance was set to work recursively.
     * @return A value of type com.aworx.lib.lang.LockMode "LockMode"
     ******************************************************************************************/
    public LockMode getMode()
    {
        return lockMode;
    }

    /** ****************************************************************************************
     * This is for debugging purposes. E.g. this enables the \e Eclipse IDE to display
     * object descriptions in the debugger.
     * @returns A human readable string representation of this object.
     ******************************************************************************************/
    @Override
    public String toString()
    {
        String result= "";
             if ( cntAcquirements == 0 )  result+= "Unlocked";
        else if ( cntAcquirements == 1 )  result+= "Locked";
        else if ( cntAcquirements >  1 )  result+= "Locked (" + cntAcquirements + ")";
        else if ( cntAcquirements <  0 )  result+= "Illegal State. cntAcquirements=" + cntAcquirements;

             if ( lockMode == LockMode.SINGLE_LOCKS )
                                    result+= " (Non-Recursive)";

             if ( mutex  == null )  result+= " (Unsafe Mode)";
        else if ( cntAcquirements >  0 )  result+= ", Owner: (" + owner.getId() + ") \"" + owner.getName() + "\"";

        return result;
    }



}// class ThreadLock

