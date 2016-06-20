// #################################################################################################
//  Unit Tests - AWorx Library
//  (Tests to create tutorial sample code and output)
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
package ut_alox;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;

import org.junit.Test;

import ut_com_aworx_uttools.AUnitTest;
import ut_com_aworx_uttools.UnitTestSampleWriter;




import com.aworx.lib.enums.Inclusion;
//! [Tut_using_statement]
import com.aworx.lib.strings.*;
import com.aworx.lox.*;
import com.aworx.lox.loggers.*;
import com.aworx.lox.core.textlogger.*;
import com.aworx.lox.tools.LogTools;
//! [Tut_using_statement]


// #################################################################################################
// Tut_ScopeDomains
// #################################################################################################
class TutScopeDom
{
    //! [Tut_ScopeDomains]
    public char[] Extract( String fileName, char[] buffer )
    {
        Log.setDomain( "ZIP/EXTRACT", Scope.METHOD ); // set Scope Domain path for this method
        //...
        Log.info( "Extracting " + fileName );
        //...
        //...
        Log.info( "Success" ); // a nice, clear, local, copyable log statement!
        //...
        return buffer;
    }
    //! [Tut_ScopeDomains]
}

//! [Tut_ScopeDomains_Zipper]
class Zipper
{
    public Zipper()
    {
        Log.setDomain( "ZIP", Scope.CLASS ); // set Scope Domain path for this class
        //...
        Log.info( "Zipper created" ); // domain "ZIP"
        //...
    }

    public char[] Compress( String fileName, char[] buffer )
    {
        Log.setDomain( "COMPRESS", Scope.METHOD ); // set Scope Domain path for this method
        //...
        Log.info( "Compressing " + fileName );
        //...
        //...
        Log.info( "Success" ); // domain "ZIP/COMPRESS"
        //...
        return buffer;
    }

    public char[] Extract( String fileName, char[] buffer )
    {
        Log.setDomain( "EXTRACT", Scope.METHOD ); // set Scope Domain path for this method
        //...
        Log.info( "Extracting " + fileName );
        //...
        //...
        Log.info( "Success" ); // domain "ZIP/EXTRACT"
        //...
        return buffer;
    }
}
//! [Tut_ScopeDomains_Zipper]

// #################################################################################################
// Tut_LogData
// #################################################################################################
//! [Tut_LogData]
class FileIO
{
    public void Read(String fileName )
    {
        Log.setDomain( "READ", Scope.METHOD );
        Log.info( "Reading " + fileName );

        int fileVersion= 0;
        //...
        //...
        // Identified file version
        fileVersion= 42;

        Log.store( new LogData( fileVersion ), "FILE_VERSION" );

        //...
        //...
        Log.info( "Success" );
    }
};
//! [Tut_LogData]

