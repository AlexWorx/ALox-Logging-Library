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
using cs.aworx.lib.lang;
using cs.aworx.lib.config;
using System.IO;

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

#if ALOX_DBG_LOG

namespace ut_cs_aworx_lox
{
    class CustomPrefix
    {
        public override String ToString() { return "CUSTOM:"; }
    }



    #if ALIB_NUNIT
        [TestFixture ()]
    #endif
    #if ALIB_IDE_VSTUDIO
        [TestClass]
    #endif
    public class CS_ALox_scopes  : AWorxUnitTesting
    {
        // used with unit test Log_ScopeInfoCacheTest
        public static void ScopeInfoCacheTest() { Log.Info("Test method of CS_ALox_scopes"); }


   void DomainTestThreadRun()
   {
       Log.Info( "DTT", "" );
   }
   void DomainTestThreadRun_RL( Object lox )
   {
       ((Lox)lox).Info( "DTT", "" );
   }

   void LogOnceTestThreadRun()
   {
        Log.Once( Verbosity.Info, "Once(Scope.ThreadOuter) 2x - 2nd thread", Scope.ThreadOuter, 0, 2 );
        Log.Once( Verbosity.Info, "Once(Scope.ThreadOuter) 2x - 2nd thread", Scope.ThreadOuter, 0, 2 );
        Log.Once( Verbosity.Info, "Once(Scope.ThreadOuter) 2x - 2nd thread", Scope.ThreadOuter, 0, 2 );
        Log.Once( Verbosity.Info, "Once(Scope.ThreadOuter) 2x - 2nd thread", Scope.ThreadOuter, 0, 2 );
   }

   void StoreDataTestThreadRun()
   {
        #if ALOX_DBG_LOG
            Object data= null;
        #endif

        Log.Store( "2nd Thread Data"       ,             Scope.ThreadOuter   );
        Log.Store( "2nd Thread Data, keyed",   "mykey",  Scope.ThreadOuter   );

        #if ALOX_DBG_LOG
            data= Log.Retrieve(          Scope.ThreadOuter ); UT_EQ( "2nd Thread Data"        , (String) data );
            data= Log.Retrieve( "mykey", Scope.ThreadOuter ); UT_EQ( "2nd Thread Data, keyed" , (String) data );
        #endif
   }

