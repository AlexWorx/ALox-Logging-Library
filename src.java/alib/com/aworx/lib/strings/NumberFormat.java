// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################

package com.aworx.lib.strings;

import java.text.DecimalFormatSymbols;

import com.aworx.lib.ALIB;


/** ********************************************************************************************
 * By providing this class, the AWorx library brings it's own implementation for converting integer
 * and double values to character string representations and vice versa.
 * This was implemented for the following reasons:
 * - To avoid problems with locale specific formats, especially the decimal separator
 *   character, which sometimes is ' . ' and sometimes is ' , '. This definition generally is
 *   a process wide setting, leading to race conditions in multi-threaded
 *   applications, which are a common source of faults and addressing them introduces
 *   another performance overhead.
 * - To be able to parse different formats without switching the locale (and even with being
 *   tolerant about format that is read)
 * - The possibility for the calling code to receive information about the location
 *   (the end) of a parsed floating point value, to continue processing a string
 *   behind this location.
 * - Cross language/platform source compatibility (the essential motivation for having the
 *   AWorx library)
 * - Performance optimization (C# and Java versions avoid unnecessary temporary object
 *   allocations)
 *
 * As an example, when writing float data into a configuration file, class
 * \ref com::aworx::lib::config::ConfigurationPlugIn "ConfigurationPlugIn" ignores the systems locale
 * setting and writes all data using '.' as decimal separator. When reading values, both ' . '
 * and ' , ' are accepted. While loosing the possibility to read configuration data that
 * uses a "thousand separator" which is generally the opposite of the decimal separator
 * (opposite here means it is a ',' when decimal separator is a '.' and vice versa), what
 * is gained is that floats are read without throwing exceptions regardless of the locale
 * that was set when they were written. Therefore configuration files are consistent
 * and readable across all software installations.
 *
 * Instances created, have default values set, independent from the current locale setting
 * of the system. To initialize this classes fields to reflect the current locale, invoke
 * #setFromLocale().
 *
 * \note The method interface of this class is quite rudimentary. Therefore, it is advisable to
 *       use more user friendly classes as
 *       \ref com::aworx::lib::strings::AString         "AString" or
 *       \ref com::aworx::lib::strings::Substring "Substring",
 *       which provide methods that accept a configured instance of this class as parameter and do
 *       the conversion internally.
 **********************************************************************************************/
public class NumberFormat
{
    /** ****************************************************************************************
     *  Constant long values for 10 ^(0...18) needed by conversion methods.
     ******************************************************************************************/
    protected static long pow10_0to18[]=
    {
        1L,                          // 10^ 0
        10L,                         // 10^ 1
        100L,                        // 10^ 2
        1000L,                       // 10^ 3
        10000L,                      // 10^ 4
        100000L,                     // 10^ 5
        1000000L,                    // 10^ 6
        10000000L,                   // 10^ 7
        100000000L,                  // 10^ 8
        1000000000L,                 // 10^ 9
        10000000000L,                // 10^10
        100000000000L,               // 10^11
        1000000000000L,              // 10^12
        10000000000000L,             // 10^13
        100000000000000L,            // 10^14
        1000000000000000L,           // 10^15
        10000000000000000L,          // 10^16
        100000000000000000L,         // 10^17
        1000000000000000000L,        // 10^18
    };

    // #########################################################################################
    //  Fields
    // #########################################################################################

    /**
     * The default static number format object, used by various methods. It therefore acts as the
     * global default settings of the currently running process.<br>
     * Method
     * \ref com::aworx::lib::ALIB::init "ALIB.init" invokes #setFromLocale() on this object.
     */

    public static  NumberFormat      global                                     =new NumberFormat();

    /**
     *  Defines the decimal point character when converting a floating point number to a string
     *  representation with method #floatToString. Also, method #stringToFloat accepts the
     *  character provided in this field aside to those provided in #decimalPointCharacters.<br>
     *  The field defaults to '.'. By invoking #setFromLocale(), the current locale's setting is
     *  determined.
     */
    public  char                      decimalPointCharacter                                 = '.';

