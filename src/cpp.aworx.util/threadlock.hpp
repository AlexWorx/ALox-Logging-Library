// #################################################################################################
//  aworx::util - Classes we need
//
//  (c) 2013-2015 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################

// include AWXU main header first...
#if !defined (HPP_AWORX_UTIL_AWXU)
    #include "awxu.hpp"
#endif

// then, set include guard
#ifndef HPP_AWORX_UTIL_THREADLOCK
#define HPP_AWORX_UTIL_THREADLOCK 1


// -------------------------------------------------------------------------------------------------
// --- includes
// -------------------------------------------------------------------------------------------------
#if !defined (HPP_AWORX_UTIL_THREAD)
    #include "thread.hpp"
#endif

#if !defined (HPP_AWORX_UTIL_OWNABLE)
    #include "ownable.hpp"
#endif

namespace aworx {
namespace       util {


// #################################################################################################
// class ThreadLockNR
// #################################################################################################

/** ************************************************************************************************
 *  This class is a simple wrapper around std::mutex (provided solely to reach compatibility of AWXU
 *  across programming languages) and hence allows *mutual exclusive access* to resources, by
 *  protecting data from concurrent access by different threads.
 *
 *  Unlike class ThreadLock, this class ThreadLockNR does not use an internal counter to allow
 *  recursive calls to Acquire() and Release(). Also, no owner is recorded, no AWXU error handler
 *  is invoked on misuse and no time limit warnings are supported.
 *  Consider using ThreadLock in most cases. The advantage of ThreadLockNR is that it operates
 *  several times faster than ThreadLock. So, for very time critical sections with frequent
 *  Lock.Release()use of ThreadLockNR can be taken into consideration.
 **************************************************************************************************/
class ThreadLockNR : public Ownable
{
    #ifdef AWXU_FEAT_THREADS

    // #############################################################################################
    // Protected fields
    // #############################################################################################
    protected:
        /**  The internal object to lock on.  */
        std::mutex*                    mutex                                              = nullptr;

    // #############################################################################################
    // constructor/destructor
    // #############################################################################################
    public:
        /** ****************************************************************************************
         *  Create a ThreadLockNR that does not allow recursion. Consider using class ThreadLock
         *  instead of this.
         * @param setUnsafeMode    (Optional) True to set this unsafe. Please don't!
         ******************************************************************************************/
        explicit
        ThreadLockNR( bool setUnsafeMode= false  )
        {
            mutex= setUnsafeMode ? nullptr
                                 : new std::mutex();
        }

        /** ****************************************************************************************
         *   Destructor.    *
         ******************************************************************************************/
        ~ThreadLockNR()                                { if( mutex != nullptr )     delete mutex;  }


    // #############################################################################################
    // Interface
    // #############################################################################################
    public:

        /** ****************************************************************************************
         * Thread which invokes this method gets registered  as the current owner of this object,
         * until the same thread releases the ownership invoking #Release.
         * In the case that this object is already owned by another thread, the invoking thread is
         * suspended until ownership can be gained.
         * Multiple (nested) calls to this method are not supported and lead to undefined behavior.
         ******************************************************************************************/
        virtual    void Acquire()                      { if ( mutex != nullptr ) mutex->lock();    }

        /** ****************************************************************************************
         * Releases ownership of this object. If #Acquire was called multiple times before, the same
         * number of calls to this method have to be performed to release ownership.
         ******************************************************************************************/
        virtual void Release()                         { if ( mutex != nullptr ) mutex->unlock();  }

        /** ****************************************************************************************
         *  If parameter is true, the whole locking system is disabled. The only objective here is
         *  to gain execution speed, as thread synchronization causes relatively expensive system
         *  calls. Use this method only if you are 100% sure that your (otherwise) critical section
         *  are executed in a single threaded environment. And: "relative expensive" means:
         *  they are not really expensive. This is only for the rare case that your critical
         *  section is very, very frequently executed.
         * @param setUnsafe    If true, ThreadLock is set unsafe, safe otherwise.
         ******************************************************************************************/
        void SetUnsafe( bool setUnsafe )
        {
            if( setUnsafe && mutex != nullptr )
            {
                delete mutex;
                mutex= nullptr;
            }
            else if( !setUnsafe && mutex == nullptr )
                mutex= new std::mutex();
        }

        /** ****************************************************************************************
         *     Query if this instance was set to unsafe mode.
         * @return    True if unsafe, false if not.
         ******************************************************************************************/
        bool IsUnsafe()                                { return ( mutex == nullptr );              }

    #else
    // #############################################################################################
    // Unsafe version of this class
    // #############################################################################################
    public:
        explicit
                    ThreadLockNR( bool= false ) {}
                   ~ThreadLockNR()              {}
        virtual void Acquire()                  {}
        virtual void Release()                  {}
                void SetUnsafe( bool )          {}
                bool IsUnsafe()                 { return true; }
    #endif
}; // class ThreadLockNR


// #################################################################################################
// class ThreadLock
// #################################################################################################

/** ************************************************************************************************
 *  This class allows *mutual exclusive access* to resources shared by different threads.
 *  In other words, access to certain data that is accessed by different threads, can
 *  be protected if each thread (aka critical section code) uses the same ThreadLock to control the
 *  access to such data.
 *
 *  If a Acquire is not followed by a corresponding Release(), other threads will not be able to
 *  gain control to this object and will wait endlessly (deadlock situation).
 *  When the Acquire and Release invocations happen within the same code block, then it is
 *  highly recommended to use a stack instantiation of class AWXU::Owner to acquire and release
 *  objects of this class.
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
 *  this class only if standard synchronization of the Java language seems too limited and
 *  mechanisms like the class uses internally would need to be implemented.
 *
 **************************************************************************************************/
class ThreadLock : public Ownable
{
    #ifdef AWXU_FEAT_THREADS

