// #################################################################################################
//  Unit Tests - AWorx Library
//  (Tests to create tutorial sample code and output)
//
//  Copyright 2013-2019 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
package ut_alox;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;

import org.junit.Test;

import com.aworx.lib.lang.Inclusion;

//! [Tut_using_statement]
import com.aworx.lib.strings.*;
import com.aworx.lox.Verbosity;
import com.aworx.lox.Scope;
import com.aworx.lox.Log;
import com.aworx.lox.ESC;
import com.aworx.lox.ALox;
import com.aworx.lox.detail.textlogger.*;
import com.aworx.lox.loggers.*;
import com.aworx.lox.tools.*;
//! [Tut_using_statement]

import ut_com_aworx.AWorxUnitTesting;
import ut_com_aworx.UTSampleWriter;


// #################################################################################################
// Tut_ScopeDomains
// #################################################################################################
class TutScopeDom
{
    @SuppressWarnings ("static-method")
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
    String fileName;
    public Zipper( String fileName )
    {
        Log.setDomain( "ZIP", Scope.CLASS ); // set Scope Domain path for this class
        //...
        this.fileName= fileName;

        Log.info( "Zipper created" ); // domain "ZIP"
        //...
    }

    public char[] Compress( char[] buffer )
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

    public char[] Extract( char[] buffer )
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
@SuppressWarnings ("static-method")
//! [Tut_LogData]
class FileIO
{
    public void Read(String fileName )
    {
        Log.setDomain( "READ", Scope.METHOD );
        Log.info( "Reading " + fileName );

        String fileVersion;
        //...
        //...
        // Identified file version
        fileVersion= "3.1";

        Log.store( fileVersion, "FILE_VERSION" );

        //...
        //...
        Log.info( "Success" );
    }
}
//! [Tut_LogData]

/** ************************************************************************************************
*  Implements the tutorial code that with snippets markers for doxygen inclusion.
**************************************************************************************************/
public class UT_dox_tutorial  extends AWorxUnitTesting
{

MemoryLogger    tutLog;
String          outputPath=        UTSampleWriter.getGeneratedSamplesDir();

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
       try  { if ( writer != null ) writer.close(); }   catch (@SuppressWarnings ("unused") Exception e) {/* void */}
    }
}

@Test
public void Tut_Hello_ALox_Minimum()
{
    UT_INIT();

    HelloALox.sayHello();
}

@Test
public void Tut_Hello_ALox()
{
    UT_INIT();

    //! [Tut_ALox_Logger_1]
    Log.addDebugLogger();
    //! [Tut_ALox_Logger_1]

    Log.removeDebugLogger();
    Log.setVerbosity( tutLog= new MemoryLogger( "Tutlog" ), Verbosity.VERBOSE );

    //! [Tut_ALox_Logger_2]
    Log.addDebugLogger();
    //! [Tut_Hello_ALox]
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
        Zipper zip= new Zipper( "myfile.zip" );
        zip.Compress( null );
        zip.Extract( null );
        tutLog.memoryLog.clear(); tutLog.cntLogs= 0;
    }
    // ...and again
    {
        Zipper zip= new Zipper( "myfile.zip" );
        zip.Compress(  null );
        zip.Extract( null );
    }

    SaveTutorialOutput( "Tut_ScopeDomains_Zipper.txt", tutLog.memoryLog );

    //---------- with scope path ---------------

    //! [Tut_ScopeDomains_Path]
    Log.setDomain( "UTIL", Scope.PACKAGE );
    //! [Tut_ScopeDomains_Path]

    tutLog.memoryLog.clear(); tutLog.cntLogs= 0;
    // do it once to set the tab positions of the meta info...
    {
        Zipper zip= new Zipper( "myfile.zip" );
        zip.Compress( null );
        zip.Extract( null );
        tutLog.memoryLog.clear(); tutLog.cntLogs= 0;
    }
    // ...and again
    {
        Zipper zip= new Zipper( "myfile.zip" );
        zip.Compress( null );
        zip.Extract(  null );
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

private void process(@SuppressWarnings ("unused") int i) {/* void */}

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
public void Tut_LogState()
{
    UT_INIT();

    //! [Tut_LogState]
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

    Log.store( "MyData 1",            Scope.METHOD );
    Log.store( "MyData 2", "DataKey", Scope.METHOD );
    Log.store( "MyData 3", "DataKey", Scope.CLASS );
    Log.store( "MyData 4", "DataKey", Scope.THREAD_OUTER );

    Log.setPrefix( "TPre: "  , Scope.THREAD_OUTER );
    Log.setPrefix( "MPre: "  , Scope.METHOD );
    Log.setPrefix( "DomPre: " );
    Log.setPrefix( "Mouse: ", "/UI/MOUSE" );
    Log.setPrefix( ESC.RED,  "/ERRORS", Inclusion.EXCLUDE );

    Log.mapThreadName( "TUTORIAL" );

    // now, log the current config
    Log.state( null, Verbosity.INFO, "The current configuration of this Lox is:" );
    //! [Tut_LogState]

    //tutLog.memoryLog.Replace( "Tutlog", "CONSOLE" );
    SaveTutorialOutput( "Tut_LogState.txt", ((MemoryLogger) Log.getLogger( "Memory" )).memoryLog );
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
    Log.setVerbosity( Log.getLogger("MEMORY"),     Verbosity.VERBOSE, ALox.INTERNAL_DOMAINS );
    Log.setVerbosity( Log.debugLogger,             Verbosity.VERBOSE, ALox.INTERNAL_DOMAINS );

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

    Log.store( "MyData 1",            Scope.METHOD );
    Log.store( "MyData 2", "DataKey", Scope.METHOD );
    Log.store( "MyData 3", "DataKey", Scope.CLASS );
    Log.store( "MyData 4", "DataKey", Scope.THREAD_OUTER );

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
        Log.info( "Working on file version {!Q}", Log.retrieve( "FILE_VERSION" ) );
        SaveTutorialOutput( "Tut_LogData2.txt", tutLog.memoryLog );
        tutLog.memoryLog.clear();
    }

    FileIO fileIo = new FileIO();
    fileIo.Read( "myfile.dat" );

    //! [Tut_LogData_2]
    Log.info( "Working on file version {!Q}", Log.retrieve( "FILE_VERSION" ) );
    //! [Tut_LogData_2]

    SaveTutorialOutput( "Tut_LogData.txt", tutLog.memoryLog );

    Log.removeDebugLogger();
    Log.removeLogger( "MEMORY" );

}

