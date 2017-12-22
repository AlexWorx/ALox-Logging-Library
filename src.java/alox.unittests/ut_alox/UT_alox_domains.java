// #################################################################################################
//  Unit Tests - AWorx Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
package ut_alox;

import java.io.BufferedWriter;
import java.io.FileWriter;


import org.junit.Test;

import com.aworx.lib.config.Configuration;
import com.aworx.lib.config.IniFile;
import com.aworx.lib.config.Variable;
import com.aworx.lox.ALox;
import com.aworx.lox.Log;
import com.aworx.lox.Lox;
import com.aworx.lox.Scope;
import com.aworx.lox.Verbosity;
import com.aworx.lox.loggers.MemoryLogger;

import ut_com_aworx.AWorxUnitTesting;

public class UT_alox_domains extends AWorxUnitTesting
{
    static void LOG_CHECK( String dom, String exp, MemoryLogger ml, Lox lox )
    {
        ml.memoryLog._(); ml.autoSizes.reset();
        Object[] logables= { "" };
        lox.entry( dom, Verbosity.INFO, logables );
        UT_EQ( exp , ml.memoryLog );
    }

    /** ********************************************************************************************
     * Log_IllegalDomainNames
     **********************************************************************************************/
    @SuppressWarnings("static-method")
    @Test
    public void Log_IllegalDomainNames()
    {
        UT_INIT();
        Log.addDebugLogger();

        MemoryLogger ml= new MemoryLogger();

        Log.setVerbosity ( ml, Verbosity.VERBOSE );
        ml.metaInfo.format._()._("<%D>");

        Log.setVerbosity(Log.debugLogger, Verbosity.VERBOSE, ALox.INTERNAL_DOMAINS );


        LOG_CHECK( ""        , "</>"              , ml,Log.LOX);
        LOG_CHECK( "LOC"     , "</LOC>"           , ml,Log.LOX);
        LOG_CHECK( "%"       , "</#>"             , ml,Log.LOX);
        LOG_CHECK( "\033"    , "</#>"             , ml,Log.LOX);
        LOG_CHECK( "<"       , "</#>"             , ml,Log.LOX);
        LOG_CHECK( ">"       , "</#>"             , ml,Log.LOX);
        LOG_CHECK( "?"       , "</#>"             , ml,Log.LOX);
        LOG_CHECK( ","       , "</#>"             , ml,Log.LOX);
        LOG_CHECK( "-"       , "</->"             , ml,Log.LOX);
        LOG_CHECK( "_"       , "</_>"             , ml,Log.LOX);
        LOG_CHECK( "@"       , "</#>"             , ml,Log.LOX);
        LOG_CHECK( "."       , "</>"              , ml,Log.LOX);
        LOG_CHECK( ".."      , "</>"              , ml,Log.LOX);
        LOG_CHECK( "CU.."    , "</CU##>"          , ml,Log.LOX);

        LOG_CHECK( "$%! "    , "</####>"          , ml,Log.LOX);

        Log.setDomain( "METH", Scope.CLASS );
        LOG_CHECK( "$%! "    , "</METH/####>"     , ml,Log.LOX);

        Log.setDomain( "A\"C" , Scope.CLASS );
        LOG_CHECK( ""        , "</A#C>"           , ml,Log.LOX);
        LOG_CHECK( "LOC"     , "</A#C/LOC>"       , ml,Log.LOX);
        LOG_CHECK( "*X*"     , "</A#C/#X#>"       , ml,Log.LOX);

        Log.removeLogger( ml );
    }

