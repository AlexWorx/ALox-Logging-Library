// #################################################################################################
//  cs.aworx.lox.unittests - ALox Logging Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
using System;
using System.Threading;
using System.Xml.Linq;
using ut_cs_aworx;
using cs.aworx.lib.enums;
using cs.aworx.lib.strings;
using cs.aworx.lox.core.textlogger;
using System.IO;
using cs.aworx.lib.config;

#if ALIB_MONO_DEVELOP
    using NUnit.Framework;
#endif
#if ALIB_VSTUDIO
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
    #if ALIB_MONO_DEVELOP
        [TestFixture ()]
    #endif
    #if ALIB_VSTUDIO
        [TestClass]
    #endif
    public class CS_ALox_Lox   : AUnitTest
    {
        // used with unit test Log_ScopeInfoCacheTest
        public static void ScopeInfoCacheTest() { Log.Info("Test method of CS_ALox_Lox"); }

    /** ********************************************************************************************
     * Lox_AddLogger.
     **********************************************************************************************/
    #if ALOX_DBG_LOG
    #if ALIB_MONO_DEVELOP
        [Test ()]
    #endif
    #if ALIB_VSTUDIO
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
    
            Log.SetVerbosity( mem1,     Verbosity.Info ); UT_EQ( 0, checkCnt.CntLogs );
            Log.SetVerbosity( mem2,     Verbosity.Info ); UT_EQ( 1, checkCnt.CntLogs );
            Log.SetVerbosity( "XYZ",    Verbosity.Info ); UT_EQ( 2, checkCnt.CntLogs );
               
            Log.RemoveLogger( mem2     );                 UT_EQ( 3, checkCnt.CntLogs );
            Log.RemoveLogger( mem1     );                 UT_EQ( 3, checkCnt.CntLogs );
            Log.RemoveLogger( mem1     );                 UT_EQ( 4, checkCnt.CntLogs );
            Log.RemoveLogger( "XYZ"    );                 UT_EQ( 5, checkCnt.CntLogs );
            Log.RemoveLogger( con      );                 UT_EQ( 5, checkCnt.CntLogs );
            Log.RemoveLogger( con      );                 UT_EQ( 6, checkCnt.CntLogs );
            Log.RemoveLogger( checkCnt );                 UT_EQ( 6, checkCnt.CntLogs );
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
    #if ALIB_MONO_DEVELOP
        [Test ()]
    #endif
    #if ALIB_VSTUDIO
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

        Log.ClearSourcePathTrimRules( Inclusion.Include, false );

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
        Log.ClearSourcePathTrimRules( Inclusion.Include, false );
        Log.SetSourcePathTrimRule( "*/src.cs/" , Inclusion.Include, -3 );  check_MemLogStartsWith( "cs/alox.unittests@"  , memLogger );
        Log.ClearSourcePathTrimRules( Inclusion.Include, false );
        Log.SetSourcePathTrimRule( "*/src.cs/" , Inclusion.Include, 2  );  check_MemLogStartsWith( "ox.unittests@"       , memLogger );

        Log.ClearSourcePathTrimRules( Inclusion.Include, false );
        Log.SetSourcePathTrimRule( "*/src.cs/" , Inclusion.Exclude     );  check_MemLogStartsWith( "/src.cs"             , memLogger );

        Log.ClearSourcePathTrimRules( Inclusion.Include, false );
        Log.SetSourcePathTrimRule( "*/src.cs/" , Inclusion.Exclude, -3 );  check_MemLogStartsWith( "lox/src.cs"          , memLogger );

        Log.ClearSourcePathTrimRules( Inclusion.Include, false );
        Log.SetSourcePathTrimRule( "*/src.cs/*", Inclusion.Exclude, -3 );  check_MemLogStartsWith( "lox/src.cs"          , memLogger );

        // clear only local rule. (the above rule was global)
        Log.ClearSourcePathTrimRules( Inclusion.Exclude, false );
                                                                            check_MemLogStartsWith( "lox/src.cs"         , memLogger );

        // set local rules
        Log.ClearSourcePathTrimRules( Inclusion.Include, false );
        Log.SetSourcePathTrimRule( "*/src.cs/" , Inclusion.Exclude, 0, Case.Ignore, Inclusion.Exclude );  check_MemLogStartsWith( "/src.cs"         , memLogger );

        Log.ClearSourcePathTrimRules( Inclusion.Include, false );
        Log.SetSourcePathTrimRule( "*/src.cs/" , Inclusion.Exclude, 0, Case.Ignore, Inclusion.Exclude );  check_MemLogStartsWith( "/src.cs"         , memLogger );

        // check non ignore case
        Log.ClearSourcePathTrimRules( Inclusion.Include, false );
        Log.SetSourcePathTrimRule( "*/src.cs/" , Inclusion.Exclude, 0, Case.Ignore, Inclusion.Exclude );   check_MemLogStartsWith( "/src.cs"         , memLogger );

        Log.ClearSourcePathTrimRules( Inclusion.Include, false );
        Log.SetSourcePathTrimRule( "*/SRC.CS/" , Inclusion.Exclude, 0, Case.Sensitive, Inclusion.Exclude );
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
    #if ALIB_MONO_DEVELOP
        [Test ()]
    #endif
    #if ALIB_VSTUDIO
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
        clearLox.ClearSourcePathTrimRules( Inclusion.Include, false );
        {
            // create iniFile
            String iniFileContents=
                 "[ALOX]\n"
                +"TESTML_FORMAT= \"%Sp\"  \n"
    
                +"GLOBAL_SOURCE_PATH_TRIM_RULES=  *src.cs/   , true  ;     \\   \n"
                             +"    /usr/lib/libzip/include/  , false, 9, true"
                +"\n"
               ;
/* SNIPPIT FOR Dox
//! [Man_SourcePathTrimming]
[ALOX]
GLOBAL_SOURCE_PATH_TRIM_RULES= *src.cs/                  , true                ; \
                               /usr/lib/libzip/include/  , false, 9, true
//! [Man_SourcePathTrimming]
*/
            String fileName= Environment.CurrentDirectory + "/Log_ConfigTrimRules.ini";
            StreamWriter file= new StreamWriter( fileName );
            file.Write( iniFileContents );
            file.Close();
    
            IniFile iniFile= new IniFile( fileName );
            iniFile.ReadFile();
            //iniFile.WriteFile(); // temporarily enable to see what we have written above

            ALIB.Config.InsertPlugin( iniFile, Configuration.PrioIniFile );
            
            // test
            Lox lox= new Lox("T_LOX", false );
    
            lox.SetVerbosity( Lox.CreateConsoleLogger("CONSOLE") , Verbosity.Verbose );
            lox.SetVerbosity( "CONSOLE"                          , Verbosity.Verbose, ALox.InternalDomains );

            MemoryLogger ml= new MemoryLogger("TESTML");
            lox.SetVerbosity(ml, Verbosity.Verbose );

            lox.Info( "" );  UT_EQ("alox.unittests", ml.MemoryLog ); ml.MemoryLog._(); ml.AutoSizes.Reset();
    
            ALIB.Config.RemovePlugin( iniFile );
            lox.RemoveLogger( ml );
            lox.RemoveLogger( "CONSOLE" );
        }

        // local rule
        clearLox.ClearSourcePathTrimRules( Inclusion.Include, false );
        {
            // create iniFile
            IniFile iniFile= new IniFile("*"); // don't read
            iniFile.Save( ALox.ConfigCategoryName, "TESTML_FORMAT","%Sp"   );
            iniFile.Save( ALox.ConfigCategoryName, "T_LOX_SOURCE_PATH_TRIM_RULES", 
                             "*;**;*alox.u*, incl ;*;**"   // default values, 0, ignore" 
                                                           // the * will be removed
                                                           // two illegal rules before and after
                    );
            ALIB.Config.InsertPlugin( iniFile, Configuration.PrioIniFile );
            

            // test
            Lox lox= new Lox("T_LOX", false );
    
            lox.SetVerbosity( Lox.CreateConsoleLogger("CONSOLE") , Verbosity.Verbose );
            lox.SetVerbosity( "CONSOLE"                          , Verbosity.Verbose, ALox.InternalDomains );

            MemoryLogger ml= new MemoryLogger("TESTML");
            lox.SetVerbosity(ml, Verbosity.Verbose );

            lox.Info( "" ); UT_EQ( "nittests"  , ml.MemoryLog ); ml.MemoryLog._(); ml.AutoSizes.Reset();
    
            ALIB.Config.RemovePlugin( iniFile );
            lox.RemoveLogger( ml );
            lox.RemoveLogger( "CONSOLE" );
        }

        clearLox.ClearSourcePathTrimRules( Inclusion.Include, false );
        {
            // create iniFile
            IniFile iniFile= new IniFile("*"); // don't read
            iniFile.Save( ALox.ConfigCategoryName, "TESTML_FORMAT","%Sp"   );
            iniFile.Save( ALox.ConfigCategoryName, "T_LOX_SOURCE_PATH_TRIM_RULES", 
                             "*alox.u, excl, 2, sens"  
                    );
            ALIB.Config.InsertPlugin( iniFile, Configuration.PrioIniFile );
            

            // test
            Lox lox= new Lox("T_LOX", false );
    
            lox.SetVerbosity( Lox.CreateConsoleLogger("CONSOLE") , Verbosity.Verbose );
            lox.SetVerbosity( "CONSOLE"                          , Verbosity.Verbose, ALox.InternalDomains );

            MemoryLogger ml= new MemoryLogger("TESTML");
            lox.SetVerbosity(ml, Verbosity.Verbose );

            lox.Info( "" ); UT_EQ( "ox.unittests"  , ml.MemoryLog ); ml.MemoryLog._(); ml.AutoSizes.Reset();
    
            ALIB.Config.RemovePlugin( iniFile );
            lox.RemoveLogger( ml );
            lox.RemoveLogger( "CONSOLE" );
        }

        // ignore case
        clearLox.ClearSourcePathTrimRules( Inclusion.Include, false );
        {
            // create iniFile
            IniFile iniFile= new IniFile("*"); // don't read
            iniFile.Save( ALox.ConfigCategoryName, "TESTML_FORMAT","%Sp"   );
            iniFile.Save( ALox.ConfigCategoryName, "T_LOX_SOURCE_PATH_TRIM_RULES", 
                             "*aLOX.U, exc, 2, ign"  
                    );
            ALIB.Config.InsertPlugin( iniFile, Configuration.PrioIniFile );
            

            // test
            Lox lox= new Lox("T_LOX", false );
    
            lox.SetVerbosity( Lox.CreateConsoleLogger("CONSOLE") , Verbosity.Verbose );
            lox.SetVerbosity( "CONSOLE"                          , Verbosity.Verbose, ALox.InternalDomains );

            MemoryLogger ml= new MemoryLogger("TESTML");
            lox.SetVerbosity(ml, Verbosity.Verbose );

            lox.Info( "" ); UT_EQ( "ox.unittests"  , ml.MemoryLog ); ml.MemoryLog._(); ml.AutoSizes.Reset();
    
            ALIB.Config.RemovePlugin( iniFile );
            lox.RemoveLogger( ml );
            lox.RemoveLogger( "CONSOLE" );
        }

        clearLox.ClearSourcePathTrimRules( Inclusion.Include, false );
        {
            // create iniFile
            IniFile iniFile= new IniFile("*"); // don't read
            iniFile.Save( ALox.ConfigCategoryName, "TESTML_FORMAT","%Sp"   );
            iniFile.Save( ALox.ConfigCategoryName, "T_LOX_SOURCE_PATH_TRIM_RULES", 
                             "*aLOX.U, excl, 2, sens"  
                    );
            ALIB.Config.InsertPlugin( iniFile, Configuration.PrioIniFile );
            

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
            ALIB.Config.RemovePlugin( iniFile );
            lox.RemoveLogger( ml );
            lox.RemoveLogger( "CONSOLE" );
        }
    }

    /** ********************************************************************************************
     * Log_ScopeInfoCacheTest
     **********************************************************************************************/
    #if ALOX_DBG_LOG
    #if ALIB_MONO_DEVELOP
        [Test ()]
    #endif
    #if ALIB_VSTUDIO
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
    #if ALIB_MONO_DEVELOP
        [Test ()]
    #endif
    #if ALIB_VSTUDIO
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
        Log.LogConfig( "/TEST",      Verbosity.Info, "Dumping Log Configuration:" );

        Log.SetVerbosity( ml, Verbosity.Info , "/DFLT"      );
        Log.SetVerbosity( ml, Verbosity.Warning     , "/DFLT/WARN" );
        Log.SetVerbosity( ml, Verbosity.Error                ,       "ERR"  );
        Log.SetVerbosity( Log.DebugLogger, Verbosity.Info , "/DFLT"      );
        Log.SetVerbosity( Log.DebugLogger, Verbosity.Warning     , "/DFLT/WARN" );
        Log.SetVerbosity( Log.DebugLogger, Verbosity.Error                ,       "ERR"  );

        Log.LogConfig( "/TEST",      Verbosity.Info, "Dumping Log Configuration:" );

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

        // log without leading "/" on domain (of course, this is quite an error of using ALox)
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
    #if ALIB_MONO_DEVELOP
        [Test ()]
    #endif
    #if ALIB_VSTUDIO
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
    #if ALIB_MONO_DEVELOP
        [Test ()]
    #endif
    #if ALIB_VSTUDIO
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

    } // class
} // namespace