    /**
     *  Defines all characters that will be accepted by #stringToFloat as the separator
     *  of integral and fractional part of the value read.<br>
     *  Defaults to ".,".<br>
     *  The advantage of allowing both common symbols is that standard numbers are accepted
     *  independent of the current locale setting. However, the thousand separator commonly
     *  is the opposite of the 'dot' standard. This class does not support parsing or writing
     *  values with thousand separators anyhow. Therefore, accepting both here is no limitation.<br>
     *  Note: In addition to the characters provided in this field, method stringToFloat accepts
     *  the single character set in #decimalPointCharacter as well.
     */
    public  char[]                    decimalPointCharacters                          = {'.',',' };

    /**
     *  Defines the decimal exponent symbol of string representations of floating point numbers
     *  when written or parsed in scientific notation by methods #stringToFloat and #floatToString.<br>
     *  Method #stringToFloat accepts characters 'e' and 'E' in addition to the string
     *  set in this field.<br>
     *  Defaults to 'E'.
     */
    public  char[]                    decimalExponentSeparator                        ={'E'};

    /**
     *  Determines if positive exponent values are prepended with an explicit '+' character when
     *  written using #floatToString.<br>
     *  Independently from this setting, method #stringToFloat always accepts such optional
     *  plus sign.<br>
     *  Defaults to false, as some systems will not accept a plus sign on the exponent value.
     */
    public  boolean                   writeExponentPlusSign                                = false;

    /**
     * Defines the minimum digits written for the integral part when converting a floating point
     * value into a string.<br>
     * If the integral part of the number provided has less digits
     * then leading '0' digits are added.<br>
     * The maximum value allowed is 15.<br>
     * A value of 0 leads to omitting the '0' before the
     * decimal separator in the case the value is below 1.0 and higher than -1.0 <br>
     * The default value is -1, which writes a minimum of 1 digit.
     * Scientific notation gets disabled when either this field or field #fractionalDigits is set to
     * any positive value, unless #forceScientificFormat evaluates to true. In the latter case,
     * both fields can also be used to set a fixed number of digits for the integer and the
     * fractional part in scientific format.
     */
    public int                        minIntegralDigits                                       = -1;

    /**
     * Defines the number of digits written for the fractional part when converting a floating point
     * value into a string.<br>
     * If the fractional part of the number provided has less digits then trailing '0'
     * digits are added.<br>
     * If the fractional part of the number provided has more digits then the fractional part is
     * rounded accordingly.<br>
     * The maximum value allowed is 15.<br>
     * The default value is -1, which writes as many digits as available in the provided float
     * variable, with a minimum of 1 digit.
     * Scientific notation gets disabled when either this field or field #minIntegralDigits is set
     * to any positive value, unless #forceScientificFormat evaluates to true. In the latter case,
     * both fields can also be used to set a fixed number of digits for the integer and the
     * fractional part in scientific format.
     */
    public int                        fractionalDigits                                        = -1;

    /**
     *  If false, the default, method #floatToString writes scientific format only if both fields,
     *  #minIntegralDigits and #fractionalDigits are evaluating to -1 and only for numbers smaller
     *  than 10^-4 or larger than 10^+6.<br>
     *  If true, scientific format is always used.<br>
     */
    public  boolean                   forceScientificFormat                                = false;


    // #############################################################################################
    //  Interface
    // #############################################################################################

    /** ****************************************************************************************
     * Sets the the the fields #decimalPointCharacter and #decimalExponentSeparator
     * to reflect the current system locale's setting.
     ******************************************************************************************/
    public void setFromLocale()
    {
        DecimalFormatSymbols dfs= DecimalFormatSymbols.getInstance();
        decimalPointCharacter=      dfs.getDecimalSeparator();
        decimalExponentSeparator=   dfs.getExponentSeparator().toCharArray();
    }

