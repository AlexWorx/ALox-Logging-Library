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
    public class CS_ALox_domains  : AUnitTest
    {
        // used with unit test Log_ScopeInfoCacheTest
        public static void ScopeInfoCacheTest() { Log.Info("Test method of CS_ALox_domains"); }


    void LOG_CHECK( String dom, String exp, MemoryLogger ml, Lox lox )
    {
        ml.MemoryLog._(); ml.AutoSizes.Reset();
        lox.Info( dom, "" );
        UT_EQ( exp , ml.MemoryLog );
    }


    /** ********************************************************************************************
     * Lox_IllegalDomainNames
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
    public void Log_IllegalDomainNames()
    {
        UT_INIT();
        Log.AddDebugLogger();

        MemoryLogger ml= new MemoryLogger();

        Log.SetVerbosity ( ml, Verbosity.Verbose );
        ml.MetaInfo.Format._()._("<%D>");

        Log.SetVerbosity(Log.DebugLogger, Verbosity.Verbose, ALox.InternalDomains );


        LOG_CHECK( ""        , "</>"              , ml,Log.LOX);
        LOG_CHECK( "LOC"     , "</LOC>"           , ml,Log.LOX);
        LOG_CHECK( "%"       , "</#>"             , ml,Log.LOX);
        LOG_CHECK( "\x03"    , "</#>"             , ml,Log.LOX);
        LOG_CHECK( "<"       , "</#>"             , ml,Log.LOX);
        LOG_CHECK( ">"       , "</#>"             , ml,Log.LOX);
        LOG_CHECK( "?"       , "</#>"             , ml,Log.LOX);
        LOG_CHECK( ","       , "</#>"             , ml,Log.LOX);
        LOG_CHECK( "-"       , "</->"             , ml,Log.LOX);
        LOG_CHECK( "_"       , "</_>"             , ml,Log.LOX);
        LOG_CHECK( "@"       , "</@>"             , ml,Log.LOX);
        LOG_CHECK( "."       , "</>"              , ml,Log.LOX);
        LOG_CHECK( ".."      , "</>"              , ml,Log.LOX);
        LOG_CHECK( "CU.."    , "</CU##>"          , ml,Log.LOX);

        LOG_CHECK( "$%! "    , "</####>"          , ml,Log.LOX);

        Log.SetDomain( "METH", Scope.Filename );
        LOG_CHECK( "$%! "    , "</METH/####>"     , ml,Log.LOX);

        Log.SetDomain( "A\"C" , Scope.Filename );
        LOG_CHECK( ""        , "</A#C>"           , ml,Log.LOX);
        LOG_CHECK( "LOC"     , "</A#C/LOC>"       , ml,Log.LOX);
        LOG_CHECK( "*X*"     , "</A#C/#X#>"       , ml,Log.LOX);

        Log.RemoveLogger( ml );
    }
    #endif

    /** ********************************************************************************************
     * Log_RelativeDomains
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
    public void Log_RelativeDomains()
    {
        UT_INIT();

        Lox lox= new Lox( "ReleaseLox" );
        MemoryLogger ml= new MemoryLogger();

        lox.SetVerbosity ( ml, Verbosity.Verbose );
        ml.MetaInfo.Format._()._("@%D#");
        lox.SetDomain( "/D1/D2/D3", Scope.Method );

        lox.Info( "D4"                 , "" ); UT_EQ( "@/D1/D2/D3/D4#"        , ml.MemoryLog ); ml.MemoryLog._(); ml.AutoSizes.Reset();
        lox.Info( "./D4"               , "" ); UT_EQ( "@/D1/D2/D3/D4#"        , ml.MemoryLog ); ml.MemoryLog._(); ml.AutoSizes.Reset();
        lox.Info( "../D4"              , "" ); UT_EQ( "@/D1/D2/D4#"           , ml.MemoryLog ); ml.MemoryLog._(); ml.AutoSizes.Reset();
        lox.Info( ".././.././D4"       , "" ); UT_EQ( "@/D1/D4#"              , ml.MemoryLog ); ml.MemoryLog._(); ml.AutoSizes.Reset();
        lox.Info( "../../../../../D4"  , "" ); UT_EQ( "@/D4#"                 , ml.MemoryLog ); ml.MemoryLog._(); ml.AutoSizes.Reset();
        lox.Info( "../D4/../D5"        , "" ); UT_EQ( "@/D1/D2/D5#"           , ml.MemoryLog ); ml.MemoryLog._(); ml.AutoSizes.Reset();


        lox.RemoveLogger( ml );
    }

    /** ********************************************************************************************
     * Log_DomainSubstitutions
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
    public void Log_DomainSubstitutions()
    {
        UT_INIT();
        Log.AddDebugLogger();

        MemoryLogger ml= new MemoryLogger();

        Log.SetVerbosity ( ml, Verbosity.Verbose );
        ml.MetaInfo.Format._()._("<%D>");

                                                        LOG_CHECK( ""     , "</>"                    , ml,Log.LOX);
                                                        LOG_CHECK( "LOC"  , "</LOC>"                 , ml,Log.LOX);

        // wrong rule
        Log.SetVerbosity(Log.DebugLogger, Verbosity.Warning, ALox.InternalDomains );    int cntLogs= Log.DebugLogger.CntLogs;
        Log.SetDomainSubstitutionRule( "LOC"        , "X"       );   ;                      UT_TRUE( cntLogs + 1 == Log.DebugLogger.CntLogs );
        Log.SetDomainSubstitutionRule( "*LOC/"      , "X"       );   ;                      UT_TRUE( cntLogs + 2 == Log.DebugLogger.CntLogs );
        Log.SetDomainSubstitutionRule( "LOC/*"      , "X"       );   ;                      UT_TRUE( cntLogs + 3 == Log.DebugLogger.CntLogs );
        Log.SetDomainSubstitutionRule( "LOC*"       , "X"       );   ;                      UT_TRUE( cntLogs + 4 == Log.DebugLogger.CntLogs );
        Log.SetDomainSubstitutionRule( "*LOC*"      , "X"       );   ;                      UT_TRUE( cntLogs + 4 == Log.DebugLogger.CntLogs );
        Log.SetDomainSubstitutionRule( "*/LOC*"     , "X"       );   ;                      UT_TRUE( cntLogs + 4 == Log.DebugLogger.CntLogs );
        Log.SetDomainSubstitutionRule( "*/LOC/*"    , "X"       );   ;                      UT_TRUE( cntLogs + 4 == Log.DebugLogger.CntLogs );

        Log.SetDomainSubstitutionRule( null        , null       );   // delete rules
        Log.SetVerbosity(Log.DebugLogger, Verbosity.Warning, ALox.InternalDomains );

        // Exact match
        Log.SetDomainSubstitutionRule( null          , null      );
        Log.SetDomainSubstitutionRule( "/LOC"        , "X"       );   LOG_CHECK( "LOC"  , "</X>"                   , ml,Log.LOX);
        Log.SetDomainSubstitutionRule( "/LOC"        , ""        );   LOG_CHECK( "LOC"  , "</LOC>"                 , ml,Log.LOX);
        Log.SetDomainSubstitutionRule( "/LO"         , "/X"      );   LOG_CHECK( "LOC"  , "</LOC>"                 , ml,Log.LOX);
        Log.SetDomainSubstitutionRule( "/LOCX"       , "/X"      );   LOG_CHECK( "LOC"  , "</LOC>"                 , ml,Log.LOX);

        Log.SetDomainSubstitutionRule( null          , null      );

        // postfix match
        Log.SetDomainSubstitutionRule( null          , null      );
        Log.SetDomainSubstitutionRule( "*/LOC"       , "X"       );   LOG_CHECK( "LOC"  , "</X>"                   , ml,Log.LOX);
        Log.SetDomainSubstitutionRule( "*/LOC"       , ""        );   LOG_CHECK( "LOC"  , "</LOC>"                 , ml,Log.LOX);
        Log.SetDomainSubstitutionRule( "*LOC"        , "X"       );   LOG_CHECK( "LOC"  , "</X>"                   , ml,Log.LOX);
        Log.SetDomainSubstitutionRule( "*LOC"        , ""        );   LOG_CHECK( "LOC"  , "</LOC>"                 , ml,Log.LOX);
        Log.SetDomainSubstitutionRule( "*C"          , "X"       );   LOG_CHECK( "LOC"  , "</LOX>"                 , ml,Log.LOX);
        Log.SetDomainSubstitutionRule( "*C"          , ""        );   LOG_CHECK( "LOC"  , "</LOC>"                 , ml,Log.LOX);

        Log.SetDomainSubstitutionRule( "*C"          , "XY"      );   LOG_CHECK( "LOC/BC" , "</LOC/BXY>"           , ml,Log.LOX);
        Log.SetDomainSubstitutionRule( "*C"          , ""        );   LOG_CHECK( "LOC/BC" , "</LOC/BC>"            , ml,Log.LOX);
        Log.SetDomainSubstitutionRule( "*/BC"        , "/"       );   LOG_CHECK( "LOC/BC" , "</LOC>"               , ml,Log.LOX);
        Log.SetDomainSubstitutionRule( "*/BC"        , ""        );   LOG_CHECK( "LOC/BC" , "</LOC/BC>"            , ml,Log.LOX);
        Log.SetDomainSubstitutionRule( "*C/BC"       , "/VE"     );   LOG_CHECK( "LOC/BC" , "</LO/VE>"             , ml,Log.LOX);

        Log.SetDomainSubstitutionRule( null          , null      );

        // prefix match
        Log.SetDomainSubstitutionRule( "/LOC*"       , "X"       );   LOG_CHECK( "LOC"  , "</X>"                   , ml,Log.LOX);
        Log.SetDomainSubstitutionRule( "/LOC*"       , ""        );   LOG_CHECK( "LOC"  , "</LOC>"                 , ml,Log.LOX);
        Log.SetDomainSubstitutionRule( "/LOC*"       , "/X"      );   LOG_CHECK( "LOC"  , "</X>"                   , ml,Log.LOX);
        Log.SetDomainSubstitutionRule( "/LOC*"       , ""        );   LOG_CHECK( "LOC"  , "</LOC>"                 , ml,Log.LOX);

        Log.SetDomain( "METH", Scope.Filename );           LOG_CHECK( "LOC"  , "</METH/LOC>"              , ml,Log.LOX);
        Log.SetDomainSubstitutionRule( "/LOC*"       , "/X"      );   LOG_CHECK( "LOC"  , "</METH/LOC>"            , ml,Log.LOX);
        Log.SetDomainSubstitutionRule( "/LOC*"       , ""        );   LOG_CHECK( "LOC"  , "</METH/LOC>"            , ml,Log.LOX);
        Log.SetDomainSubstitutionRule( "/METH*"      , "/X"      );   LOG_CHECK( "LOC"  , "</X/LOC>"               , ml,Log.LOX);
        Log.SetDomainSubstitutionRule( "/METH*"      , "/Y"      );   LOG_CHECK( "LOC"  , "</Y/LOC>"               , ml,Log.LOX);
        Log.SetDomainSubstitutionRule( "/METH*"      , "/A/B/C"  );   LOG_CHECK( "LOC"  , "</A/B/C/LOC>"           , ml,Log.LOX);
        Log.SetDomain( "", Scope.Filename );               LOG_CHECK( "LOC"  , "</LOC>"                   , ml,Log.LOX);

        // recursive (just for test, not useful), breaks after 10 recursions
        Log.SetDomainSubstitutionRule( "/R*"        , "/RR"      );   LOG_CHECK( "/REC" , "</RRRRRRRRRRREC>"       , ml,Log.LOX);
                                                                      LOG_CHECK( "/REC" , "</RRRRRRRRRRREC>"       , ml,Log.LOX);
                                                                      LOG_CHECK( "/REC" , "</RRRRRRRRRRREC>"       , ml,Log.LOX);
        Log.SetDomainSubstitutionRule( "/R*"        , "/S"       );   LOG_CHECK( "/R"   , "</S>"                   , ml,Log.LOX);
        Log.SetDomainSubstitutionRule( "/S*"        , "/R"       );   LOG_CHECK( "/R"   , "</R>"                   , ml,Log.LOX);
        Log.SetDomainSubstitutionRule( "/S*"        , "/T"       );   LOG_CHECK( "/R"   , "</T>"                   , ml,Log.LOX);

        //Log.LogConfig( "", Verbosity.Info, "Configuration now is:" );

        // substring rule
        Log.SetDomainSubstitutionRule( "*B*"        , "X"        );   LOG_CHECK( "ABC"  , "</AXC>"                 , ml,Log.LOX);
        Log.SetDomainSubstitutionRule( "*B*"        , ""         );   LOG_CHECK( "ABC"  , "</ABC>"                 , ml,Log.LOX);

        Log.SetDomainSubstitutionRule( "*/ABC*"     , "DEF"      );   LOG_CHECK( "ABC"  , "</DEF>"                 , ml,Log.LOX);
        Log.SetDomainSubstitutionRule( "*EF*"       , "ZZZ"      );   LOG_CHECK( "ABC"  , "</DZZZ>"                , ml,Log.LOX);
        Log.SetDomainSubstitutionRule( "*Z*"        , "@@"       );   LOG_CHECK( "ABC"  , "</D@@@@@@>"             , ml,Log.LOX);

        Log.SetDomainSubstitutionRule( "*/q*"       , "v"        );   LOG_CHECK( "Q"    , "</v>"                   , ml,Log.LOX);

        // delete all rules
        Log.SetDomainSubstitutionRule( null         , null       );   LOG_CHECK( "/_/abc", "</_/abc>"              , ml,Log.LOX);
                                                             LOG_CHECK( "Q"     , "</Q>"                  , ml,Log.LOX);
                                                             LOG_CHECK( "ABC"   , "</ABC>"                , ml,Log.LOX);

        //Log.LogConfig( "", Verbosity.Info, "Configuration now is:" );

        Log.RemoveLogger( ml );
    }
    #endif


    /** ********************************************************************************************
     * Log_DomainSubstitutions_IniFile
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
    public void Log_DomainSubstitutions_IniFile()
    {
        UT_INIT();

        // create ini file
        String iniFileContents=
             "[ALOX]\n"
            +"TESTMEMLOGGER_FORMAT= \"<%D>\"  \n"

            +"MYLOX_DOMAIN_SUBSTITUTION = /A_DOM -> /BETTER_NAME   ;\\ \n"
                         +"    /UI    -> /LIBS/UI    \n"

            +"x\n"
           ;
/* SNIPPIT FOR Dox
//! [Man_DomSubst_Config]
[ALOX]
MYLOX_DOMAIN_SUBSTITUTION= /A_DOM -> /BETTER_NAME   ; \
                           /UI    -> /LIBS/UI
//! [Man_DomSubst_Config]
*/
        String fileName= Environment.CurrentDirectory + "/Log_DomainSubstitutions_IniFile.ini";
        StreamWriter file= new StreamWriter( fileName );
        file.Write( iniFileContents );
        file.Close();

        IniFile iniFile= new IniFile( fileName );
        iniFile.ReadFile();
        //iniFile.WriteFile(); // temporarily enable to see what we have written above

        // add to config
        ALIB.Config.InsertPlugin( iniFile, Configuration.PrioIniFile );

        // create lox, loggers
        Lox myLox= new Lox( "MyLox" ); // name will be upper case
        myLox.SetVerbosity( Lox.CreateConsoleLogger("CONSOLE") , Verbosity.Verbose );
        myLox.SetVerbosity( "CONSOLE"                          , Verbosity.Verbose, ALox.InternalDomains );

