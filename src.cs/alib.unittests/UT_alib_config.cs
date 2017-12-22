// #################################################################################################
//  cs.aworx.unittests - AWorx Util
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
using System;
using System.IO;
using System.Runtime.InteropServices;
using cs.aworx.lox;
using cs.aworx.lox.loggers;
using cs.aworx.lib.config;
using cs.aworx.lib.strings;
using ut_cs_aworx;
using cs.aworx.lib.lang;

#if ALIB_NUNIT
    using NUnit.Framework;
#endif
#if ALIB_IDE_VSTUDIO
    using Microsoft.VisualStudio.TestTools.UnitTesting;
#endif

using System.Text;
using cs.aworx.lib;


namespace ut_cs_aworx_lib
{
    #if ALIB_NUNIT
        [TestFixture ()]
    #endif
    #if ALIB_IDE_VSTUDIO
        [TestClass]
    #endif
    public class CS_Configuration   : AWorxUnitTesting
    {



/** ********************************************************************************************
 * CommandLineArgs
 **********************************************************************************************/
#if ALIB_NUNIT
    [Test ()]
#endif
#if ALIB_IDE_VSTUDIO
    [TestMethod]
    #if !WINDOWS_PHONE
        [TestCategory("CS_Configuration")]
    #endif
#endif
public void CommandLineArgs()
{
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
    cfg.SetCommandLineArgs( args );
    Variable var= new Variable();
    UT_EQ( Configuration.PrioCLIArgs, cfg.Load   ( var.Declare( "",      "SingleHyphen" )) );   UT_EQ( "12",            var.GetString()    );
                                            cfg.Load   ( var.Declare( "",      "DoubleHyphen" ));     UT_EQ( true,            var.IsTrue()       );
    UT_EQ( Configuration.PrioCLIArgs,    var.Priority);

    UT_EQ( Configuration.PrioCLIArgs, cfg.Load   ( var.Declare( "",      "Empty"        )) );   UT_EQ( "",              var.GetString()    );
    UT_EQ( Configuration.PrioCLIArgs, cfg.Load   ( var.Declare( "",      "Whitespaces"  )) );   UT_EQ( "Hello Test",    var.GetString()    );
    UT_EQ( Configuration.PrioCLIArgs, cfg.Load   ( var.Declare( "",      "HOME"         )) );   UT_EQ( "overwritten",   var.GetString()    );
    UT_EQ( Configuration.PrioCLIArgs, cfg.Load   ( var.Declare( "",      "integer"      )) );   UT_EQ( 42,              var.GetInteger()   );
    UT_EQ( 0,                               cfg.Load   ( var.Declare( "",      "notexistent"  )) );   UT_EQ( 0,               var.GetInteger()   );
    UT_EQ( Configuration.PrioCLIArgs, cfg.Load   ( var.Declare( "",      "integer"      )) );   UT_EQ( 42,              var.GetInteger()   );
    UT_EQ( Configuration.PrioCLIArgs, cfg.Load   ( var.Declare( "",      "double"       )) );   UT_EQ( 3.14,            var.GetFloat()     );
    UT_EQ( 0,                               cfg.Load   ( var.Declare( "",      "notexistent"  )) );   UT_EQ( 0.0,             var.GetFloat()     );
    UT_EQ( Configuration.PrioCLIArgs, cfg.Load   ( var.Declare( "",      "double"       )) );   UT_EQ( 3.14,            var.GetFloat()     );
    UT_EQ( Configuration.PrioCLIArgs, cfg.Load   ( var.Declare( "ALIB",  "test"         )) );   UT_EQ( "passed",        var.GetString()    );

    UT_EQ( 0,                               cfg.Load   ( var.Declare( "IGNORE","Home"         )) );
    cfg.GetPluginTypeSafe<CLIArgs>().DefaultCategories.Add("IGNORE");
    UT_EQ( Configuration.PrioCLIArgs, cfg.Load   ( var.Declare( "IGNORE","Home"         )) );   UT_EQ( "overwritten",   var.GetString()       );
    UT_EQ( 0                              , cfg.Load   ( var.Declare( "IGNORE","Homexyz"      )) );
    cfg.GetPluginTypeSafe<CLIArgs>().AllowedMinimumShortCut=5;
    UT_EQ( 0                              , cfg.Load   ( var.Declare( "IGNORE","Homexyz"      )) );
    cfg.GetPluginTypeSafe<CLIArgs>().AllowedMinimumShortCut=4;
    UT_EQ( Configuration.PrioCLIArgs, cfg.Load   ( var.Declare( "IGNORE","Homexyz"      )) );   UT_EQ( "overwritten",   var.GetString()       );
}


/** ********************************************************************************************
 * IniFileTest
 **********************************************************************************************/

#if ALIB_NUNIT
    [Test ()]
#endif
#if ALIB_IDE_VSTUDIO
    [TestMethod]
    #if !WINDOWS_PHONE
        [TestCategory("CS_Configuration")]
    #endif
#endif
public void IniFileTest()
{
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
    +"HOMEPATH= overwritten_by_environment"                                        +"\n"
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

    String fileName= System.Environment.CurrentDirectory + "/unittest_testiniFile.cfg";

    // write sample config file
    {
        StreamWriter file= new StreamWriter( fileName );
        file.Write( iniFileContents );
        file.Close();
    }

    IniFile iniFile= new IniFile( fileName );
    UT_TRUE( (IniFile.Status.OK == iniFile.LastStatus) );

    // check some values
    Variable var= new Variable();
    iniFile.Load( var.Declare( "",    "CUBA") );         UT_EQ( "a country",      var.GetString() );
    iniFile.Load( var.Declare( "",    "cUbA") );         UT_EQ( "a country",      var.GetString() );
    iniFile.Load( var.Declare( "",    "SIZE") );         UT_EQ( "25",             var.GetString() );
    iniFile.Load( var.Declare( "",    "concat", ',') );  UT_EQ( 11 , var.Size());
                                                         UT_EQ( "start =5"       , var.GetString(0) );
                                                         UT_EQ( "end   =32"      , var.GetString(1) );
                                                         UT_EQ( "#no comment"    , var.GetString(2) );
                                                         UT_EQ( ";nocomment"     , var.GetString(3) );

    iniFile.Load( var.Declare( "ESC", "Blanks"  ) );     UT_EQ( " x "      , var.GetString() );
    iniFile.Load( var.Declare( "ESC", "Blanks2" ) );     UT_EQ( " x  y "   , var.GetString() );
    iniFile.Load( var.Declare( "ESC", "Tabs"    ) );     UT_EQ( "\tx\t"    , var.GetString() );
    iniFile.Load( var.Declare( "ESC", "nrslash" ) );     UT_EQ( "\n\r//\\" , var.GetString() );

    iniFile.Load( var.Declare( "Great Section",  "SectionVar"       ) );   UT_EQ( "5"  , var.GetString() );
    iniFile.Load( var.Declare( "2nd Section",    "SectionVar"       ) );   UT_EQ( "6"  , var.GetString() );
    iniFile.Load( var.Declare( "Great Section",  "SECTION_CONTINUED") );   UT_EQ( "yEs", var.GetString() );
    iniFile.Load( var.Declare( "Great Section",  "Tricky"           ) );   UT_EQ( "backslash\\", var.GetString() );

    // add it to ALIB config
    ALox.Init();
    ALIB.Config.InsertPlugin( iniFile, Configuration.PrioStandard );
    ALIB.Config.Load( var.Declare( "",               "CUBA"              ) );   UT_EQ( "a country"  , var.GetString() );
    ALIB.Config.Load( var.Declare( "",               "cUbA"              ) );   UT_EQ( "a country"  , var.GetString() );
    ALIB.Config.Load( var.Declare( "",               "SIZE"              ) );   UT_EQ( "25"         , var.GetString() );
    ALIB.Config.Load( var.Declare( "",               "concat"            ) );   UT_EQ( 11 , var.Size());
                                                                                UT_EQ( "start =5"   , var.GetString(0) );
                                                                                UT_EQ( "end   =32"  , var.GetString(1) );
    ALIB.Config.Load( var.Declare( "Great Section",  "SectionVar"        ) );   UT_EQ( "5"          , var.GetString() );
    ALIB.Config.Load( var.Declare( "2nd Section",    "SectionVar"        ) );   UT_EQ( "6"          , var.GetString() );
    ALIB.Config.Load( var.Declare( "Great Section",  "SECTION_CONTINUED" ) );   UT_EQ( "yEs"        , var.GetString() );
    ALIB.Config.Load( var.Declare( "Great Section",  "Tricky"            ) );   UT_EQ( "backslash\\", var.GetString() );
    ALIB.Config.Load( var.Declare( "Great Section",  "SECTION_CONTINUED" ) );   UT_TRUE( var.IsTrue() );


    // check if environment variable "home" overwrites INI file
    AString vIniFile= new AString();   iniFile.Load( var.Declare( "", "hOme" ) );               UT_EQ( "overwritten_by_environment", var.GetString() );
    int prio= ALIB.Config.Load( var.Declare("", "hOme" ));
    if (prio != Configuration.PrioEnvironment ) // Windows platform?
    {
        prio= ALIB.Config.Load( var.Declare("", "hOmePAth") );
        iniFile.Load( var.Declare( "", "hOmePAth") );    UT_EQ( "overwritten_by_environment", var.GetString() );
    }
    UT_EQ( Configuration.PrioEnvironment, prio );

    UT_TRUE( var.GetString().Length() > 0 );
    UT_TRUE( !vIniFile.Equals( var.GetString()) );

    // change a value and write a new one
    var.Declare( "New Section",  "newvar");
    var.Priority= Configuration.PrioStandard;
    UT_EQ( Configuration.PrioStandard, ALIB.Config.Store( var, "new" ) );
    ALIB.Config.Load  ( var.Declare("New Section",  "newvar") );  UT_EQ( "new",   var.GetString() );

    var.Declare( "",             "newvar");
    var.Priority= Configuration.PrioStandard;
    UT_EQ( Configuration.PrioStandard, ALIB.Config.Store( var, "aworx") );
    ALIB.Config.Load  ( var.Declare("",             "newvar") );  UT_EQ( "aworx", var.GetString() );


    var.Declare( "",   "newvarList", ',');
    var.Add("val1=5");
    var.Add("val2=10");
    var.Add("val3=hello");
    var.Priority= Configuration.PrioStandard;
    UT_EQ( Configuration.PrioStandard, ALIB.Config.Store(var) );
    ALIB.Config.Load (  var.Declare( "",  "newvarList")   );

    var.Declare( "",   "commented", ',', "2lines" );
    var.Priority= Configuration.PrioStandard;
    UT_EQ( Configuration.PrioStandard, ALIB.Config.Store(  var,  "this is c-line 1 \nand this line 2" ) );

    // write the file
    iniFile.FileName._(".writeback.txt");
    iniFile.WriteFile();

    // load the written file into another config
    IniFile readBack= new IniFile( iniFile.FileName.ToString() );
    Variable varBack= new Variable();

    // compare all
    UT_TRUE( (IniFile.Status.OK == readBack.LastStatus) );

    {
        AString msg= new AString();
        Substring orig= new Substring();
        Substring back= new Substring();
        foreach ( IniFile.Section section in iniFile.Sections )
        {
            foreach ( IniFile.Entry entry in section.Entries )
            {
                msg.Clear()._( "Reading variable " ).Field()._( section.Name )._( '/' )._( entry.Name );
                UT_PRINT( msg );


                char delim= '\0';
                if(     entry.Name.Equals("concat")
                    ||  entry.Name.Equals("newvarList")       )
                    delim= ',';

                iniFile .Load( var    .Declare( section.Name, entry.Name, delim) );
                readBack.Load( varBack.Declare( section.Name, entry.Name, delim) );

                UT_EQ( var.Size(), varBack.Size() );
                for ( int i= 0; i< var.Size(); i++ )
                {
                    int idx= var.GetString(i).IndexOf('=');
                    if( idx < 0 )
                    {
                        UT_EQ( var.GetString(i), varBack.GetString(i) );
                    }
                    else
                    {
                        int idxBack= varBack.GetString(i).IndexOf('=');
                        orig.Set( var    .GetString(i), 0, idx     );
                        back.Set( varBack.GetString(i), 0, idxBack );
                        UT_EQ( orig.Trim().ToString(), back.Trim().ToString() );
                        orig.Set( var    .GetString(i), idx     +1 );
                        back.Set( varBack.GetString(i), idxBack +1 );
                        UT_EQ( orig.Trim().ToString(), back.Trim().ToString() );
                    }
                }
            }
        }
    }

    readBack.Load ( var.Declare( "New Section",  "newvar" ) );   UT_EQ( "new"  , var.GetString() );
    readBack.Load ( var.Declare( "",             "newvar" ) );   UT_EQ( "aworx", var.GetString() );


    ALIB.Config.RemovePlugin( iniFile );


    ALIB.Config.InsertPlugin( readBack, Configuration.PrioStandard );
    ALIB.Config.Load ( var.Declare( "New Section",  "newvar") );   UT_EQ( "new"   , var.GetString() );
    ALIB.Config.Load ( var.Declare( "",             "newvar") );   UT_EQ( "aworx" , var.GetString() );

    ALIB.Config.RemovePlugin( readBack );
}

/** ********************************************************************************************
 * ConfigDefaultAndProtected
 **********************************************************************************************/
#if ALIB_NUNIT
    [Test ()]
#endif
#if ALIB_IDE_VSTUDIO
    [TestMethod]
    #if !WINDOWS_PHONE
        [TestCategory("CS_Configuration")]
    #endif
#endif
public void ConfigDefaultAndProtected()
{
    UT_INIT();

    String[] args=
    {
        "COMMANDLINE",
        "--TEST_VARIABLE=fromCommandLine",
    };

    Configuration cfg= new Configuration();
    cfg.SetCommandLineArgs( args );
    InMemoryPlugin defaultValues  = cfg.GetPluginTypeSafe<InMemoryPlugin>( Configuration.PrioDefaultValues   );
    InMemoryPlugin protectedValues= cfg.GetPluginTypeSafe<InMemoryPlugin>( Configuration.PrioProtectedValues );

    Variable var= new Variable();

    // command line
    UT_EQ( Configuration.PrioCLIArgs,    cfg.Load  ( var.Declare( "TEST",      "VARIABLE" ) ) );   UT_EQ( "fromCommandLine"    ,var.GetString() );

    // set default, does not overwrite
    defaultValues.Store( var.Declare("TEST", "VARIABLE"), "not overwriting" );
    UT_EQ( Configuration.PrioCLIArgs,    cfg.Load  ( var.Declare( "TEST",      "VARIABLE" ) ) );   UT_EQ( "fromCommandLine"    ,var.GetString() );

    // set protected, overwrites command line
    protectedValues.Store( var.Declare("TEST", "VARIABLE"), "does overwrite" );
    UT_EQ( Configuration.PrioProtectedValues,        cfg.Load  ( var.Declare( "TEST",      "VARIABLE" ) ) );   UT_EQ( "does overwrite"     ,var.GetString() );

    // set default, something else
    defaultValues.Store( var.Declare("TEST", "VAR2"), "this is var 2" );
    UT_EQ( Configuration.PrioDefaultValues,          cfg.Load  ( var.Declare( "TEST",      "VAR2"     ) ) );   UT_EQ( "this is var 2"      ,var.GetString() );

    // set and remove an entry using plugin interface
    var.Declare( "TEST", "Remove" );    UT_EQ( 0, var.Size() );     UT_EQ( 0                                  ,var.Priority );
    defaultValues.Load( var );          UT_EQ( 0, var.Size() );     UT_EQ( 0                                  ,var.Priority );
    var.Add("To be deleted");           UT_EQ( 1, var.Size() );     UT_EQ( 0                                  ,var.Priority );
    defaultValues.Store( var );         UT_EQ( 1, var.Size() );     UT_EQ( 0                                  ,var.Priority );
    var.Declare( "TEST", "Remove" );    UT_EQ( 0, var.Size() );     UT_EQ( 0                                  ,var.Priority );
    defaultValues.Load( var );          UT_EQ( 1, var.Size() );     UT_EQ( 0                                  ,var.Priority );
    var.ClearValues();                  UT_EQ( 0, var.Size() );     UT_EQ( 0                                  ,var.Priority );
    defaultValues.Store( var );         UT_EQ( 0, var.Size() );     UT_EQ( 0                                  ,var.Priority );
    var.Declare( "TEST", "Remove" );    UT_EQ( 0, var.Size() );     UT_EQ( 0                                  ,var.Priority );
    defaultValues.Load( var );          UT_EQ( 0, var.Size() );     UT_EQ( 0                                  ,var.Priority );

    // set and remove an entry using configuration interface
    cfg              .Load ( var );     UT_EQ( 0, var.Size() );     UT_EQ( 0                                  ,var.Priority );
    cfg              .Store( var );     UT_EQ( 0, var.Size() );     UT_EQ( 0                                  ,var.Priority );
    var.Add("To be deleted");           UT_EQ( 1, var.Size() );     UT_EQ( 0                                  ,var.Priority );
    cfg              .Store( var );     UT_EQ( 1, var.Size() );     UT_EQ( Configuration.PrioDefaultValues    ,var.Priority );
    var.Declare( "TEST", "Remove" );    UT_EQ( 0, var.Size() );     UT_EQ( 0                                  ,var.Priority );
    cfg              .Load ( var );     UT_EQ( 1, var.Size() );     UT_EQ( Configuration.PrioDefaultValues    ,var.Priority );
    var.Declare( "TEST", "Remove" );    UT_EQ( 0, var.Size() );     UT_EQ( 0                                  ,var.Priority );
    cfg              .Store( var );     UT_EQ( 0, var.Size() );     UT_EQ( Configuration.PrioDefaultValues    ,var.Priority );
    cfg              .Load ( var );     UT_EQ( 0, var.Size() );     UT_EQ( 0                                  ,var.Priority );
    var.Declare( "TEST", "Remove" );    UT_EQ( 0, var.Size() );     UT_EQ( 0                                  ,var.Priority );
    cfg              .Load ( var );     UT_EQ( 0, var.Size() );     UT_EQ( 0                                  ,var.Priority );

    // protected
    var.Declare( "TEST", "Protected");           UT_EQ( 0, var.Size() );                 UT_EQ( 0                                 ,var.Priority );
    var.DefaultValue._( "Default"  );
    ALIB.Config.StoreDefault( var, "def par");   UT_EQ( "def par",   var.GetString() );  UT_EQ( Configuration.PrioDefaultValues   ,var.Priority );

    var.ClearValues();
    var.Add( "def var" );
    ALIB.Config.StoreDefault( var);              UT_EQ( "def var",   var.GetString() );  UT_EQ( Configuration.PrioDefaultValues   ,var.Priority );

    var.ClearValues();
    ALIB.Config.StoreDefault( var);              UT_EQ( "Default",   var.GetString() );  UT_EQ( Configuration.PrioDefaultValues   ,var.Priority );

    var.ClearValues();
    var.Add( "def var" );
    ALIB.Config.Protect(var);                    UT_EQ( "def var",   var.GetString() );  UT_EQ( Configuration.PrioProtectedValues ,var.Priority );
    ALIB.Config.Protect(var, "prot par");        UT_EQ( "prot par",  var.GetString() );  UT_EQ( Configuration.PrioProtectedValues ,var.Priority );
    var.ClearValues();
    ALIB.Config.Protect(var);                    UT_EQ( "Default",   var.GetString() );  UT_EQ( Configuration.PrioProtectedValues ,var.Priority );
    var.DefaultValue.SetNull();
    var.ClearValues();
    ALIB.Config.Protect(var);                    UT_EQ( 0, var.Size()                );  UT_EQ( Configuration.PrioProtectedValues ,var.Priority );
    ALIB.Config.Load(var);                       UT_EQ( "Default",   var.GetString() );  UT_EQ( Configuration.PrioDefaultValues   ,var.Priority );

}

/** ********************************************************************************************
 * ConfigReplacementVariables
 **********************************************************************************************/
#if ALIB_NUNIT
    [Test ()]
#endif
#if ALIB_IDE_VSTUDIO
    [TestMethod]
    #if !WINDOWS_PHONE
        [TestCategory("CS_Configuration")]
    #endif
#endif
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
    cfg.SetCommandLineArgs( args );
    InMemoryPlugin defaultValues  = cfg.GetPluginTypeSafe<InMemoryPlugin>( Configuration.PrioDefaultValues   );
    InMemoryPlugin protectedValues= cfg.GetPluginTypeSafe<InMemoryPlugin>( Configuration.PrioProtectedValues );

