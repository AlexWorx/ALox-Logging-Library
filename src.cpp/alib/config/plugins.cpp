// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
#include "alib/alib.hpp"
#include "alib/config/configuration.hpp"
#include "alib/system/environment.hpp"


#if !defined(_STDIO_H) && !defined(_INC_STDIO)
    #include <stdio.h>  /* defines FILENAME_MAX */
#endif

using namespace std;

namespace aworx { namespace lib { namespace config
{
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
        char c= src.ConsumeChar<false>();

        if( lastWasSlash )
        {
            lastWasSlash= false;
            char escChr= c == '\\' ? '\\' :
                         c == '"'  ? '"'  :
                         c == 'n'  ? '\n' :
                         c == 'r'  ? '\r' :
                         c == 't'  ? '\t' :
                         c == 'a'  ? '\a' :
                         c == 'b'  ? '\b' :
                         c == 'v'  ? '\v' :
                         c == 'f'  ? '\f' :
                         c == 'e'  ? '\033' :
                         c;

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
        char c= src.ConsumeChar();

        switch(c)
        {
            case '\\'   : dest._<false>("\\\\"); break;
            case '"'    : dest._<false>("\\\""); break;
            case '\r'   : dest._<false>("\\r" ); break;
            case '\n'   : dest._<false>("\\n" ); break;
            case '\t'   : dest._<false>("\\t" ); break;
            case '\a'   : dest._<false>("\\a" ); break;
            case '\b'   : dest._<false>("\\b" ); break;
            case '\v'   : dest._<false>("\\v" ); break;
            case '\f'   : dest._<false>("\\f" ); break;
            case '\033' : dest._<false>("\\e" ); break;
            default     : dest._<false>(c);      break;
        }
    }

    if ( needsQuotes )
        dest._('"');
}

void XTernalizer::LoadFromString( Variable& variable, const String& value )
{
    variable.ClearValues();
    AString* varValue= &variable.Add();
    Substring src( value );

    if( variable.Delim == '\0' )
    {
        InternalizeValue( src, *varValue );
        return;
    }

    // tokenize
    bool inQuote=      false;
    bool lastWasSlash= false;
    integer idx=          0;
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
            varValue= &variable.Add();
            src.ConsumeChars( idx );
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

    for ( int i= 1; i < argCount ; i++ )
    {
        // create substring on actual variable (trim if somebody would work with quotation marks...)
        Substring actVar;
        if (!wArgs)
            (actVar= (reinterpret_cast<char**>(argVector) [i] )).Trim();
        else
        {
            // convert wide characters
            wcharConverter.Clear()._(  (reinterpret_cast<wchar_t**>(argVector))[i]  );
            (actVar= wcharConverter ).Trim();
        }

        // request '-' and allow a second '-'
        if ( !actVar.ConsumeChar('-') )
            continue;
        actVar.ConsumeChar('-');
        if ( actVar.ConsumeString( variable.Fullname, lang::Case::Ignore ) )
        {
            if ( actVar.IsEmpty() )
            {
                if ( !searchOnly )
                    variable.Add();
                return true;
            }

            if ( actVar.ConsumeChar( Whitespaces::Trim ) == '='  )
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
    system::GetEnvironmentVariable( variable.Fullname, value, lang::CurrentData::Keep );
    if ( value.IsEmpty() )
        return false;

    if( !searchOnly )
        StringConverter->LoadFromString( variable, value );
    return true;
}



}}}// namespace aworx::lib::config

