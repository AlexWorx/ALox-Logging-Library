// #################################################################################################
//  cs.aworx.lox.unittests - ALox Logging Library
//
//  Copyright 2013-2018 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
using System;
using System.Threading;
using System.Xml.Linq;
using ut_cs_aworx;

#if ALIB_NUNIT
    using NUnit.Framework;
#endif
#if ALIB_IDE_VSTUDIO
    using Microsoft.VisualStudio.TestTools.UnitTesting;
#endif

using cs.aworx.lib;
//! [DOC_SAMPLES_ALOX_ESC_USING]
using cs.aworx.lox;
//! [DOC_SAMPLES_ALOX_ESC_USING]
using cs.aworx.lox.loggers;
using cs.aworx.lox.tools;
using System.Collections.Generic;

#if !WINDOWS_PHONE
    using cs.aworx.lox.tools.json;
#endif

namespace ut_cs_aworx_lox
{
    #if ALIB_NUNIT
        [TestFixture ()]
    #endif
    #if ALIB_IDE_VSTUDIO
        [TestClass]
    #endif
    public class CS_ALox_Documentation_Samples   : AWorxUnitTesting
    {
        // used with unit test Log_ScopeInfoCacheTest
        public static void ScopeInfoCacheTest() { Log.Info("Test method of CS_ALox_Documentation_Samples"); }



/** ********************************************************************************************
 * class ESC (see also using statement above)
 **********************************************************************************************/
void docSampleESC()
{
//! [DOC_SAMPLES_ALOX_ESC]
Log.Info( "The result is: ", ESC.RED, 42 );
//! [DOC_SAMPLES_ALOX_ESC]
}



    /** ********************************************************************************************
     * Log_JSON
     **********************************************************************************************/
    #if !WINDOWS_PHONE
        #if ALIB_NUNIT
            [Test ()]
        #endif
        #if ALIB_IDE_VSTUDIO
            [TestMethod]
            #if !WINDOWS_PHONE
                [TestCategory("CS_ALox_Documentation_Samples")]
            #endif
        #endif

        public void UT_Doc_Samples()
        {
            UT_INIT();

            docSampleESC();
        }
    #endif
    } // class
} // namespace
