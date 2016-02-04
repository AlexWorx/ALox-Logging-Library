// #################################################################################################
//  cs.aworx.lox.tools - ALox Logging Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################

using System;
using System.Collections;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Runtime.CompilerServices;
using cs.aworx.lib;
using cs.aworx.lib.threads;
using cs.aworx.lib.strings;

#if ( !ALOX_NO_XML)
    using System.Xml.Linq;
#endif

#if (!ALOX_NO_REFLECTION)
    using System.Reflection;
#endif

#if (!ALOX_NO_THREADS)
    using System.Threading;
using cs.aworx.lox.core;
#endif

/** ************************************************************************************************
 *  This is the C# namespace for classes that provide tools and extensions to the 
 *  <em>%ALox Logging Library</em>.
 *  
 *  Developed by A-Worx GmbH and published under the MIT license.
 **************************************************************************************************/
namespace cs.aworx.lox.tools {

/** ************************************************************************************************
 * 
 *    Provides high level functionality for logging things like Exceptions, objects and XML documents.
 * 
 **************************************************************************************************/
public class LogTools
{
    #if ALOX_DBG_LOG || ALOX_REL_LOG

        // #############################################################################################
        #region  __String_Constants__
        // #############################################################################################

        /// The String to log out if the exception parameter equals null
        public static    String            FmtExcNull                           ="<No exception given>";

        /// Prefix for instance line numbers
        public static    String            FmtInstLineNoPrefix                  ="<";

        /// Postfix for instance line numbers
        public static    String            FmtInstLineNoPostfix                 =">";

        /// The String to log out if a given object instance equals null
        public static    String            FmtInstNull                          ="<null>";

        /// Prefix before logging out a string representation of a member because recursion limit was
        /// reached. 
        public static    String            FmtInstRecursionLimit                ="(MAX REC) ";

        /// Prefix before logging out a cyclic reference line number. 
        public static    String            FmtInstCycRefPrefix                  ="(Cyclic ref., see line <";

        /// Prefix before logging size of an IEnumberable. 
        public static    String            FmtInstIEnumerablePrefix             ="IEnumerable, size= ";

        /// Postfix after logging IEnumberable. 
        public static    String            FmtInstIEnumerablePostfix            ="";

        /// Prefix before logging size of an IEnumberable. 
        public static    String            FmtInstArrayPrefix                   ="array[";

        /// Postfix after logging IEnumberable. 
        public static    String            FmtInstArrayPostfix                  ="]";

        /// Postfix after logging out a cyclic reference line number. 
        public static    String            FmtInstCycRefPostfix                 =">)";

        /// Indent String for instance lines
        public static    String            FmtInstNoAccessToValue               ="<no access>" ;

        /// Prefix for type names
        public static    String            FmtInstTypePrefix                    ="{";

        /// Postfix for type names
        public static    String            FmtInstTypePostfix                   ="}";

        /// Indent String for instance lines
        public static    String            FmtInstIndent                        ="  ";

        #endregion

        /// Tab stop for values when logging instances.
        public static    int               instValueTabStop                     =35;

        /// Tab stop for types when logging instances.
        public static    int               instTypeTabStop                      =65;


        // #############################################################################################
        // Private/protected fields
        // #############################################################################################

        /// Buffer to build log messages.
        protected static AString                    toolBuf;

        /// Temporary helper buffer.
        protected static AString                    tempBuf;

        /// Instance line number counter.
        protected static uint                       instLineNumber;

        /// Instance line number dictionary used to refer to already logged sub objects.
        protected static Dictionary<Object, UInt32> instObject2LineNumber;

        /// Instance index of beginning of line in toolBuf.
        protected static int                        instLineBeginIdx;

        /**  
         *  This is the ThreadLock (mutex) which each method of this class uses to lock resources, e.g.
         *  the toolBuf
         *  */
        protected static ThreadLock                 Lock                                =new ThreadLock();


        // #############################################################################################
        // Public static interface (not accessible in release code)
        // #############################################################################################

    #endif // ALOX_DBG_LOG || ALOX_REL_LOG


