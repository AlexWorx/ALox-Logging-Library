// #################################################################################################
//  Unit Tests - ALox Logging Library
//  (Unit Tests to create tutorial sample code and output)
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
#include "alib/stdafx_alib.h"

#include "alox/alox.hpp"



using namespace std;
using namespace aworx;


namespace ut_alox
{

#if defined (ALOX_DBG_LOG)

    void Log_ScopeDomains_Helper2()
    {
        Log_SetDomain( "H2FILE",     Scope::Filename  )
        Log_SetDomain( "H2METHOD",   Scope::Method      )
        Log_Info("");
    }

#endif

#if defined (ALOX_REL_LOG)

    void Lox_ScopeDomains_Helper2( Lox& lox )
    {
        #define LOX_LOX lox
        Lox_SetDomain( "H2FILE",     Scope::Filename  )
        Lox_SetDomain( "H2METHOD",   Scope::Method      )
        Lox_Info("");
        #undef LOX_LOX
    }

#endif

} // namespace


