// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2018 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################


using System;
using System.Text;
using cs.aworx.lib.strings;
using System.Collections;
using System.Collections.Generic;
using cs.aworx.lib.lang;

namespace cs.aworx.lib.strings.format  {

/** ************************************************************************************************
 * Implements a \ref cs.aworx.lib.strings.format.Formatter "Formatter" according to the
 * [formatting standards of the Java language](http://docs.oracle.com/javase/8/docs/api/java/util/Formatter.html).
 *
 * \note
 *   Inherited, public fields of parent class \b FormatterStdImpl provide important possibilities
 *   for changing the formatting behavior of instances of this class. Therefore, do not forget
 *   to consult the \ref cs.aworx.lib.strings.format.FormatterStdImpl "parent classes documentation".
 *
 * In general, the original specification is covered quite well. The differences and specialties
 * are:
 * - In deviation of the Java specification, after creation, a formatter in this implementation
 *   does not produce locale aware output. Instead, number formatting is set to "computational",
 *   hence the decimal point separator is <c>'.'</c> and the grouping character <c>','</c>.
 *   As the syntax specification does not provide a feature to switch between standard and locale
 *   setting, the corresponding fields of #AlternativeNumberFormat are not used with this formatter.
 *   Instead, to enable localized output, method
 *   \ref cs.aworx.lib.strings.NumberFormat.SetFromLocale "NumberFormat.SetFromLocale"
 *   has to be invoked on field
 *   \ref cs.aworx.lib.strings.format.FormatterStdImpl.DefaultNumberFormat "FormatterStdImpl.DefaultNumberFormat".
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
 *     \ref cs.aworx.lib.strings.format.FormatterStdImpl.AlternativeNumberFormat "AlternativeNumberFormat"
 *     are used. For upper case types (\c 'G' and \c 'E'), the corresponding attributes in
 *     \ref cs.aworx.lib.strings.format.FormatterStdImpl.DefaultNumberFormat "DefaultNumberFormat" apply.
 *   - Fixed point format (\c 'f' ) is not supported to use arbitrary length.
 *     See class \ref cs.aworx.lib.strings.NumberFormat "NumberFormat" for the limits.
 *     Due to this limitation, the default number of fractional digits is not set with type \c 'f',
 *     while in Java it is set to \c 6. This is to allow higher numbers up to \c 1.e13 to be printed
 *     in non-scientific format
 *   - When both, a \p width and a \p precision is given, then the \p precision determines the
 *     fractional part, even if the type is \b 'g' or \b 'G'. This is different than specified with
 *     Java formatter, which uses \p precision as the overall width in case of types
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
 *     \ref cs.aworx.lib.strings.format.FormatterStdImpl.AlternativeNumberFormat "AlternativeNumberFormat"
 *     which is provided through parent class \b %FormatterStdImpl.
 *
 *   - Alternative form (\c '#') adds prefixes as specified in members
 *     - \ref cs.aworx.lib.strings.NumberFormat.HexLiteralPrefix "HexLiteralPrefix" and
 *     - \ref cs.aworx.lib.strings.NumberFormat.OctLiteralPrefix "OctLiteralPrefix".
 *
 *     For upper case formats,  those are taken from field
 *     \ref cs.aworx.lib.strings.format.FormatterStdImpl.DefaultNumberFormat "DefaultNumberFormat",
 *     for lower case formats from
 *     \ref cs.aworx.lib.strings.format.FormatterStdImpl.AlternativeNumberFormat "AlternativeNumberFormat".
 *     All defaults may be changed by the user.
 *
 *<p>
 * - <b>Time and Date:</b>
 *   - In the c# version, objects of type .Net-type \b %DateTime are applicable to conversion
 *     type \c 't'.
 *   - The following time conversion suffix characters are supported:
 *     \c 'H', \c 'k', \c 'I', \c 'l', \c 'M', \c 'S', \c 'B', \c 'b', \c 'h', \c 'A', \c 'a',
 *     \c 'Y', \c 'y', \c 'm', \c 'd', \c 'e', \c 'R', \c 'T', \c 'D' and \c 'F'
 *   - The following time conversion suffix characters are \b not supported:
 *     \c 'L', \c 'N', \c 'p', \c 'z', \c 'Z', \c 's', \c 'Q', \c 'C', \c 'j', \c 'r' and \c 'c'.
 *   - For technical reasons, conversion suffixes \c 'k' and \c 'e' write a leading zero. Single
 *     digit output is not possible in this python implementation and if needed, has to be done
 *     writing integer value instead.
 **************************************************************************************************/
public class FormatterJavaStyle : FormatterStdImpl
{
    // #############################################################################################
    // Protected fields
    // #############################################################################################
        /** Convert to upper case.   */
        protected bool                phaExtConversionUpper;

