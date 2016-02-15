// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
#include "alib/stdafx_alib.h"

#include "alib/config/inifile.hpp"
#include "alib/system/directory.hpp"
#include "alib/system/process.hpp"
#include "alib/strings/tokenizer.hpp"
#include "alib/compatibility/std_iostream.hpp"
#include "alib/core/util.hpp"

#include <fstream>
#include <algorithm>
using namespace std;

namespace aworx {
namespace           lib {
namespace                   config {


// #################################################################################################
// static/globals
// #################################################################################################
String                IniFile::DefaultFileExtension                                   = ".alib.ini";

// #################################################################################################
// Constructor/Destructor
// #################################################################################################
IniFile::IniFile( const String& fileName )
: ConfigurationPlugIn()
{
    EscapeSequences=   {
                             "\\\\",  "\\",
                             "\\n",   "\n",
                             "\\r",   "\r",
                             "\\t",   "\t",
                             "\\/",   "/",
                             "\\#",   "#",
                             "\\;",   ";"
                       };

    if ( fileName.IsNotEmpty() )
    {
        FileName= fileName;
    }
    else
    {
        Directory dir( Directory::SpecialFolder::HOME_CONFIG );


        #if defined (__unix__)
            const ProcessInfo& pi= ProcessInfo::Current();
            FileName._<false>( dir.Path      )
                    ._<false>( PathSeparator )
                    ._<false>( pi.ExecName   )
                    ._<false>( DefaultFileExtension  );

        #elif defined(_WIN32)
            FileName._( dir.Path )._( PathSeparator );
            TCHAR szPath[ MAX_PATH ];
            DWORD pathLen= GetModuleFileName( NULL, szPath, MAX_PATH );
            if ( pathLen <= 0)
            {
                ALIB_WARNING( "Error retrieving module name" );
                FileName._( "Unknown_module_name.aworx.ini");
            }
            else
            {
                // convert to multi byte string and search last dir separator
                String512 moduleFileName;
                moduleFileName._( szPath );
                int sepIdx= moduleFileName.LastIndexOfAny( "/\\", Inclusion::Include );
                if ( sepIdx < 0)
                {
                    ALIB_WARNING( "Error retrieving module name" );
                    FileName._( "Unknown_module_name.aworx.ini" );
                }
                else
                {
                    if( moduleFileName.EndsWith( ".exe" ) )
                        moduleFileName.Delete( moduleFileName.Length() - 4 );

                    FileName._( moduleFileName, sepIdx + 1 )._( ".aworx.ini" );
                }
            }
        #else
            #pragma message ("Unknown Platform in file: " __FILE__ )
        #endif

    }

    ReadFile();
}

// #################################################################################################
// interface
// #################################################################################################

void  IniFile::Clear()
{
    FileComments.Clear();
    Sections.clear();
    LinesWithReadErrors.clear();
    LastStatus= Status::Ok;


    // insert default section without a name as first entry
    Sections.insert( Sections.end(), new Section( nullptr ) );
}

IniFile::Section* IniFile::SearchSection( const String& name )
{
    // search
    auto sIt= find_if( Sections.begin(), Sections.end(),
                       [& name](IniFile::Section* section)
                       {
                          return section->Name.Equals( name, Case::Ignore );
                       }
                      );

    return  sIt != Sections.end()   ? *sIt
                                    : nullptr;
}

IniFile::Section* IniFile::SearchOrCreateSection( const String& name, const String& comments )
{
    Section* s= SearchSection( name );
    if ( s == nullptr )
        Sections.insert( Sections.end(), s= new Section( name ) );

    if ( s->Comments.IsEmpty() )
        s->Comments._( comments );

    return s;
}


IniFile::Variable* IniFile::Section::Insert( const String& name, const String& value, const String& comments )
{
    // search
    auto vIt= find_if( Variables.begin(), Variables.end(),
                       [& name](IniFile::Variable* variable)
                       {
                          return variable->Name.Equals( name, Case::Ignore );
                       }
                      );
    // found?
    Variable* var;
    if ( vIt != Variables.end() )
        var=  *vIt;
    else
    {
        // create variable
        Variables.insert( Variables.end(), new Variable() );
        var= Variables.back();
        var->Name= name;
    }

    var->Value=     value;

    // do not overwrite comments
    if ( var->Comments.IsEmpty() )
        var->Comments._( comments );
    return var;
}

IniFile::Variable* IniFile::Section::Get( const String& name )
{
    // search
    auto vIt= find_if( Variables.begin(), Variables.end(),
                       [& name](IniFile::Variable* variable)
                       {
                          return variable->Name.Equals( name, Case::Ignore );
                       }
                      );
    return  vIt != Variables.end() ?  *vIt
                                   :  nullptr;
}


// #################################################################################################
// Configuration plug-in interface implementation
// #################################################################################################

bool  IniFile::Get( const String& pcategory, const String& name, AString& target )
{
    // check
    if ( name.IsEmpty() )
    {
        ALIB_WARNING( "Empty name given" );
        return false;
    }
    String category= pcategory.IsNotNull() ? pcategory
                                           : "";

    target.Clear();
    Section*    section;
    Variable*   var= nullptr;
    if (    (section= SearchSection( category )) != nullptr
         && (var=     section->Get ( name )    ) != nullptr
       )
        target._( var->Value );

    return var != nullptr;
}

bool  IniFile::Save( const String& pcategory,  const String& name, const String& value,
                     const String& comments,   char           delim                     )
{
    // check
    if ( name.IsEmpty() )
    {
        ALIB_WARNING( "Empty name given" );
        return false;
    }
    String category= pcategory.IsNotNull() ? pcategory
                                           : "";

    // find or create section (create triggered by provided section comments, although empty)
    Section*    section=    SearchOrCreateSection( category, nullptr );
    Variable*   var=        section->Get( name );
    bool        changed=    false;

    if ( var == nullptr )
    {
        var= section->Insert( name, value );
        var->Delim= delim;
        changed= true;
    }
    else
    {
        if ( !var->Value.Equals( value ) )
        {
            var->Value= value;
            changed= true;
        }
    }

    if ( var->Comments.IsEmpty() && !comments.IsEmpty() )
    {
        var->Comments._( comments );
        changed= true;
    }

    // save file
    if ( changed && AutoSave )
        WriteFile();

    return true;
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
    Clear();
    LastStatus= Status::Ok;

    // open file
    ifstream file( FileName.ToCString() );
    if ( !file.is_open() )
        return LastStatus= Status::ErrorOpeningFile;

    AString     lineAS;
    String128   name;
    AString     value;
    AString     comments;
    Section*    actSection= Sections[0];
    int         lineNo= 0;
    bool        fileHeaderRead= false;

    LinesWithReadErrors.clear();

    lib::strings::ReadLineFromIStream readOp= lib::strings::ReadLineFromIStream( file );

    while( !readOp.IsEOF )
    {
        lineAS << readOp;

        lineNo= 0;

        //  place in a substring
        Substring line( lineAS );

        // empty line?
        if ( line.Trim() )
        {
            // already collecting a comment?
            if ( comments.IsNotEmpty() )
            {
                // first empty line in file found?
                if ( !fileHeaderRead )
                {
                    //store comments belonging to file
                    fileHeaderRead= true;
                    FileComments=   comments;
                    comments.Clear();
                    continue;
                }

                comments.NewLine();
            }
            continue;
        }

        // comments line: find comment character '#', ';' or //
        if ( startsWithCommentSymbol( line ) )
        {
            //gather in comments string
            if ( comments.IsNotEmpty() )
                comments.NewLine();
            comments._( line );
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
            actSection= SearchOrCreateSection( String256( line ), comments );
            comments.Clear();

            continue;
        }

        // variable line? If not, we just drop the line!
        Tokenizer tn( line, '=' );
        tn.Next();
        if ( !tn.HasNext() )
        {
            LinesWithReadErrors.insert( LinesWithReadErrors.end(), lineNo );
            continue;
        }

        name= tn.Actual;
        if ( tn.GetRest().IsEmpty() )
        {
            LinesWithReadErrors.insert( LinesWithReadErrors.end(), lineNo );
            continue;
        }

        value.Clear();
        Substring& valueRead= tn.Actual;

        // read continues as long as lines end with '\' (must not be '\\')
        char delim= 0;
        while (     valueRead.CharAtEnd() == '\\'
                && (valueRead.Length() == 1 || valueRead.CharAt<false>( valueRead.Length() -2 ) != '\\' ) )
        {
            // search end before '\'. The first of all broken lines determines the delimiter
            valueRead.ConsumeFromEnd();
            valueRead.TrimEnd();

            if (delim == 0)
            {
                delim= valueRead.CharAtEnd();
                if (  delim == '\"' ||  isalnum( delim ) )
                    delim= 0;
            }

            removeEscapeSequences ( valueRead, value );
            lineAS << readOp;
            if ( readOp.IsEOF )
            {
                // last line of the file ended with '\' !
                valueRead.Clear();
                break;
            }

            (valueRead= lineAS).Trim();
        }
        removeEscapeSequences ( valueRead, value );

        actSection->Insert( name, value, comments )->Delim= delim;
        comments.Clear();

    }
    file.close();

    return LastStatus;
}

void  IniFile::writeComments( ostream& os, const AString& comments )
{
    // is empty when trimmed?
    if ( Substring(comments).Trim() )
        return;

    // tokenize by NEWLINE character
    Tokenizer tok( comments, '\n' );
    tok.Whitespaces= " \r\t"; // \n is not a whitespace

    while( tok.HasNext() )
    {
        if ( !startsWithCommentSymbol( tok.Next() ) )
            os << DefaultCommentPrefix;
        os << tok.Actual << endl;
    }

    tok.Whitespaces=  DefaultWhitespaces;
}


int IniFile::addEscapeSequences( std::ostream& os, const Substring& value )
{
    int sizeDiff= 0;
    String256 val;
    ALIB_WARN_ONCE_PER_INSTANCE_DISABLE( val,  ReplaceExternalBuffer);

    if(    std::isblank( value.CharAtStart() )
        || std::isblank( value.CharAtEnd()  ) )
    {
        val._('\"')._( value )._('\"');
        sizeDiff= 2;
    }
    else
        val._( value );


    for( auto it= EscapeSequences.begin(); it != EscapeSequences.end(); )
    {
        TString& replacement= *it++;
        TString& needle=      *it++;
        sizeDiff+= val.SearchAndReplace( needle, replacement, 0 ) * (replacement.Length() - needle.Length() );
    }

    os.write( val.Buffer(), val.Length() );
    return sizeDiff;
}

void IniFile::removeEscapeSequences( Substring& val, AString& target )
{
    // remove quotation marks
    if( val.CharAtStart() == '\"' &&  val.ConsumeFromEnd( '\"') )
        val.Consume();

    int regionStart= target.Length();
    target._( val );

    for( auto it= EscapeSequences.begin(); it != EscapeSequences.end();  )
    {
        TString& needle=      *it++;
        TString& replacement= *it++;
        target.SearchAndReplace( needle, replacement, regionStart );
    }
}

IniFile::Status  IniFile::WriteFile()
{
    LastStatus= Status::Ok;

    // read all variables
    ofstream file ( FileName.ToCString() );
    if ( !file.is_open() )
        return LastStatus= Status::ErrorOpeningFile;

    // write header
    if ( FileComments.IsNotEmpty() )
    {
        writeComments( file, FileComments );
        file << endl;
    }

    // loop over all sections
    for ( Section* section : Sections )
    {
        // comments, name
        file << endl;
        writeComments( file, section->Comments );

        if ( section->Name.IsNotEmpty() )
            file << '[' << section->Name << ']' << endl;

        // variables
        int maxVarLength= 0;
        for ( Variable* variable : section->Variables )
            maxVarLength= max( maxVarLength, variable->Name.Length() );

        for ( Variable* variable : section->Variables )
        {
            if( variable->Comments.IsNotEmpty() )
            {
                file << endl;
                writeComments( file, variable->Comments );
            }
            file << variable->Name << '=';

            Util::WriteSpaces( file, maxVarLength - variable->Name.Length() + 1 );

            Tokenizer tok( variable->Value, variable->Delim );
            int      backSlashPos= 0;
            int      lastLineLen= 0;
            while( tok.HasNext() )
            {
                // write backslash of previous line and spaces of actual line
                if (tok.Actual.IsNotNull() )
                {
                    if ( backSlashPos < lastLineLen + 1 )
                         backSlashPos=  lastLineLen + 8;

                    Util::WriteSpaces( file, backSlashPos - lastLineLen );

                    file << '\\' << endl;

                    Util::WriteSpaces( file, maxVarLength + 2 ); // 2 for "= "
                }

                // next value
                tok.Next( Whitespaces::Keep );

                // write value
                lastLineLen=  maxVarLength + 2  + tok.Actual.Length();
                lastLineLen+= addEscapeSequences( file, tok.Actual );

                // write delim if a next line is coming
                if ( tok.HasNext() )
                {
                    file << variable->Delim;
                    lastLineLen++;
                }

            }
            file << endl;
        }
    }

    // close file
    file.close();

    return LastStatus;
}


}}}// namespace aworx::lib::config

