// #################################################################################################
//  cs.aworx.unittests - AWorx Util
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
using System;
using System.IO;
using cs.aworx.lox;
using cs.aworx.lox.loggers;
using cs.aworx.lib.config;
using cs.aworx.lib.strings;
using ut_cs_aworx;
using cs.aworx.lib.enums;

#if ALIB_MONO_DEVELOP
    using NUnit.Framework;
#endif
#if ALIB_VSTUDIO
    using Microsoft.VisualStudio.TestTools.UnitTesting;
#endif

using System.Text;
using cs.aworx.lib;


namespace ut_cs_aworx_lib
{
    #if ALIB_MONO_DEVELOP
        [TestFixture ()]
    #endif
    #if ALIB_VSTUDIO
        [TestClass]
    #endif
    public class CS_Configuration   : AWorxUnitTesting
    {



/** ********************************************************************************************
 * CommandLineArgs
 **********************************************************************************************/
#if ALIB_MONO_DEVELOP
    [Test ()]
#endif
#if ALIB_VSTUDIO
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
    UT_EQ( Configuration.PrioCmdLine,    cfg.Load   ( var.Define( "",      "SingleHyphen" )) );   UT_EQ( "12",            var.GetString()       );
                                         cfg.Load   ( var.Define( "",      "DoubleHyphen" ));     UT_EQ( true,            var.IsTrue()    );
    UT_EQ( Configuration.PrioCmdLine,    var.Priority);

    UT_EQ( Configuration.PrioCmdLine,    cfg.Load   ( var.Define( "",      "Empty"        )) );   UT_EQ( "",              var.GetString()       );
    UT_EQ( Configuration.PrioCmdLine,    cfg.Load   ( var.Define( "",      "Whitespaces"  )) );   UT_EQ( "Hello Test",    var.GetString()       );
    UT_EQ( Configuration.PrioCmdLine,    cfg.Load   ( var.Define( "",      "HOME"         )) );   UT_EQ( "overwritten",   var.GetString()       );
    UT_EQ( Configuration.PrioCmdLine,    cfg.Load   ( var.Define( "",      "integer"      )) );   UT_EQ( 42,              var.GetInteger()    );
    UT_EQ( 0,                            cfg.Load   ( var.Define( "",      "notexistent"  )) );   UT_EQ( 0,               var.GetInteger()    );
    UT_EQ( Configuration.PrioCmdLine,    cfg.Load   ( var.Define( "",      "integer"      )) );   UT_EQ( 42,              var.GetInteger()    );
    UT_EQ( Configuration.PrioCmdLine,    cfg.Load   ( var.Define( "",      "double"       )) );   UT_EQ( 3.14,            var.GetFloat() );
    UT_EQ( 0,                            cfg.Load   ( var.Define( "",      "notexistent"  )) );   UT_EQ( 0.0,             var.GetFloat() );
    UT_EQ( Configuration.PrioCmdLine,    cfg.Load   ( var.Define( "",      "double"       )) );   UT_EQ( 3.14,            var.GetFloat() );
    UT_EQ( Configuration.PrioCmdLine,    cfg.Load   ( var.Define( "ALIB",  "test"         )) );   UT_EQ( "passed",        var.GetString()       );
}


/** ********************************************************************************************
 * IniFileTest
 **********************************************************************************************/

#if ALIB_MONO_DEVELOP
    [Test ()]
#endif
#if ALIB_VSTUDIO
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

    String fileName= Environment.CurrentDirectory + "/unittest_testiniFile.cfg";

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
    iniFile.Load( var.Define( "",    "CUBA") );         UT_EQ( "a country",      var.GetString() );
    iniFile.Load( var.Define( "",    "cUbA") );         UT_EQ( "a country",      var.GetString() );
    iniFile.Load( var.Define( "",    "SIZE") );         UT_EQ( "25",             var.GetString() );
    iniFile.Load( var.Define( "",    "concat", ',') );  UT_EQ( 11 , var.Size());
                                                        UT_EQ( "start =5"       , var.GetString(0) );
                                                        UT_EQ( "end   =32"      , var.GetString(1) );
                                                        UT_EQ( "#no comment"    , var.GetString(2) );
                                                        UT_EQ( ";nocomment"     , var.GetString(3) );

