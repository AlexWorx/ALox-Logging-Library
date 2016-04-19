// #################################################################################################
//  Unit Tests - AWorx Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
package ut_alox.scopeP1.scopeP2;

import org.junit.Test;

import ut_com_aworx_uttools.AUnitTest;

import com.aworx.lib.ALIB;
import com.aworx.lib.enums.Inclusion;
import com.aworx.lib.strings.AString;
import com.aworx.lox.*;
import com.aworx.lox.loggers.MemoryLogger;

class DomainTestThread extends Thread
{
    public void run()
    {
        Log.info( "DTT", "" );
    }
};

class LogOnceTestThread extends Thread
{
    public void run()
    {
        Log.once( "", Verbosity.INFO, "Once(Scope.THREAD_OUTER) 2x - 2nd thread", Scope.THREAD_OUTER, 0, 2 );
        Log.once( "", Verbosity.INFO, "Once(Scope.THREAD_OUTER) 2x - 2nd thread", Scope.THREAD_OUTER, 0, 2 );
        Log.once( "", Verbosity.INFO, "Once(Scope.THREAD_OUTER) 2x - 2nd thread", Scope.THREAD_OUTER, 0, 2 );
        Log.once( "", Verbosity.INFO, "Once(Scope.THREAD_OUTER) 2x - 2nd thread", Scope.THREAD_OUTER, 0, 2 );
    }
};

class StoreDataTestThreadThread extends Thread
{
    AUnitTest ut;
    StoreDataTestThreadThread(AUnitTest ut) { this.ut= ut; }

    public void run()
    {
        LogData data= null;

        Log.store( new LogData( "2nd Thread Data"        ),             Scope.THREAD_OUTER   );
        Log.store( new LogData( "2nd Thread Data, keyed" ),   "mykey",  Scope.THREAD_OUTER   );

        data= Log.retrieve(          Scope.THREAD_OUTER ); ut.UT_EQ( "2nd Thread Data"        , data.stringValue );
        data= Log.retrieve( "mykey", Scope.THREAD_OUTER ); ut.UT_EQ( "2nd Thread Data, keyed" , data.stringValue );
    }
};

class CustomPrefix
{
    public String toString() { return "CUSTOM:"; };
}

public class UT_alox_scopes extends AUnitTest
{
   /** ********************************************************************************************
     * Log_Prefix
     **********************************************************************************************/
    void PFXCHECK( String exp, MemoryLogger ml )
    {
        UT_EQ( exp  , ml.memoryLog );
        ml.memoryLog._();
        ml.autoSizes.reset();
    }

