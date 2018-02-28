// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2018 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
#include "alib/alib.hpp"

#if !defined (HPP_ALIB_STRINGS_FORMAT_SIMPLETEXT)
    #include "alib/strings/format/simpletext.hpp"
#endif

#if !defined (HPP_ALIB_STRINGS_UTIL_STRINGTUPLES)
    #include "alib/strings/util/stringtuples.hpp"
#endif

#if !defined (HPP_ALIB_STRINGS_UTIL_TOKENIZER)
    #include "alib/strings/util/tokenizer.hpp"
#endif


#if !defined (HPP_ALIB_LANG_EXCEPTION)
    #include "alib/lang/exception.hpp"
#endif

#include <algorithm>

using namespace std;

namespace aworx { namespace lib { namespace strings { namespace format  {


// #################################################################################################
// Non-static methods (if used with instance).
// #################################################################################################

SimpleText& SimpleText::PushIndent( const String& indentFirstLine, const String& pIndentOtherLines )
{
    String indentOtherLines= pIndentOtherLines.IsNull()  ? indentFirstLine
                                                         : pIndentOtherLines;

    IndentFirstLine ._( indentFirstLine );
    IndentOtherLines._( indentOtherLines );
    IndentSizesFirstLine .push( indentFirstLine.Length()  );
    IndentSizesOtherLines.push( indentOtherLines.Length() );
    return *this;
}

SimpleText& SimpleText::PushIndent( uinteger qty, char fillChar )
{

    IndentFirstLine .InsertChars( fillChar, static_cast<integer>( qty ) );
    IndentOtherLines.InsertChars( fillChar, static_cast<integer>( qty ) );
    IndentSizesFirstLine .push( static_cast<integer>( qty ) );
    IndentSizesOtherLines.push( static_cast<integer>( qty ) );
    return *this;
}

SimpleText& SimpleText::PopIndent()
{
    ALIB_ASSERT_ERROR( !IndentSizesFirstLine.empty(), "SimpleText: PopIndent without prior push." )
    IndentFirstLine.DeleteEnd( static_cast<integer>( IndentSizesFirstLine.top() ) );
    IndentSizesFirstLine.pop();

    ALIB_ASSERT_ERROR( !IndentSizesOtherLines.empty(), "SimpleText: PopIndent without prior push." )
    IndentOtherLines.DeleteEnd( static_cast<integer>( IndentSizesOtherLines.top() ) );
    IndentSizesOtherLines.pop();
    return *this;
}

SimpleText&     SimpleText::Clear()
{
    Text.Clear();
    while( IndentSizesFirstLine .size() ) IndentSizesFirstLine .pop();
    while( IndentSizesOtherLines.size() ) IndentSizesOtherLines.pop();
    IndentFirstLine .Clear();
    IndentOtherLines.Clear();
    markerBulletLevel= 0;
    return *this;
}


void   SimpleText::Add( Boxes&  args )
{
    integer startIdx= Text.Length();
    Formatter.Format( Text, args );
    integer maxLineWidth;
    SimpleText::FormatParagraph( Text, startIdx, LineWidth, JustifyChar, maxLineWidth, IndentFirstLine, IndentOtherLines );
    DetectedMaxLineWidth= (std::max)(DetectedMaxLineWidth, maxLineWidth );

    if ( Text.IsNotEmpty() && !Text.EndsWith( NewLine ) )
        Text << NewLine;
}

//! @cond NO_DOX
namespace
{
    ALIB_NO_RETURN
    void throwMarkerException( Exceptions eType, String& markedBuffer, integer errPos )
    {
        String64 actText;
        integer excerptPos= 25;
        integer excerptStart= errPos - 25;
        if( excerptStart <= 0 )
        {
            excerptPos+= excerptStart;
            excerptStart= 0;
        }
        else
        {
            actText._( "[...]" );
            excerptPos+= 5;
        }


        actText._( markedBuffer, excerptStart, 50 );
        if( markedBuffer.Length() > excerptStart + 50 )
            actText._( "[...]" );
                     actText.SearchAndReplace( "\r", "\\r", excerptPos );
                     actText.SearchAndReplace( "\n", "\\n", excerptPos );
        excerptPos+= actText.SearchAndReplace( "\r", "\\r"             );
        excerptPos+= actText.SearchAndReplace( "\n", "\\n"             );

        throw Exception( ALIB_SRCPOS_REL_NULLED, eType,
                         errPos, actText, excerptPos );
    }
}
//! @endcond

void   SimpleText::AddMarked( Boxes&  args )
{
    char searchCharBuf[3];
         searchCharBuf[0]= MarkerChar;
         searchCharBuf[1]= '\n';
    String searchChars(searchCharBuf, 2);

    Formatter.Format( markedBuffer.Clear(), args );
    Substring parser=  markedBuffer;
    integer lastTextStart=  Text.Length();

    while( parser.IsNotEmpty() )
    {
        integer pos= parser.IndexOfAny<Inclusion::Include, false>( searchChars );

        // not found
        if( pos < 0 )
        {
            Text << parser;
            break;
        }

        // new line
        if( parser.CharAt( pos ) == '\n' )
        {
            parser.ConsumeChars<false, lang::CurrentData::Keep>( pos, Text, 1 );
            parser.ConsumeChar( '\r' );
            Text << NewLine;
            integer maxLineWidth;
            SimpleText::FormatParagraph( Text, lastTextStart, LineWidth, JustifyChar,
                                         maxLineWidth, IndentFirstLine, IndentOtherLines );
            DetectedMaxLineWidth= (std::max)(DetectedMaxLineWidth, maxLineWidth );
            lastTextStart=  Text.Length();
            continue;
        }

        parser.ConsumeChars<false, lang::CurrentData::Keep>( pos, Text, 1 );

        // double marker: insert one symbol
             if( parser.ConsumeChar( MarkerChar ) )
            Text << MarkerChar;

        // Indent
        else if( parser.ConsumeString(">'") )
            PushIndent(  parser.ConsumeToken( '\'' ) );

        else if( parser.ConsumeString(">>") )
            PushIndent( "  " );

        else if( parser.ConsumeString("<<") )
        {
            if( IndentSizesFirstLine.empty() )
                throwMarkerException( Exceptions::EndmarkerWithoutStart, markedBuffer,
                                      markedBuffer.Length() - parser.Length() - 3 );
            PopIndent();
        }

        // bullets
        else if( parser.ConsumeString("*>") )
        {
            if( markerBulletLevel > 0 )
            {
                IndentFirstLine .DeleteEnd( 2 )._( "  " );
                IndentOtherLines.DeleteEnd( 2 )._( "  " );
            }
            IndentFirstLine ._( MarkerBullets[markerBulletLevel] )._(' ');
            IndentOtherLines._( "  " );
            markerBulletLevel++;
        }
        else if( parser.ConsumeString("<*") )
        {
            if( markerBulletLevel == 0 )
                throwMarkerException( Exceptions::EndmarkerWithoutStart, markedBuffer,
                                      markedBuffer.Length() - parser.Length() - 3 );

            int deIndentCnt= markerBulletLevel > 1 ? 4 : 2;
            IndentFirstLine .DeleteEnd( deIndentCnt );
            IndentOtherLines.DeleteEnd( deIndentCnt );
            if( --markerBulletLevel > 0 )
            {
                IndentFirstLine ._( MarkerBullets[markerBulletLevel - 1] )._(' ');
                IndentOtherLines._( "  " );
            }
        }

        else if( parser.ConsumeChar('p' ) || parser.ConsumeChar('P') )
            Text << NewLine;


        // horizontal line
        else if( parser.ConsumeString("HL") )
        {
            Text.InsertChars( parser.ConsumeChar() , LineWidth - IndentFirstLine.Length() )
                ._( NewLine );
        }

        // not recognized
        else
        {
            throwMarkerException( Exceptions::UnknownMarker, markedBuffer,
                                  markedBuffer.Length() - parser.Length() - 1 );
        }
    }

    if( lastTextStart < Text.Length() )
    {
        integer maxLineWidth;
        SimpleText::FormatParagraph( Text, lastTextStart, LineWidth, JustifyChar, maxLineWidth,
                                     IndentFirstLine, IndentOtherLines );
        DetectedMaxLineWidth= (std::max)(DetectedMaxLineWidth, maxLineWidth );
    }
    if ( Text.IsNotEmpty() && !Text.EndsWith( NewLine ) )
        Text << NewLine;
}


// #################################################################################################
// The static formatter method
// #################################################################################################
void  SimpleText::FormatParagraph( AString& text, integer startIdx, integer lineWidth,
                                   char justifyChar, integer& maxLineWidth,
                                   const String& pIndentFirstLine,
                                   const String& pIndentOtherLines                         )
{
    maxLineWidth= 0;
    String indentFirstLines= pIndentFirstLine .IsNotNull()  ? pIndentFirstLine  : EmptyString;
    String indentOtherLines= pIndentOtherLines.IsNotNull()  ? pIndentOtherLines : pIndentFirstLine;

    bool isFirstLine= true;

    String indent= NullString;
    bool   indentAreJustSpaces= false;

    integer maxLineWidthDetectionStartIdx= startIdx;
    while ( startIdx < text.Length() )
    {
        maxLineWidth= (std::max)( maxLineWidth, startIdx - maxLineWidthDetectionStartIdx -1 );
        maxLineWidthDetectionStartIdx= startIdx;

        // skip lines beginning with newline characters, unless indent has non-space characters
        int isWinNL=  text[ startIdx ] == '\r' ? 1 : 0;
        if ( text[ startIdx + isWinNL ] == '\n' )
        {
            // set indent and check if its just spaces
            if( indent.IsNull() )
            {
                indent = isFirstLine ? indentFirstLines : indentOtherLines;
                indentAreJustSpaces= (indent.IndexOfAny<Inclusion::Exclude>( " " ) < 0 );
            }

            // insert indent if not just spaces
            if ( !indentAreJustSpaces )
            {
                text.InsertAt( indent, startIdx );
                startIdx+= indent.Length();
            }

            startIdx+= 1 + isWinNL;
            if( isFirstLine )
            {
                isFirstLine= false;
                indent=      NullString;
            }

            continue;
        }

        // insert indent
        if( indent.IsNull() )
        {
            indent = isFirstLine ? indentFirstLines : indentOtherLines;
            indentAreJustSpaces= (indent.IndexOfAny<Inclusion::Exclude>( " " ) < 0 );
        }
        text.InsertAt( indent, startIdx );

        if( isFirstLine )
        {
            isFirstLine= false;
            indent=      NullString;
        }


        // find next end of line. Remember last space in line
        integer lastSpaceInLine=  0;
        bool    isLastLine=       true;
        bool    exceeds=          false;
        integer idx= startIdx + indent.Length() - 1;
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
                    lastSpaceInLine= idx;

                if( exceeds )
                {
                    isLastLine= false;
                    break;
                }
            }
        }

