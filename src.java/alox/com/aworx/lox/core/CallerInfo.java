// ##############int###################################################################################
//  com.aworx.lox.core - ALox Logging Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
package com.aworx.lox.core;


import java.util.HashMap;
import java.util.Vector;

import com.aworx.lib.strings.AString;
import com.aworx.lib.time.Ticks;


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
     * @param threadDictionary        Dictionary for translating thread IDs into more readable
     *                                thread names.
     * @param omittablePackagePrefixes A list of prefixes of package names that are ignored, when
     *                                 the calling method is identified from the top of the calling
     *                                 stack. 
     **********************************************************************************************/
    public void set (HashMap <Long, String>    threadDictionary, Vector<String> omittablePackagePrefixes  )
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
            threadName._( name );
        else
        {
            // no, does the thread have a name?
            threadName._( thread.getName() );
            //threadName.append( '(' ).append( threadID  ).append( ')' );
        }

        // 3) ----  get caller info ----
        {
            packageName._();
            className  ._();
            methodName ._();
            fileName   ._();
            lineNumber= -1;        
        
            // get StackTrace from a new Exception (this is how Thread does it internally)
            StackTraceElement[]  stElems=      (new Exception()).getStackTrace();
            int                  stackLen=     stElems.length;
            String               teClassName;
            StackTraceElement    te;
            for( int i= 2 ; i < stackLen ; i++ ) // we skip 2 levels anyhow
            {
                te= stElems[i];
                teClassName= te.getClassName();
                boolean found= true;
                for (int idx= 0; idx< omittablePackagePrefixes.size(); idx++)
                    if ( teClassName.startsWith( omittablePackagePrefixes.elementAt( idx ) ) )
                    {
                        found= false;
                        break;
                    }
                if( found )
                {
                    // find last dot
                    int dotPos= teClassName.lastIndexOf( '.' );
                    if ( dotPos < 0 )
                        dotPos= 0;
                        
                    // write names
                    packageName.clear()._NC( teClassName, 0,           dotPos      );
                    dotPos++;
                    className  .clear()._NC( teClassName, dotPos, teClassName.length() - dotPos  );
                    methodName .clear()._   ( te.getMethodName() );
                    fileName   .clear()._   ( te.getFileName() );
                    lineNumber= te.getLineNumber();
                
                    return;
                }
            }

            // not found
            packageName._("(#err pkg)");
            className  ._("(#err class)");
            methodName ._("(#err method)");
            fileName   ._("(#err filename)");
            lineNumber= 0;
        }
    }
}
