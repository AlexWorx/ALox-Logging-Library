// #################################################################################################
//  Unit Tests - AWorx Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
package ut_alib;
import java.io.BufferedWriter;
import java.io.FileWriter;

import org.junit.Test;

import ut_com_aworx_uttools.AUnitTest;

import com.aworx.lib.*;
import com.aworx.lib.config.*;
import com.aworx.lib.enums.Alignment;
import com.aworx.lib.strings.AString;
import com.aworx.lox.ALox;


public class UT_alib_config extends AUnitTest
{
    //---------------------------------------------------------------------------------------------------------
    //--- Test CommandLineArgs
    //---------------------------------------------------------------------------------------------------------
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

        Configuration cfg= new Configuration( true, args );
        AString  v=     new AString();
        AString  temp=  new AString();
        int[]    prio=  new int[1];
        int[]    iv=    new int[1];
        double[] dv=    new double[1];
        UT_EQ( Configuration.PRIO_CMD_LINE,    cfg.get   ( null,  "SingleHyphen",  v            ) );   UT_EQ( "12",            v.toString() );
        UT_EQ( true,  cfg.isTrue( null,  "DoubleHyphen",  prio,  temp  ) );   UT_EQ( Configuration.PRIO_CMD_LINE,              prio[0] );

        UT_EQ(                             0,    cfg.get   ( null,  "Empty",         v            ) );   UT_EQ( "",              v.toString() );
        UT_EQ( Configuration.PRIO_CMD_LINE,    cfg.get   ( null,  "Whitespaces",   v            ) );   UT_EQ( "Hello Test",    v.toString() );
        UT_EQ( Configuration.PRIO_CMD_LINE,    cfg.get   ( null,  "HOME",          v            ) );   UT_EQ( "overwritten",   v.toString() );
        UT_EQ( Configuration.PRIO_CMD_LINE,    cfg.get   ( null,  "integer",       iv           ) );   UT_EQ( 42,              iv[0] );
        UT_EQ(                             0,    cfg.get   ( null,  "notexistant",   iv           ) );   UT_EQ( 0,               iv[0] );
        UT_EQ( Configuration.PRIO_CMD_LINE,    cfg.get   ( null,  "integer",       iv, temp     ) );   UT_EQ( 42,              iv[0] );
        UT_EQ( Configuration.PRIO_CMD_LINE,    cfg.get   ( null,  "double",        dv           ) );   UT_EQ( 3.14,            dv[0], 0.0 );
        UT_EQ(                             0,    cfg.get   ( null,  "notexistant",   dv           ) );   UT_EQ( 0.0,             dv[0], 0.0 );
        UT_EQ( Configuration.PRIO_CMD_LINE,    cfg.get   ( null,  "double",        dv, temp     ) );   UT_EQ( 3.14,            dv[0], 0.0 );
        UT_EQ( Configuration.PRIO_CMD_LINE,    cfg.get   ( "ALIB", "test",         v            ) );   UT_EQ( "passed",        v.toString() );
    }

    //---------------------------------------------------------------------------------------------------------
    //--- Test IniFile
    //---------------------------------------------------------------------------------------------------------
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
        catch(Exception e)
        {
            UT_TRUE( false );
        }

        IniFile iniFile= new IniFile( fileName );
        iniFile.readFile();
        UT_TRUE( (IniFile.Status.OK == iniFile.lastStatus) );

        // check some values
        AString sv= new AString();
        iniFile.get( "",    "CUBA", sv );   UT_EQ( "a country",      sv.toString() );
        iniFile.get( "",    "cUbA", sv );   UT_EQ( "a country",      sv.toString() );
        iniFile.get( "",    "SIZE", sv );   UT_EQ( "25",             sv.toString() );
        iniFile.get( "",    "concat", sv ); UT_TRUE( sv.startsWith( "start =5,end   =32" ) );

        iniFile.get( "ESC", "Blanks",    sv );   UT_EQ( " x ",             sv.toString() );
        iniFile.get( "ESC", "Blanks2",   sv );   UT_EQ( " x  y ",          sv.toString() );
        iniFile.get( "ESC", "Tabs",      sv );   UT_EQ( "\tx\t",           sv.toString() );
        iniFile.get( "ESC", "nrslash",   sv );   UT_EQ( "\n\r//\\", sv.toString() );

        iniFile.get( "Great Section",  "SectionVar",        sv );   UT_EQ( "5",  sv.toString() );
        iniFile.get( "2nd Section",    "SectionVar",        sv );   UT_EQ( "6",  sv.toString() );
        iniFile.get( "Great Section",  "SECTION_CONTINUED", sv );   UT_EQ( "yEs",sv.toString() );
        iniFile.get( "Great Section",  "Tricky",            sv );   UT_EQ( "backslash\\",  sv.toString() );

        // add it to ALIB config
        ALox.init(true, null);
        ALIB.config.insertPlugin( iniFile, Configuration.PRIO_INI_FILE );
        ALIB.config.get( "",    "CUBA", sv );   UT_EQ( "a country", sv.toString() );
        ALIB.config.get( "",    "cUbA", sv );   UT_EQ( "a country", sv.toString() );
        ALIB.config.get( "",    "SIZE", sv );   UT_EQ( "25", sv.toString() );
        ALIB.config.get( "",    "concat", sv ); UT_TRUE ( sv.startsWith( "start =5,end   =32" ) );
        ALIB.config.get( "Great Section",  "SectionVar",        sv );   UT_EQ( "5",              sv.toString() );
        ALIB.config.get( "2nd Section",    "SectionVar",        sv );   UT_EQ( "6",              sv.toString() );
        ALIB.config.get( "Great Section",  "SECTION_CONTINUED", sv );   UT_EQ( "yEs",            sv.toString() );
        ALIB.config.get( "Great Section",  "Tricky",            sv );   UT_EQ( "backslash\\",    sv.toString() );
        UT_TRUE( ALIB.config.isTrue( "Great Section",  "SECTION_CONTINUED" ) );


        // check if environment variable "home" overwrites ini-file
        AString vIniFile= new AString();   iniFile.get( "", "hOme", vIniFile );               UT_EQ( "overwritten_by_environment", vIniFile.toString() );
        AString vConfig=  new AString();
        int prio= ALIB.config.get( "", "hOme", vConfig );  UT_EQ( Configuration.PRIO_ENV_VARS, prio );
        UT_TRUE( vConfig.isNotEmpty() );
        UT_TRUE( !vIniFile.equals( vConfig) );



        // change a value and write a new one
        UT_EQ( Configuration.PRIO_INI_FILE, ALIB.config.save( "New Section",  "newvar", new AString( "new") ) );
        ALIB.config.get ( "New Section",  "newvar", sv    );   UT_EQ( "new",   sv.toString() );

        UT_EQ( Configuration.PRIO_INI_FILE, ALIB.config.save( "",             "newvar", new AString( "aworx") ) );
        ALIB.config.get ( "",             "newvar", sv     );  UT_EQ( "aworx", sv.toString() );

        double[] dv= new double[1];
        UT_EQ( Configuration.PRIO_INI_FILE, ALIB.config.save( "2nd Section",  "newvarF", 3.14 ) );
        ALIB.config.get ( "2nd Section",  "newvarF", dv ); UT_EQ(   3.14, dv[0], 0.0 );

        int[]    iv= new int[1];
        UT_EQ( Configuration.PRIO_INI_FILE, ALIB.config.save( "Great Section","newvarI", 255  ) );
        ALIB.config.get ( "Great Section","newvarI", iv ); UT_EQ(   255,  iv[0] );

        UT_EQ( Configuration.PRIO_INI_FILE, ALIB.config.save( "",             "size", 42  ) );
        ALIB.config.get ( "",  "size", iv   );                 UT_EQ(    42, iv[0] );

        UT_EQ( Configuration.PRIO_INI_FILE, ALIB.config.save( "",   "newvarList", new AString( "val1=5, val2=10, val3=hello"), null, ',' ) );
        ALIB.config.get ( "",  "newvarList", iv   );

        UT_EQ( Configuration.PRIO_INI_FILE, ALIB.config.save( "",   "commented", new AString( "2lines"), new AString( "this is c-line 1 \nand this line 2" ), ',' ) );



        // write the file
        iniFile.fileName._(".writeback.txt");
        iniFile.writeFile();

        // load the written file into another config
        IniFile readBack= new IniFile( iniFile.fileName.toString() );
        readBack.readFile();

        // compare all
        UT_TRUE( (IniFile.Status.OK == readBack.lastStatus) );

        {
            AString msg= new AString();
            for ( IniFile.Section section : iniFile.sections )
            {
                for ( IniFile.Variable variable : section.variables )
                {
                    readBack.get( section.name, variable.name, sv );
                    msg.clear()._( "Reading variable " ).field()._( section.name )._( '/' )._( variable.name )._( ": " )
                       .field(40, Alignment.LEFT)._( variable.value )._(" / ")._( sv );
                    //UT_PRINT( msg.Buffer() );

                    if( !variable.name.equals( "newvarList" ) )
                        UT_EQ( variable.value.toString(), sv.toString() );
                }
            }
        }

        readBack.get ( "New Section",  "newvar",      sv        );   UT_EQ(   "new", sv.toString() );
        readBack.get ( "",             "newvar",      sv        );   UT_EQ( "aworx", sv.toString() );
        readBack.get ( "2nd Section",  "newvarF",     dv, null  );   UT_EQ(    3.14, dv[0], 0.0 );
        readBack.get ( "Great Section","newvarI",     iv, null  );   UT_EQ(     255, iv[0] );


        ALIB.config.removePlugin( iniFile );


        ALIB.config.insertPlugin( readBack, Configuration.PRIO_INI_FILE );
        ALIB.config.get ( "New Section",  "newvar",  sv   );   UT_EQ( "new", sv.toString() );
        ALIB.config.get ( "",             "newvar",  sv   );   UT_EQ( "aworx", sv.toString() );
        ALIB.config.get ( "2nd Section",  "newvarF", dv, null   );   UT_EQ(   3.14, dv[0], 0.0 );
        ALIB.config.get ( "Great Section","newvarI", iv, null   );   UT_EQ(    255, iv[0] );

        ALIB.config.removePlugin( readBack );
    }

}
