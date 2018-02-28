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
using cs.aworx.lib.lang;
using cs.aworx.lib.strings;
using cs.aworx.lox.core.textlogger;
using System.IO;
using cs.aworx.lib.config;

#if ALIB_NUNIT
    using NUnit.Framework;
#endif
#if ALIB_IDE_VSTUDIO
    using Microsoft.VisualStudio.TestTools.UnitTesting;
#endif

using cs.aworx.lib;
using cs.aworx.lox;
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
    public class CS_ALox_Lox   : AWorxUnitTesting
    {
        // used with unit test Log_ScopeInfoCacheTest
        public static void ScopeInfoCacheTest() { Log.Info("Test method of CS_ALox_Lox"); }

    /** ********************************************************************************************
     * Lox_AddLogger.
     **********************************************************************************************/
    #if ALOX_DBG_LOG
    #if ALIB_NUNIT
        [Test ()]
    #endif
    #if ALIB_IDE_VSTUDIO
        [TestMethod]
        #if !WINDOWS_PHONE
            [TestCategory("CS_ALox")]
        #endif
    #endif
    public void Lox_AddLogger()
    {
        UT_INIT();

        // twice
        {
            ConsoleLogger con=      new ConsoleLogger();
            Log.SetVerbosity( con,      Verbosity.Verbose, ALox.InternalDomains );

            MemoryLogger checkCnt=  new MemoryLogger( "CHECK");
            Log.SetVerbosity( checkCnt, Verbosity.Warning, ALox.InternalDomains );

            MemoryLogger mem1= new MemoryLogger( "MEM" );
            MemoryLogger mem2= new MemoryLogger( "MEM" );

            int checkVal= 0;
            Log.SetVerbosity( mem1,     Verbosity.Info ); UT_EQ( checkVal+= 0, checkCnt.CntLogs );
            Log.SetVerbosity( mem2,     Verbosity.Info ); UT_EQ( checkVal+= 1, checkCnt.CntLogs );
            Log.SetVerbosity( "XYZ",    Verbosity.Info ); UT_EQ( checkVal+= 1, checkCnt.CntLogs );

            // get unknown
            Log.GetLogger( "XYZ" );                       UT_EQ( checkVal+= 1, checkCnt.CntLogs );


            Log.RemoveLogger( mem2     );                 UT_EQ( checkVal+= 1, checkCnt.CntLogs );
            Log.RemoveLogger( mem1     );                 UT_EQ( checkVal+= 0, checkCnt.CntLogs );
            Log.RemoveLogger( mem1     );                 UT_EQ( checkVal+= 1, checkCnt.CntLogs );
            Log.RemoveLogger( "XYZ"    );                 UT_EQ( checkVal+= 1, checkCnt.CntLogs );
            Log.RemoveLogger( con      );                 UT_EQ( checkVal+= 0, checkCnt.CntLogs );
            Log.RemoveLogger( con      );                 UT_EQ( checkVal+= 1, checkCnt.CntLogs );
            Log.RemoveLogger( checkCnt );                 UT_EQ( checkVal+= 0, checkCnt.CntLogs );
        }

        // one logger in two loxes
        {
            Log.AddDebugLogger();
            Lox lox= new Lox( "ReleaseLox" );

            UT_TRUE( Log.DebugLogger.GetSafeness() == Safeness.Unsafe );

            lox.SetVerbosity( Log.DebugLogger , Verbosity.Verbose );

            UT_TRUE( Log.DebugLogger.GetSafeness() == Safeness.Safe );

            lox.RemoveLogger( Log.DebugLogger );

            UT_TRUE( Log.DebugLogger.GetSafeness() == Safeness.Unsafe );

            Log.RemoveDebugLogger();
        }
    }
    #endif

    /** ********************************************************************************************
     * Log_SetSourcePathTrimRule.
     **********************************************************************************************/
    void check_MemLogStartsWith( String exp, MemoryLogger memlog, bool doLog= true )
    {
        if( doLog )
            Log.Info("");

        if( Path.DirectorySeparatorChar == '\\' )
            exp= exp.Replace( '/', '\\' );

        UT_TRUE( memlog.MemoryLog.StartsWith( exp, Case.Ignore ) );


        memlog.MemoryLog.Clear();
    }

    #if ALOX_DBG_LOG
    #if ALIB_NUNIT
        [Test ()]
    #endif
    #if ALIB_IDE_VSTUDIO
        [TestMethod]
        #if !WINDOWS_PHONE
            [TestCategory("CS_ALox")]
        #endif
    #endif
    public void Log_SetSourcePathTrimRule()
    {
        UT_INIT();

        Log.AddDebugLogger();

        MemoryLogger memLogger= new MemoryLogger();
        memLogger.MetaInfo.Format._()._( "%Sp@" );
        Log.SetVerbosity( memLogger, Verbosity.Verbose );

        Log.ClearSourcePathTrimRules( Reach.Global, false);

        if( Path.DirectorySeparatorChar == '/' )
            check_MemLogStartsWith( "/home"               , memLogger );
        else
        {
            Log.Info( "");
            UT_TRUE( memLogger.MemoryLog.CharAt(1) == ':' );
            memLogger.MemoryLog._();
        }

        Log.SetSourcePathTrimRule( "*"         , Inclusion.Include     );  // illegal rule, not stored (debug into)
        Log.SetSourcePathTrimRule( "**"        , Inclusion.Include     );  // illegal rule, not stored (debug into)
        Log.SetSourcePathTrimRule( "*/src.cs/" , Inclusion.Include     );  check_MemLogStartsWith( "alox.unittests@"     , memLogger );
        Log.SetSourcePathTrimRule( "*"         , Inclusion.Include     );  // illegal rule, not stored (debug into)
        Log.SetSourcePathTrimRule( "**"        , Inclusion.Include     );  // illegal rule, not stored (debug into)
        Log.ClearSourcePathTrimRules( Reach.Global, false);
        Log.SetSourcePathTrimRule( "*/src.cs/" , Inclusion.Include, -3 );  check_MemLogStartsWith( "cs/alox.unittests@"  , memLogger );
        Log.ClearSourcePathTrimRules( Reach.Global, false);
        Log.SetSourcePathTrimRule( "*/src.cs/" , Inclusion.Include, 2  );  check_MemLogStartsWith( "ox.unittests@"       , memLogger );

        Log.ClearSourcePathTrimRules( Reach.Global, false);
        Log.SetSourcePathTrimRule( "*/src.cs/" , Inclusion.Exclude     );  check_MemLogStartsWith( "/src.cs"             , memLogger );

        Log.ClearSourcePathTrimRules( Reach.Global, false);
        Log.SetSourcePathTrimRule( "*/src.cs/" , Inclusion.Exclude, -3 );  check_MemLogStartsWith( "lox/src.cs"          , memLogger );

        Log.ClearSourcePathTrimRules( Reach.Global, false);
        Log.SetSourcePathTrimRule( "*/src.cs/*", Inclusion.Exclude, -3 );  check_MemLogStartsWith( "lox/src.cs"          , memLogger );

        // clear only local rule. (the above rule was global)
        Log.ClearSourcePathTrimRules( Reach.Local, false );
                                                                            check_MemLogStartsWith( "lox/src.cs"         , memLogger );

        // set local rules
        Log.ClearSourcePathTrimRules( Reach.Global, false);
        Log.SetSourcePathTrimRule( "*/src.cs/" , Inclusion.Exclude, 0, Case.Ignore, Reach.Local );  check_MemLogStartsWith( "/src.cs"         , memLogger );

        Log.ClearSourcePathTrimRules( Reach.Global, false);
        Log.SetSourcePathTrimRule( "*/src.cs/" , Inclusion.Exclude, 0, Case.Ignore, Reach.Local );  check_MemLogStartsWith( "/src.cs"         , memLogger );

        // check non ignore case
        Log.ClearSourcePathTrimRules( Reach.Global, false);
        Log.SetSourcePathTrimRule( "*/src.cs/" , Inclusion.Exclude, 0, Case.Ignore, Reach.Local );   check_MemLogStartsWith( "/src.cs"         , memLogger );

        Log.ClearSourcePathTrimRules( Reach.Global, false);
        Log.SetSourcePathTrimRule( "*/SRC.CS/" , Inclusion.Exclude, 0, Case.Sensitive, Reach.Local );
        if( Path.DirectorySeparatorChar == '/' )
             check_MemLogStartsWith( "/home"               , memLogger );
        else
        {
            Log.Info( "");
            UT_TRUE( memLogger.MemoryLog.CharAt(1) == ':' );
        }

        Log.RemoveDebugLogger();
        Log.RemoveLogger( memLogger );
    }
    #endif

    /** ********************************************************************************************
     * Log_SetSourcePathTrimRuleExternal
     **********************************************************************************************/
    #if ALOX_DBG_LOG
    #if ALIB_NUNIT
        [Test ()]
    #endif
    #if ALIB_IDE_VSTUDIO
        [TestMethod]
        #if !WINDOWS_PHONE
            [TestCategory("CS_ALox")]
        #endif
    #endif
    public void Log_SetSourcePathTrimRuleExternal()
    {
        UT_INIT();

        // for the unit tests to reset, we need an extra lox to be able to clear the global rules
        // beforewe initialize our main lox
        Lox clearLox= new Lox("ClearingRules");

        // global rule
        clearLox.ClearSourcePathTrimRules( Reach.Global, false);
        {
            // create iniFile
            String iniFileContents=
                 "[ALOX]\n"
                +"TESTML_FORMAT= \"%Sp\"  \n"

                +"GLOBAL_SOURCE_PATH_TRIM_RULES=  *src.cs/   , true  ;     \\   \n"
                             +"    /usr/local/lib/  , false, 9, true, /usr/lib/"
                +"\n"
               ;
/* SNIPPIT FOR Dox
//! [Man_SourcePathTrimming]
[ALOX]
GLOBAL_SOURCE_PATH_TRIM_RULES= *src.cs/                  , true                ; \
                               /usr/local/lib/  , false, 9, true, /usr/lib/
//! [Man_SourcePathTrimming]
*/
            String fileName= System.Environment.CurrentDirectory + "/Log_ConfigTrimRules.ini";
            StreamWriter file= new StreamWriter( fileName );
            file.Write( iniFileContents );
            file.Close();

            IniFile iniFile= new IniFile( fileName );
            iniFile.ReadFile();
            //iniFile.WriteFile(); // temporarily enable to see what we have written above

            ALox.Config.InsertPlugin( iniFile, Configuration.PrioStandard );

            // test
            Lox lox= new Lox("T_LOX", false );

            lox.SetVerbosity( Lox.CreateConsoleLogger("CONSOLE") , Verbosity.Verbose );
            lox.SetVerbosity( "CONSOLE"                          , Verbosity.Verbose, ALox.InternalDomains );

            MemoryLogger ml= new MemoryLogger("TESTML");

            lox.SetVerbosity(ml, Verbosity.Verbose );

            lox.Info( "" );  UT_EQ("alox.unittests", ml.MemoryLog ); ml.MemoryLog._(); ml.AutoSizes.Reset();

            ALox.Config.RemovePlugin( iniFile );
            lox.RemoveLogger( ml );
            lox.RemoveLogger( "CONSOLE" );
        }

        // local rule
        clearLox.ClearSourcePathTrimRules( Reach.Global, false);
        ALox.Config.GetPluginTypeSafe<InMemoryPlugin>( Configuration.PrioDefaultValues   ).Reset();
        {
            // store default values
            Variable var= new Variable();
            ALox.Config.Store( var.Declare( ALox.ConfigCategory, "TESTML_FORMAT" ), "%Sp" );
            ALox.Config.Store( var.Declare( ALox.ConfigCategory, "T_LOX_SOURCE_PATH_TRIM_RULES",';'),
                    "*;**; *alox.u*, include ;*;**" // default values, 0, ignore"
                                                    // the * will be removed
                                                    // two illegal rules before and after
                                 );

            // test
            Lox lox= new Lox("T_LOX", false );

            lox.SetVerbosity( Lox.CreateConsoleLogger("CONSOLE") , Verbosity.Verbose );
            lox.SetVerbosity( "CONSOLE"                          , Verbosity.Verbose, ALox.InternalDomains );

            MemoryLogger ml= new MemoryLogger("TESTML");

            lox.SetVerbosity(ml, Verbosity.Verbose );

            lox.Info( "" ); UT_EQ( "nittests"  , ml.MemoryLog ); ml.MemoryLog._(); ml.AutoSizes.Reset();

            lox.RemoveLogger( ml );
            lox.RemoveLogger( "CONSOLE" );
        }

        clearLox.ClearSourcePathTrimRules( Reach.Global, false);
        ALox.Config.GetPluginTypeSafe<InMemoryPlugin>( Configuration.PrioDefaultValues   ).Reset();
        {
            // create iniFile
            IniFile iniFile= new IniFile("*"); // don't read
            Variable var= new Variable();
            iniFile.Store( var.Declare( ALox.ConfigCategory, "TESTML_FORMAT" ),  "%Sp" );
            iniFile.Store( var.Declare( ALox.ConfigCategory, "T_LOX_SOURCE_PATH_TRIM_RULES",';'),
                           "*alox.u, excl, 2, sens" );

            ALox.Config.InsertPlugin( iniFile, Configuration.PrioStandard );


            // test
            Lox lox= new Lox("T_LOX", false );

            lox.SetVerbosity( Lox.CreateConsoleLogger("CONSOLE") , Verbosity.Verbose );
            lox.SetVerbosity( "CONSOLE"                          , Verbosity.Verbose, ALox.InternalDomains );

            MemoryLogger ml= new MemoryLogger("TESTML");

            lox.SetVerbosity(ml, Verbosity.Verbose );

            lox.Info( "" ); UT_EQ( "ox.unittests"  , ml.MemoryLog ); ml.MemoryLog._(); ml.AutoSizes.Reset();

            // overwrite with source priority
            lox.SetSourcePathTrimRule( "*alox.u", Inclusion.Exclude, 0, Case.Ignore, "REPLACE_1/", Reach.Local );
            lox.Info( "" ); UT_EQ( "ox.unittests"  , ml.MemoryLog ); ml.MemoryLog._(); ml.AutoSizes.Reset();
            lox.SetSourcePathTrimRule( "*alox.u", Inclusion.Exclude, 0, Case.Ignore, "REPLACE_2/", Reach.Local, Configuration.PrioProtectedValues );
            lox.Info( "" ); UT_TRUE( ml.MemoryLog.StartsWith( "REPLACE_2/" ) ); ml.MemoryLog._(); ml.AutoSizes.Reset();

            ALox.Config.RemovePlugin( iniFile );
            lox.RemoveLogger( ml );
            lox.RemoveLogger( "CONSOLE" );
        }

        // ignore case
        clearLox.ClearSourcePathTrimRules( Reach.Global, false);
        ALox.Config.GetPluginTypeSafe<InMemoryPlugin>( Configuration.PrioDefaultValues   ).Reset();
        {
            // store default values
            Variable var= new Variable();
            ALox.Config.Store( var.Declare( ALox.ConfigCategory, "TESTML_FORMAT" ), "%Sp" );
            ALox.Config.Store( var.Declare( ALox.ConfigCategory, "T_LOX_SOURCE_PATH_TRIM_RULES",';' ),
                                                     "*aLOX.U, exc, 2, ign"   );


            // test
            Lox lox= new Lox("T_LOX", false );

            lox.SetVerbosity( Lox.CreateConsoleLogger("CONSOLE") , Verbosity.Verbose );
            lox.SetVerbosity( "CONSOLE"                          , Verbosity.Verbose, ALox.InternalDomains );

            MemoryLogger ml= new MemoryLogger("TESTML");

            lox.SetVerbosity(ml, Verbosity.Verbose );

            lox.Info( "" ); UT_EQ( "ox.unittests"  , ml.MemoryLog ); ml.MemoryLog._(); ml.AutoSizes.Reset();

            lox.RemoveLogger( ml );
            lox.RemoveLogger( "CONSOLE" );
        }

        clearLox.ClearSourcePathTrimRules( Reach.Global, false);
        ALox.Config.GetPluginTypeSafe<InMemoryPlugin>( Configuration.PrioDefaultValues   ).Reset();
        {
            // store default values
            Variable var= new Variable();
            ALox.Config.Store( var.Declare( ALox.ConfigCategory, "TESTML_FORMAT" ), "%Sp" );
            ALox.Config.Store( var.Declare( ALox.ConfigCategory, "T_LOX_SOURCE_PATH_TRIM_RULES",';'),
                "*aLOX.U, excl, 2, sens"  );



            // test
            Lox lox= new Lox("T_LOX", false );

            lox.SetVerbosity( Lox.CreateConsoleLogger("CONSOLE") , Verbosity.Verbose );
            lox.SetVerbosity( "CONSOLE"                          , Verbosity.Verbose, ALox.InternalDomains );

            MemoryLogger ml= new MemoryLogger("TESTML");

            lox.SetVerbosity(ml, Verbosity.Verbose );

            lox.Info( "" );
            if( Path.DirectorySeparatorChar == '/' )
                UT_EQ( "src.cs/alox.unittests"  , ml.MemoryLog );
            else
                UT_EQ( "src.cs\\alox.unittests"  , ml.MemoryLog );

            ml.MemoryLog._(); ml.AutoSizes.Reset();
            lox.RemoveLogger( ml );
            lox.RemoveLogger( "CONSOLE" );
        }
    }
    #endif

    /** ********************************************************************************************
     * Log_ScopeInfoCacheTest
     **********************************************************************************************/
    #if ALOX_DBG_LOG
    #if ALIB_NUNIT
        [Test ()]
    #endif
    #if ALIB_IDE_VSTUDIO
        [TestMethod]
        #if !WINDOWS_PHONE
            [TestCategory("CS_ALox")]
        #endif
    #endif
    public void Log_ScopeInfoCacheTest()
    {
        UT_INIT();

        Log.AddDebugLogger();

        MemoryLogger memLogger= new MemoryLogger();
        if( Path.DirectorySeparatorChar == '/' )
            memLogger.MetaInfo.Format._()._( "%Sp/%SF@" );
        else
            memLogger.MetaInfo.Format._()._( "%Sp\\%SF@" );

        Log.SetVerbosity( memLogger, Verbosity.Verbose );


                          CS_ALox_Lox.ScopeInfoCacheTest(); check_MemLogStartsWith( "alox.unittests/UT_alox_lox.cs"               , memLogger, false );
        CS_ALox_Documentation_Samples.ScopeInfoCacheTest(); check_MemLogStartsWith( "alox.unittests/UT_dox_reference_manual.cs"   , memLogger, false );
                      CS_ALox_domains.ScopeInfoCacheTest(); check_MemLogStartsWith( "alox.unittests/UT_alox_domains.cs"           , memLogger, false );

        CS_ALox_Documentation_Samples.ScopeInfoCacheTest(); check_MemLogStartsWith( "alox.unittests/UT_dox_reference_manual.cs"   , memLogger, false );
                      CS_ALox_domains.ScopeInfoCacheTest(); check_MemLogStartsWith( "alox.unittests/UT_alox_domains.cs"           , memLogger, false );

                       CS_ALox_Logger.ScopeInfoCacheTest(); check_MemLogStartsWith( "alox.unittests/UT_alox_logger.cs"            , memLogger, false );

                      CS_ALox_domains.ScopeInfoCacheTest(); check_MemLogStartsWith( "alox.unittests/UT_alox_domains.cs"           , memLogger, false );
                       CS_ALox_Logger.ScopeInfoCacheTest(); check_MemLogStartsWith( "alox.unittests/UT_alox_logger.cs"            , memLogger, false );

                        CS_ALox_Tools.ScopeInfoCacheTest(); check_MemLogStartsWith( "alox.unittests/UT_alox_logtools.cs"          , memLogger, false );
                        CS_ALox_Tools.ScopeInfoCacheTest(); check_MemLogStartsWith( "alox.unittests/UT_alox_logtools.cs"          , memLogger, false );
                      CS_ALox_release.ScopeInfoCacheTest(); check_MemLogStartsWith( "alox.unittests/UT_alox_release_log.cs"       , memLogger, false );
                        CS_ALox_Tools.ScopeInfoCacheTest(); check_MemLogStartsWith( "alox.unittests/UT_alox_logtools.cs"          , memLogger, false );
                      CS_ALox_domains.ScopeInfoCacheTest(); check_MemLogStartsWith( "alox.unittests/UT_alox_domains.cs"           , memLogger, false );
                          CS_ALox_Lox.ScopeInfoCacheTest(); check_MemLogStartsWith( "alox.unittests/UT_alox_lox.cs"               , memLogger, false );
                       CS_ALox_scopes.ScopeInfoCacheTest(); check_MemLogStartsWith( "alox.unittests/UT_alox_scopes.cs"            , memLogger, false );
               CS_ALox_domains_helper.ScopeInfoCacheTest(); check_MemLogStartsWith( "alox.unittests/UT_alox_scopes_helper.cs"     , memLogger, false );
                          CS_Tutorial.ScopeInfoCacheTest(); check_MemLogStartsWith( "alox.unittests/UT_dox_tutorial.cs"           , memLogger, false );
                       CS_ALox_Logger.ScopeInfoCacheTest(); check_MemLogStartsWith( "alox.unittests/UT_alox_logger.cs"            , memLogger, false );

        Log.RemoveDebugLogger();
        Log.RemoveLogger( memLogger );
    }
    #endif

    /** ********************************************************************************************
     * Log_SimpleScopeDomain
     **********************************************************************************************/
    #if ALOX_DBG_LOG
    #if ALIB_NUNIT
        [Test ()]
    #endif
    #if ALIB_IDE_VSTUDIO
        [TestMethod]
        #if !WINDOWS_PHONE
            [TestCategory("CS_ALox")]
        #endif
    #endif
    public void Log_SimpleScopeDomain()
    {
        UT_INIT();

        int cntLL;
        Log.Error("No domain and nothing set");
        MemoryLogger ml= new MemoryLogger();

        Log.SetDomain( "REPLACED", Scope.Method );
        Log.SetDomain( "DFLT",     Scope.Method );

        String testOK=  "OK";
        String testERR= "Error";

        #if ALOX_DBG_LOG
            uint oneLine= 1;
        #else
            uint oneLine= 0;
        #endif

        // Test Verbosity setting
        cntLL= Log.DebugLogger.CntLogs;
        Log.SetVerbosity( Log.DebugLogger    ,  Verbosity.Info );

        cntLL= Log.DebugLogger.CntLogs;    Log.Verbose    ( testERR );    UT_EQ ( (uint) 0, Log.DebugLogger.CntLogs - cntLL );
        cntLL= Log.DebugLogger.CntLogs;    Log.Info       ( testOK  );    UT_EQ ( oneLine,  Log.DebugLogger.CntLogs - cntLL );

        Log.SetVerbosity( Log.DebugLogger,  Verbosity.Warning, "" );
        cntLL= Log.DebugLogger.CntLogs;    Log.Info       ( testERR );    UT_EQ ( (uint) 0, Log.DebugLogger.CntLogs - cntLL );
        cntLL= Log.DebugLogger.CntLogs;    Log.Warning    ( testOK  );    UT_EQ ( oneLine,  Log.DebugLogger.CntLogs - cntLL );

        Log.SetVerbosity( Log.DebugLogger, Verbosity.Error, "/" );
        cntLL= Log.DebugLogger.CntLogs;    Log.Warning    ( testERR );    UT_EQ ( (uint) 0, Log.DebugLogger.CntLogs - cntLL );
        cntLL= Log.DebugLogger.CntLogs;    Log.Error      ( testOK  );    UT_EQ ( oneLine,  Log.DebugLogger.CntLogs - cntLL );


        // test sub domains
        Log.SetVerbosity( Log.DebugLogger, Verbosity.Verbose, "/test" );
        Log.State( "/TEST",      Verbosity.Info, "Dumping Log Configuration:" );

        Log.SetVerbosity( ml, Verbosity.Info , "/DFLT"      );
        Log.SetVerbosity( ml, Verbosity.Warning     , "/DFLT/WARN" );
        Log.SetVerbosity( ml, Verbosity.Error                ,       "ERR"  );
        Log.SetVerbosity( Log.DebugLogger, Verbosity.Info , "/DFLT"      );
        Log.SetVerbosity( Log.DebugLogger, Verbosity.Warning     , "/DFLT/WARN" );
        Log.SetVerbosity( Log.DebugLogger, Verbosity.Error                ,       "ERR"  );

        Log.State( "/TEST",      Verbosity.Info, "Dumping Log Configuration:" );

        // log with leading "/" on domain
        cntLL= ml.CntLogs;    Log.Verbose( "/DFLT",        testERR );    UT_EQ ( (uint) 0, ml.CntLogs - cntLL );
        cntLL= ml.CntLogs;    Log.Verbose( "/DFLT/ERR",    testERR );    UT_EQ ( (uint) 0, ml.CntLogs - cntLL );
        cntLL= ml.CntLogs;    Log.Verbose( "/DFLT/WARN",   testERR );    UT_EQ ( (uint) 0, ml.CntLogs - cntLL );

        cntLL= ml.CntLogs;    Log.Info   ( "/DFLT",        testOK  );    UT_EQ ( oneLine,  ml.CntLogs - cntLL );
        cntLL= ml.CntLogs;    Log.Info   ( "/DFLT/ERR",    testERR );    UT_EQ ( (uint) 0, ml.CntLogs - cntLL );
        cntLL= ml.CntLogs;    Log.Info   ( "/DFLT/WARN",   testERR );    UT_EQ ( (uint) 0, ml.CntLogs - cntLL );

        cntLL= ml.CntLogs;    Log.Warning( "/DFLT",        testOK  );    UT_EQ ( oneLine,  ml.CntLogs - cntLL );
        cntLL= ml.CntLogs;    Log.Warning( "/DFLT/WARN",   testOK  );    UT_EQ ( oneLine,  ml.CntLogs - cntLL );
        cntLL= ml.CntLogs;    Log.Warning( "/DFLT/ERR",    testERR );    UT_EQ ( (uint) 0, ml.CntLogs - cntLL );

        cntLL= ml.CntLogs;    Log.Error  ( "/DFLT",        testOK  );    UT_EQ ( oneLine,  ml.CntLogs - cntLL );
        cntLL= ml.CntLogs;    Log.Error  ( "/DFLT/WARN",   testOK  );    UT_EQ ( oneLine,  ml.CntLogs - cntLL );
        cntLL= ml.CntLogs;    Log.Error  ( "/DFLT/ERR",    testOK  );    UT_EQ ( oneLine,  ml.CntLogs - cntLL );

        // log without leading "/" on domain (of-course, this is quite an error of using ALox)
        cntLL= ml.CntLogs;    Log.Verbose( "DFLT",         testERR );    UT_EQ ( (uint) 0, ml.CntLogs - cntLL );
        cntLL= ml.CntLogs;    Log.Verbose( "DFLT/ERR",     testERR );    UT_EQ ( (uint) 0, ml.CntLogs - cntLL );
        cntLL= ml.CntLogs;    Log.Verbose( "DFLT/WARN",    testERR );    UT_EQ ( (uint) 0, ml.CntLogs - cntLL );

        cntLL= ml.CntLogs;    Log.Info   ( "DFLT",         testOK  );    UT_EQ ( oneLine,  ml.CntLogs - cntLL );
        cntLL= ml.CntLogs;    Log.Info   ( "DFLT/ERR",     testOK  );    UT_EQ ( oneLine,  ml.CntLogs - cntLL );
        cntLL= ml.CntLogs;    Log.Info   ( "DFLT/WARN",    testOK  );    UT_EQ ( oneLine,  ml.CntLogs - cntLL );

        cntLL= ml.CntLogs;    Log.Warning( "DFLT",         testOK  );    UT_EQ ( oneLine,  ml.CntLogs - cntLL );
        cntLL= ml.CntLogs;    Log.Warning( "DFLT/WARN",    testOK  );    UT_EQ ( oneLine,  ml.CntLogs - cntLL );
        cntLL= ml.CntLogs;    Log.Warning( "DFLT/ERR",     testOK  );    UT_EQ ( oneLine,  ml.CntLogs - cntLL );

        cntLL= ml.CntLogs;    Log.Error  ( "DFLT",         testOK  );    UT_EQ ( oneLine,  ml.CntLogs - cntLL );
        cntLL= ml.CntLogs;    Log.Error  ( "DFLT/WARN",    testOK  );    UT_EQ ( oneLine,  ml.CntLogs - cntLL );
        cntLL= ml.CntLogs;    Log.Error  ( "DFLT/ERR",     testOK  );    UT_EQ ( oneLine,  ml.CntLogs - cntLL );


        // relative addressing with "~"domain
        cntLL= ml.CntLogs;    Log.Verbose(                 testERR );    UT_EQ ( (uint) 0, ml.CntLogs - cntLL );
        cntLL= ml.CntLogs;    Log.Verbose( "",             testERR );    UT_EQ ( (uint) 0, ml.CntLogs - cntLL );
        cntLL= ml.CntLogs;    Log.Verbose( "ERR",          testERR );    UT_EQ ( (uint) 0, ml.CntLogs - cntLL );
        cntLL= ml.CntLogs;    Log.Verbose( "WARN",         testERR );    UT_EQ ( (uint) 0, ml.CntLogs - cntLL );

        cntLL= ml.CntLogs;    Log.Info   (                 testOK  );    UT_EQ ( oneLine,  ml.CntLogs - cntLL );
        cntLL= ml.CntLogs;    Log.Info   ( "",             testOK  );    UT_EQ ( oneLine,  ml.CntLogs - cntLL );
        cntLL= ml.CntLogs;    Log.Info   ( "ERR",          testERR );    UT_EQ ( (uint) 0, ml.CntLogs - cntLL );
        cntLL= ml.CntLogs;    Log.Info   ( "WARN",         testERR );    UT_EQ ( (uint) 0, ml.CntLogs - cntLL );

        cntLL= ml.CntLogs;    Log.Warning(                 testOK  );    UT_EQ ( oneLine,  ml.CntLogs - cntLL );
        cntLL= ml.CntLogs;    Log.Warning( "",             testOK  );    UT_EQ ( oneLine,  ml.CntLogs - cntLL );
        cntLL= ml.CntLogs;    Log.Warning( "WARN",         testOK  );    UT_EQ ( oneLine,  ml.CntLogs - cntLL );
        cntLL= ml.CntLogs;    Log.Warning( "ERR",          testERR );    UT_EQ ( (uint) 0, ml.CntLogs - cntLL );

        cntLL= ml.CntLogs;    Log.Error  (                 testOK  );    UT_EQ ( oneLine,  ml.CntLogs - cntLL );
        cntLL= ml.CntLogs;    Log.Error  ( "",             testOK  );    UT_EQ ( oneLine,  ml.CntLogs - cntLL );
        cntLL= ml.CntLogs;    Log.Error  ( "WARN",         testOK  );    UT_EQ ( oneLine,  ml.CntLogs - cntLL );
        cntLL= ml.CntLogs;    Log.Error  ( "ERR",          testOK  );    UT_EQ ( oneLine,  ml.CntLogs - cntLL );

    }
    #endif

    /** ********************************************************************************************
     * Log_AssertAndIf
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
    public void Log_AssertAndIf()
    {
        #if ALOX_DBG_LOG
            UT_INIT();

            Log.AddDebugLogger();

            Log.SetDomain( "ASSERT", Scope.Method );

            String testOK=  "OK";
            String testERR= "Error";

            // Test Verbosity setting
            int cntLL= Log.DebugLogger.CntLogs;
            Log.SetVerbosity( Log.DebugLogger, Verbosity.Info, "ASSERT");

            cntLL= Log.DebugLogger.CntLogs;    Log.Assert( true,  "/ASSERT",                 testERR ); UT_EQ ( 0,  Log.DebugLogger.CntLogs - cntLL );
            cntLL= Log.DebugLogger.CntLogs;    Log.Assert( false, "/ASSERT",                 testOK  ); UT_EQ ( 1,  Log.DebugLogger.CntLogs - cntLL );
            cntLL= Log.DebugLogger.CntLogs;    Log.Assert( true,                             testERR ); UT_EQ ( 0,  Log.DebugLogger.CntLogs - cntLL );
            cntLL= Log.DebugLogger.CntLogs;    Log.Assert( false,                            testOK  ); UT_EQ ( 1,  Log.DebugLogger.CntLogs - cntLL );

            cntLL= Log.DebugLogger.CntLogs;    Log.If    ( true,  "/ASSERT", Verbosity.Info, testERR ); UT_EQ ( 1,  Log.DebugLogger.CntLogs - cntLL );
            cntLL= Log.DebugLogger.CntLogs;    Log.If    ( false, "/ASSERT", Verbosity.Info, testOK  ); UT_EQ ( 0,  Log.DebugLogger.CntLogs - cntLL );
            cntLL= Log.DebugLogger.CntLogs;    Log.If    ( true,             Verbosity.Info, testERR ); UT_EQ ( 1,  Log.DebugLogger.CntLogs - cntLL );
            cntLL= Log.DebugLogger.CntLogs;    Log.If    ( false,            Verbosity.Info, testOK  ); UT_EQ ( 0,  Log.DebugLogger.CntLogs - cntLL );
        #endif
    }

    /** ********************************************************************************************
     * Log.Threads
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
    public void Log_Threads()
    {
        UT_INIT();

        Log.AddDebugLogger();

        Log.SetDomain( "TEST/THREAD1", Scope.Method );
        Log.SetVerbosity( Log.DebugLogger, Verbosity.Verbose, "TEST/THREAD1" );

        // if this gets commented out, the test might crash. At least the console will
        // become scrambled!
        //Log.LOX.Lock.setUnsafe( true );

        Thread thread = new Thread( new ThreadStart( testDifferentThreadMethod ) ) {Name = "Thread2"};
        thread.Start();

        for ( int i= 0 ; i < 50 ; i++ )
        {
            Log.Info( "This is the main thread ");// + i );
            ALIB.SleepMillis( 4 );
        }
    }

    public void testDifferentThreadMethod()
    {
        Log.SetDomain( "TEST/THREAD2", Scope.Method );
        Log.SetVerbosity( Log.DebugLogger, Verbosity.Verbose, "TEST/THREAD2" );

        for ( int i= 0 ; i < 20 ; i++ )
        {
            Log.Info( "This is a different Thread. Cnt= " + i );
            ALIB.SleepMillis( 3 );
        }
    }


    /** ********************************************************************************************
     * Log_MultipleLogables
     **********************************************************************************************/
    #if ALOX_DBG_LOG
    #if ALIB_NUNIT
        [Test ()]
    #endif
    #if ALIB_IDE_VSTUDIO
        [TestMethod]
        #if !WINDOWS_PHONE
            [TestCategory("CS_ALox")]
        #endif
    #endif
    public void Log_MultipleLogables()
    {
        UT_INIT();

        Log.AddDebugLogger();
        MemoryLogger memLogger= new MemoryLogger();
        Log.SetVerbosity( memLogger, Verbosity.Verbose );

        Object[] logables= { "First, ", "second, ", 3 };

        //---- Log.Info -----
        memLogger.MemoryLog.Clear();
        Log.Info( logables );
        UT_TRUE( memLogger.MemoryLog.IndexOf( "First, second, 3" ) > 0 );

        memLogger.MemoryLog.Clear();
//! [DOX_ALOX_LOX_MULTIPLE_PARAMS]
Log.Info( "MYDOM", new Object[] {"The result of {} + {} is ", 10, 5,  10 + 5 } );
//! [DOX_ALOX_LOX_MULTIPLE_PARAMS]

        UT_TRUE( memLogger.MemoryLog.IndexOf( "The result of 10 + 5 is 15" ) > 0 );



        //---- Log.Once -----
        memLogger.MemoryLog.Clear();
        Log.Once( logables );
        UT_TRUE( memLogger.MemoryLog.IndexOf( "First, second, 3" ) > 0 );

        memLogger.MemoryLog.Clear();
//! [DOX_ALOX_LOX_ONCE]
Log.Once( new Object[] {"One - {} - {}!", "two", 3}  );
//! [DOX_ALOX_LOX_ONCE]
        UT_TRUE( memLogger.MemoryLog.IndexOf( "One - two - 3" ) > 0 );

    }
    #endif

    /** ********************************************************************************************
     * Log.Threads
     **********************************************************************************************/
    #if ALOX_DBG_LOG
    #if ALIB_NUNIT
        [Test ()]
    #endif
    #if ALIB_IDE_VSTUDIO
        [TestMethod]
        #if !WINDOWS_PHONE
            [TestCategory("CS_ALox")]
        #endif
    #endif
    public void Log_GetState()
    {
        UT_INIT();

        Log.AddDebugLogger();
        MemoryLogger memLogger= new MemoryLogger();

        // reduce meta information to limit output width
        Log.DebugLogger.MetaInfo.Format._()._( "[%tN]%V[%D](%#): " );
        memLogger.MetaInfo.Format._()._(       "[%tN]%V[%D](%#): " );
        memLogger.MultiLineMsgMode= 3;
        Log.SetVerbosity( memLogger, Verbosity.Verbose );

        // OK, let's use ALox
        Log.SetDomain( "PNS"   ,   Scope.Path, 1 );
        Log.SetDomain( "PATH",     Scope.Path );
        Log.SetDomain( "FN",       Scope.Filename );
        Log.SetDomain( "THREAD",   Scope.ThreadOuter );

        Log.SetVerbosity( "MEMORY",        Verbosity.Off      , "/CON"    );
        Log.SetVerbosity( "DEBUG_LOGGER" , Verbosity.Verbose              );
        Log.SetVerbosity( "DEBUG_LOGGER" , Verbosity.Off      , "/MEM"    );
        Log.SetVerbosity( "DEBUG_LOGGER" , Verbosity.Error    , "/UI"     );
        Log.SetVerbosity( "DEBUG_LOGGER" , Verbosity.Info     , "/UI/DLG" );

        Log.Info( "This goes to both loggers" );
        Log.Info( "/MEM", "This goes only to the memory logger" );
        Log.Info( "/CON", "This goes only to the console logger" );

        Log.Once( "Will we see this in the config?" );
        Log.Once( "Will we see this in the config?", "ONCEKEY", Scope.Filename );

        Log.Store( "MyData 1" , Scope.Method );
        Log.Store( "MyData 2" , "DataKey", Scope.Method );
        Log.Store( 3          , "DataKey", Scope.Filename );
        Log.Store( 4          , "DataKey", Scope.ThreadOuter );

        Log.SetPrefix( "TPre: "  , Scope.ThreadOuter );
        Log.SetPrefix( "MPre: "  , Scope.Method );
        Log.SetPrefix( "DomPre: " );
        Log.SetPrefix( "Mouse: ", "/UI/MOUSE" );
        Log.SetPrefix( ESC.RED,  "/ERRORS", Inclusion.Exclude );

        Log.MapThreadName( "TUTORIAL" );

        // now, log the current config
        Log.State( null, Verbosity.Info, "State(ALL):" );

        Log.State( null, Verbosity.Info, "State(Domains):", Lox.StateInfo.Domains );
        Log.State( null, Verbosity.Info, "State(Loggers):", Lox.StateInfo.Loggers );


        // cleanup
        Log.RemoveDebugLogger();
        Log.RemoveLogger( memLogger );
    }
    #endif

    /** ********************************************************************************************
     * Log_DumpStateOnExit
     **********************************************************************************************/
    #if ALOX_DBG_LOG
    #if ALIB_NUNIT
        [Test ()]
    #endif
    #if ALIB_IDE_VSTUDIO
        [TestMethod]
        #if !WINDOWS_PHONE
            [TestCategory("CS_ALox")]
        #endif
    #endif
    public void Log_DumpStateOnExit()
    {
        UT_INIT();

        Log.AddDebugLogger();
        MemoryLogger memLogger= new MemoryLogger();


        Log.SetVerbosity( memLogger, Verbosity.Verbose );
        UT_TRUE( Log.DebugLogger.CntLogs == 0 );
        Log.RemoveLogger( memLogger );
        UT_TRUE( Log.DebugLogger.CntLogs == 0 );

        Variable var= new Variable( ALox.ConfigCategory, Log.LOX.GetName() + "_DUMP_STATE_ON_EXIT",  ',' );

        ALox.Config.Store( var, "domain=/TEST, verbosity = e, domains, basic" );
        int cntLogs;

        ALox.Config.Store( var, "domain=/TEST, verbosity = e, sptr, basic" );
        Log.SetVerbosity( memLogger, Verbosity.Verbose );
        cntLogs= Log.DebugLogger.CntLogs;
        Log.RemoveLogger( memLogger );
        UT_TRUE( Log.DebugLogger.CntLogs > cntLogs );

        ALox.Config.Store( var, "verbosity = e, domains, basic" );
        Log.SetVerbosity( memLogger, Verbosity.Verbose );
        cntLogs= Log.DebugLogger.CntLogs;
        Log.RemoveLogger( memLogger );
        UT_TRUE( Log.DebugLogger.CntLogs > cntLogs );

        ALox.Config.Store( var, "domains, loggers" );
        Log.SetVerbosity( memLogger, Verbosity.Verbose );
        cntLogs= Log.DebugLogger.CntLogs;
        Log.RemoveLogger( memLogger );
        UT_TRUE( Log.DebugLogger.CntLogs > cntLogs );

        ALox.Config.Store( var, "" );
        Log.SetVerbosity( memLogger, Verbosity.Verbose );
        cntLogs= Log.DebugLogger.CntLogs;
        Log.RemoveLogger( memLogger );
        UT_TRUE( Log.DebugLogger.CntLogs == cntLogs );

        Log.RemoveDebugLogger();
    }
    #endif

    /** ********************************************************************************************
     * Log_WriteVerbosities
     **********************************************************************************************/
    #if ALOX_DBG_LOG
    #if ALIB_NUNIT
        [Test ()]
    #endif
    #if ALIB_IDE_VSTUDIO
        [TestMethod]
        #if !WINDOWS_PHONE
            [TestCategory("CS_ALox")]
        #endif
    #endif
    public void Log_WriteVerbosities()
    {
        UT_INIT();

        Log.AddDebugLogger();
        MemoryLogger memLogger= new MemoryLogger("MYLGGR");
        Log.SetVerbosity( Log.DebugLogger, Verbosity.Verbose, ALox.InternalDomains );

        Variable var= new Variable( ALox.ConfigCategory, Log.LOX.GetName() + "_MYLGGR_VERBOSITY",  ';' );
        Variable varBack= new Variable();

        // test writing into other variable with variable name error
        UT_PRINT( "An error message should follow (wrong variable format): " );
        ALox.Config.Store( var,  "writeback MY_" );
        Log.SetVerbosity( memLogger, Verbosity.Verbose );
        Log.RemoveLogger( memLogger );

        // test writing into other variable
        ALox.Config.Store( var,  "writeback MY_VAR" );
        Log.SetVerbosity( memLogger, Verbosity.Verbose );
        Log.RemoveLogger( memLogger );
        ALox.Config.Load(varBack.Declare( "MY",  "VAR" ));
        UT_PRINT(  "Variable written: ", varBack.GetString() );
        UT_TRUE( varBack.GetString().Length() > 0 );

        // test writing into other variable without cat
        ALox.Config.Store( var,  "writeback ANON" );
        Log.SetVerbosity( memLogger, Verbosity.Verbose );
        Log.RemoveLogger( memLogger );
        ALox.Config.Load(varBack.Declare( "",  "ANON" ));
        UT_PRINT(  "Variable written: ", varBack.GetString() );
        UT_TRUE( varBack.GetString().Length() > 0 );

        // test writing into other variable without cat and with underscores in name
        ALox.Config.Store( var,  "writeback _2ND_ANON" );
        Log.SetVerbosity( memLogger, Verbosity.Verbose );
        Log.RemoveLogger( memLogger );
        ALox.Config.Load(varBack.Declare( "",  "2ND_ANON" ));
        UT_PRINT(  "Variable written: ", varBack.GetString() );
        UT_TRUE( varBack.GetString().Length() > 0 );

        // test writing into other the variable itself
        ALox.Config.Store( var,  "writeback" );
        Log.SetVerbosity( memLogger, Verbosity.Verbose );
        Log.RemoveLogger( memLogger );

        ALox.Config.Load( var);
        UT_PRINT( "Variable written: ", var.GetString() );
        UT_TRUE( var.GetString().Length() > 0 );

       Log.RemoveDebugLogger();
    }
    #endif


} // class
} // namespace