    /** ********************************************************************************************
     * 
     *  Log an exception including inner exceptions recursively. Note: Calls to this  method are
     *  automatically removed from release code.
     * 
     * @param domain     The log domain name. </param>
     * @param level      The log level. </param>
     * @param e          The Exception to log. </param>
     * @param headline   (Optional) A headline string to precede the exception with. </param>
     * @param indent     (Optional) the indentation in the output (recursively increased).
     *                          Defaults to 0. </param>
     * @param lox        (Optional) The lox to log with. If null, the static member LOX of
     *                          the static class Log is used. </param>
     * @param csf        (Optional) Caller info, compiler generated. Please omit. </param>
     * @param cln        (Optional) Caller info, compiler generated. Please omit. </param>
     * @param cmn        (Optional) Caller info, compiler generated. Please omit. </param>
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public static void Exception( String    domain,       Log.Level   level,
                                  Exception e,            String      headline= null,
                                  int       indent= 0,    Lox         lox=      null,
                                  [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )

    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            try { Lock.Acquire();

                // create/clear toolBuf
                if ( toolBuf == null )
                    toolBuf= new AString( 1024 );
                toolBuf.Clear();

                // dump exception to the Buffer
                exception ( e, headline, -1 );

                // if no lox given, use static Log.LOX or, if debug logging is not active, return
                if ( lox == null )
                    #if ALOX_DBG_LOG
                        lox= Log.LOX;
                    #else
                        return;
                    #endif

                // log it using the static Log interface
                lox.Line ( true, domain, level, toolBuf, indent, null, csf, cln, cmn);

            } finally { Lock.Release(); }
        #endif
    }

    /** ********************************************************************************************
     * 
     *  Log an exception including inner exceptions recursively. Default domain of file is used with
     *  Log.Level.Error. Note: Calls to this  method are automatically removed from release code.
     * 
     * @param level      The log level. </param>
     * @param e          The Exception to log. </param>
     * @param headline   (Optional) A headline string to precede the exception with. </param>
     * @param indent     (Optional) the indentation in the output (recursively increased).
     *                          Defaults to 0. </param>
     * @param lox        (Optional) The lox to log with. If null, the static member LOX of
     *                          the static class Log is used. </param>
     * @param csf        (Optional) Caller info, compiler generated. Please omit. </param>
     * @param cln        (Optional) Caller info, compiler generated. Please omit. </param>
     * @param cmn        (Optional) Caller info, compiler generated. Please omit. </param>
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public static void Exception( Log.Level   level,
                                  Exception   e,                String        headline= null,
                                  int         indent=    0,     Lox           lox=      null,
                                  [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )

    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            Exception( null, level, e, headline, indent, lox, csf,cln,cmn );
        #endif
    }

    /** ********************************************************************************************
     * 
     *  Log an exception including inner exceptions recursively. Default domain of file is used with
     *  Log.Level.Error. Note: Calls to this  method are automatically removed from release code.
     * 
     * @param e          The Exception to log. </param>
     * @param headline   (Optional) A headline string to precede the exception with. </param>
     * @param indent     (Optional) the indentation in the output (recursively increased).
     *                          Defaults to 0. </param>
     * @param lox        (Optional) The lox to log with. If null, the static member LOX of
     *                          the static class Log is used. </param>
     * @param cln        (Optional) Caller info, compiler generated. Please omit. </param>
     * @param cmn        (Optional) Caller info, compiler generated. Please omit. </param>
     * @param csf        (Optional) Caller info, compiler generated. Please omit. </param>
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public static void Exception( Exception e,             String headline= null,
                                  int       indent=  0,    Lox    lox=      null,
                                  [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )

    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            Exception( null, Log.Level.Error, e, headline, indent, lox, csf,cln,cmn );
        #endif
    }

    /** ********************************************************************************************
     * Uses reflection to log an object. 
     * @param domain         The log domain name. </param>
     * @param level          The log level. </param>
     * @param o              The object to be logged. </param>
     * @param maxRecursion   The maximum depth of recursion for logging nested object. </param>
     * @param headline       (Optional) A headline string to precede the exception with. </param>
     * @param indent         (Optional) The indentation in the output (recursively increased).
     *                              Defaults to 0. </param>
     * @param lox            (Optional) The lox to log with. If null, the static member LOX of
     *                              the static class Log is used. </param>
     * @param csf            (Optional) Caller info, compiler generated. Please omit. </param>
     * @param cln            (Optional) Caller info, compiler generated. Please omit. </param>
     * @param cmn            (Optional) Caller info, compiler generated. Please omit. </param>
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public static void Instance( String  domain,              Log.Level   level,
                                 Object  o,                   int         maxRecursion,
                                 String  headline=  null,     int         indent=    0,
                                 Lox     lox=       null,
                                 [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )

    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            try { Lock.Acquire();

                // if no lox given, use static Log.LOX or, if debug logging is not active, return
                if ( lox == null )
                    #if ALOX_DBG_LOG
                        lox= Log.LOX;
                    #else
                        return;
                    #endif

                #if !(ALOX_WP71 || ALOX_WP8 || ALOX_NO_REFLECTION)

                    // dump exception to the Buffer
                    instMain( o, maxRecursion, headline );

                    // log it using the static Log interface
                    lox.Line ( true, domain, level, toolBuf, indent, null, csf,cln,cmn );

                #else
                    lox.Line ( true, domain, level, "LoxTools.Instance(): Reflection not supported on this platform. ToString(): ", indent, null, csf,cln,cmn );
                    lox.Line ( true, domain, level, ( o == null ? "null" : o.ToString()), indent + 1, null, csf, cln, cmn );
                #endif // NO_REFLECTION

            } finally { Lock.Release(); }
        #endif
    }

    /** ********************************************************************************************
     * Uses reflection to log an object. 
     * @param level            The log level. </param>
     * @param o                The object to be logged. </param>
     * @param maxRecursion     The maximum depth of recursion for logging nested object. </param>
     * @param headline         (Optional) A headline string to precede the exception with. </param>
     * @param indent           (Optional) The indentation in the output (recursively increased).
     *                                Defaults to 0. </param>
     * @param lox              (Optional) The lox to log with. If null, the static member LOX of
     *                                the static class Log is used. </param>
     * @param csf              (Optional) Caller info, compiler generated. Please omit. </param>
     * @param cln              (Optional) Caller info, compiler generated. Please omit. </param>
     * @param cmn              (Optional) Caller info, compiler generated. Please omit. </param>
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public static void Instance( Log.Level  level,
                                 Object     o,                  int    maxRecursion,
                                 String     headline= null,     int    indent=    0,
                                 Lox        lox=      null,
                                 [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )

    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            Instance( null, level, o, maxRecursion, headline, indent, lox, csf, cln, cmn );
        #endif
    }

    #if  !ALOX_NO_XML
        /** ****************************************************************************************
         * 
         *  Log a XML document. Note: Calls to this method are automatically removed from release code.
         * 
         * @param domain     The log domain name. </param>
         * @param level      The log level. </param>
         * @param xDocument  the XML document to be logged. </param>
         * @param headLine   (Optional) The headline to log. </param>
         * @param indent     (Optional) the indentation in the output (recursively increased).
         *                          Defaults to 0. </param>
         * @param lox        (Optional) The lox to log with. If null, the static member LOX of
         *                          the static class Log is used. </param>
         * @param csf        (Optional) Caller info, compiler generated. Please omit. </param>
         * @param cln        (Optional) Caller info, compiler generated. Please omit. </param>
         * @param cmn        (Optional) Caller info, compiler generated. Please omit. </param>
         ******************************************************************************************/
        [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
        public static void XML( String       domain,           Log.Level    level,
                                XDocument    xDocument,        String       headLine=   null,
                                int          indent=      0,   Lox          lox=        null,
                                [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
        {
            #if ALOX_DBG_LOG || ALOX_REL_LOG
                try { Lock.Acquire();

                    // dump exception to the Buffer
                    xml( xDocument, headLine );

                    // if no lox given, use static Log.LOX or, if debug logging is not active, return
                    if ( lox == null )
                        #if ALOX_DBG_LOG
                            lox= Log.LOX;
                        #else
                            return;
                        #endif

                    // log it using the static Log interface
                    lox.Line ( true, domain, level, toolBuf, indent, null, csf, cln, cmn );


                } finally { Lock.Release(); }
            #endif
        }

        /** ****************************************************************************************
         * 
         *  Log a XML document. Note: Calls to this method are automatically removed from release code.
         * 
         * @param level      The log level. </param>
         * @param xDocument  the XML document to be logged. </param>
         * @param headLine   The headline to log. </param>
         * @param indent     (Optional) the indentation in the output (recursively increased).
         *                          Defaults to 0. </param>
         * @param lox        (Optional) The lox to log with. If null, the static member LOX of
         *                          the static class Log is used. </param>
         * @param csf        (Optional) Caller info, compiler generated. Please omit. </param>
         * @param cln        (Optional) Caller info, compiler generated. Please omit. </param>
         * @param cmn        (Optional) Caller info, compiler generated. Please omit. </param>
         ******************************************************************************************/
        [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
        public static void XML( Log.Level       level,
                                XDocument       xDocument,      String    headLine,
                                int             indent=    0,   Lox       lox= null,
                                [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
        {
            #if ALOX_DBG_LOG || ALOX_REL_LOG
                XML( null, level, xDocument, headLine, indent, lox, csf, cln, cmn );
            #endif
        }

        /** ****************************************************************************************
         * 
         *  Log a XML element. Note: Calls to this method are automatically removed from release code.
         * 
         * @param domain     The log domain name. </param>
         * @param level      The log level. </param>
         * @param xElement   the answer node of the XML tree to be logged. </param>
         * @param headLine   (Optional) The headline to log. </param>
         * @param indent     (Optional) the indentation in the output (recursively increased).
         *                          Defaults to 0. </param>
         * @param lox        (Optional) The lox to log with. If null, the static member LOX of
         *                          the static class Log is used. </param>
         * @param csf        (Optional) Caller info, compiler generated. Please omit. </param>
         * @param cln        (Optional) Caller info, compiler generated. Please omit. </param>
         * @param cmn        (Optional) Caller info, compiler generated. Please omit. </param>
         ******************************************************************************************/
        [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
        public static void XML( String      domain,     Log.Level    level,
                                XElement    xElement,   String       headLine=  null,
                                int         indent= 0,  Lox          lox=       null,
                                [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
        {
            #if ALOX_DBG_LOG || ALOX_REL_LOG
                try { Lock.Acquire();

                    // create/clear toolBuf
                    if ( toolBuf == null )
                        toolBuf= new AString( 1024 );
                    else
                        toolBuf.Clear();

                    // dump exception to the Buffer
                    xmlElement( xElement, headLine, 0 );

                    // if no lox given, use static Log.LOX or, if debug logging is not active, return
                    if ( lox == null )
                        #if ALOX_DBG_LOG
                            lox= Log.LOX;
                        #else
                            return;
                        #endif

                    // log it using the static Log interface
                    lox.Line ( true, domain, level, toolBuf, indent, null, csf, cln, cmn );


                } finally { Lock.Release(); }
            #endif
        }

        /** ****************************************************************************************
         * 
         *  Log a XML element. Note: Calls to this method are automatically removed from release code.
         * 
         * @param level        The log level. </param>
         * @param xElement     the answer node of the XML tree to be logged. </param>
         * @param headLine     The head line. </param>
         * @param indent       (Optional) the indentation in the output (recursively increased).
         *                            Defaults to 0. </param>
         * @param lox          (Optional) The lox to log with. If null, the static member LOX of
         *                            the static class Log is used. </param>
         * @param csf          (Optional) Caller info, compiler generated. Please omit. </param>
         * @param cln          (Optional) Caller info, compiler generated. Please omit. </param>
         * @param cmn          (Optional) Caller info, compiler generated. Please omit. </param>
         ******************************************************************************************/
        [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
        public static void XML( Log.Level   level,
                                XElement    xElement,    String  headLine,
                                int         indent=  0,  Lox     lox= null,
                                [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
        {
            #if ALOX_DBG_LOG || ALOX_REL_LOG
                XML( null, level, xElement, headLine, indent, lox, csf, cln, cmn );
            #endif
        }

    #endif // ALOX_NO_XML

    #if ALOX_DBG_LOG || ALOX_REL_LOG
        // #############################################################################################
        // internals
        // #############################################################################################

        /** ****************************************************************************************
         * Logs an exception. 
         * @param e          The exception to log. </param>
         * @param headline   An optional headline string preceding the exception. </param>
         * @param indent     The indentation in the output (recursively increased). If set to -1
         *                          the 'headline' is logged. </param>
         ******************************************************************************************/
        protected static void exception( Exception e, String headline, int indent )
        {
            // log headline if answer exception
            if ( indent == -1 )
            {
                indent= 0;
                if ( headline != null )
                    toolBuf._( headline ).NewLine();
            }

            // increase tab level
            indent++;

            // Assert
            if ( e == null )
            {
                toolBuf.InsertChars( ' ',  indent * 2 )._( FmtExcNull );
                return;
            }


            // log exception details
                                          { toolBuf.InsertChars( ' ',  indent * 2 )._( "Type:       ")._(e.GetType().ToString()              ).NewLine(); }
                                          { toolBuf.InsertChars( ' ',  indent * 2 )._( "Message:    ")._(e.Message                           ).NewLine(); }
            #if !ALOX_WP71                       
              if ( e.HelpLink   != null)  { toolBuf.InsertChars( ' ',  indent * 2 )._( "HelpLink:   ")._(e.HelpLink                          ).NewLine(); }
              if ( e.Source     != null)  { toolBuf.InsertChars( ' ',  indent * 2 )._( "Source:     ")._(e.Source                            ).NewLine(); }
              if ( e.HResult    != 0)     { toolBuf.InsertChars( ' ',  indent * 2 )._( "HResult:    ")._(String.Format("0x{0:X08}",e.HResult)).NewLine(); }
            #endif

            if ( e.StackTrace != null)
            {
                toolBuf.InsertChars( ' ',  indent * 2 )._( "StackTrace: ").NewLine();
                toolBuf._( e.StackTrace ).NewLine();
            }

            // recursion
            if ( e.InnerException != null )
            {
                toolBuf.InsertChars( ' ',  indent * 2 )._( "Inner:   " ).NewLine();
                exception( e.InnerException, null, indent );
            }
        }

        #if !(ALOX_WP71 || ALOX_WP8 || ALOX_NO_REFLECTION)

            /** ************************************************************************************
             * Logs the header and invokes instRecursive() 
             * @param o               The object to be logged. </param>
             * @param maxRecursion    The maximum depth of recursion for logging nested object. </param>
             * @param headLine        The headline to log. </param>
             **************************************************************************************/
            protected static void instMain( Object o, int maxRecursion, String headLine)
            {
                // prepare fields
                if ( toolBuf == null )  toolBuf= new AString( 1024 );
                else                    toolBuf.Clear();
                if ( tempBuf == null )  tempBuf= new AString( 64 );

                instLineNumber=         0;
                instLineBeginIdx=       0;
                instObject2LineNumber=  new Dictionary<Object, UInt32>();

                // log headline if answer exception
                if ( headLine != null )
                    toolBuf._( headLine )._(' ');

                // dump the object
                instRecursive( o, maxRecursion, headLine != null ? 1 : 0  );

                // dispose the dictionary
                instObject2LineNumber= null;
            }

            /** ************************************************************************************
             * Recursively log an instance using reflection. 
             * @param inst            The element. </param>
             * @param maxRecursion    The maximum depth of recursion for logging nested 
             *                               object. </param>
             * @param indent          The indentation in the output (recursively increased).
             *                               </param>
             **************************************************************************************/
            protected static void instRecursive( Object inst, int maxRecursion, int indent )
            {
                // get type
                Type type=    inst != null ? inst.GetType()
                                           : null;

                //### 1.  Detect and log value types (or null or sting)
                if ( isValueType( inst, type) )
                {
                    toolBuf._( tempBuf );
                    instTabTypeAndNewLine( type );
                    return;
                }

                //### 2. Key/Value pairs
                if ( type.IsValueType && type.IsGenericType && type.GetGenericTypeDefinition() == typeof(KeyValuePair<,>) )
                {
                    // get key/value types and objects
                    object instKey=    type.GetProperty("Key")     .GetValue(inst, null);
                    object instValue=  type.GetProperty("Value").GetValue(inst, null);

                    int keyValWritten= 0;

                    // key is of value type?
                    Type instKeyType=   instKey    != null ? instKey  .GetType()    : null;
                    Type instValueType= instValue  != null ? instValue.GetType()    : null;
                    if ( isValueType( instKey, instKeyType ) )
                    {
                        // log key value
                        keyValWritten= 1;
                        toolBuf._( tempBuf )._( ':' );

                        // value is of value type?
                        if ( isValueType( instValue, instValueType ) )
                        {
                            // log value value
                            keyValWritten= 2;
                            instTabStop( instValueTabStop );
                            toolBuf._( tempBuf );
                        }
                    }

                    // instTabTypeAndNewLine:
//                    else
                    {
                        do    { toolBuf._( ' ' ); } while ( toolBuf.Length() <= instLineBeginIdx + instTypeTabStop  );
                        toolBuf._( FmtInstTypePrefix )
                               ._( "KeyValuePair<")._( instKeyType   != null ? instKeyType  .Name : "null" )
                               ._(            ", ")._( instValueType != null ? instValueType.Name : "null" )
                               ._(             ">")
                               ._( FmtInstTypePostfix );

                        instNewLine();
                    }

                    // key no value type?
                    if ( keyValWritten == 0 )
                    {
                        instBeginLine( indent );
                        toolBuf._( "Key:" );
                        instTabStop( instValueTabStop );
                        instRecursive( instKey, maxRecursion - 1, indent + 1 );

                    }

                    if ( keyValWritten != 2 )
                    {
                        instBeginLine( indent );
                        if ( keyValWritten == 0 )
                        {
                            toolBuf._( "  Value:" );
                            //instTabStop( instValueTabStop );
                        }
                        instRecursive( instValue, maxRecursion - 1, indent + 1 );
                    }
                    return;
                }

                // ### maximum recursion? ###
                if ( maxRecursion == 0 )
                {
                    String vString=    inst.ToString();
                    String tString=    type.Namespace + "." + type.Name;

                    // often, ToString() just returns the type
                    if ( vString.Equals( tString) )
                        vString= String.Empty;

                    // append "(max rec.)" + value
                    toolBuf._( FmtInstRecursionLimit )._( vString );
                    instTabTypeAndNewLine( type );

                    return;
                }

                // ### cyclic reference? ###
                uint lineNumber;
                if ( instObject2LineNumber.TryGetValue( inst, out lineNumber ) )
                {
                    toolBuf._( FmtInstCycRefPrefix )
                           ._( lineNumber, 2 )
                           ._( FmtInstCycRefPostfix );
                    instTabTypeAndNewLine ( inst.GetType() );
                    return;
                }
                // mark object as being logged (in next line)
                instObject2LineNumber.Add( inst, instLineNumber );

                // cast to IEnumerable ( used in arrays and IEnumerables as well )
                IEnumerable enumerableElement= inst as IEnumerable;

                // ### Arrays ###
                if ( type.IsArray )
                {
                    // get array, its dimensions and their sizes
                    System.Array array=     (System.Array) inst;
                    int          qtyDim=    type.GetArrayRank();
                    int[]        dimLength= new int[ qtyDim ];

                    toolBuf._( FmtInstArrayPrefix );
                    for ( int i= 0; i < qtyDim ; i++ )
                    {
                        toolBuf._(  dimLength[ i ]= array.GetLength( i ) );
                        if ( i != qtyDim - 1 )
                            toolBuf._( ',' );
                    }
                    toolBuf._( FmtInstArrayPostfix );
                    instTabTypeAndNewLine( type );

                    // calc 'magnitudes' of dimensions
                    int[]    dimMagnitude= new int[ qtyDim ];
                    dimMagnitude[ qtyDim - 1 ]= 1;
                    for ( int i= qtyDim - 2 ; i >= 0 ; i-- )
                        dimMagnitude[ i ]= dimLength[ i + 1 ] * dimMagnitude[ i + 1 ];

                    // loop over all objects
                    int        itemNo= 0;
                    foreach (object item in enumerableElement)
                    {
                        instBeginLine( indent );

                        // calc indices from itemNo
                        toolBuf._('[');
                        int idx= itemNo++;
                        for ( int i= 0; i < qtyDim ; i++ )
                        {
                            toolBuf._( idx / dimMagnitude[ i ] );
                            idx=            idx % dimMagnitude[ i ];
                            toolBuf._( i != qtyDim - 1 ? ',' : ']');
                        }
                        toolBuf._(": ");

                        // log element
                        instRecursive( item, maxRecursion - 1, indent + 1 );
                    }
                }

                // ###  IEnumerables ###
                else if (enumerableElement != null)
                {
                    // get object count
                    int qtyObjects= enumerableElement.Cast<object>().Count();

                    // log headline and start new line
                    toolBuf._( FmtInstIEnumerablePrefix )._( qtyObjects )._( FmtInstIEnumerablePostfix );
                    instTabTypeAndNewLine( type );

                    // loop over all objects
                    int itemNo= 0;
                    foreach (object item in enumerableElement)
                    {
                        instBeginLine( indent );
                        toolBuf._( "  " )._( itemNo++, 1 )._(": ");
                        instRecursive( item, maxRecursion - 1, indent + 1 );
                    }
                }

                // ### classes ###
                else
                {
                    // finish line of object
                    instTabTypeAndNewLine( type );

                    // loop over fields
                    MemberInfo[] members= type.GetMembers( BindingFlags.Public | BindingFlags.NonPublic | BindingFlags.Instance );

                    foreach (var memberInfo in members)
                    {
                        // get type    and value
                        Type    fType;
                        object    fValue;

                        // get field/property info
                        FieldInfo       fInfo=    memberInfo as FieldInfo;
                        PropertyInfo    pInfo=    memberInfo as PropertyInfo;

                             if ( fInfo != null )
                        {
                                  fType=     fInfo.FieldType;
                            try { fValue=    fInfo.GetValue(inst); }  catch (Exception) { fValue= FmtInstNoAccessToValue; }
                        }
                        else if ( pInfo != null )
                        {
                                  fType=     pInfo.PropertyType;
                            try { fValue=    pInfo.GetValue(inst); }  catch (Exception) { fValue= FmtInstNoAccessToValue; }
                        }

                        // not a field or property?
                        else
                            continue;

                        // filter "__BackingField"s
                        if ( memberInfo.Name.Contains( "__BackingField" ) )
                            continue;

                        // begin line and log name
                        instBeginLine( indent );
                        toolBuf._( memberInfo.Name )._(':');
                        instTabStop( instValueTabStop );

                        // recursively log value
                        instRecursive( fValue, maxRecursion - 1, indent + 1 );
                    }
                }

            }

            /** ************************************************************************************
             * 
             *  Detects if the given object is of value type. Special treatment is given to 
             *  KeyValuePair&lt;,&gt;. C# treat them as a value type that causes some irritation 
             *  sometimes.
             * 
             * @param o        The object to be tested. </param>
             * @param type     The type of the object (needed outside, therefore passed here 
             *                        to avoid double creation). </param>
             * @return  the value (if given object is of value type) or null otherwise. 
             **************************************************************************************/
            protected static bool isValueType( Object o, Type type )
            {
                // clear tempBuf
                tempBuf.Clear();

                // check for null
                if ( o == null )
                {
                    tempBuf._( FmtInstNull );
                    return true;
                }

                // string?
                if ( type == typeof(String) )
                {
                    // add value and type, that's it
                    tempBuf    ._( '\"' )._( (String) o )._( '\"' );
                    return true;
                }

                // Char[]
                if ( type == typeof( Char[]) )
                {
                    Char[] charArrayVal= (Char[]) o;
                    String val;

                    val=    charArrayVal.Length > 100    ?    new String ( charArrayVal, 0, 100) + "..."
                                                        :    new String (charArrayVal );
                    if ( val.Contains((char) 0) )
                        val= val.Replace((char) 0, ' ' );

                    // add value and type, that's it
                    tempBuf    ._( '\"' )._( val )._( '\"' );

                    return true;
                }

                // value type?
                if ( type.IsValueType )
                {
                    // generic key/value pair?
                    if ( type.IsGenericType && type.GetGenericTypeDefinition() == typeof(KeyValuePair<,>))
                        return false;

                    // normal value type
                    String val= o.ToString();
                    if ( val.Length == 1 && val[0]==(char) 0 )
                        val= "\\0";
                    else if ( val.Contains((char) 0) )
                        val= val.Replace((char) 0, ' ' );

                    // add value and type, that's it
                    tempBuf._( val );

                    return true;
                }

                // not a value type
                return false;

            }

            /** ************************************************************************************
             * Adds a new line to the buffer and increases line number counter. 
             **************************************************************************************/
            protected static void instNewLine()
            {
                instLineNumber++;
                toolBuf.NewLine();
            }

            /** ************************************************************************************
             * 
             *  Appends line number (format defined in fields #FmtInstLineNoPrefix and
             *  #FmtInstLineNoPostfix) and then adds indent characters (defined in field
             *  #FmtInstIndent).
             * 
             * @param indent     The indentation of the line. </param>
             **************************************************************************************/
            protected static void instBeginLine( int indent )
            {
                instLineBeginIdx=    toolBuf.Length();
                toolBuf._( FmtInstLineNoPrefix )._( instLineNumber, 2 )._( FmtInstLineNoPostfix );
                for ( int i= indent; i > 0; i-- )
                    toolBuf._( FmtInstIndent );
            }

            /** ************************************************************************************
             * Appends spaces to move to the given tabStop (but at least one). 
             * @param tabStop     The tab stop position to go to </param>
             **************************************************************************************/
            protected static void instTabStop( int tabStop )
            {
                do    { toolBuf._( ' ' ); } while ( toolBuf.Length() <= instLineBeginIdx + tabStop  );
            }


            /** ************************************************************************************
             * Appends type information at the end of the line and starts a new line. 
             * @param type     The type to append in the log  </param>
             **************************************************************************************/
            protected static void instTabTypeAndNewLine( Type type )
            {
                if ( type != null )
                {
                    do    { toolBuf._( ' ' ); } while ( toolBuf.Length() <= instLineBeginIdx + instTypeTabStop  );
                    toolBuf._( FmtInstTypePrefix )._( type.Name )._( FmtInstTypePostfix );
                }
                instNewLine();
            }

        #endif  // !(ALOX_WP71 || ALOX_WP8 || ALOX_NO_REFLECTION)


        #if !ALOX_NO_XML

            /** ************************************************************************************
             * Dump a XML document into our Buffer. 
             * @param xDocument      The XDocument to be logged. </param>
             * @param headLine       The headline to log. </param>
             **************************************************************************************/
            protected static void xml( XDocument xDocument, String headLine)
            {
                // create/clear toolBuf
                if ( toolBuf == null )
                    toolBuf= new AString( 1024 );
                else
                    toolBuf.Clear();

                // print headline
                if ( headLine != null )
                    toolBuf._( headLine ).NewLine();

                // log elements
                foreach ( XElement el in xDocument.Elements() )
                    xmlElement( el, null, headLine != null ? 1 : 0 );
            }

            /** ************************************************************************************
             * Internal function for logging an XElement. 
             * @param xe           The XElement to log. </param>
             * @param headLine     The headline to log. </param>
             * @param indent       The indentation to Log. </param>
             **************************************************************************************/
            protected static void xmlElement( XElement xe, String headLine, int indent )
            {
                // print headline
                if ( headLine != null )
                    toolBuf._( headLine ).NewLine();

                // print name
                toolBuf.InsertChars( ' ',  indent * 2 )._( xe.Name.ToString() );
                if ( !xe.HasElements )
                    toolBuf._( '=' )._( '\"' )._(xe.Value)._( '\"' );

                // print attributes
                if ( xe.HasAttributes )
                    foreach ( var attribute in xe.Attributes() )
                        toolBuf._( ' ' )._( attribute.Name.ToString() )._( '=' )._( '\"' )._( attribute.Value )._( '\"' );

                toolBuf.NewLine();

                // recursion
                foreach ( var element in xe.Elements() )
                    xmlElement( element, null, indent + 1 );
            }
        #endif //(!ALOX_NO_XML)
    #endif  // ALOX_DBG_LOG || ALOX_REL_LOG
} //class LogTools
} // namespace
