// #################################################################################################
//  com.aworx.lox.tools - ALox Logging Library
//
//  Copyright 2013-2019 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################

/** ************************************************************************************************
 *  This is the Java package for classes that provide tools and extensions to the
 *  <b>%ALox Logging Library</b>.
 *
 *  Developed by A-Worx GmbH and published under Boost Software License.
 **************************************************************************************************/
package com.aworx.lox.tools;

import java.io.ByteArrayOutputStream;
import java.io.PrintStream;
import java.lang.reflect.Array;
import java.lang.reflect.Field;
import java.lang.reflect.Modifier;
import java.util.HashMap;
import java.util.Iterator;

import com.aworx.lib.strings.AString;
import com.aworx.lib.threads.ThreadLock;
import com.aworx.lox.Log;
import com.aworx.lox.Lox;
import com.aworx.lox.Verbosity;


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

        /** Suffix for instance line numbers */
        public static    String            fmtInstLineNoSuffix           = ">";

        /** The String to log out if a given object instance equals null */
        public static    String            fmtInstNull                    = "<null>";

        /** Prefix before logging out a string representation of a member because recursion limit was reached.  */
        public static    String            fmtInstRecursionLimit         = "(MAX REC) ";

        /** Prefix before logging out a cyclic reference line number. */
        public static    String            fmtInstCycRefPrefix           = "(Cyclic ref., see line <";

        /**  Prefix before logging size of an IEnumberable. */
        public static    String            fmtInstIterablePrefix         = "Iterable, size= ";

        /**  Suffix after logging IEnumberable. */
        public static    String            fmtInstIterableSuffix         = "";

        /**  Prefix before logging size of an IEnumberable. */
        public static    String            fmtInstArrayPrefix            = "array[";

        /**  Suffix after logging IEnumberable. */
        public static    String            fmtInstArraySuffix            = "]";


        /** Suffix after logging out a cyclic reference line number. */
        public static    String            fmtInstCycRefSuffix           = ">)";

        /** String for non-accessible members  */
        public static    String            FmtInstNoAccessToValue        = "<no access>" ;

        /** Prefix for type names */
        public static    String            fmtInstTypePrefix            = "{";

        /** Suffix for type names */
        public static    String            fmtInstTypeSuffix            = "}";

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
     * @param domain    The <em>Log Domain</em> which is combined with <em>Scope Domains</em>
     *                  set for the \e Scope of invocation.
     * @param verbosity The verbosity.
     * @param e         The Exception to log.
     * @param headline  (Optional) A headline string preceding the exception output.
     * @param lox       (Optional) The Lox to log with. If null, the static member LOX of class Log is used.
     **********************************************************************************************/
    public static void exception( String domain, Verbosity verbosity, Exception e, String headline, Lox lox)
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
            lox.entry( domain, verbosity, toolBuf );

        } finally { lock.release(); }
    }

    /** ********************************************************************************************
     *  Log an exception including inner exceptions recursively.
     *
     * @param domain    The <em>Log Domain</em> which is combined with <em>Scope Domains</em>
     *                  set for the \e Scope of invocation.
     * @param verbosity The verbosity.
     * @param e         The Exception to log.
     * @param headline  (Optional) A headline string preceding the exception output.
     **********************************************************************************************/
    public static void exception( String domain, Verbosity verbosity, Exception e, String headline )
    {
        exception( domain, verbosity, e, headline, null );
    }

    /** ********************************************************************************************
     *  Log an exception including inner exceptions recursively.
     *
     * @param domain    The <em>Log Domain</em> which is combined with <em>Scope Domains</em>
     *                  set for the \e Scope of invocation.
     * @param verbosity The verbosity.
     * @param e         The Exception to log.
     **********************************************************************************************/
    public static void exception( String domain, Verbosity verbosity, Exception e )
    {
        exception( domain, verbosity, e, null, null );
    }

    /** ********************************************************************************************
     *  Log an exception including inner exceptions recursively.
     *
     * @param verbosity   The verbosity.
     * @param e           The Exception to log.
     * @param headline    (Optional) A headline string preceding the exception output.
     **********************************************************************************************/
    public static void exception(                  Verbosity verbosity, Exception e, String headline )
    {
         exception( null, verbosity, e, headline,  null );
    }

    /** ********************************************************************************************
     *  Log an exception including inner exceptions recursively.
     *
     * @param verbosity   The verbosity.
     * @param e           The Exception to log.
     **********************************************************************************************/
    public static void exception(                  Verbosity verbosity, Exception e )
    {
        exception( null,   verbosity, e, null, null );
    }

    /** ********************************************************************************************
     *  Log an exception including inner exceptions recursively.
     *
     * @param e           The Exception to log.
     * @param headline    (Optional) A headline string preceding the exception output.
     **********************************************************************************************/
    public static void exception(                                    Exception e, String headline )
    {
        exception( null,    Verbosity.ERROR, e, headline, null );
    }

    /** ********************************************************************************************
     *  Log an exception including inner exceptions recursively.
     *
     * @param e           The Exception to log.
     **********************************************************************************************/
    public static void exception(Exception e)
    {
        exception( null, Verbosity.ERROR, e, null, null );
    }

    /** ********************************************************************************************
     *  Log the current stack trace.
     *
     * @param domain    The <em>Log Domain</em> which is combined with <em>Scope Domains</em>
     *                  set for the \e Scope of invocation.
     * @param verbosity The verbosity.
     * @param headline  (Optional) A headline string preceding the stack trace output.
     * @param lox       (Optional) The Lox to log with. If null, the static member LOX of class Log is used.
     **********************************************************************************************/
    public static void stackTrace( String domain, Verbosity verbosity, String headline, Lox lox)
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
                    toolBuf._( headline ).newLine();

                // print stack trace into tempBuf
                (new Exception()).printStackTrace( exceptionPS );
                tempBuf.clear()._( exceptionBAOS.toString() );
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
                        toolBuf.insertChars( ' ',  2 )._NC( tempBuf.buffer(), tempLineStartIdx + 4, tempLineEndIdx  - tempLineStartIdx - 4).newLine();
                }
            }

            // if no lox given, use static Log.LOX
            if ( lox == null )
                lox= Log.LOX;

            // log it using the static Log interface
            lox.entry( domain, verbosity, toolBuf );

        } finally { lock.release(); }
    }

    /** ********************************************************************************************
     *  Log the current stack trace.
     *
     * @param domain    The <em>Log Domain</em> which is combined with <em>Scope Domains</em>
     *                  set for the \e Scope of invocation.
     * @param verbosity The verbosity.
     * @param headline  (Optional) A headline string preceding the stacktrace output.
     **********************************************************************************************/
    public static void stackTrace(String domain, Verbosity verbosity, String headline)
    {
        stackTrace( domain, verbosity, headline, null );
    }

    /** ********************************************************************************************
     *  Log the current stack trace.
     *
     * @param domain    The <em>Log Domain</em> which is combined with <em>Scope Domains</em>
     *                  set for the \e Scope of invocation.
     * @param verbosity The verbosity.
     **********************************************************************************************/
    public static void stackTrace(String domain, Verbosity verbosity)
    {
        stackTrace( domain, verbosity, null, null );
    }

    /** ********************************************************************************************
     *  Log the current stack trace.
     *
     * @param verbosity   The verbosity.
     * @param headline    (Optional) A headline string preceding the stacktrace output.
     **********************************************************************************************/
    public static void stackTrace(Verbosity verbosity, String headline)
    {
        stackTrace( null, verbosity, headline, null );
    }

    /** ********************************************************************************************
     *  Log the current stack trace.
     *
     * @param verbosity   The verbosity.
     **********************************************************************************************/
    public static void stackTrace(Verbosity verbosity)
    {
        stackTrace( null, verbosity, null, null );
    }

    /** ********************************************************************************************
     * Recursively logs objects using reflection.
     * @param domain       The <em>Log Domain</em> which is combined with <em>Scope Domains</em>
     *                     set for the \e Scope of invocation.
     * @param verbosity    The verbosity.
     * @param o            The object to be logged.
     * @param maxRecursion The maximum depth of recursion for logging nested object.
     * @param headline     (Optional) A headline string to precede the exception with.
     * @param lox          (Optional) The lox to log with. If null, the static member LOX of
     *                     the static class Log is used.
     **********************************************************************************************/
    public static void instance( String domain, Verbosity verbosity, Object o, int maxRecursion, String headline, Lox lox)

    {
        try { lock.acquire();

            // if no lox given, use static Log.LOX
            if ( lox == null )
                lox= Log.LOX;

                // dump exception to the Buffer
                instMain( o, maxRecursion, headline );

                // log it using the static Log interface
                lox.entry( domain, verbosity, toolBuf );


        } finally { lock.release(); }
    }

    /** ********************************************************************************************
     * Recursively logs objects using reflection.
     * @param domain          The <em>Log Domain</em> which is combined with <em>Scope Domains</em>
     *                        set for the \e Scope of invocation.
     * @param verbosity       The verbosity.
     * @param o               The object to be logged.
     * @param maxRecursion    The maximum depth of recursion for logging nested object.
     * @param headline        (Optional) A headline string to precede the exception with.
     **********************************************************************************************/
    public static void instance(String domain, Verbosity verbosity, Object o, int maxRecursion, String headline)
    {
        instance( domain, verbosity, o, maxRecursion, headline, null );
    }

    /** ********************************************************************************************
     * Recursively logs objects using reflection.
     * @param domain          The <em>Log Domain</em> which is combined with <em>Scope Domains</em>
     *                        set for the \e Scope of invocation.
     * @param verbosity       The verbosity.
     * @param o               The object to be logged.
     * @param maxRecursion    The maximum depth of recursion for logging nested object.
     **********************************************************************************************/
    public static void instance(String domain, Verbosity verbosity, Object o, int maxRecursion)
    {
        instance( domain, verbosity, o, maxRecursion, null, null );
    }

    /** ********************************************************************************************
     * Recursively logs objects using reflection.
     * @param verbosity       The verbosity.
     * @param o               The object to be logged.
     * @param maxRecursion    The maximum depth of recursion for logging nested object.
     * @param headline        (Optional) A headline string to precede the exception with.
     **********************************************************************************************/
    public static void instance(Verbosity verbosity, Object o, int maxRecursion, String headline)
    {
        instance( null, verbosity, o, maxRecursion, headline, null );
    }

    /** ********************************************************************************************
     * Recursively logs objects using reflection.
     * @param verbosity       The verbosity.
     * @param o               The object to be logged.
     * @param maxRecursion    The maximum depth of recursion for logging nested object.
     **********************************************************************************************/
    public static void instance(Verbosity verbosity, Object o, int maxRecursion)
    {
        instance( null, verbosity, o, maxRecursion, null, null );
    }

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
                toolBuf._( headline ).newLine();
        }

        // increase tab level
        indent++;

        // Assert
        if ( e == null )
        {
            toolBuf.insertChars( ' ',  indent * 2 )._( fmtExcNull );
            return;
        }

        // log exception details
        toolBuf.insertChars( ' ',  indent * 2 )._( "Type:       ")._(e.getClass().getName()                ).newLine();
        toolBuf.insertChars( ' ',  indent * 2 )._( "Message:    ")._(e.getMessage()                        ).newLine();

        // recursion
        if ( e.getCause() != null )
        {
            toolBuf.insertChars( ' ',  indent * 2 )._( "Cause:   " ).newLine();
            exc( e.getCause() , null, indent );
        }

        // print stack trace, but only on indent level 0
        if ( indent == 1 )
        {
            // log stack trace header msg
            toolBuf.insertChars( ' ',  2 )._( fmtExcStackTraceHeader ).newLine();

            // print stack trace into tempBuf
            e.printStackTrace( exceptionPS );
            tempBuf.clear()._( exceptionBAOS.toString() );
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
                    toolBuf.insertChars( ' ',  4 )._NC( tempBuf.buffer(), tempLineStartIdx + 4, tempLineEndIdx  - tempLineStartIdx - 4).newLine();
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
        char[] buf=      tempBuf.buffer();
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
        if ( toolBuf == null )   toolBuf= new AString( 1024 );
        else                     toolBuf.clear();

        instLineNumber=          0;
        instLineBeginIdx=        0;
        instObject2LineNumber=   new HashMap<Object, Integer>();

        // log headline if answer exception
        if ( headLine != null )
            toolBuf._( headLine )._(' ');

        // dump the object
        instRecursive( o, maxRecursion, headLine != null ? 1 : 0  );

        // dispose the dictionary
        instObject2LineNumber= null;
    }


    /** ********************************************************************************************
     * Recursively log an instance using reflection.
     * @param inst         The element.
     * @param maxRecursion The maximum depth of recursion for logging nested object.
     * @param indent       The indentation in the output (recursively increased).
     **********************************************************************************************/
    @SuppressWarnings ("null")
    protected static void instRecursive( Object inst, int maxRecursion, int indent )
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
                toolBuf._( fmtInstNull );
                isValueType= true;
            }

            // string?
            else if ( inst instanceof String )
            {
                // add value and type, that's it
                toolBuf    ._( '\"' )._( (String) inst )._( '\"' );
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
                toolBuf    ._( '\"' )._( val )._( '\"' );

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
                toolBuf    ._( val );

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
            toolBuf._( fmtInstRecursionLimit )._( vString );
            instTabTypeAndNewLine( type );

            return;
        }

        // ### cyclic reference? ###
        Integer lineNumber= instObject2LineNumber.get( inst );
        if ( lineNumber != null )
        {
            toolBuf ._( fmtInstCycRefPrefix )
                    ._( lineNumber.intValue(), 2 )
                    ._( fmtInstCycRefSuffix );
            instTabTypeAndNewLine( inst.getClass() );
            return;
        }
        // mark object as being logged
        instObject2LineNumber.put( inst, new Integer( instLineNumber ) );

        // ### Arrays ###
        if ( type.isArray() )
        {
            // get array length from fields"length()"
            int qtyObjects= Array.getLength( inst );

            toolBuf._( fmtInstArrayPrefix )._( qtyObjects )._( fmtInstArraySuffix );
            instTabTypeAndNewLine( type );

            // loop over all objects
            for ( int itemNo= 0; itemNo < qtyObjects ; itemNo++ )
            {
                instBeginLine( indent );
                toolBuf._( itemNo, 1 )._(": ");

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
            toolBuf._( fmtInstIterablePrefix )._( qtyObjects )._( fmtInstIterableSuffix );
            instTabTypeAndNewLine( type );

            // loop over all objects
            int itemNo= 0;
            i= it.iterator();
            while( i.hasNext() )
            {
                instBeginLine( indent );
                toolBuf._( itemNo++, 1 )._(": ");
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
                try { value= memberInfo.get( inst ); }    catch( @SuppressWarnings ("unused") Exception e)  {    value= FmtInstNoAccessToValue; }

                // begin line and log name
                instBeginLine( indent );
                toolBuf._( memberInfo.getName() )._(':');
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
     *  Appends line number (format defined in fields #fmtInstLineNoPrefix and #fmtInstLineNoSuffix)
     *  and then adds indent characters (defined in field #fmtInstIndent).
     *
     * @param indent    The indentation of the line.
     **********************************************************************************************/
    protected static void instBeginLine( int indent )
    {
        instLineBeginIdx= toolBuf.length();
        toolBuf._( fmtInstLineNoPrefix )._( instLineNumber, 2 )._( fmtInstLineNoSuffix );
        for ( int i= indent; i > 0; i-- )
            toolBuf._( fmtInstIndent );
    }

    /** ********************************************************************************************
     *  Appends spaces to move to the given tabStop (but at least one).
     *
     * @param tabStop    The tab stop position to go to.
     **********************************************************************************************/
    protected static void instTabStop( int tabStop )
    {
        do    { toolBuf._( ' ' ); } while ( toolBuf.length() <= instLineBeginIdx + tabStop  );
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

            do    { toolBuf._( ' ' ); } while ( toolBuf.length() <= instLineBeginIdx + instTypeTabStop  );
            toolBuf._( fmtInstTypePrefix )._( typeStr )._( fmtInstTypeSuffix );
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