    iniFile.Load( var.Define( "ESC", "Blanks"  ) );   UT_EQ( " x "      , var.GetString() );
    iniFile.Load( var.Define( "ESC", "Blanks2" ) );   UT_EQ( " x  y "   , var.GetString() );
    iniFile.Load( var.Define( "ESC", "Tabs"    ) );   UT_EQ( "\tx\t"    , var.GetString() );
    iniFile.Load( var.Define( "ESC", "nrslash" ) );   UT_EQ( "\n\r//\\" , var.GetString() );

    iniFile.Load( var.Define( "Great Section",  "SectionVar"       ) );   UT_EQ( "5"  , var.GetString() );
    iniFile.Load( var.Define( "2nd Section",    "SectionVar"       ) );   UT_EQ( "6"  , var.GetString() );
    iniFile.Load( var.Define( "Great Section",  "SECTION_CONTINUED") );   UT_EQ( "yEs", var.GetString() );
    iniFile.Load( var.Define( "Great Section",  "Tricky"           ) );   UT_EQ( "backslash\\", var.GetString() );

    // add it to ALIB config
    ALox.Init();
    ALIB.Config.InsertPlugin( iniFile, Configuration.PrioIniFile );
    ALIB.Config.Load( var.Define( "",               "CUBA"              ) );   UT_EQ( "a country"  , var.GetString() );
    ALIB.Config.Load( var.Define( "",               "cUbA"              ) );   UT_EQ( "a country"  , var.GetString() );
    ALIB.Config.Load( var.Define( "",               "SIZE"              ) );   UT_EQ( "25"         , var.GetString() );
    ALIB.Config.Load( var.Define( "",               "concat"            ) );   UT_EQ( 11 , var.Size());
                                                                               UT_EQ( "start =5"   , var.GetString(0) );
                                                                               UT_EQ( "end   =32"  , var.GetString(1) );
    ALIB.Config.Load( var.Define( "Great Section",  "SectionVar"        ) );   UT_EQ( "5"          , var.GetString() );
    ALIB.Config.Load( var.Define( "2nd Section",    "SectionVar"        ) );   UT_EQ( "6"          , var.GetString() );
    ALIB.Config.Load( var.Define( "Great Section",  "SECTION_CONTINUED" ) );   UT_EQ( "yEs"        , var.GetString() );
    ALIB.Config.Load( var.Define( "Great Section",  "Tricky"            ) );   UT_EQ( "backslash\\", var.GetString() );
    ALIB.Config.Load( var.Define( "Great Section",  "SECTION_CONTINUED" ) );   UT_TRUE( var.IsTrue() );


    // check if environment variable "home" overwrites INI file
    AString vIniFile= new AString();   iniFile.Load( var.Define( "", "hOme" ) );               UT_EQ( "overwritten_by_environment", var.GetString() );
    int prio= ALIB.Config.Load( var.Define("", "hOme" ));
    if (prio != Configuration.PrioEnvironment ) // Windows platform?
    {
        prio= ALIB.Config.Load( var.Define("", "hOmePAth") );
        iniFile.Load( var.Define( "", "hOmePAth") );    UT_EQ( "overwritten_by_environment", var.GetString() );
    }
    UT_EQ( Configuration.PrioEnvironment, prio );

    UT_TRUE( var.GetString().Length() > 0 );
    UT_TRUE( !vIniFile.Equals( var.GetString()) );

