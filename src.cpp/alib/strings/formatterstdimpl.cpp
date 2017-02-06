// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
#include "alib/alib.hpp"


#if !defined (HPP_ALIB_STRINGS_FORMATTER_STD_IMPL)
    #include "alib/strings/formatterstdimpl.hpp"
#endif

#if !defined (_GLIBCXX_CMATH) && !defined (_CMATH_)
    #include <cmath>
#endif


// For code compatibility with ALox Java/C++
// We have to use underscore as the start of the name and for this have to disable a compiler
// warning. But this is a local code (cpp file) anyhow.
#if defined(__clang__)
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif

#define _NC _<false>

#if defined(__clang__)
    #pragma clang diagnostic pop
#endif


using namespace std;
using namespace aworx;

namespace aworx { namespace lib { namespace strings {

FormatterStdImpl::FormatterStdImpl( const String& formatterClassName )
: formatterName( formatterClassName )
{
    AlternativeNumberFormat.SetFromLocale();

    AlternativeNumberFormat.ExponentSeparator=  "e";
    AlternativeNumberFormat.NANLiteral       =  "nan";
    AlternativeNumberFormat.INFLiteral       =  "inf";
}

int  FormatterStdImpl::format(  AString&        pTargetString,
                                  const String&   pFormatString,
                                  const Boxes&    pArguments,
                                  int             pArgOffset        )
{
    // check for newline. This indicates that this is not a formatString string
    if( pFormatString.IndexOf('\n') >= 0 )
        return 0;

    // save parameters/init state
    targetString=       &pTargetString;
    formatString=       &pFormatString;
    arguments=          &pArguments;
    argOffset=           pArgOffset;

    // initialize state info
    nextAutoIdx=        0;
    argsConsumed=       0;

    parser=             formatString;

    for(;;)
    {
        integer actLength= pTargetString.Length();

        // find start of esc
        integer escStart= findPlaceholder();
        if ( escStart < 0 )
        {
            // write rest of formatString string (only if we had consumed before)
            if( argsConsumed > 0 && parser.Length() > 0 )
            {
                pTargetString._NC( parser );
                replaceEscapeSequences( actLength );
            }
            return argsConsumed;
        }

        // write string before ESC code
        if ( escStart == 0 )
            parser.ConsumeChars<false>(1);
        else
        {
            parser.ConsumeChars<false>( escStart, pTargetString, 1, CurrentData::Keep );
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
        ALIB_ASSERT( phaArgument != nullptr );



        // write field
        preAndPostProcess( -1 );
        integer actIdx= targetString->Length();
        if ( !writeCustomFormat() )
        {
            // standard format
            if (    ( phaFormatSpec.IsNotEmpty()  && !parseStdFormatSpec() )
                 || !checkStdFieldAgainstArgument() )
                return argsConsumed;

            // write argument
            writeStdArgument();
        }

        preAndPostProcess( actIdx );


    }// main loop searching next escape sequence
}

void FormatterStdImpl::resetPHAs()
{
    phaNF.Set( &DefaultNumberFormat );
    phaNF.HexLowerCase          = true;
    phaType=                    PHType::NotGiven;
    phaPreviousArgumentIdx=     phaArgumentIdx;
    phaArgument=                nullptr;
    phaWidth=                    0;
    phaArgumentIdx=
    phaCutContent=              -1;

    phaAlignmentSpecified=      false;
    phaAlignment=               Alignment::Left;
    phaSignPaddingMode=         false;
    phaFillChar=                 ' ';
    phaWriteBinOctHexPrefix=    false;
    phaIsPercentage=            false;
    phaTypeCode=                '\0';
    phaFormatSpec.SetNull();
}

bool    FormatterStdImpl::setArgument( int pos, bool countStartsWith1 )
{
    if( countStartsWith1 )
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
    size_t  argIdx= static_cast<size_t>( argOffset + phaArgumentIdx );
    if( argIdx >= arguments->size() )
    {
        String64 msg; msg._NC("Missing argument #" )._NC( phaArgumentIdx + (countStartsWith1 ? 1 : 0) );
        errorFormatString( msg );
        return false;
    }

    phaArgument= &(*arguments)[argIdx];
    return true;


}

bool    FormatterStdImpl::checkStdFieldAgainstArgument()
{
    const Box* arg= phaArgument;


    // types bool and hashcode always works!
    if(   phaType == PHType::Bool
       || phaType == PHType::HashCode )
        return true;


    if ( arg->IsType<double>() )
    {
        if( phaType == PHType::NotGiven )
            phaType= PHType::Float;

        if(  phaType == PHType::Float )
            return true;

        errorFormatString( String128("Incompatible format code '") << phaTypeCode
                                  << "' for argument #"            << phaArgumentIdx
                                  << " which is of floating point type" );

        return false;
    }

    if(    arg->IsType<boxed_int >()
        || arg->IsType<boxed_uint>() )
    {
        if( phaType == PHType::NotGiven )
            phaType= PHType::IntBase10;
        if(     phaType == PHType::IntBase10
            ||  phaType == PHType::IntBinary
            ||  phaType == PHType::IntOctal
            ||  phaType == PHType::IntHex
            ||  phaType == PHType::Float
            ||  phaType == PHType::Character
            )
        {
            return true;
        }

        errorFormatString( String128("Incompatible format code '") << phaTypeCode
                                  << "' for argument #"            << phaArgumentIdx
                                  << " which is of integer type" );
        return false;

    }

    if(   arg->IsType<char   >()
       || arg->IsType<wchar_t>() )
    {
        if( phaType == PHType::NotGiven )
            phaType=   PHType::Character;
        if( phaType == PHType::Character )
            return true;

        errorFormatString( String128("Incompatible format code '") << phaTypeCode
                                  << "' for argument #"            << phaArgumentIdx
                                  << " which is of character type" );
        return false;
    }

    if( phaType == PHType::NotGiven )
        phaType= PHType::String;

    return true;
}

void    FormatterStdImpl::writeStdArgument()
{
    // store actual target length to fix some float exceptional cases (inf, nan)
    integer oldTargetLength= targetString->Length();

    // write to temp buffer first, if we have a field width given
    AString* target;

    if ( phaWidth > 0 )
    {
        target= &(fieldBuffer._());

        // set default alignment
        if(     !phaAlignmentSpecified
             &&  phaType != PHType::String
             &&  phaType != PHType::Character        )
             phaAlignment= Alignment::Right;
    }
    else
        target= targetString;

    integer fieldStartIdx= target->Length();


    // the main switch over the type
    switch( phaType )
    {
        case PHType::NotGiven:
            ALIB_ERROR( "Internal error: this should have been handled by method checkStdFieldAgainstArgument" );
        break;

        case PHType::String:
            phaArgument->Invoke<boxing::IApply>( *target );
        break;

        case PHType::Bool:
            target->_NC( phaArgument->UnboxRaw() == 0 ? "false" : "true" );
        break;

        case PHType::Character:
        {
            wchar_t wc= 0;
                 if (phaArgument->IsType<char      >()) wc= static_cast<wchar_t>( phaArgument->Unbox<char      >() );
            else if (phaArgument->IsType<wchar_t   >()) wc=                       phaArgument->Unbox<wchar_t   >()  ;
            else if (phaArgument->IsType<boxed_int >()) wc= static_cast<wchar_t>( phaArgument->Unbox<boxed_int >() );
            else if (phaArgument->IsType<boxed_uint>()) wc= static_cast<wchar_t>( phaArgument->Unbox<boxed_uint>() );

            if ( wc == 0)
                wc= L'?';
            target->_NC( wc );
        }
        break;

        case PHType::IntBase10:
        {
            if (phaSignPaddingMode)
                phaNF.DecMinimumFieldWidth= phaWidth;

            if( phaArgument->IsType<boxed_int>())
                target->_NC( strings::Format( phaArgument->Unbox<boxed_int>(),   &phaNF ) );
            else
                target->_NC( strings::Format( phaArgument->Unbox<boxed_uint>(),  &phaNF ) );
        }
        break;


        case PHType::IntBinary:
        case PHType::HashCode:
        case PHType::IntHex:
        case PHType::IntOctal:
        {
            int digits= phaWidth;
            if( phaWriteBinOctHexPrefix )
            {
                target->_NC( phaType == PHType::IntOctal  ? phaNF.OctLiteralPrefix :
                             phaType == PHType::IntBinary ? phaNF.BinLiteralPrefix :
                                                            phaNF.HexLiteralPrefix       );
                digits-= static_cast<int>((target->Length() - fieldStartIdx));
                if( phaWidth > 0 && digits <= 0 )
                {
                    target->SetLength( fieldStartIdx + phaWidth );
                    break; // stop output, no space left
                }
            }
            if ( digits < 0 )
                digits= 0;
                 if( phaType == PHType::IntOctal)  target->_NC( Format::Oct(  phaArgument->UnboxRaw(), digits, &phaNF ) );
            else if( phaType == PHType::IntBinary) target->_NC( Format::Bin(  phaArgument->UnboxRaw(), digits, &phaNF ) );
            else                                   target->_NC( Format::Hex(  phaArgument->UnboxRaw(), digits, &phaNF ) );



        }
        break;

        case PHType::Float:
        {
            // get value
            double value=    phaArgument->IsType<double>()    ?                      phaArgument->Unbox<double>    ()
                          :  phaArgument->IsType<boxed_int>() ? static_cast<double>( phaArgument->Unbox<boxed_int> () )
                          :                                     static_cast<double>( phaArgument->Unbox<boxed_uint>() );
            if( phaIsPercentage )
                value*= 100.0;

            if (phaSignPaddingMode)
            {
                // write sign upfront and set fill character to 0
                if( !isnan( value ) )
                {
                    if( std::signbit(value) )
                    {
                        targetString->_NC( '-' );
                        phaWidth--;
                        value= -value;
                    }
                    else if( phaNF.PlusSign != '\0' )
                    {
                        targetString->_NC( phaNF.PlusSign );
                        phaWidth--;
                    }
                    phaNF.PlusSign= '\0';

                    if ( !phaNF.WriteGroupChars || phaNF.ThousandsGroupChar == '\0')
                        phaFillChar= '0';
                    else
                    {
                        // calculate integral part width
                        if ( phaWidth > 0 && !phaNF.ForceScientific)
                        {
                            phaNF.IntegralPartMinimumWidth= phaWidth - 1; // -1 == the dot

                            if( phaNF.FractionalPartWidth >= 0 )
                                phaNF.IntegralPartMinimumWidth-= phaNF.FractionalPartWidth;

                            if( phaIsPercentage )
                                phaNF.IntegralPartMinimumWidth--;

                            // check
                            if( phaNF.IntegralPartMinimumWidth <= 0)
                                phaNF.IntegralPartMinimumWidth= 1;
                        }
                    }
                }

            }

            target->_NC( strings::Format( value, &phaNF ) );

            if( phaIsPercentage )
                target->_NC( '%' );


            // if nan or inf was written, we fill with spaces
            if (     phaSignPaddingMode
                && (     target->IndexOf(phaNF.NANLiteral, oldTargetLength) >= 0
                     ||  target->IndexOf(phaNF.INFLiteral, oldTargetLength) >= 0 ) )
                phaFillChar= ' ';

        }
        break;
    }

    // apply cutting
    if ( phaCutContent >= 0 )
    {
        integer addedLength= CString::LengthWhenConvertedToWChar( target->Buffer() + oldTargetLength,
                                                                   target->Length() - oldTargetLength );

        // too much added?
        if( addedLength > phaCutContent )
        {
            // was not unicode?
            if( addedLength == target->Length() - oldTargetLength )
                target->SetLength( oldTargetLength + phaCutContent );

            // in the unicode case, it gets complicated: we have to convert to unicode and
            // then convert a part of it back! We do this only for a certain length
            else if( addedLength < 256)
            {
                wchar_t wBuf[256];
                {
                    target->ToWString( wBuf, 255, oldTargetLength );
                    target->SetLength( oldTargetLength );
                    target->Append( wBuf,phaCutContent );
                }
            }
        }
    }



    // if field mode, we have to apply the field buffer as a field to the real target now
    if( target ==  &fieldBuffer )
        targetString->_NC( Format::Field( fieldBuffer, phaWidth, phaAlignment, phaFillChar ) );

}

bool    FormatterStdImpl::writeCustomFormat()
{
    if( phaFormatSpec.IsEmpty() ||  !phaArgument->HasInterface<boxing::IFormat>() )
        return false;

    phaArgument->Invoke<boxing::IFormat>( phaFormatSpec, *targetString );
    return true;
}

void    FormatterStdImpl::errorFormatString( const String& msg )
{
    #if ALIB_DEBUG
    if ( !WriteErrorsToTargetString && !WriteALibErrorReports )
        return;
    #else
    if ( !WriteErrorsToTargetString )
        return;
    #endif

    String512 repMsg;
    repMsg._NC( msg )
          ._NC( " at index " )._NC( formatString->Length() - parser.Length() - 1 )
          ._NC( " in format String \"" )._NC( formatString )._NC("\".");

    #if ALIB_DEBUG
    if ( WriteErrorsToTargetString )
    #endif
        targetString->_NC(repMsg);

    #if ALIB_DEBUG
      if( WriteALibErrorReports )
          ALIB_ERROR( repMsg.ToCString() );
    #endif
}



}}}// namespace aworx::lib::strings
