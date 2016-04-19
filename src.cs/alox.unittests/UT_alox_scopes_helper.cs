// #################################################################################################
//  cs.aworx.lox.unittests - ALox Logging Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
using System;
using System.Threading;
using System.Xml.Linq;
using cs.aworx.lox.core.textlogger;
using cs.aworx.lib.strings;
using ut_cs_aworx;

using cs.aworx.lib;
using cs.aworx.lox;

#if !WINDOWS_PHONE
    using cs.aworx.lox.tools.json;
#endif

namespace ut_cs_aworx_lox
{
    public class CS_ALox_domains_helper
    {
        // used with unit test Log_ScopeInfoCacheTest
        public static void ScopeInfoCacheTest() { Log.Info("Test method of CS_ALox_domains_helper"); }

        public static void help()
        {
            Log.SetDomain( "HFILE",       Scope.Filename  );
            Log.SetDomain( "HMETHOD",     Scope.Method      );
            Log.Info("");
        }
    }
} 
