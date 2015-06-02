// #################################################################################################
//  aworx::util - Classes we need
//
//  (c) 2013-2015 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
#include "stdafx_awxu.h"


#if !defined (HPP_AWORX_UTIL_THREADLOCK)
    #include "threadlock.hpp"
#endif

#ifdef AWXU_FEAT_THREADS

#if !defined (HPP_AWORX_UTIL_ASTRING)
    #include "astring.hpp"
#endif

#if !defined (HPP_AWORX_UTIL_TICKS)
    #include "ticks.hpp"
#endif


using namespace std;


namespace aworx {
namespace       util {

// #################################################################################################
// class ThreadLock
// #################################################################################################

ThreadLock::ThreadLock( bool recursiveMode, bool setUnsafeMode )
{
    // save parameters
    this->recursiveMode=     recursiveMode;

    // set safeness
    SetUnsafe( setUnsafeMode );
}

ThreadLock::~ThreadLock()
{
    if ( mutex            != nullptr ) delete mutex;
    if ( mutexNotifier    != nullptr ) delete mutexNotifier;
}

bool ThreadLock::IsAcquired( Thread* thread )
{
    if ( IsUnsafe() )
        return lockCount > 0 ;

    if ( owner == nullptr )
        return false;

    return  owner == ( thread != nullptr ? thread : Thread::CurrentThread() ) ;
}

void ThreadLock::Acquire()
{
    // are we in unsafe mode?
    if ( IsUnsafe() )
    {
        // we are still increasing the lockCount
        lockCount=  recursiveMode     ? lockCount + 1
                                    : 1;
        // reached warning limit
        if ( lockCount  <= 0  )
        {
            if ( AWXU::AcquireErrorHandler() )
                AWXU::Error( "ThreadLock::Acquire(): unsafe mode: Counter invalid (<= 0): This should never happen. Set lock to safe mode!" );
        }

        else if ( lockCount % RecursionWarningThreshold == 0 )
        {
            if( AWXU::AcquireErrorHandler() )
            {
                AString256 errmsg( "ThreadLock::Acquire(): Recursion depth " ); errmsg << lockCount
                              <<  ". To prevent this, change ThreadSafe.recursionWarningThreshold or fix your code!";
                AWXU::Warning( errmsg.Buffer() );
            }
        }

        // end of unsafe version of this method
        return;
    }


    // get current thread
    Thread* thisThread= Thread::CurrentThread();

    // synchronize on mutex
    unique_lock<std::mutex> lock(*mutex);
    {
        // we already own the thread
        if( owner == thisThread )
        {
            // we are still increasing the lockCount
            lockCount=  recursiveMode     ? lockCount + 1
                                        : 1;
            // reached warning limit
            if ( lockCount % RecursionWarningThreshold == 0  && AWXU::AcquireErrorHandler() )
            {
                AString256 errmsg( "ThreadLock::Acquire(): Recursion depth " ); errmsg << lockCount
                              <<  ". To prevent this, change ThreadSafe.recursionWarningThreshold or fix your code!";
                AWXU::Warning( errmsg.Buffer() );
            }

            lock.unlock();
            return;
        }

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
                    if( AWXU::AcquireErrorHandler() )
                    {
                        AString256 errmsg( "ThreadLock::Acquire() took " ); errmsg << millis
                                << " ms, which exceeds given limit of "  << WaitWarningTimeLimitInMillis
                                << " ms. Change your codes critical section length if possible. Thread ID/Name: " <<  thisThread->GetId() <<  '/' << thisThread->GetName();

                        AWXU::Warning( errmsg.Buffer() );
                    }
                }
            }
        }

        // take control
        owner=        thisThread;
        lockCount=    1;

    } lock.unlock(); // synchronized
}


void ThreadLock::Release()
{
    // are we in unsafe mode?
    if ( IsUnsafe() )
    {
        // not locked
        if( recursiveMode && lockCount == 0 )
        {
            if( AWXU::AcquireErrorHandler() )
                AWXU::Error( "ThreadLock::Release() without having the lock (in unsafe mode). This must never happen, check your code, set lock to safe mode!" );
        }

        // we are still decreasing the lockCount
        lockCount=  recursiveMode     ? lockCount - 1
                                    : 0;

        // end of unsafe version of this method
        return;
    }

    // synchronize on mutex
    unique_lock<std::mutex> lock(*mutex);
    {
        // not locked
        if( lockCount == 0 && AWXU::AcquireErrorHandler() )
            AWXU::Error( "ThreadLock::Release() without having the lock. This must never happen, check your code!" );

        // decreasing the lockCount
        lockCount=  recursiveMode     ? lockCount - 1
                                    : 0;

        // release and notify next waiting thread
        if( lockCount == 0 )
        {
            owner=    nullptr;
            mutexNotifier->notify_one();
        }
    } lock.unlock(); // synchronized
}


void ThreadLock::SetUnsafe( bool setUnsafe )
{
    // are we in unsafe mode?
    if ( mutex == nullptr )
    {
        // already locked? AWXU Error
        if( lockCount != 0 && AWXU::AcquireErrorHandler() )
        {
            AString256 errmsg( "ThreadLock::SetUnsafe(): Cannot switch safeness mode while already locked. Current mode: unsafe, requested mode: " );
                       errmsg << ( setUnsafe ? "unsafe." : "safe." );
            AWXU::Error( errmsg.Buffer() );
        }

        //  switch on?
        if( ! setUnsafe )
        {
            mutex=            new std::mutex();
            mutexNotifier=    new condition_variable();
        }

        // end of unsafe version of this method
        return;
    }

    // synchronize on mutex
    unique_lock<std::mutex> lock(*mutex);
    {
        // already locked? AWXU Error
        if( owner != nullptr && AWXU::AcquireErrorHandler() )
        {
            AString256 errmsg( "ThreadLock::SetUnsafe(): Cannot switch safeness mode while already locked. Current mode: safe, requested mode: " );
                       errmsg << ( setUnsafe ? "unsafe." : "safe." ) << " Owner: "  << owner->GetId() <<  '/' << owner->GetName();
            AWXU::Error( errmsg.Buffer() );
        }

        //  switch off?
        if( setUnsafe )
        {
            lock.unlock();
            delete mutexNotifier;    mutexNotifier= nullptr;
            delete mutex;            mutex= nullptr;
            return;
        }
    } lock.unlock(); // synchronized

}


}} // namespace aworx::util

#endif // AWXU_FEAT_THREADS
