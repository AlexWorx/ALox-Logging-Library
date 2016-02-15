// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
/** @file */ // Hello Doxygen

// check for alib.hpp already there but not us
#if !defined (HPP_ALIB_ALIB)
    #error "include \"alib/alib.hpp\" before including this header"
#endif
#if defined(HPP_COM_ALIB_TEST_INCLUDES) && defined(HPP_ALIB_THREADS_THREADLOCK)
    #error "Header already included"
#endif

// Due to our blocker above, this include will never be executed. But having it, allows IDEs
// (e.g. QTCreator) to read the symbols when opening this file
#if !defined (HPP_ALIB_ALIB)
    #include "alib/alib.hpp"
#endif

// then, set include guard
#ifndef HPP_ALIB_THREADS_THREADLOCK
#if !defined( IS_DOXYGEN_PARSER)
#define HPP_ALIB_THREADS_THREADLOCK 1
#endif

// #################################################################################################
// includes
// #################################################################################################
#include "alib/core/ownable.hpp"
#include "thread.hpp"

namespace aworx {
namespace           lib {
namespace                   threads {

/** ************************************************************************************************
 * This class is a simple wrapper around std::mutex (provided solely to reach compatibility of ALIB
 * across programming languages) and hence allows *mutual exclusive access* to resources, by
 * protecting data from concurrent access by different threads.
 *
 * Unlike class ThreadLock, this class ThreadLockNR does not use an internal counter to allow
 * recursive calls to Acquire() and Release(). Also, no owner is recorded, no ALIB
 * \ref aworx::lib::ReportWriter "ReportWriter"
 * is invoked on misuse and no time limit warnings are supported.
 * Consider using ThreadLock in most cases. The advantage of ThreadLockNR is that it operates
 * several times faster than ThreadLock. So, for very time critical sections with frequent
 * Lock.Release()use of ThreadLockNR can be taken into consideration.
 *
 * \attention Nested (recursive) acquisitions are not supported and lead to undefined behavior.
 **************************************************************************************************/
class ThreadLockNR : public Ownable
{
    // #############################################################################################
    // Protected fields
    // #############################################################################################
    protected:
        /**  The internal object to lock on.  */
        #if defined(ALIB_FEAT_THREADS)
            std::mutex*                mutex                                              = nullptr;
        #else
            void*                      mutex                                              = nullptr;
        #endif

        /**  Counter of (forbidden!) recursive acquirements. Available only in debug compilations. */
        #if defined(ALIB_DEBUG)
            bool     dbgIsAcquired= false;
        #endif

    // #############################################################################################
    // constructor/destructor
    // #############################################################################################
    public:
        /** ****************************************************************************************
         *  Create a ThreadLockNR that does not allow recursion. Consider using class ThreadLock
         *  instead of this.
         * @param safeness  (Optional) Can be used to set this unsafe mode. See \#SetMode
         *                  for more information.
         *
         ******************************************************************************************/
        explicit
        ThreadLockNR( enums::Safeness safeness= enums::Safeness::Safe )
        {
            mutex= safeness == enums::Safeness::Unsafe ? nullptr
                                                   #if defined(ALIB_FEAT_THREADS)
                                                       : new std::mutex();
                                                   #else
                                                       : ((void*) 1);
                                                   #endif
        }

        /** ****************************************************************************************
         *   Destructor.    *
         ******************************************************************************************/
        virtual ~ThreadLockNR()
        {
            #if defined(ALIB_FEAT_THREADS)
                if( mutex != nullptr )
                    delete mutex;
            #endif
        }

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
        virtual void Acquire()
        {
            ALIB_ASSERT_ERROR( !dbgIsAcquired,
                    "Must not recursively acquired. Use class ThreadLock if recursion is needed" );

            #if defined(ALIB_FEAT_THREADS)
                if ( mutex != nullptr )
                    mutex->lock();
            #endif

            ALIB_DEBUG_CODE( dbgIsAcquired= true; )
        }

        /** ****************************************************************************************
         * Releases ownership of this object. If #Acquire was called multiple times before, the same
         * number of calls to this method have to be performed to release ownership.
         ******************************************************************************************/
        virtual void Release()
        {
            ALIB_ASSERT_ERROR( dbgIsAcquired,      "Release without prior acquisition" );
            #if defined(ALIB_FEAT_THREADS)
                if ( mutex != nullptr )
                        mutex->unlock();
            #endif
            ALIB_DEBUG_CODE( dbgIsAcquired= false; )
        }

        /** ****************************************************************************************
         *  If parameter is \c true, the whole locking system is disabled. The only objective here is
         *  to gain execution speed, as thread synchronization causes relatively expensive system
         *  calls. Use this method only if you are 100% sure that your (otherwise) critical section
         *  are executed in a single threaded environment. And: "relative expensive" means:
         *  they are not really expensive. This is only for the rare case that your critical
         *  section is very, very frequently executed.
         * @param safeness   Denotes the safeness mode.
         ******************************************************************************************/
        void SetMode( enums::Safeness safeness )
        {
            #if defined(ALIB_FEAT_THREADS)
                if( safeness == enums::Safeness::Unsafe && mutex != nullptr )
                {
                    delete mutex;
                    mutex= nullptr;
                    return;
                }

                if( safeness == enums::Safeness::Safe && mutex == nullptr )
                {
                    mutex= new std::mutex();
                    return;
                }
            #else
                mutex= safeness == enums::Safeness::Safe ? ((void*) 1) : nullptr;
            #endif
        }

