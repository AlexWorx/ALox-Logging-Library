// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2019 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################


package com.aworx.lib.strings.format;
import com.aworx.lib.strings.AString;
import com.aworx.lib.strings.Substring;
import com.aworx.lib.strings.NumberFormat;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.Locale;

import com.aworx.lib.time.Ticks;
import com.aworx.lib.lang.Alignment;


/** ************************************************************************************************
 * Base class for \b %ALib built-in formatters.
 * This class implements abstract method
 * \ref com.aworx.lib.strings.format.Formatter.format "Formatter.format" and introduces a set of
 * new abstract methods that have to be implemented by descendants.
 *
 * The documentation of the class is split into two sections: The first addresses users of
 * descendent classes, the second provides information on how to extend this class to implement
 * a custom formatter.
 *
 * ## Documentation For Users Of Derived Classes ##
 * The following public fields may be modified with descendent types:
 *
 * - Derived formatter types will set attributes in fields #defaultNumberFormat and
 *   #alternativeNumberFormat to reflect the default behavior of their formatting syntax.<br>
 *   Users of derived formatters may modify these attributes prior to performing a format operation
 *   to change those defaults. While this leads to a deviation of the formatting standard, it may be
 *   used instead of providing corresponding syntactic information within each and every replacement
 *   field of the format strings. Some modifications may not even be possible with just using
 *   the format specification.
 *
 * - Field #writeALibErrorReports defaults to \c true and may be used to disable
 *   \ref com.aworx.lib.lang.Report "ALib error reports" on illegal formed format strings.
 *
 * - Field #writeErrorsToTargetString defaults to \c true and may be used to disable
 *   the writing of of error messages about illegal formed format strings to the target string.
 *
 *
 * ## Documentation For Implementing Derived, Custom Formatters ##
 *
 * Derived types need to set default values for attributes in fields
 * #defaultNumberFormat and #alternativeNumberFormat within their constructor once - according
 * to defaults specified by the formatting syntax.
 * This should not be repeated per format operation. This way users of the type are allowed
 * to change such default setting (even if they this may the formatter deviates from the standard
 * it implements).
 *
 * All fields of this class named with prefix \c pha (for example, #phaAlignment) together comprise
 * the set of formatting attributes which can be modified by placeholder semantics of the format string.
 * If further attributes are needed, derived types are free to define custom members to store such
 * attributes. Implementations provided with \b %ALib give such extended attributes the prefix
 * \c phaExt.
 *
 * When parsing a placeholder of a format string, abstract method #parsePlaceholder
 * may set field #phaFormatSpec to reflect a format-specific portion the placeholder string.
 * This then can be checked in an overloaded version of #writeCustomFormat.
 * In the Java version of \b %ALib, the default implementation of this method does not forward
 * this to a Java specific, "native" interface as it is done in C# and C++ versions.
 * Instead, the only thing that is done in this method is that the argument is checked for being
 * a date/time object and custom format string is processed using public field #dateTimeFormat.
 * \note
 *   This concept (of writing a custom format specification to #phaFormatSpec) is implemented with class
 *   \ref com.aworx.lib.strings.format.FormatterPythonStyle "FormatterPythonStyle" as the
 *   "Python format mini language" supports such custom format specifications. Class
 *   \ref com.aworx.lib.strings.format.FormatterJavaStyle "FormatterJavaStyle" does \b not support
 *   this mechanism.
 *
 * The following describes the formatting process in detail (the implementation of method #format)
 * and this way helps to understand what is required from the implementation of the abstract methods:
 *
 * 1.  A newline character check is made and formatting is aborted if one was found
 *     (as proposed by contract with parent class).
 *
 * 2.  Method parameters are stored in fields #ptargetString, #pformatString, #parguments and
 *     #pargOffset. This way, the parameters can be accessed from any implemented method without
 *     the need of passing them as parameters once more.<br>
 *     In addition, field #parser is initialized. This \b Substring is used to parse
 *     the format string. Parsed portions will be consumed from the front of the string.
 *     Finally fields #argsConsumed and #nextAutoIdx are initialized to value \c 0.
 *
 * 3.  <b>Start of the loop</b> to find and process placeholders in the format string.
 *
 * 4.  Abstract method #findPlaceholder is invoked. If this fails (no further placeholder was found)
 *     parsing stops. If, and only if, a placeholder was found before, the rest of the string
 *     in #parser is written and abstract method #replaceEscapeSequences is invoked for this rest.
 *
 * 5.  The portion of the format string before the placeholder position is written and abstract
 *     method #replaceEscapeSequences is invoked on this portion (if not empty).
 *
 * 6.  Method #resetPHAs is invoked, to reset the attributes that will be parsed in the next
 *     step. The values that are set are implementation specific and need to reflect the
 *     default formatting options if no specific options are given in the format string.
 *
 * 7.  Abstract Method #parsePlaceholder is invoked to parse and consume tokens from string #parser
 *     and while doing this, to store the parsed format attributes in the fields with
 *     name prefix \c pha (or extended attributes of a derived formatter type).<br>
 *     If an argument (positional) index is found during parsing, then method
 *     #setArgument is to be invoked by abstract method \b %parsePlaceholder providing that index.<br>
 *     If the format syntax of the formatter contains a separated format specification string
 *     (a substring of the placeholder string),  then the method may store such format
 *     substring in field
 *     \ref com.aworx.lib.strings.format.FormatterStdImpl.phaFormatSpec "phaFormatSpec".
 *
 * 8.  Next, it is checked if an argument was set by \b %parsePlaceholder. If not, #setArgument
 *     is invoked providing \c -1 for the index to indicate auto-indexing.
 *     \note
 *       If auto-indexing should be implemented differently than done with default method
 *       #setArgument, then a custom formatter might either override the method or,
 *       in the case no index is given in the format string, just
 *       set fields
 *       \ref com.aworx.lib.strings.format.FormatterStdImpl.phaArgument    "phaArgument" and
 *       \ref com.aworx.lib.strings.format.FormatterStdImpl.phaArgumentIdx "phaArgumentIdx"
 *       already in \b %parsePlaceholder according to its own strategy
 *
 * 9.  Method #preAndPostProcess is invoked with parameter \p{startIdx} equalling \c -1
 *     (indicating pre-processing). This allows for example to insert tab fill-characters
 *     (tab stops) prior to writing the contents of the field.
 *
 * 10. Method  #writeCustomFormat is invoked. This allows derived formatters to write arguments in a
 *     custom way. If the method returns \c true, the loop is continued ( &rarr; Step 4.). <br>
 *     The default implementation checks if a format specification was stored in #phaFormatSpec
 *     and if yes, if #phaArgument represents a date. If so, field #dateTimeFormat is used
 *     to write the date/time value to the target string and \c true is returned.<br>
 *
 * 11. Again, if a format specification was stored in
 *     \ref com.aworx.lib.strings.format.FormatterStdImpl.phaFormatSpec "phaFormatSpec"
 *     method #parseStdFormatSpec is invoked which needs to set further attributes
 *     in the \b %Placeholder object according to to the standard format specification of the formatter.
 *
 * 12. Now, as all fields that represent formatting attributes (fields with prefix \c pha) are well
 *     set (or kept with their defaulted value), method #checkStdFieldAgainstArgument is invoked.
 *     This method is virtual but not abstract. Its default implementation checks the
 *     placeholder attributes against the provided argument type and raises an error if the
 *     argument does not fit to the placeholder format specification.
 *
 * 13. Method #writeStdArgument is invoked. This method is virtual but not abstract.
 *     Its default implementation writes the argument value formatted according to the attribute
 *     fields.
 *
 * 14. Finally #preAndPostProcess is invoked with parameter \p{startIdx} pointing to the first
 *     character in #ptargetString of the argument written.
 *     Here, actions like case conversion might be done on the field written.
 *
  * 14. End of loop ( &rarr; Step 4.)
 *
 **************************************************************************************************/