    @SuppressWarnings("static-method")
    @Test
    public void Log_Prefix()
    {
        UT_INIT();
        CustomPrefix custom1= new CustomPrefix();
        CustomPrefix custom2= new CustomPrefix();

        Log.addDebugLogger();
        MemoryLogger ml= new MemoryLogger();
        ml.metaInfo.format._();
        Log.setVerbosity(ml, Verbosity.VERBOSE );
        Log.setVerbosity(Log.debugLogger, Verbosity.VERBOSE, ALox.INTERNAL_DOMAINS );
        Log.setDomain( "/PREFIX", Scope.METHOD);

        // src scopes
        Log.setPrefix( "REPLACE:",    Scope.GLOBAL     );  Log.info( "*msg*" ); PFXCHECK( "REPLACE:*msg*"          ,ml );
        Log.setPrefix( "GLOBAL:",     Scope.GLOBAL     );  Log.info( "*msg*" ); PFXCHECK( "GLOBAL:*msg*"           ,ml );
        Log.setPrefix( null   ,       Scope.GLOBAL     );  Log.info( "*msg*" ); PFXCHECK( "*msg*"                  ,ml );
        Log.setPrefix( "REPLACE:",    Scope.CLASS      );  Log.info( "*msg*" ); PFXCHECK( "REPLACE:*msg*"          ,ml );
        Log.setPrefix( "FILE:",       Scope.CLASS      );  Log.info( "*msg*" ); PFXCHECK( "FILE:*msg*"             ,ml );
        Log.setPrefix( "REPLACE:",    Scope.METHOD     );  Log.info( "*msg*" ); PFXCHECK( "FILE:REPLACE:*msg*"     ,ml );
        Log.setPrefix( "METHOD:",     Scope.METHOD     );  Log.info( "*msg*" ); PFXCHECK( "FILE:METHOD:*msg*"      ,ml );

        Log.setPrefix( null   ,       Scope.METHOD     );  Log.info( "*msg*" ); PFXCHECK( "FILE:*msg*"             ,ml );
        Log.setPrefix( "METHOD:",     Scope.METHOD     );  Log.info( "*msg*" ); PFXCHECK( "FILE:METHOD:*msg*"      ,ml );

        // set custom
        Log.setPrefix( null   ,       Scope.METHOD     );  Log.info( "*msg*" ); PFXCHECK( "FILE:*msg*"             ,ml );
        Log.setPrefix( custom1  ,     Scope.METHOD     );  Log.info( "*msg*" ); PFXCHECK( "FILE:CUSTOM:*msg*"      ,ml );
        Log.setPrefix( custom1  ,     Scope.METHOD     );  Log.info( "*msg*" ); PFXCHECK( "FILE:CUSTOM:*msg*"      ,ml );
        Log.setPrefix( custom2  ,     Scope.METHOD     );  Log.info( "*msg*" ); PFXCHECK( "FILE:CUSTOM:*msg*"      ,ml );
        Log.setPrefix( null   ,       Scope.METHOD     );  Log.info( "*msg*" ); PFXCHECK( "FILE:*msg*"             ,ml );
        Log.setPrefix( custom1  ,     Scope.METHOD     );  Log.info( "*msg*" ); PFXCHECK( "FILE:CUSTOM:*msg*"      ,ml );
        Log.setPrefix( "METHOD:",     Scope.METHOD     );  Log.info( "*msg*" ); PFXCHECK( "FILE:METHOD:*msg*"      ,ml );
        Log.setPrefix( "METHOD:",     Scope.METHOD     );  Log.info( "*msg*" ); PFXCHECK( "FILE:METHOD:*msg*"      ,ml );

        // domain related
        Log.setPrefix( "DOM1:" );                          Log.info( "*msg*" ); PFXCHECK( "FILE:METHOD:DOM1:*msg*"            ,ml );
        Log.setPrefix( "DOM2:" );                          Log.info( "*msg*" ); PFXCHECK( "FILE:METHOD:DOM1:DOM2:*msg*"       ,ml );
        Log.setPrefix( "DOM3:" );                          Log.info( "*msg*" ); PFXCHECK( "FILE:METHOD:DOM1:DOM2:DOM3:*msg*"  ,ml );
        Log.setPrefix( ""      );                          Log.info( "*msg*" ); PFXCHECK( "FILE:METHOD:DOM1:DOM2:*msg*"       ,ml );
        Log.setPrefix( ""      );                          Log.info( "*msg*" ); PFXCHECK( "FILE:METHOD:DOM1:*msg*"            ,ml );
        Log.setPrefix( "DOMR:", "/" );                     Log.info( "*msg*" ); PFXCHECK( "FILE:METHOD:DOMR:DOM1:*msg*"       ,ml );
        Log.setPrefix( "DOMX:", "", Inclusion.EXCLUDE );   Log.info( "*msg*" ); PFXCHECK( "DOMX:*msg*"                        ,ml );
        Log.setPrefix( ""      );                          Log.info( "*msg*" ); PFXCHECK( "FILE:METHOD:DOMR:DOM1:*msg*"       ,ml );
        Log.setPrefix( "DRX:", "/", Inclusion.EXCLUDE );   Log.info( "*msg*" ); PFXCHECK( "DRX:DOM1:*msg*"                    ,ml );
        Log.setPrefix( ""    , "/"  );                     Log.info( "*msg*" ); PFXCHECK( "FILE:METHOD:DOMR:DOM1:*msg*"       ,ml );

        // source path
        Log.setPrefix( "REPLACE:",    Scope.PACKAGE    );  Log.info( "*msg*" ); PFXCHECK( "REPLACE:FILE:METHOD:DOMR:DOM1:*msg*"         ,ml );
        Log.setPrefix( "PATH:",       Scope.PACKAGE    );  Log.info( "*msg*" ); PFXCHECK( "PATH:FILE:METHOD:DOMR:DOM1:*msg*"            ,ml );
        Log.setPrefix( "REPLACE:",    Scope.PACKAGE, 1 );  Log.info( "*msg*" ); PFXCHECK( "REPLACE:PATH:FILE:METHOD:DOMR:DOM1:*msg*"    ,ml );
        Log.setPrefix( "PO1:",        Scope.PACKAGE, 1 );  Log.info( "*msg*" ); PFXCHECK( "PO1:PATH:FILE:METHOD:DOMR:DOM1:*msg*"        ,ml );
        Log.setPrefix( "REPLACE:",    Scope.PACKAGE, 2 );  Log.info( "*msg*" ); PFXCHECK( "REPLACE:PO1:PATH:FILE:METHOD:DOMR:DOM1:*msg*",ml );
        Log.setPrefix( "PO2:",        Scope.PACKAGE, 2 );  Log.info( "*msg*" ); PFXCHECK( "PO2:PO1:PATH:FILE:METHOD:DOMR:DOM1:*msg*"    ,ml );
        Log.setPrefix( "REPLACE:",    Scope.GLOBAL     );  Log.info( "*msg*" ); PFXCHECK( "REPLACE:PO2:PO1:PATH:FILE:METHOD:DOMR:DOM1:*msg*"  , ml );

        // remove all previous scope domains
        Log.setPrefix( null    ,Scope.GLOBAL           );
        Log.setPrefix( null    ,Scope.PACKAGE          );
        Log.setPrefix( null    ,Scope.PACKAGE ,1       );
        Log.setPrefix( null    ,Scope.PACKAGE ,2       );
        Log.setPrefix( null    ,Scope.CLASS            );
        Log.setPrefix( null    ,Scope.METHOD           );

        Log.setPrefix( null      ); // domain "/PREFIX"
        Log.setPrefix( null      ); // domain "/PREFIX" nothing here any more
        Log.setPrefix( null, "/" ); // domain "/"
                                                            Log.info( "*msg*" ); PFXCHECK( "*msg*"                        ,ml );

        // Thread-related
        Log.setPrefix( "TO:"   ,Scope.THREAD_OUTER     );  Log.info( "*msg*" ); PFXCHECK( "TO:*msg*"                     ,ml );
        Log.setPrefix( "GL:"   ,Scope.GLOBAL           );  Log.info( "*msg*" ); PFXCHECK( "GL:TO:*msg*"                  ,ml );
        Log.setPrefix( "MET:"  ,Scope.METHOD           );  Log.info( "*msg*" ); PFXCHECK( "GL:TO:MET:*msg*"              ,ml );
        Log.setPrefix( ":TI"   ,Scope.THREAD_INNER     );  Log.info( "*msg*" ); PFXCHECK( "GL:TO:MET:*msg*:TI"           ,ml );

        Log.setPrefix( "TO2:"  ,Scope.THREAD_OUTER     );  Log.info( "*msg*" ); PFXCHECK( "GL:TO:TO2:MET:*msg*:TI"       ,ml );
        Log.setPrefix( ":TI2"  ,Scope.THREAD_INNER     );  Log.info( "*msg*" ); PFXCHECK( "GL:TO:TO2:MET:*msg*:TI:TI2"   ,ml );

        Log.setPrefix( "TO3:"  ,Scope.THREAD_OUTER     );  Log.info( "*msg*" ); PFXCHECK( "GL:TO:TO2:TO3:MET:*msg*:TI:TI2"    ,ml );
        Log.setPrefix( ":TI3"  ,Scope.THREAD_INNER     );  Log.info( "*msg*" ); PFXCHECK( "GL:TO:TO2:TO3:MET:*msg*:TI:TI2:TI3",ml );


        Log.setPrefix( null    ,Scope.THREAD_INNER     );  Log.info( "*msg*" ); PFXCHECK( "GL:TO:TO2:TO3:MET:*msg*:TI:TI2"    ,ml );
        Log.setPrefix( null    ,Scope.THREAD_INNER     );  Log.info( "*msg*" ); PFXCHECK( "GL:TO:TO2:TO3:MET:*msg*:TI"   ,ml );
        Log.setPrefix( null    ,Scope.THREAD_OUTER     );  Log.info( "*msg*" ); PFXCHECK( "GL:TO:TO2:MET:*msg*:TI"       ,ml );
        Log.setPrefix( null    ,Scope.THREAD_OUTER     );  Log.info( "*msg*" ); PFXCHECK( "GL:TO:MET:*msg*:TI"           ,ml );
        Log.setPrefix( null    ,Scope.THREAD_OUTER     );  Log.info( "*msg*" ); PFXCHECK( "GL:MET:*msg*:TI"              ,ml );
        Log.setPrefix( null    ,Scope.GLOBAL           );  Log.info( "*msg*" ); PFXCHECK( "MET:*msg*:TI"                 ,ml );
        Log.setPrefix( null    ,Scope.METHOD           );  Log.info( "*msg*" ); PFXCHECK( "*msg*:TI"                     ,ml );
        Log.setPrefix( null    ,Scope.THREAD_INNER     );  Log.info( "*msg*" ); PFXCHECK( "*msg*"                        ,ml );

        // check if breaking dom-releated, removes all thread inner correctly
        Log.setPrefix( ":TI"         ,Scope.THREAD_INNER);  Log.info( "*msg*" ); PFXCHECK( "*msg*:TI"                  ,ml );
        Log.setPrefix( "DOM1:", ""   ,Inclusion.INCLUDE );  Log.info( "*msg*" ); PFXCHECK( "DOM1:*msg*:TI"             ,ml );
        Log.setPrefix( "DOMX:", ""   ,Inclusion.EXCLUDE );  Log.info( "*msg*" ); PFXCHECK( "DOMX:*msg*"                ,ml );
        Log.setPrefix( ":TI"         ,Scope.THREAD_INNER);  Log.info( "*msg*" ); PFXCHECK( "DOMX:*msg*"                ,ml );
        Log.setPrefix( null, ""                         );  Log.info( "*msg*" ); PFXCHECK( "DOM1:*msg*:TI:TI"          ,ml );

        Log.removeLogger( ml );

        //Log.logConfig( "", Verbosity.INFO, "Configuration now is:" );
    }


