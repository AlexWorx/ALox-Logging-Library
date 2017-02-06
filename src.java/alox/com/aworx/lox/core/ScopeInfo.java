// ##############int###################################################################################
//  com.aworx.lox.core - ALox Logging Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
package com.aworx.lox.core;


import java.util.HashMap;
import java.util.Locale;
import java.util.Vector;

import com.aworx.lib.strings.AString;
import com.aworx.lib.time.Ticks;


/** ************************************************************************************************
 * Encapsulates information of the caller that can be collected. This is platform specific, in
 * this case, .NET 4.5. What we currently can get from the .NET compiler, is the source file
 * name of the calling code, the line number within the source file name and the name of the
 * method the call is placed. We do not get the class name of the object or even its instance.
 **************************************************************************************************/
public class ScopeInfo
{
    // #############################################################################################
    // protected fields
    // #############################################################################################

        /** The name of the Lox we are attached to */
        private   String                  loxName;

        /** A reference to list of prefixes of \e 'packages.classes.methods' maintained by our lox*/
        private   Vector<String>          omittablePackagePrefixes;

        /** A reference to thread dictionary maintained by our lox  */
        private   HashMap <Long, String>  threadDictionary;

        /** The thread that invoked the call. */
        private   Thread                  thread;

        /** Name and path of the source code file the log call is placed in. */
        private   AString                 threadName                  = new AString(32);

        /** Flag that indicates whether stack trace information was retrieved already (false) or not
         *  (true). */
        private   boolean                 lazyStackTrace              = true;

        /** Name and path of the source code file the log call is placed in. */
        private   AString                 packageName                 = new AString(32);

        /** Name of the method the log call is placed in. */
        private   AString                 className                   = new AString(32);

        /** Name of the method the log call is placed in. */
        private   AString                 methodName                  = new AString(32);

        /** Name  of the source code file the log call is placed in. */
        private   AString                 fileName                    = new AString(32);

        /** The line number within the source file where the log call is placed in. */
        private   int                     lineNumber;

    // #############################################################################################
    // public fields
    // #############################################################################################

        /** Time of the call represented by this instance. */
        public      Ticks                   timeStamp                   = new Ticks();

    // #############################################################################################
    // public interface
    // #############################################################################################

        /** ****************************************************************************************
         * Constructs a scope info.
         * @param name              The name of the Lox we belong to.
         *                          Will be converted to upper case.
         * @param threadDictionary  A dictionary to map thread IDs to user friendly names which is
         *                          managed outside of this class.
         * @param omittablePackagePrefixes A list of prefixes of package names that are ignored, when
         *                                 the calling method is identified from the top of the calling
         *                                 stack.
         ******************************************************************************************/
        public ScopeInfo( String name,  HashMap <Long, String> threadDictionary,
                          Vector<String> omittablePackagePrefixes                    )
        {
            this.loxName=                   name.toUpperCase( Locale.US );
            this.threadDictionary=          threadDictionary;
            this.omittablePackagePrefixes=  omittablePackagePrefixes;
        }

        /** ****************************************************************************************
         * Stores parameters and sets actual time stamp.
         * @param thread The thread executing a log statement. If \c null, it will be
         *               determined if needed.
         ******************************************************************************************/
        public void set( Thread thread )
        {
            timeStamp.set();

            this.thread= thread;
            threadName.clear();

            lazyStackTrace= true;
        }

        /** ****************************************************************************************
         * Releases latest scope information.
         ******************************************************************************************/
        public void release ()
        {
            lazyStackTrace= true;
        }

        /** ****************************************************************************************
         * Receives the name of the \b Lox we are belonging to (this is a 1:1 relationship).
         * @return The name of the \b Lox.
         ******************************************************************************************/
        public String getLoxName()
        {
            return loxName;
        }

        /** ****************************************************************************************
         * Receives the ID of the thread executing the scope.
         * @return The name of the thread.
         ******************************************************************************************/
        public Thread getThread()
        {
            if ( thread == null )
                thread= Thread.currentThread();

            return thread;
        }

        /** ****************************************************************************************
         * Receives the ID of the thread executing the scope.
         * @return The name of the thread.
         ******************************************************************************************/
        public long getThreadID()
        {
            return getThread().getId();
        }

        /** ****************************************************************************************
         * Receives the name of the thread executing the scope. If a mapping exists, the mapped
         * name is returned
         * @return The name of the thread.
         ******************************************************************************************/
        public AString getThreadName()
        {
            if ( threadName.isEmpty() )
            {
                // do we have a dictionary entry?
                String name= threadDictionary.size() > 0 ? threadDictionary.get( new Long( getThreadID() ) )
                                                         : null;
                if( name != null )
                    threadName._( name );
                else
                {
                    threadName._( getThread().getName() );
                }
            }
            return threadName;
        }

        /** Receives the callees package name.
         *  @return The callees package name.*/
        public AString  getPackageName()    { updateStackTrace();   return packageName;  }

        /** Receives the callees method name.
         *  @return The callees method name.*/
        public AString  getMethodName()     { updateStackTrace();   return methodName;  }

        /** Receives the callees file name.
         *  @return The callees file name.*/
        public AString  getFileName()       { updateStackTrace();   return fileName;  }

        /** Receives the callees class name.
         *  @return The callees class name.*/
        public AString  getClassName()      { updateStackTrace();   return className;  }

        /** Receives the callees line number.
         *  @return The callees line number.*/
        public int      getLineNumber()     { updateStackTrace();   return lineNumber;  }



    // #############################################################################################
    // internals
    // #############################################################################################
        /** ****************************************************************************************
         * Retrieves the scope information from a stack trace when field #lazyStackTrace is true.
         ******************************************************************************************/
        private void updateStackTrace ()
        {
            if( !lazyStackTrace )
                return;
            lazyStackTrace= false;

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
                    methodName .clear()._  ( te.getMethodName() );
                    fileName   .clear()._  ( te.getFileName() );
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
