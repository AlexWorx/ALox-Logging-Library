// #################################################################################################
//  com.aworx.lox.core - ALox Logging Library
//
//  (c) 2013-2015 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################

using System;
using System.Collections.Generic;
using com.aworx.util;

#if !ALOX_NO_THREADS
    using System.Threading;
#endif

namespace com.aworx.lox.core {
/** ************************************************************************************************
 * <summary>
 *  Encapsulates information of the caller that can be collected. This is platform specific, in
 *  this case, .NET 4.5. What we currently can get from the .NET compiler, is the source file name
 *  of the calling code, the line number within the source file name and the name of the method
 *  the call is placed. We do not get the class name of the object or even its instance.
 * </summary>
 **************************************************************************************************/
#if ALOX_DEBUG || ALOX_REL_LOG

public class CallerInfo
{
    // #############################################################################################
    // Public fields / Properties
    // #############################################################################################

    /** <summary>    Name and path of the source code file the log call is placed in. </summary> **/
    public        String                    SourceFileName;

    /** <summary>    Line number within the source code file the log call is placed in. </summary> **/
    public        int                       LineNumber;

    /** <summary>    Name of the method the log call is placed in. </summary> **/
    public        String                    MethodName;

    /** <summary> Time of the call represented by this instance. </summary> **/
    public        Ticks                     TimeStamp                    = new Ticks();

    /** <summary> The id of the thread that executed the log. </summary> **/
    public        int                       ThreadID;

    /** <summary> The name of the thread that executed the log. </summary> **/
    public        AString                   ThreadName                    = new AString(32);


    // #############################################################################################
    // public interface
    // #############################################################################################

    /** ********************************************************************************************
     * <summary> Stores caller parameters, sets actual time stamp and receives thread information </summary>
     * <param name="callerSourceFileName">    Name and path of the source code file the log call is
     *                                        placed in. </param>
     * <param name="callerLineNumber">        Line number within the source code file the log call is
     *                                        placed in. </param>
     * <param name="callerMemberName">        Name of the method the log call is placed in. </param>
     * <param name="threadDictionary">        Dictionary for translating thread IDs into more readable
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
                ThreadName.Append( threadName );
            else
            {
                if ( String.IsNullOrEmpty ( thread.Name ) )
                    ThreadName.Append( ThreadID );
                else
                    ThreadName.Append( thread.Name ).Append( '(' ).Append( ThreadID ).Append( ')' );
            }
        }
        #endif
    }

} // class CallerInfo

#endif // ALOX_DEBUG || ALOX_REL_LOG ,started before class CallerInfo


} // namespace
