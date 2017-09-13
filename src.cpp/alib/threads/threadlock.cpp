// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
#include "alib/alib.hpp"


#if !defined (HPP_ALIB_THREADS_THREADLOCK)
    #include "alib/threads/threadlock.hpp"
#endif
#if !defined (HPP_ALIB_TIME_TICKS)
    #include "alib/time/ticks.hpp"
#endif

namespace aworx { namespace lib { namespace threads
{

ThreadLock::ThreadLock( LockMode pLockMode, Safeness pSafeness )
: lockMode(pLockMode)
{
    SetSafeness( pSafeness );
}

ThreadLock::~ThreadLock()
{
    ALIB_ASSERT_WARNING( cntAcquirements == 0, "Destruction while locked" );

    #if ALIB_FEAT_THREADS
        if ( mutex            != nullptr ) delete mutex;
        if ( mutexNotifier    != nullptr ) delete mutexNotifier;
    #endif
}

int ThreadLock::DbgCountAcquirements( Thread* thread ) const
{
    #if ALIB_FEAT_THREADS
        if ( GetSafeness() == Safeness::Unsafe )
            return cntAcquirements;

        if ( owner == nullptr )
        {
            ALIB_ASSERT( cntAcquirements <= 0 );
            return cntAcquirements;
        }
        ALIB_ASSERT( cntAcquirements > 0 );

        return  ( owner == ( thread != nullptr ? thread : Thread::CurrentThread() ) )
                ?  cntAcquirements
                : -cntAcquirements;
    #else
        (void) thread;
        return cntAcquirements;
    #endif
}

#if ALIB_DEBUG
    void ThreadLock::Acquire( const TString& file, int line, const TString& func )
#else
    void ThreadLock::Acquire()
#endif
{
    // are we in unsafe mode?
    if ( GetSafeness() == Safeness::Unsafe )
    {
        // we are still increasing the cntAcquirements
        cntAcquirements=  lockMode == LockMode::Recursive  ? cntAcquirements + 1
                                                           : 1;

        // reached warning limit?
        ALIB_ASSERT_WARNING( cntAcquirements > 0 && cntAcquirements % RecursionWarningThreshold != 0,
                            "Recursion depth warning.\n"
                            "To prevent this, change ThreadSafe.recursionWarningThreshold or fix your code.\n"
                            "Depth: ", cntAcquirements );

        // end of unsafe version of this method
        return;
    }


    // get current thread
    Thread* thisThread= Thread::CurrentThread();

    // synchronize on mutex
    #if ALIB_FEAT_THREADS
    std::unique_lock<std::mutex> lock(*mutex);  {
    #endif

        // we already own the thread
        if( owner == thisThread )
        {
            // we are still increasing the cntAcquirements
            cntAcquirements=  lockMode== LockMode::Recursive  ? cntAcquirements + 1
                                                              : 1;
            // reached warning limit?
            ALIB_ASSERT_WARNING( cntAcquirements > 0  && cntAcquirements % RecursionWarningThreshold != 0,
                                "Recursion depth warning.\n"
                                "To prevent this, change ThreadSafe.recursionWarningThreshold or fix your code.\n"
                                "Depth: ", cntAcquirements );

            #if ALIB_FEAT_THREADS
                lock.unlock();
            #endif
            return;
        }

        #if ALIB_FEAT_THREADS
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
                    ALIB_WARNING( (String1K() <<
                        "Timeout acquiring lock (" << millis
                        << "). Change your codes' critical section length if possible."
                        << "\n  This thread: " << thisThread->GetId() << '/' << thisThread->GetName()
                        << "\n  Owner:       " <<      owner->GetId() << '/' <<      owner->GetName()
                        << "\n  Location of acquirement: " << acquirementSourcefile
                                                           << '[' << acquirementLineNumber << "]: "
                                                           << acquirementMethodName << "().").ToCString()

                    )
                }
            }
        }
        #endif

        // take control
        owner=           thisThread;
        #if ALIB_DEBUG
            acquirementSourcefile= file;
            acquirementLineNumber= line;
            acquirementMethodName= func;
        #endif
        cntAcquirements= 1;

    #if ALIB_FEAT_THREADS
    } lock.unlock(); // synchronized
    #endif
}


void ThreadLock::Release()
{
    // are we in unsafe mode?
    if ( GetSafeness() == Safeness::Unsafe )
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
    #if ALIB_FEAT_THREADS
    std::unique_lock<std::mutex> lock(*mutex); {
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
            #if ALIB_FEAT_THREADS
                mutexNotifier->notify_one();
            #endif
        }
    #if ALIB_FEAT_THREADS
    } lock.unlock(); // synchronized
    #endif
}


void ThreadLock::SetSafeness( Safeness safeness )
{
    // are we in unsafe mode?
    if ( mutex == nullptr )
    {
        // already locked? ALIB Error
        if( cntAcquirements != 0 )
        {
            ALIB_ERROR( (String256() << "Cannot switch safeness mode while already locked.\n"
                        "  Current mode: unsafe, requested mode: " << safeness).ToCString() )

            return;
        }

        //  switch on?
        if( safeness == Safeness::Safe )
        {
            #if ALIB_FEAT_THREADS
                mutex=            new std::mutex();
                mutexNotifier=    new std::condition_variable();
            #else
                mutex=            this;
            #endif
        }

        // end of unsafe version of this method
        return;
    }

    // synchronize on mutex
    #if ALIB_FEAT_THREADS
    std::unique_lock<std::mutex> lock(*mutex); {
    #endif
        // already locked? ALIB Error
        if ( owner != nullptr )
        {
            ALIB_ERROR( (String256() << "Cannot switch safeness mode while already locked.\n"
                                        "  Current mode: safe, requested mode: " << safeness << "\n"
                                        "  Owner: "<< owner->GetId() << '/' << owner->GetName() ).ToCString() )
            return;
        }

        //  switch off?
        if( safeness == Safeness::Unsafe )
        {
            #if ALIB_FEAT_THREADS
                lock.unlock();
                delete mutexNotifier;    mutexNotifier= nullptr;
                delete mutex;            mutex= nullptr;
            #else
                mutex= nullptr;
            #endif

            return;
        }
    #if ALIB_FEAT_THREADS
    } lock.unlock(); // synchronized
    #endif

}


}}}// namespace aworx::lib::threads