    Variable var= new Variable();

    // replacements from command line plugin
    var.Declare( "TEST", "VARIABLE" );
    protectedValues.Store( var, "no replacment"                ); cfg.Load( var );   UT_EQ( "no replacment"                   ,var.GetString() );
    protectedValues.Store( var, "$UKN"                         ); cfg.Load( var );   UT_EQ( ""                                ,var.GetString() );
    protectedValues.Store( var, "-$UKN * $UKN2-"               ); cfg.Load( var );   UT_EQ( "- * -"                           ,var.GetString() );
    protectedValues.Store( var, "$NOCATCMDLINE"                ); cfg.Load( var );   UT_EQ( "NoCatCommandLine"                ,var.GetString() );
    protectedValues.Store( var, "$$NOCATCMDLINE$"              ); cfg.Load( var );   UT_EQ( "$NoCatCommandLine$"              ,var.GetString() );
    protectedValues.Store( var, "$REPL_CMDLINE"                ); cfg.Load( var );   UT_EQ( "ReplCommandLine"                 ,var.GetString() );
    protectedValues.Store( var, "$REPL_ CMDLINE"               ); cfg.Load( var );   UT_EQ( " CMDLINE"                        ,var.GetString() );
    protectedValues.Store( var, "$repL_CmdLine"                ); cfg.Load( var );   UT_EQ( "ReplCommandLine"                 ,var.GetString() );
    protectedValues.Store( var, "$repL_CmdLine$repL_CmdLine"   ); cfg.Load( var );   UT_EQ( "ReplCommandLineReplCommandLine"  ,var.GetString() );
    protectedValues.Store( var, "$repL_CmdLine $repL_CmdLine"  ); cfg.Load( var );   UT_EQ( "ReplCommandLine ReplCommandLine" ,var.GetString() );

