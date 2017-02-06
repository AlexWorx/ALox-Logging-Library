// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
#include "alib/alib.hpp"

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

namespace aworx { namespace lib { namespace config
{

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
        ALIB_WARNING( "Index out of range: ", idx  );
        return;
    }

    int replSize= replVariable.Size();
    if( replSize == 0 )
    {
        values.erase( values.begin() + idx );
        return;
    }

    values[static_cast<size_t>(idx)]._()._( replVariable.GetString(0) );
    for( int i= 1 ; i < replSize; i++ )
    {
        values.insert( values.begin() + idx + i, AString( replVariable.GetString(i) ) );
        qtyValues++;
    }
}

AString&    Variable::Add()
{
    size_t actIdx= static_cast<size_t>(qtyValues);
    qtyValues++;
    if( actIdx < values.size() )
        return values[actIdx].Clear();

    values.insert( values.end(), AString() );
    return values[actIdx];
}



bool        Variable::IsTrue    (int idx) { return  idx < qtyValues ? Config->IsTrue( GetString (idx) )                   : false; }
integer     Variable::GetInteger(int idx) { return  idx < qtyValues ? static_cast<integer>(GetString(idx)->ParseInt())    : 0;     }
double      Variable::GetFloat  (int idx) { return  idx < qtyValues ? GetString(idx)->ParseFloat( Config ? &Config->NumberFormat : &NumberFormat::Global ) : 0.0;   }



// #################################################################################################
// convenience methods using Configuration::Default singleton
// #################################################################################################
int  Variable::Load()
{
    return Configuration::Default.Load( *this );
}

int  Variable::Store( const String& externalizedValue )
{
    return Configuration::Default.Store( *this, externalizedValue );
}

int  Variable::StoreDefault( const String& externalizedValue )
{
    if ( externalizedValue.IsNotNull() )
        Configuration::Default.DefaultValues.StringConverter->LoadFromString( *this, externalizedValue );

    if ( Size() == 0 && DefaultValue.IsNotNull() )
        Configuration::Default.DefaultValues.StringConverter->LoadFromString( *this, DefaultValue );

    Priority= Configuration::PrioDefault;
    return Configuration::Default.Store( *this, NullString );
}

int  Variable::Protect( const String& externalizedValue )
{
    if ( externalizedValue.IsNotNull() )
        Configuration::Default.DefaultValues.StringConverter->LoadFromString( *this, externalizedValue );

    if ( Size() == 0 && DefaultValue.IsNotNull() )
        Configuration::Default.DefaultValues.StringConverter->LoadFromString( *this, DefaultValue );

    Priority= Configuration::PrioProtected;
    return Configuration::Default.Store( *this, NullString );
}

int  Variable::LoadFromString( const String& externalizedValue )
{
    Configuration::Default.DefaultValues.StringConverter->LoadFromString( *this, externalizedValue );
    return Size();
}

bool Variable::GetAttribute( const String& attrName, Substring& result, char attrDelim )
{
    for ( int i= 0; i< Size(); i++ )
    {
        result.Set( GetString(i ) );
        if (    result.ConsumeString ( attrName,  lang::Case::Ignore, lang::Whitespaces::Trim )
             && result.ConsumeChar   ( attrDelim, lang::Case::Ignore, lang::Whitespaces::Trim ) )
        {
            result.Trim();
            return true;
        }
    }
    return false;
}

}}}// namespace aworx::lib::config

