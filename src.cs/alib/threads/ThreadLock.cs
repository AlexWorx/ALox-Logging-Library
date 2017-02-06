// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
using System;
using System.Text;
using System.Threading;
using cs.aworx.lib.time;
using cs.aworx.lib.lang;
using System.Runtime.CompilerServices;
using cs.aworx.lib.strings;

/** ************************************************************************************************
 *  This namespace of the A-Worx Library holds classes that are providing an interface into
 *  multi threaded programming. The design of the classes tries to mimic the basic thread
 *  interface of the Java language.
 *
 *  As C# provides standardized multi-threading support, this namespace is quite empty in
 *  the C# Version of the AWorx Library.
 **************************************************************************************************/
namespace cs.aworx.lib.threads  {

/** ************************************************************************************************
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
 * code, it is quite useful to be able to control this behavior.
 *
 *  Caution: Use this class with great care. Deadlocks are not easy to detect and debug. Use
 *  this class only if standard synchronization of the Java language seems too limited and mechanisms
 *  like the class uses internally would need to be implemented.
 **************************************************************************************************/
public class ThreadLock
{
    // #############################################################################################
    // Public fields
    // #############################################################################################

    /**
     * This is a threshold that causes Acquire() to send a warning to
     * \ref cs::aworx::lib::lang::ReportWriter "ReportWriter"
     * if acquiring the access takes longer than the given number of milliseconds.
     * To disable such messages, set this value to 0. Default is 1 second.
     */
    public    int               waitWarningTimeLimitInMillis                                =1000;

    /**
     * Limit of recursions. If limit is reached or a multiple of it, an error is passed to
     * \ref cs::aworx::lib::lang::ReportWriter "ReportWriter". Defaults is 10.
     */
    public    int               RecursionWarningThreshold                                   =10;

    // #############################################################################################
    // Protected fields
    // #############################################################################################

    /**  Flag if recursion support is on. If not, nested locks are not counted.  */
    protected LockMode          lockMode;

    /**  Counter for the number of Acquire() calls of the current thread.  */
    protected int               lockCount;

    /**  The current owner of the ThreadLock.  */
    protected Thread            owner;

    /**  The internal object to lock on.  */
    protected Object            mutex;

    /**  The internal object to measure the time */
    protected Ticks             waitTime                                               =new Ticks();

    #if DEBUG
        /**  Debug information on acquirement location */
        protected int           acquirementLineNumber;

        /**  Debug information on acquirement location */
        protected String        acquirementSourcefile;

        /**  Debug information on acquirement location */
        protected String        acquirementMethodName;
    #endif



    // #############################################################################################
    // Constructors
    // #############################################################################################

    /** ********************************************************************************************
     *  Create a ThreadLock that allows recursion. A warning will be given (ALIB Error) when the
     *  given recursion level is reached (and each multiple of it). In addition the lock can be
     *  initialized to be unsafe, which means the locking critical sections is disabled.
     *
     * @param lockMode  (Optional) Flag if recursion support is on (the default).
     *                  If not, nested locks are not counted.
     * @param safeness  (Optional) Defaults to \c Safeness.Safe.
     *                  See #SetSafeness for more information.
     **********************************************************************************************/
    public ThreadLock( LockMode lockMode=  LockMode.Recursive, Safeness safeness= Safeness.Safe  )
    {
        // save parameters
        this.lockMode=    lockMode;

        // set safeness
        SetSafeness( safeness );
    }

    // #############################################################################################
    // Interface
    // #############################################################################################