    // #############################################################################################
    // Public fields
    // #############################################################################################
    public:
        /**
         * This is a threshold that causes Acquire() to send a warning to the AWXU error handler if
         * acquiring the access takes longer than the given number of milliseconds.
         * To disable such messages, set this value to 0. Default is 1 second.
         *  */
        long                        WaitWarningTimeLimitInMillis                           =1000L;

        /**
         * Limit of recursions. If limit is reached or a multiple of it, an error is is passed to
         * the AWXU error handler. Defaults is 10.
         *  */
        int                         RecursionWarningThreshold                              =10;

    // #############################################################################################
    // Protected fields
    // #############################################################################################
    protected:
        /**  Flag if recursion support is on. If not, nested locks are not counted.  */
        bool                        recursiveMode;

        /**  Counter for the number of Acquire() calls of the current thread.  */
        int                         lockCount                                               =0;

        /**  Thread ID of the current owner.  */
        Thread*                     owner                                                  =nullptr;

        /**  The internal object to lock on.  */
        std::mutex*                 mutex                                                  =nullptr;

        /**  The internal object to lock on.  */
        std::condition_variable*    mutexNotifier                                          =nullptr;


    // #############################################################################################
    // Constructors
    // #############################################################################################
    public:

        /** ****************************************************************************************
         *  Create a ThreadLock that allows recursion. A warning will be given (AWXU Error) when the
         *  given recursion level is reached (and each multiple of it). In addition the lock can be
         *  initialized to be unsafe, which means the locking critical sections is disabled.
         *
         * @param recursiveMode    (Optional) Flag if recursion support is on. If not, nested locks
         *                                 are not counted.
         * @param setUnsafeMode    (Optional) True to set this unsafe. Please don't!
         ******************************************************************************************/
        explicit AWXU_API          ThreadLock( bool recursiveMode= true, bool setUnsafeMode= false);

        /** ****************************************************************************************
         *  Destructor.
         ******************************************************************************************/
        AWXU_API                  ~ThreadLock();

    // #############################################################################################
    // Interface
    // #############################################################################################
    public:

        /** ****************************************************************************************
         * Thread which invokes this method gets registered  as the current owner of this object,
         * until the same thread releases the ownership invoking #Release.
         * In the case that this object is already owned by another thread, the invoking thread is
         * suspended until ownership can be gained.
         * Multiple (nested) calls to this method are counted and the object is only released when
         * the same number of Release() calls have been made.
         ******************************************************************************************/
        AWXU_API  virtual void        Acquire();

        /** ****************************************************************************************
         * Releases ownership of this object. If #Acquire was called multiple times before, the same
         * number of calls to this method have to be performed to release ownership.
         ******************************************************************************************/
        AWXU_API  virtual void        Release();

        /** ****************************************************************************************
         *  Identifies if the provided thread is the actual owner of this ThreadLock. If the
         *  parameter is omitted, then it is tested if the current thread owns this lock.
         *  Note: This method is provided mainly for debugging and implementing debug assertions
         *  into the code. It is *not* considered a good practice to use this method for
         *  implementing software logic. In contrast the software should be designed in a way, that
         *  it is always clear who owns a ThreadLock or at least that acquiring a thread lock
         *  can be performed instead.
         *
         * @param thread The thread to test current ownership of this. If omitted the ownership is
         *                          identified for the current thread.
         * @return True if this is acquired by the given (or current) thread, false if not.
         ******************************************************************************************/
        AWXU_API  bool                IsAcquired( Thread* thread= nullptr );


        /** ****************************************************************************************
         *  If parameter is true, the whole locking system is disabled. The only objective here is
         *  to gain execution speed, as thread synchronization causes relatively expensive system
         *  calls. Use this method only if you are 100% sure that your (otherwise) critical section
         *  are executed in a single threaded environment. And: "relative expensive" means: they
         *  are not really expensive. This only for the rare case that your critical section is
         *  very, very frequently executed.
         *
         * @param setUnsafe    If true, ThreadLock is set unsafe, safe otherwise.
         ******************************************************************************************/
        AWXU_API  void                SetUnsafe( bool setUnsafe );

        /** ****************************************************************************************
         *  Query if this instance was set to unsafe mode.
         * @return    True if unsafe, false if not.
         ******************************************************************************************/
                  bool                IsUnsafe()                    { return ( mutex == nullptr ); }

    #else
    // #############################################################################################
    // Unsafe version of this class
    // #############################################################################################
    protected:
        int                         cntLck                                                 =0;
        bool                        recursiveMode                                          =0;
    public:
        long                        WaitWarningTimeLimitInMillis                           =1000L;
        int                         RecursionWarningThreshold                              =10;
        explicit
                     ThreadLock( bool recMode= true, bool= false ) { recursiveMode= recMode; }
                    ~ThreadLock()                          {}
        virtual void Acquire()                             { if( recursiveMode || cntLck == 0 ) cntLck++; }
        virtual void Release()                             { if( cntLck > 0 ) cntLck--; }
                bool IsAcquired( Thread* = nullptr )       { return cntLck > 0; }
                void SetUnsafe( bool mode )                { if( !mode ) cntLck= 0; }
                bool IsUnsafe()                            { return true; }
    #endif
}; // class ThreadLock


}}  // namespace aworx::util

#endif // HPP_AWORX_UTIL_THREADLOCK
