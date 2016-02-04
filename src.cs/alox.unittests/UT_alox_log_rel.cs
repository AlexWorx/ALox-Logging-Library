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

#if ALIB_MONO_DEVELOP
    using NUnit.Framework;
#endif
#if ALIB_VSTUDIO
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
    #if ALIB_MONO_DEVELOP
        [TestFixture ()]
    #endif
    #if ALIB_VSTUDIO
        [TestClass]
    #endif
    public class CS_ALox_Rel   : UnitTest
    {
    /** ********************************************************************************************
     * The loggers. 
     **********************************************************************************************/
    public static Lox                 lox;
    #if ALOX_DBG_LOG || ALOX_REL_LOG
        public static ConsoleLogger       cl;
        public static MemoryLogger        ml;
    #endif  // ALOX_DBG_LOG || ALOX_REL_LOG

    /** ********************************************************************************************
     * Creates loggers. 
     **********************************************************************************************/
    public void   clearCreateAndAddLoggers( bool memoryLogger= false, bool consoleLogger= true)
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            lox= new Lox();
            cl= null;
            ml= null;

            if ( consoleLogger )
            {
                cl= new ConsoleLogger("UNITTESTLOGGER");
                lox.AddLogger( cl );
            }

            if ( memoryLogger )
            {
                ml= new MemoryLogger();
                lox.AddLogger( ml );
            }

            lox.MapThreadName( "UnitTest" );
        #endif  // ALOX_DBG_LOG || ALOX_REL_LOG
    }


    /** ********************************************************************************************
     * Log_TestLogLevelSetting 
     **********************************************************************************************/
    #if ALIB_MONO_DEVELOP
        [Test ()]
    #endif
    #if ALIB_VSTUDIO
        [TestMethod]
        #if !WINDOWS_PHONE
            [TestCategory("CS_ALox")]
        #endif
    #endif
    public void Lox_TestLogLevelSetting()
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            clearCreateAndAddLoggers();
            lox.SetDomain( "TLLS_DF", Log.Scope.Method );
            uint logLinesBefore= cl.CntLogs;
        #endif
        #if ALOX_DBG_LOG
            lox.SetDomain( lox.InternalDomain, Log.DomainLevel.Off );
        #endif

        // Test log level setting
        
        lox.SetDomain( "TLLS_DF", Log.DomainLevel.All );
        lox.Verbose  (         "This Verbose line should be logged" );
        lox.Info     (         "This Info    line should be logged" );
        lox.Warning  (         "This WARN    line should be logged" );
        lox.Error    (         "This Error   line should be logged" );
        lox.Verbose  (         "(Indented) This Verbose line should be logged", 1 );
        lox.Info     (         "(Indented) This Info    line should be logged", 1 );
        lox.Warning  (         "(Indented) This WARN    line should be logged", 1 );
        lox.Error    (         "(Indented) This Error   line should be logged", 1 );

        lox.SetDomain( "TLLS_DF", Log.DomainLevel.InfoWarningsAndErrors );
        lox.Verbose  (         "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.Info     (         "This Info    line should be logged" );
        lox.Warning  (         "This Warning line should be logged" );
        lox.Error    (         "This Error   line should be logged" );
        lox.Verbose  (         "(Indented) This Verbose line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        lox.Info     (         "(Indented) This Info    line should be logged", 1 );
        lox.Warning  (         "(Indented) This Warning line should be logged", 1 );
        lox.Error    (         "(Indented) This Error   line should be logged", 1 );


        lox.SetDomain( "TLLS_DF", Log.DomainLevel.WarningsAndErrors );
        lox.Verbose  (         "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.Info     (         "This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.Warning  (         "This Warning line should be logged" );
        lox.Error    (         "This Error   line should be logged" );
        lox.Verbose  (         "(Indented) This Verbose line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        lox.Info     (         "(Indented) This Info    line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        lox.Warning  (         "(Indented) This Warning line should be logged", 1 );
        lox.Error    (         "(Indented) This Error   line should be logged", 1 );

        lox.SetDomain( "TLLS_DF", Log.DomainLevel.Errors );
        lox.Verbose  (         "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.Info     (         "This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.Warning  (         "This Warning line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.Error    (         "This Error   line should be logged" );
        lox.Verbose  (         "(Indented) This Verbose line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        lox.Info     (         "(Indented) This Info    line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        lox.Warning  (         "(Indented) This Warning line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        lox.Error    (         "(Indented) This Error   line should be logged", 1 );

        lox.SetDomain( "TLLS_DF", Log.DomainLevel.Off );
        lox.Verbose  (         "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.Info     (         "This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.Warning  (         "This Warning line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.Error    (         "This Error   line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.Verbose  (         "(Indented) This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.Info     (         "(Indented) This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.Warning  (         "(Indented) This Warning line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.Error    (         "(Indented) This Error   line should NOT be logged. !!!!!Test Error!!!!!" );

        lox.SetDomain( "TLLS", Log.DomainLevel.All );
        lox.Verbose  ( "TLLS", "This Verbose line should be logged" );
        lox.Info     ( "TLLS", "This Info    line should be logged" );
        lox.Warning  ( "TLLS", "This WARN    line should be logged" );
        lox.Error    ( "TLLS", "This Error   line should be logged" );
        lox.Verbose  ( "TLLS", "(Indented) This Verbose line should be logged", 1 );
        lox.Info     ( "TLLS", "(Indented) This Info    line should be logged", 1 );
        lox.Warning  ( "TLLS", "(Indented) This WARN    line should be logged", 1 );
        lox.Error    ( "TLLS", "(Indented) This Error   line should be logged", 1 );

        lox.SetDomain( "TLLS", Log.DomainLevel.InfoWarningsAndErrors );
        lox.Verbose  ( "TLLS", "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.Info     ( "TLLS", "This Info    line should be logged" );
        lox.Warning  ( "TLLS", "This Warning line should be logged" );
        lox.Error    ( "TLLS", "This Error   line should be logged" );
        lox.Verbose  ( "TLLS", "(Indented) This Verbose line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        lox.Info     ( "TLLS", "(Indented) This Info    line should be logged", 1 );
        lox.Warning  ( "TLLS", "(Indented) This Warning line should be logged", 1 );
        lox.Error    ( "TLLS", "(Indented) This Error   line should be logged", 1 );


        lox.SetDomain( "TLLS", Log.DomainLevel.WarningsAndErrors );
        lox.Verbose  ( "TLLS", "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.Info     ( "TLLS", "This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.Warning  ( "TLLS", "This Warning line should be logged" );
        lox.Error    ( "TLLS", "This Error   line should be logged" );
        lox.Verbose  ( "TLLS", "(Indented) This Verbose line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        lox.Info     ( "TLLS", "(Indented) This Info    line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        lox.Warning  ( "TLLS", "(Indented) This Warning line should be logged", 1 );
        lox.Error    ( "TLLS", "(Indented) This Error   line should be logged", 1 );

        lox.SetDomain( "TLLS", Log.DomainLevel.Errors );
        lox.Verbose  ( "TLLS", "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.Info     ( "TLLS", "This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.Warning  ( "TLLS", "This Warning line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.Error    ( "TLLS", "This Error   line should be logged" );
        lox.Verbose  ( "TLLS", "(Indented) This Verbose line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        lox.Info     ( "TLLS", "(Indented) This Info    line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        lox.Warning  ( "TLLS", "(Indented) This Warning line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        lox.Error    ( "TLLS", "(Indented) This Error   line should be logged", 1 );

        lox.SetDomain( "TLLS", Log.DomainLevel.Off );
        lox.Verbose  ( "TLLS", "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.Info     ( "TLLS", "This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.Warning  ( "TLLS", "This Warning line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.Error    ( "TLLS", "This Error   line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.Verbose  ( "TLLS", "(Indented) This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.Info     ( "TLLS", "(Indented) This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.Warning  ( "TLLS", "(Indented) This Warning line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.Error    ( "TLLS", "(Indented) This Error   line should NOT be logged. !!!!!Test Error!!!!!" );

        #if ALOX_DBG_LOG
            UT_EQ ( (uint) 40, cl.CntLogs - logLinesBefore );
        #elif ALOX_REL_LOG
            UT_EQ ( (uint)  0, cl.CntLogs - logLinesBefore );
        #endif
    }


    } // class
} // namespace
