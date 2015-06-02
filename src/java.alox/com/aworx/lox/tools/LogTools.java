// #################################################################################################
//  com.aworx.lox.tools - ALox Logging Library
//
//  (c) 2013-2015 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
package com.aworx.lox.tools;

import java.io.ByteArrayOutputStream;
import java.io.PrintStream;
import java.lang.reflect.Array;
import java.lang.reflect.Field;
import java.lang.reflect.Modifier;
import java.util.HashMap;
import java.util.Iterator;

import com.aworx.lox.Log;
import com.aworx.lox.Lox;
import com.aworx.util.AString;
import com.aworx.util.ThreadLock;


/** ************************************************************************************************
 *    Provides high level functionality for logging things like Exceptions or object instances.
 **************************************************************************************************/
public abstract class LogTools
{
    // #############################################################################################
    // ### String_Constants
    // #############################################################################################

        /** The String to log out if the exception parameter equals null */
        public static    String            fmtExcNull                    = "<No exception given>";

        /** The String to log out prior to an exception stack trace */
        public static    String            fmtExcStackTraceHeader        = "Exception stack trace:";

        /** Prefix for instance line numbers */
        public static    String            fmtInstLineNoPrefix           = "<";

        /** Postfix for instance line numbers */
        public static    String            fmtInstLineNoPostfix          = ">";

        /** The String to log out if a given object instance equals null */
        public static    String            fmtInstNull                    = "<null>";

        /** Prefix before logging out a string representation of a member because recursion limit was reached.  */
        public static    String            fmtInstRecursionLimit         = "(MAX REC) ";

        /** Prefix before logging out a cyclic reference line number. */
        public static    String            fmtInstCycRefPrefix           = "(Cyclic ref., see line <";

        /**  Prefix before logging size of an IEnumberable. */
        public static    String            fmtInstIterablePrefix         = "Iterable, size= ";

        /**  Postfix after logging IEnumberable. */
        public static    String            fmtInstIterablePostfix        = "";

        /**  Prefix before logging size of an IEnumberable. */
        public static    String            fmtInstArrayPrefix            = "array[";

        /**  Postfix after logging IEnumberable. */
        public static    String            fmtInstArrayPostfix           = "]";


        /** Postfix after logging out a cyclic reference line number. */
        public static    String            fmtInstCycRefPostfix          = ">)";

        /** Indent String for instance lines */
        public static    String            FmtInstNoAccessToValue        = "<no access>" ;

        /** Prefix for type names */
        public static    String            fmtInstTypePrefix            = "{";

        /** Postfix for type names */
        public static    String            fmtInstTypePostfix            = "}";

        /** Indent String for instance lines */
        public static    String            fmtInstIndent                = "  ";

        // #############################################################################################
        // Public fields
        // #############################################################################################

        /** Tab stop for values when logging instances. */
        public    static        int            instValueTabStop         = 35;

        /** Tab stop for types when logging instances. */
        public    static        int            instTypeTabStop          = 65;

        // #############################################################################################
        // Private/protected fields
        // #############################################################################################

        /**Buffer to build log messages. */
        protected    static        AString                        toolBuf;

        /** Internal buffer for temporary operations */
        protected    static        AString                        tempBuf                    = new AString(512);

        /** Pointer to start of current line in tempBuf, used by nextTempBufLine */
        protected    static        int                            tempLineStartIdx;

        /** Pointer to end of current line in tempBuf, used by nextTempBufLine */
        protected    static        int                            tempLineEndIdx;

        /**Instance line number counter. */
        protected    static        int                            instLineNumber;

        /**Instance line number dictionary used to refer to already logged sub objects. */
        protected    static        HashMap<Object, Integer>       instObject2LineNumber;

        /**Instance index of beginning of line in toolBuf. */
        protected    static        int                            instLineBeginIdx;

        /**
         *  This is the ThreadLock (mutex) which each method of this class uses to lock resources, e.g.
         *  the toolBuf
         */
        protected    static        ThreadLock                     lock                    = new ThreadLock();

        /** Used for logging exceptions. */
        protected    static        ByteArrayOutputStream          exceptionBAOS;

        /** Used for logging exceptions. */
        protected    static        PrintStream                    exceptionPS             = new PrintStream(exceptionBAOS= new ByteArrayOutputStream(8192));

        // #############################################################################################
        // Public static interface (not accessible in release code)
        // #############################################################################################


