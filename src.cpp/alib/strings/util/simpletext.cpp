// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
#include "alib/alib.hpp"

#if !defined (HPP_ALIB_STRINGS_SIMPLETEXT)
    #include "alib/strings/util/simpletext.hpp"
#endif


using namespace std;

namespace aworx { namespace lib { namespace strings { namespace util  {



void SimpleText::AddIndent( const String& increment )
{
    Indent._( increment );
}

void SimpleText::AddIndent( int qty, char fillChar )
{
    if ( qty > 0 )
        Indent.InsertChars( fillChar, qty );
    else
        Indent.DeleteEnd( - qty );
}


void   SimpleText::AddParagraph( const Boxes&  args )
{
    integer startIdx= Text.Length();

    Formatter.Format( Text, args );

    SimpleText::FormatParagraph( Text, startIdx, LineWidth, Justifier, Indent, IndentFirstLine );

    if ( Text.IsNotEmpty() && !Text.EndsWith( NewLine ) )
        Text << NewLine;
}

void  SimpleText::FormatParagraph( AString& text, integer startIdx, integer lineWidth, char justifier,
                                   String indent, const String& indentFirstLine  )
{
    // check
    if ( indent.IsNull() )
        indent= "";// EmptyString;

    bool isFirstLine=           indentFirstLine.IsNotNull();

    String actIndentx;
    bool   actIdentSet= false;
    bool   indentAreJustSpaces= false;

    while ( startIdx < text.Length() )
    {
        // skip lines beginning with newline characters
        int isWinNL=  text[ startIdx ] == '\r' ? 1 : 0;
        if ( text[ startIdx + isWinNL ] == '\n' )
        {
            if( !actIdentSet )
            {
                actIndentx = isFirstLine ? indentFirstLine : indent;
                indentAreJustSpaces= (actIndentx.IndexOfAny( " ", Inclusion::Exclude ) < 0 );
            }
            if ( !indentAreJustSpaces )
            {
                text.InsertAt( actIndentx, startIdx );
                startIdx+= actIndentx.Length();
            }
            startIdx+= 1 + isWinNL;
            if( isFirstLine )
            {
                isFirstLine= false;
                actIdentSet= false;
            }
            continue;
        }

        // insert indent
        if( !actIdentSet )
        {
            actIndentx = isFirstLine ? indentFirstLine : indent;
            indentAreJustSpaces= (actIndentx.IndexOfAny( " ", Inclusion::Exclude ) < 0 );
        }
        text.InsertAt( actIndentx, startIdx );

        if( isFirstLine )
        {
            isFirstLine= false;
            actIdentSet= false;
        }


        // find next end of line. Remember last space
        integer lastSpace=  0;
        bool    textEnd=    true;
        bool    exceeds=    false;
        integer idx= startIdx + actIndentx.Length() - 1;
        while (++idx < text.Length() )
        {
            char c= text[idx];
            if ( c == '\n' )
            {
                idx++;
                break;
            }
            exceeds= lineWidth > 0 && idx - startIdx >= lineWidth;

            if( c == ' ' )
            {
                if(idx - startIdx <= lineWidth )
                    lastSpace= idx;

                if( exceeds )
                {
                    textEnd= false;
                    break;
                }
            }
        }

        // cut block.
        if( exceeds )
        {
            if( lastSpace || !textEnd )
            {
                integer wrapPos= lastSpace > 0 ? lastSpace : idx;
                text.ReplaceSubstring( NewLine, wrapPos, 1 );
                idx= wrapPos + NewLine.Length();

                // block justification
                if( justifier != '\0' )
                {
                    integer qtyInserts= lineWidth - (idx - startIdx ) + 1;
                    if( qtyInserts > 0 )
                    {
                        // search first non-space after indent.
                        integer leftInsertBoundary= startIdx + actIndentx.Length();
                        while ( leftInsertBoundary < idx && text[leftInsertBoundary] == ' ' )
                            leftInsertBoundary++;

                        if( leftInsertBoundary < idx )
                        {
                            while( qtyInserts > 0 )
                            {
                                integer actPos= idx - 1;
                                bool foundOne= false;
                                while( qtyInserts > 0 )
                                {
                                    actPos= text.LastIndexOf( ' ', actPos );
                                    if( actPos < leftInsertBoundary )
                                        break;
                                    foundOne= true;
                                    text.InsertChars( justifier, 1, actPos );
                                    idx++;
                                    qtyInserts--;
                                    while( --actPos > leftInsertBoundary && text[actPos] == ' ' )
                                        ;
                                }

                                if( !foundOne )
                                    break;
                            }
                        }
                    }
                }

             }
        }

        startIdx= idx;
    }
}


}}}} // namespace [aworx::lib::strings::util]