    // replacements without category name
    protectedValues.Store( var.Declare( ""    , "NOCAT"   ), "NoCat"    );
    protectedValues.Store( var.Declare( ""    , "NO_CAT"  ), "No_cat"   );
    protectedValues.Store( var.Declare( "TEST", "VARIABLE"), "$nocat"                       ); cfg.Load( var );   UT_EQ( "NoCat"   ,var.GetString() );
    protectedValues.Store( var.Declare( "TEST", "VARIABLE"), "$_nocat"                      ); cfg.Load( var );   UT_EQ( "NoCat"   ,var.GetString() );

    // need to add an underscore, if no category but name contains underscore!
    protectedValues.Store( var.Declare( "TEST", "VARIABLE"), "$no_cat"                      ); cfg.Load( var );   UT_EQ( ""        ,var.GetString() );
    protectedValues.Store( var.Declare( "TEST", "VARIABLE"), "$_no_cat"                     ); cfg.Load( var );   UT_EQ( "No_cat"  ,var.GetString() );


    // nested variables
    protectedValues.Store( var.Declare( "Rep", "Var1"     ), "$Rep_Var2"                         );
    protectedValues.Store( var.Declare( "Rep", "Var2"     ), "nested"                            );
    protectedValues.Store( var.Declare( "TEST", "VARIABLE"), "$rep_var2"                    ); cfg.Load( var );   UT_EQ( "nested"                          ,var.GetString() );
    protectedValues.Store( var.Declare( "TEST", "VARIABLE"), "$rep_var1"                    ); cfg.Load( var );   UT_EQ( "nested"                          ,var.GetString() );