    /** ********************************************************************************************
     *  Log an exception including inner exceptions recursively.
     *
     * @param domain      The log domain name.
     * @param level       The log level.
     * @param e           The Exception to log.
     * @param headline    (Optional) A headline string preceding the exception output.
     * @param indent      (Optional) the indentation in the output (recursively increased). Defaults to 0.
     * @param lox         (Optional) The Lox to log with. If null, the static member LOX of class Log is used.
     **********************************************************************************************/
    public static void exception( String domain, Log.Level level, Exception e, String headline, int indent, Lox lox)
    {
        try { lock.acquire();

            // create/clear toolBuf
            if ( toolBuf == null )
                toolBuf= new AString( 1024 );
            toolBuf.clear();

            // dump exception to the Buffer
            exc ( e, headline, -1 );

            // if no lox given, use static Log.LOX
            if ( lox == null )
                lox= Log.LOX;

            // log it using the static Log interface
            lox.line ( true, domain, level, toolBuf, indent, null );

        } finally { lock.release(); }
    }

    /** ********************************************************************************************
     *  Log an exception including inner exceptions recursively.
     *
     * @param domain      The log domain name.
     * @param level       The log level.
     * @param e           The Exception to log.
     * @param headline    (Optional) A headline string preceding the exception output.
     * @param indent      (Optional) the indentation in the output (recursively increased). Defaults to 0.
     **********************************************************************************************/
    public static void exception( String domain, Log.Level level, Exception e, String headline, int indent ){ exception( domain,  level, e, headline,     indent, null ); }
    /** ********************************************************************************************
     *  Log an exception including inner exceptions recursively.
     *
     * @param domain      The log domain name.
     * @param level       The log level.
     * @param e           The Exception to log.
     * @param headline    (Optional) A headline string preceding the exception output.
     **********************************************************************************************/
    public static void exception( String domain, Log.Level level, Exception e, String headline )            { exception( domain,  level, e, headline,     0,        null ); }
    /** ********************************************************************************************
     *  Log an exception including inner exceptions recursively.
     *
     * @param domain      The log domain name.
     * @param level       The log level.
     * @param e           The Exception to log.
     **********************************************************************************************/
    public static void exception( String domain, Log.Level level, Exception e )                                { exception( domain,  level, e, null,         0,        null ); }
    /** ********************************************************************************************
     *  Log an exception including inner exceptions recursively.
     *
     * @param level       The log level.
     * @param e           The Exception to log.
     * @param headline    (Optional) A headline string preceding the exception output.
     * @param indent      (Optional) the indentation in the output (recursively increased). Defaults to 0.
     * @param lox         (Optional) The Lox to log with. If null, the static member LOX of class Log is used.
     **********************************************************************************************/
    public static void exception(                  Log.Level level, Exception e, String headline, int indent, Lox lox){ exception( null,    level, e, headline,     indent, lox ); }
    /** ********************************************************************************************
     *  Log an exception including inner exceptions recursively.
     *
     * @param level       The log level.
     * @param e           The Exception to log.
     * @param headline    (Optional) A headline string preceding the exception output.
     * @param indent      (Optional) the indentation in the output (recursively increased). Defaults to 0.
     **********************************************************************************************/
    public static void exception(                  Log.Level level, Exception e, String headline, int indent )        { exception( null,    level, e, headline,     indent, null ); }
    /** ********************************************************************************************
     *  Log an exception including inner exceptions recursively.
     *
     * @param level       The log level.
     * @param e           The Exception to log.
     * @param headline    (Optional) A headline string preceding the exception output.
     **********************************************************************************************/
    public static void exception(                  Log.Level level, Exception e, String headline )                    { exception( null,    level, e, headline,     0,        null ); }
    /** ********************************************************************************************
     *  Log an exception including inner exceptions recursively.
     *
     * @param level       The log level.
     * @param e           The Exception to log.
     **********************************************************************************************/
    public static void exception(                  Log.Level level, Exception e )                                        { exception( null,      level, e, null,         0,        null ); }
    /** ********************************************************************************************
     *  Log an exception including inner exceptions recursively.
     *
     * @param e           The Exception to log.
     * @param headline    (Optional) A headline string preceding the exception output.
     * @param indent      (Optional) the indentation in the output (recursively increased). Defaults to 0.
     * @param lox         (Optional) The Lox to log with. If null, the static member LOX of class Log is used.
     **********************************************************************************************/
    public static void exception(                                    Exception e, String headline, int indent, Lox lox){ exception( null,    Log.Level.ERROR, e, headline,     indent, lox ); }
    /** ********************************************************************************************
     *  Log an exception including inner exceptions recursively.
     *
     * @param e           The Exception to log.
     * @param headline    (Optional) A headline string preceding the exception output.
     * @param indent      (Optional) the indentation in the output (recursively increased). Defaults to 0.
     **********************************************************************************************/
    public static void exception(                                    Exception e, String headline, int indent )        { exception( null,    Log.Level.ERROR, e, headline,     indent, null ); }
    /** ********************************************************************************************
     *  Log an exception including inner exceptions recursively.
     *
     * @param e           The Exception to log.
     * @param headline    (Optional) A headline string preceding the exception output.
     **********************************************************************************************/
    public static void exception(                                    Exception e, String headline )                    { exception( null,    Log.Level.ERROR, e, headline,     0,        null ); }
    /** ********************************************************************************************
     *  Log an exception including inner exceptions recursively.
     *
     * @param e           The Exception to log.
     **********************************************************************************************/
    public static void exception(                                    Exception e )                                        { exception( null,      Log.Level.ERROR, e, null,         0,        null ); }