    /** ********************************************************************************************
     *  Thread which invokes this method gets registered  as the current owner of this object, until the
     *  same thread releases the ownership invoking Release().
     *  In the case that this object is already owned by another thread, the invoking thread is suspended
     *  until ownership can be gained.
     *  Multiple (nested) calls to this method are counted and the object is only released when the same
     *  number of Release() calls have been made.
     *
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    virtual
    public void Acquire(
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        // are we in unsafe mode?
        if ( mutex == null )
        {
            // we are still increasing the lockCount
            lockCount=  lockMode == LockMode.Recursive ? lockCount + 1
                                                       : 1;

            // reached warning limit
            if ( lockCount <= 0 )
                ALIB_DBG.ERROR( "Unsafe mode: Counter invalid (<= 0): This should never happen. Set lock to safe mode!" );

            else if ( lockCount % RecursionWarningThreshold == 0 )
                ALIB_DBG.WARNING( "Recursion depth " + lockCount + ". To prevent this, change ThreadSafe.recursionWarningThreshold or fix your code!");

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
                lockCount=  lockMode == LockMode.Recursive ? lockCount + 1
                                                           : 1;
                // reached warning limit
                if ( lockCount % RecursionWarningThreshold == 0 )
                    ALIB_DBG.WARNING( "Recursion depth " + lockCount + ". To prevent this, change ThreadSafe.recursionWarningThreshold or fix your code!");

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
                            ALIB_DBG.WARNING(    "Timeout (" + waitWarningTimeLimitInMillis
                                              +  " ms). Change your codes critical section length if possible." + CString.NewLineChars
                                              +  "This thread: "  + thisThread.ManagedThreadId + "/" + thisThread.Name  + CString.NewLineChars
                                              +  "Owning thread: " + ( owner != null ? ( owner.ManagedThreadId + "/" + owner.Name ) : "null" )
                                    #if DEBUG
                                              + CString.NewLineChars
                                              +  "Location of acquirement: " + acquirementSourcefile + ":" + acquirementLineNumber + " " + acquirementMethodName + "()"
                                    #endif
                                        );
                        }

                    }
                }
                catch(Exception ) {} // ignore spurious wakeups
            }

            // take control
            owner=        thisThread;
            #if DEBUG
                acquirementLineNumber= cln;
                acquirementSourcefile= csf;
                acquirementMethodName= cmn;
            #endif

            lockCount=    1;

        } // synchronized
    }

    /** ********************************************************************************************
     *  Releases ownership of this object. If Acquire() was called multiple times before, the same
     *  number of calls to this method have to be performed to release ownership.
     **********************************************************************************************/
    virtual
    public void Release()
    {
        // are we in unsafe mode?
        if ( mutex == null )
        {
            // not locked
            if( lockMode == LockMode.Recursive && lockCount == 0 )
                 ALIB_DBG.ERROR( "Release() without Acquire() (unsafe mode). This must never happen, check your code, set lock to safe mode!" );

            // we are still decreasing the lockCount
            lockCount=  lockMode == LockMode.Recursive  ? lockCount - 1
                                                        : 0;
            // end of unsafe version of this method
            return;
        }

        // synchronize on mutex
        lock ( mutex )
        {
            // not locked
            if( lockCount == 0 )
                ALIB_DBG.ERROR( "Release() without Acquire(). This must never happen, check your code!" );

            // decreasing the lockCount
            lockCount=  lockMode == LockMode.Recursive ? lockCount - 1
                                                       : 0;

            // release and notify next waiting thread
            if( lockCount == 0 )
            {
                owner= null;
                Monitor.Pulse( mutex );

                #if DEBUG
                    acquirementLineNumber= -1;
                    acquirementSourcefile= null;
                    acquirementMethodName= null;
                #endif
            }
        } // synchronized
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
    public int DbgCountAcquirements( Thread thread= null )
    {
        if ( GetSafeness() == Safeness.Unsafe )
            return lockCount;

        if ( owner == null )
            return 0;

        return  (owner == ( thread != null ? thread : Thread.CurrentThread ))
                ?  lockCount
                : -lockCount;
    }


    /** ********************************************************************************************
     *  If parameter is true, the whole locking system is disabled. The only objective here is to
     *  to gain execution speed, as thread synchronization causes relatively expensive system calls.
     *  Use this method only if you are 100% sure that your (otherwise) critical section are executed
     *  in a single threaded environment. And: "relative expensive" means: they are not really
     *  expensive. This is provided only for the rare case that your critical section is very,
     *  very frequently executed.
     *
     * @param safeness  Determines if this object should use a mutex (\c Safeness.Safe)
     *                  or just do nothing (\c Safeness.Unsafe).
     *************************************************************************************************/
    public void SetSafeness( Safeness safeness )
    {
        // are we in unsafe mode?
        if ( mutex == null )
        {
            // already locked? ALIB Error
            if( lockCount != 0 )
            {
                ALIB_DBG.ERROR( "Cannot switch safeness mode while already locked. Current mode: unsafe, requested mode: "
                                +  safeness.ToString() );
                return;
            }

            //  switch on?
            if( safeness == Safeness.Safe )
                mutex= new Object();

            // end of unsafe version of this method
            return;
        }

        // synchronize on mutex
        lock ( mutex )
        {
            // already locked? ALIB Error
            if( owner != null  )
            {
                ALIB_DBG.ERROR( "Cannot switch safeness mode while already locked. Current mode: safe, requested mode: "
                                + safeness.ToString() );
                return;
            }

            //  switch off?
            if( safeness == Safeness.Unsafe )
                mutex= null;
        }
    }

    /** ********************************************************************************************
     * Query if this instance was set to unsafe mode.
     * @return A value of type cs::aworx::lib::lang::Safeness "Safeness"
     **********************************************************************************************/
    public Safeness GetSafeness()
    {
        return ( mutex == null ) ? Safeness.Unsafe : Safeness.Safe;
    }

    /** ****************************************************************************************
     *  Query if this instance was set to work recursively.
     * @return A value of type cs::aworx::lib::lang::LockMode "LockMode"
     ******************************************************************************************/
    public LockMode GetMode()
    {
        return lockMode;
    }

    /** ****************************************************************************************
     * This is for debugging purposes. E.g. this enables the \e Monodevelop IDE to display
     * object descriptions in the debugger.
     * @returns A human readable string representation of this object.
     ******************************************************************************************/
    public override String ToString()
    {
        String result= "";
             if ( lockCount == 0 )  result+= "Unlocked";
        else if ( lockCount == 1 )  result+= "Locked";
        else if ( lockCount >  1 )  result+= "Locked (" + lockCount + ")";
        else if ( lockCount <  0 )  result+= "Illegal State. lockCount=" + lockCount;

             if ( lockMode == LockMode.SingleLocks )
                                    result+= " (Non-Recursive)";

             if ( mutex == null  )  result+= " (Unsafe Mode)";
        else if ( lockCount >  0 )  result+= ", Owner: (" + owner.ManagedThreadId + ") \"" + owner.Name + "\"";

        return result;
    }



}// class ThreadLock


} // namespace / EOF