/** ************************************************************************************************
 * Tut_Format
 **************************************************************************************************/
@Test
public void Tut_Format()
{
    UT_INIT();
    Log.addDebugLogger();
    Log.setVerbosity( tutLog= new MemoryLogger( "Tutlog" ), Verbosity.VERBOSE );

    Log.setVerbosity( Log.debugLogger, Verbosity.VERBOSE, ALox.INTERNAL_DOMAINS );


    //! [Tut_Format_1]
    Log.info( "Value=", 5 );
    //! [Tut_Format_1]
    SaveTutorialOutput( "Tut_Format_1.txt", tutLog.memoryLog );


    //! [Tut_Format_P]
    Log.info( "Value={}", 5 );
    //! [Tut_Format_P]

    //! [Tut_Format_J]
    Log.info( "Value=%s", 5 );
    //! [Tut_Format_J]


    //! [Tut_Format_Multi]
    Log.info( "One-", "Two-", "Three" );
    Log.info( "{}-{}-{}", "One", "Two", "Three" );
    Log.info( "{}-{}-"  , "One", "Two", "Three" );
    Log.info( "{}-"  , "One", "{}-", "Two", "{}", "Three" );
    //! [Tut_Format_Multi]

    tutLog.memoryLog.clear();
    //! [Tut_Format_Mix]
    Log.info( "Python Style: {!s}","PS", " - ", "Java Style: \"%s\"", "JS" );
    //! [Tut_Format_Mix]
    SaveTutorialOutput( "Tut_Format_Mix.txt", tutLog.memoryLog );

    tutLog.memoryLog.clear();
    //! [Tut_Format_Sample_1]
    Log.info( ">{:<10}<" , "left" );
    Log.info( ">{:>10}<" , "right" );
    Log.info( ">{:^10}<" , "center" );
    Log.info( ">{:10.3}<", 12.3456789 );

    Log.info( "Tab:{!Tab12}", "Stop" );

    Log.info( "Auto Tab:{!ATab}", "Stop" );
    Log.info( "Auto Tab XXX:{!ATab}", "Stop" );
    Log.info( "Auto Tab:{!ATab}", "Stop" );

    Log.info( "A quoted {!Q} string", "Placeholder" );
    Log.info( "A quoted {!Q} number", 395 );

    Log.info( "Upper {0!Q!up} and lower {0!Q!lo} conversion", "CaSe" );

    Log.info( "Hex: {:#x}. With group chars: {0:x,}", 0x11FF22EE );
    Log.info( "Oct: {:#o}. With group chars: {0:o,}", 012345670 );
    Log.info( "Bin: {:#b}. With group chars: {0:b,}", 145 );
    //! [Tut_Format_Sample_1]
    SaveTutorialOutput( "Tut_Format_Sample_1.txt", tutLog.memoryLog );

    Log.removeDebugLogger();
    Log.removeLogger( "MEMORY" );
}

} // class