    /** ********************************************************************************************
     *  Log the current stack trace.
     *
     * @param domain      The log domain name.
     * @param level       The log level.
     * @param headline    (Optional) A headline string preceding the stacktrace output.
     * @param indent      (Optional) the indentation of the output. Defaults to 0.
     * @param lox         (Optional) The Lox to log with. If null, the static member LOX of class Log is used.
     **********************************************************************************************/
    public static void stackTrace( String domain, Log.Level level, String headline, int indent, Lox lox)
    {
        try { lock.acquire();

            // create/clear toolBuf
            if ( toolBuf == null )
                toolBuf= new AString( 1024 );
            toolBuf.clear();

            // dump exception to the Buffer
            {
                // headline
                if ( headline != null )
                    toolBuf.append( headline ).newLine();

                // print stack trace into tempBuf
                (new Exception()).printStackTrace( exceptionPS );
                tempBuf.clear().append( exceptionBAOS.toString() );
                exceptionBAOS.reset();

                // loop over lines in temp buf
                tempLineEndIdx= 0;
                while ( true )
                {
                    // next line
                    nextTempBufLine();
                    if ( tempLineStartIdx == tempLineEndIdx )
                        break;

                    // append line
                    if( tempBuf.containsAt( "\tat ", tempLineStartIdx ) )
                        toolBuf.append( ' ',  2 ).append( tempBuf, tempLineStartIdx + 4, tempLineEndIdx  - tempLineStartIdx - 4).newLine();
                }
            }

            // if no lox given, use static Log.LOX
            if ( lox == null )
                lox= Log.LOX;

            // log it using the static Log interface
            lox.line ( true, domain, level, toolBuf, indent, null );

        } finally { lock.release(); }
    }

    /** ********************************************************************************************
     *  Log the current stack trace.
     *
     * @param domain      The log domain name.
     * @param level       The log level.
     * @param headline    (Optional) A headline string preceding the stacktrace output.
     * @param indent      (Optional) the indentation of the output. Defaults to 0.
     **********************************************************************************************/
    public static void stackTrace( String domain, Log.Level level, String headline, int indent ){ stackTrace( domain,    level, headline,     indent, null ); }
    /** ********************************************************************************************
     *  Log the current stack trace.
     *
     * @param domain      The log domain name.
     * @param level       The log level.
     * @param headline    (Optional) A headline string preceding the stacktrace output.
     **********************************************************************************************/
    public static void stackTrace( String domain, Log.Level level, String headline )            { stackTrace( domain,    level, headline,     0,        null ); }
    /** ********************************************************************************************
     *  Log the current stack trace.
     *
     * @param domain      The log domain name.
     * @param level       The log level.
     **********************************************************************************************/
    public static void stackTrace( String domain, Log.Level level )                                { stackTrace( domain,    level, null,         0,        null ); }
    /** ********************************************************************************************
     *  Log the current stack trace.
     *
     * @param level       The log level.
     * @param headline    (Optional) A headline string preceding the stacktrace output.
     * @param indent      (Optional) the indentation of the output. Defaults to 0.
     **********************************************************************************************/
    public static void stackTrace(                   Log.Level level, String headline, int indent ){ stackTrace( null,        level, headline,     indent, null ); }
    /** ********************************************************************************************
     *  Log the current stack trace.
     *
     * @param level       The log level.
     * @param headline    (Optional) A headline string preceding the stacktrace output.
     **********************************************************************************************/
    public static void stackTrace(                   Log.Level level, String headline )            { stackTrace( null,        level, headline,     0,        null ); }
    /** ********************************************************************************************
     *  Log the current stack trace.
     *
     * @param level       The log level.
     **********************************************************************************************/
    public static void stackTrace(                   Log.Level level )                                { stackTrace( null,        level, null,         0,        null ); }


