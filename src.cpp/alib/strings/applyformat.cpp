// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
#include "alib/stdafx_alib.h"

#include "alib/alib.hpp"

#if !defined (HPP_ALIB_STRINGS_NUMBERFORMAT)
    #include "alib/strings/numberformat.hpp"
#endif



using namespace std;

namespace aworx {
namespace           lib {
namespace                   strings {



// #################################################################################################
// Tab()
// #################################################################################################

template<>  int ApplyTo( AString& target, const Format::Tab& tab)
{
    int reference= tab.reference;
    if (reference < 0 )
    {
        // search backwards
        reference= target.LastIndexOfAny<false>( NewLine, Inclusion::Include, target.Length() -1 );
        if ( reference < 0 )
            reference= 0;
        else
        {
            // if new line has more than one character (windows) we have to now search the first
            // character that is not in newline
            reference= target.IndexOfAny<false>( NewLine, Inclusion::Exclude, reference );
        }
    }
    int length=   target.Length();
    int qtyChars= tab.minPad > 0 ? tab.minPad : 0;

    if ( tab.tabSize > 1 )
        qtyChars+= (tab.tabSize - ( (length + qtyChars - reference) % tab.tabSize ) ) % tab.tabSize;

    if ( qtyChars <= 0 )
        return 0;

    target.InsertChars( tab.tabChar, qtyChars );
    return qtyChars;
}


// #################################################################################################
// Field()
// #################################################################################################
template<>  int ApplyTo( AString& target, const Format::Field& field)
{
    int width=    field.width;
    int padSize=  field.width - field.contents.Length();

    // check pad field.width
    if (padSize <= 0 || field.alignment == Alignment::Left )
    {
                                target._           <false>( field.contents );
        if (padSize > 0 )       target.InsertChars <false>( field.padChar, padSize );
        return width;
    }

    // align Right
    if ( field.alignment == Alignment::Right )
    {
        if( padSize > 0 )
            target.InsertChars <false>( field.padChar, padSize );
        target.Apply<false>( field.contents );
        return width;
    }

    // align Center
    int leftPadding= padSize / 2;
    if( leftPadding > 0 )
        target.InsertChars<false> ( field.padChar, leftPadding  );
    target.Apply<false> ( field.contents );
    if( padSize > leftPadding ) target.InsertChars <false> ( field.padChar, padSize - leftPadding );

    return width;
}

// #################################################################################################
// Integers
// #################################################################################################
template<>  int ApplyTo( AString& target,  const Format::Int32& fmt )
{
    int minDigits= fmt.minDigits;
    if ( minDigits > 20 )    minDigits= 20;
    target.EnsureRemainingCapacity( (minDigits > 10 ? minDigits : 10 ) + 1 );

    bool isNegative= (fmt.value < 0);
    int length=      target.Length();
    int oldLength=   length;
    if (isNegative)
        (target.VBuffer())[length++]= '-';

    length= NumberFormat::Global.IntegerToString(   isNegative  ? -((int_fast64_t) fmt.value)
                                                                :   (int_fast64_t) fmt.value,
                                                    target.VBuffer(), length,
                                                    minDigits  );

    target.SetLength<false>( length );

    return length-oldLength;
}

template<>  int ApplyTo( AString& target,  const Format::UInt32& fmt )
{
    int minDigits= fmt.minDigits;
    if ( minDigits > 20 )    minDigits= 20;
    target.EnsureRemainingCapacity( minDigits > 10 ? minDigits : 10  );

    int length=      target.Length();
    int oldLength=   length;
    length= NumberFormat::Global.IntegerToString( fmt.value, target.VBuffer(), length,  minDigits );

    target.SetLength<false>( length );

    return length-oldLength;
}

template<>  int ApplyTo( AString& target,  const Format::Int64& fmt )
{
    int minDigits= fmt.minDigits;
    if ( minDigits > 20 )    minDigits= 20;
    target.EnsureRemainingCapacity( 21 );

    bool isNegative= (fmt.value < 0);
    int length=      target.Length();
    int oldLength=   length;
    if (isNegative)
        (target.VBuffer())[length++]= '-';
    length= NumberFormat::Global.IntegerToString(  isNegative ? -fmt.value : fmt.value,
                                                   target.VBuffer(), length,
                                                   minDigits );

    target.SetLength<false>( length );
    return length-oldLength;
}

template<>  int ApplyTo( AString& target,  const Format::UInt64& fmt )
{
    int minDigits= fmt.minDigits;
    if ( minDigits > 20 )    minDigits= 20;
    target.EnsureRemainingCapacity( 20 );

    int length=      target.Length();
    int oldLength=   length;
    length= NumberFormat::Global.IntegerToString( fmt.value, target.VBuffer(), length,  minDigits );
    target.SetLength<false>( length );

    return length-oldLength;
}

// #################################################################################################
// Floats
// #################################################################################################
template<>  int ApplyTo( AString& target, const Format::Double& fmt )
{
    NumberFormat* numberFormat= fmt.nf;
    if ( numberFormat == nullptr )
        numberFormat= &NumberFormat::Global;
    target.EnsureRemainingCapacity( 32 ); // 2x15 + '.' + '-'

    int length=      target.Length();
    int oldLength=   length;
    length= numberFormat->FloatToString( fmt.value, target.VBuffer(), length );

    target.SetLength<false>( length );

    // return me for concatenated operations
    return length-oldLength;
}


}}}// namespace aworx::lib::strings
