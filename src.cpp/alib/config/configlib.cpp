// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
#include "alib/alib.hpp"

#if !defined (HPP_ALIB_CONFIG_CONFIGURATION)
#   include "alib/config/configuration.hpp"
#endif

#if !defined (HPP_ALIB_LANG_RESOURCE_TUPLE_LOADER)
#   include "alib/lang/resourcedtupleloader.hpp"
#endif

ALIB_LANG_RESOURCED( aworx::lib::config::Priorities, aworx::lib::CONFIG, "Priorities" )
ALIB_LANG_ENUM_META_DATA_RESOURCE_LOADER( aworx::lib::config::Priorities )


//! @cond NO_DOX
// we do not use macro ALIB_ENUM_SPECIFICATION_IMPL( aworx::lib::config::VariableDecl )
// because we need to provide a different delimiter
namespace aworx { namespace lib { namespace lang {
void T_EnumMetaDataSpecification<aworx::lib::config::VariableDecl>::LoadTable(void* t, Library& l,const String& n )
{
    ResourcedTupleLoader::LoadTable( *reinterpret_cast< std::vector<TTuple>*>(t), l, n, '|' );
}
}}}
//! @endcond


using namespace std;
using namespace aworx;
using namespace aworx::lib::config;

#if ALIB_MODULE_STRINGS


#endif // ALIB_MODULE_STRINGS


namespace aworx { namespace lib {

// The singleton of the library class located in namespace aworx::lib.
config::Config CONFIG;

namespace config  {


void Config::init( Phases phase )
{
    if( phase == Phases::resourceset )
    {
        #if ALIB_MODULE_BOXING && ALIB_MODULE_STRINGS
            ALIB_BOXING_DEFINE_IAPPLY_FOR_APPLICABLE_TYPE( config::Exceptions     )
            ALIB_BOXING_DEFINE_IAPPLY_FOR_APPLICABLE_TYPE( aworx::lib::config::Priorities )
        #endif

        Res->AddBulk( ResourceCategory.ToCString(),

        "ExceptionsPrefix" , "config::" ,
        "ExceptionsPostfix", ""         ,
        "Exceptions",
            "0"  ","    "OK"                ","  ""    ","
            "1"  ","    "ErrorOpeningFile"  ","  "EOF" ","
            "2"  ","    "ErrorWritingFile"  ","  "EWF"  ,

         "EOF", "Can't open {}file '{}' for reading." ,
         "EWF", "Can't open {}file '{}' for writing." ,


         "Priorities",
          "0"       ","   "NONE"                   ",1"      ","
          "500"     ","   "AutoDetected"           ",1"      ","
          "10000"   ","   "DefaultValues"          ",1"      ","
          "20000"   ","   "Standard"               ",1"      ","
          "30000"   ","   "Environment"            ",1"      ","
          "40000"   ","   "CLI"                    ",1"      ","
          "-1"      ","   "ProtectedValues"        ",1"       ,


        // names of the configuration plug-ins added to configuration in default construction.
        "CfgPlgDef"  , "Internal Default Variables" ,
        "CfgPlgPro"  , "Protected Variables"        ,
        "CfgPlgEnv"  , "Environment Variables"      ,
        "CfgPlgCLI"  , "Command Line Arguments"     ,

        // end of AddBulk()
        nullptr );


        // load plugin slots resources already now, so that plug-ins may be added to resource
        // object. It will be reloaded in next phase. Hence, a very special treatment here.
        EnumMetaData<Priorities>::GetSingleton()->CheckLoad();
    }

    else if( phase == Phases::resourceload )
    {
        // reloaded plug-in slots resources in case it was changed after static phase
        EnumMetaData<Priorities>::GetSingleton()->Table.clear();
        EnumMetaData<Priorities>::GetSingleton()->Map.clear();
        EnumMetaData<Priorities>::GetSingleton()->CheckLoad();
    }

}

void Config::terminationCleanUp()
{
}


}}}// namespace [aworx::lib::config]