public abstract class FormatterStdImpl extends Formatter
{
    // #############################################################################################
    //  protected fields
    // #############################################################################################
        /** The name of the formatter as provided in the constructor. Used for generating
         *  error messages. */
        protected String                 formatterName;

        /** The target string as provided with method #format. */
        protected AString                ptargetString;

        /** The length of the target string before adding the formatted contents.*/
        protected int                    targetStringStartLength;

        /** The format string as provided with method #format. */
        protected Substring              pformatString                             = new Substring();

        /** The list of arguments provided with method #format.     */
        protected ArrayList<Object>      parguments;

        /** The offset of the first argument to use. Provided with method #format. */
        protected int                    pargOffset;

        /** The current (remaining) format string.      */
        protected Substring              parser                                   = new Substring();

        /** The number of arguments consumed by the current format string.  */
        protected int                    argsConsumed;

        /** Counter for auto-indexed arguments.     */
        protected int                    nextAutoIdx;

        /** A buffer to be used when writing aligned fields.   */
        protected AString                fieldBuffer                                = new AString();

        /** A reused date object */
        Date tmpDate= new Date();


    // #############################################################################################
    //  Placeholder attribute members
    // #############################################################################################

        /** Denotes the requested value type of placeholders. */
        protected enum  PHType
        {
            NotGiven        , ///< The default
            String          , ///< %String type requested

            Character       , ///< Converts a given character or integer number to the corresponding
                              ///< unicode character before printing.

            // Integer types
            IntBase10       , ///< Outputs a given number in base 10. The default.
            IntBinary       , ///< Outputs a given number in base 2.
            IntOctal        , ///< Outputs a given number in base 8.
            IntHex          , ///< Outputs a given number in base 16.