    /** ********************************************************************************************
     * Log_RelativeDomains
     **********************************************************************************************/
    @SuppressWarnings("static-method")
    @Test
    public void Log_RelativeDomains()
    {
        UT_INIT();

        Lox lox= new Lox( "ReleaseLox" );
        MemoryLogger ml= new MemoryLogger();

        lox.setVerbosity ( ml, Verbosity.VERBOSE );
        ml.metaInfo.format._()._("@%D#");
        lox.setDomain( "/D1/D2/D3", Scope.METHOD );

        lox.info( "D4"                 , "" ); UT_EQ(  "@/D1/D2/D3/D4#"        , ml.memoryLog ); ml.memoryLog._(); ml.autoSizes.reset();
        lox.info( "./D4"               , "" ); UT_EQ(  "@/D1/D2/D3/D4#"        , ml.memoryLog ); ml.memoryLog._(); ml.autoSizes.reset();
        lox.info( "../D4"              , "" ); UT_EQ(  "@/D1/D2/D4#"           , ml.memoryLog ); ml.memoryLog._(); ml.autoSizes.reset();
        lox.info( ".././.././D4"       , "" ); UT_EQ(  "@/D1/D4#"              , ml.memoryLog ); ml.memoryLog._(); ml.autoSizes.reset();
        lox.info( "../../../../../D4"  , "" ); UT_EQ(  "@/D4#"                 , ml.memoryLog ); ml.memoryLog._(); ml.autoSizes.reset();
        lox.info( "../D4/../D5"        , "" ); UT_EQ(  "@/D1/D2/D5#"           , ml.memoryLog ); ml.memoryLog._(); ml.autoSizes.reset();


        lox.removeLogger( ml );
    }