    /** ********************************************************************************************
     * Log_Prefix
     **********************************************************************************************/
    void PFXCHECK( String exp, MemoryLogger ml )
    {
        UT_EQ( exp  , ml.MemoryLog );
        ml.MemoryLog._();
        ml.AutoSizes.Reset();
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
    public void Log_Prefix()
    {
        UT_INIT();

        // we have tell alox to include more directories in the scope path
        Log.ClearSourcePathTrimRules( Reach.Global, false );
        Log.SetSourcePathTrimRule( "*/alox/src.cs/", Inclusion.Exclude );

        CustomPrefix custom1= new CustomPrefix();
        CustomPrefix custom2= new CustomPrefix();

        Log.AddDebugLogger();
        MemoryLogger ml= new MemoryLogger();
        ml.MetaInfo.Format._();
        Log.SetVerbosity(ml, Verbosity.Verbose );
        Log.SetVerbosity(Log.DebugLogger, Verbosity.Verbose, ALox.InternalDomains );
        Log.SetDomain( "/PREFIX", Scope.Method );

//! [DOX_ALOX_LOX_SETPREFIX]
Log.SetPrefix( new Object[] {"One, ", "two, ", 3 },  Scope.Global   );
//! [DOX_ALOX_LOX_SETPREFIX]
Log.Info( "*msg*" ); PFXCHECK( "One, two, 3*msg*"    ,ml );


        // src scopes
        Log.SetPrefix( "REPLACE:",    Scope.Global      );  Log.Info( "*msg*" ); PFXCHECK( "REPLACE:*msg*"          ,ml );
        Log.SetPrefix( "GLOBAL:",     Scope.Global      );  Log.Info( "*msg*" ); PFXCHECK( "GLOBAL:*msg*"           ,ml );
        Log.SetPrefix( null   ,       Scope.Global      );  Log.Info( "*msg*" ); PFXCHECK( "*msg*"                  ,ml );
        Log.SetPrefix( "REPLACE:",    Scope.Filename    );  Log.Info( "*msg*" ); PFXCHECK( "REPLACE:*msg*"          ,ml );
        Log.SetPrefix( "FILE:",       Scope.Filename    );  Log.Info( "*msg*" ); PFXCHECK( "FILE:*msg*"             ,ml );
        Log.SetPrefix( "REPLACE:",    Scope.Method      );  Log.Info( "*msg*" ); PFXCHECK( "FILE:REPLACE:*msg*"     ,ml );
        Log.SetPrefix( "METHOD:",     Scope.Method      );  Log.Info( "*msg*" ); PFXCHECK( "FILE:METHOD:*msg*"      ,ml );

        Log.SetPrefix( null   ,       Scope.Method      );  Log.Info( "*msg*" ); PFXCHECK( "FILE:*msg*"             ,ml );
        Log.SetPrefix( "METHOD:",     Scope.Method      );  Log.Info( "*msg*" ); PFXCHECK( "FILE:METHOD:*msg*"      ,ml );

        // set custom
        Log.SetPrefix( null   ,       Scope.Method      );  Log.Info( "*msg*" ); PFXCHECK( "FILE:*msg*"             ,ml );
        Log.SetPrefix( custom1  ,     Scope.Method      );  Log.Info( "*msg*" ); PFXCHECK( "FILE:CUSTOM:*msg*"      ,ml );
        Log.SetPrefix( custom1  ,     Scope.Method      );  Log.Info( "*msg*" ); PFXCHECK( "FILE:CUSTOM:*msg*"      ,ml );
        Log.SetPrefix( custom2  ,     Scope.Method      );  Log.Info( "*msg*" ); PFXCHECK( "FILE:CUSTOM:*msg*"      ,ml );
        Log.SetPrefix( null   ,       Scope.Method      );  Log.Info( "*msg*" ); PFXCHECK( "FILE:*msg*"             ,ml );
        Log.SetPrefix( custom1  ,     Scope.Method      );  Log.Info( "*msg*" ); PFXCHECK( "FILE:CUSTOM:*msg*"      ,ml );
        Log.SetPrefix( "METHOD:",     Scope.Method      );  Log.Info( "*msg*" ); PFXCHECK( "FILE:METHOD:*msg*"      ,ml );
        Log.SetPrefix( "METHOD:",     Scope.Method      );  Log.Info( "*msg*" ); PFXCHECK( "FILE:METHOD:*msg*"      ,ml );

        // domain related
        Log.SetPrefix( "DOM1:" );                           Log.Info( "*msg*" ); PFXCHECK( "FILE:METHOD:DOM1:*msg*"            ,ml );
        Log.SetPrefix( new Object[] {"DO","M2:"} );         Log.Info( "*msg*" ); PFXCHECK( "FILE:METHOD:DOM1:DOM2:*msg*"       ,ml );
        Log.SetPrefix( "DOM3:" );                           Log.Info( "*msg*" ); PFXCHECK( "FILE:METHOD:DOM1:DOM2:DOM3:*msg*"  ,ml );
        Log.SetPrefix( ""      );                           Log.Info( "*msg*" ); PFXCHECK( "FILE:METHOD:DOM1:DOM2:*msg*"       ,ml );
        Log.SetPrefix( ""      );                           Log.Info( "*msg*" ); PFXCHECK( "FILE:METHOD:DOM1:*msg*"            ,ml );
        Log.SetPrefix( "DOMR:", "/" );                      Log.Info( "*msg*" ); PFXCHECK( "FILE:METHOD:DOMR:DOM1:*msg*"       ,ml );
        Log.SetPrefix( "DOMX:", "", Inclusion.Exclude );    Log.Info( "*msg*" ); PFXCHECK( "DOMX:*msg*"                        ,ml );
        Log.SetPrefix( ""      );                           Log.Info( "*msg*" ); PFXCHECK( "FILE:METHOD:DOMR:DOM1:*msg*"       ,ml );
        Log.SetPrefix( "DRX:", "/", Inclusion.Exclude );    Log.Info( "*msg*" ); PFXCHECK( "DRX:DOM1:*msg*"                    ,ml );
        Log.SetPrefix( ""    , "/"  );                      Log.Info( "*msg*" ); PFXCHECK( "FILE:METHOD:DOMR:DOM1:*msg*"       ,ml );

        // source path
        Log.SetPrefix( "REPLACE:",    Scope.Path        );  Log.Info( "*msg*" ); PFXCHECK( "REPLACE:FILE:METHOD:DOMR:DOM1:*msg*"         ,ml );
        Log.SetPrefix( "PATH:",       Scope.Path        );  Log.Info( "*msg*" ); PFXCHECK( "PATH:FILE:METHOD:DOMR:DOM1:*msg*"            ,ml );
        Log.SetPrefix( "REPLACE:",    Scope.Path, 1     );  Log.Info( "*msg*" ); PFXCHECK( "REPLACE:PATH:FILE:METHOD:DOMR:DOM1:*msg*"    ,ml );
        Log.SetPrefix( "PO1:",        Scope.Path, 1     );  Log.Info( "*msg*" ); PFXCHECK( "PO1:PATH:FILE:METHOD:DOMR:DOM1:*msg*"        ,ml );
        Log.SetPrefix( "REPLACE:",    Scope.Path, 2     );  Log.Info( "*msg*" ); PFXCHECK( "REPLACE:PO1:PATH:FILE:METHOD:DOMR:DOM1:*msg*",ml );
        Log.SetPrefix( "PO2:",        Scope.Path, 2     );  Log.Info( "*msg*" ); PFXCHECK( "PO2:PO1:PATH:FILE:METHOD:DOMR:DOM1:*msg*"    ,ml );
        Log.SetPrefix( "REPLACE:",    Scope.Global      );  Log.Info( "*msg*" ); PFXCHECK( "REPLACE:PO2:PO1:PATH:FILE:METHOD:DOMR:DOM1:*msg*"  , ml );

        // remove all previous scope domains
        Log.SetPrefix( null          ,Scope.Global      );
        Log.SetPrefix( null          ,Scope.Path        );
        Log.SetPrefix( null          ,Scope.Path    ,1  );
        Log.SetPrefix( null          ,Scope.Path    ,2  );
        Log.SetPrefix( null          ,Scope.Filename    );
        Log.SetPrefix( null          ,Scope.Method      );

        Log.SetPrefix( null      ); // domain "/PREFIX"
        Log.SetPrefix( null      ); // domain "/PREFIX" nothing here any more
        Log.SetPrefix( null, "/" ); // domain "/"
                                                            Log.Info( "*msg*" ); PFXCHECK( "*msg*"                        ,ml );

        // Thread-related
        Log.SetPrefix( "TO:"         ,Scope.ThreadOuter );  Log.Info( "*msg*" ); PFXCHECK( "TO:*msg*"                     ,ml );
        Log.SetPrefix( "GL:"         ,Scope.Global      );  Log.Info( "*msg*" ); PFXCHECK( "GL:TO:*msg*"                  ,ml );
        Log.SetPrefix( "MET:"        ,Scope.Method      );  Log.Info( "*msg*" ); PFXCHECK( "GL:TO:MET:*msg*"              ,ml );
        Log.SetPrefix( ":TI"         ,Scope.ThreadInner );  Log.Info( "*msg*" ); PFXCHECK( "GL:TO:MET:*msg*:TI"           ,ml );

        Log.SetPrefix( "TO2:"        ,Scope.ThreadOuter );  Log.Info( "*msg*" ); PFXCHECK( "GL:TO:TO2:MET:*msg*:TI"       ,ml );
        Log.SetPrefix( ":TI2"        ,Scope.ThreadInner );  Log.Info( "*msg*" ); PFXCHECK( "GL:TO:TO2:MET:*msg*:TI:TI2"   ,ml );

        Log.SetPrefix( "TO3:"        ,Scope.ThreadOuter );  Log.Info( "*msg*" ); PFXCHECK( "GL:TO:TO2:TO3:MET:*msg*:TI:TI2"    ,ml );
        Log.SetPrefix( ":TI3"        ,Scope.ThreadInner );  Log.Info( "*msg*" ); PFXCHECK( "GL:TO:TO2:TO3:MET:*msg*:TI:TI2:TI3",ml );


        Log.SetPrefix( null          ,Scope.ThreadInner );  Log.Info( "*msg*" ); PFXCHECK( "GL:TO:TO2:TO3:MET:*msg*:TI:TI2"    ,ml );
        Log.SetPrefix( null          ,Scope.ThreadInner );  Log.Info( "*msg*" ); PFXCHECK( "GL:TO:TO2:TO3:MET:*msg*:TI"   ,ml );
        Log.SetPrefix( null          ,Scope.ThreadOuter );  Log.Info( "*msg*" ); PFXCHECK( "GL:TO:TO2:MET:*msg*:TI"       ,ml );
        Log.SetPrefix( null          ,Scope.ThreadOuter );  Log.Info( "*msg*" ); PFXCHECK( "GL:TO:MET:*msg*:TI"           ,ml );
        Log.SetPrefix( null          ,Scope.ThreadOuter );  Log.Info( "*msg*" ); PFXCHECK( "GL:MET:*msg*:TI"              ,ml );
        Log.SetPrefix( null          ,Scope.Global      );  Log.Info( "*msg*" ); PFXCHECK( "MET:*msg*:TI"                 ,ml );
        Log.SetPrefix( null          ,Scope.Method      );  Log.Info( "*msg*" ); PFXCHECK( "*msg*:TI"                     ,ml );
        Log.SetPrefix( null          ,Scope.ThreadInner );  Log.Info( "*msg*" ); PFXCHECK( "*msg*"                        ,ml );

        // check if breaking dom-related, removes all thread inner correctly
        Log.SetPrefix( ":TI"         ,Scope.ThreadInner );  Log.Info( "*msg*" ); PFXCHECK( "*msg*:TI"                  ,ml );
        Log.SetPrefix( "DOM1:", ""   ,Inclusion.Include );  Log.Info( "*msg*" ); PFXCHECK( "DOM1:*msg*:TI"             ,ml );
        Log.SetPrefix( "DOMX:", ""   ,Inclusion.Exclude );  Log.Info( "*msg*" ); PFXCHECK( "DOMX:*msg*"                ,ml );
        Log.SetPrefix( ":TI"         ,Scope.ThreadInner );  Log.Info( "*msg*" ); PFXCHECK( "DOMX:*msg*"                ,ml );
        Log.SetPrefix( null, ""                         );  Log.Info( "*msg*" ); PFXCHECK( "DOM1:*msg*:TI:TI"          ,ml );

        Log.RemoveLogger( ml );
    }
    #endif

    /** ********************************************************************************************
     * Log_ScopeDomains
     **********************************************************************************************/
    void LSD()      {  Log.SetDomain( "LSD",  Scope.Method );    Log.Info( "" );    }
    void LSD_A()    {  Log.SetDomain( "A",    Scope.Method );    Log.Info( "" );    }
    void LSD_A_B()  {  Log.SetDomain( "B",    Scope.Method );    Log.Info( "" );    }
    void LSD2_A_B() {  Log.SetDomain( "B2",   Scope.Method );    Log.Info( "" );    }
    void LSD2_A()   {  Log.SetDomain( "A2",   Scope.Method );    Log.Info( "" );    }
    void LSD2()     {  Log.SetDomain( "LSD2", Scope.Method );    Log.Info( "" );    }

    void SDCHECK( String exp, MemoryLogger ml )
    {
        UT_EQ( exp  , ml.MemoryLog );
        ml.MemoryLog._();
        ml.AutoSizes.Reset();
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
    public void Log_ScopeDomains()
    {
        UT_INIT();

        // we have tell alox to include more directories in the scope path
        Log.ClearSourcePathTrimRules( Reach.Global, false);
        Log.SetSourcePathTrimRule( "*/alox/src.cs/", Inclusion.Exclude );

        Log.AddDebugLogger();
        MemoryLogger ml= new MemoryLogger();
        ml.MetaInfo.Format._()._("@%D#");
        Log.SetVerbosity( ml, Verbosity.Verbose );
        Log.SetVerbosity(Log.DebugLogger, Verbosity.Verbose, ALox.InternalDomains );


        // test methods with extending names
        LSD();         UT_EQ( "@/LSD#",      ml.MemoryLog );   ml.MemoryLog._(); ml.AutoSizes.Reset();
        LSD_A();       UT_EQ( "@/A#",        ml.MemoryLog );   ml.MemoryLog._(); ml.AutoSizes.Reset();
        LSD_A_B();     UT_EQ( "@/B#",        ml.MemoryLog );   ml.MemoryLog._(); ml.AutoSizes.Reset();
        LSD2_A_B();    UT_EQ( "@/B2#",       ml.MemoryLog );   ml.MemoryLog._(); ml.AutoSizes.Reset();
        LSD2_A();      UT_EQ( "@/A2#",       ml.MemoryLog );   ml.MemoryLog._(); ml.AutoSizes.Reset();
        LSD2();        UT_EQ( "@/LSD2#",     ml.MemoryLog );   ml.MemoryLog._(); ml.AutoSizes.Reset();

        // scope global
        Log.SetDomain( "REPLACE",    Scope.Global    );  Log.Info( "" ); SDCHECK( "@/REPLACE#"                    ,ml );
        Log.SetDomain( "GLOBAL",     Scope.Global    );  Log.Info( "" ); SDCHECK( "@/GLOBAL#"                     ,ml );

        Log.SetDomain( null,         Scope.Global    );  Log.Info( "" ); SDCHECK( "@/#"                           ,ml );

        // scope source
        Log.SetDomain( "REPLACE",    Scope.Filename  );  Log.Info( "" ); SDCHECK( "@/REPLACE#"                    ,ml );
        Log.SetDomain( "FILE",       Scope.Filename  );  Log.Info( "" ); SDCHECK( "@/FILE#"                       ,ml );

        // scope method
        Log.SetDomain( "REPLACE",    Scope.Method    );  Log.Info( "" ); SDCHECK( "@/FILE/REPLACE#"               ,ml );
        Log.SetDomain( "METHOD",     Scope.Method    );  Log.Info( "" ); SDCHECK( "@/FILE/METHOD#"                ,ml );
        Log.SetDomain( "/ABS",       Scope.Method    );  Log.Info( "" ); SDCHECK( "@/ABS#"                        ,ml );

        // unset method with null
        Log.SetDomain( null,         Scope.Method    );  Log.Info( "" ); SDCHECK( "@/FILE#"                       ,ml );

        // unset method with ""
        Log.SetDomain( "/METHOD",    Scope.Method    );  Log.Info( "" ); SDCHECK( "@/METHOD#"                     ,ml );
        Log.SetDomain( "",           Scope.Method    );  Log.Info( "" ); SDCHECK( "@/FILE#"                       ,ml );
        Log.SetDomain( "METHOD",     Scope.Method    );  Log.Info( "" ); SDCHECK( "@/FILE/METHOD#"                ,ml );

        // source path
        Log.SetDomain( "REPLACE",    Scope.Path      );  Log.Info( "" ); SDCHECK( "@/REPLACE/FILE/METHOD#"        ,ml );
        Log.SetDomain( "PATH",       Scope.Path      );  Log.Info( "" ); SDCHECK( "@/PATH/FILE/METHOD#"           ,ml );
        Log.SetDomain( "REPLACE",    Scope.Path, 1   );  Log.Info( "" ); SDCHECK( "@/REPLACE/PATH/FILE/METHOD#"   ,ml );
        Log.SetDomain( "PO1",        Scope.Path, 1   );  Log.Info( "" ); SDCHECK( "@/PO1/PATH/FILE/METHOD#"       ,ml );
        Log.SetDomain( "REPLACE",    Scope.Path, 2   );  Log.Info( "" ); SDCHECK( "@/REPLACE/PO1/PATH/FILE/METHOD#",ml);
        Log.SetDomain( "PO2",        Scope.Path, 2   );  Log.Info( "" ); SDCHECK( "@/PO2/PO1/PATH/FILE/METHOD#"   ,ml );
        Log.SetDomain( "PO50",       Scope.Path, 50  );  Log.Info( "" ); SDCHECK( "@/PO50/PO2/PO1/PATH/FILE/METHOD#"   ,ml );

        Log.SetDomain( "GLOBAL",     Scope.Global         );  Log.Info( "" );          SDCHECK( "@/GLOBAL/PO50/PO2/PO1/PATH/FILE/METHOD#"  , ml );
                                                                 CS_ALox_domains_helper.help(); SDCHECK( "@/GLOBAL/PO50/PO2/PO1/PATH/HFILE/HMETHOD#", ml );
                                                                         Log.Info( "" );        SDCHECK( "@/GLOBAL/PO50/PO2/PO1/PATH/FILE/METHOD#"  , ml );

        //Log.State( "", Verbosity.Info, "Configuration now is:" ); ml.MemoryLog._(); ml.AutoSizes.Reset();

        // remove all previous scope domains
        Log.SetDomain( "",     Scope.Global      );
        Log.SetDomain( "",     Scope.Path        );
        Log.SetDomain( "",     Scope.Path    ,1  );
        Log.SetDomain( "",     Scope.Path    ,2  );
        Log.SetDomain( "",     Scope.Path    ,45 ); // same as 50 above! (test)
        Log.SetDomain( "",     Scope.Filename    );
        Log.SetDomain( "",     Scope.Method      );  Log.Info(  "LOC", "" ); SDCHECK( "@/LOC#"                 ,ml );

        // Thread-related
        Log.SetDomain( "T_O",  Scope.ThreadOuter );  Log.Info(  ""   , "" ); SDCHECK( "@/T_O#"                 ,ml );
        Log.SetDomain( "GL",   Scope.Global      );  Log.Info(  ""   , "" ); SDCHECK( "@/GL/T_O#"              ,ml );
        Log.SetDomain( "MET",  Scope.Method      );  Log.Info(  ""   , "" ); SDCHECK( "@/GL/T_O/MET#"          ,ml );
        Log.SetDomain( "MET",  Scope.Method      );  Log.Info(  "LOC", "" ); SDCHECK( "@/GL/T_O/MET/LOC#"      ,ml );
        Log.SetDomain( "T_I",  Scope.ThreadInner );  Log.Info(  ""   , "" ); SDCHECK( "@/GL/T_O/MET/T_I#"      ,ml );

                                                              Log.Info(  "LOC", "" ); SDCHECK( "@/GL/T_O/MET/LOC/T_I#"  ,ml );
        Log.SetDomain( "T_O2", Scope.ThreadOuter );  Log.Info(  ""   , "" ); SDCHECK( "@/GL/T_O/T_O2/MET/T_I#" ,ml );
        Log.SetDomain( "T_I2", Scope.ThreadInner );  Log.Info(  ""   , "" ); SDCHECK( "@/GL/T_O/T_O2/MET/T_I/T_I2#" ,ml );

        Log.SetDomain( "/T_O3",Scope.ThreadOuter );  Log.Info(  ""   , "" ); SDCHECK( "@/T_O3/MET/T_I/T_I2#"   ,ml );
        Log.SetDomain( "/T_I3",Scope.ThreadInner );  Log.Info(  ""   , "" ); SDCHECK( "@/T_I3#"                ,ml );

        Log.SetDomain         ( ""     ,Scope.ThreadInner );  Log.Info(  ""   , "" ); SDCHECK( "@/T_O3/MET/T_I/T_I2#"   ,ml );
        Log.RemoveThreadDomain( "T_IXX",Scope.ThreadInner );  Log.Info(  ""   , "" ); SDCHECK( "@/T_O3/MET/T_I/T_I2#"   ,ml );
        Log.RemoveThreadDomain( "T_I"  ,Scope.ThreadInner );  Log.Info(  ""   , "" ); SDCHECK( "@/T_O3/MET/T_I2#"       ,ml );
        Log.RemoveThreadDomain( ""     ,Scope.ThreadInner );  Log.Info(  ""   , "" ); SDCHECK( "@/T_O3/MET/T_I2#"       ,ml );
        Log.SetDomain         ( ""     ,Scope.ThreadInner );  Log.Info(  ""   , "" ); SDCHECK( "@/T_O3/MET#"            ,ml );
        Log.SetDomain         ( ""     ,Scope.ThreadOuter );  Log.Info(  ""   , "" ); SDCHECK( "@/GL/T_O/T_O2/MET#"     ,ml );
        Log.SetDomain         ( "T_O3", Scope.ThreadOuter );  Log.Info(  ""   , "" ); SDCHECK( "@/GL/T_O/T_O2/T_O3/MET#",ml );
        Log.RemoveThreadDomain( "T_O2" ,Scope.ThreadOuter );  Log.Info(  ""   , "" ); SDCHECK( "@/GL/T_O/T_O3/MET#"     ,ml );
        Log.RemoveThreadDomain( "T_O"  ,Scope.ThreadOuter );  Log.Info(  ""   , "" ); SDCHECK( "@/GL/T_O3/MET#"         ,ml );
        Log.SetDomain         ( ""     ,Scope.ThreadOuter );  Log.Info(  ""   , "" ); SDCHECK( "@/GL/MET#"              ,ml );
        Log.SetDomain         ( ""     ,Scope.Global      );  Log.Info(  ""   , "" ); SDCHECK( "@/MET#"                 ,ml );
        Log.SetDomain         ( ""     ,Scope.Method      );  Log.Info(  ""   , "" ); SDCHECK( "@/#"                    ,ml );

        // second thread
        Thread thread= new Thread( new ThreadStart( DomainTestThreadRun ) );

        Log.SetDomain( "THIS_THREAD",   Scope.ThreadOuter );
        Log.SetDomain( "OTHER_THREAD",  Scope.ThreadOuter, thread );
        thread.Start();
        while( thread.IsAlive )
            ALIB.SleepMillis(1);
                               UT_EQ( "@/OTHER_THREAD/DTT#", ml.MemoryLog );  ml.MemoryLog._(); ml.AutoSizes.Reset();
        Log.Info( "ME", "" );  UT_EQ( "@/THIS_THREAD/ME#"  , ml.MemoryLog );  ml.MemoryLog._(); ml.AutoSizes.Reset();

        //Log.State( "", Verbosity.Info, "Configuration now is:" ); ml.MemoryLog._(); ml.AutoSizes.Reset();
    }
    #endif

    /** ********************************************************************************************
     * Lox_ScopeDomains
     **********************************************************************************************/
    void SDCHECK_RL( String exp, MemoryLogger ml )
    {
        UT_EQ( exp  , ml.MemoryLog );
        ml.MemoryLog._();
        ml.AutoSizes.Reset();
    }

    void CICHECK_RL( String exp, MemoryLogger ml ) // no caller info, we don't check
    {
        ml.MemoryLog._();
        ml.AutoSizes.Reset();
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
    public void Lox_ScopeDomains()
    {
        UT_INIT();

        // we have tell alox to include more directories in the scope path
        Log.ClearSourcePathTrimRules( Reach.Global, false);
        Log.SetSourcePathTrimRule( "*/alox/src.cs/", Inclusion.Exclude );

        Lox lox= new Lox( "ReleaseLox" );
        TextLogger consoleLogger= Lox.CreateConsoleLogger();
        MemoryLogger ml= new MemoryLogger();
        ml.MetaInfo.Format._()._("@%D#");
        lox.SetVerbosity(ml, Verbosity.Verbose );

        lox.SetVerbosity(consoleLogger, Verbosity.Verbose );
        lox.SetVerbosity(consoleLogger, Verbosity.Verbose, ALox.InternalDomains );

        // scope global
        lox.SetDomain( "REPLACE",    Scope.Global   );  lox.Info(  ""   , "" ); SDCHECK_RL( "@/REPLACE#"                     ,ml );
        lox.SetDomain( "GLOBAL",     Scope.Global   );  lox.Info(  ""   , "" ); SDCHECK_RL( "@/GLOBAL#"                      ,ml );

        lox.SetDomain( null,         Scope.Global   );  lox.Info(  ""   , "" ); SDCHECK_RL( "@/#"                            ,ml );

        // scope source
        lox.SetDomain( "REPLACE",    Scope.Filename );  lox.Info(  ""   , "" ); CICHECK_RL( "@/REPLACE#"                     ,ml );
        lox.SetDomain( "FILE",       Scope.Filename );  lox.Info(  ""   , "" ); CICHECK_RL( "@/FILE#"                        ,ml );

        // scope method
        lox.SetDomain( "REPLACE",    Scope.Method   );  lox.Info(  ""   , "" ); CICHECK_RL( "@/FILE/REPLACE#"                ,ml );
        lox.SetDomain( "Method",     Scope.Method   );  lox.Info(  ""   , "" ); CICHECK_RL( "@/FILE/METHOD#"                 ,ml );
        lox.SetDomain( "/ABS",       Scope.Method   );  lox.Info(  ""   , "" ); CICHECK_RL( "@/ABS#"                         ,ml );

        // unset method with null
        lox.SetDomain( null,         Scope.Method   );  lox.Info(  ""   , "" ); CICHECK_RL( "@/FILE#"                        ,ml );

        // unset method with ""
        lox.SetDomain( "/METHOD",    Scope.Method   );  lox.Info(  ""   , "" ); CICHECK_RL( "@/METHOD#"                      ,ml );
        lox.SetDomain( "",           Scope.Method   );  lox.Info(  ""   , "" ); CICHECK_RL( "@/FILE#"                        ,ml );
        lox.SetDomain( "Method",     Scope.Method   );  lox.Info(  ""   , "" ); CICHECK_RL( "@/FILE/METHOD#"                 ,ml );

        // source path
        lox.SetDomain( "REPLACE",    Scope.Path     );  lox.Info(  ""   , "" ); CICHECK_RL( "@/REPLACE/FILE/METHOD#"         ,ml );
        lox.SetDomain( "PATH",       Scope.Path     );  lox.Info(  ""   , "" ); CICHECK_RL( "@/PATH/FILE/METHOD#"            ,ml );
        lox.SetDomain( "REPLACE",    Scope.Path, 1  );  lox.Info(  ""   , "" ); CICHECK_RL( "@/REPLACE/PATH/FILE/METHOD#"    ,ml );
        lox.SetDomain( "PO1",        Scope.Path, 1  );  lox.Info(  ""   , "" ); CICHECK_RL( "@/PO1/PATH/FILE/METHOD#"        ,ml );
        lox.SetDomain( "REPLACE",    Scope.Path, 2  );  lox.Info(  ""   , "" ); CICHECK_RL( "@/REPLACE/PO1/PATH/FILE/METHOD#",ml );
        lox.SetDomain( "PO2",        Scope.Path, 2  );  lox.Info(  ""   , "" ); CICHECK_RL( "@/PO2/PO1/PATH/FILE/METHOD#"    ,ml );

        lox.SetDomain( "GLOBAL",     Scope.Global   );  lox.Info(  ""   , "" ); CICHECK_RL( "@/GLOBAL/PO2/PO1/PATH/FILE/METHOD#"  , ml );


        // remove all previous scope domains
        lox.SetDomain( "",     Scope.Global      );
        lox.SetDomain( "",     Scope.Path        );
        lox.SetDomain( "",     Scope.Path    ,1  );
        lox.SetDomain( "",     Scope.Path    ,2  );
        lox.SetDomain( "",     Scope.Filename    );
        lox.SetDomain( "",     Scope.Method      );  lox.Info(  "LOC", "" ); SDCHECK_RL(  "@/LOC#"                ,ml );

        // Thread-related
        lox.SetDomain( "T_O",  Scope.ThreadOuter );  lox.Info(  ""   , "" ); SDCHECK_RL( "@/T_O#"                 ,ml );
        lox.SetDomain( "GL",   Scope.Global      );  lox.Info(  ""   , "" ); SDCHECK_RL( "@/GL/T_O#"              ,ml );
        lox.SetDomain( "MET",  Scope.Method      );  lox.Info(  ""   , "" ); CICHECK_RL( "@/GL/T_O/MET#"          ,ml );
                                                              lox.Info(  "LOC", "" ); CICHECK_RL( "@/GL/T_O/MET/LOC#"      ,ml );
        lox.SetDomain( "T_I",  Scope.ThreadInner );  lox.Info(  ""   , "" ); CICHECK_RL( "@/GL/T_O/MET/T_I#"      ,ml );
                                                              lox.Info(  "LOC", "" ); CICHECK_RL( "@/GL/T_O/MET/LOC/T_I#"  ,ml );
        lox.SetDomain( "T_O2", Scope.ThreadOuter );  lox.Info(  ""   , "" ); CICHECK_RL( "@/GL/T_O/T_O2/MET/T_I#" ,ml );
        lox.SetDomain( "T_I2", Scope.ThreadInner );  lox.Info(  ""   , "" ); CICHECK_RL( "@/GL/T_O/T_O2/MET/T_I/T_I2#" ,ml );

        lox.SetDomain( "/T_O3",Scope.ThreadOuter );  lox.Info(  ""   , "" ); CICHECK_RL( "@/T_O3/MET/T_I/T_I2#"   ,ml );
        lox.SetDomain( "/T_I3",Scope.ThreadInner );  lox.Info(  ""   , "" ); SDCHECK_RL( "@/T_I3#"                ,ml );
        lox.SetDomain( "",     Scope.Method      );  lox.Info(  ""   , "" ); SDCHECK_RL( "@/T_I3#"                ,ml );

        lox.SetDomain         ( ""     ,Scope.ThreadInner );  lox.Info(  ""   , "" ); SDCHECK_RL( "@/T_O3/T_I/T_I2#"   ,ml );
        lox.RemoveThreadDomain( "T_IXX",Scope.ThreadInner );  lox.Info(  ""   , "" ); SDCHECK_RL( "@/T_O3/T_I/T_I2#"   ,ml );
        lox.RemoveThreadDomain( "T_I"  ,Scope.ThreadInner );  lox.Info(  ""   , "" ); SDCHECK_RL( "@/T_O3/T_I2#"       ,ml );
        lox.RemoveThreadDomain( ""     ,Scope.ThreadInner );  lox.Info(  ""   , "" ); SDCHECK_RL( "@/T_O3/T_I2#"       ,ml );
        lox.SetDomain         ( ""     ,Scope.ThreadInner );  lox.Info(  ""   , "" ); SDCHECK_RL( "@/T_O3#"            ,ml );
        lox.SetDomain         ( ""     ,Scope.ThreadOuter );  lox.Info(  ""   , "" ); SDCHECK_RL( "@/GL/T_O/T_O2#"     ,ml );
        lox.SetDomain         ( "T_O3", Scope.ThreadOuter );  lox.Info(  ""   , "" ); SDCHECK_RL( "@/GL/T_O/T_O2/T_O3#",ml );
        lox.RemoveThreadDomain( "T_O2" ,Scope.ThreadOuter );  lox.Info(  ""   , "" ); SDCHECK_RL( "@/GL/T_O/T_O3#"     ,ml );
        lox.RemoveThreadDomain( "T_O"  ,Scope.ThreadOuter );  lox.Info(  ""   , "" ); SDCHECK_RL( "@/GL/T_O3#"         ,ml );
        lox.SetDomain         ( ""     ,Scope.ThreadOuter );  lox.Info(  ""   , "" ); SDCHECK_RL( "@/GL#"              ,ml );
        lox.SetDomain         ( ""     ,Scope.Global      );  lox.Info(  ""   , "" ); SDCHECK_RL( "@/#"                 ,ml );


        // second thread
        Thread thread= new Thread( new ParameterizedThreadStart( DomainTestThreadRun_RL ) );
        lox.SetDomain( "THIS_THREAD",   Scope.ThreadOuter );
        lox.SetDomain( "OTHER_THREAD",  Scope.ThreadOuter, thread );
        thread.Start( lox );
        while( thread.IsAlive )
            ALIB.SleepMillis(1);
                               UT_EQ( "@/OTHER_THREAD/DTT#", ml.MemoryLog );  ml.MemoryLog._(); ml.AutoSizes.Reset();
        lox.Info( "ME", "" );  UT_EQ( "@/THIS_THREAD/ME#"  , ml.MemoryLog );  ml.MemoryLog._(); ml.AutoSizes.Reset();

        // cleanup
        lox.RemoveLogger( consoleLogger );
        lox.RemoveLogger( ml );
    }
    #endif

    /** ********************************************************************************************
     * Log.Once
     **********************************************************************************************/
    void logOnceMethod()
    {
        Log.Once( Verbosity.Info, "Once(Scope filename) 4x -from other method", Scope.Filename, 0, 4 );
    }

    #if ALIB_NUNIT
        [Test ()]
    #endif
    #if ALIB_IDE_VSTUDIO
        [TestMethod]
        #if !WINDOWS_PHONE
            [TestCategory("CS_ALox")]
        #endif
    #endif
    public void Log_LogOnce()
    {
        UT_INIT();

        Log.AddDebugLogger();
            MemoryLogger ml= new MemoryLogger();
        Log.SetVerbosity ( ml, Verbosity.Verbose );
        Log.SetVerbosity( Log.DebugLogger,  Verbosity.Verbose, ALox.InternalDomains );
        Log.SetDomain( "ONCE", Scope.Method );

        //-------------------- associated to scope method-----------------
        for (int i= 0; i < 5 ; i++ )
            Log.Once( Verbosity.Info, "Once(Scope method) 1x", Scope.Method );
        Log.Once( Verbosity.Info, "Once(Scope method) 1x", Scope.Method );

        UT_EQ( 1, ml.CntLogs ); ml.CntLogs= 0;


        //-------------------- associated to scope filename -----------------
        for (int i= 0; i < 5 ; i++ )
        {
            Log.Once( "Subdom", Verbosity.Info, "Once(Scope filename) 4x", Scope.Filename, 0, 4 );
            logOnceMethod();
        }
        Log.Once( Verbosity.Info, "Once(Scope filename) 4x", Scope.Filename, 0, 4 );

        UT_EQ( 4, ml.CntLogs ); ml.CntLogs= 0;

        //-------------------- associated to scope thread -----------------
        Log.Once( Verbosity.Info, "Once(Scope.ThreadOuter) 2x - main thread", Scope.ThreadOuter, 0, 2 );
        UT_EQ( 1, ml.CntLogs ); ml.CntLogs= 0;
        Thread thread= new Thread( new ThreadStart( LogOnceTestThreadRun ) );
        thread.Start();
        while( thread.IsAlive )
            ALIB.SleepMicros(1);
        UT_EQ( 2, ml.CntLogs ); ml.CntLogs= 0;
        Log.Once( Verbosity.Info, "Once(Scope.ThreadOuter) 2x - main thread", Scope.ThreadOuter, 0, 2 );
        UT_EQ( 1, ml.CntLogs ); ml.CntLogs= 0;
        Log.Once( Verbosity.Info, "Once(Scope.ThreadOuter) 2x - main thread", Scope.ThreadOuter, 0, 2 );
        UT_EQ( 0, ml.CntLogs ); ml.CntLogs= 0;
        Log.Once( Verbosity.Info, "Once(Scope.ThreadOuter) 2x - main thread", Scope.ThreadOuter, 0, 2 );
        UT_EQ( 0, ml.CntLogs ); ml.CntLogs= 0;

        // different group
        Log.Once( "Once(group, Scope.ThreadOuter) 2x - main thread", "group", Scope.ThreadOuter, 0, 1 );
        UT_EQ( 1, ml.CntLogs ); ml.CntLogs= 0;
        Log.Once( "Once(group, Scope.ThreadOuter) 2x - main thread", "group", Scope.ThreadOuter, 0, 1 );
        UT_EQ( 0, ml.CntLogs ); ml.CntLogs= 0;

        //-------------------- associated to line (using group interface)  -----------------
        for (int i= 0; i < 5 ; i++ )
            Log.Once( Verbosity.Info, "Once(line) 1x" );
        UT_EQ( 1, ml.CntLogs ); ml.CntLogs= 0;

        for (int i= 0; i < 5; i++ )
            Log.Once( Verbosity.Info, "Once(line other) 2x", "", 2 );
        UT_EQ( 2, ml.CntLogs ); ml.CntLogs= 0;

        for (int i= 0; i < 5; i++ )
            Log.Once( Verbosity.Info, "Once(line other) 1x", "", 1 );
        UT_EQ( 1, ml.CntLogs ); ml.CntLogs= 0;

        for (int i= 0; i < 5; i++ )
            Log.Once( Verbosity.Info, "Once(line other) 0x", "", 0 );
        UT_EQ( 0, ml.CntLogs ); ml.CntLogs= 0;

        for (int i= 0; i < 5; i++ )
            Log.Once( "Once(line) Just msg and number", 2 );
        UT_EQ( 2, ml.CntLogs ); ml.CntLogs= 0;

        for (int i= 0; i < 5; i++ )
            Log.Once( "Once(line) Just msg ");
        UT_EQ( 1, ml.CntLogs ); ml.CntLogs= 0;

        //-------------------- associated to group -----------------
        for (int i= 0; i < 5 ; i++ )
            Log.Once( Verbosity.Info, "Once(\"a group\") 1x", "a group" );
        UT_EQ( 1, ml.CntLogs ); ml.CntLogs= 0;
        Log.Once( Verbosity.Info, "Once(\"a group\") 1x but tricked up", "a group", 2 );
        UT_EQ( 1, ml.CntLogs ); ml.CntLogs= 0;


        Log.Once( Verbosity.Info, "Once(\"a group\") 1x", "a group" );
        UT_EQ( 0, ml.CntLogs ); ml.CntLogs= 0;

        Log.Once( Verbosity.Info, "Once(\"b group\") 1x", "b group" );
        UT_EQ( 1, ml.CntLogs ); ml.CntLogs= 0;

        Log.Once( Verbosity.Info, "Once(\"b group\") 1x", "b group" );
        UT_EQ( 0, ml.CntLogs ); ml.CntLogs= 0;

        Log.Once( Verbosity.Info, "Once(\"c group\") 2x", "c group", 2 );
        UT_EQ( 1, ml.CntLogs ); ml.CntLogs= 0;

        Log.Once( Verbosity.Info, "Once(\"c group\") 2x", "c group", 2 );
        UT_EQ( 1, ml.CntLogs ); ml.CntLogs= 0;

        Log.Once( Verbosity.Info, "Once(\"c group\") 2x", "c group", 2 );
        UT_EQ( 0, ml.CntLogs ); ml.CntLogs= 0;

        Log.Once( Verbosity.Info, "Once(\"a group\") 1x", "a group" );
        UT_EQ( 0, ml.CntLogs ); ml.CntLogs= 0;

        Log.Once( Verbosity.Info, "Once(\"b group\") 1x", "b group" );
        UT_EQ( 0, ml.CntLogs ); ml.CntLogs= 0;

        Log.Once( Verbosity.Info, "Once(\"c group\") 2x", "c group", 2 );
        UT_EQ( 0, ml.CntLogs ); ml.CntLogs= 0;

        // AString
        Log.Once( new AString( "Once with AString" ) );
        UT_EQ( 1, ml.CntLogs ); ml.CntLogs= 0;


        //-------------------- Log every Nth -----------------
        for (int i= 0; i < 10 ; i++ )
            Log.Once( Verbosity.Info, "Every 2nd ", -2 );
        UT_EQ( 5, ml.CntLogs ); ml.CntLogs= 0;

        for (int i= 0; i < 10 ; i++ )
            Log.Once( Verbosity.Info, "Every 3rd ", -3 );

        UT_EQ( 4, ml.CntLogs ); ml.CntLogs= 0;
    }

    /** ********************************************************************************************
     * Log_Data
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
    public void Log_Data()
    {
        UT_INIT();

        Log.AddDebugLogger();
        Log.DebugLogger.MetaInfo.Format._()._(utWriter.logger.MetaInfo.Format);
        Log.SetVerbosity( Log.DebugLogger, Verbosity.Verbose, ALox.InternalDomains );
        Log.SetDomain( "Data", Scope.Method );


        // without key
        Log.Store( null           ,    Scope.Global         );
        Log.Store( "Replaced"     ,    Scope.Global         );
        Log.Store( null           ,    Scope.Global         );
        Log.Store( "Global"       ,    Scope.Global         );
        Log.Store( "Replaced"     ,    Scope.ThreadOuter    );
        Log.Store( "ThreadOuter"  ,    Scope.ThreadOuter    );
        Log.Store( "Replaced"     ,    Scope.Path,    1     );
        Log.Store( "Path1"        ,    Scope.Path,    1     );
        Log.Store( "Replaced"     ,    Scope.Path           );
        Log.Store( "Path"         ,    Scope.Path           );
        Log.Store( "Replaced"     ,    Scope.Filename       );
        Log.Store( "FileName"     ,    Scope.Filename       );
        Log.Store( "Replaced"     ,    Scope.Method         );
        Log.Store( "Method"       ,    Scope.Method         );
        Log.Store( "Replaced"     ,    Scope.ThreadInner    );
        Log.Store( "ThreadInner"  ,    Scope.ThreadInner    );

        Object data= null;
        data= Log.Retrieve( Scope.Global       ); UT_EQ( "Global"        , (String) data );
        data= Log.Retrieve( Scope.ThreadOuter  ); UT_EQ( "ThreadOuter"   , (String) data );
        data= Log.Retrieve( Scope.Path,    1   ); UT_EQ( "Path1"         , (String) data );
        data= Log.Retrieve( Scope.Path         ); UT_EQ( "Path"          , (String) data );
        data= Log.Retrieve( Scope.Filename     ); UT_EQ( "FileName"      , (String) data );
        data= Log.Retrieve( Scope.Method       ); UT_EQ( "Method"        , (String) data );
        data= Log.Retrieve( Scope.ThreadInner  ); UT_EQ( "ThreadInner"   , (String) data );

        // wit key
        Log.Store( "Replaced"    ,   "mykey",  Scope.Global         );
        Log.Store( "Global"      ,   "mykey",  Scope.Global         );
        Log.Store( "Replaced"    ,   "mykey",  Scope.ThreadOuter    );
        Log.Store( "ThreadOuter" ,   "mykey",  Scope.ThreadOuter    );
        Log.Store( "Replaced"    ,   "mykey",  Scope.Path,    1     );
        Log.Store( "Path1"       ,   "mykey",  Scope.Path,    1     );
        Log.Store( "Replaced"    ,   "mykey",  Scope.Path           );
        Log.Store( "Path"        ,   "mykey",  Scope.Path           );
        Log.Store( "Replaced"    ,   "mykey",  Scope.Filename       );
        Log.Store( "FileName"    ,   "mykey",  Scope.Filename       );
        Log.Store( "Replaced"    ,   "mykey",  Scope.Method         );
        Log.Store( "Method"      ,   "mykey",  Scope.Method         );
        Log.Store( "Replaced"    ,   "mykey",  Scope.ThreadInner    );
        Log.Store( "ThreadInner" ,   "mykey",  Scope.ThreadInner    );


        data= Log.Retrieve( "mykey", Scope.Global       ); UT_EQ( "Global"        , (String) data );
        data= Log.Retrieve( "mykey", Scope.ThreadOuter  ); UT_EQ( "ThreadOuter"   , (String) data );
        data= Log.Retrieve( "mykey", Scope.Path,    1   ); UT_EQ( "Path1"         , (String) data );
        data= Log.Retrieve( "mykey", Scope.Path         ); UT_EQ( "Path"          , (String) data );
        data= Log.Retrieve( "mykey", Scope.Filename     ); UT_EQ( "FileName"      , (String) data );
        data= Log.Retrieve( "mykey", Scope.Method       ); UT_EQ( "Method"        , (String) data );
        data= Log.Retrieve( "mykey", Scope.ThreadInner  ); UT_EQ( "ThreadInner"   , (String) data );


        // threaded
        Log.Store( "Main Thread Data"       ,             Scope.ThreadOuter   );
        Log.Store( "Main Thread Data, keyed",   "mykey",  Scope.ThreadOuter   );


        Thread thread= new Thread( new ThreadStart( StoreDataTestThreadRun ) );
        thread.Start();
        while( thread.IsAlive )
            ALIB.SleepMicros(1);

        data= Log.Retrieve(          Scope.ThreadOuter ); UT_EQ( "Main Thread Data"         , (String) data );
        data= Log.Retrieve( "mykey", Scope.ThreadOuter ); UT_EQ( "Main Thread Data, keyed"  , (String) data );

    }

    } // class

} // namespace
#endif
