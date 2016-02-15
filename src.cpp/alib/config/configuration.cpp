// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
#include "alib/stdafx_alib.h"
#include "alib/config/configuration.hpp"

#include <algorithm>

using namespace std;

namespace aworx {
namespace           lib {
namespace                   config {


Configuration::Configuration( Inclusion environment, int argc, void **argv, bool wArgs )
{
    // set default true values
    TrueValues.emplace_back( "1"    );
    TrueValues.emplace_back( "true" );
    TrueValues.emplace_back( "yes"  );
    TrueValues.emplace_back( "ok"   );

    // create command line plug-in
    cmdLineCP=  nullptr;
    if ( argc != 0 && argv != nullptr )
    {
        cmdLineCP= new CommandLinePlugIn ( argc, argv, wArgs );
        InsertPlugin( cmdLineCP, 10 );
    }

    // environment config plug-in
    envCP=  nullptr;
    if ( environment == Inclusion::Include )
    {
        envCP= new EnvironmentPlugIn();
        InsertPlugin( envCP,    20 );
    }
}

Configuration::~Configuration()
{
    for ( auto& pairPrioPlug : plugins )
        delete pairPrioPlug.second;
}

void Configuration::InsertPlugin( ConfigurationPlugIn* plugin, int priority )
{
    OWN(*this);

    plugins.insert(
         std::find_if(  plugins.begin(),  plugins.end(),
                        [priority]( PrioAndPlugin& pairPrioPlug)
                        {
                            ALIB_ASSERT_ERROR( pairPrioPlug.first != priority,
                                "Configuration::InsertPlugin(): Plug-in with same priority exists" );

                            return pairPrioPlug.first >= priority;
                        }
                     ),

        std::pair<int, ConfigurationPlugIn*>(priority, plugin)
   );

   plugin->Parent= this;
}

bool Configuration::RemovePlugin( ConfigurationPlugIn* plugin )
{
    OWN(*this);

    size_t qty= plugins.size();
    plugins.erase( std::remove_if( plugins.begin(), plugins.end(),
                                   [plugin](PrioAndPlugin& pair)   { return pair.second == plugin; } ),
                   plugins.end() );

    ALIB_ASSERT_WARNING( plugins.size() != qty, "Configuration::RemovePlugin(): No Plug-in was removed " )

    plugin->Parent= nullptr;
    return  plugins.size() < qty;
}


int  Configuration::Get( const String& category, const String& name, AString& target )
{
    OWN(*this);

    target.Clear();

    if ( !name.IsEmpty() )
        for ( auto& pairPrioPlug : plugins )
            if ( pairPrioPlug.second->Get( category, name, target ) )
                return pairPrioPlug.first;

    return 0;
}

int  Configuration::Get( const String& category, const String& name, int32_t& target )
{
    OWN(*this);

    target= 0;

    if ( !name.IsEmpty() )
        for ( auto& pairPrioPlug : plugins )
            if ( pairPrioPlug.second->Get( category, name, target ) )
                return pairPrioPlug.first;

    return 0;
}


int  Configuration::Get( const String& category, const String& name, double& target )
{
    OWN(*this);

    target= 0.0;

    if ( !name.IsEmpty() )
        for ( auto& pairPrioPlug : plugins )
            if ( pairPrioPlug.second->Get( category, name, target ) )
                return pairPrioPlug.first;

    return 0;
}

bool Configuration::IsTrue( const String& category, const String& name, int* pluginPriority )
{
    OWN(*this);

    String64 value;
    int  localIntDummy;
    if ( pluginPriority == nullptr )
        pluginPriority= &localIntDummy;


    if( (*pluginPriority= Get( category, name, value )) != 0 )
    {
        for ( auto& it : TrueValues )
            if ( value.Equals( it, Case::Ignore ) )
                return true;
    }

    return false;
}

int Configuration::Save( const String& category, const String& name, const String& value,
                         const String& comments,  char        delim )
{
    OWN(*this);

    if ( !name.IsEmpty() )
        for ( auto& pairPrioPlug : plugins )
            if ( pairPrioPlug.second->Save( category, name, value, comments, delim ) )
                return pairPrioPlug.first;
    return 0;
}


int Configuration::Save( const String& category, const String& name, int value,
                         const String& comments )
{
    OWN(*this);

    if ( !name.IsEmpty() )
        for ( auto& pairPrioPlug : plugins )
            if ( pairPrioPlug.second->Save( category, name, value, comments ) )
                return pairPrioPlug.first;
    return 0;
}

int Configuration::Save( const String& category, const String& name, double value,
                         const String& comments )
{
    OWN(*this);

    if ( !name.IsEmpty() )
        for ( auto& pairPrioPlug : plugins )
            if ( pairPrioPlug.second->Save( category, name, value, comments ) )
                return pairPrioPlug.first;
    return 0;
}


}}}// namespace aworx::lib::config

