// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
#include "alib/stdafx_alib.h"
#include "alib/config/configuration.hpp"
#include "alib/strings/assubstring.hpp"
#include "alib/system/system.hpp"


#if !defined(_STDIO_H) && !defined(_INC_STDIO)
    #include <stdio.h>  /* defines FILENAME_MAX */
#endif

using namespace std;
using namespace aworx::lib::enums;
using namespace aworx::lib::system;
using namespace aworx::lib::strings;

namespace aworx {
namespace           lib {
namespace                   config {

// #################################################################################################
// ConfigurationPlugIn
// #################################################################################################

bool  ConfigurationPlugIn::Get( const AS& category, const AS& name,  int32_t& target )
{
    target= 0;
    String64 value;
    if ( !Get( category, name, value ) )
        return false;

    target= value.ToInt( );
    return true;
}

bool  ConfigurationPlugIn::Get( const AS& category, const AS& name,  double& target )
{
    target= 0.0;
    String64 value;
    if ( !Get( category, name, value ) )
        return false;

    target= value.ToFloat( 0, nullptr, Parent != nullptr ? &Parent->NumberFormat : &NumberFormat::Global );
    return true;
}


bool  ConfigurationPlugIn::Save( const AS& category, const AS& name,
                                 int            value,    const AS& comments  )
{
    String32 valueString;
    valueString._( value );
    return Save( category, name, valueString, comments, '\0' );
}

bool  ConfigurationPlugIn::Save( const AS& category, const AS& name,
                                 double         value,    const AS& comments  )
{
    String64 valueString;
    valueString._( Format::Double(value, Parent != nullptr ? &Parent->NumberFormat : &NumberFormat::Global)  );
    return Save( category, name, valueString, comments, '\0' );
}


// #################################################################################################
// CommandLinePlugIn
// #################################################################################################
CommandLinePlugIn::CommandLinePlugIn( int argc, void **argv, bool wArgs )
: ConfigurationPlugIn()
{
    this->argc=     argc;
    this->argv=     argv;
    this->wArgs=    wArgs;
}

bool  CommandLinePlugIn::Get( const AS& category, const AS& name, AString& target )
{
    // assemble option name as CATEGORY_NAME
    String128 category_name;
    if ( category.IsNotEmpty() )
        category_name._( category )._( '_' );
    category_name._( name );

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

        if ( actVar.StartsWith( category_name, enums::Case::Ignore ) )
        {
            actVar.Consume<false>( category_name.Length() );
            if ( actVar.Consume( Whitespaces::Trim ) == '='  )
            {
                actVar.Trim();
                target= actVar;
                return true;
            }
         }
    }

    return false;
}

// #################################################################################################
// EnvironmentPlugIn
// #################################################################################################
EnvironmentPlugIn::EnvironmentPlugIn()
: ConfigurationPlugIn()
{
}

bool  EnvironmentPlugIn::Get( const AS& category, const AS& name, AString& target )
{
    String128 category_name;
    if ( category.IsNotEmpty() )
        category_name._( category )._( '_' );
    category_name._( name );

    System::GetVariable( category_name, target );
    return target.Trim().Length() > 0;
}



}}}// namespace aworx::lib::config