            // Floating types
            Float           , ///< Outputs a number in floating point format.

            // Bool
            Bool            , ///< Writes "true" or "false".
            HashCode        , ///< Writes raw box data as hex.

            // special
            Fill            , ///< Writes #phaFillChar x-times. Used with python-style conversion
                              ///< <b>{!Fill[C]}</b>
        }

    /** The type of the attribute as specified in the placeholder.
         *  This is set to
         *  \ref com.aworx.lib.strings.format.FormatterStdImpl.PHType.NotGiven "PHType.NotGiven"
         *  in default implementation of #resetPHAs. */
        protected PHType                      phaType;

        /** The current Box.
         *  This is set by #parsePlaceholder if explicit indexing is used. Otherwise by #format which
         *  invokes #setArgument if #parsePlaceholder did not set it yet.
         *  Set to \c null in default implementation of #resetPHAs. */
        protected Object                      phaArgument;

        /** The positional index of the current #phaArgument.
         *  This is set by #parsePlaceholder if explicit indexing is used. Otherwise by #format which
         *  invokes #setArgument if #parsePlaceholder did not set it yet.
         *  Set to \c -1 in default implementation of #resetPHAs. */
        protected int                         phaArgumentIdx;

        /** The index of the previous argument. Used when addressing previous argument
         *  number (eg. in Java formatting style this could be "%<$...").
         *  This is set to #phaArgumentIdx in default implementation of #resetPHAs. */
        protected int                         phaPreviousArgumentIdx;

        /** The portion of the replacement field that represents the format specification.
         *  This field might be set in method #parsePlaceholder and consumed in methods
         *  #writeCustomFormat and #parseStdFormatSpec.<br>
         *  This field is nulled in default implementation of #resetPHAs. */
        protected Substring                   phaFormatSpec                       = new Substring();

        /** The number format object for the actual attribute. With method #resetPHAs values found
         *  in object #defaultNumberFormat will be copied into this. */
        protected NumberFormat                phaNF                            = new NumberFormat();

        /** The (minimum) width of the output.
         *  This is set to \c 0 in default implementation of #resetPHAs. */
        protected int                         phaWidth;


        /** If not negative, the string representation of the argument is cut prior to
         *  applying any field operation. It could be also named "precision", hence
         *  the number of characters to show - even if the field will be wider.
         *  This is set to \c -1 in default implementation of #resetPHAs. */
        protected int                         phaCutContent;

        /** If true, an alignment was explicitly specified.
         *  This is set to \c false in default implementation of #resetPHAs. */
        protected boolean                     phaAlignmentSpecified;

        /** The alignment of the contents within a field.
         *  This is set to \ref com.aworx.lib.lang.Alignment.LEFT "Alignment.LEFT" in default
         *  implementation of #resetPHAs. */
        protected Alignment                   phaAlignment;

        /** The filling character for fields that are larger than their content.
         *  Method #resetPHAs will set this to <c>' '</c>. */
        protected char                        phaFillChar;

        /** Forces the padding to be placed after the sign (if any) but before the digits.
         *  This is used for printing fields in the form ‘+000000120'.
         *  This alignment option is only valid for numeric types.
         *  Set to \c false in default implementation of #resetPHAs. */
        protected boolean                     phaSignPaddingMode;

        /** Used with binary, octal, or hexadecimal output. Specifies that the output will be
         *  prefixed by strings found in fields
         *  \ref com.aworx.lib.strings.NumberFormat.binLiteralPrefix "binLiteralPrefix",
         *  \ref com.aworx.lib.strings.NumberFormat.hexLiteralPrefix "hexLiteralPrefix" or
         *  \ref com.aworx.lib.strings.NumberFormat.octLiteralPrefix "octLiteralPrefix" which
         *  default to  \c "0b", \c "0o" and \c "0x".
         *  Set to \c false in default implementation of #resetPHAs. */
        protected boolean                     phaWriteBinOctHexPrefix;

        /** Can be \c true for float-types. If \c true, the value is multiplied with 100 and
         *  a percentage symbol \c '\%' is printed after the value.
         *  Set to \c false in default implementation of #resetPHAs. */
        protected boolean                     phaIsPercentage;

        /** This is the (format specific) type code of the current format operation.
         *  Used only to display error messages. May be used differently in derived classes.
         *  Is nulled in default implementation of #resetPHAs. */
        protected char                        phaTypeCode;


    // #############################################################################################
    //  public fields
    // #############################################################################################
        /**
         * This number format is used to store default attributes for formatting numbers.
         * Likewise #alternativeNumberFormat, it is never used directly for formatting.
         * Instead, at the beginning of parsing a next
         * placeholder field, values are copied to #phaNF. During the parsing process, values
         * are then modified only in #phaNF, probably taken from #alternativeNumberFormat.
         *
         * This object is initialized in the constructor (of descendants) once to meet the formatting
         * defaults of the corresponding specification.
         *
         * \note
         *   Changing attribute values of this object allows to change the default formatting
         *   options of numbers!
         */
        public NumberFormat            defaultNumberFormat                     = new NumberFormat();

