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
#if !defined (HPP_ALIB_SYSTEM_DIRECTORY)
    #include "alib/system/directory.hpp"
#endif
#if !defined (HPP_ALIB_SYSTEM_PROCESSINFO)
    #include "alib/system/process.hpp"
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
// interface
// #################################################################################################

InMemoryPlugin::~InMemoryPlugin()
{
    for ( Section* section : Sections )
        delete section;
}

void  InMemoryPlugin::Reset()
{
    for ( Section* section : Sections )
        delete section;
    Sections.clear();
    Sections.insert( Sections.end(), createSection( nullptr ) );
}

InMemoryPlugin::Section* InMemoryPlugin::SearchSection( const String& name ) const
{
    if ( name.IsEmpty() )
        return Sections[0];

    auto sIt= find_if( Sections.begin(), Sections.end(),
                       [& name](InMemoryPlugin::Section* section)
                       {
                          return section->Name.Equals( name, Case::Ignore );
                       }
                      );

    return  sIt != Sections.end()   ? *sIt
                                    : nullptr;
}

InMemoryPlugin::Section* InMemoryPlugin::SearchOrCreateSection( const String& name, const String& comments )
{
    Section* s= SearchSection( name );
    if ( s == nullptr )
        Sections.insert( Sections.end(), s= createSection( name ) );

    if ( s->Comments.IsEmpty() )
        s->Comments._( comments );

    return s;
}


// #################################################################################################
// Configuration plug-in interface implementation
// #################################################################################################

bool  InMemoryPlugin::Load( Variable& variable, bool searchOnly ) const
{
    ALIB_ASSERT_WARNING( variable.Name.IsNotEmpty(), "Empty name given" );

    Section*    section;
    Entry*      entry=  nullptr;
    if (    (section= SearchSection     ( variable.Category     ) ) != nullptr
         && (entry=   section->GetEntry ( variable.Name, false  ) ) != nullptr
         && !searchOnly                                                            )
    {
        entry->ToVariable( this, variable );
    }

    return entry != nullptr;
}

bool  InMemoryPlugin::Store( Variable& variable  )
{
    Section*    section=    SearchOrCreateSection( variable.Category, nullptr );
    if ( variable.Size() > 0 )
    {
        Entry* entry= section->GetEntry( variable.Name, true );
        entry->FromVariable( this, variable );
        return true;
    }

    return  section->DeleteEntry( variable.Name );
}


// #################################################################################################
// class InMemoryPlugin::Section
// #################################################################################################
bool InMemoryPlugin::Section::DeleteEntry ( const String& name )
{
    for ( size_t idx= 0; idx < Entries.size(); ++idx )
    {
        Entry* entry= Entries[idx];
        if ( entry->Name.Equals( name, enums::Case::Ignore ) )
        {
            delete Entries[idx];
            Entries.erase( Entries.begin() + idx );
            return true;
        }
    }
    return false;
}

InMemoryPlugin::Entry* InMemoryPlugin::Section::GetEntry( const String& name, bool create )
{
    if ( name.IsEmpty() )
    {
        ALIB_WARNING( "Empty variable name given" );
        return nullptr;
    }

    auto entryIt= find_if( Entries.begin(), Entries.end(),
                             [& name](InMemoryPlugin::Entry* variable)
                             {
                                return  variable->Name.Equals( name, Case::Ignore );
                             }
                         );
    if( entryIt != Entries.end() )
        return *entryIt;

    if ( !create )
        return nullptr;

    // create entry
    Entries.insert( Entries.end(), createEntry( name ) );
    return Entries.back();
}

// #################################################################################################
// class InMemoryPlugin::Entry
// #################################################################################################
void InMemoryPlugin::Entry::ToVariable( const InMemoryPlugin* , Variable& variable )
{
    ALIB_ASSERT( Delim != '\0' || Values.size() <= 1);
    if ( Delim != '\0' )
        variable.Delim= Delim;
    if ( FormatHints != 0 )
        variable.FormatHints= FormatHints;
    if ( FormatAttrAlignment.IsNotEmpty() )
        variable.FormatAttrAlignment= FormatAttrAlignment;

    variable.Comments._()._( Comments );
    for( AString& val : Values )
        variable.AddString( val );
}


void InMemoryPlugin::Entry::FromVariable( const InMemoryPlugin* , Variable& variable )
{
    // copy attributes
    Delim=               variable.Delim;
    FormatHints=         variable.FormatHints;
    FormatAttrAlignment= variable.FormatAttrAlignment;

    if ( Comments.IsEmpty() )    // do not overwrite comments
        Comments._( variable.Comments );

    // adjust size of value array
    int varSize=       variable.Size();
    int valSize= (int) Values.size();
    while (valSize < varSize )
    {
        Values.insert( Values.end(), AString() );
        valSize++;
    }
    if (valSize > varSize )
        Values.erase( Values.begin() + varSize, Values.end() );

    // copy
    for ( int i= 0; i< varSize; i++ )
        Values[i]._()._( variable.GetString( i ) );
}


}}}// namespace aworx::lib::config