    /** ********************************************************************************************
     *     Recursively logs objects using reflection.
     * @param domain       The log domain name.
     * @param level        The log level.
     * @param o            The object to be logged.
     * @param maxRecursion The maximum depth of recursion for logging nested object.
     * @param headline     (Optional) A headline string to precede the exception with.
     * @param indent       (Optional) The indentation in the output (recursively increased).
     *                     Defaults to 0.
     * @param lox          (Optional) The lox to log with. If null, the static member LOX of
     *                     the static class Log is used.
     **********************************************************************************************/
    public static void instance( String domain, Log.Level level, Object o, int maxRecursion, String headline, int indent, Lox lox)

    {
        try { lock.acquire();

            // if no lox given, use static Log.LOX
            if ( lox == null )
                lox= Log.LOX;

                // dump exception to the Buffer
                instMain( o, maxRecursion, headline );

                // log it using the static Log interface
                lox.line ( true, domain, level, toolBuf, indent, null );


        } finally { lock.release(); }
    }

    /** ********************************************************************************************
     *     Recursively logs objects using reflection.
     * @param domain          The log domain name.
     * @param level           The log level.
     * @param o               The object to be logged.
     * @param maxRecursion    The maximum depth of recursion for logging nested object.
     * @param headline        (Optional) A headline string to precede the exception with.
     * @param indent          (Optional) The indentation in the output (recursively increased). Defaults to 0.
     **********************************************************************************************/
    public static void instance( String domain, Log.Level level, Object o, int maxRecursion, String headline, int indent )    { instance( domain,    level, o, maxRecursion, headline,     indent, null ); }
    /** ********************************************************************************************
     *     Recursively logs objects using reflection.
     * @param domain          The log domain name.
     * @param level           The log level.
     * @param o               The object to be logged.
     * @param maxRecursion    The maximum depth of recursion for logging nested object.
     * @param headline        (Optional) A headline string to precede the exception with.
     **********************************************************************************************/
    public static void instance( String domain, Log.Level level, Object o, int maxRecursion, String headline )                { instance( domain,    level, o, maxRecursion, headline,     0,        null ); }
    /** ********************************************************************************************
     *     Recursively logs objects using reflection.
     * @param domain          The log domain name.
     * @param level           The log level.
     * @param o               The object to be logged.
     * @param maxRecursion    The maximum depth of recursion for logging nested object.
     **********************************************************************************************/
    public static void instance( String domain, Log.Level level, Object o, int maxRecursion )                                { instance( domain,    level, o, maxRecursion, null,         0,        null ); }