    /** ********************************************************************************************
     * Log_DomainSubstitutions
     **********************************************************************************************/
    @SuppressWarnings("static-method")
    @Test
    public void Log_DomainSubstitutions()
    {
        UT_INIT();
        Log.addDebugLogger();
        Log.debugLogger.metaInfo.format._()._( utWriter.logger.metaInfo.format );
        MemoryLogger ml= new MemoryLogger();

        Log.setVerbosity ( ml, Verbosity.VERBOSE );
        ml.metaInfo.format._()._("<%D>");

                                                            LOG_CHECK( ""     , "</>"                    , ml,Log.LOX);
                                                            LOG_CHECK( "LOC"  , "</LOC>"                 , ml,Log.LOX);

        // wrong rule
        Log.setVerbosity(Log.debugLogger, Verbosity.WARNING, ALox.INTERNAL_DOMAINS );  int cntLogs= Log.debugLogger.cntLogs;
        Log.setDomainSubstitutionRule( "LOC"        , "X"       );              UT_TRUE( cntLogs + 1 == Log.debugLogger.cntLogs );
        Log.setDomainSubstitutionRule( "*LOC/"      , "X"       );              UT_TRUE( cntLogs + 2 == Log.debugLogger.cntLogs );
        Log.setDomainSubstitutionRule( "LOC/*"      , "X"       );              UT_TRUE( cntLogs + 3 == Log.debugLogger.cntLogs );
        Log.setDomainSubstitutionRule( "LOC*"       , "X"       );              UT_TRUE( cntLogs + 4 == Log.debugLogger.cntLogs );
        Log.setDomainSubstitutionRule( "*LOC*"      , "X"       );              UT_TRUE( cntLogs + 4 == Log.debugLogger.cntLogs );
        Log.setDomainSubstitutionRule( "*/LOC*"     , "X"       );              UT_TRUE( cntLogs + 4 == Log.debugLogger.cntLogs );
        Log.setDomainSubstitutionRule( "*/LOC/*"    , "X"       );              UT_TRUE( cntLogs + 4 == Log.debugLogger.cntLogs );


        Log.setDomainSubstitutionRule( null        , null       );   // delete rules
        Log.setVerbosity(Log.debugLogger, Verbosity.INFO, ALox.INTERNAL_DOMAINS );

        // Exact match
        Log.setDomainSubstitutionRule( null          , null      );
        Log.setDomainSubstitutionRule( "/LOC"        , "X"       );   LOG_CHECK( "LOC"  , "</X>"                   , ml,Log.LOX);
        Log.setDomainSubstitutionRule( "/LOC"        , ""        );   LOG_CHECK( "LOC"  , "</LOC>"                 , ml,Log.LOX);
        Log.setDomainSubstitutionRule( "/LO"         , "/X"      );   LOG_CHECK( "LOC"  , "</LOC>"                 , ml,Log.LOX);
        Log.setDomainSubstitutionRule( "/LOCX"       , "/X"      );   LOG_CHECK( "LOC"  , "</LOC>"                 , ml,Log.LOX);

        Log.setDomainSubstitutionRule( null          , null      );

        // postfix match
        Log.setDomainSubstitutionRule( null          , null      );
        Log.setDomainSubstitutionRule( "*/LOC"       , "X"       );   LOG_CHECK( "LOC"  , "</X>"                   , ml,Log.LOX);
        Log.setDomainSubstitutionRule( "*/LOC"       , ""        );   LOG_CHECK( "LOC"  , "</LOC>"                 , ml,Log.LOX);
        Log.setDomainSubstitutionRule( "*LOC"        , "X"       );   LOG_CHECK( "LOC"  , "</X>"                   , ml,Log.LOX);
        Log.setDomainSubstitutionRule( "*LOC"        , ""        );   LOG_CHECK( "LOC"  , "</LOC>"                 , ml,Log.LOX);
        Log.setDomainSubstitutionRule( "*C"          , "X"       );   LOG_CHECK( "LOC"  , "</LOX>"                 , ml,Log.LOX);
        Log.setDomainSubstitutionRule( "*C"          , ""        );   LOG_CHECK( "LOC"  , "</LOC>"                 , ml,Log.LOX);

        Log.setDomainSubstitutionRule( "*C"          , "XY"      );   LOG_CHECK( "LOC/BC" , "</LOC/BXY>"           , ml,Log.LOX);
        Log.setDomainSubstitutionRule( "*C"          , ""        );   LOG_CHECK( "LOC/BC" , "</LOC/BC>"            , ml,Log.LOX);
        Log.setDomainSubstitutionRule( "*/BC"        , "/"       );   LOG_CHECK( "LOC/BC" , "</LOC>"               , ml,Log.LOX);
        Log.setDomainSubstitutionRule( "*/BC"        , ""        );   LOG_CHECK( "LOC/BC" , "</LOC/BC>"            , ml,Log.LOX);
        Log.setDomainSubstitutionRule( "*C/BC"       , "/VE"     );   LOG_CHECK( "LOC/BC" , "</LO/VE>"             , ml,Log.LOX);

        Log.setDomainSubstitutionRule( null          , null      );

        // prefix match
        Log.setDomainSubstitutionRule( "/LOC*"       , "X"       );   LOG_CHECK( "LOC"  , "</X>"                   , ml,Log.LOX);
        Log.setDomainSubstitutionRule( "/LOC*"       , ""        );   LOG_CHECK( "LOC"  , "</LOC>"                 , ml,Log.LOX);
        Log.setDomainSubstitutionRule( "/LOC*"       , "/X"      );   LOG_CHECK( "LOC"  , "</X>"                   , ml,Log.LOX);
        Log.setDomainSubstitutionRule( "/LOC*"       , ""        );   LOG_CHECK( "LOC"  , "</LOC>"                 , ml,Log.LOX);

        Log.setDomain( "METH", Scope.CLASS );                         LOG_CHECK( "LOC"  , "</METH/LOC>"            , ml,Log.LOX);
        Log.setDomainSubstitutionRule( "/LOC*"       , "/X"      );   LOG_CHECK( "LOC"  , "</METH/LOC>"            , ml,Log.LOX);
        Log.setDomainSubstitutionRule( "/LOC*"       , ""        );   LOG_CHECK( "LOC"  , "</METH/LOC>"            , ml,Log.LOX);
        Log.setDomainSubstitutionRule( "/METH*"      , "/X"      );   LOG_CHECK( "LOC"  , "</X/LOC>"               , ml,Log.LOX);
        Log.setDomainSubstitutionRule( "/METH*"      , "/Y"      );   LOG_CHECK( "LOC"  , "</Y/LOC>"               , ml,Log.LOX);
        Log.setDomainSubstitutionRule( "/METH*"      , "/A/B/C"  );   LOG_CHECK( "LOC"  , "</A/B/C/LOC>"           , ml,Log.LOX);
        Log.setDomain( "", Scope.CLASS );                             LOG_CHECK( "LOC"  , "</LOC>"                 , ml,Log.LOX);

        // recursive (just for test, not useful), breaks after 10 recursions
        Log.setDomainSubstitutionRule( "/R*"        , "/RR"      );   LOG_CHECK( "/REC" , "</RRRRRRRRRRREC>"       , ml,Log.LOX);
                                                                      LOG_CHECK( "/REC" , "</RRRRRRRRRRREC>"       , ml,Log.LOX);
                                                                      LOG_CHECK( "/REC" , "</RRRRRRRRRRREC>"       , ml,Log.LOX);
        Log.setDomainSubstitutionRule( "/R*"        , "/S"       );   LOG_CHECK( "/R"   , "</S>"                   , ml,Log.LOX);
        Log.setDomainSubstitutionRule( "/S*"        , "/R"       );   LOG_CHECK( "/R"   , "</R>"                   , ml,Log.LOX);
        Log.setDomainSubstitutionRule( "/S*"        , "/T"       );   LOG_CHECK( "/R"   , "</T>"                   , ml,Log.LOX);

        //Log.state( "", Verbosity.INFO, "Configuration now is:" );

        // substring rule
        Log.setDomainSubstitutionRule( "*B*"        , "X"        );   LOG_CHECK( "ABC"  , "</AXC>"                 , ml,Log.LOX);
        Log.setDomainSubstitutionRule( "*B*"        , ""         );   LOG_CHECK( "ABC"  , "</ABC>"                 , ml,Log.LOX);


        Log.setDomainSubstitutionRule( "*/ABC*"     , "DEF"      );   LOG_CHECK( "ABC"  , "</DEF>"                 , ml,Log.LOX);
        Log.setDomainSubstitutionRule( "*EF*"       , "ZZZ"      );   LOG_CHECK( "ABC"  , "</DZZZ>"                , ml,Log.LOX);
        Log.setDomainSubstitutionRule( "*Z*"        , "EE"       );   LOG_CHECK( "ABC"  , "</DEEEEEE>"             , ml,Log.LOX);

        Log.setDomainSubstitutionRule( "*/Q*"       , "V"        );   LOG_CHECK( "Q"    , "</V>"                   , ml,Log.LOX);


        // delete all rules
        Log.setDomainSubstitutionRule( null        , null       );   LOG_CHECK( "/_/ABC", "</_/ABC>"              , ml,Log.LOX);
                                                                     LOG_CHECK( "Q"     , "</Q>"                  , ml,Log.LOX);
                                                                     LOG_CHECK( "ABC"   , "</ABC>"                , ml,Log.LOX);

        //Log.state( "", Verbosity.INFO, "Configuration now is:" );

        Log.removeLogger( ml );
    }

