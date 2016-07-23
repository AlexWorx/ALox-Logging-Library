// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
#include "alib/stdafx_alib.h"
#include "alib/config/configuration.hpp"
#include "alib/system/system.hpp"


#if !defined(_STDIO_H) && !defined(_INC_STDIO)
    #include <stdio.h>  /* defines FILENAME_MAX */
#endif

using namespace std;

namespace aworx {
namespace           lib {
namespace                   config {

// #################################################################################################
// XTernalizer
// #################################################################################################
void XTernalizer::InternalizeValue( Substring& src, AString& dest )
{
    src.Trim();
    bool inUnquoted=   true;
    bool inQuote=      false;
    bool lastWasSlash= false;

    while( src.IsNotEmpty() )
    {
        char c= src.Consume<false>();

        if( lastWasSlash )
        {
            lastWasSlash= false;
            char escChr= c == '\\' ? '\\' :
                         c == 'n'  ? '\n' :
                         c == 'r'  ? '\r' :
                         c == 't'  ? '\t' :
                         c == '"'  ? '"'  : c;

            dest._<false>(escChr);
            continue;
        }

        if( c== '\\' )
        {
            lastWasSlash= true;
            continue;
        }

        if( c== '"' )
        {
            inQuote= !inQuote;
            inUnquoted= false;
            continue;
        }

        if( inQuote || inUnquoted )
        {
            dest._<false>(c);
            continue;
        }

        if( DefaultWhitespaces.IndexOf(c) >= 0 )
            continue;
        inUnquoted= true;

        dest._<false>(c);
    }
}

void XTernalizer::ExternalizeValue( Substring& src, AString& dest, char delim )
{
    bool needsQuotes=       src.CharAtStart() == ' '
                        ||  src.CharAtEnd()   == ' '
                        ||  src.IndexOf( delim ) >= 0;
    if ( needsQuotes )
        dest._<false>('"');

    while( src.IsNotEmpty() )
    {
        char c= src.Consume();

        switch(c)
        {
            case '\\' : dest._<false>("\\\\"); break;
            case '\r' : dest._<false>("\\r" ); break;
            case '\n' : dest._<false>("\\n" ); break;
            case '\t' : dest._<false>("\\t" ); break;
            case '"'  : dest._<false>("\\\""); break;
            default   : dest._<false>(c);      break;
        }
    }

    if ( needsQuotes )
        dest._('"');
}

void XTernalizer::LoadFromString( Variable& variable, const String& value )
{
    variable.ClearValues();
    AString* varValue= &variable.AddString();
    Substring src( value );

    if( variable.Delim == '\0' )
    {
        InternalizeValue( src, *varValue );
        return;
    }

    // tokenize
    bool inQuote=      false;
    bool lastWasSlash= false;
    int  idx=          0;
    while( idx < src.Length()  )
    {
        char c= src.CharAt<false>( idx++ );

        if( lastWasSlash )
        {
            lastWasSlash= false;
            continue;
        }

        if( c== '\\' )
        {
            lastWasSlash= true;
            continue;
        }

        if( c== '"' )
        {
            inQuote= !inQuote;
            continue;
        }

        if( !inQuote && c == variable.Delim )
        {
            Substring tok( src, 0, idx - 1 );
            InternalizeValue( tok, *varValue );
            varValue= &variable.AddString();
            src.Consume( idx );
            src.TrimStart();
            idx= 0;
        }
    }
    if ( src.IsNotEmpty() )
    {
        InternalizeValue( src, *varValue );
    }
}



// #################################################################################################
// CommandLinePlugin
// #################################################################################################
bool  CommandLinePlugin::Load( Variable& variable, bool searchOnly )  const
{
    // assemble option name as CATEGORY_NAME
    String4K   wcharConverter;

    for ( int i= 1; i < argc ; i++ )
    {
        // create substring on actual variable (trim if somebody would work with quotation marks...)
        Substring actVar;
        if (!wArgs)
            (actVar= ( ((char**) argv)[i] )).Trim();
        else
        {
            // convert wide characters
            wcharConverter.Clear()._(  ((wchar_t**) argv)[i]  );
            (actVar= wcharConverter ).Trim();
        }

        // request '-' and allow a second '-'
        if ( !actVar.Consume('-') )
            continue;
        actVar.Consume('-');
        if ( actVar.StartsWith( variable.Fullname, enums::Case::Ignore ) )
        {
            actVar.Consume<false>( variable.Fullname.Length() );
            if ( actVar.IsEmpty() )
            {
                if ( !searchOnly )
                    variable.AddString();
                return true;
            }

            if ( actVar.Consume( Whitespaces::Trim ) == '='  )
            {
                if ( !searchOnly )
                    StringConverter->LoadFromString( variable, actVar.Trim() );
                return true;
            }
         }
    }

    return false;
}

// #################################################################################################
// EnvironmentPlugin
// #################################################################################################
EnvironmentPlugin::EnvironmentPlugin()
: ConfigurationPlugin()
{
}

bool  EnvironmentPlugin::Load( Variable& variable, bool searchOnly )  const
{
    String256 value;
    ALIB_WARN_ONCE_PER_INSTANCE_DISABLE( value,  ReplaceExternalBuffer );
    System::GetVariable( variable.Fullname, value, enums::CurrentData::Keep );
    if ( value.IsEmpty() )
        return false;

    if( !searchOnly )
        StringConverter->LoadFromString( variable, value );
    return true;
}



}}}// namespace aworx::lib::config