    /** ********************************************************************************************
     *     Recursively logs objects using reflection.
     * @param level           The log level.
     * @param o               The object to be logged.
     * @param maxRecursion    The maximum depth of recursion for logging nested object.
     * @param headline        (Optional) A headline string to precede the exception with.
     * @param indent          (Optional) The indentation in the output (recursively increased). Defaults to 0.
     * @param lox             (Optional) The lox to log with. If null, the static member LOX of
     *                        the static class Log is used.
     **********************************************************************************************/
    public static void instance(                 Log.Level level, Object o, int maxRecursion, String headline, int indent, Lox lox )    { instance( null,    level, o, maxRecursion, headline,     indent, lox ); }
    /** ********************************************************************************************
     *     Recursively logs objects using reflection.
     * @param level           The log level.
     * @param o               The object to be logged.
     * @param maxRecursion    The maximum depth of recursion for logging nested object.
     * @param headline        (Optional) A headline string to precede the exception with.
     * @param indent          (Optional) The indentation in the output (recursively increased). Defaults to 0.
     **********************************************************************************************/
    public static void instance(                 Log.Level level, Object o, int maxRecursion, String headline, int indent )            { instance( null,    level, o, maxRecursion, headline,     indent, null ); }
    /** ********************************************************************************************
     *     Recursively logs objects using reflection.
     * @param level           The log level.
     * @param o               The object to be logged.
     * @param maxRecursion    The maximum depth of recursion for logging nested object.
     * @param headline        (Optional) A headline string to precede the exception with.
     **********************************************************************************************/
    public static void instance(                 Log.Level level, Object o, int maxRecursion, String headline )                        { instance( null,    level, o, maxRecursion, headline,     0,        null ); }
    /** ********************************************************************************************
     *     Recursively logs objects using reflection.
     * @param level           The log level.
     * @param o               The object to be logged.
     * @param maxRecursion    The maximum depth of recursion for logging nested object.
     **********************************************************************************************/
    public static void instance(                 Log.Level level, Object o, int maxRecursion )                                        { instance( null,    level, o, maxRecursion, null,         0,        null ); }


//    #if  !ALOX_NO_XML
//        / ** ***********************************************************************************************
//         *
//         *  Log a xml document.
//         *
//         * @param domain    The log domain name.
//         * @param level     The log level.
//         * @param xDocument the xml document to be logged.
//         * @param headLine  (Optional) The headline to log.
//         * @param indent    (Optional) the indentation in the output (recursively increased).
//         *                  Defaults to 0.
//         * @param lox       (Optional) The lox to log with. If null, the static member LOX of
//         *                  the static class Log is used.
//         ******************************************************************************************/
//        public static void XML(    String        domain,            Log.Level    level,
//                                XDocument    xDocument,        String        headLine=    null,
//                                int            indent=      0,     Lox            lox=        null)
//        {
//            try { Lock.acquire();
//
//                // dump exception to the Buffer
//                xml( xDocument, headLine );
//
//                // if no lox given, use static Log.LOX
//                if ( lox == null )
//                    lox= Log.LOX;
//
//                // log it using the static Log interface
//                lox.Line ( true, domain, level, toolBuf, indent, null, csf, cln, cmn );
//
//
//            } finally { Lock.release(); }
//        }
//
//        / ** ***********************************************************************************************
//         *
//         *  Log a xml document.
//         *
//         * @param level     The log level.
//         * @param xDocument the xml document to be logged.
//         * @param headLine  The headline to log.
//         * @param indent    (Optional) the indentation in the output (recursively increased).
//         *                  Defaults to 0.
//         * @param lox       (Optional) The lox to log with. If null, the static member LOX of
//         *                  the static class Log is used.
//         ******************************************************************************************/
//        public static void XML(    Log.Level        level,
//                                XDocument        xDocument,    String    headLine,
//                                int                indent=    0,     Lox        lox= null)
//        {
//            XML( null, level, xDocument, headLine, indent, lox, csf, cln, cmn );
//        }
//
//        / ** ***********************************************************************************************
//         *
//         *  Log a xml element.
//         *
//         * @param domain    The log domain name. If not starting with a slash ('/')
//         *                  this is appended to any default domain name that might have been
//         *                  specified for the source file.
//         * @param level     The log level.
//         * @param xElement  the answer node of the xml tree to be logged.
//         * @param headLine  (Optional) The headline to log.
//         * @param indent    (Optional) the indentation in the output (recursively increased).
//         *                  Defaults to 0.
//         * @param lox       (Optional) The lox to log with. If null, the static member LOX of
//         *                  the static class Log is used.
//         ******************************************************************************************/
//        public static void XML(    String            domain,        Log.Level    level,
//                                XElement        xElement,    String        headLine=    null,
//                                int                indent=     0, Lox            lox= null )
//        {
//            try { Lock.acquire();
//
//                // create/clear toolBuf
//                if ( toolBuf == null )
//                    toolBuf= new AString( 1024 );
//                else
//                    toolBuf.clear();
//
//                // dump exception to the Buffer
//                xmlElement( xElement, headLine, 0 );
//
//                // if no lox given, use static Log.LOX
//                if ( lox == null )
//                    lox= Log.LOX;
//
//                // log it using the static Log interface
//                lox.Line ( true, domain, level, toolBuf, indent, null, csf, cln, cmn );
//
//
//            } finally { Lock.release(); }
//        }
//
//        / ** ***********************************************************************************************
//         *
//         *  Log a xml element.
//         *
//         * @param level       The log level.
//         * @param xElement    the answer node of the xml tree to be logged.
//         * @param headLine    The head line.
//         * @param indent      (Optional) the indentation in the output (recursively increased).
//         *                             Defaults to 0.
//         * @param lox          (Optional) The lox to log with. If null, the static member LOX of
//         *                             the static class Log is used.
//         ******************************************************************************************/
//        public static void XML(    Log.Level    level,
//                                XElement    xElement,    String        headLine,
//                                int            indent=    0,     Lox            lox= null )
//        {
//            XML( null, level, xElement, headLine, indent, lox, csf, cln, cmn );
//        }
//
//    #endif // ALOX_NO_XML
//

