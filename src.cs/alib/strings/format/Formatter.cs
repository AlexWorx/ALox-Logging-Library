// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################


using System;
using System.Text;
using cs.aworx.lib.strings;
using System.Collections;
using System.Collections.Generic;
using cs.aworx.lib.lang;
using cs.aworx.lib.threads;

namespace cs.aworx.lib.strings.format  {

/** ************************************************************************************************
 * Writes formatted text into an \ref cs::aworx::lib::strings::AString "AString".
 *
 * While this class is abstract, only derived classes that support a specific format syntax can
 * be instantiated and used. Built-in formatters provided with \b %ALib are:
 * - \ref cs::aworx::lib::strings::format::FormatterPythonStyle  "FormatterPythonStyle", which mimics
 *   the [Python formatting syntax](https://docs.python.org/3.5/library/string.html#format-string-syntax)
 *   and
 * - \ref cs::aworx::lib::strings::format::FormatterJavaStyle    "FormatterJavaStyle", which mimics
 *   the formatting syntax of corresponding
 *   [Java class "Formatter"](http://docs.oracle.com/javase/8/docs/api/java/util/Formatter.html)
 *
 * One of the design goals of \b %ALib is to provide a library for (currently) three programming
 * languages \b C++, \b Java and \b C#, which allows to reach a certain level of source code
 * compatibility if used in cross-platform/language projects. Now, why do we provide
 * <b>Python Style</b> instead of to mimic what is coming with \b .Net languages like \b C#?
 *
 * The answer is that we considered <b>Python Style</b> to be more powerful. It is also more powerful
 * than the <b>Java Style</b> formatting syntax. But the latter is in its basics similar to
 * good old \c printf format string style and hence for \b %ALib a must have.
 * The good news is that in its very basics, <b>Python Style</b> is similar to \b .Net formatting.
 * This way, there is some "familiar basic syntax" available for everybody.<br>
 * Finally, it is worth to mention that the \b %ALib implementation of <b>Python Style</b> formatting
 * is extending the original standard even a little.
 *
 *
 * ##Concatenated Formatters And Concatenated Format Operations##
 *
 * In comparison to "usual", similar classes that are found in other libraries/languages, there
 * are two main differences with this class:
 * 1. This class supports the concatenation of formatters by passing an instance of
 *    a different derived type in the constructor. A formatter that has a (list of) concatenated
 *    other formatter(s) attached, allows to detect the provided format syntax by passing the format
 *    operation recursively to the concatenated formatter(s). Of-course this approach is limited to
 *    such syntax definitions that are not ambiguous. (...It works well with formatters
 *    \b %FormatterPythonStyle and \b %FormatterJavaStyle!)
 *
 * 2. Usually (in other libraries) the interface of formatting methods accept a dedicated
 *    format string and list of arguments to format. Method #Format of this class however
 *    expects just an argument list. The processing then is done as follows:
 *    The first argument in the list is tested to be a format string.  If it is, method #format
 *    will report how many arguments form the list have been "consumed" and formatting will continue
 *    with the first argument after the last consumed one. If the actual argument is not identified
 *    as a format string (tested with each concatenated formatter), the string is just appended to
 *    the target and formatting continues with the next argument in the list.<br>
 *    If at the end of this processing loop a single argument is left, then this is not checked
 *    for being a format string. Instead, it will be just appended to the target as is.
 *    An argument that potentially could be a format string is simply skipped (ignored) if it
 *    evaluates to \c null.
 *
 * This behaviour has the following consequences:
 * - No format string needs to be passed. In this case, the arguments are appended to the target
 *   \b %AString in their sequence order
 * - More than one format string (with according) arguments might be passed.
 * - The different format strings might even follow a different syntax.
 *
 * The biggest \b advantage of this implementation is that format strings and arguments might be
 * collected prior to invoking the formatter. Collection might happen at different places and times
 * in a process with the only restriction that not more or less arguments might be added to the
 * overall list than referred to in the format string. In other words, format strings have to
 * be well set in respect to the arguments they consume.
 *
 * The biggest <b>potential issue</b> of this approach is that a string argument that is not meant
 * to be a format string might be accidentally interpreted as one if it happens to contain one or
 * more placeholder characters that are matched by one of the concatenated formatters. (In this case it
 * it is likely that the format is invalid and an error is written. In debug mode, even an assertion
 * might be raised). To avoid such ambiguity, the following considerations have to be taken into
 * account when passing arguments:
 * - Ambiguities might only happen with string-type arguments. Other types that are converted to
 *   string representations are never considered a potential format string.
 * - Strings that contain a newline-character (ascii \b 0x0a) are not considered to be a format string.
 *   (Newline characters in a format string have to be escaped using a formatter-specific notation,
 *   e.g. \c "\n").
 * - A string-type argument that is the last in the list (or the only one) is safe
 *   (no ambiguity can occur) because the last argument is never checked for being a format string.
 * - %String-type arguments that do not contain placeholder characters defined by one of the formatters
 *   are safe.
 *
 * \attention
 *   <b>The rule that results from this is:</b><br>
 *   If none of the conditions mentioned above can be guaranteed, then the argument in question
 *   should be passed together with a preceding simple formatting string, for example,
 *   \c "{}" for \b %FormatterPythonStyle or
 *   \c "%s" in case of \b %FormatterJavaStyle.
 *
 * ##Choosing The %Formatter##
 * As elaborated above, there are two built-in formatter types and those can be concatenated.
 * Finally, there is the option to implement an own, custom formatter. For the undecided, the
 * recommendation is to use <b>Java Style</b> for simple, quick <c>printf-</c> like formatting
 * and to choose <b>Python Style</b> in the moment formatting requirements get more complex.
 * A special case and good sample for the use of \b ALib formatting features is found in the
 * [ALox Logging Library](https://github.com/AlexWorx/ALox-Logging-Library). Here the special
 * situation is that \b %ALox itself is a library and hence exposes its formatters used to
 * users. Therefore \b %ALox (by default) uses a <b>Python Style</b> formatter and a concatenated
 * <b>Java Style</b> version. This way, simple samples will work from scratch for users of all
 * three languages!
 *
 * ##Usage##
 * The class is abstract, hence only derived types can be instantiated.
 * Those types are constructed with optionally providing a concatenated instance of another
 * derived type. The optional concatenated formatter object has a lower priority in respect to
 * detecting a format string.
 *
 * Two overloaded methods \b Format exists:
 * - The first method accepts a target \b AString and a variadic list of arguments. This method
 *   can be used if the format string(s) and all arguments are available/known at the point of
 *   invocation.
 * - The second method accepts a target \b AString and a list of arguments. This method
 *   can be used if format string(s) and arguments are collected prior to the final invocation
 *   of the formatter.
 *
 * \note
 *   The use of this class is not "thread safe".
 *
 * ##Implementing A Custom %Formatter##
 * To implement a custom formatter, the abstract methods found in this class have to be implemented.
 * With class
 * \ref cs::aworx::lib::strings::format::FormatterStdImpl "FormatterStdImpl" a - still abstract -
 * descendant class is provided. This class implements method #format but introduces a set of
 * new abstract methods to overwrite. Although, those are more methods, these methods are probably
 * more simple to implement and therefore deriving from this class might be considered for new
 * custom types.
 *
 * The two built-in <b>Formatter</b>s provided with \b %ALib,
 * \ref cs::aworx::lib::strings::format::FormatterPythonStyle  "FormatterPythonStyle" and
 * \ref cs::aworx::lib::strings::format::FormatterJavaStyle    "FormatterJavaStyle" derive from
 * \b %FormatterStdImpl and copying the source code of one of them might be a good start for
 * implementing a custom type.
 **************************************************************************************************/
public abstract class Formatter
{
    // #############################################################################################
    //  protected fields
    // #############################################################################################
        /** A list of boxes. This is reset with every new invocation of variadic argument version of
         *  method #Format   */
        protected            List<Object>         boxes;