    /** ********************************************************************************************
     * Log_DomainSubstitutions_IniFile
     **********************************************************************************************/
    @SuppressWarnings("static-method")
    @Test
    public void Log_DomainSubstitutions_IniFile()
    {
        UT_INIT();
        // create INI file
        String iniFileContents=
             "[ALOX]\n"
            +"TESTMEMLOGGER_FORMAT= \"<%D>\"  \n"

            +"MYLOX_DOMAIN_SUBSTITUTION = /A_DOM -> /BETTER_NAME ;\\ \n"
                         +"    /UI    -> /LIBS/UI    \n"

            +"x\n"
           ;
        String fileName=System.getProperty("user.dir") + "/Log_DomainSubstitutions_IniFile.ini";
        try
        {
            BufferedWriter file= new BufferedWriter( new FileWriter( fileName ) );
            file.write( iniFileContents );
            file.close();
        }
        catch(@SuppressWarnings ("unused") Exception e)
        {
            UT_TRUE( false );
        }

        IniFile iniFile= new IniFile( fileName );
        iniFile.readFile();

        // add to config
        ALox.config.insertPlugin( iniFile, Configuration.PRIO_STANDARD );

        // create lox, loggers
        Lox myLox= new Lox( "MyLox" ); // name will be upper case
        myLox.setVerbosity( Lox.createConsoleLogger("CONSOLE") , Verbosity.VERBOSE );
        myLox.setVerbosity( "CONSOLE"                          , Verbosity.VERBOSE, ALox.INTERNAL_DOMAINS );

        MemoryLogger ml= new MemoryLogger("TESTMEMLOGGER");
        myLox.setVerbosity ( ml, Verbosity.VERBOSE );

        LOG_CHECK( "DOM"    , "</DOM>"              , ml,myLox);
        LOG_CHECK( "A_DOM"  , "</BETTER_NAME>"      , ml,myLox);
        LOG_CHECK( "UI"     , "</LIBS/UI>"          , ml,myLox);

        //Log.state( "", Verbosity.INFO, "Configuration now is:" );

        ALox.config.removePlugin( iniFile );
        myLox.removeLogger( ml );
        myLox.removeLogger( "CONSOLE" );
    }

