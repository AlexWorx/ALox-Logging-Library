// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
#include "alib/alib.hpp"


#if !defined (HPP_ALIB_STRINGS_FORMATTER_PYTHONSTYLE)
    #include "alib/strings/formatterpythonstyle.hpp"
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

FormatterPythonStyle::FormatterPythonStyle()
: FormatterStdImpl( "FormatterPythonStyle" )
{
    // set number format to python defaults
    DefaultNumberFormat.ForceDecimalPoint       = false;
    DefaultNumberFormat.WriteExponentPlusSign   = true;

}

void FormatterPythonStyle::resetPHAs()
{
    // first invoke parent's setting...
    FormatterStdImpl::resetPHAs();

    // ...then make some "python like" adjustments
    phaExtConversion= nullptr;

    phaNF.ForceDecimalPoint             = false;
    phaNF.ExponentSeparator             = AlternativeNumberFormat.ExponentSeparator; // choose lower case as default
    phaNF.INFLiteral                    = AlternativeNumberFormat.INFLiteral;        // choose lower case as default
    phaNF.NANLiteral                    = AlternativeNumberFormat.NANLiteral;        // choose lower case as default
    phaNF.OmitTrailingFractionalZeros   = true;

    phaExtPrecision                     = -1;
    phaExtDefaultPrecision              = 6;
}

integer FormatterPythonStyle::findPlaceholder()
{
    integer idx= 0;
    while(     (idx= parser.IndexOf('{', idx )) >= 0
           &&  parser.CharAt( idx + 1 ) == '{'                   )
    {
        // double ESC found (escaped {{)
        idx+= + 2;
    }
    return idx;
}

bool FormatterPythonStyle::parsePlaceholder()
{
    enum states
    {
        POSITION                    = 1,
        CONVERSION                  = 2,
        COLON                       = 3,
        FORMAT_SPEC                 = 4,
        END                         = 10,
    };

    states  state= POSITION;
    #define NEXTSTATE(s) { state= s; continue; }

    while( true )
    {
        // switch over state. With 'break' we consume on character (kind of success) while
        // with 'continue' we keep the current character (and go to another state)
        switch ( state )
        {
            case POSITION:

                if( isdigit( parser.CharAtStart() )  )
                {
                    int argNo;
                    parser.ConsumeDecDigits( argNo );
                    setArgument( argNo, false );
                }
                NEXTSTATE(CONVERSION);


            case CONVERSION:
                if( parser.CharAtStart() == '!' )
                {
                    integer endConversion= parser.IndexOfAny(":}", Inclusion::Include );
                    if( endConversion < 0 )
                    {
                        errorFormatString( "Closing replacement bracket '}' not found" );
                        return false;
                    }

                    parser.ConsumeChars( endConversion, &phaExtConversion );
                }
                NEXTSTATE(COLON);

            case COLON:
                if( parser.CharAtStart() != ':'  )
                {
                    state= END;
                    continue;
                }

                parser.ConsumeChars(1);
                NEXTSTATE(FORMAT_SPEC)

            case FORMAT_SPEC:
            {
                // find end of format spec (allow "\}" in format string)
                integer eoFormatSpec= -1;
                do
                {
                    eoFormatSpec= parser.IndexOf( '}', eoFormatSpec + 1 );
                }
                while(      eoFormatSpec > 0
                        &&  parser.CharAt( eoFormatSpec - 1) == '\\' );

                if ( eoFormatSpec < 0 )
                {
                    errorFormatString( "Closing replacement bracket '}' not found" );
                    return false;
                }

                // extract format spec to separate substring
                parser.ConsumeChars( eoFormatSpec, &phaFormatSpec ) ;

                NEXTSTATE(END)
            }

            case END:
                if( parser.CharAtStart() != '}'  )
                {
                    errorFormatString( "Closing replacement bracket '}' not found" );
                    return false;
                }
                parser.ConsumeChars(1);
                return true;

        } // state switch

    } // read loop

}