        /**
         * This number format is used to store alternative attributes. Likewise #defaultNumberFormat,
         * it is never used directly for formatting.
         * Instead when processing the placeholder syntax, alternatives get copied from either this
         * object or from #defaultNumberFormat.
         *
         * This object is initialized in the constructor (of descendants) once to meet the formatting
         * defaults of the corresponding specification.
         *
         * Not all fields in this object are used. The ones used are:
         * <p>
         * - Locale-specific versions of floating point separators:
         *   - \ref com.aworx.lib.strings.NumberFormat.decimalPointChar   "decimalPointChar"
         *   - \ref com.aworx.lib.strings.NumberFormat.thousandsGroupChar "thousandsGroupChar"
         *
         *   These are retrieved according to the current locale once in the constructor. To
         *   change the locale, these fields can be changed.
         *
         * - Lower case versions of floating point literals:
         *   - \ref com.aworx.lib.strings.NumberFormat.exponentSeparator "exponentSeparator"
         *   - \ref com.aworx.lib.strings.NumberFormat.INFLiteral        "INFLiteral"
         *   - \ref com.aworx.lib.strings.NumberFormat.NANLiteral        "NANLiteral"
         *
         * - Lower case versions of prefix literals that indicate the base of integer values:
         *   - \ref com.aworx.lib.strings.NumberFormat.binLiteralPrefix "binLiteralPrefix"
         *   - \ref com.aworx.lib.strings.NumberFormat.hexLiteralPrefix "hexLiteralPrefix"
         *   - \ref com.aworx.lib.strings.NumberFormat.octLiteralPrefix "octLiteralPrefix"
         */
        public NumberFormat            alternativeNumberFormat                 = new NumberFormat();

        /** Flag that causes the creation of \b %ALib error reports on format syntax errors, argument
         *  type errors, etc.
         *  Defaults to \c true. (Ignored in release compilations. see class
         *  \ref com.aworx.lib.lang.Report "Report" for more information.)                */
        public SimpleDateFormat        dateTimeFormat       = new SimpleDateFormat("", Locale.ROOT);

        /** Flag that causes the creation of \b %ALib error reports on format syntax errors, argument
         *  type errors, etc.
         *  Defaults to \c true. (Ignored in release compilations. see class
         *  \ref com.aworx.lib.lang.Report "Report" for more information.)                */
        public boolean                 writeALibErrorReports                                 = true;

        /** Flag that causes error messages to be written into the target string.
         *  Defaults to \c true. */
        public boolean                 writeErrorsToTargetString                             = true;

    // #############################################################################################
    //  Constructor/destructor
    // #############################################################################################
        /** ****************************************************************************************
         * Constructor.
         * @param formatterClassName The name of the derived class. Used to generate error messages
         *              including a link into the online documentation. (Therefor
         *              has to be the exact name.
         ******************************************************************************************/
        public FormatterStdImpl( String formatterClassName )
        {
            formatterName = formatterClassName;
            alternativeNumberFormat.setFromLocale();

            alternativeNumberFormat.exponentSeparator=  "e";
            alternativeNumberFormat.NANLiteral       =  "nan";
            alternativeNumberFormat.INFLiteral       =  "inf";
        }

        /** ****************************************************************************************
         * Clones the settings from the given formatter.
         * @param reference  The formatter to copy settings from.
         ******************************************************************************************/
        public void    cloneSettings( FormatterStdImpl reference )
        {
            defaultNumberFormat    .set( reference.defaultNumberFormat     );
            alternativeNumberFormat.set( reference.alternativeNumberFormat );

            writeALibErrorReports=        reference.writeALibErrorReports;
            writeErrorsToTargetString=    reference.writeErrorsToTargetString;
        }


    // #############################################################################################
    //  Implementation of abstract interface of parent class Formatter
    // #############################################################################################