    // change a value and write a new one
    var.Define( "New Section",  "newvar");
    var.Priority= Configuration.PrioIniFile;
    UT_EQ( Configuration.PrioIniFile, ALIB.Config.Store( var, "new" ) );
    ALIB.Config.Load  ( var.Define("New Section",  "newvar") );  UT_EQ( "new",   var.GetString() );

    var.Define( "",             "newvar");
    var.Priority= Configuration.PrioIniFile;
    UT_EQ( Configuration.PrioIniFile, ALIB.Config.Store( var, "aworx") );
    ALIB.Config.Load  ( var.Define("",             "newvar") );  UT_EQ( "aworx", var.GetString() );


    var.Define( "",   "newvarList", ',');
    var.AddString("val1=5");
    var.AddString("val2=10");
    var.AddString("val3=hello");
    var.Priority= Configuration.PrioIniFile;
    UT_EQ( Configuration.PrioIniFile, ALIB.Config.Store(var) );
    ALIB.Config.Load (  var.Define( "",  "newvarList")   );

    var.Define( "",   "commented", ',', "2lines" );
    var.Priority= Configuration.PrioIniFile;
    UT_EQ( Configuration.PrioIniFile, ALIB.Config.Store(  var,  "this is c-line 1 \nand this line 2" ) );

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

                iniFile .Load( var    .Define( section.Name, entry.Name, delim) );
                readBack.Load( varBack.Define( section.Name, entry.Name, delim) );

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

    readBack.Load ( var.Define( "New Section",  "newvar" ) );   UT_EQ( "new"  , var.GetString() );
    readBack.Load ( var.Define( "",             "newvar" ) );   UT_EQ( "aworx", var.GetString() );


    ALIB.Config.RemovePlugin( iniFile );


    ALIB.Config.InsertPlugin( readBack, Configuration.PrioIniFile );
    ALIB.Config.Load ( var.Define( "New Section",  "newvar") );   UT_EQ( "new"   , var.GetString() );
    ALIB.Config.Load ( var.Define( "",             "newvar") );   UT_EQ( "aworx" , var.GetString() );

    ALIB.Config.RemovePlugin( readBack );
}

/** ********************************************************************************************
 * ConfigDefaultAndProtected
 **********************************************************************************************/
#if ALIB_MONO_DEVELOP
    [Test ()]
