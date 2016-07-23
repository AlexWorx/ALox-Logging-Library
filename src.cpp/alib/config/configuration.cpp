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

#include <algorithm>

using namespace std;

namespace aworx {
namespace           lib {
namespace                   config {


// #################################################################################################
// Configuration
// #################################################################################################

Configuration::Configuration()
: ThreadLock()
{
    // set default true values
    TrueValues.emplace_back( "1"    );
    TrueValues.emplace_back( "true" );
    TrueValues.emplace_back( "t"    );
    TrueValues.emplace_back( "yes"  );
    TrueValues.emplace_back( "y"    );
    TrueValues.emplace_back( "on"   );
    TrueValues.emplace_back( "ok"   );

    insertPlugin( &DefaultValues  , Configuration::PrioDefault        );
    insertPlugin( &Environment    , Configuration::PrioEnvironment    );
    insertPlugin( &CmdLine        , Configuration::PrioCmdLine        );
    insertPlugin( &ProtectedValues, Configuration::PrioProtected      );
}


void Configuration::insertPlugin( ConfigurationPlugin* plugin, int priority )
{
    plugins.insert(
         std::find_if(  plugins.begin(),  plugins.end(),
                        [priority]( PluginAndPrio& ppp)
                        {
                            ALIB_ASSERT_ERROR( ppp.first != priority,
                                "Configuration::InsertPlugin(): Plug-in with same priority exists" );

                            return ppp.first < priority;
                        }
                     ),

        std::pair<int, ConfigurationPlugin*>(priority, plugin)
   );
}

bool Configuration::RemovePlugin( ConfigurationPlugin* plugin )
{
    OWN(*this);

    size_t qty= plugins.size();
    plugins.erase( std::remove_if( plugins.begin(), plugins.end(),
                                   [plugin](PluginAndPrio& pair)   { return pair.second == plugin; } ),
                   plugins.end() );

    ALIB_ASSERT_WARNING( plugins.size() != qty, "Configuration::RemovePlugin(): No Plug-in was removed " )

    return  plugins.size() < qty;
}

int Configuration::FetchFromDefault( ConfigurationPlugin& dest )
{
    OWN(*this);

    int cntCopied= 0;
    Variable variable;
    for( size_t sNo= 0; sNo < DefaultValues.Sections.size() ; sNo++ )
    {
        InMemoryPlugin::Section* section= DefaultValues.Sections[sNo];
        for( size_t vNo= 0; vNo < section->Entries.size() ; vNo++ )
        {
            InMemoryPlugin::Entry* entry= section->Entries[vNo];
            if( !dest.Load( variable.Define( section->Name, entry->Name ), true ) )
            {
                DefaultValues.Load  ( variable );
                dest.Store( variable );
                cntCopied++;
            }
        }
    }

    return  cntCopied;
}

bool Configuration::IsTrue( const String& value )
{
    for ( auto& it : TrueValues )
        if ( value.Equals( it, Case::Ignore ) )
            return true;

    return false;
}



// #############################################################################################
// Load/Store
// #############################################################################################
int Configuration::Load( Variable& variable )
{
    OWN(*this);

    variable.Config=    this;
    variable.Priority=  loadImpl( variable, true );

    if ( variable.Priority == 0 && variable.DefaultValue.IsNotNull() )
        Store( variable, variable.DefaultValue );

    return variable.Priority;
}

int Configuration::Store( Variable& variable, const String& externalizedValue )
{
    OWN(*this);

    // checks
    if( externalizedValue.IsNull() )
    {
        if ( variable.Name.IsEmpty())
        {
            ALIB_ERROR( "Trying to store an undefined variable."  );
            return 0;
        }

        if ( variable.Size() > 1 && variable.Delim == '\0' )
        {
            ALIB_ERROR_S512(    "Trying to store variable \"" << variable.Fullname
                             << "\" which has multiple values set but no delimiter defined."  );
            return 0;
        }
    }

    // store us as config
    variable.Config= this;

    // detect?
    bool detected= variable.Priority < 0;
    if ( detected )
    {
        variable.Priority= 0;
        for ( auto& ppp : plugins )
            if ( ppp.second->Load( variable, true ) )
            {
                variable.Priority= ppp.first;
                break;
            }
    }

    // new variables go to default
    if ( variable.Priority == 0 )
        variable.Priority= Configuration::PrioDefault;

    // we do not store if detected priority is protected
    else if( detected && variable.Priority == Configuration::PrioProtected )
        return (variable.Priority= 0);

    // store
    for ( auto& ppp : plugins )
        if (    ppp.first <= variable.Priority
             && ppp.second->Store( variable, externalizedValue ) )
            {
                return (variable.Priority= ppp.first);
            }

    return (variable.Priority= 0);
}




// #############################################################################################
// internals
// #############################################################################################

int  Configuration::loadImpl( Variable& variable, bool substitute )
{
    variable.ClearValues();
    if ( variable.Name.IsEmpty() )
    {
        ALIB_WARNING( "Empty variable name given" );
        return 0;
    }

    // search variable
    int priority= 0;
    for ( auto& ppp : plugins )
        if ( ppp.second->Load( variable ) )
        {
            priority= ppp.first;
            break;
        }

    // not found?
    if ( !substitute || priority == 0 )
        return 0;

    // substitution in all values of variable
    for ( int valueNo= 0; valueNo < variable.Size(); valueNo++ )
    {
        int searchStartIdx=  0;
        int maxReplacements = 50;
        do
        {
            AString& value= *variable.GetString( valueNo );

            // search start
            int repStart= value.IndexOf( SubstitutionVariableStart, searchStartIdx );
            if ( repStart < 0 )
                break;
            searchStartIdx= repStart;
            int varStart= repStart + SubstitutionVariableStart.Length();

            Variable replVar;
            int repLen;
            int varLen;

            // search end in two different ways depending on setting of public field "SubstitutionVariableEnd"
            if ( SubstitutionVariableEnd.IsEmpty() )
            {
                int idx=   value.IndexOfAny( SubstitutionVariableDelimiters, Inclusion::Include, varStart );
                if ( idx < 0 )
                    idx= value.Length();

                varLen= idx - varStart;
                repLen= idx - repStart;
            }
            else
            {
                int idx=   value.IndexOf   ( SubstitutionVariableEnd, varStart );
                if (idx < 0 )
                {
                    ALIB_WARNING_S512(     "End of substitution variable not found (while start was found). Variable name: "
                                        << variable.Fullname
                                        << " Value: \"" << variable.GetString() << "\"." );
                    break;
                }

                varLen= idx - varStart;
                repLen= idx + SubstitutionVariableEnd.Length() - repStart;
            }

            // get variable name string
            Substring    replVarCategory;
            Substring    replVarName( value, varStart, varLen );
            if ( replVarName.IsEmpty() )
            {
                searchStartIdx+=   SubstitutionVariableStart.Length()
                                 + SubstitutionVariableEnd.Length();
                continue;
            }

            // parse category from name
            int catSeparatorIdx= replVarName.IndexOf( '_' );
            if (catSeparatorIdx >= 0 )
            {
                replVarCategory.Set( replVarName, 0                   , catSeparatorIdx );
                replVarName    .Set( replVarName, catSeparatorIdx + 1);
            }

            // load replacement variable
            if ( replVarName.IsNotEmpty() )
            {
                replVar.Define( replVarCategory, replVarName, variable.Delim );
                loadImpl( replVar, false );
            }
            else
                replVar.ClearValues();

            // do the replacement (even if no variable was found)
            if ( replVar.Size() == 1 )
                value.ReplaceSubstring( replVar.GetString(), repStart, repLen );

            else if ( replVar.Size() > 1 )
            {
                variable.ReplaceValue( valueNo, replVar );

                // repeat replacements in current value, as current value changed
                valueNo--;
                break;
            }

            else
                value.ReplaceSubstring( "",                 repStart, repLen );

        }
        while( --maxReplacements );

        // warn if max replacements
        if( maxReplacements <= 0 )
            ALIB_WARNING_S512(     "Too many substitutions in variable " << variable.Fullname
                                << ". Probably a recursive variable definition was made. ");
    }
    return priority;
}




}}}// namespace aworx::lib::config