    // #############################################################################################
    // internals
    // #############################################################################################

    /** ********************************************************************************************
     *     Logs an exception.
     * @param e         The exception to be logged.
     * @param headline  A headline string to precede the exception with.
     * @param indent    The indentation in the output (recursively increased). If set to -1
     *                  the 'headline' is logged.
     **********************************************************************************************/
    protected static void exc( Throwable e, String headline, int indent )
    {
        // log headline if answer exception
        if ( indent == -1 )
        {
            indent= 0;
            if ( headline != null )
                toolBuf.append( headline ).newLine();
        }

        // increase tab level
        indent++;

        // Assert
        if ( e == null )
        {
            toolBuf.append( ' ',  indent * 2 ).append( fmtExcNull );
            return;
        }

        // log exception details
        toolBuf.append( ' ',  indent * 2 ).append( "Type:       ").append(e.getClass().getName()                ).newLine();
        toolBuf.append( ' ',  indent * 2 ).append( "Message:    ").append(e.getMessage()                        ).newLine();

        // recursion
        if ( e.getCause() != null )
        {
            toolBuf.append( ' ',  indent * 2 ).append( "Cause:   " ).newLine();
            exc( e.getCause() , null, indent );
        }

        // print stack trace, but only on indent level 0
        if ( indent == 1 )
        {
            // log stack trace header msg
            toolBuf.append( ' ',  2 ).append( fmtExcStackTraceHeader ).newLine();

            // print stack trace into tempBuf
            e.printStackTrace( exceptionPS );
            tempBuf.clear().append( exceptionBAOS.toString() );
            exceptionBAOS.reset();

            // loop over lines in temp buf
            tempLineEndIdx= 0;
            while ( true )
            {
                // next line
                nextTempBufLine();
                if ( tempLineStartIdx == tempLineEndIdx )
                    break;

                // append line
                if( tempBuf.containsAt( "\tat ", tempLineStartIdx ) )
                    toolBuf.append( ' ',  4 ).append( tempBuf, tempLineStartIdx + 4, tempLineEndIdx  - tempLineStartIdx - 4).newLine();
            }
        }

    }

    /** ********************************************************************************************
     *  Finds the next line in #tempBuf and stores start and end index in #tempLineStartIdx and
     *  #tempLineEndIdx.
     **********************************************************************************************/
    protected static void nextTempBufLine()
    {
        char c;
        char[] buf=        tempBuf.buffer();
        int exLength=    tempBuf.length();

        // skip end of line characters
        int start= tempLineEndIdx;
        while( start < exLength && ( (c= buf[start])=='\r' || c=='\n' ) )
            start++;

        // find end of line
        int end= start + 1;
        while( end < exLength &&  (c= buf[end]) != '\r'  &&  c != '\n')
            end++;

        // end of buf? return empty string
        if ( end - start <= 1  )
            start= end;

        // store return values in fields
        tempLineStartIdx=    start;
        tempLineEndIdx=        end;
    }


    /** ********************************************************************************************
     *  Logs the header and invokes instRecursive().
     *
     * @param o             The object to be logged.
     * @param maxRecursion  The maximum depth of recursion for logging nested object.
     * @param headLine      The headline to log.
     **********************************************************************************************/
    protected static void instMain( Object o, int maxRecursion, String headLine)
    {
        // prepare fields
        if ( toolBuf == null )        toolBuf= new AString( 1024 );
        else                        toolBuf.clear();

        instLineNumber=            0;
        instLineBeginIdx=        0;
        instObject2LineNumber=  new HashMap<Object, Integer>();

        // log headline if answer exception
        if ( headLine != null )
            toolBuf.append( headLine ).append(' ');

        // dump the object
        instRecursive( o, maxRecursion, headLine != null ? 1 : 0  );

        // dispose the dictionary
        instObject2LineNumber= null;
    }