bool FormatterPythonStyle::parseStdFormatSpec()
{
    // parse alignment and fill character. This is a bit tricky to shorten the code.
    // The alignment token <,>,^ or = can be on first or second position. If second, then the
    // first was a fill character. Therefore we loop from 0 to 1....
    integer charsToConsume= 1;
    phaAlignmentSpecified= true;
    Substring& formatSpec= phaFormatSpec;


    int cNo= 0;
    do switch ( formatSpec.CharAt( cNo++ ) )
    {
        case '<': phaAlignment= Alignment::Left;    break;
        case '>': phaAlignment= Alignment::Right;   break;
        case '^': phaAlignment= Alignment::Center;  break;
        case '=': phaAlignment= Alignment::Right;
                  phaSignPaddingMode=  true;        break;

        default:
            if(cNo == 1 )
            {
                charsToConsume= 2;
                phaFillChar= formatSpec.CharAtStart();
            }
            else
            {
                charsToConsume= 0;
                phaFillChar= ' ';
                phaAlignmentSpecified= false;
            }
        break;
    }
    while( cNo < 2 && charsToConsume != 1 );
    formatSpec.ConsumeChars( charsToConsume );

    // other things to parse
    char actChar;
    while( (actChar= formatSpec.CharAtStart()) != '\0' )
    {
        // width
        if( isdigit( actChar ) )
        {
            // Python doc says:
            //   When no explicit alignment is given, preceding the width field by a zero ('0') character
            //   enables sign-aware zero-padding for numeric types.
            //   This is equivalent to a fill character of '0' with an alignment type of '='.
            if ( actChar == '0' )
                phaSignPaddingMode= true;
            formatSpec.ConsumeDecDigits( phaWidth );

            continue; // not consume below
        }

        // precision. Python doc says:
        // "The precision is a decimal number indicating how many digits should be displayed
        // after the decimal point for a floating point value formatted with 'f' and 'F', or
        // before and after the decimal point for a floating point value formatted with 'g' or 'G'.
        // For non-number types the field indicates the maximum field size - in other words,
        // how many characters will be used from the field content. The precision is not
        // allowed for integer values."
        else if( actChar == '.' )
        {
            formatSpec.ConsumeChars( 1 );
            if ( ! formatSpec.ConsumeDecDigits( phaExtPrecision ) )
            {
                errorFormatString( "Missing precision value after '.' character" );
                return false;
            }
            continue;
        }


        // ----------------------------- Types -------------------------------------
        else if (String("sdcboxXeEfFngGhHB%").IndexOf( actChar ) >= 0 )
        {
            if ( phaTypeCode != '\0' )
            {
                String128 msg;
                msg._( "Duplicate type code '")._( actChar )._( "' given (previous was '")
                   ._( phaTypeCode )._("')");
                errorFormatString( msg );
                return false;
            }

            phaTypeCode= actChar;

            if( String("EGF").IndexOf( actChar ) >= 0 )
            {
                phaNF.ExponentSeparator= DefaultNumberFormat.ExponentSeparator;
                phaNF.INFLiteral=        DefaultNumberFormat.INFLiteral;
                phaNF.NANLiteral=        DefaultNumberFormat.NANLiteral;
            }


            switch( actChar )
            {
                case 's':   phaType= PHType::String;                break;
                case 'd':   phaType= PHType::IntBase10;             break;
                case 'c':   phaType= PHType::Character;             break;
                case 'b':   phaType= PHType::IntBinary;             break;
                case 'o':   phaType= PHType::IntOctal;              break;

                case 'X':   phaNF.HexLowerCase= false;              ALIB_FALLTHROUGH
                case 'x':   phaType= PHType::IntHex;                break;

                case 'H':   phaNF.HexLowerCase= false;              ALIB_FALLTHROUGH
                case 'h':   phaType= PHType::HashCode;              break;
                case 'B':   phaType= PHType::Bool;                  break;

                // float types
                case 'E':
                case 'e':   phaType= PHType::Float;
                            phaNF.ForceScientific= true;            break;

                case '%':   phaIsPercentage= true;                  ALIB_FALLTHROUGH
                case 'f':
                case 'F':   phaNF.OmitTrailingFractionalZeros= false;
                            phaType= PHType::Float;                 break;

                case 'n':   phaNF.DecimalPointChar=   AlternativeNumberFormat.DecimalPointChar;
                            phaNF.ThousandsGroupChar= AlternativeNumberFormat.ThousandsGroupChar;
                                                                   ALIB_FALLTHROUGH
                case 'G':                                          ALIB_FALLTHROUGH
                case 'g':   phaType= PHType::Float;
                            phaExtDefaultPrecision=   -1;
                break;

                default:    ALIB_ERROR("Unhandled character in choices string above");
                            return false;

            }//switch
        }


        // others
        else switch( actChar )
        {
            // sign
            case '+':   phaNF.PlusSign= '+' ;  break;
            case '-':   phaNF.PlusSign= '\0';  break;
            case ' ':   phaNF.PlusSign= ' ' ;  break;

            // alternate version ('#')
            case '#':   phaWriteBinOctHexPrefix=             true;
                        phaNF.ForceDecimalPoint=             true;
                        phaNF.OmitTrailingFractionalZeros=   false;
            break;

            // Enable grouping
            case ',':   phaNF.WriteGroupChars= true;
                        break;


            default:    errorFormatString( String32("Unknown format character '")._( actChar )._('\'')  );
                        return false;
        }

        formatSpec.ConsumeChars(1);
    }

    return true;
}