        /** ****************************************************************************************
         * Implemented abstract format method which invokes a set of new abstract methods
         * as described in the main documentation of this class.
         *
         * @param targetString  An AString that takes the result.
         * @param formatString  The format string.
         * @param arguments     The objects to convert.
         * @param argOffset     The first object in \p{arguments} to use.
         *
         * @return The number of args consumed.
         ******************************************************************************************/
        @Override
        protected
        int     format( AString            targetString,
                        Substring          formatString,
                        ArrayList<Object>  arguments,
                        int                argOffset        )
        {
            // check for newline. This indicates that this is not a formatString string
            if( formatString.indexOf('\n') >= 0 )
                return 0;

            // save parameters/init state
            this.ptargetString=             targetString;
            this.targetStringStartLength=   targetString.length();
            this.pformatString.set( formatString );
            this.parguments=                arguments;
            this.pargOffset=                argOffset;

            // initialize state info
            nextAutoIdx=        0;
            argsConsumed=       0;

            parser=             formatString;

            for(;;)
            {
                int actLength= targetString.length();

                // find start of esc
                int escStart= findPlaceholder();
                if ( escStart < 0 )
                {
                    // write rest of formatString string (only if we had consumed before)
                    if( argsConsumed > 0 && parser.length() > 0 )
                    {
                        targetString._NC( parser );
                        replaceEscapeSequences( actLength );
                    }
                    return argsConsumed;
                }

                // write string before ESC code
                if ( escStart == 0 )
                    parser.consumeChars(1);
                else
                {
                    targetString._NC( parser.buf, parser.start, escStart );
                    parser.consumeChars( escStart + 1 );
                    replaceEscapeSequences( actLength );
                }

                // get and clean field attributes
                resetPHAs();

                // invoke abstract method for parsing the attributes
                if ( !parsePlaceholder() )
                    return argsConsumed;

                // If no position was set in the field format string, automatically use next parameter
                if ( phaArgumentIdx < 0 )
                    if ( !setArgument( -1, false ) )
                        return argsConsumed;

                // write field
                if( preAndPostProcess( -1, null ) )
                {
                    int actIdx= targetString.length();
                    if ( !writeCustomFormat() )
                    {
                        // standard format
                        if (    ( phaFormatSpec.isNotEmpty()  && !parseStdFormatSpec() )
                             || !checkStdFieldAgainstArgument() )
                            return argsConsumed;

                        // write argument
                        writeStdArgument();
                    }

                    preAndPostProcess( actIdx, null );
                }

            }// main loop searching next escape sequence
        }

    // #############################################################################################
    //  Helper methods
    // #############################################################################################

        /** ****************************************************************************************
         * Helper method to detect if #phaArgument holds an integral type.
         * @return \c true if #phaArgument holds a signed integral type.
         ******************************************************************************************/
        boolean isIntegral()
        {
            return      phaArgument instanceof Integer
                    ||  phaArgument instanceof Long
                    ||  phaArgument instanceof Short
                    ||  phaArgument instanceof Byte   ;
        }


        /** ****************************************************************************************
         * Extracts an integral value from #phaArgument. Must be used only if #isIntegral
         * returned \c true.
         * @return The contents of #phaArgument casted as \c long.
         ******************************************************************************************/
        long getIntegral()
        {
            return      phaArgument instanceof Integer  ? ((Integer) phaArgument).longValue()
                    :   phaArgument instanceof Long     ? ((Long   ) phaArgument).longValue()
                    :   phaArgument instanceof Short    ? ((Short  ) phaArgument).longValue()
                    :   phaArgument instanceof Byte     ? ((Byte   ) phaArgument).longValue()
                    :   0;
        }

    // #############################################################################################
    //  Introduction of new, partly abstract methods to be implemented (or optionally overwritten)
    //  by descendents.
    // #############################################################################################

        /** ****************************************************************************************
         * Abstract method to search the next index of an argument placeholder in the remaining
         * substring (field #parser) of the format string.
         *
         * @return The index found, \c -1 if not found.
         ******************************************************************************************/
        protected abstract int           findPlaceholder();

        /** ****************************************************************************************
         * Overridable method to clean and reset the fields representing the current placeholder
         * attributes (those with name prefix \c pha) prior to parsing them.
         *
         * The default implementation sets all pha-fields as documented per field.
         * \note
         *   Derived classes (aka the specific formatter classes) are to invoke this (parent)
         *   implementation first and then to make some own adjustments to meet the defaults that
         *   apply to the formatting specification implemented by the derived class and - if this
         *   applies - also to reset extended attributes of the derived formatter type.
         ******************************************************************************************/
        protected  void                  resetPHAs()
        {
            phaNF.set( defaultNumberFormat );
            phaNF.hexLowerCase          = true;
            phaType=                    PHType.NotGiven;
            phaPreviousArgumentIdx=     phaArgumentIdx;
            phaArgument=                null;
            phaWidth=                    0;
            phaArgumentIdx=
            phaCutContent=              -1;

            phaAlignmentSpecified=      false;
            phaAlignment=               Alignment.LEFT;
            phaSignPaddingMode=         false;
            phaFillChar=                 ' ';
            phaWriteBinOctHexPrefix=    false;
            phaIsPercentage=            false;
            phaTypeCode=                '\0';
            phaFormatSpec.setNull();
        }



        /** ****************************************************************************************
         * Abstract method to parse the format definition at the start of string
         * #parser and set the placeholder attributes accordingly.<br>
         * Field #phaFormatSpec might be set by this method to portion of the placeholder format
         * string. If so, methods #writeCustomFormat and #parseStdFormatSpec are used to then parse
         * this portion of the placeholder string.
         *
         * @return \c true on success, \c false on errors.
         ******************************************************************************************/
        protected abstract boolean       parsePlaceholder();