        /** Alternate form given ('#').   */
        protected bool                phaAlternateForm;

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

    /** ********************************************************************************************
     * Constructs this formatter.
     * Inherited field #DefaultNumberFormat is initialized to meet the formatting defaults of
     * Java.
     **********************************************************************************************/
    public FormatterJavaStyle()
    : base ("FormatterJavaStyle")
    {
        // set number format to Java defaults
        DefaultNumberFormat.ForceDecimalPoint       = false;
        DefaultNumberFormat.WriteExponentPlusSign   = true;

        // set number format to Java defaults
        DefaultNumberFormat    .HexLiteralPrefix._()._( "0X" );
        DefaultNumberFormat    .OctLiteralPrefix._()._( "0"  );
        AlternativeNumberFormat.OctLiteralPrefix._()._( "0"  );

        DefaultNumberFormat    .NANLiteral         =
        AlternativeNumberFormat.NANLiteral         = "NaN";
        DefaultNumberFormat    .INFLiteral         = "INFINITY";
        AlternativeNumberFormat.INFLiteral         = "Infinity";
    }


    // #############################################################################################
    //  Implementation of FormatterStdImpl interface
    // #############################################################################################

        /** ****************************************************************************************
         * Invokes parent implementation and then applies some changes to reflect what is defined as
         * default in the Java string format specification.
         ******************************************************************************************/
        protected override void    resetPHAs()
        {
            // first invoke parent's setting...
            base.resetPHAs();

            // ...then make some "Java like" adjustments
            phaExtConversionUpper               = false;
            phaAlignment                        = Alignment.Right;

            phaNF.ForceDecimalPoint             = false;
            phaNF.OmitTrailingFractionalZeros   = false;

            phaAlternateForm                    = false;

            phaExtPrecision                     = -1;
            phaExtDefaultPrecision              = 6;
        }


        /** ****************************************************************************************
         * Searches for \c '\%' which is not '%%' or '%n'.
         *
         * @return The index found, -1 if not found.
         ******************************************************************************************/
        protected override  int  findPlaceholder()
        {
            int idx= 0;
            while(     (idx= parser.IndexOf('%', idx )) >= 0
                   &&  (    parser.CharAt( idx + 1 ) == '%'
                         || parser.CharAt( idx + 1 ) == 'n'   ) )
            {
                // double ESC found (escaped %% or %n)
                idx+= + 2;
            }
            return idx;
        }


        /** ****************************************************************************************
         * States used in #parsePlaceholder.
         ******************************************************************************************/
        protected enum ppStates
        {
            POSITION        =  1,
            FLAGS           =  2,
            WIDTH           =  3,
            PRECISION       =  4,
            TYPE            =  5,
            TYPE_SUFFIX     =  6,
            END             = 10,
        };

