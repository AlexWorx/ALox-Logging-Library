// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
#include "alib/alib.hpp"

#if !defined (HPP_ALIB_STRINGS_NUMBERFORMAT)
    #include "alib/strings/numberformat.hpp"
#endif



using namespace std;

namespace aworx { namespace lib { namespace strings
{

// We are faking all template specializations of namespace strings for doxygen into namespace
// strings::applyto to keep the documentation of namespace string clean!
#if defined(DOX_PARSER)

/**
 * \attention
 *   This is a non-existing namespace! It is exclusively defined for the
 *   [documentation parser](http://www.stack.nl/~dimitri/doxygen).
 *
 * \attention
 *   In this <b>"documentation namespace"</b>, you will find specializations of templated namespace
 *   functions and types of namespace
 *   \ref aworx::lib::strings. This is of-course wrong in respect to the C++ language
 *   definition, which requires such specializations to be placed in the original namespace.<br>
 *   It was decided to 'trick' the documentation parser to
 *   show these specialization in this namespace, to keep namespace \b %aworx::lib::strings
 *   clean and to have all specializations in one place.<br>
 *   In other words: All types and functions described in this namespace are residing in namespace
 *   #aworx::lib::strings.
 */
namespace applyto {
#endif

// #################################################################################################
// Tab()
// #################################################################################################

integer T_Apply<Format::Tab>::Apply( AString& target, const Format::Tab& tab)
{
    integer reference= tab.reference;
    if (reference < 0 )
    {
        // search backwards
        reference= target.LastIndexOfAny( NewLine, Inclusion::Include, target.Length() -1 );
        if ( reference < 0 )
            reference= 0;
        else
        {
            // if new line has more than one character (windows) we have to now search the first
            // character that is not in newline
            reference= target.IndexOfAny<false>( NewLine, Inclusion::Exclude, reference );
            if (reference < 0 )
                reference= target.Length();

        }
    }
    integer length=   target.Length();
    integer qtyChars= tab.minPad > 0 ? tab.minPad : 0;

    if ( tab.tabSize > 1 )
        qtyChars+= (tab.tabSize - ( (length + qtyChars - reference) % tab.tabSize ) ) % tab.tabSize;

    if ( qtyChars <= 0 )
        return 0;

    target.InsertChars<false>( tab.tabChar, qtyChars );
    return qtyChars;
}


// #################################################################################################
// Field()
// #################################################################################################
integer T_Apply<Format::Field>::Apply( AString& target, const Format::Field& field)
{
    integer width=    field.theWidth;
    integer padSize=  field.theWidth
                       - CString::LengthWhenConvertedToWChar( field.theContent.Buffer(),
                                                              field.theContent.Length() );

    // check pad field.width
    if (padSize <= 0 || field.theAlignment == Alignment::Left )
    {
                                target._          <false>( field.theContent );
        if (padSize > 0 )       target.InsertChars<false>( field.padChar, padSize );
        return width;
    }

    // align Right
    if ( field.theAlignment == Alignment::Right )
    {
        if( padSize > 0 )
            target.InsertChars<false>( field.padChar, padSize );
        target.Apply<false>( field.theContent );
        return width;
    }

    // align Center
    integer leftPadding= padSize / 2;
    if( leftPadding > 0 )
        target.InsertChars<false> ( field.padChar, leftPadding  );
    target.Apply<false> ( field.theContent );
    if( padSize > leftPadding ) target.InsertChars<false> ( field.padChar, padSize - leftPadding );

    return width;
}

// #################################################################################################
// Escape()
// #################################################################################################
integer T_Apply<Format::Escape>::Apply( AString& target, const Format::Escape& escape)
{
    if( target.AdjustRegion( const_cast<Format::Escape&>(escape).startIdx,
                             const_cast<Format::Escape&>(escape).length   ) )
        return 0;

    integer regionEnd= escape.startIdx + escape.length;

    //
    // To escape sequences
    //
    if (escape.pSwitch == Switch::On)
    {
        for( integer idx= escape.startIdx; idx < regionEnd ; ++idx )
        {
            char c= target.CharAt(idx);

            char resultChar= '\0';
            switch(c)
            {
                case '\\' : resultChar= '\\'; break;
                case '\r' : resultChar= 'r' ; break;
                case '\n' : resultChar= 'n' ; break;
                case '\t' : resultChar= 't' ; break;
                case '\a' : resultChar= 'a' ; break;
                case '\b' : resultChar= 'b' ; break;
                case '\v' : resultChar= 'v' ; break;
                case '\f' : resultChar= 'f' ; break;
             // case '\e' : resultChar= 'e' ; break; Not C++ standard
                case '"'  : resultChar= '"' ; break;

                default   :                   break;
            }

            if( resultChar != '\0')
            {
                target.InsertChars<false>(' ', 1, idx);
                target[idx++]= '\\';
                target[idx]= resultChar;
                regionEnd++;
            }
            else
            {
                unsigned char uc= static_cast<unsigned char>(c);
                if (uc < 32  )
                {
                    target.InsertChars<false>(' ', 3, idx);
                    target[idx++]= '\\';
                    target[idx++]= '0';
                    char oct= uc >> 3;
                    target[idx++]= '0' + oct;
                         oct=  uc & 7;
                    target[idx]  = '0' + oct;

                    regionEnd+=3;
                }
                else
                if ( uc >126 )
                {
                    target.InsertChars<false>(' ', 3, idx);
                    target[idx++]= '\\';
                    target[idx++]= 'x';
                    char nibble= uc >> 4;
                    target[idx++]= (nibble <10 ? '0' : 'A' -10) + nibble;
                         nibble=  uc & 15;
                    target[idx]  = (nibble <10 ? '0' : 'A' -10) + nibble;

                    regionEnd+=3;
                }
            }
        }
    }
    //
    // Un-escape escape sequences
    //

    else
    {
        regionEnd--; // we can go 1 over it!
        for( integer idx= escape.startIdx; idx < regionEnd ; ++idx )
        {
            char c= target.CharAt(idx);
            if( c != '\\' )
                continue;
            c= target.CharAt(idx + 1);

            char resultChar= '\0';
            switch(c)
            {
                case '\\' : resultChar= '\\'; break;
                case 'r'  : resultChar= '\r' ; break;
                case 'n'  : resultChar= '\n' ; break;
                case 't'  : resultChar= '\t' ; break;
                case 'a'  : resultChar= '\a' ; break;
                case 'b'  : resultChar= '\b' ; break;
                case 'v'  : resultChar= '\v' ; break;
                case 'f'  : resultChar= '\f' ; break;
             // case 'e'  : resultChar= '\e' ; break; Not C++ standard
                case '"'  : resultChar= '"' ; break;

                default   :                   break;
            }

            if( resultChar != '\0')
            {
                target.Delete( idx, 1);
                target[idx]= resultChar;
                regionEnd--;
            }
            else
            {
                if (c == '0' && idx + 2 < regionEnd )
                {
                    target[idx]= static_cast<char> (   (target[idx + 2] - '0' ) *8
                                                     + (target[idx + 3] - '0' )
                                                   );
                    target.Delete( idx+1, 3);
                    regionEnd-=3;
                }
                else
                if (c == 'x' && idx + 2 < regionEnd )
                {
                    c= target[idx+2];
                         if( c>='0' && c<= '9') c-= '0';
                    else if( c>='a' && c<= 'f') c-= 'a' - 10;
                    else if( c>='A' && c<= 'F') c-= 'A' - 10;
                    unsigned char nc= static_cast<unsigned char>( c );
                    c= target[idx + 3];
                         if( c>='0' && c<= '9') c-= '0';
                    else if( c>='a' && c<= 'f') c-= 'a' - 10;
                    else if( c>='A' && c<= 'F') c-= 'A' - 10;

                    target[idx]= static_cast<char> ( (nc << 4) + c );
                    target.Delete( idx+1, 3);
                    regionEnd-=3;
                }
            }
        }
    }


    return 1;
}

// #################################################################################################
// Integers
// #################################################################################################
integer T_Apply<Format>::Apply( AString& target,  const Format& fmt )
{
    NumberFormat* nf= fmt.nf;
    if( nf == nullptr )
        nf= &NumberFormat::Computational;

    target.EnsureRemainingCapacity( fmt.valueType== 3 ?  48  //float: 2x15 + '.' + ',' + sign + fear
                                                      :  28  //int:   20 digits, grouping symbol, sign and what have you
                                  );

    integer length=      target.Length();
    integer oldLength=   length;


    length=  fmt.valueType == 1 ?  nf->WriteDecSigned  ( fmt.v.sInt, target.VBuffer(), length, fmt.theWidth  ) :
             fmt.valueType == 2 ?  nf->WriteDecUnsigned( fmt.v.uInt, target.VBuffer(), length, fmt.theWidth  ) :
                                   nf->WriteFloat      ( fmt.v.fp,   target.VBuffer(), length, fmt.theWidth  );

    target.SetLength<false>( length );

    return length-oldLength;
}

integer T_Apply<Format::Bin>::Apply( AString& target,  const Format::Bin& fmt )
{
    NumberFormat* nf= fmt.nf;
    if( nf == nullptr )
        nf= &NumberFormat::Computational;

    target.EnsureRemainingCapacity( 80 );

    integer length=      target.Length();
    integer oldLength=   length;

    length= nf->WriteBin( fmt.theValue, target.VBuffer(), length,  fmt.theWidth );

    target.SetLength<false>( length );

    return length-oldLength;
}

integer T_Apply<Format::Hex>::Apply( AString& target,  const Format::Hex& fmt )
{
    NumberFormat* nf= fmt.nf;
    if( nf == nullptr )
        nf= &NumberFormat::Computational;

    target.EnsureRemainingCapacity( 25 );

    integer length=      target.Length();
    integer oldLength=   length;

    length= nf->WriteHex( fmt.theValue, target.VBuffer(), length,  fmt.theWidth );

    target.SetLength<false>( length );

    return length-oldLength;
}

integer T_Apply<Format::Oct>::Apply( AString& target,  const Format::Oct& fmt )
{
    NumberFormat* nf= fmt.nf;
    if( nf == nullptr )
        nf= &NumberFormat::Computational;

    target.EnsureRemainingCapacity( 30 );

    integer length=      target.Length();
    integer oldLength=   length;

    length= nf->WriteOct( fmt.theValue, target.VBuffer(), length,  fmt.theWidth );

    target.SetLength<false>( length );

    return length-oldLength;
}

// We are faking all template specializations of namespace strings for doxygen into namespace
// strings::applyto to keep the documentation of namespace string clean!
#if defined(DOX_PARSER)
}
#endif


}}}// namespace aworx::lib::strings
