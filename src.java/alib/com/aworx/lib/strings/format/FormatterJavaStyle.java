package com.aworx.lib.strings.format;
import com.aworx.lib.lang.Alignment;
import com.aworx.lib.lang.Switch;
import com.aworx.lib.strings.AString;
import com.aworx.lib.strings.CString;


/** ************************************************************************************************
 * Implements a \ref com.aworx.lib.strings.format.Formatter "Formatter" according to the
 * [formatting standards of the Java language](http://docs.oracle.com/javase/8/docs/api/java/util/Formatter.html).
 *
 * \note
 *   Inherited, public fields of parent class \b FormatterStdImpl provide important possibilities
 *   for changing the formatting behavior of instances of this class. Therefore, do not forget
 *   to consult the \ref com.aworx.lib.strings.format.FormatterStdImpl "parent classes documentation".
 *
 * In general, the original specification is covered quite well. The differences and specialties
 * are:
 * - In deviation of the Java specification, after creation, a formatter in this implementation
 *   does not produce locale aware output. Instead, number formatting is set to "computational",
 *   hence the decimal point separator is <c>'.'</c> and the grouping character <c>','</c>.
 *   As the syntax specification does not provide a feature to switch between standard and locale
 *   setting, the corresponding fields of #alternativeNumberFormat are not used with this formatter.
 *   Instead, to enable localized output, method
 *   \ref com.aworx.lib.strings.NumberFormat.setFromLocale "NumberFormat.setFromLocale"
 *   has to be invoked on field
 *   \ref com.aworx.lib.strings.format.FormatterStdImpl.defaultNumberFormat "FormatterStdImpl.defaultNumberFormat".
 *   Alternatively, attributes of this object may be changed manually or by other means to reflect
 *   a desired locale.
 * - Hexadecimal floating point output (conversion type \c 'a' and \c 'A') is not supported.
 * - Flag \c '(', used to write negative numbers in round brackets, is not supported.
 * - Addressing the previous argument index using \c '%<' is already allowed with the first
 *   placeholder.
 *   This Chooses the first argument. (In Java a \b MissingFormatArgumentException would be thrown.)
 * - Flag \c '^' is an extension to the standard and denotes
 *   center-alignment - just like \c '-' in the standard denotes left-alignment.
 *   Right-alignment is the default.
 *
 *<p>
 * - <b>Floating point values:</b>
 *   - If standard field type \c 's' is given together with a precision, the field is cut, even if
 *     it cuts the number somewhere. (This is just a warning and same behavior as in original
 *     specification.)
 *   - For lower case floating point format types (\c 'f', \c 'g' and \c 'e'), the values specified
 *     in attributes \b %ExponentSeparator, \b %NANLiteral and \b %INFLiteral of object
 *     \ref com.aworx.lib.strings.format.FormatterStdImpl.alternativeNumberFormat "alternativeNumberFormat"
 *     are used. For upper case types (\c 'G' and \c 'E'), the corresponding attributes in
 *     \ref com.aworx.lib.strings.format.FormatterStdImpl.defaultNumberFormat "defaultNumberFormat" apply.
 *   - Fixed point format (\c 'f' ) is not supported to use arbitrary length.
 *     See class \ref com.aworx.lib.strings.NumberFormat "NumberFormat" for the limits.
 *     Due to this limitation, the default number of fractional digits is not set with type \c 'f',
 *     while in Java it is set to \c 6. This is to allow higher numbers up to \c 1.e13 to be printed
 *     in non-scientific format
 *   - When both, a \p{width} and a \p{precision} is given, then the \p{precision} determines the
 *     fractional part, even if the type is \b 'g' or \b 'G'. This is different than specified with
 *     Java formatter, which uses \p{precision} as the overall width in case of types
 *     \b 'g' or \b 'G'.
 *
 *<p>
 * - <b>Hexadecimal and Octal Numbers:</b>
 *   - Hexadecimal and octal output is <b>cut in size</b> (!) when a field width is given that
 *     is smaller than the resulting amount of digits of the number arguments provided.
 *       \note  This implies that a value written might not be equal to the value given.
 *              This is not a bug but a design decision. The rational behind this is that with this
 *              behavior, there is no need to mask lower digits when passing the arguments to the
 *              format invocation. In other words, the formatter "assumes" that the given field width
 *              indicates that only a corresponding number of lower digits are of interest.
 *
 *   - The number <b>grouping option</b> (<c>','</c>) can also be used with binary, hexadecimal
 *     and octal output.
 *     The types support different grouping separators for nibbles, bytes, 16-bit and 32-bit words.
 *     Changing the separator symbols, is not possible with the format fields of the format strings
 *     (if it was, this would become very incompatible to Java standards). Changes have to be made
 *     prior to the format operation by modifying field
 *     \ref com.aworx.lib.strings.format.FormatterStdImpl.alternativeNumberFormat "alternativeNumberFormat"
 *     which is provided through parent class \b %FormatterStdImpl.
 *
 *   - Alternative form (\c '#') adds prefixes as specified in members
 *     - \ref com.aworx.lib.strings.NumberFormat.hexLiteralPrefix "hexLiteralPrefix" and
 *     - \ref com.aworx.lib.strings.NumberFormat.octLiteralPrefix "octLiteralPrefix".
 *
 *     For upper case formats,  those are taken from field
 *     \ref com.aworx.lib.strings.format.FormatterStdImpl.defaultNumberFormat "defaultNumberFormat",
 *     for lower case formats from
 *     \ref com.aworx.lib.strings.format.FormatterStdImpl.alternativeNumberFormat "alternativeNumberFormat".
 *     All defaults may be changed by the user.
 *
 *<p>
 * - <b>Time and Date:</b>
 *   - In the Java version, boxed values of types
 *     \ref com.aworx.lib.time.Ticks "Ticks" and \b java.util.Date  are applicable to conversion
 *     type \c 't'.
 *   - The following time conversion suffix characters are supported:
 *     \c 'H', \c 'k', \c 'I', \c 'l', \c 'M', \c 'S', \c 'B', \c 'b', \c 'h', \c 'A', \c 'a',
 *     \c 'Y', \c 'y', \c 'm', \c 'd', \c 'e', \c 'R', \c 'T', \c 'D' and \c 'F'
 *   - The following time conversion suffix characters are \b not supported:
 *     \c 'L', \c 'N', \c 'p', \c 'z', \c 'Z', \c 's', \c 'Q', \c 'C', \c 'j', \c 'r' and \c 'c'.
 **************************************************************************************************/
