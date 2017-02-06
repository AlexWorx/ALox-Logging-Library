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

/** ************************************************************************************************
 *  This namespace of the A-Worx Library holds classes that are providing an interface into
 *  multi threaded programming. The design of the classes tries to mimic the basic thread
 *  interface of the Java language.
 *
 *  As C# provides standardized multi-threading support, this namespace is quite empty in
 *  the C# Version of the AWorx Library.
 **************************************************************************************************/
using System.Collections.Generic;
using System.Runtime.CompilerServices;


namespace cs.aworx.lib.threads  {

/** ************************************************************************************************
 * This class extends class ThreadLock, adding functionality to register 'acquirers' of type
 * \b %ThreadLock. Only with the second \e acquirer added, the lock is activated
 * using \ref cs::aworx::lib::threads::ThreadLock::SetSafeness "ThreadLock.SetSafeness(Safeness.Safe)".
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
 * explained with  \ref cs::aworx::lib::ALIB::StdOutputStreamsLock "ALIB.StdOutputStreamsLock". If the first acquirer
 * is null, the second should be added in a thread-safe way. This means,
 * the code invoking #AddAcquirer needs to care for itself, that this object is not acquired
 * during this process. E.g. it can be done in the bootstrap section of a process, when no parallel
 * threads were started. For further acquirere, such care does not need to be taken.
 * While an \e acquirer must not be attached twice, 'anonymous' (null) \e acquirers may.
 * For each anonymous invocation of #AddAcquirer, a corresponding call #RemoveAcquirer is
 * needed, to get back to \b Safeness.Unsafe.
 **************************************************************************************************/
public class SmartLock :  ThreadLock
{
    // #############################################################################################
    // Protected fields
    // #############################################################################################

        /**  The list of acquirers.  */
        protected List<ThreadLock>             acquirers                    =new List<ThreadLock>();

    // #############################################################################################
    // Constructors
    // #############################################################################################

        /** ****************************************************************************************
         * Constructs an SmartLock. Parent ThreadLock is initialized to Unsafe mode.
         ******************************************************************************************/
        public SmartLock()
        : base( LockMode.Recursive, Safeness.Unsafe )
        {
        }

    // #############################################################################################
    // Interface
    // #############################################################################################

        /** ****************************************************************************************
         * Adds an acquirer.
         * @param newAcquirer The acquirer to add.
         * @return The new number of \e acquirers set.
         ******************************************************************************************/
        [MethodImpl(MethodImplOptions.Synchronized)]
        public virtual int AddAcquirer( ThreadLock newAcquirer )
        {
            int count= -1;
            #if DEBUG
                bool errAlreadyAdded=      true;
                bool errHasToBeRecursive=   false;
                int  errWasAcquired=        0;
            #endif

            count= acquirers.Count;

            // check doubly added
            if (     newAcquirer == null
                 ||  acquirers.IndexOf( newAcquirer ) < 0 )
            {
                #if DEBUG
                    errAlreadyAdded= false;
                    errWasAcquired=  DbgCountAcquirements() == 0 ? 0 : 1;
                #endif

                // switch on?
                if( acquirers.Count == 1 )
                {
                    #if DEBUG
                        errAlreadyAdded= false;
                    #endif
                    ThreadLock firstAcquirer= acquirers[0];

                    // non-anonymous acquirer?
                    if ( firstAcquirer != null )
                    {
                        if( firstAcquirer.GetMode() == LockMode.Recursive )
                        {
                            firstAcquirer.Acquire();
                                SetSafeness( Safeness.Safe );
                                acquirers.Add( newAcquirer );
                                count++;
                            firstAcquirer.Release();
                        }
                        #if DEBUG
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
                        #if DEBUG
                            if ( errWasAcquired == 1 )
                                errWasAcquired= 2;
                        #endif

                        SetSafeness( Safeness.Safe );
                        acquirers.Add( newAcquirer );
                        count++;
                    }
                }
                else
                    acquirers.Add( newAcquirer );
            }

            #if DEBUG
                ALIB_DBG.ASSERT_ERROR( !errAlreadyAdded,    "Acquirer already registered." );
                ALIB_DBG.ASSERT_ERROR( !errHasToBeRecursive, "Acquireres need to be in recursive mode " );
                ALIB_DBG.ASSERT_ERROR( errWasAcquired != 1,  "Already acquired. Hint: Acquirer[0] must not acquire this before adding itself!" );
                ALIB_DBG.ASSERT_ERROR( errWasAcquired != 2,  "Acquired and acquirer[0] anonymous. Misuse of SmartLock!" );
            #endif

            return count;
        }

        /** ****************************************************************************************
         * Removes an acquirer.
         * @param acquirerToRemove The acquirer to remove.
         * @return The new number of \e acquirers set.
         ******************************************************************************************/
        [MethodImpl(MethodImplOptions.Synchronized)]
        public virtual int RemoveAcquirer( ThreadLock acquirerToRemove )
        {
            int  count= 0;
            bool errNotFound=    true;
            bool errWasAcquired= false;

            #if DEBUG
                errWasAcquired=  DbgCountAcquirements() != 0;
            #endif

            // search acquirer
            if( acquirers.IndexOf( acquirerToRemove ) >= 0 )
            {
                errNotFound= false;

                // switch off?
                if( acquirers.Count == 2 )
                {
                    ThreadLock acquirer1=  acquirers[0];
                    ThreadLock acquirer2=  acquirers[1];
                    if( acquirer1== acquirerToRemove ) acquirer1= null;
                    if( acquirer2== acquirerToRemove ) acquirer2= null;

                    // Acquire acquirers in their order of appearance
                    if ( acquirer1 != null ) acquirer1.Acquire();
                      if ( acquirer2 != null ) acquirer2.Acquire();
                        SetSafeness( Safeness.Unsafe );
                        acquirers.Remove( acquirerToRemove );
                      if ( acquirer2 != null ) acquirer2.Release();
                    if ( acquirer1 != null ) acquirer1.Release();
                }

                // just remove acquirer, keep mode
                else
                    acquirers.Remove( acquirerToRemove );
            }

            count= acquirers.Count;

            ALIB_DBG.ASSERT_ERROR( !errNotFound,    "Acquirer not found." );
            ALIB_DBG.ASSERT_ERROR( !errWasAcquired, "Acquired on release. Hint: Acquirers must acquire only when acquired themselves!" );
            return count;
        }

        /** ****************************************************************************************
         * Returns the number of \e acquirers. This is for debug and statistics purposes.
         * @return The number of \e acquirers set.
         ******************************************************************************************/
        public int           CntAcquirers()
        {
            return acquirers.Count;
        }

} // class SmartLock


} // namespace / EOF