        /** ****************************************************************************************
         * Parses placeholder field in Java syntax. The portion \p format_spec is not set as this
         * is not supported by the syntax.
         *
         * @return \c true on success, \c false on errors.
         ******************************************************************************************/
        protected override bool    parsePlaceholder()
        {
            ppStates  state= ppStates.POSITION;

            while( true )
            {
                // switch over state. With 'break' we consume one character (kind of success) while
                // with 'continue' we keep the current character (and go to another state)
                switch ( state )
                {
                    case ppStates.POSITION:
                    {
                        int argNo= -1;
                        if ( parser.ConsumeChar('<') )
                        {
                            argNo= phaPreviousArgumentIdx + 1;
                        }
                        else
                        {
                            int i= 0;
                            while(    i < parser.Length()
                                   && Char.IsDigit( parser.CharAt(i) ) )
                                 ++i;

                            if(  i > 0 &&  parser.CharAt(i) == '$')
                            {
                                parser.ConsumeDecDigits( out argNo );
                                parser.ConsumeChar('$');
                            }
                        }
                        if( argNo > 0 )
                            setArgument( argNo, true  );

                        state= ppStates.FLAGS; continue;
                    }

                    case ppStates.FLAGS:
                    {
                        bool flagsDone= false;
                        while(!flagsDone)
                        {
                            switch ( parser.CharAtStart() )
                            {
                                case '-':
                                    phaAlignment= Alignment.Left;
                                    phaAlignmentSpecified= true;
                                    break;

                                case '^':
                                    phaAlignment= Alignment.Center;
                                    phaAlignmentSpecified= true;
                                    break;

                                case '#':
                                {
                                    phaAlternateForm= true;
                                    phaWriteBinOctHexPrefix=             true;
                                    phaNF.ForceDecimalPoint=             true;
                                    phaNF.OmitTrailingFractionalZeros=   false;
                                    break;
                                }

                                case '+':
                                case ' ':
                                    phaNF.PlusSign= parser.CharAtStart();
                                    break;

                                case '0':
                                    phaSignPaddingMode= true;
                                    break;

                                case ',':
                                    phaNF.WriteGroupChars= true;
                                    break;

                                case '(':
                                    errorFormatString("Brackets for negative values not supported");
                                    return false;

                                default:
                                    flagsDone= true;
                                    break;
                            }

                            if( !flagsDone )
                                parser.ConsumeChars( 1 );
                        }
                        state= ppStates.WIDTH; continue;;
                    }


                    case ppStates.WIDTH:
                    {
                        if( Char.IsDigit( parser.CharAtStart() ) )
                            parser.ConsumeDecDigits( out phaWidth );

                        state= ppStates.PRECISION; continue;
                    }

                    case ppStates.PRECISION:
                    {
                        if( parser.ConsumeChar( '.' ) && !parser.ConsumeDecDigits( out phaExtPrecision ) )
                        {
                            errorFormatString("Missing decimal value after precision symbol '.'");
                            return false;
                        }

                        state= ppStates.TYPE; continue;
                    }

                    case ppStates.TYPE:
                    {
                        char typeChar=  parser.CharAtStart();
                        parser.ConsumeChars( 1 );

                        char typeCharLower= Char.ToLower( typeChar );

                        if ( typeCharLower == 'a' )
                        {
                            errorFormatString("Hexadecimal float format not supported");
                            return false;
                        }

                        if( phaAlternateForm && "sSbBhHgGcCtT".IndexOf( typeChar ) >= 0 )
                        {
                            errorFormatString( "Format Flags Conversion Mismatch Exception: Conversion = "
                                              + typeChar + ", Flags = #" );
                            return false;
                        }

                        if( "seg".IndexOf( typeChar ) >= 0 )
                        {
                            if( typeChar != 's' )
                                phaNF.ExponentSeparator= AlternativeNumberFormat.ExponentSeparator;
                            phaNF.INFLiteral=        AlternativeNumberFormat.INFLiteral;
                            phaNF.NANLiteral=        AlternativeNumberFormat.NANLiteral;
                        }

                        if( "SBCT".IndexOf( typeChar ) >= 0 )
                            phaExtConversionUpper= true;

                        if( "egf".IndexOf( typeCharLower ) < 0 )
                            phaCutContent=  phaExtPrecision;

                        if( phaExtPrecision >=0 && "cCtTd".IndexOf( typeChar ) >= 0 )
                        {
                            errorFormatString("Precision not applicable for: Conversion = "
                                              + typeChar + ", Precision = ." + phaExtPrecision );
                            return false;
                        }

                             if( typeChar == 'X' || typeChar == 'H' )   phaNF.HexLowerCase= false;
                        else if( typeChar == 'x' || typeChar == 'h' )   phaNF.HexLiteralPrefix= AlternativeNumberFormat.HexLiteralPrefix;


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
                                        phaNF.ForceScientific=  true;            break;
                            case 'g':   phaType= PHType.Float;                  break;
                            case 'f':   phaType= PHType.Float;
                                        phaNF.IntegralPartMinimumWidth= 1;
                                        phaExtDefaultPrecision=        -1;       break;

                            case 't':   phaExtDateTime= parser.CharAtStart();
                                        parser.ConsumeChars( 1 );
                                        switch( phaExtDateTime )
                                        {
                                            case 'H': phaFormatSpec.Set("HH" );       break;
                                            case 'k': phaFormatSpec.Set("HH" );       break; // should be one H, but not allowed!
                                            case 'I': phaFormatSpec.Set("hh tt" );    break;
                                            case 'l': phaFormatSpec.Set("h tt"  );    break;
                                            case 'M': phaFormatSpec.Set("mm" );       break;
                                            case 'S': phaFormatSpec.Set("ss" );       break;
                                            // not supported: case 'L': ;
                                            // not supported: case 'N': ;
                                            // not supported: case 'p': ;
                                            // not supported: case 'z': ;
                                            // not supported: case 'Z': ;
                                            // not supported: case 's': ;
                                            // not supported: case 'Q': ;
                                            case 'B': phaFormatSpec.Set( "MMMM"      );   break;
                                            case 'b': phaFormatSpec.Set( "MMM"       );   break;
                                            case 'h':
                                            case 'A': phaFormatSpec.Set( "dddd"      );   break;
                                            case 'a': phaFormatSpec.Set( "ddd"       );   break;
                                            // not supported: case 'C': ;
                                            case 'Y': phaFormatSpec.Set( "yyyy"      );   break;
                                            case 'y': phaFormatSpec.Set( "yy"        );   break;
                                            // not supported: case 'j': ;
                                            case 'm': phaFormatSpec.Set( "MM"        );   break;
                                            case 'd': phaFormatSpec.Set( "dd"        );   break;
                                            case 'e': phaFormatSpec.Set( "dd"        );   break;  // should be one d, but not allowed!

                                            case 'R': phaFormatSpec.Set( "HH:mm"     );   break;
                                            case 'T': phaFormatSpec.Set( "HH:mm:ss"  );   break;
                                            // not supported: case 'r': ;

                                            case 'D': phaFormatSpec.Set( "MM/dd/yy"  );   break;
                                            case 'F': phaFormatSpec.Set( "yyyy-MM-dd");   break;
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

                    case ppStates.TYPE_SUFFIX:
                    {
                        state= ppStates.END; continue;
                    }

                    case ppStates.END:
                        //parser.ConsumeChars(1);
                        return true;

                } // state switch

            } // read loop
        }


        /** ****************************************************************************************
         * Does nothing. Java does not support custom format specifications.
         *
         * @return \c true to indicate success.
         ******************************************************************************************/
        protected override bool    parseStdFormatSpec()
        {
            return true;
        }

        /** ****************************************************************************************
         * Replaces \c "%%" with \c '\%' and \c "%n" with ascii \c 0x0a. In addition applies
         * \ref cs.aworx.lib.strings.AString.Escape "AString.Escape" on \p target which replaces
         * standard codes like \c "\\n", \c "\\r" or \c "\\t" with corresponding ascii codes.
         * (The latter is an extension to the standard behavior of Java formatter.)
         *
         * @param startIdx The start of the region to replace
         ******************************************************************************************/
        protected override void    replaceEscapeSequences( int startIdx )
        {
            targetString.SearchAndReplace( "%%" , "%"                  , startIdx );
            targetString.SearchAndReplace( "%n" , CString.NewLineChars , startIdx );
            targetString.Escape( Switch.Off, startIdx );
        }


        /** ****************************************************************************************
         * All that this formatter does with this overridden method is to convert strings to
         * upper case.
         *
         * @param startIdx  The int of the start of the field written in #targetString.
         *                  \c -1 indicates pre-phase.
         * @param target    The target string, only if different from field #targetString, which
         *                  indicates intermediate phase.
         * @return \c false, if the placeholder should be skipped (nothing is written for it).
         *         \c true otherwise.
         ******************************************************************************************/
        protected override bool    preAndPostProcess( int startIdx, AString target )
        {
            if( startIdx >= 0 && phaExtConversionUpper && target == null )
                targetString.ToUpper( startIdx );
            return true;
        }



        /** ****************************************************************************************
         * Makes some attribute adjustments and invokes standard implementation
         * @return \c true if OK, \c false if replacement should be aborted.
         ******************************************************************************************/
        protected override bool    checkStdFieldAgainstArgument()
        {
            bool wasFloat= phaType == PHType.Float;
            if( wasFloat )
            {
                if ( phaExtPrecision >= 0 )
                    phaNF.FractionalPartWidth= phaExtPrecision;
                else if( phaNF.FractionalPartWidth < 0 )
                    phaNF.FractionalPartWidth= phaExtDefaultPrecision;
            }

            bool result= base.checkStdFieldAgainstArgument();

            if( !wasFloat && phaType == PHType.Float )
            {
                if ( phaExtPrecision >= 0 )
                    phaNF.FractionalPartWidth= phaExtPrecision;
            }

            return result;
        }


} // class

} // namespace / EOF
