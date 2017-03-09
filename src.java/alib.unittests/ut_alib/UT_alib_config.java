// #################################################################################################
//  Unit Tests - AWorx Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
package ut_alib;
import java.io.BufferedWriter;
import java.io.FileWriter;

import org.junit.Test;

import com.aworx.lib.strings.Substring;
import com.aworx.lib.config.Configuration;
import com.aworx.lib.config.InMemoryPlugin;
import com.aworx.lib.config.IniFile;
import com.aworx.lib.config.Variable;
import com.aworx.lox.ALox;

import ut_com_aworx.AWorxUnitTesting;


public class UT_alib_config extends AWorxUnitTesting
{
/** ********************************************************************************************
 * CommandLineArgs
 **********************************************************************************************/
@SuppressWarnings("static-method")
@Test
public void CommandLineArgs()
{
    UT_INIT();

    String[] args=
    {
        "-SingleHyphen=12",
        "--DoubleHyphen=yes",
        "--Empty",
        "--Whitespaces   =  Hello Test  ",
        "--integer =  42",
        "--double =  3.14",
        "-Home=overwritten",
        "--ALIB_TEST=passed",
    };

    Configuration cfg= new Configuration();
    cfg.setCommandLineArgs( args );
    Variable var= new Variable();
    UT_EQ( Configuration.PRIO_CMD_LINE,    cfg.load   ( var.define( "",      "SingleHyphen" )) );   UT_EQ( "12",            var.getString()       );
                                           cfg.load   ( var.define( "",      "DoubleHyphen" ));     UT_EQ( true,            var.isTrue()    );
    UT_EQ( Configuration.PRIO_CMD_LINE,    var.priority);

    UT_EQ( Configuration.PRIO_CMD_LINE,    cfg.load   ( var.define( "",      "Empty"        )) );   UT_EQ( "",              var.getString()       );
    UT_EQ( Configuration.PRIO_CMD_LINE,    cfg.load   ( var.define( "",      "Whitespaces"  )) );   UT_EQ( "Hello Test",    var.getString()       );
    UT_EQ( Configuration.PRIO_CMD_LINE,    cfg.load   ( var.define( "",      "HOME"         )) );   UT_EQ( "overwritten",   var.getString()       );
    UT_EQ( Configuration.PRIO_CMD_LINE,    cfg.load   ( var.define( "",      "integer"      )) );   UT_EQ( 42,              var.getInteger()    );
    UT_EQ( 0,                              cfg.load   ( var.define( "",      "notexistent"  )) );   UT_EQ( 0,               var.getInteger()    );
    UT_EQ( Configuration.PRIO_CMD_LINE,    cfg.load   ( var.define( "",      "integer"      )) );   UT_EQ( 42,              var.getInteger()    );
    UT_EQ( Configuration.PRIO_CMD_LINE,    cfg.load   ( var.define( "",      "double"       )) );   UT_EQ( 3.14,            var.getDouble() );
    UT_EQ( 0,                              cfg.load   ( var.define( "",      "notexistent"  )) );   UT_EQ( 0.0,             var.getDouble() );
    UT_EQ( Configuration.PRIO_CMD_LINE,    cfg.load   ( var.define( "",      "double"       )) );   UT_EQ( 3.14,            var.getDouble() );
    UT_EQ( Configuration.PRIO_CMD_LINE,    cfg.load   ( var.define( "ALIB",  "test"         )) );   UT_EQ( "passed",        var.getString()       );
}

/** ********************************************************************************************
 * IniFile
 **********************************************************************************************/
@SuppressWarnings("static-method")
@Test
public void IniFile()
{
    UT_INIT();

    // write sample config file
    //UT_PRINT(""); UT_PRINT( "### Configuration with IniFile ###" );
    String iniFileContents=
     "##########################################################################"  +"\n"
    +"## unit test config file"                                                    +"\n"
    +"##########################################################################"  +"\n"
    +"// this is also a comment"                                                   +"\n"
    +"; and this is as well"                                                       +"\n"
    +""                                                                            +"\n"
    +"HOME= overwritten_by_environment"                                            +"\n"
    +""                                                                            +"\n"
    +"concat=    start =5,          \\"                                            +"\n"
    +"           end   =32,       \\"                                              +"\n"
    +"           \\#no comment,   \\"                                              +"\n"
    +"           \\;nocomment,   \\"                                               +"\n"
    +"           ;a comment,   \\"                                                 +"\n"
    +"           getsLonger,    \\"                                                +"\n"
    +"           getsLongerxxx,   \\"                                              +"\n"
    +"           getsshorter,    \\"                                               +"\n"
    +"           getsLongerxxxxx,  \\"                                             +"\n"
    +"           getsLongerxxxxxxxxx,  \\"                                         +"\n"
    +"           getsshorterxx,    \\"                                             +"\n"
    +"           last"                                                             +"\n"
    +""                                                                            +"\n"
    +""                                                                            +"\n"
    +"CUBA=a country"                                                              +"\n"
    +"# The size "                                                                 +"\n"
    +" SIZE=  25 "                                                                 +"\n"
    +""                                                                            +"\n"
    +"# doble comment line"                                                        +"\n"
    +"# double, i meant"                                                           +"\n"
    +"2Comments= much talk"                                                        +"\n"
    +""                                                                            +"\n"
    +"# A great section"                                                           +"\n"
    +"[Great Section] "                                                            +"\n"
    +"SectionVar=5"                                                                +"\n"
    +"Double=12.3"                                                                 +"\n"
    +"Tricky=  backslash\\\\"                                                      +"\n"
    +"# A 2nd section"                                                             +"\n"
    +"[2nd Section] "                                                              +"\n"
    +"SectionVar=6"                                                                +"\n"
    +""                                                                            +"\n"
    +""                                                                            +"\n"
    +"[Great Section] "                                                            +"\n"
    +"SECTION_CONTINUED   = yEs"                                                   +"\n"
    +""                                                                            +"\n"
    +""                                                                            +"\n"
    +"[ESC] "                                                                      +"\n"
    +"Blanks=  \" x \""                                                            +"\n"
    +"Blanks2= \" x \" \\"                                                         +"\n"
    +"         \" y \" "                                                           +"\n"
    +"Tabs=\t\t\\tx\\t"                                                            +"\n"
    +"nrslash= \"\\n\\r//\\\\\""                                                   +"\n"
   ;

    String fileName= System.getProperty("user.dir") + "/unittest_testiniFile.cfg";

    // write sample config file
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
    UT_TRUE( (IniFile.Status.OK == iniFile.lastStatus) );

    // check some values
    Variable var= new Variable();

    iniFile.load( var.define("",    "CUBA"        ) );   UT_EQ( "a country",      var.getString() );
    iniFile.load( var.define("",    "cUbA"        ) );   UT_EQ( "a country",      var.getString() );
    iniFile.load( var.define("",    "SIZE"        ) );   UT_EQ( "25",             var.getString() );
    iniFile.load( var.define("",    "concat", ',' ) );   UT_EQ( 11 , var.size());
                                                         UT_EQ( "start =5",       var.getString(0) );
                                                         UT_EQ( "end   =32",      var.getString(1) );
                                                         UT_EQ( "#no comment"    ,var.getString(2) );
                                                         UT_EQ( ";nocomment"     ,var.getString(3) );

    iniFile.load( var.define("ESC", "Blanks" ) );   UT_EQ( " x ",             var.getString() );
    iniFile.load( var.define("ESC", "Blanks2") );   UT_EQ( " x  y ",          var.getString() );
    iniFile.load( var.define("ESC", "Tabs"   ) );   UT_EQ( "\tx\t",           var.getString() );
    iniFile.load( var.define("ESC", "nrslash") );   UT_EQ( "\n\r//\\", var.getString() );

    iniFile.load( var.define("Great Section",  "SectionVar"        ) );   UT_EQ( "5",  var.getString() );
    iniFile.load( var.define("2nd Section",    "SectionVar"        ) );   UT_EQ( "6",  var.getString() );
    iniFile.load( var.define("Great Section",  "SECTION_CONTINUED" ) );   UT_EQ( "yEs",var.getString() );
    iniFile.load( var.define("Great Section",  "Tricky"            ) );   UT_EQ( "backslash\\",  var.getString() );

    // add it to ALIB config
    ALox.init( null );
    Configuration.Default.insertPlugin( iniFile, Configuration.PRIO_INI_FILE );
    Configuration.Default.load( var.define( "",               "CUBA"              ) );   UT_EQ( "a country"  , var.getString() );
    Configuration.Default.load( var.define( "",               "cUbA"              ) );   UT_EQ( "a country"  , var.getString() );
    Configuration.Default.load( var.define( "",               "SIZE"              ) );   UT_EQ( "25"         , var.getString() );
    Configuration.Default.load( var.define( "",               "concat"            ) );   UT_EQ( 11 , var.size());
                                                                             UT_EQ( "start =5",  var.getString(0) );
                                                                             UT_EQ( "end   =32", var.getString(1) );
    Configuration.Default.load( var.define( "Great Section",  "SectionVar"        ) );   UT_EQ( "5"          , var.getString() );
    Configuration.Default.load( var.define( "2nd Section",    "SectionVar"        ) );   UT_EQ( "6"          , var.getString() );
    Configuration.Default.load( var.define( "Great Section",  "SECTION_CONTINUED" ) );   UT_EQ( "yEs"        , var.getString() );
    Configuration.Default.load( var.define( "Great Section",  "Tricky"            ) );   UT_EQ( "backslash\\", var.getString() );
    Configuration.Default.load( var.define( "Great Section",  "SECTION_CONTINUED" ) );   UT_TRUE( var.isTrue() );


    // check if environment variable "home" overwrites INI file
    var.define( "", "hOme" );
    iniFile.load( var );    UT_EQ( "overwritten_by_environment", var.getString() );
    int prio= var.load();   UT_EQ( Configuration.PRIO_ENVIRONMENT, prio );
    UT_TRUE( var.getString().isNotEmpty() );
    UT_TRUE( !var.getString().equals( ("overwritten_by_environment" ) ) );


    // change a value and write a new one
    var.define( "New Section",  "newvar");
    var.priority= Configuration.PRIO_INI_FILE;
    UT_EQ( Configuration.PRIO_INI_FILE, Configuration.Default.store( var, "new" ) );
    Configuration.Default.load  ( var.define("New Section",  "newvar") );  UT_EQ( "new",   var.getString() );

    var.define( "", "newvar");
    var.priority= Configuration.PRIO_INI_FILE;
    UT_EQ( Configuration.PRIO_INI_FILE, Configuration.Default.store( var, "aworx") );
    Configuration.Default.load  ( var.define("",             "newvar") );  UT_EQ( "aworx", var.getString() );


    var.define( "",   "newvarList", ',');
    var.add("val1=5");
    var.add("val2=10");
    var.add("val3=hello");
    var.priority= Configuration.PRIO_INI_FILE;
    UT_EQ( Configuration.PRIO_INI_FILE, Configuration.Default.store(var) );
    Configuration.Default.load (  var.define( "",  "newvarList")   );


    var.define( "",   "commented", ',', "2lines");
    var.priority= Configuration.PRIO_INI_FILE;
    UT_EQ( Configuration.PRIO_INI_FILE, Configuration.Default.store( var, "this is c-line 1 \nand this line 2" ) );


    // write the file
    iniFile.fileName._(".writeback.txt");
    iniFile.writeFile();

    // load the written file into another config
    IniFile readBack= new IniFile( iniFile.fileName.toString() );
    Variable varBack= new Variable();

    // compare all
    UT_TRUE( (IniFile.Status.OK == readBack.lastStatus) );

    {
        Substring orig= new Substring();
        Substring back= new Substring();
        for ( InMemoryPlugin.Section section : iniFile.sections )
        {
            for ( InMemoryPlugin.Entry entry : section.entries )
            {
                UT_PRINT( "Reading variable {!Q}/{!Q}", section.name, entry.name );


                char delim= '\0';
                if(     entry.name.equals("concat")
                    ||  entry.name.equals("newvarList")       )
                    delim= ',';

                iniFile .load( var    .define( section.name, entry.name, delim) );
                readBack.load( varBack.define( section.name, entry.name, delim) );

                UT_EQ( var.size(), varBack.size() );
                for ( int i= 0; i< var.size(); i++ )
                {
                    int idx= var.getString(i).indexOf('=');
                    if( idx < 0 )
                    {
                        UT_EQ( var.getString(i), varBack.getString(i) );
                    }
                    else
                    {
                        int idxBack= varBack.getString(i).indexOf('=');
                        orig.set( var    .getString(i), 0, idx     );
                        back.set( varBack.getString(i), 0, idxBack );
                        UT_EQ( orig.trim().toString(), back.trim().toString() );
                        orig.set( var    .getString(i), idx     +1 );
                        back.set( varBack.getString(i), idxBack +1 );
                        UT_EQ( orig.trim().toString(), back.trim().toString() );
                    }
                }
            }
        }
    }

    readBack.load ( var.define( "New Section",  "newvar") );   UT_EQ(   "new", var.getString() );
    readBack.load ( var.define( "",             "newvar") );   UT_EQ( "aworx", var.getString() );


    Configuration.Default.removePlugin( iniFile );


    Configuration.Default.insertPlugin( readBack, Configuration.PRIO_INI_FILE );
    Configuration.Default.load ( var.define( "New Section",  "newvar") );   UT_EQ( "new"   , var.getString() );
    Configuration.Default.load ( var.define( "",             "newvar") );   UT_EQ( "aworx" , var.getString() );

    Configuration.Default.removePlugin( readBack );
}

/** ********************************************************************************************
 * ConfigDefaultAndProtected
 **********************************************************************************************/
@SuppressWarnings("static-method")
@Test
public void ConfigDefaultAndProtected()
{
    UT_INIT();

    String[] args=
    {
        "COMMANDLINE",
        "--TEST_VARIABLE=fromCommandLine",
    };

    Configuration cfg= new Configuration();
    cfg.setCommandLineArgs( args );

    Variable var= new Variable();

    // command line
    UT_EQ( Configuration.PRIO_CMD_LINE,    cfg.load  ( var.define( "TEST",      "VARIABLE" ) ) );   UT_EQ( "fromCommandLine"    ,var.getString() );

    // set default, does not overwrite
    cfg.defaultValues.store( var.define( "TEST", "VARIABLE"), "not overwriting" );
    UT_EQ( Configuration.PRIO_CMD_LINE,    cfg.load  ( var.define( "TEST",      "VARIABLE" ) ) );   UT_EQ( "fromCommandLine"    ,var.getString() );

    // set protected, overwrites command line
    cfg.protectedValues.store( var.define( "TEST", "VARIABLE"), "does overwrite" );
    UT_EQ( Configuration.PRIO_PROTECTED,   cfg.load  ( var.define( "TEST",      "VARIABLE" ) ) );   UT_EQ( "does overwrite"     ,var.getString() );

    // set default, something else
    cfg.defaultValues.store( var.define( "TEST", "VAR2"), "this is var 2" );
    UT_EQ( Configuration.PRIO_DEFAULT,     cfg.load  ( var.define( "TEST",      "VAR2"     ) ) );   UT_EQ( "this is var 2"      ,var.getString() );

    // set and remove an entry using plugin interface
    var.define( "TEST", "Remove" );     UT_EQ( 0, var.size() );     UT_EQ( -1                           ,var.priority );
    cfg.defaultValues.load( var );      UT_EQ( 0, var.size() );     UT_EQ( -1                           ,var.priority );
    var.add("To be deleted");     UT_EQ( 1, var.size() );     UT_EQ( -1                           ,var.priority );
    cfg.defaultValues.store( var );     UT_EQ( 1, var.size() );     UT_EQ( -1                           ,var.priority );
    var.define( "TEST", "Remove" );     UT_EQ( 0, var.size() );     UT_EQ( -1                           ,var.priority );
    cfg.defaultValues.load( var );      UT_EQ( 1, var.size() );     UT_EQ( -1                           ,var.priority );
    var.clearValues();                  UT_EQ( 0, var.size() );     UT_EQ( -1                           ,var.priority );
    cfg.defaultValues.store( var );     UT_EQ( 0, var.size() );     UT_EQ( -1                           ,var.priority );
    var.define( "TEST", "Remove" );     UT_EQ( 0, var.size() );     UT_EQ( -1                           ,var.priority );
    cfg.defaultValues.load( var );      UT_EQ( 0, var.size() );     UT_EQ( -1                           ,var.priority );

    // set and remove an entry using configuration interface
    cfg              .load ( var );     UT_EQ( 0, var.size() );     UT_EQ(  0                           ,var.priority );
    cfg              .store( var );     UT_EQ( 0, var.size() );     UT_EQ(  0                           ,var.priority );
    var.add("To be deleted");     UT_EQ( 1, var.size() );     UT_EQ(  0                           ,var.priority );
    cfg              .store( var );     UT_EQ( 1, var.size() );     UT_EQ( Configuration.PRIO_DEFAULT   ,var.priority );
    var.define( "TEST", "Remove" );     UT_EQ( 0, var.size() );     UT_EQ( -1                           ,var.priority );
    cfg              .load ( var );     UT_EQ( 1, var.size() );     UT_EQ( Configuration.PRIO_DEFAULT   ,var.priority );
    var.define( "TEST", "Remove" );     UT_EQ( 0, var.size() );     UT_EQ( -1                           ,var.priority );
    cfg              .store( var );     UT_EQ( 0, var.size() );     UT_EQ( Configuration.PRIO_DEFAULT   ,var.priority );
    cfg              .load ( var );     UT_EQ( 0, var.size() );     UT_EQ( 0                            ,var.priority );
    var.define( "TEST", "Remove" );     UT_EQ( 0, var.size() );     UT_EQ( -1                           ,var.priority );
    cfg              .load ( var );     UT_EQ( 0, var.size() );     UT_EQ( 0                            ,var.priority );

    // protected
    var.define( "TEST", "Protected");   UT_EQ( 0, var.size() );                 UT_EQ( -1                           ,var.priority );
    var.defaultValue._( "Default"  );
    var.storeDefault( "def par");       UT_EQ( "def par",   var.getString() );  UT_EQ( Configuration.PRIO_DEFAULT   ,var.priority );

    var.clearValues();
    var.add( "def var" );
    var.storeDefault();                 UT_EQ( "def var",   var.getString() );  UT_EQ( Configuration.PRIO_DEFAULT   ,var.priority );

    var.clearValues();
    var.storeDefault();                 UT_EQ( "Default",   var.getString() );  UT_EQ( Configuration.PRIO_DEFAULT   ,var.priority );

    var.clearValues();
    var.add( "def var" );
    var.protect();                      UT_EQ( "def var",   var.getString() );  UT_EQ( Configuration.PRIO_PROTECTED ,var.priority );
    var.protect("prot par");            UT_EQ( "prot par",  var.getString() );  UT_EQ( Configuration.PRIO_PROTECTED ,var.priority );
    var.clearValues();
    var.protect();                      UT_EQ( "Default",   var.getString() );  UT_EQ( Configuration.PRIO_PROTECTED ,var.priority );
    var.defaultValue.setNull();
    var.clearValues();
    var.protect();                      UT_EQ( 0, var.size()                );  UT_EQ( Configuration.PRIO_PROTECTED ,var.priority );
    var.load();                         UT_EQ( "Default",   var.getString() );  UT_EQ( Configuration.PRIO_DEFAULT   ,var.priority );

}

/** ********************************************************************************************
 * ConfigReplacementVariables
 **********************************************************************************************/
@SuppressWarnings("static-method")
@Test
public void ConfigReplacementVariables()
{
    UT_INIT();

    String[] args=
    {
        "COMMANDLINE",
        "--REPL_CMDLINE=ReplCommandLine",
        "--NOCATCMDLINE=NoCatCommandLine",
    };

    Configuration cfg= new Configuration();
    cfg.setCommandLineArgs( args );
    Variable var= new Variable();

    // replacements from command line plugin
    var.define( "TEST", "VARIABLE" );
    cfg.protectedValues.store( var, "no replacment"                ); cfg.load( var );   UT_EQ( "no replacment"                   ,var.getString()   );
    cfg.protectedValues.store( var, "$UKN"                         ); cfg.load( var );   UT_EQ( ""                                ,var.getString()   );
    cfg.protectedValues.store( var, "-$UKN * $UKN2-"               ); cfg.load( var );   UT_EQ( "- * -"                           ,var.getString()   );
    cfg.protectedValues.store( var, "$NOCATCMDLINE"                ); cfg.load( var );   UT_EQ( "NoCatCommandLine"                ,var.getString()   );
    cfg.protectedValues.store( var, "$$NOCATCMDLINE$"              ); cfg.load( var );   UT_EQ( "$NoCatCommandLine$"              ,var.getString()   );
    cfg.protectedValues.store( var, "$REPL_CMDLINE"                ); cfg.load( var );   UT_EQ( "ReplCommandLine"                 ,var.getString()   );
    cfg.protectedValues.store( var, "$REPL_ CMDLINE"               ); cfg.load( var );   UT_EQ( " CMDLINE"                        ,var.getString()   );
    cfg.protectedValues.store( var, "$repL_CmdLine"                ); cfg.load( var );   UT_EQ( "ReplCommandLine"                 ,var.getString()   );
    cfg.protectedValues.store( var, "$repL_CmdLine$repL_CmdLine"   ); cfg.load( var );   UT_EQ( "ReplCommandLineReplCommandLine"  ,var.getString()   );
    cfg.protectedValues.store( var, "$repL_CmdLine $repL_CmdLine"  ); cfg.load( var );   UT_EQ( "ReplCommandLine ReplCommandLine" ,var.getString()   );

    // replacements without category name
    cfg.protectedValues.store( var.define(""    , "NOCAT"   ), "NoCat"    );
    cfg.protectedValues.store( var.define(""    , "NO_CAT"  ), "No_cat"   );
    cfg.protectedValues.store( var.define("TEST", "VARIABLE"), "$nocat"   ); cfg.load( var.define("TEST",  "VARIABLE") );   UT_EQ( "NoCat"   ,var.getString()   );
    cfg.protectedValues.store( var.define("TEST", "VARIABLE"), "$_nocat"  ); cfg.load( var.define("TEST",  "VARIABLE") );   UT_EQ( "NoCat"   ,var.getString()   );

    // need to add an underscore, if no category but name contains underscore!
    cfg.protectedValues.store( var.define("TEST", "VARIABLE"), "$no_cat"  ); cfg.load( var.define("TEST",  "VARIABLE") );   UT_EQ( ""        ,var.getString()   );
    cfg.protectedValues.store( var.define("TEST", "VARIABLE"), "$_no_cat" ); cfg.load( var.define("TEST",  "VARIABLE") );   UT_EQ( "No_cat"  ,var.getString()   );


    // nested variables
    cfg.protectedValues.store( var.define("Rep", "Var1"     ), "$Rep_Var2");
    cfg.protectedValues.store( var.define("Rep", "Var2"     ), "nested"   );
    cfg.protectedValues.store( var.define("TEST", "VARIABLE"), "$rep_var2"); cfg.load( var.define("TEST",  "VARIABLE") );   UT_EQ( "nested"                          ,var.getString()   );
    cfg.protectedValues.store( var.define("TEST", "VARIABLE"), "$rep_var1"); cfg.load( var.define("TEST",  "VARIABLE") );   UT_EQ( "nested"                          ,var.getString()   );

    // illegal recursion
    UT_PRINT( "One warning should follow" );
    cfg.protectedValues.store( var.define("Rep", "Var1"     ), "$Rep_Var2" );
    cfg.protectedValues.store( var.define("Rep", "Var2"     ), "$Rep_Var1" );
    cfg.protectedValues.store( var.define("TEST", "VARIABLE"), "$rep_var1" ); cfg.load( var.define("TEST",  "VARIABLE") );

    // custom variable definitions
    cfg.protectedValues.store( var.define("Rep", "CUST"     ), "cf"           );

    cfg.protectedValues.store( var.define("TEST", "VARIABLE"), ">>$REP_CUST<<"); cfg.load( var.define("TEST",  "VARIABLE") );   UT_EQ( ">>cf<<"                          ,var.getString()   );

    cfg.substitutionVariableStart._()._( "${" );
    cfg.substitutionVariableEnd  ._()._( "}"  );
    var.define( "TEST", "VARIABLE" );
    cfg.protectedValues.store( var, ">>${REP_CUST}<<"              ); cfg.load( var );   UT_EQ( ">>cf<<"                          ,var.getString()   );

    cfg.substitutionVariableStart._()._( "€€€-");
    cfg.substitutionVariableEnd  ._()._( "--"  );
    cfg.protectedValues.store( var, ">>€€€-REP_CUST--<<"           ); cfg.load( var );   UT_EQ( ">>cf<<"                          ,var.getString()   );
    cfg.protectedValues.store( var, ">>€€€-REP_CUST--"             ); cfg.load( var );   UT_EQ( ">>cf"                            ,var.getString()   );
    cfg.protectedValues.store( var, "€€€-REP_CUST--"               ); cfg.load( var );   UT_EQ( "cf"                              ,var.getString()   );
    cfg.protectedValues.store( var, "€€€-REP_CUST--€€€-REP_CUST--" ); cfg.load( var );   UT_EQ( "cfcf"                            ,var.getString()   );
    cfg.protectedValues.store( var, "€€-REP_CUST--"                ); cfg.load( var );   UT_EQ( "€€-REP_CUST--"                   ,var.getString()   );

    UT_PRINT( "One warning should follow" );
    cfg.protectedValues.store( var, "€€€-REP_CUST-"                ); cfg.load( var );   UT_EQ( "€€€-REP_CUST-"                   ,var.getString()   );

    cfg.substitutionVariableStart._()._( "$" );
    cfg.substitutionVariableEnd._();

    // multi line replacements
    cfg.defaultValues.store( var.define("ML", "REPL1", ';' ), "repl1-v1;repl1-v2"   );
    cfg.defaultValues.store( var.define("ML", "REPL2", ';' ), "repl2-v1;repl2-v2"   );
    cfg.defaultValues.store( var.define("ML", "VAR"  , ';' ), "$ML_REPL1;$ML_REPL2" );
    var.define("ML", "VAR", ';' );
    cfg.load( var );
    UT_EQ( 4, var.size() );
    UT_EQ( "repl1-v1", var.getString(0) );
    UT_EQ( "repl1-v2", var.getString(1) );
    UT_EQ( "repl2-v1", var.getString(2) );
    UT_EQ( "repl2-v2", var.getString(3) );
}

}
