// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
#include "alib/alib.hpp"


#if !defined (HPP_ALIB_THREADS_SMARTLOCK)
    #include "alib/threads/smartlock.hpp"
#endif
#if !defined (HPP_ALIB_TIME_TICKS)
    #include "alib/time/ticks.hpp"
#endif

#include <algorithm>


namespace aworx { namespace lib { namespace threads
{

int SmartLock::CntAcquirers()
{
    OWN( lock )
    return static_cast<int>( acquirers.size() );
}

int   SmartLock::AddAcquirer( ThreadLock* newAcquirer )
{
    size_t count;
    #if ALIB_DEBUG
        bool errAlreadyAdded=       true;
        bool errHasToBeRecursive=   false;
        int  errWasAcquired=        0;
    #endif
    {
        OWN( lock )

        count= acquirers.size();

        // check doubly added
        if (     newAcquirer == nullptr
             ||  std::find( acquirers.begin(), acquirers.end(), newAcquirer ) == acquirers.end() )
        {
            #if ALIB_DEBUG
                errAlreadyAdded= false;
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
                    #if ALIB_DEBUG
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
                    #if ALIB_DEBUG
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


    ALIB_ASSERT_ERROR( !errAlreadyAdded,     "Acquirer already registered." );
    ALIB_ASSERT_ERROR( !errHasToBeRecursive, "Acquirers need to be in recursive mode " );
    ALIB_ASSERT_ERROR( errWasAcquired!=1,    "Already acquired. Hint: Acquirer[0] must not acquire this before adding itself!" );
    ALIB_ASSERT_ERROR( errWasAcquired!=2,    "Acquired and acquirer[0] anonymous. Misuse of SmartLock!" );

    return static_cast<int>( count );
}

int   SmartLock::RemoveAcquirer( ThreadLock* acquirerToRemove )
{
    size_t count;
    #if ALIB_DEBUG
        bool errWasAcquired;
        bool errNotFound=    true;
    #endif
    {
        OWN( lock )

        #if ALIB_DEBUG
            errWasAcquired=   ThreadLock::DbgCountAcquirements() != 0;
        #endif

        // search acquirer
        auto it= std::find( acquirers.begin(), acquirers.end(), acquirerToRemove );
        if( it != acquirers.end() )
        {
            #if ALIB_DEBUG
                errNotFound= false;
            #endif

            // switch off?
            if( acquirers.size() == 2 )
            {
                ThreadLock* acquirer1=  acquirers[0];
                ThreadLock* acquirer2=  acquirers[1];
                if( acquirer1== acquirerToRemove ) acquirer1= nullptr;
                if( acquirer2== acquirerToRemove ) acquirer2= nullptr;

                // Acquire acquirers in their order of appearance
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
        count= acquirers.size();
    }

    ALIB_ASSERT_ERROR( !errNotFound,    "Acquirer not found." );
    ALIB_ASSERT_ERROR( !errWasAcquired, "Acquired on release. Hint: Acquirers must acquire only when acquired themselves!" );
    return static_cast<int>( count );
}



}}}// namespace aworx::lib::threads


