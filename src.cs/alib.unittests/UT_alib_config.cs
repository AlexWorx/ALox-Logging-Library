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
    public class CS_Configuration   : AUnitTest
    {



//---------------------------------------------------------------------------------------------------------
//--- Read and write a configuration file
//---------------------------------------------------------------------------------------------------------
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

            Configuration cfg= new Configuration( true, args );
            AString  v=     new AString();
            AString  temp=  new AString();
            int      prio;
            int      iv=    -1;
            double   dv=    -1.0;
            UT_EQ( Configuration.PrioCmdLine,    cfg.Get   ( null,  "SingleHyphen",  v            ) );   UT_EQ( "12",            v );
            UT_EQ( true,  cfg.IsTrue( null,  "DoubleHyphen",  out prio,temp) );   UT_EQ( Configuration.PrioCmdLine,              prio );

            UT_EQ(                             0,    cfg.Get   ( null,  "Empty",         v            ) );   UT_EQ( "",              v );
            UT_EQ( Configuration.PrioCmdLine,    cfg.Get   ( null,  "Whitespaces",   v            ) );   UT_EQ( "Hello Test",    v );
            UT_EQ( Configuration.PrioCmdLine,    cfg.Get   ( null,  "HOME",          v            ) );   UT_EQ( "overwritten",   v );
            UT_EQ( Configuration.PrioCmdLine,    cfg.Get   ( null,  "integer",       out iv       ) );   UT_EQ( 42,              iv );
            UT_EQ(                             0,    cfg.Get   ( null,  "notexistant",   out iv       ) );   UT_EQ( 0,               iv );
            UT_EQ( Configuration.PrioCmdLine,    cfg.Get   ( null,  "integer",       out iv, temp ) );   UT_EQ( 42,              iv );
            UT_EQ( Configuration.PrioCmdLine,    cfg.Get   ( null,  "double",        out dv       ) );   UT_EQ( 3.14,            dv, 0.0 );
            UT_EQ(                             0,    cfg.Get   ( null,  "notexistant",   out dv       ) );   UT_EQ( 0.0,             dv, 0.0 );
            UT_EQ( Configuration.PrioCmdLine,    cfg.Get   ( null,  "double",        out dv, temp ) );   UT_EQ( 3.14,            dv, 0.0 );
            UT_EQ( Configuration.PrioCmdLine,    cfg.Get   ( "ALIB", "test",         v            ) );   UT_EQ( "passed",        v );

        }