    /** ********************************************************************************************
     * Log.DomainsDefault
     **********************************************************************************************/
    void SDCHECK( String exp, MemoryLogger ml )
    {
        UT_EQ( exp  , ml.memoryLog );
        ml.memoryLog._();
        ml.autoSizes.reset();
    }

    @SuppressWarnings("static-method")
    @Test
    public void Log_ScopeDomains()
    {
        UT_INIT();

        Log.addDebugLogger();
        MemoryLogger ml= new MemoryLogger();
        ml.metaInfo.format._()._("@%D#");
        Log.setVerbosity( ml, Verbosity.VERBOSE );
        Log.setVerbosity(Log.debugLogger, Verbosity.VERBOSE, ALox.INTERNAL_DOMAINS );

        Log.setDomain( "REPLACE",    Scope.GLOBAL      );  Log.info( "" ); SDCHECK( "@/REPLACE#"                    ,ml );
        Log.setDomain( "GLOBAL",     Scope.GLOBAL      );  Log.info( "" ); SDCHECK( "@/GLOBAL#"                     ,ml );

        Log.setDomain( null,         Scope.GLOBAL      );  Log.info( "" ); SDCHECK( "@/#"                           ,ml );

        // scope source
        Log.setDomain( "REPLACE",    Scope.CLASS       );  Log.info( "" ); SDCHECK( "@/REPLACE#"                    ,ml );
        Log.setDomain( "CLASS",      Scope.CLASS       );  Log.info( "" ); SDCHECK( "@/CLASS#"                      ,ml );

        // scope method
        Log.setDomain( "REPLACE",    Scope.METHOD      );  Log.info( "" ); SDCHECK( "@/CLASS/REPLACE#"              ,ml );
        Log.setDomain( "METHOD",     Scope.METHOD      );  Log.info( "" ); SDCHECK( "@/CLASS/METHOD#"               ,ml );
        Log.setDomain( "/ABS",       Scope.METHOD      );  Log.info( "" ); SDCHECK( "@/ABS#"                        ,ml );

        // unset method with null
        Log.setDomain( null,         Scope.METHOD      );  Log.info( "" ); SDCHECK( "@/CLASS#"                      ,ml );

        // unset method with ""
        Log.setDomain( "/METHOD",    Scope.METHOD      );  Log.info( "" ); SDCHECK( "@/METHOD#"                     ,ml );
        Log.setDomain( "",           Scope.METHOD      );  Log.info( "" ); SDCHECK( "@/CLASS#"                      ,ml );
        Log.setDomain( "METHOD",     Scope.METHOD      );  Log.info( "" ); SDCHECK( "@/CLASS/METHOD#"               ,ml );

        // source path
        Log.setDomain( "REPLACE",    Scope.PACKAGE     );  Log.info( "" ); SDCHECK( "@/REPLACE/CLASS/METHOD#"         ,ml );
        Log.setDomain( "PACK",       Scope.PACKAGE     );  Log.info( "" ); SDCHECK( "@/PACK/CLASS/METHOD#"            ,ml );
        Log.setDomain( "REPLACE",    Scope.PACKAGE, 1  );  Log.info( "" ); SDCHECK( "@/REPLACE/PACK/CLASS/METHOD#"    ,ml );
        Log.setDomain( "PO1",        Scope.PACKAGE, 1  );  Log.info( "" ); SDCHECK( "@/PO1/PACK/CLASS/METHOD#"        ,ml );
        Log.setDomain( "REPLACE",    Scope.PACKAGE, 2  );  Log.info( "" ); SDCHECK( "@/REPLACE/PO1/PACK/CLASS/METHOD#",ml );
        Log.setDomain( "PO2",        Scope.PACKAGE, 2  );  Log.info( "" ); SDCHECK( "@/PO2/PO1/PACK/CLASS/METHOD#"    ,ml );

        Log.setDomain( "GLOBAL",     Scope.GLOBAL      );  Log.info( "" );                SDCHECK( "@/GLOBAL/PO2/PO1/PACK/CLASS/METHOD#"   , ml );
                                                                    UT_alox_scopes_helper.help(); SDCHECK( "@/GLOBAL/PO2/PO1/PACK/HCLASS/HMETHOD#" , ml );
                                                                    Log.info( "" );                SDCHECK( "@/GLOBAL/PO2/PO1/PACK/CLASS/METHOD#"   , ml );


        // remove all previous scope domains
        Log.setDomain( "",     Scope.GLOBAL      );
        Log.setDomain( "",     Scope.PACKAGE     );
        Log.setDomain( "",     Scope.PACKAGE ,1  );
        Log.setDomain( "",     Scope.PACKAGE ,2  );
        Log.setDomain( "",     Scope.CLASS       );
        Log.setDomain( "",     Scope.METHOD      );  Log.info(  "LOC", "" ); SDCHECK( "@/LOC#"                 ,ml );

        // Thread
        Log.setDomain( "T_O",  Scope.THREAD_OUTER);  Log.info(  ""   , "" ); SDCHECK( "@/T_O#"                 ,ml );
        Log.setDomain( "GL",   Scope.GLOBAL      );  Log.info(  ""   , "" ); SDCHECK( "@/GL/T_O#"              ,ml );
        Log.setDomain( "MET",  Scope.METHOD      );  Log.info(  ""   , "" ); SDCHECK( "@/GL/T_O/MET#"          ,ml );
        Log.setDomain( "MET",  Scope.METHOD      );  Log.info(  "LOC", "" ); SDCHECK( "@/GL/T_O/MET/LOC#"      ,ml );
        Log.setDomain( "T_I",  Scope.THREAD_INNER);  Log.info(  ""   , "" ); SDCHECK( "@/GL/T_O/MET/T_I#"      ,ml );

                                                              Log.info(  "LOC", "" ); SDCHECK( "@/GL/T_O/MET/LOC/T_I#"  ,ml );
        Log.setDomain( "T_O2", Scope.THREAD_OUTER);  Log.info(  ""   , "" ); SDCHECK( "@/GL/T_O/T_O2/MET/T_I#" ,ml );
        Log.setDomain( "T_I2", Scope.THREAD_INNER);  Log.info(  ""   , "" ); SDCHECK( "@/GL/T_O/T_O2/MET/T_I/T_I2#" ,ml );

        Log.setDomain( "/T_O3",Scope.THREAD_OUTER);  Log.info(  ""   , "" ); SDCHECK( "@/T_O3/MET/T_I/T_I2#"   ,ml );
        Log.setDomain( "/T_I3",Scope.THREAD_INNER);  Log.info(  ""   , "" ); SDCHECK( "@/T_I3#"                ,ml );

        Log.setDomain         ( ""     ,Scope.THREAD_INNER );  Log.info(  ""   , "" ); SDCHECK( "@/T_O3/MET/T_I/T_I2#"   ,ml );
        Log.removeThreadDomain( "T_IXX",Scope.THREAD_INNER );  Log.info(  ""   , "" ); SDCHECK( "@/T_O3/MET/T_I/T_I2#"   ,ml );
        Log.removeThreadDomain( "T_I"  ,Scope.THREAD_INNER );  Log.info(  ""   , "" ); SDCHECK( "@/T_O3/MET/T_I2#"       ,ml );
        Log.removeThreadDomain( ""     ,Scope.THREAD_INNER );  Log.info(  ""   , "" ); SDCHECK( "@/T_O3/MET/T_I2#"       ,ml );
        Log.setDomain         ( ""     ,Scope.THREAD_INNER );  Log.info(  ""   , "" ); SDCHECK( "@/T_O3/MET#"            ,ml );
        Log.setDomain         ( ""     ,Scope.THREAD_OUTER );  Log.info(  ""   , "" ); SDCHECK( "@/GL/T_O/T_O2/MET#"     ,ml );
        Log.setDomain         ( "T_O3", Scope.THREAD_OUTER );  Log.info(  ""   , "" ); SDCHECK( "@/GL/T_O/T_O2/T_O3/MET#",ml );
        Log.removeThreadDomain( "T_O2" ,Scope.THREAD_OUTER );  Log.info(  ""   , "" ); SDCHECK( "@/GL/T_O/T_O3/MET#"     ,ml );
        Log.removeThreadDomain( "T_O"  ,Scope.THREAD_OUTER );  Log.info(  ""   , "" ); SDCHECK( "@/GL/T_O3/MET#"         ,ml );
        Log.setDomain         ( ""     ,Scope.THREAD_OUTER );  Log.info(  ""   , "" ); SDCHECK( "@/GL/MET#"              ,ml );
        Log.setDomain         ( ""     ,Scope.GLOBAL       );  Log.info(  ""   , "" ); SDCHECK( "@/MET#"                 ,ml );
        Log.setDomain         ( ""     ,Scope.METHOD       );  Log.info(  ""   , "" ); SDCHECK( "@/#"                    ,ml );

        // second thread
        Thread thread= new DomainTestThread();

        Log.setDomain( "THIS_THREAD",   Scope.THREAD_OUTER );
        Log.setDomain( "OTHER_THREAD",  Scope.THREAD_OUTER, thread );
        thread.start();
        while( thread.isAlive() )
            ALIB.sleepMillis(1);
                               UT_EQ( "@/OTHER_THREAD/DTT#", ml.memoryLog );  ml.memoryLog._(); ml.autoSizes.reset();
        Log.info( "ME", "" );  UT_EQ( "@/THIS_THREAD/ME#"  , ml.memoryLog );  ml.memoryLog._(); ml.autoSizes.reset();

        //Log.logConfig( "", Verbosity.INFO, "Configuration now is:" );
    }