        // wrap line.
        if( exceeds && ( lastSpaceInLine || !isLastLine ) )
        {
            integer wrapPos= lastSpaceInLine > 0 ? lastSpaceInLine : idx;
            text.ReplaceSubstring( NewLine, wrapPos, 1 );
            idx= wrapPos + NewLine.Length();

            // block justification
            if( justifyChar != '\0' )
            {
                integer qtyInserts= lineWidth - (idx - startIdx ) + 1;
                if( qtyInserts > 0 )
                {
                    // search first non-space after indent.
                    integer leftInsertBoundary= startIdx + indent.Length();
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
                                text.InsertChars( justifyChar, 1, actPos );
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

        startIdx= idx;
    }

    maxLineWidth= (std::max)( maxLineWidth, startIdx - maxLineWidthDetectionStartIdx -1 );
}


SimpleText& SimpleText::AddException( Exception&  e )
{
    Tokenizer tknzr;
    tknzr.Whitespaces= "\r";
    String256 buf;
    ALIB_WARN_ONCE_PER_INSTANCE_DISABLE( buf,  ReplaceExternalBuffer );

    size_t entryNo= 1;
    for ( auto entry= e.Entries.begin(); entry < e.Entries.end(); entry++ )
    {
        Add( "E{}: <{}>", entryNo, entry->Code );
        PushIndent( "    " );
        Exception::Describe( buf.Clear(), *entry );
        tknzr.Set( buf, '\n' );
        while( tknzr.HasNext() )
            Add( tknzr.Next()  );

        PopIndent();
        entryNo++;
    }

    return *this;
}


}}}} // namespace [aworx::lib::strings::util]