#endif
#if ALIB_VSTUDIO
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

    Variable var= new Variable();

    // command line
    UT_EQ( Configuration.PrioCmdLine,    cfg.Load  ( var.Define( "TEST",      "VARIABLE" ) ) );   UT_EQ( "fromCommandLine"    ,var.GetString() );

    // set default, does not overwrite
    cfg.DefaultValues.Store( var.Define("TEST", "VARIABLE"), "not overwriting" );
    UT_EQ( Configuration.PrioCmdLine,    cfg.Load  ( var.Define( "TEST",      "VARIABLE" ) ) );   UT_EQ( "fromCommandLine"    ,var.GetString() );

    // set protected, overwrites command line
    cfg.ProtectedValues.Store( var.Define("TEST", "VARIABLE"), "does overwrite" );
    UT_EQ( Configuration.PrioProtected,  cfg.Load  ( var.Define( "TEST",      "VARIABLE" ) ) );   UT_EQ( "does overwrite"     ,var.GetString() );

    // set default, something else
    cfg.DefaultValues.Store( var.Define("TEST", "VAR2"), "this is var 2" );
    UT_EQ( Configuration.PrioDefault,    cfg.Load  ( var.Define( "TEST",      "VAR2"     ) ) );   UT_EQ( "this is var 2"      ,var.GetString() );

    // set and remove an entry using plugin interface
    var.Define( "TEST", "Remove" );     UT_EQ( 0, var.Size() );     UT_EQ( -1                           ,var.Priority );
    cfg.DefaultValues.Load( var );      UT_EQ( 0, var.Size() );     UT_EQ( -1                           ,var.Priority );
    var.AddString("To be deleted");     UT_EQ( 1, var.Size() );     UT_EQ( -1                           ,var.Priority );
    cfg.DefaultValues.Store( var );     UT_EQ( 1, var.Size() );     UT_EQ( -1                           ,var.Priority );
    var.Define( "TEST", "Remove" );     UT_EQ( 0, var.Size() );     UT_EQ( -1                           ,var.Priority );
    cfg.DefaultValues.Load( var );      UT_EQ( 1, var.Size() );     UT_EQ( -1                           ,var.Priority );
    var.ClearValues();                  UT_EQ( 0, var.Size() );     UT_EQ( -1                           ,var.Priority );
    cfg.DefaultValues.Store( var );     UT_EQ( 0, var.Size() );     UT_EQ( -1                           ,var.Priority );
    var.Define( "TEST", "Remove" );     UT_EQ( 0, var.Size() );     UT_EQ( -1                           ,var.Priority );
    cfg.DefaultValues.Load( var );      UT_EQ( 0, var.Size() );     UT_EQ( -1                           ,var.Priority );

    // set and remove an entry using configuration interface
    cfg              .Load ( var );     UT_EQ( 0, var.Size() );     UT_EQ(  0                           ,var.Priority );
    cfg              .Store( var );     UT_EQ( 0, var.Size() );     UT_EQ(  0                           ,var.Priority );
    var.AddString("To be deleted");     UT_EQ( 1, var.Size() );     UT_EQ(  0                           ,var.Priority );
    cfg              .Store( var );     UT_EQ( 1, var.Size() );     UT_EQ( Configuration.PrioDefault    ,var.Priority );
    var.Define( "TEST", "Remove" );     UT_EQ( 0, var.Size() );     UT_EQ( -1                           ,var.Priority );
    cfg              .Load ( var );     UT_EQ( 1, var.Size() );     UT_EQ( Configuration.PrioDefault    ,var.Priority );
    var.Define( "TEST", "Remove" );     UT_EQ( 0, var.Size() );     UT_EQ( -1                           ,var.Priority );
    cfg              .Store( var );     UT_EQ( 0, var.Size() );     UT_EQ( Configuration.PrioDefault    ,var.Priority );
    cfg              .Load ( var );     UT_EQ( 0, var.Size() );     UT_EQ( 0                            ,var.Priority );
    var.Define( "TEST", "Remove" );     UT_EQ( 0, var.Size() );     UT_EQ( -1                           ,var.Priority );
    cfg              .Load ( var );     UT_EQ( 0, var.Size() );     UT_EQ( 0                            ,var.Priority );

    // protected
    var.Define( "TEST", "Protected");   UT_EQ( 0, var.Size() );                 UT_EQ( -1                          ,var.Priority );
    var.DefaultValue._( "Default"  );
    var.StoreDefault( "def par");       UT_EQ( "def par",   var.GetString() );  UT_EQ( Configuration.PrioDefault   ,var.Priority );

    var.ClearValues();
    var.AddString( "def var" );
    var.StoreDefault();                 UT_EQ( "def var",   var.GetString() );  UT_EQ( Configuration.PrioDefault   ,var.Priority );

    var.ClearValues();
    var.StoreDefault();                 UT_EQ( "Default",   var.GetString() );  UT_EQ( Configuration.PrioDefault   ,var.Priority );

    var.ClearValues();
    var.AddString( "def var" );
    var.Protect();                      UT_EQ( "def var",   var.GetString() );  UT_EQ( Configuration.PrioProtected ,var.Priority );
    var.Protect("prot par");            UT_EQ( "prot par",  var.GetString() );  UT_EQ( Configuration.PrioProtected ,var.Priority );
    var.ClearValues();
    var.Protect();                      UT_EQ( "Default",   var.GetString() );  UT_EQ( Configuration.PrioProtected ,var.Priority );
    var.DefaultValue.SetNull();
    var.ClearValues();
    var.Protect();                      UT_EQ( 0, var.Size()                );  UT_EQ( Configuration.PrioProtected ,var.Priority );
    var.Load();                         UT_EQ( "Default",   var.GetString() );  UT_EQ( Configuration.PrioDefault   ,var.Priority );

}

