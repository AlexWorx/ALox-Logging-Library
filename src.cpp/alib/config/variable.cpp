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

#if !defined(HPP_ALIB_STRINGS_NUMBERFORMAT)
    #include "alib/strings/numberformat.hpp"
#endif

#if !defined(HPP_ALIB_STRINGS_TOKENIZER)
    #include "alib/strings/tokenizer.hpp"
#endif



using namespace std;

namespace aworx {
namespace           lib {
namespace                   config {


void    Variable::clear()
{
    Config=         nullptr;
    Priority=       -1;
    Delim=          '\0';
    FormatHints=    0;

    Category._();
    Name    ._();
    Comments._();
    Fullname._();
    ClearValues();

}

Variable&    Variable::Define( const VariableDefinition&    definition,
                               std::vector<String>&         replacements )
{
    clear();

    Delim=               definition.Delim;
    FormatHints=         definition.FormatHints;
    FormatAttrAlignment= definition.FormatAttrAlignment;

    // set Category, Name, Comment
    Category._(    definition.Category.IsNotNull()
                           ?  definition.Category
                           :  definition.CategoryFallback
                           ? *definition.CategoryFallback
                           : NullString                     );
    Name    ._( definition.Name    );
    Comments._( definition.Comments );

    if ( definition.DefaultValue.IsNotNull() )
        DefaultValue._()._( definition.DefaultValue );
    else
        DefaultValue.SetNull();


    // replace strings
    int replCnt= 1;
    for ( auto replacement : replacements )
    {
        String64 search("%"); search._( replCnt );
        if ( replacement.IsNotNull() ) { Category    .SearchAndReplace( search, replacement );
                                         Name        .SearchAndReplace( search, replacement );
                                         Comments    .SearchAndReplace( search, replacement );
                                         DefaultValue.SearchAndReplace( search, replacement );
                                       }

        replCnt++;
    }

    // set full name
    if( Category.IsNotEmpty() )
        Fullname._( Category )._( '_' );
    Fullname._( Name );

    ALIB_ASSERT_WARNING(  Name.IsNotEmpty(), "Empty variable name given" );

    return *this;
}

Variable&   Variable::Define( const String& category,  const String& name,  char  delim ,
                              const String& comments     )
{
    clear();

    Category._(category);
    Name    ._(name);
    Comments._(comments);
    Delim=   delim;

    if( Category.IsNotEmpty() )
        Fullname._( Category )._( '_' );
    Fullname._( Name );

    return *this;
}

void Variable::ReplaceValue( int idx, Variable& replVariable )
{
    if( idx < 0 || idx >= qtyValues )
    {
        ALIB_WARNING_S512( "Index out of range: " << idx << " ( 0 - " << qtyValues << " allowed)." );
        return;
    }

    int replSize= replVariable.Size();
    if( replSize == 0 )
    {
        values.erase( values.begin() + idx );
        return;
    }

    values[idx]._()._( replVariable.GetString(0) );
    for( int i= 1 ; i < replSize; i++ )
    {
        values.insert( values.begin() + idx + i, AString( replVariable.GetString(i) ) );
        qtyValues++;
    }
}

AString&    Variable::AddString()
{
    int actIdx= qtyValues;
    qtyValues++;
    if( actIdx < (int) values.size() )
        return values[actIdx].Clear();

    values.insert( values.end(), AString() );
    return values[actIdx];
}

AString&    Variable::AddInteger( int value )
{
    return AddString()._( value );
}

AString&    Variable::AddFloat( double value )
{
    return AddString()._( Format::Double( value, &ALIB::Config.NumberFormat ) );
}



bool        Variable::IsTrue   (int idx) { return  idx < qtyValues ? Config->IsTrue( GetString(idx) )                             : false; }
int         Variable::GetInteger   (int idx) { return  idx < qtyValues ? GetString(idx)->ToInt()                                      : 0;     }
double      Variable::GetFloat(int idx) { return  idx < qtyValues ? GetString(idx)->ToFloat( 0, nullptr, &Config->NumberFormat ) : 0.0;   }



// #################################################################################################
// convenience methods using ALIB::Config singelton
// #################################################################################################
int  Variable::Load()
{
    return ALIB::Config.Load( *this );
}

int  Variable::Store( const String& externalizedValue )
{
    return ALIB::Config.Store( *this, externalizedValue );
}

int  Variable::StoreDefault( const String& externalizedValue )
{
    if ( externalizedValue.IsNotNull() )
        ALIB::Config.DefaultValues.StringConverter->LoadFromString( *this, externalizedValue );

    if ( Size() == 0 && DefaultValue.IsNotNull() )
        ALIB::Config.DefaultValues.StringConverter->LoadFromString( *this, DefaultValue );

    Priority= Configuration::PrioDefault;
    return ALIB::Config.Store( *this, NullString );
}

int  Variable::Protect( const String& externalizedValue )
{
    if ( externalizedValue.IsNotNull() )
        ALIB::Config.DefaultValues.StringConverter->LoadFromString( *this, externalizedValue );

    if ( Size() == 0 && DefaultValue.IsNotNull() )
        ALIB::Config.DefaultValues.StringConverter->LoadFromString( *this, DefaultValue );

    Priority= Configuration::PrioProtected;
    return ALIB::Config.Store( *this, NullString );
}

int  Variable::LoadFromString( const String& externalizedValue )
{
    ALIB::Config.DefaultValues.StringConverter->LoadFromString( *this, externalizedValue );
    return Size();
}

bool Variable::GetAttribute( const String& attrName, Substring& result, char attrDelim )
{
    for ( int i= 0; i< Size(); i++ )
    {
        result.Set( GetString(i ) );
        if (    result.Consume( attrName,  enums::Case::Ignore, enums::Whitespaces::Trim )
             && result.Consume( attrDelim, enums::Case::Ignore, enums::Whitespaces::Trim ) )
        {
            result.Trim();
            return true;
        }
    }
    return false;
}

}}}// namespace aworx::lib::config

