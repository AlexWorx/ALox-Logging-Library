// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
#include "alib/stdafx_alib.h"

#include "alib/alib.hpp"

#if !defined (HPP_AWORX_LIB_STRINGS_NUMBERFORMAT)
    #include "alib/strings/numberformat.hpp"
#endif

#if !defined (HPP_AWORX_LIB_STRINGS_ASTRING)
    #include "alib/strings/asalloc.hpp"
#endif
#include <clocale>
#include <cmath>
#include <algorithm>

#if defined(_MSC_VER)
    #include <intrin.h>
#endif

using namespace std;


namespace aworx {
namespace           lib {
namespace                   strings {

#if !defined( IS_DOXYGEN_PARSER )

constexpr const uint64_t pow10_0to19[]=
{
    1UL,                          // 10^ 0
    10UL,                         // 10^ 1
    100UL,                        // 10^ 2
    1000UL,                       // 10^ 3
    10000UL,                      // 10^ 4
    100000UL,                     // 10^ 5
    1000000UL,                    // 10^ 6
    10000000UL,                   // 10^ 7
    100000000UL,                  // 10^ 8
    1000000000UL,                 // 10^ 9
    10000000000UL,                // 10^10
    100000000000UL,               // 10^11
    1000000000000UL,              // 10^12
    10000000000000UL,             // 10^13
    100000000000000UL,            // 10^14
    1000000000000000UL,           // 10^15
    10000000000000000UL,          // 10^16
    100000000000000000UL,         // 10^17
    1000000000000000000UL,        // 10^18
    10000000000000000000UL,       // 10^19
};

#endif

// #################################################################################################
// static fields
// #################################################################################################
NumberFormat                NumberFormat::Global;

// #################################################################################################
//  Integer conversion
// #################################################################################################

int64_t NumberFormat::StringToInteger( const AS& src, int& idx )
{
    int64_t retVal=    0;

    // check
    int length= src.Length();
    if( idx >= length )
        return 0;

    const char* buf=    src.Buffer();
    char        c=      buf[idx];

    // read sign
    bool negative= false;
         if ( c == '+' )     idx++;
    else if ( c == '-' )  {  idx++;   negative= true;  }

    // read number
    while ( idx < length )
    {
        c= buf[idx];
        if ( c < '0' || c > '9' )
            break;

        retVal= ( retVal * 10 ) + ( (int) ( c - '0' ) );
        idx++;
    }
    // that's it
    return negative? -retVal : retVal;
}

int NumberFormat::IntegerToString( uint_fast64_t value, char* buffer, int idx, int minDigits )
{
    // adjust minDigits to 1..20 and maxDigits to 1..minDigits
    if ( minDigits < 1  )           minDigits= 1;
    if ( minDigits > 20 )           minDigits= 20;

    // special treatment for 0 values
    if( value == 0 )
    {
        for (int i= 0; i< minDigits ; i++ )
            buffer[idx++]= '0';
        return idx;
    }

    // get a maximum value for the number of digits to print
    int sizeHint;

    #if defined(__GNUC__) || defined(_WIN64)

        int binDigits;
        #if defined(__GNUC__)
        {
                 if( sizeof(uint_fast64_t) == sizeof( unsigned int       ) )  binDigits= 64 - __builtin_clz  ( value );
            else if( sizeof(uint_fast64_t) == sizeof( unsigned long      ) )  binDigits= 64 - __builtin_clzl ( value );
            else if( sizeof(uint_fast64_t) == sizeof( unsigned long long ) )  binDigits= 64 - __builtin_clzll( value );
        }
        #else
        {
            #include <intrin.h>
            unsigned long Index;
            _BitScanReverse64( &Index, value );
            binDigits= Index + 1;
        }
        #endif

          sizeHint= 1;
          if (binDigits >=  4) sizeHint++; // 2 digits
          if (binDigits >=  7) sizeHint++; // 2 digits
          if (binDigits >= 10) sizeHint++; // 3 digits
          if (binDigits >= 14) sizeHint++; // 4 digits
          if (binDigits >= 17) sizeHint++; // 5 digits
          if (binDigits >= 20) sizeHint++; // 6 digits
          if (binDigits >= 24) sizeHint++; // 7 digits
          if (binDigits >= 26) sizeHint= 20;
          sizeHint= sizeHint;
          if ( sizeHint  < minDigits )    sizeHint= minDigits;

    #else

        sizeHint= 20;;
        int digits= sizeHint/2;
        while( digits > minDigits && value < pow10_0to19[digits] )
        {
            sizeHint= digits;
            digits/= 2;
        }

    #endif

    // main loop
    int  actDigit=      sizeHint;
    bool printStarted=  false;
    while ( --actDigit >= 0)
    {
        // rest is zeros?
        if ( value == 0 )
        {
            while ( actDigit >= 0)
            {
                if (  (printStarted|= actDigit-- < minDigits ) == false )
                    continue;
                buffer[idx++]= '0';
            }
            return idx;
        }

        // get next d
        unsigned int digitValue=   (unsigned int) ( value / pow10_0to19[actDigit] );
        ALIB_ASSERT( digitValue <= 9 );

        // don't write, yet?
        if ( (printStarted|= digitValue != 0 || actDigit < minDigits) == false )
            continue;

        // write the digit
        buffer[idx++]= (char) ( 48 + digitValue ); // 48= '0'

        // next
        value=    value % pow10_0to19[actDigit];
    }

    return idx;
}

// #################################################################################################
//  Float conversion
// #################################################################################################

void NumberFormat::SetFromLocale()
{
    struct lconv * lc=localeconv();

    DecimalPointCharacter=      *(lc->decimal_point);
}

int NumberFormat::FloatToString( double value,  char* buffer, int idx )
{
    // for debugging:
    // char* origBuffer= buffer;
    // for( int i= 0; i<24; i++ )
    //   origBuffer[i]= '\0';

    constexpr int MaxFloatSignificantDigits= 16;

    // negative? -> turn positive
    if ( value < 0.0 )
    {
        buffer[idx++]= '-';
        value= -value;
    }

    // calc dot position
    int  exp10=      value != 0.0   ? (int) floor((log10( value ) ))
                                    : 0;

    // decide if we are using scientific format (with e) or not
    bool scientific=  (     ForceScientificFormat
                        || (     MinIntegralDigits < 0
                             &&  FractionalDigits  < 0
                             &&  ( exp10 > 6 || exp10 <= -5 )
                           )    );

    int minIntegralDigits= (std::min) ( MinIntegralDigits, 15 ); //Note: the brackets around (std::min) are
    int fractionalDigits=  (std::min) ( FractionalDigits,  15 ); //      to avoid conflicts with Windows 'max' macro



    // result variables used for output
    uint_fast64_t intPart;
    uint_fast64_t fractPart;
    int unusedFractDigits;
    int firstNonZero;
    int intPartSize;

    // scientific output
    if ( scientific )
    {
        int dotPos=  MaxFloatSignificantDigits - exp10;
        intPart=     llrint( value * pow( 10, dotPos ) );
        fractPart=   intPart %  pow10_0to19[ MaxFloatSignificantDigits ];
        intPart=     intPart /  pow10_0to19[ MaxFloatSignificantDigits ];
        intPartSize= 1;

        // determine first non zero fract number
        firstNonZero= 0;
        if ( fractPart > 0 )
        {
            ALIB_ASSERT( MaxFloatSignificantDigits - firstNonZero < 20);
            while ( fractPart < pow10_0to19[ MaxFloatSignificantDigits - firstNonZero - 1 ] )
                firstNonZero++;
            ALIB_ASSERT( MaxFloatSignificantDigits - firstNonZero > 0);
        }
        firstNonZero++;

        unusedFractDigits= fractionalDigits >= 0 ?  MaxFloatSignificantDigits - fractionalDigits
                                                 :  1;
    }

     // normal output, number > 0
     else if (exp10 >= 0 )
     {
        intPartSize= MaxFloatSignificantDigits - exp10;
        ALIB_ASSERT( intPartSize > 0  && intPartSize <= MaxFloatSignificantDigits );
        intPart=     llrint( value * pow( 10, intPartSize ) );
        fractPart=   intPart %  pow10_0to19[ intPartSize ];
        intPart=     intPart /  pow10_0to19[ intPartSize ];

        // determine first non zero fract number
        firstNonZero= 0;
        if ( fractPart > 0 )
        {
            ALIB_ASSERT( intPartSize - firstNonZero < 20 );
            while ( fractPart < pow10_0to19[ intPartSize - firstNonZero - 1 ] )
                firstNonZero++;
            ALIB_ASSERT( intPartSize - firstNonZero > 0 );
        }
        firstNonZero++;

        unusedFractDigits= fractionalDigits >= 0 ?  intPartSize - fractionalDigits
                                                 :  1;
     }

    // normal output, number  < 0
    else
    {
        // just zeros? -> write them and return
        firstNonZero= -exp10;
        intPart=      0;
        intPartSize=  1;
        fractPart=    llrint( value * pow( 10, MaxFloatSignificantDigits + firstNonZero) );
        unusedFractDigits= fractionalDigits >= 0 ?  MaxFloatSignificantDigits - ( fractionalDigits - firstNonZero )
                                                 :  1;
     }

    // cut fract digits and round it up
    if (     (fractionalDigits < 0 || fractionalDigits  >= firstNonZero - 1 )
         &&  unusedFractDigits >  0
         &&  unusedFractDigits <= 18 )
    {

        uint_fast64_t rest=      fractPart % pow10_0to19[ unusedFractDigits ];
                      fractPart= fractPart / pow10_0to19[ unusedFractDigits ];
        if ( rest > pow10_0to19[ unusedFractDigits ] / 2 )
        {
            fractPart++;
            int  overflowDigit= 0;
            bool overflow=      false;
            while (     overflowDigit <= fractionalDigits
                    && (overflow|= fractPart == pow10_0to19[ overflowDigit ]) == false
                    &&  fractPart > pow10_0to19[ overflowDigit ]
                   )
                overflowDigit++;

            if ( overflow )
            {
                if ( overflowDigit == fractionalDigits )
                {
                    fractPart= 0;
                    intPart++;
                }
                else
                {
                    ALIB_ASSERT( firstNonZero > 1 );
                    firstNonZero--;
                }
            }
        }
    }

    // write int part
    if ( intPart != 0L || minIntegralDigits != 0 )
        idx= IntegerToString( intPart, buffer, idx, minIntegralDigits );

    // write dot
    buffer[idx++]=  DecimalPointCharacter;


    // write fract part
    if (fractionalDigits != 0)
    {
        int fractZeros= firstNonZero - 1;
        if ( fractionalDigits > 0 && fractZeros > fractionalDigits )
            fractZeros= fractionalDigits;

        for ( int i= 0 ; i < fractZeros ; i++ )
            buffer[idx++]= '0';

        int  qtyDigits=        fractionalDigits - fractZeros;
        int  actDigit=         MaxFloatSignificantDigits + 1;
        int  cntOmittedZeros=  0;
        int  cntDigits=        0;
        bool printStarted=     false;
        while (    fractPart > 0
                && ( qtyDigits< 0 || cntDigits < qtyDigits )
              )
        {
            actDigit--;

            // get next d
            unsigned int digitValue=   (unsigned int)  ( fractPart / pow10_0to19[actDigit] );

            ALIB_ASSERT( digitValue <= 9 );

            // don't write, yet?
            if ( (printStarted|= (digitValue != 0)) == false )
                continue;
            cntDigits++;

            // write digtit unless its a '0'
            if ( digitValue == 0 )
                cntOmittedZeros++;
            else
            {
                for ( int i= 0; i< cntOmittedZeros ; i++ )
                    buffer[idx++]= '0';
                cntOmittedZeros= 0;
                buffer[idx++]= (char) ( 48 + digitValue ); // 48= '0'
            }

            // next
            fractPart=    fractPart % pow10_0to19[actDigit];
        }

        // assure that if -1 for fractDigits if given,at least 1 digit is printed
        if (fractionalDigits < 0 )
            qtyDigits= 1;

        // write omitted zeros
        if ( cntDigits < qtyDigits  )
        {
            for ( int i= 0; i< cntOmittedZeros ; i++ )
                buffer[idx++]= '0';
            cntDigits+= cntOmittedZeros;

            // write missing digits
            for ( int i= cntDigits; i< qtyDigits; i++ )
                buffer[idx++]= '0';
        }
    }

    // write eNN
    if ( scientific )
    {
        int p= 0;
        while( DecimalExponentSeparator[p] != '\0' )
            buffer[idx++]= DecimalExponentSeparator[p++];

        if ( exp10 < 0 )
            buffer[idx++]= '-';
        else if ( WriteExponentPlusSign )
            buffer[idx++]= '+';

        idx= IntegerToString( exp10 >= 0 ? exp10 : -exp10, buffer, idx, 2 );
    }

    return idx;
}

double NumberFormat::StringToFloat( const AS& src, int& startIdx )
{
    // checks
    if( startIdx < 0 || startIdx >= src.Length() )
        return 0.0;

    // get pointers
    const char* buf=    src.Buffer() + startIdx;
    const char* bufEnd= src.Buffer() + src.Length();

    // +/- sign
    bool negative= false;
         if ( *buf == '+' )     buf++;
    else if ( *buf == '-' )  {  buf++;   negative= true;  }

    if ( buf >= bufEnd )
        return 0.0;

    double retval= 0.0;

    // read number before dot?
    char c= *buf;
    if ( c != DecimalPointCharacter && DecimalPointCharacters.IndexOf( c ) < 0 )
    {
        if (  c < '0' || c > '9' )
            return 0.0;

        {
            int intIdx= 0;
            retval= (double) StringToInteger( AS(buf, (int) (bufEnd - buf) ), intIdx );
            buf+= intIdx;
        }

        // no dot following?
        if (     buf >= bufEnd
             ||(      DecimalPointCharacter != *buf
                  &&  DecimalPointCharacters.IndexOf( *buf ) < 0 )
           )
        {
            startIdx= (int) (buf - src.Buffer());
            return negative ? -retval : retval;
        }
    }

    // consume dot
    buf++;

    // read number after dot
    if (      buf <  bufEnd
         &&  *buf >= '0'  &&  *buf <= '9' )
    {
        int intIdx= 0;
        double intValue= (double) StringToInteger( AS(buf, (int)( bufEnd - buf ) ), intIdx );
        buf+= intIdx;
        retval+= ( intValue / pow( 10, intIdx ) );
    }

    // read eNNN
    if ( buf <  bufEnd )
    {
        bool eSepFound=  false;
        int  sepLen= DecimalExponentSeparator.Length();
        if ( buf + sepLen < bufEnd )
        {
            int pos= 0;
            while (     pos < sepLen
                    &&  DecimalExponentSeparator.CharAt<false>(pos) == *(buf + pos) )
                pos++;
            if ( (eSepFound= ( pos == sepLen ) ) == true )
                buf += pos;
        }
        eSepFound |= *buf == 'e' || *buf == 'E';

        if (eSepFound)
        {
            int intIdx= 0;
            int exp= (int) StringToInteger( AS(buf, (int)( bufEnd - buf ) ), intIdx );
            buf+= intIdx;
            retval*= pow( 10, exp );
        }
    }

    // adjust given idx
    startIdx= (int)( buf - src.Buffer() );

    // that's it
    return negative ? -retval : retval;

}



}}}// namespace aworx::lib::strings