    // illegal recursion
    UT_PRINT( "One warning should follow" );
    protectedValues.Store( var.Declare( "Rep", "Var1"     ), "$Rep_Var2"                         );
    protectedValues.Store( var.Declare( "Rep", "Var2"     ), "$Rep_Var1"                         );
    protectedValues.Store( var.Declare( "TEST", "VARIABLE"), "$rep_var1"                    ); cfg.Load( var );

    // custom variables
    protectedValues.Store( var.Declare( "Rep", "CUST"     ), "cf"                                );

    protectedValues.Store( var.Declare( "TEST", "VARIABLE"), ">>$REP_CUST<<"                ); cfg.Load( var );   UT_EQ( ">>cf<<"                          ,var.GetString() );

    cfg.SubstitutionVariableStart._()._( "${" );
    cfg.SubstitutionVariableEnd  ._()._( "}"  );
    protectedValues.Store( var.Declare( "TEST", "VARIABLE"), ">>${REP_CUST}<<"              ); cfg.Load( var );   UT_EQ( ">>cf<<"                          ,var.GetString() );

    cfg.SubstitutionVariableStart._()._( "€€€-");
    cfg.SubstitutionVariableEnd  ._()._( "--"  );
    protectedValues.Store( var.Declare( "TEST", "VARIABLE"), ">>€€€-REP_CUST--<<"           ); cfg.Load( var );   UT_EQ( ">>cf<<"                          ,var.GetString() );
    protectedValues.Store( var.Declare( "TEST", "VARIABLE"), ">>€€€-REP_CUST--"             ); cfg.Load( var );   UT_EQ( ">>cf"                            ,var.GetString() );
    protectedValues.Store( var.Declare( "TEST", "VARIABLE"), "€€€-REP_CUST--"               ); cfg.Load( var );   UT_EQ( "cf"                              ,var.GetString() );
    protectedValues.Store( var.Declare( "TEST", "VARIABLE"), "€€€-REP_CUST--€€€-REP_CUST--" ); cfg.Load( var );   UT_EQ( "cfcf"                            ,var.GetString() );
    protectedValues.Store( var.Declare( "TEST", "VARIABLE"), "€€-REP_CUST--"                ); cfg.Load( var );   UT_EQ( "€€-REP_CUST--"                   ,var.GetString() );

    UT_PRINT( "One warning should follow" );
    protectedValues.Store( var.Declare( "TEST", "VARIABLE"), "€€€-REP_CUST-"                ); cfg.Load( var );   UT_EQ( "€€€-REP_CUST-"                   ,var.GetString() );
    cfg.SubstitutionVariableStart._()._( "$" );
    cfg.SubstitutionVariableEnd._();

    // multi line replacements
    defaultValues.Store( var.Declare("ML", "REPL1", ';'), "repl1-v1;repl1-v2"   );
    defaultValues.Store( var.Declare("ML", "REPL2", ';'), "repl2-v1;repl2-v2"   );
    defaultValues.Store( var.Declare("ML", "VAR"  , ';'), "$ML_REPL1;$ML_REPL2" );
    var.Declare("ML", "VAR", ';' );
    cfg.Load( var );
    UT_EQ( 4, var.Size() );
    UT_EQ( "repl1-v1", var.GetString(0) );
    UT_EQ( "repl1-v2", var.GetString(1) );
    UT_EQ( "repl2-v1", var.GetString(2) );
    UT_EQ( "repl2-v2", var.GetString(3) );
}


}}// class/namespace