/** ************************************************************************************************
*  Implements the tutorial code that with snippets markers for doxygen inclusion.
**************************************************************************************************/
public class UT_dox_tutorial  extends AUnitTest
{

MemoryLogger    tutLog;
String          outputPath=        UnitTestSampleWriter.getGeneratedSamplesDir();

void SaveTutorialOutput( String fileName, AString log )
{
    // check
    if ( outputPath.length() == 0 )
        return;

    @SuppressWarnings ("resource")
    BufferedWriter writer = null;
    try
    {
        File logFile= new File( outputPath + fileName );
        writer= new BufferedWriter(new FileWriter(logFile));
        writer.write( log.toString() );
    }
    catch (Exception e)
    {
        e.printStackTrace();
    }
    finally
    {
       try  { if ( writer != null ) writer.close(); }   catch (Exception e) {}
    }
}

@Test
public void Tut_Hello_ALox_Minimum()
{
    UT_INIT();

    (new HelloALox()).sayHello();
}

@Test
public void Tut_Hello_ALox()
{
    UT_INIT();

    //! [Tut_Hello_ALox]
    //! [Tut_ALox_Logger_1]
    Log.addDebugLogger();
    //! [Tut_ALox_Logger_1]

    Log.removeDebugLogger();
    Log.setVerbosity( tutLog= new MemoryLogger( "Tutlog" ), Verbosity.VERBOSE );

    //! [Tut_ALox_Logger_2]
    Log.addDebugLogger();
    Log.info( "Hello ALox" );
    //! [Tut_ALox_Logger_2]
    //! [Tut_Hello_ALox]

    SaveTutorialOutput( "Tut_ALox_Logger.txt", tutLog.memoryLog );
}

@Test
public void Tut_Verbosity()
{
    UT_INIT();

    Log.setVerbosity( tutLog= new MemoryLogger( "Tutlog" ), Verbosity.VERBOSE );

    //! [Tut_Verbosity]
    Log.addDebugLogger();

    Log.error  ( "A severe error happened :-(" );
    Log.warning( "This is a warning :-/ Maybe an error follows?" );
    Log.info   ( "Just for your further information!" );
    Log.verbose( "Today, I am in the mood to talk..." );
    //! [Tut_Verbosity]


    //! [Tut_Verbosity_SetVerbosity]
    Log.setVerbosity( Log.debugLogger, Verbosity.WARNING );
    //! [Tut_Verbosity_SetVerbosity]

    //! [Tut_Verbosity_SetVerbosity_2]
    Log.setVerbosity( "DEBUG_LOGGER", Verbosity.WARNING );
    //! [Tut_Verbosity_SetVerbosity_2]

    SaveTutorialOutput( "Tut_Verbosity.txt", tutLog.memoryLog );
    tutLog.memoryLog.clear(); tutLog.cntLogs= 0;
    Log.setVerbosity( tutLog, Verbosity.WARNING );

    Log.removeDebugLogger();

    //! [Tut_Verbosity_2]
    Log.addDebugLogger();

    Log.setVerbosity( Log.debugLogger, Verbosity.WARNING );

    Log.error  ( "A severe error happened :-(" );
    Log.warning( "This is a warning :-/ Maybe an error follows?" );
    Log.info   ( "Just for your further information!" );
    Log.verbose( "Today, I am in the mood to talk..." );
    //! [Tut_Verbosity_2]

    SaveTutorialOutput( "Tut_Verbosity_2.txt", tutLog.memoryLog );
    Log.removeLogger( tutLog );
}

@Test
public void Tut_Domains()
{
    UT_INIT();

    Log.setVerbosity( tutLog= new MemoryLogger( "Tutlog" ), Verbosity.VERBOSE );

    //! [Tut_Domains]
    Log.addDebugLogger();
    Log.setVerbosity( Log.debugLogger, Verbosity.VERBOSE ); // the default anyhow
    //...
    Log.verbose( "HTTP", "Connected" );
    //...
    //...
    //...
    Log.verbose( "UI",   "Somebody moved the mouse!" );
    //...
    //! [Tut_Domains]


    SaveTutorialOutput( "Tut_Domains.txt", tutLog.memoryLog );
    tutLog.memoryLog.clear(); tutLog.cntLogs= 0;
    Log.removeDebugLogger();

    Log.setVerbosity( tutLog, Verbosity.VERBOSE,  "HTTP" ); // our interest
    Log.setVerbosity( tutLog, Verbosity.ERROR,    "UI"   ); // only if ouch!

    //! [Tut_Domains_2]
    Log.addDebugLogger();

    Log.setVerbosity( Log.debugLogger, Verbosity.VERBOSE,  "HTTP" ); // our interest
    Log.setVerbosity( Log.debugLogger, Verbosity.ERROR,    "UI"   ); // only if ouch!
    //...
    Log.verbose( "HTTP", "Connected" );
    //...
    //...
    //...
    Log.verbose( "UI",   "Somebody moved the mouse!" );
    //...
    //! [Tut_Domains_2]

    SaveTutorialOutput( "Tut_Domains_2.txt", tutLog.memoryLog );
    Log.removeLogger( tutLog );
}

@Test
public void Tut_HierDom()
{
    UT_INIT();

    Log.setVerbosity( tutLog= new MemoryLogger( "Tutlog" ), Verbosity.VERBOSE );

    //! [Tut_DomainsHierarchical]
    Log.addDebugLogger();
    Log.setVerbosity( Log.debugLogger, Verbosity.VERBOSE ); // the default anyhow
    //...
    Log.info   ( "UI/MOUSE",   "A mouse click" );
    //...
    Log.verbose( "UI/MOUSE",   "Somebody moved the mouse!" );
    //...
    //...
    Log.info   ( "UI/DLG",     "About dialog opend" );
    //...
    Log.verbose( "UI/DLG",     "About dialog, link to product page pressed." );
    //...
    //! [Tut_DomainsHierarchical]


    SaveTutorialOutput( "Tut_DomainsHierarchical.txt", tutLog.memoryLog );
    tutLog.memoryLog.clear(); tutLog.cntLogs= 0;
    Log.removeDebugLogger();

    //! [Tut_DomainsHierarchical_2]
    Log.setVerbosity( Log.debugLogger, Verbosity.WARNING, "UI"  ); // Always sets all sub-domains!
    //! [Tut_DomainsHierarchical_2]

    //! [Tut_DomainsHierarchical_3]
    Log.setVerbosity( Log.debugLogger, Verbosity.WARNING, "UI"       ); // First set parent...
    Log.setVerbosity( Log.debugLogger, Verbosity.VERBOSE, "UI/MOUSE" ); // ...then children!
    //! [Tut_DomainsHierarchical_3]

    Log.removeLogger( tutLog );
}


@Test
public void Tut_ScopeDomains()
{
    UT_INIT();

    Log.setVerbosity( tutLog= new MemoryLogger( "Tutlog" ), Verbosity.VERBOSE );
    Log.addDebugLogger();

    TutScopeDom tsd= new TutScopeDom();
    tsd.Extract( "myfile.zip", null );

    SaveTutorialOutput( "Tut_ScopeDomains.txt", tutLog.memoryLog );
    tutLog.memoryLog.clear(); tutLog.cntLogs= 0;

    // do it once to set the tab positions of the meta info...
    {
        Zipper zip= new Zipper();
        zip.Compress( "myfile.zip", null );
        zip.Extract( "myfile.zip", null );
        tutLog.memoryLog.clear(); tutLog.cntLogs= 0;
    }
    // ...and again
    {
        Zipper zip= new Zipper();
        zip.Compress( "myfile.zip", null );
        zip.Extract( "myfile.zip", null );
    }

    SaveTutorialOutput( "Tut_ScopeDomains_Zipper.txt", tutLog.memoryLog );

    //---------- with scope path ---------------

    //! [Tut_ScopeDomains_Path]
    Log.setDomain( "UTIL", Scope.PACKAGE );
    //! [Tut_ScopeDomains_Path]

    tutLog.memoryLog.clear(); tutLog.cntLogs= 0;
    // do it once to set the tab positions of the meta info...
    {
        Zipper zip= new Zipper();
        zip.Compress( "myfile.zip", null );
        zip.Extract( "myfile.zip", null );
        tutLog.memoryLog.clear(); tutLog.cntLogs= 0;
    }
    // ...and again
    {
        Zipper zip= new Zipper();
        zip.Compress( "myfile.zip", null );
        zip.Extract( "myfile.zip", null );
    }
    SaveTutorialOutput( "Tut_ScopeDomains_Zipper_Path.txt", tutLog.memoryLog );
    tutLog.memoryLog.clear(); tutLog.cntLogs= 0;

    Log.setDomain( null, Scope.PACKAGE );
    Log.setDomain( null, Scope.CLASS );

    //! [Tut_ScopeDomains_ParamDom]
    Log.setDomain( "METHOD", Scope.METHOD );
    Log.info(          "No domain parameter given" );
    Log.info( "PARAM", "Domain parameter \"PARAM\" given" );
    //! [Tut_ScopeDomains_ParamDom]

    // clear autosizes, repeat it twice
    tutLog.autoSizes.reset();
    Log.info(          "No domain parameter given" );
    Log.info( "PARAM", "Domain parameter \"PARAM\" given" );
    tutLog.memoryLog.clear(); tutLog.cntLogs= 0;
    Log.info(          "No domain parameter given" );
    Log.info( "PARAM", "Domain parameter \"PARAM\" given" );

    SaveTutorialOutput( "Tut_ScopeDomains_ParamDom.txt", tutLog.memoryLog );
    tutLog.memoryLog.clear(); tutLog.cntLogs= 0;


    //! [Tut_ScopeDomains_ParamDom_2]
    Log.setDomain( "READ", Scope.METHOD );
    Log.info( "Reading file" );
    //...
    //...
    Log.info( "/CONFIG",   "Path not found." );
    //...
    //! [Tut_ScopeDomains_ParamDom_2]

    SaveTutorialOutput( "Tut_ScopeDomains_ParamDom_2.txt", tutLog.memoryLog );

    Log.removeLogger( tutLog );
}


@Test
public void Tut_Prefix()
{
    UT_INIT();

    Log.setVerbosity( tutLog= new MemoryLogger( "Tutlog" ), Verbosity.VERBOSE );
    Log.addDebugLogger();


    //! [Tut_Prefix]
    Log.setPrefix( "ALOX TUTORIAL: ", Scope.METHOD );

    Log.info( "Well, just a sample" );
    //! [Tut_Prefix]


    SaveTutorialOutput( "Tut_Prefix.txt", tutLog.memoryLog );

    //! [Tut_Prefix_2]
    Log.setPrefix( ESC.BG_MAGENTA, Scope.CLASS );
    //! [Tut_Prefix_2]

    Log.warning( "magenta" );

    Log.removeLogger( tutLog );
}


public void Tut_ConditionalLogging()
{
    String[] array= new String[5];
    int len= 5;
    String search= null;

    //! [Tut_ConditionalLogging]
    int i= 0;
    while( i < len )
    {
        if ( array[i] == search )
        {
            process( i );
            break;
        }
        i++;
    }
    if ( i == len )
        Log.error( "Nothing found :-(" );
    //! [Tut_ConditionalLogging]

    //! [Tut_ConditionalLogging2]
    Log.Assert( i < len, "Nothing found :-(" );
    //! [Tut_ConditionalLogging2]

    //! [Tut_ConditionalLogging3]
    Log.If( i == len, Verbosity.ERROR, "Nothing found :-(" );
    //! [Tut_ConditionalLogging3]

    //! [Tut_ConditionalLoggingOnce]
    Log.once( "I tell you this now only once!" );
    //! [Tut_ConditionalLoggingOnce]
}

private void process(@SuppressWarnings ("unused") int i) {}

@Test
public void Tut_Instance()
{
    UT_INIT();

    Log.setVerbosity( new ConsoleLogger(), Verbosity.VERBOSE, "/" );
    Log.setVerbosity( tutLog= new MemoryLogger( "Tutlog" ),  Verbosity.VERBOSE, "MYDOM" );
    Log.setVerbosity( tutLog, Verbosity.VERBOSE, "/" );
    tutLog.multiLineMsgMode= 4;

    //! [Tut_Instance]
    // Log multi-lines without meta info
    ((TextLogger) Log.getLogger( "Console" )).multiLineMsgMode= 4;

    // Log current thread instance
    LogTools.instance( "MYDOM", Verbosity.INFO, Thread.currentThread(), 4, "Actual Thread: " );
    //! [Tut_Instance]


    // cut the output to 30 lines
    int lines= 32;
    int idx= 0;
    while (lines-- != 0)
    {
        idx= tutLog.memoryLog.indexOf( CString.NEW_LINE_CHARS, idx + CString.NEW_LINE_CHARS.length() );
        if ( idx < 0 )
            break;
    }
    if (idx > 0)
        tutLog.memoryLog.setLength( idx + CString.NEW_LINE_CHARS.length() );
    tutLog.memoryLog._( "..." )._( CString.NEW_LINE_CHARS );
    tutLog.memoryLog._( "..." )._( CString.NEW_LINE_CHARS );
    tutLog.memoryLog._( "..." )._( CString.NEW_LINE_CHARS );
    SaveTutorialOutput( "Tut_Instance.txt", tutLog.memoryLog );
    Log.removeLogger( tutLog );
    Log.removeLogger( "CONSOLE" );
}

@Test
public void Tut_Exception()
{
    UT_INIT();

    Log.setVerbosity( tutLog= new MemoryLogger( "Tutlog" ) , Verbosity.WARNING, "/" );
    tutLog.multiLineMsgMode= 4;

    //! [Tut_Exceptions]
    Exception testException=  new Exception( "TestException Message",
                                                new Exception ( "InnerException Message",
                                                                new Exception("Inner, inner Exception") ) );
    LogTools.exception( "MYDOM", Verbosity.WARNING, testException, "Logging an exception: " );
    //! [Tut_Exceptions]

    tutLog.memoryLog.searchAndReplace( "Tutlog", "CONSOLE" );
    SaveTutorialOutput( "Tut_Exceptions.txt", tutLog.memoryLog );

    Log.removeLogger( tutLog );
}

//@Test
//public void Tut_XML()
//{
//    UT_INIT();
//
//    Log.set( tutLog= new MemoryLogger( "Tutlog" ), "/", Verbosity.OFF  );
//    tutLog.rootDomain.setLevel( "/", Verbosity.VERBOSE );
//
//    //! [Tut_XML]
//    String xmltext= "<MainTag>"
//                        +"<SubTag>Hello ALox XML</SubTag>"
//                        +"<SubTag2>"
//                            +"<SubsubTag>A sub tags' string</SubsubTag>"
//                        +"</SubTag2>"
//                    +"</MainTag>";
//    XDocument xdoc= XDocument.Parse( xmltext );
//
//    LogTools.XML("MYDOM", Verbosity.INFO, xdoc, "Logging an xml document: " );
//    //! [Tut_XML]
//
//    tutLog.memoryLog.Replace( "Tutlog", "CONSOLE" );
//    SaveTutorialOutput( "Tut_XML.txt", tutLog.memoryLog );
//}


@Test
public void Tut_LogConfig()
{
    UT_INIT();

    //! [Tut_LogConfig]
    // create two different loggers
    Log.addDebugLogger();
    Log.setVerbosity( new MemoryLogger(),  Verbosity.VERBOSE );

    // reduce meta information to limit tutorial output width
    Log.debugLogger                         .metaInfo.format._()._( "[%tN]%V[%D](%#): " );
    ((MemoryLogger) Log.getLogger("MEMORY")).metaInfo.format._()._( "[%tN]%V[%D](%#): " );
    ((MemoryLogger) Log.getLogger("MEMORY")).multiLineMsgMode= 3;

    // OK, let's use ALox
    Log.setDomain( "PNS"   ,   Scope.PACKAGE, 1 );
    Log.setDomain( "PATH",     Scope.PACKAGE );
    Log.setDomain( "FN",       Scope.CLASS );
    Log.setDomain( "THREAD",   Scope.THREAD_OUTER );

    Log.setVerbosity( "MEMORY",        Verbosity.OFF      , "/CON"    );
    Log.setVerbosity( "DEBUG_LOGGER" , Verbosity.VERBOSE              );
    Log.setVerbosity( "DEBUG_LOGGER" , Verbosity.OFF      , "/MEM"    );
    Log.setVerbosity( "DEBUG_LOGGER" , Verbosity.ERROR    , "/UI"     );
    Log.setVerbosity( "DEBUG_LOGGER" , Verbosity.INFO     , "/UI/DLG" );

    Log.info( "This goes to both loggers" );
    Log.info( "/MEM", "This goes only to the memory logger" );
    Log.info( "/CON", "This goes only to the console logger" );

    Log.once( "Will we see this in the config?" );
    Log.once( "", Verbosity.INFO, "Will we see this in the config?", "ONCEKEY", Scope.CLASS );

    Log.store( new LogData("MyData 1"), Scope.METHOD );
    Log.store( new LogData("MyData 2"), "DataKey", Scope.METHOD );
    Log.store( new LogData("MyData 3"), "DataKey", Scope.CLASS );
    Log.store( new LogData("MyData 4"), "DataKey", Scope.THREAD_OUTER );

    Log.setPrefix( "TPre: "  , Scope.THREAD_OUTER );
    Log.setPrefix( "MPre: "  , Scope.METHOD );
    Log.setPrefix( "DomPre: " );
    Log.setPrefix( "Mouse: ", "/UI/MOUSE" );
    Log.setPrefix( ESC.RED,  "/ERRORS", Inclusion.EXCLUDE );

    Log.mapThreadName( "TUTORIAL" );

    // now, log the current config
    Log.logConfig( null, Verbosity.INFO, "The current configuration of this Lox is:" );
    //! [Tut_LogConfig]

    //tutLog.memoryLog.Replace( "Tutlog", "CONSOLE" );
    SaveTutorialOutput( "Tut_LogConfig.txt", ((MemoryLogger) Log.getLogger( "Memory" )).memoryLog );
    Log.removeLogger( "Memory" );
}

@Test
public void Tut_LogInternalDomains()
{
    UT_INIT();

    //! [Tut_LogInternalDomains]
    // This is the very same code as above...
    Log.addDebugLogger();
    Log.setVerbosity( new MemoryLogger(),  Verbosity.VERBOSE );

    // reduce meta information to limit tutorial output width
    Log.debugLogger                         .metaInfo.format._()._( "[%tN]%V[%D](%#): " );
    ((MemoryLogger) Log.getLogger("MEMORY")).metaInfo.format._()._( "[%tN]%V[%D](%#): " );

    // ... with one difference: we are activating the internal domain
    Log.setVerbosity( ((MemoryLogger) Log.getLogger("MEMORY")), Verbosity.VERBOSE, ALox.INTERNAL_DOMAINS );
    Log.setVerbosity( Log.debugLogger,                          Verbosity.VERBOSE, ALox.INTERNAL_DOMAINS );

    Log.setDomain( "PNS"   ,   Scope.PACKAGE, 1 );
    Log.setDomain( "PATH",     Scope.PACKAGE );
    Log.setDomain( "FN",       Scope.CLASS );
    Log.setDomain( "THREAD",   Scope.THREAD_OUTER );

    Log.setVerbosity( "MEMORY",        Verbosity.OFF      , "/CON"    );
    Log.setVerbosity( "DEBUG_LOGGER" , Verbosity.VERBOSE              );
    Log.setVerbosity( "DEBUG_LOGGER" , Verbosity.OFF      , "/MEM"    );
    Log.setVerbosity( "DEBUG_LOGGER" , Verbosity.ERROR    , "/UI"     );
    Log.setVerbosity( "DEBUG_LOGGER" , Verbosity.INFO     , "/UI/DLG" );

    Log.once( "Will we see this in the config?" );
    Log.once( "", Verbosity.INFO, "Will we see this in the config?", "ONCEKEY", Scope.CLASS );

    Log.store( new LogData("MyData 1"), Scope.METHOD );
    Log.store( new LogData("MyData 2"), "DataKey", Scope.METHOD );
    Log.store( new LogData("MyData 3"), "DataKey", Scope.CLASS );
    Log.store( new LogData("MyData 4"), "DataKey", Scope.THREAD_OUTER );

    Log.setPrefix( "TPre: "  , Scope.THREAD_OUTER );
    Log.setPrefix( "MPre: "  , Scope.METHOD );
    Log.setPrefix( "DomPre: " );
    Log.setPrefix( "Mouse: ", "/UI/MOUSE" );
    Log.setPrefix( ESC.RED,  "/ERRORS", Inclusion.EXCLUDE );

    Log.mapThreadName( "TUTORIAL" );
    //! [Tut_LogInternalDomains]

    SaveTutorialOutput( "Tut_LogInternalDomains.txt", ((MemoryLogger) Log.getLogger( "Memory" )).memoryLog );

    Log.removeLogger( "MEMORY" );
    Log.removeDebugLogger();
}

/** ************************************************************************************************
 * Tut_UsingLogBuffer
 **************************************************************************************************/
@Test
public void Tut_UsingLogBuffer()
{
    UT_INIT();

    Log.setVerbosity( tutLog= new MemoryLogger( "Tutlog" ), Verbosity.VERBOSE, "/" );

    //! [Tut_UsingLogBuffer1]
    //  Create logger and register domain LOGBUF
    Log.addDebugLogger();
    Log.setDomain( "LOGBUF", Scope.METHOD );
    Log.setVerbosity( Log.debugLogger, Verbosity.VERBOSE, "LOGBUF" );

    //  Let's do some logging using the internal buffer singleton;
    Log.info( Log.buf()._( "Hello Buf!. This is only one string. Not useful to use the buf, however..." ) );
    Log.info( Log.buf()._( "This is a 5-digtit rep of 42: " )._( 42, 5 ) );
    Log.info( Log.buf()._( "***All upper case and stars replaced by dollar signs ***" )
                       .toUpper()
                       .searchAndReplaceAll( "*", "$" ) );
    //! [Tut_UsingLogBuffer1]

    //! [Tut_UsingLogBuffer2]
    // using the log buf outside of the <em>Log Statement</em>
    LogBuf logBuf= Log.buf();
    logBuf._( "Lets see if school math is correct: " );
    int a= 4;
    int b= 2;
    if( a/b == 3)
    {
        // shout it out loud!
        logBuf._( "They taught me wrong in school!" );
        Log.error( logBuf );
    }
    else
    {
        // we better say nothing
        Log.bufAbort();
    }
    //! [Tut_UsingLogBuffer2]

    //! [Tut_UsingLogBuffer3]
    // causing trouble
    Log.info( "Let's create an internal error by accessing the buffer twice:" );
    Log.buf();
    Log.buf();
    //! [Tut_UsingLogBuffer3]

    // END OF TUTORIAL
    tutLog.memoryLog.searchAndReplace( "Tutlog", "CONSOLE" );
    SaveTutorialOutput( "Tut_UsingLogBuffer.txt", tutLog.memoryLog );
    Log.removeLogger( tutLog );
}

/** ************************************************************************************************
 * Tut_LogData
 **************************************************************************************************/
@Test
public void Tut_LogData()
{
    UT_INIT();
    Log.addDebugLogger();
    Log.setVerbosity( tutLog= new MemoryLogger( "Tutlog" ), Verbosity.VERBOSE, "/" );

    Log.setVerbosity( Log.debugLogger, Verbosity.VERBOSE, ALox.INTERNAL_DOMAINS );

    // access without prior setting
    {
        SaveTutorialOutput( "Tut_LogData2.txt", tutLog.memoryLog );
        tutLog.memoryLog.clear();
    }

    FileIO fileIo = new FileIO();
    fileIo.Read( "myfile.dat" );

    //! [Tut_LogData_2]
    Log.info( "Working on file version " + Log.retrieve( "FILE_VERSION" ).integerValue );
    //! [Tut_LogData_2]

    SaveTutorialOutput( "Tut_LogData.txt", tutLog.memoryLog );

    Log.removeDebugLogger();
    Log.removeLogger( "MEMORY" );

}

} // class