public class FormatterJavaStyle extends FormatterStdImpl
{
    // #############################################################################################
    // Protected fields
    // #############################################################################################
        /** Convert to upper case.   */
        protected boolean              phaExtConversionUpper;

        /** Alternate form given ('#').   */
        protected boolean             phaAlternateForm;

        /** The value read from the precision field.
         *  This is set to \c -1 in #resetPHAs. */
        protected int                 phaExtPrecision;

        /** The default precision if not given.
         *  This is set to \c 6 in #resetPHAs, but is changed when specific. */
        protected int                 phaExtDefaultPrecision;

        /** The character after conversion type 't'/'T'. */
        protected char                phaExtDateTime;


    // #############################################################################################
    //  Constructor/Destructor
    // #############################################################################################

        /** ****************************************************************************************
         * Constructs this formatter.
         * Inherited field #defaultNumberFormat is initialized to meet the formatting defaults of
         * Java.
         ******************************************************************************************/
        public FormatterJavaStyle()
        {
            super("FormatterJavaStyle");
            construct();
        }

        /** ****************************************************************************************
         * Constructor helper method.
         ******************************************************************************************/
        protected void construct()
        {
            // set number format to Java defaults
            defaultNumberFormat    .forceDecimalPoint       = false;
            defaultNumberFormat    .writeExponentPlusSign   = true;

            // set number format to Java defaults
            defaultNumberFormat    .hexLiteralPrefix._()._( "0X" );
            defaultNumberFormat    .octLiteralPrefix._()._( "0"  );
            alternativeNumberFormat.octLiteralPrefix._()._( "0"  );

            defaultNumberFormat    .NANLiteral         =
            alternativeNumberFormat.NANLiteral         = "NaN";
            defaultNumberFormat    .INFLiteral         = "INFINITY";
            alternativeNumberFormat.INFLiteral         = "Infinity";
        }