    /** ****************************************************************************************
     *     Log_Once
     ******************************************************************************************/
    void logOnceMethod()
    {
        Log.once( "", Verbosity.INFO, "Once(Scope package) 4x -from other method", Scope.PACKAGE, 0, 4 );
    }

    @Test
    public void Log_Once()
    {
        UT_INIT();

        Log.addDebugLogger();
        MemoryLogger ml= new MemoryLogger();
        Log.setVerbosity ( ml, Verbosity.VERBOSE );
        Log.setVerbosity( Log.debugLogger,  Verbosity.VERBOSE, ALox.INTERNAL_DOMAINS );
        Log.setDomain( "ONCE", Scope.METHOD );

        //-------------------- associated to scope method-----------------
        for (int i= 0; i < 5 ; i++ )
            Log.once( "", Verbosity.INFO, "Once(Scope Method) 1x", Scope.METHOD );
        Log.once( "", Verbosity.INFO, "Once(Scope Method) 1x", Scope.METHOD );

        UT_EQ( 1, ml.cntLogs ); ml.cntLogs= 0;


        //-------------------- associated to scope package -----------------
        for (int i= 0; i < 5 ; i++ )
        {
            Log.once( "Subdom", Verbosity.INFO, "Once(Scope package) 4x", Scope.PACKAGE, 0, 4 );
            logOnceMethod();
        }
        Log.once( "", Verbosity.INFO, "Once(Scope package) 4x", Scope.PACKAGE, 0, 4 );

        UT_EQ( 4, ml.cntLogs ); ml.cntLogs= 0;

        //-------------------- associated to scope thread -----------------
        Log.once( "", Verbosity.INFO, "Once(Scope.THREAD_OUTER) 2x - main thread", Scope.THREAD_OUTER, 0, 2 );
        UT_EQ( 1, ml.cntLogs ); ml.cntLogs= 0;
        LogOnceTestThread thread= new LogOnceTestThread();
        thread.start();
        while( thread.isAlive() );
            ALIB.sleepMicros(1);
        UT_EQ( 2, ml.cntLogs ); ml.cntLogs= 0;
        Log.once( "", Verbosity.INFO, "Once(Scope.THREAD_OUTER) 2x - main thread", Scope.THREAD_OUTER, 0, 2 );
        UT_EQ( 1, ml.cntLogs ); ml.cntLogs= 0;
        Log.once( "", Verbosity.INFO, "Once(Scope.THREAD_OUTER) 2x - main thread", Scope.THREAD_OUTER, 0, 2 );
        UT_EQ( 0, ml.cntLogs ); ml.cntLogs= 0;
        Log.once( "", Verbosity.INFO, "Once(Scope.THREAD_OUTER) 2x - main thread", Scope.THREAD_OUTER, 0, 2 );
        UT_EQ( 0, ml.cntLogs ); ml.cntLogs= 0;

        // different group
        Log.once( "", Verbosity.INFO, "Once(group, Scope.THREAD_OUTER) 2x - main thread", "group", Scope.THREAD_OUTER, 0, 1 );
        UT_EQ( 1, ml.cntLogs ); ml.cntLogs= 0;
        Log.once( "", Verbosity.INFO, "Once(group, Scope.THREAD_OUTER) 2x - main thread", "group", Scope.THREAD_OUTER, 0, 1 );
        UT_EQ( 0, ml.cntLogs ); ml.cntLogs= 0;

        //-------------------- associated to line -----------------
        for (int i= 0; i < 5 ; i++ )
            Log.once( "Once(line) 1x" );
        UT_EQ( 1, ml.cntLogs ); ml.cntLogs= 0;

        for (int i= 0; i < 5; i++ )
            Log.once( "Once(line other) 2x", 2 );
        UT_EQ( 2, ml.cntLogs ); ml.cntLogs= 0;

        for (int i= 0; i < 5; i++ )
            Log.once( "", Verbosity.INFO, "Once(line other) 1x", 1 );
        UT_EQ( 1, ml.cntLogs ); ml.cntLogs= 0;

        for (int i= 0; i < 5; i++ )
            Log.once( "", Verbosity.INFO, "Once(line other) 0x", 0 );
        UT_EQ( 0, ml.cntLogs ); ml.cntLogs= 0;

        for (int i= 0; i < 5; i++ )
            Log.once( "Once(line) Just msg and number", 2 );
        UT_EQ( 2, ml.cntLogs ); ml.cntLogs= 0;

        for (int i= 0; i < 5; i++ )
            Log.once( "Once(line) Just msg ");
        UT_EQ( 1, ml.cntLogs ); ml.cntLogs= 0;

        //-------------------- associated to group -----------------
        for (int i= 0; i < 5 ; i++ )
            Log.once( "", Verbosity.INFO, "Once(\"a group\") 1x", "a group" );
        UT_EQ( 1, ml.cntLogs ); ml.cntLogs= 0;
        Log.once( "", Verbosity.INFO, "Once(\"a group\") 1x but tricked up", "a group", 2 );
        UT_EQ( 1, ml.cntLogs ); ml.cntLogs= 0;


        Log.once( "", Verbosity.INFO, "Once(\"a group\") 1x", "a group" );
        UT_EQ( 0, ml.cntLogs ); ml.cntLogs= 0;

        Log.once( "", Verbosity.INFO, "Once(\"b group\") 1x", "b group" );
        UT_EQ( 1, ml.cntLogs ); ml.cntLogs= 0;

        Log.once( "", Verbosity.INFO, "Once(\"b group\") 1x", "b group" );
        UT_EQ( 0, ml.cntLogs ); ml.cntLogs= 0;

        Log.once( "", Verbosity.INFO, "Once(\"c group\") 2x", "c group", 2 );
        UT_EQ( 1, ml.cntLogs ); ml.cntLogs= 0;

        Log.once( "", Verbosity.INFO, "Once(\"c group\") 2x", "c group", 2 );
        UT_EQ( 1, ml.cntLogs ); ml.cntLogs= 0;

        Log.once( "", Verbosity.INFO, "Once(\"c group\") 2x", "c group", 2 );
        UT_EQ( 0, ml.cntLogs ); ml.cntLogs= 0;

        Log.once( "", Verbosity.INFO, "Once(\"a group\") 1x", "a group" );
        UT_EQ( 0, ml.cntLogs ); ml.cntLogs= 0;

        Log.once( "", Verbosity.INFO, "Once(\"b group\") 1x", "b group" );
        UT_EQ( 0, ml.cntLogs ); ml.cntLogs= 0;

        Log.once( "", Verbosity.INFO, "Once(\"c group\") 2x", "c group", 2 );
        UT_EQ( 0, ml.cntLogs ); ml.cntLogs= 0;

        //-------------------- Log every Nth -----------------
        for (int i= 0; i < 10 ; i++ )
            Log.once( "", Verbosity.INFO, "Every 2nd ", -2 );
        UT_EQ( 5, ml.cntLogs ); ml.cntLogs= 0;

        for (int i= 0; i < 10 ; i++ )
            Log.once( "", Verbosity.INFO, "Every 3rd ", -3 );

        UT_EQ( 4, ml.cntLogs ); ml.cntLogs= 0;



        //Log.logConfig( "", Verbosity.INFO, "Configuration now is:" );
    }

