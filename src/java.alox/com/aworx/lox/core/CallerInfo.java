// #################################################################################################
//  com.aworx.lox.core - ALox Logging Library
//
//  (c) 2013-2015 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
package com.aworx.lox.core;


import java.util.HashMap;

import com.aworx.util.AString;
import com.aworx.util.Ticks;


/** ************************************************************************************************
 * Encapsulates information of the caller that can be collected. This is platform specific, in
 * this case, .NET 4.5. What we currently can get from the .NET compiler, is the source file
 * name of the calling code, the line number within the source file name and the name of the
 * method the call is placed. We do not get the class name of the object or even its instance.
 **************************************************************************************************/
public class CallerInfo
{
    // #############################################################################################
    // Public fields / Properties
    // #############################################################################################

    /** Time of the call represented by this instance. */
    public    Ticks                 timeStamp                   = new Ticks();

    /**    Name and path of the source code file the log call is placed in. */
    public    AString               packageName                 = new AString(32);

    /**    Name of the method the log call is placed in. */
    public    AString               className                   = new AString(32);

    /**    Name of the method the log call is placed in. */
    public    AString               methodName                  = new AString(32);

    /**    Name and path of the source code file the log call is placed in. */
    public    AString               fileName                    = new AString(32);

    /**    The line number within the source file where the log call is placed in. */
    public    int                   lineNumber;

    /** The thread that invoked the call. */
    public    Thread                thread;

    /** Name and path of the source code file the log call is placed in. */
    public    AString               threadName                  = new AString(32);

    /** Name and path of the source code file the log call is placed in. */
    public    long                  threadID;

    // #############################################################################################
    // public interface
    // #############################################################################################

    /** ********************************************************************************************
     * Stores parameters and sets actual time stamp.
     *
     * @param threadDictionary          Dictionary for translating thread IDs into more readable
     *                                 thread names.
     * @param skipablePackagePrefix Portion of the source code name that is removable (not to be logged).
     **********************************************************************************************/
    public void set (HashMap <Long, String>    threadDictionary, String skipablePackagePrefix  )
    {
        // 1) ----  first, we set the time stamp (as early as possible) ----
        timeStamp.set();

        // 2) ----  get current thread  ----
        thread=        Thread.currentThread();
        threadID=    thread.getId();

        // do we have a dictionary entry?
        threadName.clear();
        String name= threadDictionary.get( threadID );
        if( name != null )
            threadName.append( name );
        else
        {
            // no, does the thread have a name?
            threadName.append( thread.getName() ).append( '(' );
            if ( threadID > Integer.MAX_VALUE)
                threadName.append( AString.empty + threadID  );
            else
                threadName.append( (int) threadID );
            threadName.append( ')' );
        }

        // 3) ----  get caller info ----
        {
            // get StackTrace from a new Exception (this is how Thread does it internally)
            StackTraceElement[]  stElems=      (new Exception()).getStackTrace();
            int                  stackLen=     stElems.length;
            String               teClassName;
            StackTraceElement    te;
            int i= (stackLen - 1 > 3) ? 3 : stackLen - 1;    // we skip 3 levels anyhow
            while (true )
            {
                te= stElems[i];
                teClassName= te.getClassName();
                if ( !teClassName.startsWith( skipablePackagePrefix ) )
                    break;

                // next
                if (++i == stackLen )
                {
                    packageName.clear().append("(#err pkg)");
                    className  .clear().append("(#err class)");
                    methodName .clear().append("(#err method)");
                    fileName   .clear().append("(#err filename)");
                    lineNumber= 0;
                    return;
                }
            }

            // find last dot
            int dotPos= teClassName.lastIndexOf( '.' );

            // write names
            packageName.clear().append( teClassName, 0,           dotPos      );
            className  .clear().append( teClassName, dotPos + 1, 10000        );
            methodName .clear().append( te.getMethodName() );
            fileName   .clear().append( te.getFileName() );
            lineNumber= te.getLineNumber();
        }
    }
}