    /** ********************************************************************************************
     * Log_Domain_IniFile
     **********************************************************************************************/
    @SuppressWarnings("static-method")
    @Test
    public void Log_Domain_IniFile()
    {
        UT_INIT();

        // Without priorities
        {
            // create iniFile
            IniFile iniFile= new IniFile("*"); // don't read
            Variable var= new Variable();
            iniFile.store( var.declare( ALox.configCategoryName, "TESTML_FORMAT"),  "%Sp" );
            iniFile.store( var.declare( ALox.configCategoryName, "T_LOX_TESTML_VERBOSITY",';'),
                             "/DOM_VERB  = VerboseXX  ;" // xx is allowed!
                          +  "/DOM_INFO  = Info       ;"
                          +  "/DOM_WARN  = WARNING    ;"
                          +  "/DOM_ERR   = erRor      ;"
                          +  "/DOM_OFF   = off        ;"
                          +  "/DOM_OFF2  = xxx        ;"
                          +  "/ATSTART*  = Info       ;"
                          +  "*ATEND     = Info       ;"
                          +  "*SUBSTR*   = Info       ;"
                          +  "/OVERWRITE = Info       ;"
                        );
            ALox.config.insertPlugin( iniFile, Configuration.PRIO_STANDARD );


            // test
            Lox lox= new Lox("T_LOX", false);

            lox.setVerbosity( Lox.createConsoleLogger("CONSOLE") , Verbosity.VERBOSE );
            lox.setVerbosity( "CONSOLE"                          , Verbosity.VERBOSE, ALox.INTERNAL_DOMAINS );

            // pre-create one of the domains to test if loggers added later get config for existing domains
            lox.verbose( "DOM_INFO"     , "test" );

            MemoryLogger ml= new MemoryLogger("TESTML");
            lox.setVerbosity( ml, Verbosity.OFF );

            lox.info   (                  "test" );    UT_EQ(  0, ml.cntLogs ); ml.cntLogs= 0;
            lox.error  ( "NOSETTING"    , "test" );    UT_EQ(  0, ml.cntLogs ); ml.cntLogs= 0;

            lox.verbose( "DOM_VERB"     , "test" );    UT_EQ(  1, ml.cntLogs ); ml.cntLogs= 0;

            lox.verbose( "DOM_INFO"     , "test" );    UT_EQ(  0, ml.cntLogs ); ml.cntLogs= 0;
            lox.info   ( "DOM_INFO"     , "test" );    UT_EQ(  1, ml.cntLogs ); ml.cntLogs= 0;

            lox.info   ( "DOM_WARN"     , "test" );    UT_EQ(  0, ml.cntLogs ); ml.cntLogs= 0;
            lox.warning( "DOM_WARN"     , "test" );    UT_EQ(  1, ml.cntLogs ); ml.cntLogs= 0;

            lox.warning( "DOM_ERR"      , "test" );    UT_EQ(  0, ml.cntLogs ); ml.cntLogs= 0;
            lox.error  ( "DOM_ERR"      , "test" );    UT_EQ(  1, ml.cntLogs ); ml.cntLogs= 0;

            lox.error  ( "DOM_OFF"      , "test" );    UT_EQ(  0, ml.cntLogs ); ml.cntLogs= 0;
            lox.error  ( "DOM_OFF2"     , "test" );    UT_EQ(  0, ml.cntLogs ); ml.cntLogs= 0;

            lox.verbose( "ATSTART"      , "test" );    UT_EQ(  0, ml.cntLogs ); ml.cntLogs= 0;
            lox.info   ( "ATSTART"      , "test" );    UT_EQ(  1, ml.cntLogs ); ml.cntLogs= 0;
            lox.verbose( "ATSTARTXX"    , "test" );    UT_EQ(  0, ml.cntLogs ); ml.cntLogs= 0;
            lox.info   ( "ATSTARTXX"    , "test" );    UT_EQ(  1, ml.cntLogs ); ml.cntLogs= 0;
            lox.verbose( "XXATSTART"    , "test" );    UT_EQ(  0, ml.cntLogs ); ml.cntLogs= 0;
            lox.info   ( "XXATSTART"    , "test" );    UT_EQ(  0, ml.cntLogs ); ml.cntLogs= 0;
            lox.verbose( "XATSTARTX"    , "test" );    UT_EQ(  0, ml.cntLogs ); ml.cntLogs= 0;
            lox.info   ( "XATSTARTX"    , "test" );    UT_EQ(  0, ml.cntLogs ); ml.cntLogs= 0;

            lox.verbose( "ATEND"        , "test" );    UT_EQ(  0, ml.cntLogs ); ml.cntLogs= 0;
            lox.info   ( "ATEND"        , "test" );    UT_EQ(  1, ml.cntLogs ); ml.cntLogs= 0;
            lox.verbose( "ATENDXX"      , "test" );    UT_EQ(  0, ml.cntLogs ); ml.cntLogs= 0;
            lox.info   ( "ATENDXX"      , "test" );    UT_EQ(  0, ml.cntLogs ); ml.cntLogs= 0;
            lox.verbose( "XXATEND"      , "test" );    UT_EQ(  0, ml.cntLogs ); ml.cntLogs= 0;
            lox.info   ( "XXATEND"      , "test" );    UT_EQ(  1, ml.cntLogs ); ml.cntLogs= 0;
            lox.verbose( "XATENDX"      , "test" );    UT_EQ(  0, ml.cntLogs ); ml.cntLogs= 0;
            lox.info   ( "XATENDX"      , "test" );    UT_EQ(  0, ml.cntLogs ); ml.cntLogs= 0;

            lox.verbose( "SUBSTR"       , "test" );    UT_EQ(  0, ml.cntLogs ); ml.cntLogs= 0;
            lox.info   ( "SUBSTR"       , "test" );    UT_EQ(  1, ml.cntLogs ); ml.cntLogs= 0;
            lox.verbose( "SUBSTRXX"     , "test" );    UT_EQ(  0, ml.cntLogs ); ml.cntLogs= 0;
            lox.info   ( "SUBSTRXX"     , "test" );    UT_EQ(  1, ml.cntLogs ); ml.cntLogs= 0;
            lox.verbose( "XXSUBSTR"     , "test" );    UT_EQ(  0, ml.cntLogs ); ml.cntLogs= 0;
            lox.info   ( "XXSUBSTR"     , "test" );    UT_EQ(  1, ml.cntLogs ); ml.cntLogs= 0;
            lox.verbose( "XSUBSTRX"     , "test" );    UT_EQ(  0, ml.cntLogs ); ml.cntLogs= 0;
            lox.info   ( "XSUBSTRX"     , "test" );    UT_EQ(  1, ml.cntLogs ); ml.cntLogs= 0;

            // overwrite config
            lox.verbose( "/OVERWRITE"   , "test" );    UT_EQ(  0, ml.cntLogs ); ml.cntLogs= 0;
            lox.info   ( "/OVERWRITE"   , "test" );    UT_EQ(  1, ml.cntLogs ); ml.cntLogs= 0;

            lox.setVerbosity( ml , Verbosity.WARNING, "/OVERWRITE" ); // does not overwrite
            lox.verbose( "/OVERWRITE"   , "test" );    UT_EQ(  0, ml.cntLogs ); ml.cntLogs= 0;
            lox.info   ( "/OVERWRITE"   , "test" );    UT_EQ(  1, ml.cntLogs ); ml.cntLogs= 0;

            lox.setVerbosity( ml , Verbosity.WARNING, "/OVERWRITE", Configuration.PRIO_PROTECTED_VALUES - 1 ); // does overwrite
            lox.verbose( "/OVERWRITE"   , "test" );    UT_EQ(  0, ml.cntLogs ); ml.cntLogs= 0;
            lox.info   ( "/OVERWRITE"   , "test" );    UT_EQ(  0, ml.cntLogs ); ml.cntLogs= 0;
            lox.warning( "/OVERWRITE"   , "test" );    UT_EQ(  1, ml.cntLogs ); ml.cntLogs= 0;

            // overwrite non-config
            lox.error  ( "/A"           , "test" );    UT_EQ(  0, ml.cntLogs ); ml.cntLogs= 0;
            lox.error  ( "/A/B"         , "test" );    UT_EQ(  0, ml.cntLogs ); ml.cntLogs= 0;
            lox.error  ( "/A/C"         , "test" );    UT_EQ(  0, ml.cntLogs ); ml.cntLogs= 0;

            lox.setVerbosity( ml , Verbosity.INFO, "/A/B", Configuration.PRIO_DEFAULT_VALUES -1 ); // does not overwrite
            lox.verbose( "/A/B"         , "test" );    UT_EQ(  0, ml.cntLogs ); ml.cntLogs= 0;
            lox.info   ( "/A/B"         , "test" );    UT_EQ(  0, ml.cntLogs ); ml.cntLogs= 0;

            lox.setVerbosity( ml , Verbosity.INFO, "/A/B", Configuration.PRIO_DEFAULT_VALUES); // does overwrite
            lox.verbose( "/A/B"         , "test" );    UT_EQ(  0, ml.cntLogs ); ml.cntLogs= 0;
            lox.info   ( "/A/B"         , "test" );    UT_EQ(  1, ml.cntLogs ); ml.cntLogs= 0;

            lox.setVerbosity( ml , Verbosity.INFO, "/A/B", Configuration.PRIO_DEFAULT_VALUES + 1 ); // one higher
            lox.verbose( "/A/B"         , "test" );    UT_EQ(  0, ml.cntLogs ); ml.cntLogs= 0;
            lox.info   ( "/A/B"         , "test" );    UT_EQ(  1, ml.cntLogs ); ml.cntLogs= 0;

            lox.setVerbosity( ml , Verbosity.VERBOSE, "/A" );
            lox.verbose( "/A"           , "test" );    UT_EQ(  1, ml.cntLogs ); ml.cntLogs= 0;
            lox.verbose( "/A/B"         , "test" );    UT_EQ(  0, ml.cntLogs ); ml.cntLogs= 0;
            lox.info   ( "/A/B"         , "test" );    UT_EQ(  1, ml.cntLogs ); ml.cntLogs= 0;
            lox.verbose( "/A/C"         , "test" );    UT_EQ(  1, ml.cntLogs ); ml.cntLogs= 0;

            //lox.state( "", Verbosity.INFO, "Configuration now is:" );

            ALox.config.removePlugin( iniFile );
            lox.removeLogger( ml );
            lox.removeLogger( "CONSOLE" );
        }
    }
}