    // #############################################################################################
    //  Implementation of FormatterStdImpl interface
    // #############################################################################################

        /** ****************************************************************************************
         * Invokes parent implementation and then applies some changes to reflect what is defined as
         * default in the Java string format specification.
         ******************************************************************************************/
        @Override
        protected void    resetPHAs()
        {
            // first invoke parent's setting...
            super.resetPHAs();

            // ...then make some "Java like" adjustments
            phaExtConversionUpper               = false;
            phaAlignment                        = Alignment.RIGHT;

            phaNF.forceDecimalPoint             = false;
            phaNF.omitTrailingFractionalZeros   = false;

            phaAlternateForm                    = false;

            phaExtPrecision                     = -1;
            phaExtDefaultPrecision              = 6;
        }


        /** ****************************************************************************************
         * Searches for \c '\%' which is not '%%' or '%n'.
         *
         * @return The index found, -1 if not found.
         ******************************************************************************************/
        @Override
        protected  int  findPlaceholder()
        {
            int idx= 0;
            while(     (idx= parser.indexOf('%', idx )) >= 0
                   &&  (    parser.charAt( idx + 1 ) == '%'
                         || parser.charAt( idx + 1 ) == 'n'   ) )
            {
                // double ESC found (escaped %% or %n)
                idx+= + 2;
            }
            return idx;
        }


        //! @cond NO_DOX
        protected enum ppStates
        {
            POSITION     ,
            FLAGS        ,
            WIDTH        ,
            PRECISION    ,
            TYPE         ,
            TYPE_SUFFIX  ,
            END          ,
        }
        //! @endcond