void    FormatterPythonStyle::replaceEscapeSequences( integer startIdx )
{
    targetString->SearchAndReplace( "{{" , "{" , startIdx );
    targetString->SearchAndReplace( "}}" , "}" , startIdx );
    targetString->_<false>( Format::Escape( Switch::Off, startIdx ) );
}

void    FormatterPythonStyle::preAndPostProcess( integer startIdx )
{
    bool isPostProcess= startIdx>= 0;
    Substring conversion= phaExtConversion;

    while( conversion.IsNotEmpty() )
    {
        if( !conversion .ConsumeChar('!') )
        {
            errorFormatString( String256("Expected '!' in (rest of) conversion string \"!")._( conversion )._('"')  );
            return;
        }

             if( conversion.ConsumePartOf("Upper", 1, Case::Ignore) > 0 )   { if (isPostProcess) targetString->ToUpper( startIdx );                 }
        else if( conversion.ConsumePartOf("Lower", 1, Case::Ignore) > 0 )   { if (isPostProcess) targetString->ToLower( startIdx );                 }
        else if( conversion.ConsumePartOf("str"  , 1, Case::Ignore) > 0
               ||conversion.ConsumePartOf("Quote", 1, Case::Ignore) > 0 )   { if (isPostProcess) targetString->InsertAt<false>("\"", startIdx)._<false>( "\"" );  }
        else if( conversion.ConsumePartOf("Tab"  , 1, Case::Ignore) > 0 )
        {
            char tabChar= ' ';
            if( conversion.ConsumeChar('C', Case::Ignore ) )
                tabChar= conversion.ConsumeChar();
            if (tabChar == '\0' )
                tabChar= ' ';
            int tabSize;
            if( !conversion.ConsumeDecDigits<int>( tabSize ) )
                tabSize= 8;

            if( !isPostProcess )
                targetString->_<false>( Format::Tab( tabSize, -1, 1, tabChar ) );

        }

        else if( conversion.ConsumePartOf("ATab"  , 2, Case::Ignore) > 0 )
        {

            if( conversion.ConsumePartOf("Reset"  , 1, Case::Ignore) > 0 )
            {
                if(!isPostProcess)
                    TabSizes.Reset();
            }
            else
            {
                char tabChar= ' ';
                if( conversion.ConsumeChar('C', Case::Ignore ) )
                    tabChar= conversion.ConsumeChar();
                if (tabChar == '\0' )
                    tabChar= ' ';

                int growth;
                if( !conversion.ConsumeDecDigits<int>( growth ) )
                    growth= 3;
                else
                    growth--;

                if( !isPostProcess )
                {
                    integer tabStop= TabSizes.Next( targetString->Length() + 1, growth );
                    targetString->InsertChars<false>( tabChar, tabStop - targetString->Length() );
                }
            }
        }

        else if(    conversion.ConsumePartOf("Esc"  , 1, Case::Ignore) > 0
                 || conversion.ConsumePartOf("A"    , 1, Case::Ignore) > 0)
        {
            Switch toESC= Switch::On;
            conversion.ConsumeChar('<');
            if(conversion.ConsumeChar('>') )
                toESC=  Switch::Off;

            if( isPostProcess )
                targetString->_<false>( Format::Escape( toESC, startIdx ) );
        }

        // error (not recognized)
        else
        {
            errorFormatString( String256("Unknown conversion string \"!")._( conversion )._('"')  );
            return;
        }

    }
}

bool  FormatterPythonStyle::checkStdFieldAgainstArgument()
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

    if( phaType == PHType::String || phaType == PHType::Bool  )
        phaCutContent= phaExtPrecision;
    else if ( phaExtPrecision >= 0 && phaType != PHType::Float )
    {
        errorFormatString( "Precision not allowed in integer format specifier" );
        return false;
    }

    return result;

}


}}}// namespace aworx::lib::strings
