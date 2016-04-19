// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################


package com.aworx.lib.threads;

import java.util.ArrayList;

import com.aworx.lib.ALIB;
import com.aworx.lib.enums.LockMode;
import com.aworx.lib.enums.Safeness;


/** ************************************************************************************************
 * This class extends class ThreadLock, adding functionality to register 'acquirers' of type
 * \b %ThreadLock. Only with the second \e acquirer added, the lock is activated
 * using \ref com::aworx::lib::threads::ThreadLock::setSafeness "ThreadLock.setSafeness(Safeness.Safe)".
 * The goal is to not use a mutex, when such use is not needed. In occasions with very high
 * frequency of acquisition, this can provide a performance benefit.
 *
 * <b>The following rules apply:</b><br>
 * - An instance of this type must not be acquired before an \e acquirer is registered.
 * - The \e acquirers have to be in recursive mode.
 * - If \e acquirers are locked in a nested fashion, then they have to be added
 *   in the same order they are locked and removed in reverse order
 * - An \e acquirer must not be added twice. (This is not a technical restriction, but a chosen
 *   design. While a second addition is ignored, in debug versions of the code, an
 *   <em>ALib Error Report</em> is written (by default this triggers an assertion).
 *
 * <b>Using nulled acquirers:</b><br>
 * Sometimes it is useful to add a \c null as an \e acquirer. A sample for this is found and
 * explained with
 * \ref com::aworx::lib::ALIB::stdOutputStreamsLock "ALIB.stdOutputStreamsLock".
 * If the first acquirer is null, the second should be added in a thread-safe way. This means,
 * the code invoking #addAcquirer needs to care for itself, that this object is not acquired
 * during this process. E.g. it can be done in the bootstrap section of a process, when no parallel
 * threads were started. For further acquirers, such care does not need to be taken.
 * While an \e acquirer must not be attached twice, 'anonymous' (null) \e acquirers may.
 * For each anonymous invocation of #addAcquirer, a corresponding call #removeAcquirer is
 * needed, to get back to \b Safeness.Unsafe.
 **************************************************************************************************/
public class SmartLock extends  ThreadLock
{
    // #############################################################################################
    // Protected fields
    // #############################################################################################

        /**  The list of acquirers.  */
        protected ArrayList<ThreadLock>        acquirers    = new ArrayList<ThreadLock>();

    // #############################################################################################
    // Constructors
    // #############################################################################################

        /** ****************************************************************************************
         * Constructs an SmartLock. Parent ThreadLock is initialized to Unsafe mode.
         ******************************************************************************************/
        public SmartLock()
        {
            super( LockMode.RECURSIVE, Safeness.UNSAFE );
        }

    // #############################################################################################
    // Interface
    // #############################################################################################

        /** ****************************************************************************************
         * Adds an acquirer.
         * @param newAcquirer The acquirer to add.
         * @return The new number of \e acquirers set.
         ******************************************************************************************/
        public int   addAcquirer( ThreadLock newAcquirer )
        {
            int count= -1;
            boolean errAllreadyAdded=      true;
            boolean errHasToBeRecursive=   false;
            int     errWasAcquired=        0;

            try { ALIB.lock.acquire();

                count= acquirers.size();

                // check doubly added
                if (     newAcquirer == null
                     ||  acquirers.indexOf( newAcquirer ) < 0 )
                {
                    errAllreadyAdded= false;
                    errWasAcquired=   dbgCountAcquirements(null) == 0 ? 0 : 1;

                    // switch on?
                    if( acquirers.size() == 1 )
                    {
                        errAllreadyAdded= false;
                        ThreadLock firstAcquirer= acquirers.get(0);

                        // non-anonymous acquirer?
                        if ( firstAcquirer != null )
                        {
                            if( firstAcquirer.getMode() == LockMode.RECURSIVE )
                            {
                                firstAcquirer.acquire();
                                    setSafeness( Safeness.SAFE );
                                    acquirers.add( newAcquirer );
                                    count++;
                                firstAcquirer.release();
                            }
                            else
                                errHasToBeRecursive= false;

                        }
                        // critical section: our first acquirer is anonymous. As documented in class,
                        // this must happen only in situations, when we are sure, that we are safe, e.g. still
                        // single threaded execution of process bootstrap.
                        else
                        {
                            // If this assert happens, its only good luck: we detected a misuse. But it should
                            // be very seldom to be detected this way :-/
                            if ( errWasAcquired == 1 )
                                errWasAcquired= 2;

                            setSafeness( Safeness.SAFE );
                            acquirers.add( newAcquirer );
                            count++;
                        }
                    }
                    else
                        acquirers.add( newAcquirer );
                }
            } finally { ALIB.lock.release(); }

            ALIB.ASSERT_ERROR( !errAllreadyAdded,    "Acquirer already registered." );
            ALIB.ASSERT_ERROR( !errHasToBeRecursive, "Acquireres need to be in recursive mode " );
            ALIB.ASSERT_ERROR( errWasAcquired != 1,  "Already aquired. Hint: Acquirer[0] must not acquire this before adding itself!" );
            ALIB.ASSERT_ERROR( errWasAcquired != 2,  "Aquired and acquirer[0] anonymous. Misuse of SmartLock!" );

            return count;
        }

        /** ****************************************************************************************
         * Removes an acquirer.
         * @param acquirerToRemove The acquirer to remove.
         * @return The new number of \e acquirers set.
         ******************************************************************************************/
        public int   removeAcquirer( ThreadLock acquirerToRemove )
        {
            int     count= 0;
            boolean errNotFound=    true;
            boolean errWasAcquired= false;;

            try { ALIB.lock.acquire();

                errWasAcquired= dbgCountAcquirements(null) != 0;

                // search acquirer
                if( acquirers.indexOf( acquirerToRemove ) >= 0 )
                {
                    errNotFound= false;

                    // switch off?
                    if( acquirers.size() == 2 )
                    {
                        ThreadLock acquirer1=  acquirers.get(0);
                        ThreadLock acquirer2=  acquirers.get(1);
                        if( acquirer1== acquirerToRemove ) acquirer1= null;
                        if( acquirer2== acquirerToRemove ) acquirer2= null;

                        // Acquire acquirers in their order of appearance
                        if ( acquirer1 != null ) acquirer1.acquire();
                          if ( acquirer2 != null ) acquirer2.acquire();
                            setSafeness( Safeness.UNSAFE );
                            acquirers.remove( acquirerToRemove );
                          if ( acquirer2 != null ) acquirer2.release();
                        if ( acquirer1 != null ) acquirer1.release();
                    }

                    // just remove acquirer, keep mode
                    else
                        acquirers.remove( acquirerToRemove );
                }

               count= acquirers.size();

            } finally { ALIB.lock.release(); }

            ALIB.ASSERT_ERROR( !errNotFound,    "Acquirer not found." );
            ALIB.ASSERT_ERROR( !errWasAcquired, "Aquired on release. Hint: Acquirers must acquire only when acquired themselves!" );
            return count;
        }

        /** ****************************************************************************************
         * Returns the number of \e acquirers. This is for debug and statistics purposes.
         * @return The number of \e acquirers set.
         ******************************************************************************************/
        public int           cntAcquirers()
        {
            return acquirers.size();
        }

} // class SmartLock