        /** ****************************************************************************************
         * Parses placeholder field in Java syntax. The portion \p{format_spec} is not set as this
         * is not supported by the syntax.
         *
         * @return \c true on success, \c false on errors.
         ******************************************************************************************/
        @Override
        protected boolean parsePlaceholder()
        {
            ppStates  state= ppStates.POSITION;

            while( true )
            {
                // switch over state. With 'break' we consume one character (kind of success) while
                // with 'continue' we keep the current character (and go to another state)
                switch ( state )
                {
                    case POSITION:
                    {
                        int argNo= -1;
                        if ( parser.consumeChar('<') )
                        {
                            argNo= phaPreviousArgumentIdx + 1;
                        }
                        else
                        {
                            int i= 0;
                            while(    i < parser.length()
                                   && Character.isDigit( parser.charAt(i) ) )
                                 ++i;

                            if(  i > 0 &&  parser.charAt(i) == '$')
                            {
                                parser.consumeDecDigits(); argNo= (int) parser.consumedLong;
                                parser.consumeChar('$');
                            }
                        }
                        if( argNo > 0 )
                            setArgument( argNo, true  );

                        state= ppStates.FLAGS; continue;
                    }

                    case FLAGS:
                    {
                        boolean flagsDone= false;
                        while(!flagsDone)
                        {
                            switch ( parser.charAtStart() )
                            {
                                case '-':
                                    phaAlignment= Alignment.LEFT;
                                    phaAlignmentSpecified= true;
                                    break;

                                case '^':
                                    phaAlignment= Alignment.CENTER;
                                    phaAlignmentSpecified= true;
                                    break;

                                case '#':
                                {
                                    phaAlternateForm= true;
                                    phaWriteBinOctHexPrefix=             true;
                                    phaNF.forceDecimalPoint=             true;
                                    phaNF.omitTrailingFractionalZeros=   false;
                                    break;
                                }

                                case '+':
                                case ' ':
                                    phaNF.plusSign= parser.charAtStart();
                                    break;

                                case '0':
                                    phaSignPaddingMode= true;
                                    break;

                                case ',':
                                    phaNF.writeGroupChars= true;
                                    break;

                                case '(':
                                    errorFormatString("Brackets for negative values not supported");
                                    return false;

                                default:
                                    flagsDone= true;
                                    break;
                            }

                            if( !flagsDone )
                                parser.consumeChars( 1 );
                        }
                        state= ppStates.WIDTH; continue;
                    }


                    case WIDTH:
                    {
                        if( Character.isDigit( parser.charAtStart() ) )
                        {
                            parser.consumeDecDigits();
                            phaWidth= (int) parser.consumedLong;
                        }

                        state= ppStates.PRECISION; continue;
                    }

                    case PRECISION:
                    {
                        if( parser.consumeChar( '.' ) )
                        {
                            if( !parser.consumeDecDigits() )
                            {
                                errorFormatString("Missing decimal value after precision symbol '.'");
                                return false;
                            }
                            phaExtPrecision= (int) parser.consumedLong;
                        }
                        state= ppStates.TYPE; continue;
                    }

                    case TYPE:
                    {
                        char typeChar=  parser.charAtStart();
                        parser.consumeChars( 1 );

                        char typeCharLower= Character.toLowerCase( typeChar );

                        if ( typeCharLower == 'a' )
                        {
                            errorFormatString("Hexadecimal float format not supported");
                            return false;
                        }

                        if( phaAlternateForm && "sSbBhHgGcCtT".indexOf( typeChar ) >= 0 )
                        {
                            errorFormatString( "Format Flags Conversion Mismatch Exception: Conversion = "
                                              + typeChar + ", Flags = #" );
                            return false;
                        }

                        if( "seg".indexOf( typeChar ) >= 0 )
                        {
                            if( typeChar != 's' )
                                phaNF.exponentSeparator= alternativeNumberFormat.exponentSeparator;
                            phaNF.INFLiteral=            alternativeNumberFormat.INFLiteral;
                            phaNF.NANLiteral=            alternativeNumberFormat.NANLiteral;
                        }

                        if( "SBCT".indexOf( typeChar ) >= 0 )
                            phaExtConversionUpper= true;

                        if( "egf".indexOf( typeCharLower ) < 0 )
                            phaCutContent=  phaExtPrecision;

                        if( phaExtPrecision >=0 && "cCtTd".indexOf( typeChar ) >= 0 )
                        {
                            errorFormatString("Precision not applicable for: Conversion = "
                                              + typeChar + ", Precision = ." + phaExtPrecision );
                            return false;
                        }

                             if( typeChar == 'X' || typeChar == 'H' )   phaNF.hexLowerCase= false;
                        else if( typeChar == 'x' || typeChar == 'h' )   phaNF.hexLiteralPrefix= alternativeNumberFormat.hexLiteralPrefix;


                        switch ( typeCharLower )
                        {
                            case 's':   phaExtPrecision=   -1;
                                        break;

                            case 'b':   phaType=  PHType.Bool;                  break;
                            case 'c':   phaType=  PHType.Character;             break;
                            case 'd':   phaType=  PHType.IntBase10;             break;
                            case 'o':   phaType=  PHType.IntOctal;              break;
                            case 'x':   phaType=  PHType.IntHex;                break;
                            case 'h':   phaType=  PHType.IntHex;                break;
                            case 'e':   phaType=  PHType.Float;
                                        phaNF.forceScientific=  true;           break;
                            case 'g':   phaType= PHType.Float;                  break;
                            case 'f':   phaType= PHType.Float;
                                        phaNF.integralPartMinimumWidth= 1;
                                        phaExtDefaultPrecision=        -1;      break;

                            case 't':   phaExtDateTime= parser.charAtStart();
                                        parser.consumeChars( 1 );
                                        switch( phaExtDateTime )
                                        {
                                            case 'H': phaFormatSpec.set("HH" );       break;
                                            case 'k': phaFormatSpec.set("H"  );       break;
                                            case 'I': phaFormatSpec.set("KK a" );     break;
                                            case 'l': phaFormatSpec.set("K a"  );     break;
                                            case 'M': phaFormatSpec.set("mm" );       break;
                                            case 'S': phaFormatSpec.set("ss" );       break;
                                            // not supported: case 'L': ;
                                            // not supported: case 'N': ;
                                            // not supported: case 'p': ;
                                            // not supported: case 'z': ;
                                            // not supported: case 'Z': ;
                                            // not supported: case 's': ;
                                            // not supported: case 'Q': ;
                                            case 'B': phaFormatSpec.set( "MMMM"      );   break;
                                            case 'b': phaFormatSpec.set( "MMM"       );   break;
                                            case 'h':
                                            case 'A': phaFormatSpec.set( "EEEE"      );   break;
                                            case 'a': phaFormatSpec.set( "EEE"       );   break;
                                            // not supported: case 'C': ;
                                            case 'Y': phaFormatSpec.set( "yyyy"      );   break;
                                            case 'y': phaFormatSpec.set( "yy"        );   break;
                                            // not supported: case 'j': ;
                                            case 'm': phaFormatSpec.set( "MM"        );   break;
                                            case 'd': phaFormatSpec.set( "dd"        );   break;
                                            case 'e': phaFormatSpec.set( "d"         );   break;

                                            case 'R': phaFormatSpec.set( "HH:mm"     );   break;
                                            case 'T': phaFormatSpec.set( "HH:mm:ss"  );   break;
                                            // not supported: case 'r': ;

                                            case 'D': phaFormatSpec.set( "MM/dd/yy"  );   break;
                                            case 'F': phaFormatSpec.set( "yyyy-MM-dd");   break;
                                            // not supported: case 'c': ;




                                            default:
                                            errorFormatString( "Unknown date/time conversion suffix character '"
                                                               + phaExtDateTime + '\'' );
                                            return  false;

                                        }
                                        break;

                            default:
                                errorFormatString("Unknown Format Conversion Exception");
                                return false;
                        }

                        state= ppStates.TYPE_SUFFIX; continue;
                    }

                    case TYPE_SUFFIX:
                    {
                        state= ppStates.END; continue;
                    }

                    case END:
                        //parser.consumeChars(1);
                        return true;

                } // state switch

            } // read loop
        }