    /** ********************************************************************************************
     *     Recursively log an instance using reflection.
     * @param inst         The element.
     * @param maxRecursion The maximum depth of recursion for logging nested object.
     * @param indent       The indentation in the output (recursively increased).
     **********************************************************************************************/
    @SuppressWarnings ("null") protected static void instRecursive( Object inst, int maxRecursion, int indent )
    {
        // get type
        @SuppressWarnings ("rawtypes")
        Class type= inst!= null     ? inst.getClass()
                                    : null;

        //### 1.  Detect and log value types (or null or sting) ###
        {
            boolean isValueType= false;

            // check for null
            if ( inst == null )
            {
                toolBuf.append( fmtInstNull );
                isValueType= true;
            }

            // string?
            else if ( inst instanceof String )
            {
                // add value and type, that's it
                toolBuf    .append( '\"' ).append( (String) inst ).append( '\"' );
                isValueType= true;
            }

            // Char[]
            else if ( inst instanceof char[] )
            {
                char[] charArrayVal= (char[]) inst;
                String val;

                val= charArrayVal.length > 100    ? new String ( charArrayVal, 0, 100) + "..."
                                                : new String (charArrayVal );
                val= val.replace((char) 0, ' ' );

                // add value and type, that's it
                toolBuf    .append( '\"' ).append( val ).append( '\"' );

                isValueType= true;
            }

            // java.lang wrapper type?
            else if ( isWrapperType( inst ) )
            {
                String val= inst.toString();
                if ( val.length() == 1 && val.charAt(0)==(char) 0 )
                    val= "\\0";
                else
                    val= val.replace((char) 0, ' ' );

                // add value and type, that's it
                toolBuf    .append( val );

                isValueType= true;
            }

            // if it was a value type, log type, finish line and return true
            if ( isValueType )
            {
                instTabTypeAndNewLine( type );
                return;
            }
        }

        // ### maximum recursion? ###
        if ( maxRecursion == 0 )
        {
            @SuppressWarnings ("null") String vString=    inst.toString();
            @SuppressWarnings ("null") String tString=    type.getName();

            // often, toString() just returns the type or prepends the type
            if ( vString.startsWith( tString) )
                vString= vString.substring( tString.length() );

            // append "(max rec.)" + value
            toolBuf.append( fmtInstRecursionLimit ).append( vString );
            instTabTypeAndNewLine( type );

            return;
        }

        // ### cyclic reference? ###
        Integer lineNumber= instObject2LineNumber.get( inst );
        if ( lineNumber != null )
        {
            toolBuf    .append( fmtInstCycRefPrefix )
                    .append( lineNumber.intValue(), 2 )
                    .append( fmtInstCycRefPostfix );
            instTabTypeAndNewLine( inst.getClass() );
            return;
        }
        // mark object as being logged
        instObject2LineNumber.put( inst, instLineNumber );

        // ### Arrays ###
        if ( type.isArray() )
        {
            // get array length from fields"length()"
            int qtyObjects= Array.getLength( inst );

            toolBuf.append( fmtInstArrayPrefix ).append( qtyObjects ).append( fmtInstArrayPostfix );
            instTabTypeAndNewLine( type );

            // loop over all objects
            for ( int itemNo= 0; itemNo < qtyObjects ; itemNo++ )
            {
                instBeginLine( indent );
                toolBuf.append( itemNo, 1 ).append(": ");

                // get item
                Object item= Array.get( inst, itemNo );

                // log element
                instRecursive( item, maxRecursion - 1, indent + 1 );
            }
        }


        // ###  Iterables ###
        else if ( inst instanceof Iterable )
        {
            @SuppressWarnings ("rawtypes")
            Iterable it= (Iterable) inst;

            // get object count
            int qtyObjects= 0;
            @SuppressWarnings ("rawtypes")
            Iterator i= it.iterator();
            while( i.hasNext() )
            {
                qtyObjects++;
                i.next();
            }

            // log headline and start new line
            toolBuf.append( fmtInstIterablePrefix ).append( qtyObjects ).append( fmtInstIterablePostfix );
            instTabTypeAndNewLine( type );

            // loop over all objects
            int itemNo= 0;
            i= it.iterator();
            while( i.hasNext() )
            {
                instBeginLine( indent );
                toolBuf.append( itemNo++, 1 ).append(": ");
                instRecursive( i.next(), maxRecursion - 1, indent + 1 );
            }
        }


        // ### Classes ###
        else
        {
            // finish line of object
            instTabTypeAndNewLine( type );

            // loop over fields
            Field[] members= type.getDeclaredFields();

            for (int fNo= 0; fNo < members.length; fNo++)
            {
                // get actual field
                Field memberInfo= members[fNo];

                // check for const
                int modifiers= memberInfo.getModifiers();
                if( (modifiers & (Modifier.FINAL + Modifier.STATIC)) != 0 )
                    continue;

                // allow protected/private fields access
                memberInfo.setAccessible( true );

                Object value=    null;
                try { value= memberInfo.get( inst ); }    catch( Exception e)  {    value= FmtInstNoAccessToValue; }

                // begin line and log name
                instBeginLine( indent );
                toolBuf.append( memberInfo.getName() ).append(':');
                instTabStop( instValueTabStop );

                // recursively log value
                instRecursive( value, maxRecursion - 1, indent + 1 );
            }
        }
    }