    // #############################################################################################
    //  Integer conversion
    // #############################################################################################

    /** ****************************************************************************************
     * Reads a (long) integer from the given character array starting at the given position.
     * The output parameter is set to point to first character that is not a number.
     * If no number is found at the given index, zero is returned and the output parameter is
     * set to the original start index.
     *
     * Leading whitespace characters are <em>not</em> ignored (parsing will fail).
     *
     * @param buffer  The character array to read the value from.
     * @param idx     The start index from where the integer value is tried to be parsed.
     * @param maxIdx  The maximum index to look at. Must be smaller than the buffer length.
     * @param newIdx   Optional output variable (in array position 0) that will point to the
     *                 first character after the integer number that was parsed.
     *                 If parsing fails, it will be set to the value of parameter idx.
     *                 Therefore, this parameter can be used to check if a value was found.
     *
     * @return  The parsed value. In addition, the output parameter newIdx is set to point
     *          to the first character behind any found integer number.
     ******************************************************************************************/
    public long stringToInteger( char[] buffer, int idx, int maxIdx, int[] newIdx )
    {
        // check
        if( idx > maxIdx )
            return 0;

        if (newIdx != null )
            newIdx[0]= idx;

        // read sign
        boolean negative= false;
        if      ( buffer[idx] == '-' )
        {
            negative= true;
            idx++;
        }
        else if ( buffer[idx] == '+' )
            idx++;

        long  retVal=    0;
        while ( idx <= maxIdx )
        {
            char  c= buffer[ idx ];
            if ( c < '0' || c > '9' )
                break;

            retVal= ( retVal * 10 ) + ( (int) ( c - '0' ) );
            idx++;
        }

        if (newIdx != null )
            newIdx[0]= idx;

        return negative? -retVal : retVal;
    }

    /** ****************************************************************************************
     *  Converts the given long value to a string representation.<br>
     *  Negative numbers have to be converted to positive values when invoking this method.
     *  The maximum number of digits written are 20. The given buffer has to be large
     *  enough to receive the characters. The method does not check any overflow within the
     *  given character buffer.
     *
     *  \note This method is used internally by various AString conversion methods. It is
     *        advisable to use AString methods to convert integer values.
     *
     * @param value        The integer value to convert. In other versions of the AWorx library
     *                     this is an unsigned value. Java lacks that type. Nevertheless, only
     *                     positive numbers are accepted
     * @param buffer       The character array to write the value to. Depending on the value
     *                     given, a maximum of 20 characters need to be allocated prior to
     *                     invoking this method.
     * @param idx          The index within the character array to write the value to.
     * @param minDigits    The minimum number of digits to append.
     *                     If given value has less digits, '0' characters are prepended.
     *                     The given value is cut to the range 1..20 (max digits of an
     *                     unsigned 64 bit integer).
     * @param sizeHint     The maximum number of digits found in the value. This is a hint
     *                     for optimizing the loop. If -1 is provided, the number is detected.
     *                     If a number is provided that is lower than the actual 'log10(value)',
     *                     the method produces unpredictable results.
     *
     * @return  The index of the new new end of the buffer.
     ******************************************************************************************/
    public int integerToString( long value, char[] buffer, int idx, int minDigits, int sizeHint )
    {
        ALIB.ASSERT_ERROR( value >= 0, "Only positive values are allowed" );

        // adjust minDigits to 1..20 and maxDigits to 1..minDigits
        if ( minDigits < 1  )           minDigits= 1;
        if ( minDigits > 20 )           minDigits= 20;
        if ( sizeHint  < minDigits )    sizeHint= minDigits;
        if ( sizeHint  > 20 )           sizeHint= 20;

        int      actDigit=       sizeHint;
        boolean  printStarted=   false;
        while ( --actDigit >= 0 )
        {
            // rest is zeros?
            if ( value == 0 )
            {
                while ( actDigit >= 0)
                {
                    if ( !  (printStarted|= actDigit-- < minDigits ) )
                        continue;
                    buffer[ idx++ ]= '0';
                }
                return idx;
            }

            // get next d
            long actBase=        pow10_0to18[ actDigit ];
            int   digitValue=     (int) (value / actBase);
            ALIB.ASSERT( digitValue <= 9 );

            // did we hit i for the first time
            if ( !  (printStarted|= (digitValue != 0) || actDigit < minDigits) )
                continue;

            // print the digit
            buffer[ idx++ ]= (char) ( 48 + digitValue ); // 48= '0'

            // next
            value=    value % actBase;
        }

        // return me for concatenated operations
        return idx;
    }

