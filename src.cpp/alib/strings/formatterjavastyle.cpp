// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
#include "alib/alib.hpp"


#if !defined (HPP_ALIB_STRINGS_FORMATTER_JAVASTYLE)
    #include "alib/strings/formatterjavastyle.hpp"
#endif



// For code compatibility with ALox Java/C++
// We have to use underscore as the start of the name and for this have to disable a compiler
// warning. But this is a local code (cpp file) anyhow.
#if defined(__clang__)
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif


#if defined(__clang__)
    #pragma clang diagnostic pop
#endif


using namespace std;

namespace aworx { namespace lib { namespace strings
{

FormatterJavaStyle::FormatterJavaStyle()
: FormatterStdImpl( "FormatterJavaStyle" )
{
    // set number format to Java defaults
    DefaultNumberFormat.ForceDecimalPoint       = false;
    DefaultNumberFormat.WriteExponentPlusSign   = true;

    // set number format to Java defaults
    DefaultNumberFormat    .HexLiteralPrefix   =  "0X";

    DefaultNumberFormat    .OctLiteralPrefix   =
    AlternativeNumberFormat.OctLiteralPrefix   = "0";

    DefaultNumberFormat    .NANLiteral         =
    AlternativeNumberFormat.NANLiteral         = "NaN";
    DefaultNumberFormat    .INFLiteral         = "INFINITY";
    AlternativeNumberFormat.INFLiteral         = "Infinity";
}

void FormatterJavaStyle::resetPHAs()
{
    // first invoke parent's setting...
    FormatterStdImpl::resetPHAs();

    // ...then make some "Java like" adjustments
    phaExtConversionUpper               = false;
    phaAlignment                        = Alignment::Right;

    phaNF.ForceDecimalPoint             = false;
    phaNF.OmitTrailingFractionalZeros   = false;

    phaAlternateForm                    = false;

    phaExtPrecision                     = -1;
    phaExtDefaultPrecision              = 6;
}

integer FormatterJavaStyle::findPlaceholder()
{
    integer idx= 0;
    while(     (idx= parser.IndexOf('%', idx )) >= 0
           &&  (    parser.CharAt( idx + 1 ) == '%'
                 || parser.CharAt( idx + 1 ) == 'n'      ) )
    {
        // double ESC found (escaped %% or %n)
        idx+= + 2;
    }
    return idx;
}

void    FormatterJavaStyle::replaceEscapeSequences( integer startIdx )
{
    targetString->SearchAndReplace( "%%", "%",     startIdx );
    targetString->SearchAndReplace( "%n", NewLine, startIdx );
    targetString->_<false>( Format::Escape( Switch::Off, startIdx ) );
}


bool FormatterJavaStyle::parsePlaceholder()
{
    enum states
    {
        POSITION        =  1,
        FLAGS           =  2,
        WIDTH           =  3,
        PRECISION       =  4,
        TYPE            =  5,
        TYPE_SUFFIX     =  6,
        END             = 10,
    };

    states  state= POSITION;
    #define NEXTSTATE(s) { state= s; continue; }

    while( true )
    {
        // switch over state. With 'break' we consume one character (kind of success) while
        // with 'continue' we keep the current character (and go to another state)
        switch ( state )
        {
            case POSITION:
            {
                int argNo= -1;
                if ( parser.ConsumeChar('<') )
                {
                    argNo= phaPreviousArgumentIdx + 1;
                }
                else
                {
                    integer i= 0;
                    while(    i < parser.Length()
                           && isdigit( parser.CharAt<false>(i) ) )
                         ++i;

                    if(  i > 0 &&  parser.CharAt<false>(i) == '$')
                    {
                        parser.ConsumeDecDigits( argNo );
                        ALIB_ASSERT_RESULT_EQUALS( parser.ConsumeChar('$'), true );
                    }
                }
                if( argNo > 0 )
                    setArgument( argNo, true  );

                NEXTSTATE(FLAGS);
            }

            case FLAGS:
            {
                bool flagsDone= false;
                while(!flagsDone)
                {
                    switch ( parser.CharAtStart() )
                    {
                        case '-':
                            phaAlignment= Alignment::Left;
                            phaAlignmentSpecified= true;
                            break;

                        case '^':
                            phaAlignment= Alignment::Center;
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
                NEXTSTATE(WIDTH);
            }


            case WIDTH:
            {
                if( isdigit( parser.CharAtStart() ) )
                    parser.ConsumeDecDigits( phaWidth );

                NEXTSTATE(PRECISION);
            }

            case PRECISION:
            {
                if( parser.ConsumeChar( '.' ) && !parser.ConsumeDecDigits( phaExtPrecision ) )
                {
                    errorFormatString("Missing decimal value after precision symbol '.'");
                    return false;
                }

                NEXTSTATE(TYPE);
            }

            case TYPE:
            {
                char typeChar=  parser.CharAtStart();
                parser.ConsumeChars( 1 );

                char typeCharLower= static_cast<char>( tolower( typeChar ) );

                if ( typeCharLower == 'a' )
                {
                    errorFormatString("Hexadecimal float format not supported");
                    return false;
                }

                if( phaAlternateForm && String( "sSbBhHgGcCtT").IndexOf( typeChar ) >= 0 )
                {
                    errorFormatString(String128("Format Flags Conversion Mismatch Exception: Conversion = ")
                                      << typeChar << ", Flags = #" );
                    return false;
                }

                if( String("seg").IndexOf( typeChar ) >= 0 )
                {
                    if( typeChar != 's' )
                        phaNF.ExponentSeparator= AlternativeNumberFormat.ExponentSeparator;
                    phaNF.INFLiteral=        AlternativeNumberFormat.INFLiteral;
                    phaNF.NANLiteral=        AlternativeNumberFormat.NANLiteral;
                }

                if( String("SBCT").IndexOf( typeChar ) >= 0 )
                    phaExtConversionUpper= true;

                if( String("egf").IndexOf( typeCharLower ) < 0 )
                    phaCutContent=  phaExtPrecision;

                if( phaExtPrecision >=0 && String( "cCtTd").IndexOf( typeChar ) >= 0 )
                {
                    errorFormatString(String128("Precision not applicable for: Conversion = ")
                                      << typeChar << ", Precision = ." << phaExtPrecision );
                    return false;
                }

                     if( typeChar == 'X' || typeChar == 'H' )   phaNF.HexLowerCase= false;
                else if( typeChar == 'x' || typeChar == 'h' )   phaNF.HexLiteralPrefix= AlternativeNumberFormat.HexLiteralPrefix;


                switch ( typeCharLower )
                {
                    case 's':   phaExtPrecision=   -1;
                                break;

                    case 'b':   phaType=  PHType::Bool;                  break;
                    case 'c':   phaType=  PHType::Character;             break;
                    case 'd':   phaType=  PHType::IntBase10;             break;
                    case 'o':   phaType=  PHType::IntOctal;              break;
                    case 'x':   phaType=  PHType::IntHex;                break;
                    case 'h':   phaType=  PHType::IntHex;                break;
                    case 'e':   phaType=  PHType::Float;
                                phaNF.ForceScientific=  true;            break;
                    case 'g':   phaType= PHType::Float;                  break;
                    case 'f':   phaType= PHType::Float;
                                phaNF.IntegralPartMinimumWidth= 1;
                                phaExtDefaultPrecision=        -1;       break;

                    case 't':   phaExtDateTime= parser.CharAtStart();
                                parser.ConsumeChars( 1 );
                                switch( phaExtDateTime )
                                {
                                    case 'H': phaFormatSpec= "HH";       break;
                                    case 'k': phaFormatSpec= "H";        break;
                                    case 'I': phaFormatSpec= "KK";       break;
                                    case 'l': phaFormatSpec= "K";        break;
                                    case 'M': phaFormatSpec= "mm";       break;
                                    case 'S': phaFormatSpec= "ss";       break;
                                    // not supported: case 'L': ;
                                    // not supported: case 'N': ;
                                    // not supported: case 'p': ;
                                    // not supported: case 'z': ;
                                    // not supported: case 'Z': ;
                                    // not supported: case 's': ;
                                    // not supported: case 'Q': ;
                                    case 'B': phaFormatSpec= "MMMM";         break;
                                    case 'b': phaFormatSpec= "MMM";          break;
                                    case 'h':
                                    case 'A': phaFormatSpec= "dddd";         break;
                                    case 'a': phaFormatSpec= "ddd";          break;
                                    // not supported: case 'C': ;
                                    case 'Y': phaFormatSpec= "yyyy";         break;
                                    case 'y': phaFormatSpec= "yy";           break;
                                    // not supported: case 'j': ;
                                    case 'm': phaFormatSpec= "MM";           break;
                                    case 'd': phaFormatSpec= "dd";           break;
                                    case 'e': phaFormatSpec= "d";            break;

                                    case 'R': phaFormatSpec= "HH:mm";        break;
                                    case 'T': phaFormatSpec= "HH:mm:ss";     break;
                                    // not supported: case 'r': ;

                                    case 'D': phaFormatSpec= "MM/dd/yy";     break;
                                    case 'F': phaFormatSpec= "yyyy-MM-dd";   break;
                                    // not supported: case 'c': ;




                                    default:
                                    errorFormatString(String128("Unknown date/time conversion suffix character '")
                                                      << phaExtDateTime << '\'');
                                    return  false;

                                }
                                break;

                    default:
                        errorFormatString("Unknown Format Conversion Exception");
                        return false;
                }

                NEXTSTATE(TYPE_SUFFIX);
            }

            case TYPE_SUFFIX:
            {
                NEXTSTATE(END);
            }

            case END:
                //parser.ConsumeChars(1);
                return true;

        } // state switch

    } // read loop

}

void    FormatterJavaStyle::preAndPostProcess( integer startIdx )
{
    if( startIdx >= 0 && phaExtConversionUpper )
        targetString->ToUpper( startIdx );
}

bool  FormatterJavaStyle::checkStdFieldAgainstArgument()
{
    bool wasFloat= phaType == PHType::Float;
    if( wasFloat )
    {
        if ( phaExtPrecision >= 0 )
            phaNF.FractionalPartWidth= phaExtPrecision;
        else if( phaNF.FractionalPartWidth < 0 )
            phaNF.FractionalPartWidth= phaExtDefaultPrecision;
    }

    bool result= FormatterStdImpl::checkStdFieldAgainstArgument();

    if( !wasFloat && phaType == PHType::Float )
    {
        if ( phaExtPrecision >= 0 )
            phaNF.FractionalPartWidth= phaExtPrecision;
    }

    return result;
}


}}}// namespace aworx::lib::strings