    /** ********************************************************************************************
     * Tests if an object is a primitive wrapper type.
     * @param o The object to check
     * @return true, if object is a wrapper type
     **********************************************************************************************/
    protected static boolean isWrapperType( Object o )
    {
        return         o instanceof Boolean
                ||  o instanceof Character
                ||  o instanceof Byte
                ||  o instanceof Short
                ||  o instanceof Integer
                ||  o instanceof Long
                ||  o instanceof Float
                ||  o instanceof Double
                ||  o instanceof Void;
    }

    /** ********************************************************************************************
     *  Adds a new line to the buffer and increases line number counter.
     **********************************************************************************************/
    protected static void instNewLine()
    {
        instLineNumber++;
        toolBuf.newLine();
    }

    /** ********************************************************************************************
     *  Appends line number (format defined in fields #fmtInstLineNoPrefix and #fmtInstLineNoPostfix)
     *  and then adds indent characters (defined in field #fmtInstIndent).
     *
     * @param indent    The indentation of the line.
     **********************************************************************************************/
    protected static void instBeginLine( int indent )
    {
        instLineBeginIdx=toolBuf.length();
        toolBuf.append( fmtInstLineNoPrefix ).append( instLineNumber, 2 ).append( fmtInstLineNoPostfix );
        for ( int i= indent; i > 0; i-- )
            toolBuf.append( fmtInstIndent );
    }

    /** ********************************************************************************************
     *  Appends spaces to move to the given tabStop (but at least one).
     *
     * @param tabStop    The tab stop position to go to.
     **********************************************************************************************/
    protected static void instTabStop( int tabStop )
    {
        do    { toolBuf.append( ' ' ); } while ( toolBuf.length() <= instLineBeginIdx + tabStop  );
    }

    /** ********************************************************************************************
     *  Appends type information at the end of the line and starts a new line.
     *
     * @param type    The class to append in the log.
     **********************************************************************************************/
    protected static void instTabTypeAndNewLine( @SuppressWarnings ("rawtypes") Class type )
    {
        if ( type != null)
        {
            String typeStr= type.getName();
                 if (typeStr.startsWith( "java.lang." ))    typeStr= typeStr.substring( 10 );
            else if (typeStr.startsWith( "java.util." ))    typeStr= typeStr.substring( 10 );

            do    { toolBuf.append( ' ' ); } while ( toolBuf.length() <= instLineBeginIdx + instTypeTabStop  );
            toolBuf.append( fmtInstTypePrefix ).append( typeStr ).append( fmtInstTypePostfix );
        }
        instNewLine();
    }


//        /** ****************************************************************************************
//         *  Dump a xml document into our Buffer.
//         * @param xDocument     The XDocument to be logged.
//         * @param headLine      The headline to log.
//         ******************************************************************************************/
//        protected static void xml( XDocument xDocument, String headLine)
//        {
//            // create/clear toolBuf
//            if ( toolBuf == null )
//                toolBuf= new AString( 1024 );
//            else
//                toolBuf.clear();
//
//            // print headline
//            if ( headLine != null )
//                toolBuf.append( headLine ).newLine();
//
//            foreach ( XElement el in xDocument.Elements() )
//                xmlElement( el, null, headLine != null ? 1 : 0 );
//        }
//
//        /** ****************************************************************************************
//         *     Internal function for logging an XElement.
//         * @param xe          The XElement to log.
//         * @param headLine    The headline to log.
//         * @param indent      The indentation to Log.
//         ******************************************************************************************/
//        protected static void xmlElement( XElement xe, String headLine, int indent )
//        {
//            // print headline
//            if ( headLine != null )
//                toolBuf.append( headLine ).newLine();
//
//            // print name
//            toolBuf.append( ' ',  indent * 2 ).append( xe.Name.ToString() );
//            if ( !xe.HasElements )
//                toolBuf.append( '=' ).append( '\"' ).append(xe.Value).append( '\"' );
//
//            // print attributes
//            if ( xe.HasAttributes )
//                foreach ( var attribute in xe.Attributes() )
//                    toolBuf.append( ' ' ).append( attribute.Name.ToString() ).append( '=' ).append( '\"' ).append( attribute.Value ).append( '\"' );
//
//            toolBuf.newLine();
//
//            // recursion
//            foreach ( var element in xe.Elements() )
//                xmlElement( element, null, indent + 1 );
//        }

}