/** ********************************************************************************************
 * ConfigReplacementVariables
 **********************************************************************************************/
#if ALIB_MONO_DEVELOP
    [Test ()]
#endif
#if ALIB_VSTUDIO
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

    Variable var= new Variable();

    // replacements from command line plugin
    var.Define( "TEST", "VARIABLE" );
    cfg.ProtectedValues.Store( var, "no replacment"                ); cfg.Load( var );   UT_EQ( "no replacment"                   ,var.GetString() );
    cfg.ProtectedValues.Store( var, "$UKN"                         ); cfg.Load( var );   UT_EQ( ""                                ,var.GetString() );
    cfg.ProtectedValues.Store( var, "-$UKN * $UKN2-"               ); cfg.Load( var );   UT_EQ( "- * -"                           ,var.GetString() );
    cfg.ProtectedValues.Store( var, "$NOCATCMDLINE"                ); cfg.Load( var );   UT_EQ( "NoCatCommandLine"                ,var.GetString() );
    cfg.ProtectedValues.Store( var, "$$NOCATCMDLINE$"              ); cfg.Load( var );   UT_EQ( "$NoCatCommandLine$"              ,var.GetString() );
    cfg.ProtectedValues.Store( var, "$REPL_CMDLINE"                ); cfg.Load( var );   UT_EQ( "ReplCommandLine"                 ,var.GetString() );
    cfg.ProtectedValues.Store( var, "$REPL_ CMDLINE"               ); cfg.Load( var );   UT_EQ( " CMDLINE"                        ,var.GetString() );
    cfg.ProtectedValues.Store( var, "$repL_CmdLine"                ); cfg.Load( var );   UT_EQ( "ReplCommandLine"                 ,var.GetString() );
    cfg.ProtectedValues.Store( var, "$repL_CmdLine$repL_CmdLine"   ); cfg.Load( var );   UT_EQ( "ReplCommandLineReplCommandLine"  ,var.GetString() );
    cfg.ProtectedValues.Store( var, "$repL_CmdLine $repL_CmdLine"  ); cfg.Load( var );   UT_EQ( "ReplCommandLine ReplCommandLine" ,var.GetString() );

    // replacements without category name
    cfg.ProtectedValues.Store( var.Define( ""    , "NOCAT"   ), "NoCat"    );
    cfg.ProtectedValues.Store( var.Define( ""    , "NO_CAT"  ), "No_cat"   );
    cfg.ProtectedValues.Store( var.Define( "TEST", "VARIABLE"), "$nocat"                       ); cfg.Load( var );   UT_EQ( "NoCat"   ,var.GetString() );
    cfg.ProtectedValues.Store( var.Define( "TEST", "VARIABLE"), "$_nocat"                      ); cfg.Load( var );   UT_EQ( "NoCat"   ,var.GetString() );

    // need to add an underscore, if no category but name contains underscore!
    cfg.ProtectedValues.Store( var.Define( "TEST", "VARIABLE"), "$no_cat"                      ); cfg.Load( var );   UT_EQ( ""        ,var.GetString() );
    cfg.ProtectedValues.Store( var.Define( "TEST", "VARIABLE"), "$_no_cat"                     ); cfg.Load( var );   UT_EQ( "No_cat"  ,var.GetString() );


    // nested variables
    cfg.ProtectedValues.Store( var.Define( "Rep", "Var1"     ), "$Rep_Var2"                         );
    cfg.ProtectedValues.Store( var.Define( "Rep", "Var2"     ), "nested"                            );
    cfg.ProtectedValues.Store( var.Define( "TEST", "VARIABLE"), "$rep_var2"                    ); cfg.Load( var );   UT_EQ( "nested"                          ,var.GetString() );
    cfg.ProtectedValues.Store( var.Define( "TEST", "VARIABLE"), "$rep_var1"                    ); cfg.Load( var );   UT_EQ( "nested"                          ,var.GetString() );

    // illegal recursion
    UT_PRINT( "One warning should follow" );
    cfg.ProtectedValues.Store( var.Define( "Rep", "Var1"     ), "$Rep_Var2"                         );
    cfg.ProtectedValues.Store( var.Define( "Rep", "Var2"     ), "$Rep_Var1"                         );
    cfg.ProtectedValues.Store( var.Define( "TEST", "VARIABLE"), "$rep_var1"                    ); cfg.Load( var );

    // custom variable definitions
    cfg.ProtectedValues.Store( var.Define( "Rep", "CUST"     ), "cf"                                );

    cfg.ProtectedValues.Store( var.Define( "TEST", "VARIABLE"), ">>$REP_CUST<<"                ); cfg.Load( var );   UT_EQ( ">>cf<<"                          ,var.GetString() );

    cfg.SubstitutionVariableStart._()._( "${" );
    cfg.SubstitutionVariableEnd  ._()._( "}"  );
    cfg.ProtectedValues.Store( var.Define( "TEST", "VARIABLE"), ">>${REP_CUST}<<"              ); cfg.Load( var );   UT_EQ( ">>cf<<"                          ,var.GetString() );

    cfg.SubstitutionVariableStart._()._( "€€€-");
    cfg.SubstitutionVariableEnd  ._()._( "--"  );
    cfg.ProtectedValues.Store( var.Define( "TEST", "VARIABLE"), ">>€€€-REP_CUST--<<"           ); cfg.Load( var );   UT_EQ( ">>cf<<"                          ,var.GetString() );
    cfg.ProtectedValues.Store( var.Define( "TEST", "VARIABLE"), ">>€€€-REP_CUST--"             ); cfg.Load( var );   UT_EQ( ">>cf"                            ,var.GetString() );
    cfg.ProtectedValues.Store( var.Define( "TEST", "VARIABLE"), "€€€-REP_CUST--"               ); cfg.Load( var );   UT_EQ( "cf"                              ,var.GetString() );
    cfg.ProtectedValues.Store( var.Define( "TEST", "VARIABLE"), "€€€-REP_CUST--€€€-REP_CUST--" ); cfg.Load( var );   UT_EQ( "cfcf"                            ,var.GetString() );
    cfg.ProtectedValues.Store( var.Define( "TEST", "VARIABLE"), "€€-REP_CUST--"                ); cfg.Load( var );   UT_EQ( "€€-REP_CUST--"                   ,var.GetString() );

    UT_PRINT( "One warning should follow" );
    cfg.ProtectedValues.Store( var.Define( "TEST", "VARIABLE"), "€€€-REP_CUST-"                ); cfg.Load( var );   UT_EQ( "€€€-REP_CUST-"                   ,var.GetString() );
    cfg.SubstitutionVariableStart._()._( "$" );
    cfg.SubstitutionVariableEnd._();

    // multi line replacements
    cfg.DefaultValues.Store( var.Define("ML", "REPL1", ';'), "repl1-v1;repl1-v2"   );
    cfg.DefaultValues.Store( var.Define("ML", "REPL2", ';'), "repl2-v1;repl2-v2"   );
    cfg.DefaultValues.Store( var.Define("ML", "VAR"  , ';'), "$ML_REPL1;$ML_REPL2" );
    var.Define("ML", "VAR", ';' );
    cfg.Load( var );
    UT_EQ( 4, var.Size() );
    UT_EQ( "repl1-v1", var.GetString(0) );
    UT_EQ( "repl1-v2", var.GetString(1) );
    UT_EQ( "repl2-v1", var.GetString(2) );
    UT_EQ( "repl2-v2", var.GetString(3) );
}


}}// class/namespace
