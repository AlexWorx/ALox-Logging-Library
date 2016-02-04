// #################################################################################################
//  cs.aworx.lox.core - ALox Logging Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################

using System;
using System.Collections.Generic;
using cs.aworx.lib;
using cs.aworx.lib.time;
using cs.aworx.lib.strings;

#if !ALOX_NO_THREADS
    using System.Threading;
#endif

namespace cs.aworx.lox.core {
/** ************************************************************************************************
 *
 *  Encapsulates information of the caller that can be collected. This is platform specific, in
 *  this case, .NET 4.5. What we currently can get from the .NET compiler, is the source file name
 *  of the calling code, the line number within the source file name and the name of the method
 *  the call is placed. We do not get the class name of the object or even its instance.
 *
 **************************************************************************************************/
#if ALOX_DBG_LOG || ALOX_REL_LOG

public class CallerInfo
{
    // #############################################################################################
    // Public fields / Properties
    // #############################################################################################

    /** Name and path of the source code file the log call is placed in.  **/
    public        String                    SourceFileName;

    /** Line number within the source code file the log call is placed in.  **/
    public        int                       LineNumber;

    /** Name of the method the log call is placed in.  **/
    public        String                    MethodName;

    /** Time of the call represented by this instance.  **/
    public        Ticks                     TimeStamp                     = new Ticks();

    /** The id of the thread that executed the log.  **/
    public        int                       ThreadID;

    /** The name of the thread that executed the log.  **/
    public        AString                   ThreadName                    = new AString(32);


    // #############################################################################################
    // public interface
    // #############################################################################################

    /** ********************************************************************************************
     * Stores caller parameters, sets actual time stamp and receives thread information
     * @param callerSourceFileName     Name and path of the source code file the log call is
     *                                        placed in. </param>
     * @param callerLineNumber         Line number within the source code file the log call is
     *                                        placed in. </param>
     * @param callerMemberName         Name of the method the log call is placed in. </param>
     * @param threadDictionary         Dictionary for translating thread IDs into more readable
     *                                        thread names. </param>
     **********************************************************************************************/
#if !ALOX_NO_THREADS
    public void Set (String callerSourceFileName, int callerLineNumber, String callerMemberName, Dictionary<int, String> threadDictionary )
#else
    public void Set (String callerSourceFileName, int callerLineNumber, String callerMemberName )
#endif
    {
        // 1) set the actual timestamp as early as possible
        TimeStamp.Set();

        // 2) save parameters
        this.MethodName=        callerMemberName;
        this.SourceFileName=    callerSourceFileName;
        this.LineNumber=        callerLineNumber;

        // 3) get thread information
        #if !ALOX_NO_THREADS
        {
            ThreadName.Clear();

            // get current thread
            Thread thread= Thread.CurrentThread;
            ThreadID=      thread.ManagedThreadId;

            // do we have a dictionary entry?
            String threadName;
            if( threadDictionary.TryGetValue( ThreadID,  out threadName) )
                ThreadName._( threadName );
            else
            {
                if ( String.IsNullOrEmpty ( thread.Name ) )
                    ThreadName._( ThreadID );
                else
                    ThreadName._( thread.Name )._( '(' )._( ThreadID )._( ')' );
            }
        }
        #endif
    }

} // class CallerInfo

#endif // ALOX_DBG_LOG || ALOX_REL_LOG ,started before class CallerInfo


} // namespace