        /** The currently parsed formatted string (local as member/reused object). */
        protected            Substring            lamFormatString                 = new Substring();

        /**
         * A static, global instance which is used by ALib internally (e.g. for formatting
         * \ref cs::aworx::lib::lang::Report "Report" messages).
         * Applications can acquire and use this instance using #AcquireDefault and #ReleaseDefault.
         */
        protected static     Formatter            defaultFormatter;

        /** Lock to protect access to #defaultFormatter. Used by #AcquireDefault and
         *  #ReleaseDefault. */
        protected static     ThreadLock           defaultFormatterLock           = new ThreadLock();



    // #############################################################################################
    //  public fields
    // #############################################################################################
        /**
         *  An optional, next formatter. If set, this formatter will be invoked for a format string
         *  that does not contain recognized placeholders.
         *  \attention
         *    This field is public and not further maintained by this class. Setting the field lies
         *    completely in the responsibility of the user. E.g. cyclic settings must be avoided.
         */
        public         Formatter                   Next;

    // #############################################################################################
    //  static interface
    // #############################################################################################
        /**
         * Locks and returns the global, default formatter for general purpose use.
         * A subsequent call to #ReleaseDefault has to follow.
         * The formatter is of type
         * \ref cs::aworx::lib::strings::format::FormatterPythonStyle "FormatterPythonStyle". Other formatters
         * might be attached to the one returned (chained) to support different format
         * standards.
         *
         * @return The global formatter singleton.
         */
        public static Formatter                   AcquireDefault()
        {
            #if DEBUG
                defaultFormatterLock.RecursionWarningThreshold= 1;
            #endif
            defaultFormatterLock.Acquire();

            if ( Formatter.defaultFormatter == null )
                Formatter.defaultFormatter= new FormatterPythonStyle();

            return Formatter.defaultFormatter;
        }