        /** ****************************************************************************************
         * Virtual method that may write an argument using a custom method/format.
         * This default implementation checks if #phaFormatSpec is set and object #phaArgument
         * represents a date/time value.
         * If so, field #dateTimeFormat is used to format the argument and \c true is returned,
         * what causes method #format (which invokes this method) to
         * continue with the next replacement field.
         * If \c false is returned, method #format continues the field processing by invoking
         * #parseStdFormatSpec, #checkStdFieldAgainstArgument and #writeStdArgument.
         *
         * @return \c true if #phaArgument was written, \c false otherwise.
         ******************************************************************************************/
        protected  boolean       writeCustomFormat()
        {
            if ( phaFormatSpec.isEmpty() )
                return false;

            Date date= null;
                 if( phaArgument instanceof Date  )   date= (Date) phaArgument;
            else if( phaArgument instanceof Ticks ) { date= tmpDate; tmpDate.setTime( ((Ticks)phaArgument).inEpochMillis() ); }


            if( date == null )
                return false;

            dateTimeFormat.applyPattern( phaFormatSpec.toString() );
            ptargetString._( dateTimeFormat.format( date ) );

            return true;
        }


        /** ****************************************************************************************
         * Abstract method to parse the format specification for standard types (those that
         * are not processed by #writeCustomFormat). This method may be left empty
         * (just return constant \c true) if method #parsePlaceholder will never sets
         * field #phaFormatSpec.
         *
         * @return \c true on success, \c false on errors.
         ******************************************************************************************/
        protected abstract boolean      parseStdFormatSpec();



        /** ****************************************************************************************
         * Virtual method invoked after #parseStdFormatSpec and before #writeStdArgument().
         * The default implementation checks the settings of placeholder attribute values
         * (fields with prefix \c pha), which were set by #parsePlaceholder and optionally by
         * #parseStdFormatSpec, against the type of the argument given.
         *
         * If type and format information is missing in the format string, reasonable default
         * values are set depending on the type of the argument.
         *
         * If the argument type contradicts the replacement field type, #errorFormatString is
         * invoked.
         *
         * @return \c true if OK, \c false if replacement should be aborted.
         ******************************************************************************************/
        protected  boolean      checkStdFieldAgainstArgument()
        {
            // types boolean and hashcode always works!
            if(   phaType == PHType.Bool
               || phaType == PHType.HashCode )
                return true;


            if ( phaArgument instanceof Double || phaArgument instanceof Float  )
            {
                if( phaType == PHType.NotGiven )
                    phaType= PHType.Float;

                if(     phaType == PHType.Float )
                    return true;

                errorFormatString(   "Incompatible format code '" + phaTypeCode
                                   + "' for argument #"           + phaArgumentIdx
                                   + " which is of floatingpoint type" );

                return false;
            }


            if( isIntegral() )
            {
                if( phaType == PHType.NotGiven )
                    phaType= PHType.IntBase10;
                if(     phaType == PHType.IntBase10
                    ||  phaType == PHType.IntBinary
                    ||  phaType == PHType.IntOctal
                    ||  phaType == PHType.IntHex
                    ||  phaType == PHType.Float
                    ||  phaType == PHType.Character
                    ||  phaType == PHType.Fill
                    )
                {
                    return true;
                }

                errorFormatString(   "Incompatible format code '"  + phaTypeCode
                                   + "' for argument #"            + phaArgumentIdx
                                   + " which is of integer type" );
                return false;

            }

            if( phaArgument instanceof Character )
            {
                if( phaType == PHType.NotGiven )
                    phaType=   PHType.Character;
                if( phaType == PHType.Character )
                    return true;

                errorFormatString(   "Incompatible format code '"  + phaTypeCode
                                   + "' for argument #"            + phaArgumentIdx
                                   + " which is of character type"  );
                return false;
            }

            if( phaType == PHType.NotGiven )
                phaType= PHType.String;

            return true;
        }