//---------------------------------------------------------------------------------------------------------
//--- Read and write a configuration file
//---------------------------------------------------------------------------------------------------------
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
            iniFile.ReadFile();
            UT_TRUE( (IniFile.Status.OK == iniFile.LastStatus) );

            // check some values
            AString sv= new AString();
            iniFile.Get( "",    "CUBA", sv );   UT_EQ( "a country",      sv );
            iniFile.Get( "",    "cUbA", sv );   UT_EQ( "a country",      sv );
            iniFile.Get( "",    "SIZE", sv );   UT_EQ( "25",             sv );
            iniFile.Get( "",    "concat", sv ); UT_TRUE( sv.StartsWith( "start =5,end   =32" ) );

            iniFile.Get( "ESC", "Blanks",    sv );   UT_EQ( " x ",             sv );
            iniFile.Get( "ESC", "Blanks2",   sv );   UT_EQ( " x  y ",          sv );
            iniFile.Get( "ESC", "Tabs",      sv );   UT_EQ( "\tx\t",           sv );
            iniFile.Get( "ESC", "nrslash",   sv );   UT_EQ( "\n\r//\\", sv );

            iniFile.Get( "Great Section",  "SectionVar",        sv );   UT_EQ( "5",  sv );
            iniFile.Get( "2nd Section",    "SectionVar",        sv );   UT_EQ( "6",  sv );
            iniFile.Get( "Great Section",  "SECTION_CONTINUED", sv );   UT_EQ( "yEs",sv );
            iniFile.Get( "Great Section",  "Tricky",            sv );   UT_EQ( "backslash\\",  sv );

            // add it to ALIB config
            ALox.Init();
            ALIB.Config.InsertPlugin( iniFile, Configuration.PrioIniFile );
            ALIB.Config.Get( "",    "CUBA", sv );   UT_EQ( "a country", sv );
            ALIB.Config.Get( "",    "cUbA", sv );   UT_EQ( "a country", sv );
            ALIB.Config.Get( "",    "SIZE", sv );   UT_EQ( "25", sv );
            ALIB.Config.Get( "",    "concat", sv ); UT_TRUE ( sv.StartsWith( "start =5,end   =32" ) );
            ALIB.Config.Get( "Great Section",  "SectionVar",        sv );   UT_EQ( "5",              sv );
            ALIB.Config.Get( "2nd Section",    "SectionVar",        sv );   UT_EQ( "6",              sv );
            ALIB.Config.Get( "Great Section",  "SECTION_CONTINUED", sv );   UT_EQ( "yEs",            sv );
            ALIB.Config.Get( "Great Section",  "Tricky",            sv );   UT_EQ( "backslash\\",    sv );
            UT_TRUE( ALIB.Config.IsTrue( "Great Section",  "SECTION_CONTINUED" ) );


            // check if environment variable "home" overwrites ini-file
            AString vIniFile= new AString();   iniFile.Get( "", "hOme", vIniFile );               UT_EQ( "overwritten_by_environment", vIniFile );
            AString vConfig=  new AString();
            int prio= ALIB.Config.Get( "", "hOme", vConfig );
            if (prio != Configuration.PrioEnvVars ) // Windows platform?
            {
                prio= ALIB.Config.Get( "", "hOmePAth", vConfig );
                iniFile.Get( "", "hOmePAth", vIniFile );      UT_EQ( "overwritten_by_environment", vIniFile );
            }
            UT_EQ( Configuration.PrioEnvVars, prio );

            UT_TRUE( vConfig.Length() > 0 );
            UT_TRUE( !vIniFile.Equals( vConfig) );



            // change a value and write a new one
            UT_EQ( Configuration.PrioIniFile, ALIB.Config.Save( "New Section",  "newvar", new AString( "new") ) );
            ALIB.Config.Get ( "New Section",  "newvar", sv    );   UT_EQ( "new",   sv );

            UT_EQ( Configuration.PrioIniFile, ALIB.Config.Save( "",             "newvar", new AString( "aworx") ) );
            ALIB.Config.Get ( "",             "newvar", sv     );  UT_EQ( "aworx", sv );

            double dv;
            UT_EQ( Configuration.PrioIniFile, ALIB.Config.Save( "2nd Section",  "newvarF", 3.14 ) );
            ALIB.Config.Get ( "2nd Section",  "newvarF", out dv ); UT_EQ(   3.14, dv );

            int    iv;
            UT_EQ( Configuration.PrioIniFile, ALIB.Config.Save( "Great Section","newvarI", 255  ) );
            ALIB.Config.Get ( "Great Section","newvarI", out iv ); UT_EQ(   255,  iv );

            UT_EQ( Configuration.PrioIniFile, ALIB.Config.Save( "",             "size", 42  ) );
            ALIB.Config.Get ( "",  "size", out iv   );                 UT_EQ(    42, iv );

            UT_EQ( Configuration.PrioIniFile, ALIB.Config.Save( "",   "newvarList", new AString( "val1=5, val2=10, val3=hello"), null, ',' ) );
            ALIB.Config.Get ( "",  "newvarList", out iv   );

            UT_EQ( Configuration.PrioIniFile, ALIB.Config.Save( "",   "commented", new AString( "2lines"), new AString( "this is c-line 1 \nand this line 2" ), ',' ) );



            // write the file
            iniFile.FileName._(".writeback.txt");
            iniFile.WriteFile();

            // load the written file into another config
            IniFile readBack= new IniFile( iniFile.FileName.ToString() );
            readBack.ReadFile();

            // compare all
            UT_TRUE( (IniFile.Status.OK == readBack.LastStatus) );

            {
                AString msg= new AString();
                foreach ( IniFile.Section section in iniFile.Sections )
                {
                    foreach ( IniFile.Variable variable in section.Variables )
                    {
                        readBack.Get( section.Name, variable.Name, sv );
                        msg.Clear()._( "Reading variable " ).Field()._( section.Name )._( '/' )._( variable.Name )._( ": " );
                        msg.Field(40, Alignment.Left)._( variable.Value )._(" / ")._( sv );
                        UT_PRINT( msg );
                        if( !variable.Name.Equals( "newvarList" ) )
                            UT_EQ( variable.Value, sv );
                    }
                }
            }

            readBack.Get ( "New Section",  "newvar",      sv        );   UT_EQ(   "new", sv );
            readBack.Get ( "",             "newvar",      sv        );   UT_EQ( "aworx", sv );
            readBack.Get ( "2nd Section",  "newvarF", out dv, null  );   UT_EQ(    3.14, dv );
            readBack.Get ( "Great Section","newvarI", out iv, null  );   UT_EQ(     255, (int) iv );


            ALIB.Config.RemovePlugin( iniFile );


            ALIB.Config.InsertPlugin( readBack, Configuration.PrioIniFile );
            ALIB.Config.Get ( "New Section",  "newvar",  sv   );   UT_EQ( "new", sv );
            ALIB.Config.Get ( "",             "newvar",  sv   );   UT_EQ( "aworx", sv );
            ALIB.Config.Get ( "2nd Section",  "newvarF", out dv, null   );   UT_EQ(   3.14, dv );
            ALIB.Config.Get ( "Great Section","newvarI", out iv, null   );   UT_EQ(    255, (int) iv );

            ALIB.Config.RemovePlugin( readBack );
        }


}}// class/namespace
