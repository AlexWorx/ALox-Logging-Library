// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
#include "alib/stdafx_alib.h"

#if !defined (HPP_ALIB_CONFIG_CONFIGURATION)
    #include "alib/config/configuration.hpp"
#endif
#if !defined (HPP_ALIB_CONFIG_INI_FILE)
    #include "alib/config/inifile.hpp"
#endif
#if !defined (HPP_ALIB_SYSTEM_DIRECTORY)
    #include "alib/system/directory.hpp"
#endif
#if !defined (HPP_ALIB_SYSTEM_SYSTEM)
    #include "alib/system/system.hpp"
#endif
#if !defined (HPP_ALIB_SYSTEM_PROCESSINFO)
    #include "alib/system/process.hpp"
#endif
#if !defined (HPP_ALIB_STRINGS_TOKENIZER)
    #include "alib/strings/tokenizer.hpp"
#endif
#if !defined (HPP_ALIB_COMPATIBILITY_STD_IOSTREAM)
    #include "alib/compatibility/std_iostream.hpp"
#endif
#if !defined (HPP_ALIB_UTIL)
    #include "alib/core/util.hpp"
#endif

#include <fstream>
#include <algorithm>
using namespace std;

namespace aworx {
namespace           lib {
namespace                   config {


// #################################################################################################
// static/globals
// #################################################################################################
#if defined(_MSC_VER)
    #pragma warning( push )
    #pragma warning( disable : 4592 )
#endif
String                IniFile::DefaultFileExtension                                   = ".ini";
#if defined(_MSC_VER)
    #pragma warning( pop )
#endif

// #################################################################################################
// class InMemoryPlugin::Entry
// #################################################################################################
void IniFile::Entry::ToVariable( const InMemoryPlugin* parent, Variable& variable )
{
    // if we are still raw, then parse the INI file content
    if ( Values.size() == 0 )
    {
        ALIB_ASSERT( Delim == '\0' );
        Delim= variable.Delim;
        variable.Comments._()._( Comments );

        //-----  remove INI-File specific from raw value -----
        String512 raw;
        ALIB_WARN_ONCE_PER_INSTANCE_DISABLE( raw,  ReplaceExternalBuffer);
        raw._( RawValue );

        // remove '='
        raw.TrimStart();
        if ( raw.CharAtStart() != '=' )
        {
            ALIB_WARNING_S512( "No equal sign in variable \"" << variable.Fullname << "\" of INI file." );
        }
        else
            raw.DeleteStart(1).TrimStart();


        // remove "\\n"
        int startIdx= 0;
        while ( (startIdx= raw.IndexOf( '\n', startIdx )) >= 0 )
        {
            // find \\n and trim around this location
            int delLen= 2;
            if ( raw.CharAt( --startIdx) == '\r' )
            {
                delLen= 3;
                --startIdx;
            }
            ALIB_ASSERT( raw.CharAt(startIdx) == '\\' );
            raw.Delete( startIdx, delLen );

            startIdx= raw.TrimAt( startIdx );

            // if now the next value is starting with a comment symbol, we remove to the next \n
            for(;;)
            {
                char c= raw.CharAt( startIdx );
                if (     c != '#'
                    &&   c != ';'
                    && ( c != '/' || raw.CharAt( startIdx + 1 ) != '/' ) )
                    break;

                int idx= raw.IndexOf( '\n', startIdx );
                if (idx < 0 ) idx= raw.Length();
                raw.Delete( startIdx, idx - startIdx + 1 );
                if( startIdx >= raw.Length() )
                    break;
                startIdx= raw.TrimAt( startIdx );
            }
        }

        // now convert
        parent->StringConverter->LoadFromString( variable, raw );

        // copy the parsed values back to our entry and store the delimiter
        for( int i= 0; i < variable.Size() ; i++ )
            Values.emplace_back( AString( variable.GetString( i ) ) );
    }

    // otherwise, use base method
    else
        InMemoryPlugin::Entry::ToVariable( parent, variable );
}

void IniFile::Entry::FromVariable( const InMemoryPlugin* parent, Variable& variable )
{
    RawValue._();
    InMemoryPlugin::Entry::FromVariable( parent, variable );
}


// #################################################################################################
// Constructor/Destructor
// #################################################################################################
IniFile::IniFile( const String& fileName )
: InMemoryPlugin()
{
    if ( fileName.IsNotEmpty() )
    {
        // don't read anything
        if ( fileName.StartsWith( "*" ) )
        {
            AutoSave= false;
            return;
        }

        FileName= fileName;
    }
    else
    {
        Directory dir( Directory::SpecialFolder::HomeConfig );
        FileName._( dir.Path      )
                ._( DirectorySeparator )
                ._( ProcessInfo::Current().Name  );

        #if defined(_WIN32)
            if( FileName.EndsWith( ".exe" ) )
                FileName.DeleteEnd( 4 );
        #endif

        FileName._( DefaultFileExtension );
    }

    ReadFile();
}

void  IniFile::Reset()
{
    InMemoryPlugin::Reset();
    FileComments.Clear();
    LinesWithReadErrors.clear();
    LastStatus= Status::Ok;
}


// #################################################################################################
// Read/Write files
// #################################################################################################

#if !defined(IS_DOXYGEN_PARSER)
bool startsWithCommentSymbol( Substring& subs )
{
    int i= String("#;/").IndexOf( subs.CharAtStart() );
    return      ( i >= 0 && i < 2)
            ||  ( i == 2 && subs[1] == '/'  );
}
#endif

IniFile::Status  IniFile::ReadFile()
{
    Reset();
    LastStatus= Status::Ok;

    // open file
    ifstream file( FileName.ToCString() );
    if ( !file.is_open() )
        return LastStatus= Status::ErrorOpeningFile;

    AString     lineAS;
    String128   name;
    AString     value;
    AString     comments;
    Section*    actSection= (IniFile::Section*) Sections[0];

    int         lineNo= 0;
    bool        fileHeaderRead= false;

    LinesWithReadErrors.clear();

    lib::strings::ReadLineFromIStream readOp= lib::strings::ReadLineFromIStream( file );

    String16 separatorCharacters( '=' );
    separatorCharacters._( DefaultWhitespaces );

    while( !readOp.IsEOF )
    {
        lineAS << readOp;
        lineNo++;
        Substring line( lineAS );

        bool isEmpty=       line.Trim().IsEmpty();
        bool isCommentLine= startsWithCommentSymbol( line );

        if ( isCommentLine )
        {
            if ( comments.IsNotEmpty() )
                comments.NewLine();
            comments._(line);
            continue;
        }

        // still processing file header?
        if ( !fileHeaderRead )
        {
            fileHeaderRead= true;
            FileComments=   comments;
            comments.Clear();
        }

        // empty line?
        if ( isEmpty )
        {
            if ( comments.IsNotEmpty() )
                comments.NewLine();
            continue;
        }

        // section line
        if ( line.Consume('[') )
        {
            fileHeaderRead= true;

            // we do not care if there is no closing bracket. But if there is one, we remove it.
            if( !line.ConsumeFromEnd( ']' ) )
                LinesWithReadErrors.insert( LinesWithReadErrors.end(), lineNo );


            // search the section in our section list (if section existed already, new comments
            // are dropped)
            actSection= (IniFile::Section*) SearchOrCreateSection( line, comments );
            comments.Clear();

            continue;
        }

        // Variable line
        value.Clear();
        int idx= line.IndexOfAny( separatorCharacters, enums::Inclusion::Include );
        if( idx < 0 )
        {
            name._()._( line );
            line.Clear();
        }
        else
        {
            name._()._( line, 0, idx );
            line.Consume( idx );
            value._(line);
        }

        // read continues as long as lines end with '\' (must not be '\\')
        while (    line.CharAtEnd()  == '\\'
                && (line.Length() == 1 || line.CharAt<false>( line.Length() -2 ) != '\\' ) )
        {
            value.NewLine();
            lineAS << readOp;
            if ( readOp.IsEOF )
            {
                // last line of the file ended with '\' !
                line.Clear();
                break;
            }
            lineAS.TrimEnd();
            line= lineAS;

            value._( lineAS );
        }

        // insert entry with raw value
        {
            IniFile::Entry* entry= (IniFile::Entry*) actSection->GetEntry( name, true );
            entry->Values  .clear();
            entry->Comments._()._( comments );
            entry->RawValue._()._( value );

            // if there is just no raw value, we add an empty string to the entries' values
            if ( value.IsEmpty() )
                entry->Values.insert( entry->Values.end(), AString() );
        }

        comments.Clear();

    }
    file.close();

    return LastStatus;
}

void  IniFile::writeComments( ostream& os, const AString& comments )
{
    // is empty when trimmed?
    if ( Substring(comments).Trim().IsEmpty() )
        return;

    // tokenize by NEWLINE character
    Tokenizer tknzr( comments, '\n' );
    tknzr.Whitespaces= " \r\t"; // \n is not a whitespace

    while( tknzr.Next(enums::Whitespaces::Keep).IsNotNull() )
    {
        if ( !startsWithCommentSymbol( tknzr.Actual ) )
            os << DefaultCommentPrefix;
        os << tknzr.Actual << endl;
    }

    tknzr.Whitespaces=  DefaultWhitespaces;
}

#if !defined( IS_DOXYGEN_PARSER)
int getAssignmentPos( const AString& value, const String& alignmentSeparator )
{
    int idx= value.IndexOf( alignmentSeparator );
    if( idx > 0 )
    {
        int idxQuote= value.IndexOf( '"' );
        if ( idxQuote < 0  || idxQuote > idx )
            return idx;
    }
    return -1;
}
#endif

IniFile::Status  IniFile::WriteFile()
{
    LastStatus= Status::Ok;

    // read all variables
    ofstream file ( FileName.ToCString() );
    if ( !file.is_open() )
        return LastStatus= Status::ErrorOpeningFile;

    // write file header
    if ( FileComments.IsNotEmpty() )
    {
        writeComments( file, FileComments );
        file << endl;
    }

    // loop over all sections
    int cntVars= 0;
    for ( InMemoryPlugin::Section* section : Sections )
    {
        // comments, name
        if ( cntVars > 0 )
            file << endl;

        // write section comments and name
        writeComments( file, section->Comments );
        if ( section->Name.IsNotEmpty() )
            file << '[' << section->Name << ']' << endl;

        // variables
        int maxVarLength= 0;
        for ( InMemoryPlugin::Entry* entry : section->Entries )
            maxVarLength= max( maxVarLength, entry->Name.Length() );

        bool previousVarHasComments= true;
        for ( InMemoryPlugin::Entry* entry : section->Entries )
        {
            cntVars++;

            // write comments
            if( entry->Comments.IsNotEmpty() )
            {
                // we make an extra empty line if previous var had no comments
                if( !previousVarHasComments)
                    file << endl;

                writeComments( file, entry->Comments );
            }

            // write name =
            file << entry->Name;

            // either write raw value (if it was not used by the application)
            if (((IniFile::Entry*) entry)->RawValue.IsNotEmpty() )
            {
                file << ((IniFile::Entry*) entry)->RawValue;
            }

            // or write the values parsed by the software
            else
            {
                file << '=';
                Util::WriteSpaces( file, maxVarLength - entry->Name.Length() + 1 );

                bool     isFirst=      true;
                String128 externalizedValue;

                //-------- write as single-line ----------
                if ( 0 == ( entry->FormatHints & Variable::FormatHint_MultLine  ) )
                {
                    bool delimSpaces=  (0 == ( entry->FormatHints & Variable::FormatHint_NoDelimSpaces ) );
                    for( AString& value : entry->Values )
                    {
                        // write delim and backslash of previous line, newline and then spaces of actual line
                        if ( !isFirst )
                        {
                            ALIB_ASSERT_ERROR_S512( entry->Delim != 0,
                                                    "No delimiter given for multi-value variable \""
                                                    << entry->Name << "\"." );

                            if( delimSpaces && FormatSpaceBeforeDelim)
                                file << ' ';

                            file << entry->Delim;

                            if( delimSpaces && FormatSpaceAfterDelim)
                                file << ' ';
                        }

                        // externalize value
                        Substring src( value );
                        externalizedValue._();
                        StringConverter->ExternalizeValue( src, externalizedValue, entry->Delim );
                        file << externalizedValue;
                        isFirst= false;
                    }
                }

                // ---------- write as multi-line ----------
                else
                {
                    int      backSlashPos= 0;
                    ALIB_WARN_ONCE_PER_INSTANCE_DISABLE( externalizedValue,  ReplaceExternalBuffer);
                    int      lastLineLen=  0;

                    // Get maximum position of attribute assignment char '=' or ':' (if exists)
                    int maxAttributeAssignPos= 0;
                    bool allAttrHavePrecedingBlanks= true;
                    if (entry->FormatAttrAlignment.IsNotEmpty() )
                    {
                        for( AString& value : entry->Values )
                        {
                            int attributeAssignPos= getAssignmentPos( value, entry->FormatAttrAlignment );
                            if ( attributeAssignPos > 0 )
                            {
                                if ( maxAttributeAssignPos < attributeAssignPos )
                                    maxAttributeAssignPos= attributeAssignPos;
                                allAttrHavePrecedingBlanks&= value.CharAt( attributeAssignPos - 1 ) == ' ';
                            }
                        }
                        if ( !allAttrHavePrecedingBlanks )
                            maxAttributeAssignPos += 1;
                    }

                    // loop over values of entry
                    for( AString& value : entry->Values )
                    {

                        // write delim and backslash of previous line, newline and then spaces of actual line
                        if ( !isFirst )
                        {
                            ALIB_ASSERT_ERROR_S512( entry->Delim != 0,
                                                    "No delimiter given for multi-value variable \""
                                                    << entry->Name << "\"." );
                            file << entry->Delim;
                            lastLineLen++;

                            if ( backSlashPos < lastLineLen + 1 )
                                 backSlashPos=  lastLineLen + 4;

                            Util::WriteSpaces( file, backSlashPos - lastLineLen );

                            file << '\\' << endl;

                            Util::WriteSpaces( file, maxVarLength + 2 ); // 2 for "= "
                        }

                        // externalize value
                        Substring src( value );
                        externalizedValue._();
                        StringConverter->ExternalizeValue( src, externalizedValue, entry->Delim );

                        // if first character is a INI comment char, then escape it
                        char firstChar= externalizedValue.CharAt(0);
                        if( !isFirst && (firstChar == '#' || firstChar == ';' ) )
                            externalizedValue.InsertAt("\\", 0 );

                        // if assignment, insert spaces to align assignments
                        if (entry->FormatAttrAlignment.IsNotEmpty() )
                        {
                            int attributeAssignPos= getAssignmentPos( externalizedValue, entry->FormatAttrAlignment );
                            if ( attributeAssignPos > 0 && attributeAssignPos < maxAttributeAssignPos )
                                externalizedValue.InsertChars( ' ',
                                                               maxAttributeAssignPos-attributeAssignPos,
                                                               attributeAssignPos + (FormatIncludeDelimInAttrAlignment ?
                                                                                      0 : entry->FormatAttrAlignment.Length() )
                                                              );
                        }
                        file << externalizedValue;

                        lastLineLen=  maxVarLength + 2  + externalizedValue.Length();
                        isFirst= false;
                    }
                }
            }
            file << endl;

            // add an empty line if we have comments
            if( (previousVarHasComments= entry->Comments.IsNotEmpty() ) == true )
                file << endl;
        }
    }

    // close file
    file.close();

    return LastStatus;
}


}}}// namespace aworx::lib::config