    // #############################################################################################
    //  Float conversion
    // #############################################################################################

    /** ****************************************************************************************
     *  Appends the given double value as string representation.
     *
     *  This method supports to write a variable or fixed number of digits for the integral
     *  and the fractional part of the provided value, or in <em>scientific notation</em>.
     *  In <em>scientific notation</em>, the value is multiplied with a power of 10 so that
     *  the integral part of the number falls into the range of 0 and 9. Then, the the negative
     *  value of the exponent of this multiplicand is appended, separated by the string defined in
     *  #decimalExponentSeparator.
     *
     *  The output format is dependent on various settings provided in the fields of this class.
     *
     * @param value     The double value to append.
     * @param buffer    The character array to write the value into.
     *                  Depending on the value given and the format settings, a maximum of
     *                  32 characters need to be allocated prior to invoking this method.
     * @param idx       The index within the buffer to start writing to.
     *
     * @return   The index pointing behind the last character written.
     ******************************************************************************************/
    public  int floatToString( double value, char[] buffer, int  idx )
    {
        // for debugging:
        // char* origBuffer= buffer;
        // for( int i= 0; i<24; i++ )
        //   origBuffer[i]= '\0';

        final int maxFloatSignificantDigits= 16;


        // negative? -> turn positive
        if ( value < 0.0 )
        {
            buffer[idx++]= '-';
            value= -value;
        }

        // calc dot position
        int  exp10=      value != 0.0   ? (int) Math.floor((Math.log10( value ) ))
                                        : 0;

        // decide if we are using scientific format (with e) or not
        boolean scientific=  (     forceScientificFormat
                               || (     minIntegralDigits < 0
                                    &&  fractionalDigits  < 0
                                    &&  ( exp10 > 6 || exp10 <= -5 )
                                  )    );

        int minIntegralDigits= Math.min( this.minIntegralDigits, 15 );
        int fractionalDigits=  Math.min( this.fractionalDigits,  15 );



        // result variables used for output
        long intPart;
        long fractPart;
        int unusedFractDigits;
        int firstNonZero;
        int intPartSize;

        // scientific output
        if ( scientific )
        {
            int dotPos=  maxFloatSignificantDigits - exp10;
            intPart=     (long) ( value * Math.pow( 10, dotPos ) );
            fractPart=   intPart %  pow10_0to18[ maxFloatSignificantDigits ];
            intPart=     intPart /  pow10_0to18[ maxFloatSignificantDigits ];
            intPartSize= 1;

            // determine first non zero fract number
            firstNonZero= 0;
            if ( fractPart > 0 )
            {
                ALIB.ASSERT( maxFloatSignificantDigits - firstNonZero < 20);
                while ( fractPart < pow10_0to18[ maxFloatSignificantDigits - firstNonZero - 1 ] )
                    firstNonZero++;
                ALIB.ASSERT( maxFloatSignificantDigits - firstNonZero > 0);
            }
            firstNonZero++;

            unusedFractDigits= fractionalDigits >= 0 ?  maxFloatSignificantDigits - fractionalDigits
                                                     :  1;
        }

         // normal output, number > 0
         else if (exp10 >= 0 )
         {
            intPartSize= maxFloatSignificantDigits - exp10;
            ALIB.ASSERT( intPartSize > 0  && intPartSize <= maxFloatSignificantDigits );

            intPart=     (long) ( value * Math.pow( 10, intPartSize ) );
            fractPart=   intPart %  pow10_0to18[ intPartSize ];
            intPart=     intPart /  pow10_0to18[ intPartSize ];

            // determine first non zero fract number
            firstNonZero= 0;
            if ( fractPart > 0 )
            {
                ALIB.ASSERT( intPartSize - firstNonZero < 20 );
                while ( fractPart < pow10_0to18[ intPartSize - firstNonZero - 1 ] )
                    firstNonZero++;
                ALIB.ASSERT( intPartSize - firstNonZero > 0 );
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
            fractPart=    (long) ( value * Math.pow( 10, maxFloatSignificantDigits + firstNonZero) );
            unusedFractDigits= fractionalDigits >= 0 ?  maxFloatSignificantDigits - ( fractionalDigits - firstNonZero )
                                                     :  1;
         }

        // cut fract digits and round it up
        if (     (fractionalDigits < 0 || fractionalDigits  >= firstNonZero - 1 )
             &&  unusedFractDigits >  0
             &&  unusedFractDigits <= 18 )
        {

            long rest=      fractPart % pow10_0to18[ unusedFractDigits ];
                  fractPart= fractPart / pow10_0to18[ unusedFractDigits ];
            if ( rest > pow10_0to18[ unusedFractDigits ] / 2 )
            {
                fractPart++;
                int  overflowDigit= 0;
                boolean overflow=      false;
                while (     overflowDigit <= fractionalDigits
                        && !(overflow|= fractPart == pow10_0to18[ overflowDigit ])
                        &&  fractPart > pow10_0to18[ overflowDigit ]
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
                        ALIB.ASSERT( firstNonZero > 1 );
                        firstNonZero--;
                    }
                }
            }
        }

        // write int part
        if ( intPart != 0L || minIntegralDigits != 0 )
            idx= integerToString( intPart, buffer, idx, minIntegralDigits, intPartSize );

        // write dot
        buffer[idx++]=  decimalPointCharacter;


        // write fract part
        if (fractionalDigits != 0)
        {
            int fractZeros= firstNonZero - 1;
            if ( fractionalDigits > 0 && fractZeros > fractionalDigits )
                fractZeros= fractionalDigits;

            for ( int i= 0 ; i < fractZeros ; i++ )
                buffer[idx++]= '0';

            int     qtyDigits=        fractionalDigits - fractZeros;
            int     actDigit=         maxFloatSignificantDigits + 1;
            int     cntOmittedZeros=  0;
            int     cntDigits=        0;
            boolean printStarted=     false;
            while (    fractPart > 0
                    && ( qtyDigits< 0 || cntDigits < qtyDigits )
                  )
            {
                actDigit--;

                // get next d
                int digitValue=   (int) ( fractPart / pow10_0to18[actDigit] );

                ALIB.ASSERT( digitValue >= 0 && digitValue <= 9 );

                // don't write, yet?
                if ( !  (printStarted|= (digitValue != 0)) )
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
                fractPart=    fractPart % pow10_0to18[actDigit];
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
            for (int i= 0; i< decimalExponentSeparator.length ; i++)
                buffer[idx++]= decimalExponentSeparator[i];

            if ( exp10 < 0 )
                buffer[idx++]= '-';
            else if ( writeExponentPlusSign )
                buffer[idx++]= '+';
            idx= integerToString( (long) ( exp10 >= 0 ? exp10 : -exp10), buffer, idx, 2, 3 );
        }

        return idx;
    }

    /** ****************************************************************************************
     * Reads a floating point value from the given character array at the given position.
     * The given output parameter is set to point to first character that does not belong to
     * the number.
     * If no number is found at the given index, zero is returned and the output parameter is
     * set to the original start index.
     *
     * Leading whitespace characters are <em>not</em> ignored (parsing will fail).
     *
     * \note When parsing 'many' floating point values, it is advisable to create
     *       an int[] of size one and provide this to each invocation of this method to
     *       avoid the internal allocation.
     *
     * @param buffer   The character array to read the value from.
     * @param idx      The start index from where the float value is tried to be parsed.
     * @param maxIdx   The maximum index to look at. Must be smaller than the buffer length.
     * @param newIdx   Optional output variable (in array position 0) that will point to the
     *                 first character after the integer number that was parsed.
     *                 If parsing fails, it will be set to the value of parameter idx.
     *                 Therefore, this parameter can be used to check if a value was found.
     *
     * @return  The parsed value. In addition, on success, the output parameter newIdx is set
     *          to point to the first character behind any found float number.
     ******************************************************************************************/
    public double stringToFloat( char[] buffer, int idx, int maxIdx,  int[] newIdx )
    {
        // initialize output
        if( newIdx != null )
            newIdx[0]= idx;

        // checks
        if ( maxIdx >= buffer.length )
            maxIdx= buffer.length-1;

        if ( idx < 0 || idx > maxIdx )
            return 0.0;

        // +/- sign
        boolean negative= false;
        if      ( buffer[idx] == '+' )
            idx++;
        else if ( buffer[idx] == '-' )
        {
            idx++;
            negative= true;
        }

        if ( idx > maxIdx )
            return 0.0;

        // if given, we use the return array for temporary results of toInteger()
        int[] tempIdx= newIdx != null ? newIdx
                                      : new int[1];

        double retval= 0.0;

        // read number before dot?
        char c= buffer[idx];
        if (  c != decimalPointCharacter && CString.indexOf( c, decimalPointCharacters ) < 0 )
        {
            if ( !Character.isDigit( c ) )
                return 0.0;

            retval= stringToInteger( buffer, idx, maxIdx, tempIdx );
            idx= tempIdx[0];

            // no dot following?
            if (      idx > maxIdx
                  ||  (     buffer[idx] != decimalPointCharacter
                        &&  CString.indexOf( buffer[idx], decimalPointCharacters ) < 0 )
               )
            {
                if( newIdx != null )
                    newIdx[0]= idx;
                return negative ? -retval : retval;
            }
        }

        // consume dot
        idx++;

        // read number after dot
        if ( idx <= maxIdx && Character.isDigit( buffer[idx] ) )
        {
            int oldIdx= idx;
            double intValue= stringToInteger( buffer, idx, maxIdx, tempIdx );
            idx= tempIdx[0];
            retval+= ( intValue / Math.pow( 10, idx - oldIdx ) );
        }

        // read eNNN
        if ( idx < maxIdx + 1)
        {
            boolean eSepFound=  false;
            if ( idx < maxIdx + decimalExponentSeparator.length )
            {
                int pos= 0;
                while (     pos < decimalExponentSeparator.length
                        &&  decimalExponentSeparator[pos] == buffer[idx+pos] )
                    pos++;
                if ( eSepFound= ( pos == decimalExponentSeparator.length ) )
                    idx+= pos;
            }

            if ( !eSepFound && (buffer[idx] == 'e' || buffer[idx] == 'E') )
            {
                eSepFound= true;
                idx++;
            }
            if (eSepFound)
            {
                int exp= (int) stringToInteger( buffer, idx, maxIdx, tempIdx );
                retval*= Math.pow( 10.0, exp );
                idx= tempIdx[0];
            }
        }

        // that's it
        if( newIdx != null )
            newIdx[0]= idx;
        return negative ? -retval : retval;
    }


}  //  class NumberFormat



