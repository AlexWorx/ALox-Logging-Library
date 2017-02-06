// #################################################################################################
//  cs.aworx.lox.unittests - ALox Logging Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
using System;
using System.Threading;
using System.Xml.Linq;
using cs.aworx.lox.core.textlogger;
using cs.aworx.lib.strings;
using ut_cs_aworx;

#if ALIB_NUNIT
    using NUnit.Framework;
#endif
#if ALIB_IDE_VSTUDIO
    using Microsoft.VisualStudio.TestTools.UnitTesting;
#endif

using cs.aworx.lib;
using cs.aworx.lox;
using cs.aworx.lox.core;
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
    public class CS_ALox_release   : AWorxUnitTesting
    {
        // used with unit test Log_ScopeInfoCacheTest
        public static void ScopeInfoCacheTest() { Log.Info("Test method of CS_ALox_release"); }

    /** ********************************************************************************************
     * Lox_LogLevelSetting
     **********************************************************************************************/
    #if ALIB_NUNIT
        [Test ()]
    #endif
    #if ALIB_IDE_VSTUDIO
        [TestMethod]
        #if !WINDOWS_PHONE
            [TestCategory("CS_ALox")]
        #endif
    #endif
    public void Lox_LogLevelSetting()
    {
        UT_INIT();
        Lox lox= new Lox( "ReleaseLox" );
        TextLogger logger= Lox.CreateConsoleLogger( null );
        lox.SetDomain( "TLLS_DF", Scope.Method );
        int logLinesBefore= logger.CntLogs;

        // Test Verbosity setting

        lox.SetVerbosity( logger, Verbosity.Verbose, "" );
        lox.Verbose  (         "This Verbose line should be logged" );
        lox.Info     (         "This Info    line should be logged" );
        lox.Warning  (         "This WARN    line should be logged" );
        lox.Error    (         "This Error   line should be logged" );

        lox.SetVerbosity( logger, Verbosity.Info, "" );
        lox.Verbose  (         "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.Info     (         "This Info    line should be logged" );
        lox.Warning  (         "This Warning line should be logged" );
        lox.Error    (         "This Error   line should be logged" );

        lox.SetVerbosity( logger, Verbosity.Warning, "" );
        lox.Verbose  (         "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.Info     (         "This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.Warning  (         "This Warning line should be logged" );
        lox.Error    (         "This Error   line should be logged" );

        lox.SetVerbosity( logger, Verbosity.Error, "" );
        lox.Verbose  (         "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.Info     (         "This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.Warning  (         "This Warning line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.Error    (         "This Error   line should be logged" );

        lox.SetVerbosity( logger, Verbosity.Off, "" );
        lox.Verbose  (         "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.Info     (         "This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.Warning  (         "This Warning line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.Error    (         "This Error   line should NOT be logged. !!!!!Test Error!!!!!" );

        lox.SetVerbosity( logger, Verbosity.Verbose, "/TLLS" );
        lox.Verbose  ( "/TLLS", "This Verbose line should be logged" );
        lox.Info     ( "/TLLS", "This Info    line should be logged" );
        lox.Warning  ( "/TLLS", "This WARN    line should be logged" );
        lox.Error    ( "/TLLS", "This Error   line should be logged" );

        lox.SetVerbosity( logger, Verbosity.Info, "/TLLS" );
        lox.Verbose  ( "/TLLS", "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.Info     ( "/TLLS", "This Info    line should be logged" );
        lox.Warning  ( "/TLLS", "This Warning line should be logged" );
        lox.Error    ( "/TLLS", "This Error   line should be logged" );


        lox.SetVerbosity( logger, Verbosity.Warning, "/TLLS" );
        lox.Verbose  ( "/TLLS", "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.Info     ( "/TLLS", "This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.Warning  ( "/TLLS", "This Warning line should be logged" );
        lox.Error    ( "/TLLS", "This Error   line should be logged" );

        lox.SetVerbosity( logger, Verbosity.Error, "/TLLS" );
        lox.Verbose  ( "/TLLS", "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.Info     ( "/TLLS", "This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.Warning  ( "/TLLS", "This Warning line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.Error    ( "/TLLS", "This Error   line should be logged" );

        lox.SetVerbosity( logger, Verbosity.Off, "/TLLS" );
        lox.Verbose  ( "/TLLS", "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.Info     ( "/TLLS", "This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.Warning  ( "/TLLS", "This Warning line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.Error    ( "/TLLS", "This Error   line should NOT be logged. !!!!!Test Error!!!!!" );

        UT_EQ ( (uint) 20, logger.CntLogs - logLinesBefore );

        lox.RemoveLogger( logger );
    }


    } // class
} // namespace
