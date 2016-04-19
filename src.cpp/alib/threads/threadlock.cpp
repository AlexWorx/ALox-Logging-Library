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
#if !defined (HPP_ALIB_TIME)
    #include "alib/time/ticks.hpp"
#endif

#include <algorithm>


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
    SetSafeness( safeness );
}

ThreadLock::~ThreadLock()
{
    ALIB_ASSERT_WARNING_S512( cntAcquirements == 0, "Destruction while locked" );

    #if defined(ALIB_FEAT_THREADS)
        if ( mutex            != nullptr ) delete mutex;
        if ( mutexNotifier    != nullptr ) delete mutexNotifier;
    #endif
}

int ThreadLock::DbgCountAcquirements( Thread* thread )
{
    #if defined(ALIB_FEAT_THREADS)
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

#if defined( ALIB_DEBUG )
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
        ALIB_ASSERT_WARNING_S512( cntAcquirements > 0 && cntAcquirements % RecursionWarningThreshold != 0,
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
            ALIB_ASSERT_WARNING_S512( cntAcquirements > 0  && cntAcquirements % RecursionWarningThreshold != 0,
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
                    ALIB_WARNING_S512(    "Timeout (" << WaitWarningTimeLimitInMillis
                                         << " ms). Change your codes' critical section length if possible."           << NewLine
                                         << "This thread: " <<  thisThread->GetId() <<  '/' << thisThread->GetName()  << NewLine
                                         << "Owner: "       <<  owner->     GetId() <<  '/' << owner->     GetName()  << NewLine
                                         << "Location of acquirement: " << acquirementSourcefile << ':'
                                                                        << acquirementLineNumber << ' '
                                                                        << acquirementMethodName << "()"
                                      );
                }
            }
        }
        #endif

        // take control
        owner=           thisThread;
        #if defined( ALIB_DEBUG )
            acquirementSourcefile= file;
            acquirementLineNumber= line;
            acquirementMethodName= func;
        #endif
        cntAcquirements= 1;

    #if defined(ALIB_FEAT_THREADS)
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


void ThreadLock::SetSafeness( Safeness safeness )
{
    // are we in unsafe mode?
    if ( mutex == nullptr )
    {
        // already locked? ALIB Error
        if( cntAcquirements != 0 )
        {
            ALIB_ERROR_S512( "Cannot switch safeness mode while already locked. "
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
            ALIB_ERROR_S512(  "Cannot switch safeness mode while already locked. "
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

// #################################################################################################
// class SmartLock
// #################################################################################################

int SmartLock::CntAcquirers()
{
    OWN( ALIB::Lock )
    return (int) acquirers.size();
}

int   SmartLock::AddAcquirer( ThreadLock* newAcquirer )
{
    int count= -1;
    #if defined ALIB_DEBUG
        bool errAllreadyAdded=      true;
        bool errHasToBeRecursive=   false;
        int  errWasAcquired=        0;
    #endif
    {
        OWN( ALIB::Lock )

        count= (int) acquirers.size();

        // check doubly added
        if (     newAcquirer == nullptr
             ||  std::find( acquirers.begin(), acquirers.end(), newAcquirer ) == acquirers.end() )
        {
            #if defined ALIB_DEBUG
                errAllreadyAdded= false;
                errWasAcquired=   ThreadLock::DbgCountAcquirements() != 0 ? 1 : 0;
            #endif

            // switch on?
            if( acquirers.size() == 1 )
            {
                ThreadLock* firstAcquirer= acquirers[0];

                // non-anonymous acquirer?
                if ( firstAcquirer != nullptr )
                {
                    if( firstAcquirer->GetMode() == LockMode::Recursive )
                    {
                        firstAcquirer->Acquire( ALIB_DBG_SRC_INFO_PARAMS);
                            SetSafeness( Safeness::Safe );
                            acquirers.emplace_back( newAcquirer );
                            count++;
                        firstAcquirer->Release();
                    }
                    #if defined ALIB_DEBUG
                    else
                        errHasToBeRecursive= false;
                    #endif

                }

                // critical section: our first acquirer is anonymous. As documented in class,
                // this must happen only in situations, when we are sure, that we are safe, e.g. still
                // single threaded execution of process bootstrap.
                else
                {
                    // If this assert happens, its only good luck: we detected a misuse. But it should
                    // be very seldom to be detected this way :-/
                    #if defined ALIB_DEBUG
                        if ( errWasAcquired == 1 )
                            errWasAcquired= 2;
                    #endif

                    SetSafeness( Safeness::Safe );
                    acquirers.emplace_back( newAcquirer );
                    count++;
                }
            }
            else
                acquirers.emplace_back( newAcquirer );
        }
    }//OWN


    ALIB_ASSERT_ERROR( !errAllreadyAdded,    "Acquirer already registered." );
    ALIB_ASSERT_ERROR( !errHasToBeRecursive, "Acquireres need to be in recursive mode " );
    ALIB_ASSERT_ERROR( errWasAcquired!=1,    "Already aquired. Hint: Acquirer[0] must not acquire this before adding itself!" );
    ALIB_ASSERT_ERROR( errWasAcquired!=2,    "Aquired and acquirer[0] anonymous. Misuse of SmartLock!" );

    return count;
}

int   SmartLock::RemoveAcquirer( ThreadLock* acquirerToRemove )
{
    int count= -1;
    #if defined ALIB_DEBUG
        bool errNotFound=    true;
        bool errWasAcquired= false;
    #endif
    {
        OWN( ALIB::Lock )

        #if defined ALIB_DEBUG
            errWasAcquired=   ThreadLock::DbgCountAcquirements() != 0;
        #endif

        // search acquirer
        auto it= std::find( acquirers.begin(), acquirers.end(), acquirerToRemove );
        if( it != acquirers.end() )
        {
            #if defined ALIB_DEBUG
                errNotFound= false;
            #endif

            // switch off?
            if( acquirers.size() == 2 )
            {
                ThreadLock* acquirer1=  acquirers[0];
                ThreadLock* acquirer2=  acquirers[1];
                if( acquirer1== acquirerToRemove ) acquirer1= nullptr;
                if( acquirer2== acquirerToRemove ) acquirer2= nullptr;

                // Aquire acquirers in their order of appearance
                if ( acquirer1 != nullptr ) acquirer1->Acquire(ALIB_DBG_SRC_INFO_PARAMS);
                  if ( acquirer2 != nullptr ) acquirer2->Acquire(ALIB_DBG_SRC_INFO_PARAMS);
                      SetSafeness( Safeness::Unsafe );
                      acquirers.erase( it );
                  if ( acquirer2 != nullptr ) acquirer2->Release();
                if ( acquirer1 != nullptr ) acquirer1->Release();
            }

            // just remove acquirer, keep mode
            else
                acquirers.erase( it );
        }
        count= (int) acquirers.size();
    }

    ALIB_ASSERT_ERROR( !errNotFound,    "Acquirer not found." );
    ALIB_ASSERT_ERROR( !errWasAcquired, "Aquired on release. Hint: Acquirers must acquire only when acquired themselves!" );
    return count;
}



}}}// namespace aworx::lib::threads