// SNIPPIT FOR Dox
#if NEVER_DEFINED
//! [Man_DomSubst_Config_Prevent]
myLox= new Lox( "MyLox" );                      // name will be converted to upper case
myLox.SetDomainSubstitutionRule( null, null );  // clear rules eventually read in constructor
//! [Man_DomSubst_Config_Prevent]
#endif


        MemoryLogger ml= new MemoryLogger("TESTMEMLOGGER");
        myLox.SetVerbosity ( ml, Verbosity.Verbose );

        LOG_CHECK( "DOM"    , "</DOM>"              , ml,myLox);
        LOG_CHECK( "A_DOM"  , "</BETTER_NAME>"      , ml,myLox);
        LOG_CHECK( "UI"     , "</LIBS/UI>"          , ml,myLox);

        //Log.LogConfig( "", Verbosity.Info, "Configuration now is:" );

        ALIB.Config.RemovePlugin( iniFile );
        myLox.RemoveLogger( ml );
        myLox.RemoveLogger( "CONSOLE" );
    }
    #endif //ALOX_DBG_LOG


    /** ********************************************************************************************
     * Log_Domain_IniFile
     **********************************************************************************************/
    #if ALOX_REL_LOG

    #if ALIB_MONO_DEVELOP
        [Test ()]
    #endif
    #if ALIB_VSTUDIO
        [TestMethod]
        #if !WINDOWS_PHONE
            [TestCategory("CS_ALox")]
        #endif
    #endif
    public void Log_Domain_IniFile()
    {
        UT_INIT();

        // Without priorities
        {
            // create iniFile
            IniFile iniFile= new IniFile("*"); // don't read
            iniFile.Save( ALox.ConfigCategoryName, "TESTML_FORMAT","%Sp"   );
            iniFile.Save( ALox.ConfigCategoryName, "T_LOX_TESTML_VERBOSITY",
                             "/DOM_VERB  = VerboseXX  ;" // xx is allowed!
                           + "/DOM_INFO  = Info       ;"
                           + "/DOM_WARN  = WARNING    ;"
                           + "/DOM_ERR   = erRor      ;"
                           + "/DOM_OFF   = off        ;"
                           + "/DOM_OFF2  = xxx        ;"
                           + "/ATSTART*  = Info       ;"
                           + "*ATEND     = Info       ;"
                           + "*SUBSTR*   = Info       ;"
                           + "/OVERWRITE = Info       ;"
                    );
            ALIB.Config.InsertPlugin( iniFile, Configuration.PrioIniFile );


            // test
            Lox lox= new Lox("T_LOX", false);

            lox.SetVerbosity( Lox.CreateConsoleLogger("CONSOLE") , Verbosity.Verbose );
            lox.SetVerbosity( "CONSOLE"                          , Verbosity.Verbose, ALox.InternalDomains );

            // pre-create one of the domains to test if loggers added later get config for existing domains
            lox.Verbose( "DOM_INFO"     , "test" );

            MemoryLogger ml= new MemoryLogger("TESTML");
            lox.SetVerbosity( ml, Verbosity.Off );

            lox.Info   (                  "test" );    UT_EQ(  0, ml.CntLogs ); ml.CntLogs= 0;
            lox.Error  ( "NOSETTING"    , "test" );    UT_EQ(  0, ml.CntLogs ); ml.CntLogs= 0;

            lox.Verbose( "DOM_VERB"     , "test" );    UT_EQ(  1, ml.CntLogs ); ml.CntLogs= 0;

            lox.Verbose( "DOM_INFO"     , "test" );    UT_EQ(  0, ml.CntLogs ); ml.CntLogs= 0;
            lox.Info   ( "DOM_INFO"     , "test" );    UT_EQ(  1, ml.CntLogs ); ml.CntLogs= 0;

            lox.Info   ( "DOM_WARN"     , "test" );    UT_EQ(  0, ml.CntLogs ); ml.CntLogs= 0;
            lox.Warning( "DOM_WARN"     , "test" );    UT_EQ(  1, ml.CntLogs ); ml.CntLogs= 0;

            lox.Warning( "DOM_ERR"      , "test" );    UT_EQ(  0, ml.CntLogs ); ml.CntLogs= 0;
            lox.Error  ( "DOM_ERR"      , "test" );    UT_EQ(  1, ml.CntLogs ); ml.CntLogs= 0;

            lox.Error  ( "DOM_OFF"      , "test" );    UT_EQ(  0, ml.CntLogs ); ml.CntLogs= 0;
            lox.Error  ( "DOM_OFF2"     , "test" );    UT_EQ(  0, ml.CntLogs ); ml.CntLogs= 0;

            lox.Verbose( "ATSTART"      , "test" );    UT_EQ(  0, ml.CntLogs ); ml.CntLogs= 0;
            lox.Info   ( "ATSTART"      , "test" );    UT_EQ(  1, ml.CntLogs ); ml.CntLogs= 0;
            lox.Verbose( "ATSTARTXX"    , "test" );    UT_EQ(  0, ml.CntLogs ); ml.CntLogs= 0;
            lox.Info   ( "ATSTARTXX"    , "test" );    UT_EQ(  1, ml.CntLogs ); ml.CntLogs= 0;
            lox.Verbose( "XXATSTART"    , "test" );    UT_EQ(  0, ml.CntLogs ); ml.CntLogs= 0;
            lox.Info   ( "XXATSTART"    , "test" );    UT_EQ(  0, ml.CntLogs ); ml.CntLogs= 0;
            lox.Verbose( "XATSTARTX"    , "test" );    UT_EQ(  0, ml.CntLogs ); ml.CntLogs= 0;
            lox.Info   ( "XATSTARTX"    , "test" );    UT_EQ(  0, ml.CntLogs ); ml.CntLogs= 0;

            lox.Verbose( "ATEND"        , "test" );    UT_EQ(  0, ml.CntLogs ); ml.CntLogs= 0;
            lox.Info   ( "ATEND"        , "test" );    UT_EQ(  1, ml.CntLogs ); ml.CntLogs= 0;
            lox.Verbose( "ATENDXX"      , "test" );    UT_EQ(  0, ml.CntLogs ); ml.CntLogs= 0;
            lox.Info   ( "ATENDXX"      , "test" );    UT_EQ(  0, ml.CntLogs ); ml.CntLogs= 0;
            lox.Verbose( "XXATEND"      , "test" );    UT_EQ(  0, ml.CntLogs ); ml.CntLogs= 0;
            lox.Info   ( "XXATEND"      , "test" );    UT_EQ(  1, ml.CntLogs ); ml.CntLogs= 0;
            lox.Verbose( "XATENDX"      , "test" );    UT_EQ(  0, ml.CntLogs ); ml.CntLogs= 0;
            lox.Info   ( "XATENDX"      , "test" );    UT_EQ(  0, ml.CntLogs ); ml.CntLogs= 0;

            lox.Verbose( "SUBSTR"       , "test" );    UT_EQ(  0, ml.CntLogs ); ml.CntLogs= 0;
            lox.Info   ( "SUBSTR"       , "test" );    UT_EQ(  1, ml.CntLogs ); ml.CntLogs= 0;
            lox.Verbose( "SUBSTRXX"     , "test" );    UT_EQ(  0, ml.CntLogs ); ml.CntLogs= 0;
            lox.Info   ( "SUBSTRXX"     , "test" );    UT_EQ(  1, ml.CntLogs ); ml.CntLogs= 0;
            lox.Verbose( "XXSUBSTR"     , "test" );    UT_EQ(  0, ml.CntLogs ); ml.CntLogs= 0;
            lox.Info   ( "XXSUBSTR"     , "test" );    UT_EQ(  1, ml.CntLogs ); ml.CntLogs= 0;
            lox.Verbose( "XSUBSTRX"     , "test" );    UT_EQ(  0, ml.CntLogs ); ml.CntLogs= 0;
            lox.Info   ( "XSUBSTRX"     , "test" );    UT_EQ(  1, ml.CntLogs ); ml.CntLogs= 0;

            // overwrite config
            lox.Verbose( "/OVERWRITE"   , "test" );    UT_EQ(  0, ml.CntLogs ); ml.CntLogs= 0;
            lox.Info   ( "/OVERWRITE"   , "test" );    UT_EQ(  1, ml.CntLogs ); ml.CntLogs= 0;

            lox.SetVerbosity( ml , Verbosity.Warning, "/OVERWRITE" ); // does not overwrite
            lox.Verbose( "/OVERWRITE"   , "test" );    UT_EQ(  0, ml.CntLogs ); ml.CntLogs= 0;
            lox.Info   ( "/OVERWRITE"   , "test" );    UT_EQ(  1, ml.CntLogs ); ml.CntLogs= 0;

            lox.SetVerbosity( ml , Verbosity.Warning, "/OVERWRITE", 1000 ); // does overwrite
            lox.Verbose( "/OVERWRITE"   , "test" );    UT_EQ(  0, ml.CntLogs ); ml.CntLogs= 0;
            lox.Info   ( "/OVERWRITE"   , "test" );    UT_EQ(  0, ml.CntLogs ); ml.CntLogs= 0;
            lox.Warning( "/OVERWRITE"   , "test" );    UT_EQ(  1, ml.CntLogs ); ml.CntLogs= 0;

            // overwrite non-config
            lox.Error  ( "/A"           , "test" );    UT_EQ(  0, ml.CntLogs ); ml.CntLogs= 0;
            lox.Error  ( "/A/B"         , "test" );    UT_EQ(  0, ml.CntLogs ); ml.CntLogs= 0;
            lox.Error  ( "/A/C"         , "test" );    UT_EQ(  0, ml.CntLogs ); ml.CntLogs= 0;

            lox.SetVerbosity( ml , Verbosity.Info, "/A/B", Lox.PrioSource -1 ); // does not overwrite
            lox.Verbose( "/A/B"         , "test" );    UT_EQ(  0, ml.CntLogs ); ml.CntLogs= 0;
            lox.Info   ( "/A/B"         , "test" );    UT_EQ(  0, ml.CntLogs ); ml.CntLogs= 0;

            lox.SetVerbosity( ml , Verbosity.Info, "/A/B", Lox.PrioSource ); // does overwrite
            lox.Verbose( "/A/B"         , "test" );    UT_EQ(  0, ml.CntLogs ); ml.CntLogs= 0;
            lox.Info   ( "/A/B"         , "test" );    UT_EQ(  1, ml.CntLogs ); ml.CntLogs= 0;

            lox.SetVerbosity( ml , Verbosity.Info, "/A/B", Lox.PrioSource + 1 ); // one higher
            lox.Verbose( "/A/B"         , "test" );    UT_EQ(  0, ml.CntLogs ); ml.CntLogs= 0;
            lox.Info   ( "/A/B"         , "test" );    UT_EQ(  1, ml.CntLogs ); ml.CntLogs= 0;

            lox.SetVerbosity( ml , Verbosity.Verbose, "/A" );
            lox.Verbose( "/A"           , "test" );    UT_EQ(  1, ml.CntLogs ); ml.CntLogs= 0;
            lox.Verbose( "/A/B"         , "test" );    UT_EQ(  0, ml.CntLogs ); ml.CntLogs= 0;
            lox.Info   ( "/A/B"         , "test" );    UT_EQ(  1, ml.CntLogs ); ml.CntLogs= 0;
            lox.Verbose( "/A/C"         , "test" );    UT_EQ(  1, ml.CntLogs ); ml.CntLogs= 0;

            //lox.LogConfig( "", Verbosity.Info, "Configuration now is:" ); ml.MemoryLog._(); ml.AutoSizes.Reset();

            ALIB.Config.RemovePlugin( iniFile );
            lox.RemoveLogger( ml );
            lox.RemoveLogger( "CONSOLE" );
        }


    }
    #endif //ALOX_REL_LOG

    } // class
} // namespace
