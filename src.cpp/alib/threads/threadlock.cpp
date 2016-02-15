// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
#include "alib/stdafx_alib.h"


#if !defined (HPP_ALIB_THREADS_THREADLOCK)
    #include "alib/threads/threadlock.hpp"
#endif


#if !defined (HPP_ALIB_STRINGS_ASTRING)
    #include "alib/strings/asalloc.hpp"
#endif

#if !defined (HPP_ALIB_TIME)
    #include "alib/time/ticks.hpp"
#endif


using namespace std;

namespace aworx {
namespace           lib {
namespace                   threads {

// #################################################################################################
// class ThreadLock
// #################################################################################################

ThreadLock::ThreadLock( LockMode lockMode, Safeness safeness )
: lockMode(lockMode)
{
    // set safeness
    SetMode( safeness );
}

ThreadLock::~ThreadLock()
{
    ALIB_ASSERT_WARNING_AS( cntAcquirements == 0, "Destruction while locked" );

    #if defined(ALIB_FEAT_THREADS)
        if ( mutex            != nullptr ) delete mutex;
        if ( mutexNotifier    != nullptr ) delete mutexNotifier;
    #endif
}

int ThreadLock::IsAcquired( Thread* thread )
{
    #if defined(ALIB_FEAT_THREADS)
        if ( Mode() == Safeness::Unsafe )
            return cntAcquirements;

        if ( owner == nullptr )
        {
            ALIB_ASSERT( cntAcquirements <= 0 );
            return cntAcquirements;
        }
        ALIB_ASSERT( cntAcquirements > 0 );

        return  ( owner == ( thread != nullptr ? thread : Thread::CurrentThread() ) )
                ? cntAcquirements
                : 0;
    #else
        (void) thread;
        return cntAcquirements;
    #endif
}

void ThreadLock::Acquire()
{
    // are we in unsafe mode?
    if ( Mode() == Safeness::Unsafe )
    {
        // we are still increasing the cntAcquirements
        cntAcquirements=  lockMode == LockMode::Recursive  ? cntAcquirements + 1
                                                           : 1;

        // reached warning limit?
        ALIB_ASSERT_WARNING_AS( cntAcquirements > 0 && cntAcquirements % RecursionWarningThreshold != 0,
                "Recursion depth " << cntAcquirements
           <<   ". To prevent this, change ThreadSafe.recursionWarningThreshold or fix your code!" );

        // end of unsafe version of this method
        return;
    }


    // get current thread
    Thread* thisThread= Thread::CurrentThread();

    // synchronize on mutex
    #if defined(ALIB_FEAT_THREADS)
    unique_lock<std::mutex> lock(*mutex);  {
    #endif

        // we already own the thread
        if( owner == thisThread )
        {
            // we are still increasing the cntAcquirements
            cntAcquirements=  lockMode== LockMode::Recursive  ? cntAcquirements + 1
                                                      : 1;
            // reached warning limit?
            ALIB_ASSERT_WARNING_AS( cntAcquirements > 0  && cntAcquirements % RecursionWarningThreshold != 0,
                    "Recursion depth " << cntAcquirements
                <<  ". To prevent this, change ThreadSafe.recursionWarningThreshold or fix your code!" );

            #if defined(ALIB_FEAT_THREADS)
                lock.unlock();
            #endif
            return;
        }

        #if defined(ALIB_FEAT_THREADS)
        // we do not own this thread, wait until lock is free
        bool hasWarned= false;
        while( owner != nullptr )
        {
            // wait unconditional
            if ( WaitWarningTimeLimitInMillis <= 0 || hasWarned )
                mutexNotifier->wait( lock );

            // wait with time limit
            else
            {
                Ticks    waitTime;
                mutexNotifier->wait_for( lock,  std::chrono::milliseconds(WaitWarningTimeLimitInMillis) );
                auto millis=   waitTime.Age().InMillis();
                if ( millis >= WaitWarningTimeLimitInMillis )
                {
                    hasWarned= true;
                    ALIB_WARNING_AS(    "Timeout (" << WaitWarningTimeLimitInMillis
                                         << " ms). Change your codes' critical section length if possible."
                                            " Thread ID/Name: "  <<  thisThread->GetId() <<  '/' << thisThread->GetName()
                                      );
                }
            }
        }
        #endif

        // take control
        owner=           thisThread;
        cntAcquirements= 1;

    #if defined(ALIB_FEAT_THREADS)
    } lock.unlock(); // synchronized
    #endif
}


void ThreadLock::Release()
{
    // are we in unsafe mode?
    if ( Mode() == Safeness::Unsafe )
    {
        // not locked
        if( lockMode == LockMode::Recursive && cntAcquirements == 0 )
        {
            ALIB_ERROR( "Release without acquire (unsafe mode)."
                        "Note: This must never happen, check your code, set lock to safe mode!" );
        }

        // we are still decreasing the cntAcquirements
        cntAcquirements=  lockMode== LockMode::Recursive ? cntAcquirements - 1
                                                         : 0;

        // end of unsafe version of this method
        return;
    }

    // synchronize on mutex
    #if defined(ALIB_FEAT_THREADS)
    unique_lock<std::mutex> lock(*mutex); {
    #endif

        // not locked?
        ALIB_ASSERT_ERROR( cntAcquirements != 0, "Illegal release without acquire (safe mode)." );

        // decreasing the cntAcquirements
        cntAcquirements=  lockMode == LockMode::Recursive  ? cntAcquirements - 1
                                                           : 0;

        // release and notify next waiting thread
        if( cntAcquirements == 0 )
        {
            owner=    nullptr;
            #if defined(ALIB_FEAT_THREADS)
                mutexNotifier->notify_one();
            #endif
        }
    #if defined(ALIB_FEAT_THREADS)
    } lock.unlock(); // synchronized
    #endif
}


void ThreadLock::SetMode( Safeness safeness )
{
    // are we in unsafe mode?
    if ( mutex == nullptr )
    {
        // already locked? ALIB Error
        if( cntAcquirements != 0 )
        {
            ALIB_ERROR_AS( "Cannot switch safeness mode while already locked. "
                           "Current mode: unsafe, requested mode: "  << safeness )

            return;
        }

        //  switch on?
        if( safeness == Safeness::Safe )
        {
            #if defined(ALIB_FEAT_THREADS)
                mutex=            new std::mutex();
                mutexNotifier=    new condition_variable();
            #else
                mutex=            this;
            #endif
        }

        // end of unsafe version of this method
        return;
    }

    // synchronize on mutex
    #if defined(ALIB_FEAT_THREADS)
    unique_lock<std::mutex> lock(*mutex); {
    #endif
        // already locked? ALIB Error
        if ( owner != nullptr )
        {
            ALIB_ERROR_AS(  "Cannot switch safeness mode while already locked. "
                            "Current mode: safe, requested mode: " << safeness
                            << " Owner: "  << owner->GetId() <<  '/' << owner->GetName() )
            return;
        }

        //  switch off?
        if( safeness == Safeness::Unsafe )
        {
            #if defined(ALIB_FEAT_THREADS)
                lock.unlock();
                delete mutexNotifier;    mutexNotifier= nullptr;
                delete mutex;            mutex= nullptr;
            #else
                mutex= nullptr;
            #endif

            return;
        }
    #if defined(ALIB_FEAT_THREADS)
    } lock.unlock(); // synchronized
    #endif

}


}}}// namespace aworx::lib::threads