        /** ****************************************************************************************
         *     Query if this instance was set to unsafe mode.
         * @return    \c true if unsaf\c falselse if not.
         ******************************************************************************************/
        enums::Safeness Mode()                     { return  mutex == nullptr ? enums::Safeness::Unsafe
                                                                              : enums::Safeness::Safe;       }
}; // class ThreadLockNR


/** ************************************************************************************************
 *  This class allows *mutual exclusive access* to resources shared by different threads.
 *  In other words, access to certain data that is accessed by different threads, can
 *  be protected if each thread (aka critical section code) uses the same ThreadLock to control the
 *  access to such data.
 *
 *  If an Acquire is not followed by a corresponding Release(), other threads will not be able to
 *  gain control to this object and will wait endlessly (deadlock situation).
 *  When the Acquire and Release invocations happen within the same code block, then it is
 *  highly recommended to use a stack instantiation of class ALIB::Owner to acquire and release
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
 **************************************************************************************************/
class ThreadLock : public Ownable
{
    // #############################################################################################
    // Public fields
    // #############################################################################################
    public:
        /**
         * This is a threshold that causes Acquire() to send a warning to
         * \ref aworx::lib::ReportWriter "ReportWriter" if
         * acquiring the access takes longer than the given number of milliseconds.
         * To disable such messages, set this value to 0. Default is 1 second.
         */
        long                          WaitWarningTimeLimitInMillis                           =1000L;

        /**
         * Limit of recursions. If limit is reached or a multiple of it, an error is is passed to
         * \ref aworx::lib::ReportWriter "ReportWriter". Defaults is 10.
         */
        int                           RecursionWarningThreshold                                 =10;

    // #############################################################################################
    // Protected fields
    // #############################################################################################
    protected:
        /**  Flag if recursion support is on. If not, nested locks are not counted.  */
        enums::LockMode               lockMode;

        /**  Counter for the number of Acquire() calls of the current thread.  */
        int                           cntAcquirements                                            =0;


        /**  Thread ID of the current owner.  */
        Thread*                       owner                                                =nullptr;

        #if defined(ALIB_FEAT_THREADS)

            /**  The internal object to lock on.  */
            std::mutex*               mutex                                                =nullptr;

            /**  The internal object to lock on.  */
            std::condition_variable*  mutexNotifier                                        =nullptr;
        #else
            void*                     mutex                                                =nullptr;
        #endif

    // #############################################################################################
    // Constructors
    // #############################################################################################
    public:

        /** ****************************************************************************************
         *  Create a ThreadLock that allows recursion. A warning will be given (ALIB Error) when the
         *  given recursion level is reached (and each multiple of it). In addition the lock can be
         *  initialized to be unsafe, which means the locking critical sections is disabled.
         *
         * @param lockMode  (Optional) Flag if recursion support is on (the default).
         *                  If not, nested locks are not counted.
         * @param safeness  (Optional) Defaults to \c Safeness::Safe.
         *                  See #SetMode for more information.
         ******************************************************************************************/
        ALIB_API
        explicit          ThreadLock(  enums::LockMode lockMode=  enums::LockMode::Recursive,
                                       enums::Safeness safeness=  enums::Safeness::Safe);

        /** ****************************************************************************************
         *  Destructor.
         ******************************************************************************************/
        ALIB_API
        virtual          ~ThreadLock();

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
        ALIB_API  virtual void    Acquire();

        /** ****************************************************************************************
         * Releases ownership of this object. If #Acquire was called multiple times before, the same
         * number of calls to this method have to be performed to release ownership.
         ******************************************************************************************/
        ALIB_API  virtual void    Release();

        /** ****************************************************************************************
         *  Identifies if the provided thread is the actual owner of this ThreadLock. If the
         *  parameter is omitted, then it is tested if the current thread owns this lock.
         *  \note This method is provided mainly for debugging and implementing debug assertions
         *        into the code. It is *not* considered a good practice to use this method for
         *        implementing  software logic.
         *        In contrast the software should be designed in a way, that it is always
         *        clear who owns a ThreadLock or at least that acquiring a thread lock can be
         *        performed instead.
         *
         * @param thread The thread to test current ownership of this. If omitted the ownership is
         *                          identified for the current thread.
         * @return If acquired by the given thread (the current thread if parameter \p thread is
         *         omitted), the number of (recursive) acquire calls is returned. Otherwise
         *         returns 0.
         ******************************************************************************************/
        ALIB_API  int             IsAcquired( Thread* thread= nullptr );


        /** ****************************************************************************************
         *  If parameter is \c Safeness::Unsafe, the whole locking system is disabled.
         *  The only objective here is to to gain execution speed, as thread synchronization causes
         *  relatively expensive system calls.
         *  Use this method only if you are 100% sure that your (otherwise) critical section are
         *  executed in a single threaded environment. And: "relative expensive" means: they are not
         *  really expensive. This is provided only for the rare case that your critical section is
         *  very, very frequently executed.
         *
         * @param safeness  Determines if this object should use a mutex (\c Safeness::Safe)
         *                  or just do nothing (\c Safeness::Unsafe).
         ******************************************************************************************/
        ALIB_API  void            SetMode( enums::Safeness safeness );

        /** ****************************************************************************************
         *  Query if this instance was set to unsafe mode.
         * @return    \c true if unsafe, \c false if not.
         ******************************************************************************************/
        enums::Safeness           Mode()     { return mutex == nullptr ? enums::Safeness::Unsafe
                                                                       : enums::Safeness::Safe;  }

}; // class ThreadLock


}} // namespace lib::threads

/** Type alias name in namespace #aworx. */
using     ThreadLock= aworx::lib::threads::ThreadLock;

}  // namespace aworx

#endif // HPP_ALIB_THREADS_THREADLOCK