        /** Releases the previously default formatter singleton, previously retrieved with
         *  #AcquireDefault */
        public static void                         ReleaseDefault()
        {
            defaultFormatterLock.Release();
        }


    // #############################################################################################
    //  Interface
    // #############################################################################################

        /** ****************************************************************************************
         * Variadic template method that accepts an target \b %AString and a list of applicable
         * arguments.
         *
         * @param target   An AString that takes the result.
         * @param args     The variadic list of arguments to be used with formatters.
         * @tparam BoxedObjects Variadic template type list.
         ******************************************************************************************/
        public virtual
        void    Format( AString target, params Object[] args  )
        {
            // create argument objects using implicit constructor invocation
            if (boxes == null)
                boxes = new List<Object>();
            else
                boxes.Clear();

            for (int i = 0; i < args.Length; ++i)
                boxes.Add(args[i]);

            Format( target, boxes );
        }


        /** ****************************************************************************************
         * Applies the given arguments to the target using this and optionally provided
         * sub-formatter(s).
         *
         * @param target     An AString that takes the result.
         * @param args       The objects to apply.
         ******************************************************************************************/
        public virtual
        void    Format( AString target, List<Object> args )
        {
            // initialize formatters
            Formatter formatter= this;
            do
                formatter.initializeFormat();
            while( (formatter= formatter.Next) != null );

            // loop over boxes
            int argIdx= 0;
            while ( argIdx < args.Count - 1 )
            {
                // any sort of string?
                Object actual= args[argIdx++];
                lamFormatString.SetNull();
                if (actual is String)    lamFormatString.Set((String)    actual);
                if (actual is Substring) lamFormatString.Set((Substring) actual);

                if( lamFormatString.IsNotNull() )
                {
                    // try each formatter unless one succeeds
                    int  qtyConsume= 0;
                    formatter= this;
                    while(    ( qtyConsume= formatter.format( target, lamFormatString, args, argIdx ) ) == 0
                           &&  (formatter= formatter.Next) != null )
                    {}

                    // no formatter reacted?
                    if( qtyConsume == 0 )
                        // we just append the string...
                        target._NC( lamFormatString );
                    else
                        // ...otherwise arguments were consumed
                        argIdx+=  qtyConsume;
                }

                // not a string: use ToString method, which might have been overwritten by the user.
                else
                    target._( actual );
            }

            // the last argument was not consumed?
            if ( argIdx == args.Count - 1 )
                target._NC( args[argIdx] );

        }

        /** ****************************************************************************************
         * Virtual bot not abstract method which is invoked with each invocation of
         * \ref cs::aworx::lib::strings::format::Formatter::Format "Formatter.Format".
         * The default implementation does nothing.
         ******************************************************************************************/
        protected virtual void                initializeFormat()                                  {}

        /** ****************************************************************************************
         * The abstract format method that needs to be implemented by descendants.
         * Note that parameter \p startIdx and the demanded return value together comprise the
         * possibility to use more than one formatter in parallel and to perform multiple format
         * operations on suitable argument lists. This demands the implementation of this method to
         * \b not copy the format string to the \p target in the case that no 'escape sequence'
         * was found. For further information, see the general documentation of this class.
         *
         * @param target        The %AString that takes the result.
         * @param formatString  The format string.
         * @param args          The objects to apply.
         * @param startArgument The first object in \p args to convert.
         *
         * @return The number of args consumed.
         ******************************************************************************************/
        protected abstract int format(  AString       target,
                                        Substring     formatString,
                                        List<Object>  args,
                                        int           startArgument );

} // class Formatter

} // namespace / EOF