        /** ****************************************************************************************
         * Does nothing. Java does not support custom format specifications.
         *
         * @return \c true to indicate success.
         ******************************************************************************************/
        @Override
        protected boolean parseStdFormatSpec()
        {
            return true;
        }

        /** ****************************************************************************************
         * Replaces \c "%%" with \c '\%' and \c "%n" with ascii \c 0x0a. In addition applies
         * \ref com.aworx.lib.strings.AString.escape "AString.escape" on \p{target} which replaces
         * standard codes like \c "\\n", \c "\\r" or \c "\\t" with corresponding ascii codes.
         * (The latter is an extension to the standard behavior of Java formatter.)
         *
         * @param startIdx The start of the region to replace
         ******************************************************************************************/
        @Override
        protected void    replaceEscapeSequences( int startIdx )
        {
            ptargetString.searchAndReplace( "%%" , "%"                    , startIdx );
            ptargetString.searchAndReplace( "%n" , CString.NEW_LINE_CHARS , startIdx );
            ptargetString.escape( Switch.OFF, startIdx );
        }


        /** ****************************************************************************************
         * All that this formatter does with this overridden method is to convert strings to
         * upper case.
         *
         * @param startIdx  The int of the start of the field written in #ptargetString.
         *                  \c -1 indicates pre-phase.
         * @param target    The target string, only if different from field #ptargetString, which
         *                  indicates intermediate phase.
         * @return \c false, if the placeholder should be skipped (nothing is written for it).
         *         \c true otherwise.
         ******************************************************************************************/
        @Override
        protected boolean preAndPostProcess( int startIdx, AString target )
        {
            if( startIdx >= 0 && phaExtConversionUpper && target == null )
                ptargetString.toUpper( startIdx );
            return true;
        }


        /** ****************************************************************************************
         * Makes some attribute adjustments and invokes standard implementation
         * @return \c true if OK, \c false if replacement should be aborted.
         ******************************************************************************************/
        @Override
        protected boolean    checkStdFieldAgainstArgument()
        {
            boolean wasFloat= phaType == PHType.Float;
            if( wasFloat )
            {
                if ( phaExtPrecision >= 0 )
                    phaNF.fractionalPartWidth= phaExtPrecision;
                else if( phaNF.fractionalPartWidth < 0 )
                    phaNF.fractionalPartWidth= phaExtDefaultPrecision;
            }

            boolean result= super.checkStdFieldAgainstArgument();

            if( !wasFloat && phaType == PHType.Float )
            {
                if ( phaExtPrecision >= 0 )
                    phaNF.fractionalPartWidth= phaExtPrecision;
            }

            return result;
        }


}
