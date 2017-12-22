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

import com.aworx.lib.ALIB;
import com.aworx.lib.strings.Substring;
import com.aworx.lib.config.Configuration;
import com.aworx.lib.config.CLIArgs;
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
    UT_EQ( Configuration.PRIO_CLI_ARGS,    cfg.load   ( var.declare( "",      "SingleHyphen" )) );   UT_EQ( "12",            var.getString()   );
                                                 cfg.load   ( var.declare( "",      "DoubleHyphen" ));     UT_EQ( true,            var.isTrue()      );
    UT_EQ( Configuration.PRIO_CLI_ARGS,    var.priority);

    UT_EQ( Configuration.PRIO_CLI_ARGS,    cfg.load   ( var.declare( "",      "Empty"        )) );   UT_EQ( "",              var.getString()   );
    UT_EQ( Configuration.PRIO_CLI_ARGS,    cfg.load   ( var.declare( "",      "Whitespaces"  )) );   UT_EQ( "Hello Test",    var.getString()   );
    UT_EQ( Configuration.PRIO_CLI_ARGS,    cfg.load   ( var.declare( "",      "HOME"         )) );   UT_EQ( "overwritten",   var.getString()   );
    UT_EQ( Configuration.PRIO_CLI_ARGS,    cfg.load   ( var.declare( "",      "integer"      )) );   UT_EQ( 42,              var.getInteger()  );
    UT_EQ( 0,                                    cfg.load   ( var.declare( "",      "notexistent"  )) );   UT_EQ( 0,               var.getInteger()  );
    UT_EQ( Configuration.PRIO_CLI_ARGS,    cfg.load   ( var.declare( "",      "integer"      )) );   UT_EQ( 42,              var.getInteger()  );
    UT_EQ( Configuration.PRIO_CLI_ARGS,    cfg.load   ( var.declare( "",      "double"       )) );   UT_EQ( 3.14,            var.getDouble()   );
    UT_EQ( 0,                                    cfg.load   ( var.declare( "",      "notexistent"  )) );   UT_EQ( 0.0,             var.getDouble()   );
    UT_EQ( Configuration.PRIO_CLI_ARGS,    cfg.load   ( var.declare( "",      "double"       )) );   UT_EQ( 3.14,            var.getDouble()   );
    UT_EQ( Configuration.PRIO_CLI_ARGS,    cfg.load   ( var.declare( "ALIB",  "test"         )) );   UT_EQ( "passed",        var.getString()   );


    UT_EQ( 0,                                    cfg.load   ( var.declare( "IGNORE","Home"         )) );
    cfg.getPluginTypeSafe(CLIArgs.class).defaultCategories.add("IGNORE");
    UT_EQ( Configuration.PRIO_CLI_ARGS,    cfg.load   ( var.declare( "IGNORE","Home"         )) );   UT_EQ( "overwritten",   var.getString()       );
    UT_EQ( 0                                   , cfg.load   ( var.declare( "IGNORE","Homexyz"      )) );
    cfg.getPluginTypeSafe(CLIArgs.class).allowedMinimumShortCut=5;
    UT_EQ( 0                                   , cfg.load   ( var.declare( "IGNORE","Homexyz"      )) );
    cfg.getPluginTypeSafe(CLIArgs.class).allowedMinimumShortCut=4;
    UT_EQ( Configuration.PRIO_CLI_ARGS   , cfg.load   ( var.declare( "IGNORE","Homexyz"      )) );   UT_EQ( "overwritten",   var.getString()       );

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

    iniFile.load( var.declare("",    "CUBA"        ) );   UT_EQ( "a country",      var.getString() );
    iniFile.load( var.declare("",    "cUbA"        ) );   UT_EQ( "a country",      var.getString() );
    iniFile.load( var.declare("",    "SIZE"        ) );   UT_EQ( "25",             var.getString() );
    iniFile.load( var.declare("",    "concat", ',' ) );   UT_EQ( 11 , var.size());
                                                          UT_EQ( "start =5",       var.getString(0) );
                                                          UT_EQ( "end   =32",      var.getString(1) );
                                                          UT_EQ( "#no comment"    ,var.getString(2) );
                                                          UT_EQ( ";nocomment"     ,var.getString(3) );

    iniFile.load( var.declare("ESC", "Blanks" ) );        UT_EQ( " x ",             var.getString() );
    iniFile.load( var.declare("ESC", "Blanks2") );        UT_EQ( " x  y ",          var.getString() );
    iniFile.load( var.declare("ESC", "Tabs"   ) );        UT_EQ( "\tx\t",           var.getString() );
    iniFile.load( var.declare("ESC", "nrslash") );        UT_EQ( "\n\r//\\", var.getString() );

    iniFile.load( var.declare("Great Section",  "SectionVar"        ) );   UT_EQ( "5",  var.getString() );
    iniFile.load( var.declare("2nd Section",    "SectionVar"        ) );   UT_EQ( "6",  var.getString() );
    iniFile.load( var.declare("Great Section",  "SECTION_CONTINUED" ) );   UT_EQ( "yEs",var.getString() );
    iniFile.load( var.declare("Great Section",  "Tricky"            ) );   UT_EQ( "backslash\\",  var.getString() );

    // add it to ALIB config
    ALIB.config.insertPlugin( iniFile, Configuration.PRIO_STANDARD );
    ALIB.config.load( var.declare( "",               "CUBA"              ) );   UT_EQ( "a country"  , var.getString() );
    ALIB.config.load( var.declare( "",               "cUbA"              ) );   UT_EQ( "a country"  , var.getString() );
    ALIB.config.load( var.declare( "",               "SIZE"              ) );   UT_EQ( "25"         , var.getString() );
    ALIB.config.load( var.declare( "",               "concat"            ) );   UT_EQ( 11 , var.size());
                                                                                UT_EQ( "start =5",  var.getString(0) );
                                                                                UT_EQ( "end   =32", var.getString(1) );
    ALIB.config.load( var.declare( "Great Section",  "SectionVar"        ) );   UT_EQ( "5"          , var.getString() );
    ALIB.config.load( var.declare( "2nd Section",    "SectionVar"        ) );   UT_EQ( "6"          , var.getString() );
    ALIB.config.load( var.declare( "Great Section",  "SECTION_CONTINUED" ) );   UT_EQ( "yEs"        , var.getString() );
    ALIB.config.load( var.declare( "Great Section",  "Tricky"            ) );   UT_EQ( "backslash\\", var.getString() );
    ALIB.config.load( var.declare( "Great Section",  "SECTION_CONTINUED" ) );   UT_TRUE( var.isTrue() );


    // check if environment variable "home" overwrites INI file
    var.declare( "", "hOme" );
    iniFile.load( var );    UT_EQ( "overwritten_by_environment", var.getString() );
    int prio= ALox.config.load( var );   UT_EQ( Configuration.PRIO_ENVIRONMENT, prio );
    UT_TRUE( var.getString().isNotEmpty() );
    UT_TRUE( !var.getString().equals( ("overwritten_by_environment" ) ) );


    // change a value and write a new one
    var.declare( "New Section",  "newvar");
    var.priority= Configuration.PRIO_STANDARD;
    UT_EQ( Configuration.PRIO_STANDARD, ALIB.config.store( var, "new" ) );
    ALIB.config.load  ( var.declare("New Section",  "newvar") );  UT_EQ( "new",   var.getString() );

    var.declare( "", "newvar");
    var.priority= Configuration.PRIO_STANDARD;
    UT_EQ( Configuration.PRIO_STANDARD, ALIB.config.store( var, "aworx") );
    ALIB.config.load  ( var.declare("",             "newvar") );  UT_EQ( "aworx", var.getString() );


    var.declare( "",   "newvarList", ',');
    var.add("val1=5");
    var.add("val2=10");
    var.add("val3=hello");
    var.priority= Configuration.PRIO_STANDARD;
    UT_EQ( Configuration.PRIO_STANDARD, ALIB.config.store(var) );
    ALIB.config.load (  var.declare( "",  "newvarList")   );


    var.declare( "",   "commented", ',', "2lines");
    var.priority= Configuration.PRIO_STANDARD;
    UT_EQ( Configuration.PRIO_STANDARD, ALIB.config.store( var, "this is c-line 1 \nand this line 2" ) );


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

                iniFile .load( var    .declare( section.name, entry.name, delim) );
                readBack.load( varBack.declare( section.name, entry.name, delim) );

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

    readBack.load ( var.declare( "New Section",  "newvar") );   UT_EQ(   "new", var.getString() );
    readBack.load ( var.declare( "",             "newvar") );   UT_EQ( "aworx", var.getString() );


    ALIB.config.removePlugin( iniFile );


    ALIB.config.insertPlugin( readBack, Configuration.PRIO_STANDARD );
    ALIB.config.load ( var.declare( "New Section",  "newvar") );   UT_EQ( "new"   , var.getString() );
    ALIB.config.load ( var.declare( "",             "newvar") );   UT_EQ( "aworx" , var.getString() );

    ALIB.config.removePlugin( readBack );
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
    InMemoryPlugin defaultValues  = cfg.getPluginTypeSafe( Configuration.PRIO_DEFAULT_VALUES   ,InMemoryPlugin.class );
    InMemoryPlugin protectedValues= cfg.getPluginTypeSafe( Configuration.PRIO_PROTECTED_VALUES ,InMemoryPlugin.class );

    Variable var= new Variable();

    // command line
    UT_EQ( Configuration.PRIO_CLI_ARGS,    cfg.load  ( var.declare( "TEST",      "VARIABLE" ) ) );   UT_EQ( "fromCommandLine"    ,var.getString() );

    // set default, does not overwrite
    defaultValues.store( var.declare( "TEST", "VARIABLE"), "not overwriting" );
    UT_EQ( Configuration.PRIO_CLI_ARGS,    cfg.load  ( var.declare( "TEST",      "VARIABLE" ) ) );   UT_EQ( "fromCommandLine"    ,var.getString() );

    // set protected, overwrites command line
    protectedValues.store( var.declare( "TEST", "VARIABLE"), "does overwrite" );
    UT_EQ( Configuration.PRIO_PROTECTED_VALUES,         cfg.load  ( var.declare( "TEST",      "VARIABLE" ) ) );   UT_EQ( "does overwrite"     ,var.getString() );

    // set default, something else
    defaultValues.store( var.declare( "TEST", "VAR2"), "this is var 2" );
    UT_EQ( Configuration.PRIO_DEFAULT_VALUES,           cfg.load  ( var.declare( "TEST",      "VAR2"     ) ) );   UT_EQ( "this is var 2"      ,var.getString() );

    // set and remove an entry using plugin interface
    var.declare( "TEST", "Remove" );    UT_EQ( 0, var.size() );     UT_EQ( 0                                ,var.priority );
    defaultValues.load( var );          UT_EQ( 0, var.size() );     UT_EQ( 0                                ,var.priority );
    var.add("To be deleted");           UT_EQ( 1, var.size() );     UT_EQ( 0                                ,var.priority );
    defaultValues.store( var );         UT_EQ( 1, var.size() );     UT_EQ( 0                                ,var.priority );
    var.declare( "TEST", "Remove" );    UT_EQ( 0, var.size() );     UT_EQ( 0                                ,var.priority );
    defaultValues.load( var );          UT_EQ( 1, var.size() );     UT_EQ( 0                                ,var.priority );
    var.clearValues();                  UT_EQ( 0, var.size() );     UT_EQ( 0                                ,var.priority );
    defaultValues.store( var );         UT_EQ( 0, var.size() );     UT_EQ( 0                                ,var.priority );
    var.declare( "TEST", "Remove" );    UT_EQ( 0, var.size() );     UT_EQ( 0                                ,var.priority );
    defaultValues.load( var );          UT_EQ( 0, var.size() );     UT_EQ( 0                                ,var.priority );

    // set and remove an entry using configuration interface
    cfg              .load ( var );     UT_EQ( 0, var.size() );     UT_EQ( 0                                ,var.priority );
    cfg              .store( var );     UT_EQ( 0, var.size() );     UT_EQ( 0                                ,var.priority );
    var.add("To be deleted");           UT_EQ( 1, var.size() );     UT_EQ( 0                                ,var.priority );
    cfg              .store( var );     UT_EQ( 1, var.size() );     UT_EQ( Configuration.PRIO_DEFAULT_VALUES,var.priority );
    var.declare( "TEST", "Remove" );    UT_EQ( 0, var.size() );     UT_EQ( 0                                ,var.priority );
    cfg              .load ( var );     UT_EQ( 1, var.size() );     UT_EQ( Configuration.PRIO_DEFAULT_VALUES,var.priority );
    var.declare( "TEST", "Remove" );    UT_EQ( 0, var.size() );     UT_EQ( 0                                ,var.priority );
    cfg              .store( var );     UT_EQ( 0, var.size() );     UT_EQ( Configuration.PRIO_DEFAULT_VALUES,var.priority );
    cfg              .load ( var );     UT_EQ( 0, var.size() );     UT_EQ( 0                                ,var.priority );
    var.declare( "TEST", "Remove" );    UT_EQ( 0, var.size() );     UT_EQ( 0                                ,var.priority );
    cfg              .load ( var );     UT_EQ( 0, var.size() );     UT_EQ( 0                                ,var.priority );

    // protected
    var.declare( "TEST", "Protected" );  UT_EQ( 0, var.size() );                             UT_EQ( 0                                ,var.priority );
    var.defaultValue._( "Default"  );
    ALox.config.storeDefault( var, "def par");       UT_EQ( "def par",   var.getString() );  UT_EQ( Configuration.PRIO_DEFAULT_VALUES,var.priority );

    var.clearValues();
    var.add( "def var" );
    ALox.config.storeDefault( var );                 UT_EQ( "def var",   var.getString() );  UT_EQ( Configuration.PRIO_DEFAULT_VALUES,var.priority );

    var.clearValues();
    ALox.config.storeDefault( var );                 UT_EQ( "Default",   var.getString() );  UT_EQ( Configuration.PRIO_DEFAULT_VALUES,var.priority );

    var.clearValues();
    var.add( "def var" );
    ALox.config.protect( var );                      UT_EQ( "def var",   var.getString() );  UT_EQ( Configuration.PRIO_PROTECTED_VALUES,var.priority );
    ALox.config.protect(var, "prot par");            UT_EQ( "prot par",  var.getString() );  UT_EQ( Configuration.PRIO_PROTECTED_VALUES,var.priority );
    var.clearValues();
    ALox.config.protect( var );                      UT_EQ( "Default",   var.getString() );  UT_EQ( Configuration.PRIO_PROTECTED_VALUES,var.priority );
    var.defaultValue.setNull();
    var.clearValues();
    ALox.config.protect( var );                      UT_EQ( 0, var.size()                );  UT_EQ( Configuration.PRIO_PROTECTED_VALUES,var.priority );
    ALox.config.load( var );                         UT_EQ( "Default",   var.getString() );  UT_EQ( Configuration.PRIO_DEFAULT_VALUES,  var.priority );

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
    InMemoryPlugin defaultValues  = cfg.getPluginTypeSafe( Configuration.PRIO_DEFAULT_VALUES   ,InMemoryPlugin.class );
    InMemoryPlugin protectedValues= cfg.getPluginTypeSafe( Configuration.PRIO_PROTECTED_VALUES ,InMemoryPlugin.class );
    cfg.setCommandLineArgs( args );
    Variable var= new Variable();

    // replacements from command line plugin
    var.declare( "TEST", "VARIABLE" );
    protectedValues.store( var, "no replacment"                ); cfg.load( var );   UT_EQ( "no replacment"                   ,var.getString()   );
    protectedValues.store( var, "$UKN"                         ); cfg.load( var );   UT_EQ( ""                                ,var.getString()   );
    protectedValues.store( var, "-$UKN * $UKN2-"               ); cfg.load( var );   UT_EQ( "- * -"                           ,var.getString()   );
    protectedValues.store( var, "$NOCATCMDLINE"                ); cfg.load( var );   UT_EQ( "NoCatCommandLine"                ,var.getString()   );
    protectedValues.store( var, "$$NOCATCMDLINE$"              ); cfg.load( var );   UT_EQ( "$NoCatCommandLine$"              ,var.getString()   );
    protectedValues.store( var, "$REPL_CMDLINE"                ); cfg.load( var );   UT_EQ( "ReplCommandLine"                 ,var.getString()   );
    protectedValues.store( var, "$REPL_ CMDLINE"               ); cfg.load( var );   UT_EQ( " CMDLINE"                        ,var.getString()   );
    protectedValues.store( var, "$repL_CmdLine"                ); cfg.load( var );   UT_EQ( "ReplCommandLine"                 ,var.getString()   );
    protectedValues.store( var, "$repL_CmdLine$repL_CmdLine"   ); cfg.load( var );   UT_EQ( "ReplCommandLineReplCommandLine"  ,var.getString()   );
    protectedValues.store( var, "$repL_CmdLine $repL_CmdLine"  ); cfg.load( var );   UT_EQ( "ReplCommandLine ReplCommandLine" ,var.getString()   );

    // replacements without category name
    protectedValues.store( var.declare(""    , "NOCAT"   ), "NoCat"    );
    protectedValues.store( var.declare(""    , "NO_CAT"  ), "No_cat"   );
    protectedValues.store( var.declare("TEST", "VARIABLE"), "$nocat"   ); cfg.load( var.declare("TEST",  "VARIABLE") );   UT_EQ( "NoCat"   ,var.getString()   );
    protectedValues.store( var.declare("TEST", "VARIABLE"), "$_nocat"  ); cfg.load( var.declare("TEST",  "VARIABLE") );   UT_EQ( "NoCat"   ,var.getString()   );

    // need to add an underscore, if no category but name contains underscore!
    protectedValues.store( var.declare("TEST", "VARIABLE"), "$no_cat"  ); cfg.load( var.declare("TEST",  "VARIABLE") );   UT_EQ( ""        ,var.getString()   );
    protectedValues.store( var.declare("TEST", "VARIABLE"), "$_no_cat" ); cfg.load( var.declare("TEST",  "VARIABLE") );   UT_EQ( "No_cat"  ,var.getString()   );


    // nested variables
    protectedValues.store( var.declare("Rep", "Var1"     ), "$Rep_Var2");
    protectedValues.store( var.declare("Rep", "Var2"     ), "nested"   );
    protectedValues.store( var.declare("TEST", "VARIABLE"), "$rep_var2"); cfg.load( var.declare("TEST",  "VARIABLE") );   UT_EQ( "nested"                          ,var.getString()   );
    protectedValues.store( var.declare("TEST", "VARIABLE"), "$rep_var1"); cfg.load( var.declare("TEST",  "VARIABLE") );   UT_EQ( "nested"                          ,var.getString()   );

    // illegal recursion
    UT_PRINT( "One warning should follow" );
    protectedValues.store( var.declare("Rep", "Var1"     ), "$Rep_Var2" );
    protectedValues.store( var.declare("Rep", "Var2"     ), "$Rep_Var1" );
    protectedValues.store( var.declare("TEST", "VARIABLE"), "$rep_var1" ); cfg.load( var.declare("TEST",  "VARIABLE") );

    // custom variables
    protectedValues.store( var.declare("Rep", "CUST"     ), "cf"           );

    protectedValues.store( var.declare("TEST", "VARIABLE"), ">>$REP_CUST<<"); cfg.load( var.declare("TEST",  "VARIABLE") );   UT_EQ( ">>cf<<"                          ,var.getString()   );

    cfg.substitutionVariableStart._()._( "${" );
    cfg.substitutionVariableEnd  ._()._( "}"  );
    var.declare( "TEST", "VARIABLE" );
    protectedValues.store( var, ">>${REP_CUST}<<"              ); cfg.load( var );   UT_EQ( ">>cf<<"                          ,var.getString()   );

    cfg.substitutionVariableStart._()._( "€€€-");
    cfg.substitutionVariableEnd  ._()._( "--"  );
    protectedValues.store( var, ">>€€€-REP_CUST--<<"           ); cfg.load( var );   UT_EQ( ">>cf<<"                          ,var.getString()   );
    protectedValues.store( var, ">>€€€-REP_CUST--"             ); cfg.load( var );   UT_EQ( ">>cf"                            ,var.getString()   );
    protectedValues.store( var, "€€€-REP_CUST--"               ); cfg.load( var );   UT_EQ( "cf"                              ,var.getString()   );
    protectedValues.store( var, "€€€-REP_CUST--€€€-REP_CUST--" ); cfg.load( var );   UT_EQ( "cfcf"                            ,var.getString()   );
    protectedValues.store( var, "€€-REP_CUST--"                ); cfg.load( var );   UT_EQ( "€€-REP_CUST--"                   ,var.getString()   );

    UT_PRINT( "One warning should follow" );
    protectedValues.store( var, "€€€-REP_CUST-"                ); cfg.load( var );   UT_EQ( "€€€-REP_CUST-"                   ,var.getString()   );

    cfg.substitutionVariableStart._()._( "$" );
    cfg.substitutionVariableEnd._();

    // multi line replacements
    defaultValues.store( var.declare("ML", "REPL1", ';' ), "repl1-v1;repl1-v2"   );
    defaultValues.store( var.declare("ML", "REPL2", ';' ), "repl2-v1;repl2-v2"   );
    defaultValues.store( var.declare("ML", "VAR"  , ';' ), "$ML_REPL1;$ML_REPL2" );
    var.declare("ML", "VAR", ';' );
    cfg.load( var );
    UT_EQ( 4, var.size() );
    UT_EQ( "repl1-v1", var.getString(0) );
    UT_EQ( "repl1-v2", var.getString(1) );
    UT_EQ( "repl2-v1", var.getString(2) );
    UT_EQ( "repl2-v2", var.getString(3) );
}

}