    /** ****************************************************************************************
     *     Log_StoreData
     ******************************************************************************************/
    @Test
    public void Log_StoreData()
    {
        UT_INIT();

        Log.addDebugLogger();
        Log.setVerbosity( Log.debugLogger, Verbosity.VERBOSE, ALox.INTERNAL_DOMAINS );
        Log.setDomain( "DATA", Scope.METHOD );

        // LogData Constructors
        {
            LogData ld;
            AString  asnull= new AString();
            ld= new LogData(              ); UT_EQ(  asnull, ld.stringValue ); UT_EQ( 0, ld.integerValue ); UT_TRUE( ld.objectValue == null );
            ld= new LogData(       3      ); UT_EQ(  asnull, ld.stringValue ); UT_EQ( 3, ld.integerValue ); UT_TRUE( ld.objectValue == null );
            ld= new LogData(       3, this); UT_EQ(  asnull, ld.stringValue ); UT_EQ( 3, ld.integerValue ); UT_TRUE( ld.objectValue == this );
            ld= new LogData("ABC"         ); UT_EQ(   "ABC", ld.stringValue ); UT_EQ( 0, ld.integerValue ); UT_TRUE( ld.objectValue == null );
            ld= new LogData("ABC",    this); UT_EQ(   "ABC", ld.stringValue ); UT_EQ( 0, ld.integerValue ); UT_TRUE( ld.objectValue == this );
            ld= new LogData("ABC", 3      ); UT_EQ(   "ABC", ld.stringValue ); UT_EQ( 3, ld.integerValue ); UT_TRUE( ld.objectValue == null );
            ld= new LogData("ABC", 3, this); UT_EQ(   "ABC", ld.stringValue ); UT_EQ( 3, ld.integerValue ); UT_TRUE( ld.objectValue == this );
        }

        // without key
        Log.store( null                         ,    Scope.GLOBAL         );
        Log.store( new LogData( "Replaced"     ),    Scope.GLOBAL         );
        Log.store( null                         ,    Scope.GLOBAL         );
        Log.store( new LogData( "Replaced"     ),    Scope.GLOBAL         );
        Log.store( new LogData( "Global"       ),    Scope.GLOBAL         );
        Log.store( new LogData( "Replaced"     ),    Scope.THREAD_OUTER    );
        Log.store( new LogData( "ThreadOuter"  ),    Scope.THREAD_OUTER    );
        Log.store( new LogData( "Replaced"     ),    Scope.PACKAGE,    1     );
        Log.store( new LogData( "Path1"        ),    Scope.PACKAGE,    1     );
        Log.store( new LogData( "Replaced"     ),    Scope.PACKAGE           );
        Log.store( new LogData( "Path"         ),    Scope.PACKAGE           );
        Log.store( new LogData( "Replaced"     ),    Scope.CLASS       );
        Log.store( new LogData( "FileName"     ),    Scope.CLASS       );
        Log.store( new LogData( "Replaced"     ),    Scope.METHOD         );
        Log.store( new LogData( "Method"       ),    Scope.METHOD         );
        Log.store( new LogData( "Replaced"     ),    Scope.THREAD_INNER    );
        Log.store( new LogData( "ThreadInner"  ),    Scope.THREAD_INNER    );

        LogData data= null;
        data= Log.retrieve( Scope.GLOBAL       ); UT_EQ( "Global"        , data.stringValue );
        data= Log.retrieve( Scope.THREAD_OUTER ); UT_EQ( "ThreadOuter"   , data.stringValue );
        data= Log.retrieve( Scope.PACKAGE,    1); UT_EQ( "Path1"         , data.stringValue );
        data= Log.retrieve( Scope.PACKAGE      ); UT_EQ( "Path"          , data.stringValue );
        data= Log.retrieve( Scope.CLASS        ); UT_EQ( "FileName"      , data.stringValue );
        data= Log.retrieve( Scope.METHOD       ); UT_EQ( "Method"        , data.stringValue );
        data= Log.retrieve( Scope.THREAD_INNER ); UT_EQ( "ThreadInner"   , data.stringValue );

        // wit key
        Log.store( new LogData( "Replaced"     ),   "mykey",  Scope.GLOBAL         );
        Log.store( new LogData( "Global"       ),   "mykey",  Scope.GLOBAL         );
        Log.store( new LogData( "Replaced"     ),   "mykey",  Scope.THREAD_OUTER   );
        Log.store( new LogData( "ThreadOuter"  ),   "mykey",  Scope.THREAD_OUTER   );
        Log.store( new LogData( "Replaced"     ),   "mykey",  Scope.PACKAGE,    1  );
        Log.store( new LogData( "Path1"        ),   "mykey",  Scope.PACKAGE,    1  );
        Log.store( new LogData( "Replaced"     ),   "mykey",  Scope.PACKAGE        );
        Log.store( new LogData( "Path"         ),   "mykey",  Scope.PACKAGE        );
        Log.store( new LogData( "Replaced"     ),   "mykey",  Scope.CLASS          );
        Log.store( new LogData( "FileName"     ),   "mykey",  Scope.CLASS          );
        Log.store( new LogData( "Replaced"     ),   "mykey",  Scope.METHOD         );
        Log.store( new LogData( "Method"       ),   "mykey",  Scope.METHOD         );
        Log.store( new LogData( "Replaced"     ),   "mykey",  Scope.THREAD_INNER   );
        Log.store( new LogData( "ThreadInner"  ),   "mykey",  Scope.THREAD_INNER   );


        data= Log.retrieve( "mykey", Scope.GLOBAL       ); UT_EQ( "Global"        , data.stringValue );
        data= Log.retrieve( "mykey", Scope.THREAD_OUTER ); UT_EQ( "ThreadOuter"   , data.stringValue );
        data= Log.retrieve( "mykey", Scope.PACKAGE,    1); UT_EQ( "Path1"         , data.stringValue );
        data= Log.retrieve( "mykey", Scope.PACKAGE      ); UT_EQ( "Path"          , data.stringValue );
        data= Log.retrieve( "mykey", Scope.CLASS        ); UT_EQ( "FileName"      , data.stringValue );
        data= Log.retrieve( "mykey", Scope.METHOD       ); UT_EQ( "Method"        , data.stringValue );
        data= Log.retrieve( "mykey", Scope.THREAD_INNER ); UT_EQ( "ThreadInner"   , data.stringValue );


        // threaded
        Log.store( new LogData( "Main Thread Data"        ),             Scope.THREAD_OUTER   );
        Log.store( new LogData( "Main Thread Data, keyed" ),   "mykey",  Scope.THREAD_OUTER   );


        Thread thread= new StoreDataTestThreadThread( this );
        thread.start();
        while( thread.isAlive() );
            ALIB.sleepMicros(1);

        data= Log.retrieve(          Scope.THREAD_OUTER ); UT_EQ( "Main Thread Data"         , data.stringValue );
        data= Log.retrieve( "mykey", Scope.THREAD_OUTER ); UT_EQ( "Main Thread Data, keyed"  , data.stringValue );

        //Log.logConfig( "", Verbosity.INFO, "Configuration now is:" );
    }
}