        /** ****************************************************************************************
         * Virtual method to write the argument. The default implementation should be sufficient
         * for most derived formatter implementations, but of-course can be overridden and extended.
         ******************************************************************************************/
        protected  void         writeStdArgument()
        {
            // store actual target length to fix some float exceptional cases (inf, nan)
            int oldTargetLength= ptargetString.length();

            // write to temp buffer first, if we have a field width given
            AString target;

            if ( phaWidth > 0 )
            {
                target= fieldBuffer._();

                // set default alignment
                if(     !phaAlignmentSpecified
                     &&  phaType != PHType.String
                     &&  phaType != PHType.Character        )
                     phaAlignment= Alignment.RIGHT;
            }
            else
                target= ptargetString;

            int fieldStartIdx= target.length();


            // the main switch over the type
            switch( phaType )
            {
                case NotGiven:
                    com.aworx.lib.ALIB_DBG.ERROR( "Internal error: this should have been handled by method checkStdFieldAgainstArgument" );
                break;

                case String:
                    target._( phaArgument );
                break;

                case Bool:
                {
                   boolean value=     phaArgument instanceof Boolean ? ((Boolean) phaArgument).booleanValue()
                                   :  isIntegral()                   ? (getIntegral() != 0)
                                   :  phaArgument != null;
                   target._NC( value ? "true" : "false" );
                }
                break;

                case Character:
                {
                    char asChar =   phaArgument instanceof Character ? ((Character) phaArgument).charValue()
                                  : isIntegral()        ? (char) getIntegral()
                                  : '?';
                    target._( asChar );
                }
                break;


                case Fill:
                    target.insertChars( phaFillChar, (int) getIntegral() );
                break;

                case IntBase10:
                {
                    if (phaSignPaddingMode)
                        phaNF.decMinimumFieldWidth= phaWidth;


                    target._( getIntegral(), phaNF );
                }
                break;

                case IntBinary:
                case HashCode:
                case IntHex:
                case IntOctal:
                {
                    long value=  phaType == PHType.HashCode ? phaArgument.hashCode()
                                                            : getIntegral();

                    int digits= phaWidth;
                    if( phaWriteBinOctHexPrefix )
                    {
                        target._NC(phaType == PHType.IntOctal  ? phaNF.octLiteralPrefix :
                                   phaType == PHType.IntBinary ? phaNF.binLiteralPrefix :
                                                                 phaNF.hexLiteralPrefix       );
                        digits-= (target.length() - fieldStartIdx);
                        if( phaWidth > 0 && digits <= 0 )
                        {
                            target.setLength( fieldStartIdx + phaWidth );
                            break; // stop output, no space left
                        }
                    }
                    if ( digits < 0 )
                        digits= 0;

                         if( phaType == PHType.IntOctal)  target._Oct( value,  digits, phaNF );
                    else if( phaType == PHType.IntBinary) target._Bin( value,  digits, phaNF );
                    else                                  target._Hex( value,  digits, phaNF );
                }
                break;


                case Float:
                {
                    // get value
                    double value=   phaArgument instanceof Double ? ((Double) phaArgument).doubleValue()
                                  : phaArgument instanceof Float  ? ((Float ) phaArgument).doubleValue()
                                  : (double) getIntegral();
                    if( phaIsPercentage )
                        value*= 100.0;

                    if (phaSignPaddingMode)
                    {
                        // write sign upfront and set fill character to 0
                        long raw=  Double.doubleToRawLongBits( value );
                        if( raw != NumberFormat.bitsNaN)
                        {
                            // negative? -> turn positive
                            if ( (raw & NumberFormat.signMask) == NumberFormat.signMask )
                            {
                                ptargetString._( '-' );
                                phaWidth--;
                                value= -value;
                            }
                            else if( phaNF.plusSign != '\0' )
                            {
                                ptargetString._( phaNF.plusSign );
                                phaWidth--;
                            }
                            phaNF.plusSign= '\0';

                            if ( !phaNF.writeGroupChars || phaNF.thousandsGroupChar == '\0')
                                phaFillChar= '0';
                            else
                            {
                                // calculate integral part width
                                if ( phaWidth > 0 && !phaNF.forceScientific)
                                {
                                    phaNF.integralPartMinimumWidth= phaWidth - 1; // -1 == the dot

                                    if( phaNF.fractionalPartWidth >= 0 )
                                        phaNF.integralPartMinimumWidth-= phaNF.fractionalPartWidth;

                                    if( phaIsPercentage )
                                        phaNF.integralPartMinimumWidth--;

                                    // check
                                    if( phaNF.integralPartMinimumWidth <= 0)
                                        phaNF.integralPartMinimumWidth= 1;
                                }
                            }
                        }
                    }

                    target._( value, phaNF );

                    if( phaIsPercentage )
                        target._( '%' );


                    // if nan or inf was written, we fill with spaces
                    if (     phaSignPaddingMode
                        && (     target.indexOf(phaNF.NANLiteral, oldTargetLength) >= 0
                             ||  target.indexOf(phaNF.INFLiteral, oldTargetLength) >= 0 ) )
                        phaFillChar= ' ';

                }
                break;
            }

            // now do an 'intermediate post phase' processing
            preAndPostProcess( fieldStartIdx, target );


            // apply cutting
            if ( phaCutContent >= 0  &&   target.length() - oldTargetLength > phaCutContent  )
                target.setLength( oldTargetLength + phaCutContent );

            // if field mode, we have to apply the field buffer as a field to the real target now
            if( target ==  fieldBuffer )
                ptargetString.field()._NC( fieldBuffer ).field( phaWidth, phaAlignment, phaFillChar );

        }
        /** ****************************************************************************************
         * Virtual method to do pre- and post- processing of the field written.
         * Pre-processing could for example be adding tabulator spaces, letter case conversions,
         *
         * A negative given index \p{startIdx} indicates the pre-processing phase.
         * If \p{target} is given, this indicates an "intermediate phase": The argument has been
         * written, but no alignment or cutting has been done, yet. This phase should usually
         * be ignored, but is for example important for search and replacement actions.
         * If a field has a custom format implementation (e.g. time and date values), then
         * the intermediate phase is never called.
         *
         * \note
         *   The reason why this method is \b not implemented as two different ones is that
         *   derived classes might do some more complicated parsing of parts of the placeholder
         *   string in this method. In this case, the parsing is needed to be implemented only
         *   once, while the finally parsed commands are only conditionally executed depending
         *   if executed as pre or post phase.
         *
         * @param startIdx  If \c -1 pre-processing is indicated, otherwise post-processing and
         *                  the index of the start of the field written in #ptargetString is given.
         * @param target    The target string, only if different from field #ptargetString, which
         *                  indicates intermediate phase.
         * @return \c false, if the placeholder should be skipped (nothing is written for it).
         *         \c true otherwise.
         ******************************************************************************************/
        protected  boolean     preAndPostProcess(int startIdx, AString target)
        {
            /* empty default implementation */
            return true;
        }

