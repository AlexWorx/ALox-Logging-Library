// #################################################################################################
//  aworx - Unit Tests
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
#include "alib/stdafx_alib.h"

#include "alib/alib.hpp"

#if !defined (HPP_ALIB_CONFIG_INI_FILE)
    #include "alib/config/inifile.hpp"
#endif

#if !defined (HPP_ALIB_STRINGS_ASTRING)
    #include "alib/strings/asalloc.hpp"
#endif

#if !defined (HPP_ALIB_SYSTEM_DIRECTORY)
    #include "alib/system/directory.hpp"
#endif


#define TESTCLASSNAME       CPP_ALib_Config
#include "aworx_unittests.hpp"


#include <iostream>
#include <fstream>

using namespace std;
using namespace aworx;

namespace ut_aworx {

UT_CLASS()

//--------------------------------------------------------------------------------------------------
//--- Read and write a configuration file
//--------------------------------------------------------------------------------------------------

UT_METHOD(CommandLineArgs)
{
    UT_INIT();

    const char* args[]=
    {
        "COMMANDLINE",
        "-SingleHyphen=12",
        "--DoubleHyphen=yes",
        "--Empty",
        "--Whitespaces   =  Hello Test  ",
        "--integer =  42",
        "--double =  3.14",
        "-Home=overwritten",
        "--ALIB_TEST=passed",
    };

    Configuration cfg;
    cfg.AddStandardPlugIns( Inclusion::Include, 9, (void**) args );
    AString  v;
    int      prio;
    int32_t  iv;
    double   dv;
    UT_EQ( Configuration::PrioCmdLine,    cfg.Get   ( "",      "SingleHyphen",  v      ) );   UT_EQ( "12",            v   );
    UT_EQ( true,  cfg.IsTrue( "",      "DoubleHyphen",  &prio  ) );   UT_EQ( Configuration::PrioCmdLine,              prio);

    UT_EQ(                              0,    cfg.Get   ( "",      "Empty",         v      ) );   UT_EQ( "",              v   );
    UT_EQ( Configuration::PrioCmdLine,    cfg.Get   ( "",      "Whitespaces",   v      ) );   UT_EQ( "Hello Test",    v   );
    UT_EQ( Configuration::PrioCmdLine,    cfg.Get   ( "",      "HOME",          v      ) );   UT_EQ( "overwritten",   v   );
    UT_EQ( Configuration::PrioCmdLine,    cfg.Get   ( "",      "integer",       iv     ) );   UT_EQ( 42,              iv  );
    UT_EQ(                              0,    cfg.Get   ( "",      "notexistent",   iv     ) );   UT_EQ( 0,               iv  );
    UT_EQ( Configuration::PrioCmdLine,    cfg.Get   ( "",      "integer",       iv     ) );   UT_EQ( 42,              iv  );
    UT_EQ( Configuration::PrioCmdLine,    cfg.Get   ( "",      "double",        dv     ) );   UT_EQ( 3.14,            dv  );
    UT_EQ(                              0,    cfg.Get   ( "",      "notexistent",   dv     ) );   UT_EQ( 0.0,             dv  );
    UT_EQ( Configuration::PrioCmdLine,    cfg.Get   ( "",      "double",        dv     ) );   UT_EQ( 3.14,            dv  );
    UT_EQ( Configuration::PrioCmdLine,    cfg.Get   ( "ALIB",  "test",           v     ) );   UT_EQ( "passed",        v   );
}

UT_METHOD(CommandLineArgsWChar)
{
    UT_INIT();

    const wchar_t* args[]=
    {
        L"COMMANDLINE",
        L"-SingleHyphen=12",
        L"--DoubleHyphen=yes",
        L"--Empty",
        L"--Whitespaces   =  Hello Test  ",
        L"--integer =  42",
        L"--double =  3.14",
        L"-Home=overwritten",
        L"--ALIB_TEST=passed",
    };

    Configuration cfg;
    cfg.AddStandardPlugIns( Inclusion::Include, 9, (void**) args, true );
    AString  v;
    int      prio;
    int32_t  iv;
    double   dv;
    UT_EQ( Configuration::PrioCmdLine,    cfg.Get   ( "",      "SingleHyphen",  v      ) );   UT_EQ( "12",            v   );
    UT_EQ( true,  cfg.IsTrue( "",      "DoubleHyphen",  &prio  ) );   UT_EQ( Configuration::PrioCmdLine,              prio);

    UT_EQ(                              0,    cfg.Get   ( "",      "Empty",         v      ) );   UT_EQ( "",              v   );
    UT_EQ( Configuration::PrioCmdLine,    cfg.Get   ( "",      "Whitespaces",   v      ) );   UT_EQ( "Hello Test",    v   );
    UT_EQ( Configuration::PrioCmdLine,    cfg.Get   ( "",      "HOME",          v      ) );   UT_EQ( "overwritten",   v   );
    UT_EQ( Configuration::PrioCmdLine,    cfg.Get   ( "",      "integer",       iv     ) );   UT_EQ( 42,              iv  );
    UT_EQ(                              0,    cfg.Get   ( "",      "notexistent",   iv     ) );   UT_EQ( 0,               iv  );
    UT_EQ( Configuration::PrioCmdLine,    cfg.Get   ( "",      "integer",       iv     ) );   UT_EQ( 42,              iv  );
    UT_EQ( Configuration::PrioCmdLine,    cfg.Get   ( "",      "double",        dv     ) );   UT_EQ( 3.14,            dv  );
    UT_EQ(                              0,    cfg.Get   ( "",      "notexistent",   dv     ) );   UT_EQ( 0.0,             dv  );
    UT_EQ( Configuration::PrioCmdLine,    cfg.Get   ( "",      "double",        dv     ) );   UT_EQ( 3.14,            dv  );
    UT_EQ( Configuration::PrioCmdLine,    cfg.Get   ( "ALIB",  "test",           v     ) );   UT_EQ( "passed",        v   );
}

//--------------------------------------------------------------------------------------------------
//--- Read and write a configuration file
//--------------------------------------------------------------------------------------------------

UT_METHOD(IniFiles)
{
    UT_INIT();

    // write sample config file
    UT_PRINT(""); UT_PRINT( "### Configuration with IniFile ###" );
    const char* iniFileContents=
    "##########################################################################"  "\n"
    "## unit test config file"                                                    "\n"
    "##########################################################################"  "\n"
    "// this is also a comment"                                                   "\n"
    "; and this is as well"                                                       "\n"
    ""                                                                            "\n"
    "HOME=     overwritten_by_environment"                                        "\n"
    "HOMEPATH= overwritten_by_environment"                                        "\n"
    ""                                                                            "\n"
    "concat=    start =5,          \\"                                            "\n"
    "           end   =32,       \\"                                              "\n"
    "           getsLonger,    \\"                                                "\n"
    "           getsLongerxxx,   \\"                                              "\n"
    "           getsshorter,    \\"                                               "\n"
    "           getsLongerxxxxx,  \\"                                             "\n"
    "           getsLongerxxxxxxxxx,  \\"                                         "\n"
    "           getsshorterxx,    \\"                                             "\n"
    "           last"                                                             "\n"
    ""                                                                            "\n"
    ""                                                                            "\n"
    "CUBA=a country"                                                              "\n"
    "# The size "                                                                 "\n"
    " SIZE=  25 "                                                                 "\n"
    ""                                                                            "\n"
    "# doble comment line"                                                        "\n"
    "# double, I meant"                                                           "\n"
    "2Comments= much talk"                                                        "\n"
    ""                                                                            "\n"
    "# A great section"                                                           "\n"
    "[Great Section] "                                                            "\n"
    "SectionVar=5"                                                                "\n"
    "Double=12.3"                                                                 "\n"
    "Tricky=  backslash\\\\"                                                      "\n"
    "OverWritten=No"                                                              "\n"
    ""                                                                            "\n"
    "# A 2nd section"                                                             "\n"
    "[2nd Section] "                                                              "\n"
    "SectionVar=6"                                                                "\n"
    ""                                                                            "\n"
    ""                                                                            "\n"
    "[Great Section] "                                                            "\n"
    "SECTION_CONTINUED   = yEs"                                                   "\n"
    ""                                                                            "\n"
    "OverWritten=Yes"                                                             "\n"
    ""                                                                            "\n"
    "[ESC] "                                                                      "\n"
    "Blanks=  \" x \""                                                            "\n"
    "Blanks2= \" x \" \\"                                                         "\n"
    "         \" y \" "                                                           "\n"
    "Tabs=\t\t\\tx\\t"                                                            "\n"
    "nrslash= \"\\n\\r//\\\\\""                                                   "\n"
   ;

    AString fileName;
    Directory::CurrentDirectory( fileName );
    fileName._("/unittest_testiniFile.cfg");

    // write sample config file
    {
        ofstream iniFile;
        iniFile.open ( fileName.ToCString() );
        iniFile << iniFileContents;
        iniFile.close();
    }

    IniFile iniFile( fileName );
    iniFile.ReadFile();
    UT_TRUE( (IniFile::Status::Ok == iniFile.LastStatus) );

    // check some values
    AString sv;
    iniFile.Get( "",               "CUBA",              sv );   UT_EQ( "a country",       sv );
    iniFile.Get( "",               "cUbA",              sv );   UT_EQ( "a country",       sv );
    iniFile.Get( "",               "SIZE",              sv );   UT_EQ( "25",              sv );
    iniFile.Get( "",               "concat",            sv );   UT_TRUE( sv.StartsWith( "start =5,end   =32" ) );

    iniFile.Get( "ESC",            "Blanks",            sv );   UT_EQ( " x ",             sv );
    iniFile.Get( "ESC",            "Blanks2",           sv );   UT_EQ( " x  y ",          sv );
    iniFile.Get( "ESC",            "Tabs",              sv );   UT_EQ( "\tx\t",           sv );
    iniFile.Get( "ESC",            "nrslash",           sv );   UT_EQ( "\n\r//\\",        sv );

    iniFile.Get( "Great Section",  "SectionVar",        sv );   UT_EQ( "5",               sv );
    iniFile.Get( "2nd Section",    "SectionVar",        sv );   UT_EQ( "6",               sv );
    iniFile.Get( "Great Section",  "SECTION_CONTINUED", sv );   UT_EQ( "yEs",             sv );
    iniFile.Get( "Great Section",  "Tricky",            sv );   UT_EQ( "backslash\\",     sv );
    iniFile.Get( "Great Section",  "Overwritten",       sv );   UT_EQ( "Yes",             sv );


    // add it to ALIB config
    ALIB::Config.InsertPlugin( &iniFile, Configuration::PrioIniFile );
    ALIB::Config.Get( "",    "CUBA", sv );   UT_EQ( "a country", sv );
    ALIB::Config.Get( "",    "cUbA", sv );   UT_EQ( "a country", sv );
    ALIB::Config.Get( "",    "SIZE", sv );   UT_EQ( "25", sv );
    ALIB::Config.Get( "",    "concat", sv ); UT_TRUE ( sv.StartsWith( "start =5,end   =32" ) );
    ALIB::Config.Get( "Great Section",  "SectionVar",        sv );   UT_EQ( "5",              sv );
    ALIB::Config.Get( "2nd Section",    "SectionVar",        sv );   UT_EQ( "6",              sv );
    ALIB::Config.Get( "Great Section",  "SECTION_CONTINUED", sv );   UT_EQ( "yEs",            sv );
    ALIB::Config.Get( "Great Section",  "Tricky",            sv );   UT_EQ( "backslash\\",    sv );
    UT_TRUE( ALIB::Config.IsTrue( "Great Section",  "SECTION_CONTINUED" ) );


    // check if environment variable "home" overwrites INI file
    const char* HOME_ENV_NAME;
    #if defined(_WIN32)
        HOME_ENV_NAME= "HOmepATH";
    #else
        HOME_ENV_NAME= "HomE";
    #endif

    AString vIniFile;   iniFile.Get( "", HOME_ENV_NAME, vIniFile );                 UT_EQ( "overwritten_by_environment", vIniFile );
    AString vConfig;    int prio= ALIB::Config.Get( "", HOME_ENV_NAME, vConfig ); UT_EQ( Configuration::PrioEnvVars, prio );
    UT_TRUE( vConfig.IsNotEmpty() );
    UT_TRUE( !vIniFile.Equals( vConfig) );


    // change a value and write a new one
    UT_EQ( Configuration::PrioIniFile, ALIB::Config.Save( "New Section",  "newvar", "new" ) );
    ALIB::Config.Get ( "New Section",  "newvar", sv    );   UT_EQ( "new",   sv );

    UT_EQ( Configuration::PrioIniFile, ALIB::Config.Save( "",             "newvar", "aworx") );
    ALIB::Config.Get ( "",             "newvar", sv     );  UT_EQ( "aworx", sv );

    double dv;
    UT_EQ( Configuration::PrioIniFile, ALIB::Config.Save( "2nd Section",  "newvarF", 3.14 ) );
    ALIB::Config.Get ( "2nd Section",  "newvarF", dv   );   UT_EQ(   3.14, dv );

    int32_t iv;
    UT_EQ( Configuration::PrioIniFile, ALIB::Config.Save( "Great Section","newvarI", 255  ) );
    ALIB::Config.Get ( "Great Section","newvarI", iv   );   UT_EQ(   255, iv );

    UT_EQ( Configuration::PrioIniFile, ALIB::Config.Save( "",             "size", 42  ) );
    ALIB::Config.Get ( "",  "size", iv   );                 UT_EQ(    42, iv );

    UT_EQ( Configuration::PrioIniFile, ALIB::Config.Save( "",   "newvarList", "val1=5, val2=10, val3=hello", (const char*) nullptr, ',' ) );
    ALIB::Config.Get ( "",  "newvarList", iv   );

    UT_EQ( Configuration::PrioIniFile, ALIB::Config.Save( "",   "commented", "2lines", "this is c-line 1 \nand this line 2", ',' ) );



    // write the file
    iniFile.FileName._(".writeback.txt");
    iniFile.WriteFile();

    // load the written file into another config
    IniFile readBack;
    readBack.FileName= iniFile.FileName;
    readBack.ReadFile();

    // compare all
    UT_TRUE( (IniFile::Status::Ok == readBack.LastStatus) );

    {
        String512 msg;
        for ( IniFile::Section* section : iniFile.Sections )
        {
            for ( IniFile::Variable* variable : section->Variables )
            {
                readBack.Get( section->Name, variable->Name, sv );
                msg.Clear()._( "Reading variable " )
                ._(Format::Field( String256() << section->Name << '/' << variable->Name << ": ", 40, Alignment::Left) )
                << variable->Value << " / " << sv;
                UT_PRINT( msg );

                if( !variable->Name.Equals( "newvarList" ) )
                    UT_EQ( variable->Value, sv );
            }
        }
    }

    readBack.Get ( "New Section",  "newvar",  sv   );   UT_EQ( "new", sv );
    readBack.Get ( "",             "newvar",  sv   );   UT_EQ( "aworx", sv );
    readBack.Get ( "2nd Section",  "newvarF", dv   );   UT_EQ(   3.14, dv );
    readBack.Get ( "Great Section","newvarI", iv   );   UT_EQ(    255, (int) iv );


    ALIB::Config.RemovePlugin( &iniFile );


    ALIB::Config.InsertPlugin( &readBack, Configuration::PrioIniFile );
    ALIB::Config.Get ( "New Section",  "newvar",  sv   );   UT_EQ( "new", sv );
    ALIB::Config.Get ( "",             "newvar",  sv   );   UT_EQ( "aworx", sv );
    ALIB::Config.Get ( "2nd Section",  "newvarF", dv   );   UT_EQ(   3.14, dv );
    ALIB::Config.Get ( "Great Section","newvarI", iv   );   UT_EQ(    255, (int) iv );

    ALIB::Config.RemovePlugin( &readBack );
}



UT_CLASS_END

}; //namespace