        /** ****************************************************************************************
         * Helper method (overridable) that usually is invoked by implementation of
         * #parsePlaceholder when an argument index is read from the format string,
         *
         * If this does not happen, method #format will invoke this method providing \c -1 for
         * value of parameter \p{pos} to automatically choose the next argument.
         *
         * Consequently, this method sets the fields
         * \ref com.aworx.lib.strings.format.FormatterStdImpl.phaArgument    "Argument" and
         * \ref com.aworx.lib.strings.format.FormatterStdImpl.phaArgumentIdx "ArgumentIdx"
         * in given \p{field}.
         * For auto-values, it increments #nextAutoIdx.
         * Finally, this method is responsible for the correct book-keeping of #argsConsumed.
         *
         * @param pos   The index of the argument.
         *              If \c -1 is given, the index is auto-incremented using field #nextAutoIdx.
         * @param countStartsWith_1 If \c true, given \p{pos} is counting arguments with \c 1 being
         *                         the first. Otherwise with \c 0.
         * @return \c true on success, \c false on errors.
         ******************************************************************************************/
        protected  boolean       setArgument( int pos, boolean countStartsWith_1 )
        {
            if( countStartsWith_1 )
            {
                if( pos == 0 )
                {
                    errorFormatString( "Wrong argument index '0'" );
                    return false;
                }
                else if( pos > 0 )
                    pos--;
            }

            // auto? If not, set auto to this pos + 1
            phaArgumentIdx= ( pos >= 0)  ?  pos : nextAutoIdx++;

            // store maximum value used
            if ( argsConsumed - 1 < phaArgumentIdx )
                argsConsumed= phaArgumentIdx + 1;

            // get corresponding argument
            int  argIdx= pargOffset + phaArgumentIdx;
            if( argIdx >= parguments.size() )
            {
                errorFormatString( "Missing argument #" + (phaArgumentIdx + (countStartsWith_1 ? 1 : 0) ) );
                return false;
            }

            phaArgument= parguments.get(argIdx);
            return true;


        }


        /** ****************************************************************************************
         * Helper method (overridable) that optionally
         * - creates an \b %ALib error report (dependent on field #writeALibErrorReports).
         * - writes an error message to the target string (dependent on field
         *   #writeErrorsToTargetString).
         *
         * This method can (and should) be invoked by descendent types in case of format string
         * syntax errors, argument index errors, etc.
         *
         * @param msg             The error message.
         ******************************************************************************************/
        protected  void          errorFormatString( String msg )
        {
            if ( !writeErrorsToTargetString && !writeALibErrorReports )
                return;

            AString repMsg= new AString();
            repMsg._NC( msg )
                  ._NC( " at index " )._( pformatString.length() - parser.length() - 1 )
                  ._NC( " in format String \"" )._NC( pformatString )._NC("\".");

            if ( writeErrorsToTargetString )
                ptargetString._NC(repMsg);

            if( writeALibErrorReports )
                com.aworx.lib.ALIB_DBG.ERROR( repMsg.toString() );
        }

        /** ****************************************************************************************
         * Replace "escaped" placeholder field characters. For example these are \c "{{" in
         * python style or \c "%%" in JAVA style.<br>
         * In addition other escape sequences defined with the format are to be replaced
         * with this method.
         *
         * @param startIdx The start of the region to replace
         ******************************************************************************************/
        protected abstract void         replaceEscapeSequences( int startIdx );

} // class Formatter
