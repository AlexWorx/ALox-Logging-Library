// #################################################################################################
//  Unit Tests - AWorx Library
//  (Tests to create tutorial sample code and output)
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
package ut_com_aworx_lox;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;

import org.junit.Test;

import ut_com_aworx_uttools.UnitTestSampleWriter;

//! [Tut_using_statement]
import com.aworx.lib.enums.*;
import com.aworx.lib.strings.*;
import com.aworx.lox.*;
import com.aworx.lox.loggers.*;
import com.aworx.lox.core.textlogger.*;
import com.aworx.lox.tools.LogTools;
//! [Tut_using_statement]



/** ************************************************************************************************
*  Implements the tutorial code that with snippets markers for doxygen inclusion.
**************************************************************************************************/
public class UT_alox_tutorial
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
    (new HelloALox()).sayHello();
}

@Test
public void Tut_Hello_ALox()
{
    Log.reset();
    Log.addLogger( tutLog= new MemoryLogger( "Tutlog" ) );


    //! [Tut_Hello_ALox]
    //! [Tut_Hello_ALox_Line1]
    Log.addDebugLogger();
    //! [Tut_Hello_ALox_Line1]
    //! [Tut_Hello_ALox_Line2]
    Log.setDomain( "APP", Log.DomainLevel.INFO_WARNINGS_AND_ERRORS );
    //! [Tut_Hello_ALox_Line2]

    //! [Tut_Hello_ALox_Line3]
    Log.info( "APP",    "Hello ALox" );
    //! [Tut_Hello_ALox_Line3]
    //! [Tut_Hello_ALox]

    SaveTutorialOutput( "Tut_Hello_ALox.txt", tutLog.memoryLog );
}

@Test
public void Tut_LogLevels()
{
    Log.reset();
    Log.addLogger( tutLog= new MemoryLogger( "Tutlog"  ) );

    //! [Tut_LogLevels]
    Log.addDebugLogger();
    //! [Tut_LogLevels_SetDomain]
    Log.setDomain( "APP", Log.DomainLevel.INFO_WARNINGS_AND_ERRORS );
    //! [Tut_LogLevels_SetDomain]

    Log.error  ( "APP",    "A severe error happened :-(" );
    Log.warning( "APP",    "This is a warning :-/ Maybe an error follows?" );
    Log.info   ( "APP",    "Just for your further information!" );
    Log.verbose( "APP",    "Today, I am in the mood to talk..." );
    //! [Tut_LogLevels]

    SaveTutorialOutput( "Tut_LogLevels.txt", tutLog.memoryLog );
}

@Test
public void Tut_DefaultDomains()
{
    Log.reset();
    Log.addLogger( tutLog= new MemoryLogger( "Tutlog"  ) );

    //! [Tut_DefaultDomains]
    Log.addLogger( new ConsoleLogger() );
    Log.setDomain( "APP", Log.Scope.PACKAGE );
    Log.setDomain( "APP", Log.DomainLevel.INFO_WARNINGS_AND_ERRORS );

    Log.error  ( "A severe error happened :-(" );
    Log.warning( "This is a warning :-/ Maybe an error follows?" );
    Log.info   ( "Just for your further information!" );
    Log.verbose( "Today, I am in the mood to talk..." );
    //! [Tut_DefaultDomains]

    SaveTutorialOutput( "Tut_DefaultDomains.txt", tutLog.memoryLog );

    Log.reset();
    Log.addLogger( tutLog= new MemoryLogger( "Tutlog" ));
    tutLog.rootDomain.setLevel( Log.DomainLevel.ALL, Propagation.NONE );
    tutLog.setDomain( Log.LOX.internalDomain, Log.DomainLevel.WARNINGS_AND_ERRORS );

    //! [Tut_DefaultDomains_part2]
    Log.info  ( "APP", "Hello ALox" );
    //! [Tut_DefaultDomains_part2]

    tutLog.memoryLog.searchAndReplace( "Tutlog", "CONSOLE" );
    SaveTutorialOutput( "Tut_DefaultDomains_part2.txt", tutLog.memoryLog );
}

public void Tut_Placing()
{
    //! [Tut_Placing_Part1]
    Log.addLogger( new ConsoleLogger() );

    Log.setDomain( "MYAPP",     Log.DomainLevel.ALL);
    Log.setDomain( "SOCKETS",   Log.DomainLevel.WARNINGS_AND_ERRORS );
    Log.setDomain( "UI",        Log.DomainLevel.ERRORS );
    Log.setDomain( "UI/DLGS",   Log.DomainLevel.INFO_WARNINGS_AND_ERRORS );
    Log.setDomain( "3DCALC",    Log.DomainLevel.OFF  );
    //! [Tut_Placing_Part1]

    //! [Tut_Placing_Part3]
    Log.info( "MYDOM/PERF", "Heavy calculation started..." );
        heavyCalculation();
    Log.info( "MYDOM/PERF", "Heavy calculation finished!" );
    //! [Tut_Placing_Part3]

    //! [Tut_Placing_Part3b]
    Log.info( "~PERF", "Heavy calculation started..." );
        heavyCalculation();
    Log.info( "~PERF", "Heavy calculation finished!" );
    //! [Tut_Placing_Part3b]
}
void heavyCalculation() {}

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
}
private void process(@SuppressWarnings ("unused") int i) {}

@Test
public void Tut_Instance()
{
    Log.reset();
    Log.addLogger( new ConsoleLogger() );
    Log.addLogger( tutLog= new MemoryLogger( "Tutlog" )  );
    Log.setDomain( "MYDOM", Log.DomainLevel.ALL );
    tutLog.rootDomain.setLevel( Log.DomainLevel.ALL, Propagation.NONE );
    tutLog.multiLineMsgMode= 4;

    //! [Tut_Instance]
    // Log multi-lines without indent
    ((TextLogger) Log.getLogger( "Console" )).multiLineMsgMode= 4;

    // Log current thread instance
    LogTools.instance( "MYDOM", Log.Level.INFO, Thread.currentThread(), 2, "Actual Thread: ", 1 );
    //! [Tut_Instance]

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
}

@Test
public void Tut_Exception()
{
    Log.reset();
    Log.addLogger( tutLog= new MemoryLogger( "Tutlog" ) );
    tutLog.rootDomain.setLevel( Log.DomainLevel.WARNINGS_AND_ERRORS, Propagation.NONE );

    //! [Tut_Exceptions]
    Exception testException=  new Exception( "TestException Message",
                                                new Exception ( "InnerException Message",
                                                                new Exception("Inner, inner Exception") ) );
    LogTools.exception( "MYDOM", Log.Level.WARNING, testException, "Logging an exception: " );
    //! [Tut_Exceptions]

    tutLog.memoryLog.searchAndReplace( "Tutlog", "CONSOLE" );
    SaveTutorialOutput( "Tut_Exceptions.txt", tutLog.memoryLog );
}

//@Test
//public void Tut_XML()
//{
//    Log.reset();
//    Log.addLogger( tutLog= new MemoryLogger( "Tutlog" ), Log.DomainLevel.OFF  );
//    tutLog.rootDomain.setLevel( Log.DomainLevel.ALL, Propagation.NONE );
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
//    LogTools.XML("MYDOM", Log.Level.INFO, xdoc, "Logging an xml document: " );
//    //! [Tut_XML]
//
//    tutLog.memoryLog.Replace( "Tutlog", "CONSOLE" );
//    SaveTutorialOutput( "Tut_XML.txt", tutLog.memoryLog );
//}


@Test
public void Tut_SeparatedLogLevels()
{
    Log.reset();
    Log.addLogger( tutLog= new MemoryLogger( "Tutlog" )  );
    Log.setDomain( "MYDOM", Log.DomainLevel.ALL );
    tutLog.rootDomain.setLevel( Log.DomainLevel.OFF, Propagation.NONE );
    tutLog.multiLineMsgMode= 4;
    tutLog.metaInfo.format.clear()._( "%L [%O]: ");

    Log.setDomain( "DOM",  Log.DomainLevel.ALL );
    Log.setDomain( "DOM/CON", Log.DomainLevel.ALL, "Tutlog" );
    Log.setDomain( "DOM/MEM", Log.DomainLevel.OFF, "Tutlog" );


    //! [Tut_SeparatedLogLevels]
    // create two different loggers
    Log.addLogger( new ConsoleLogger( "MyConsoleLogger" ) );
    Log.addLogger( new MemoryLogger ( "MyMemoryLogger" ) );

    // reduce meta information to limit tutorial output width
    ((TextLogger) Log.getLogger("MyConsoleLogger")).metaInfo.format.clear()._( " %L [%O]: ");
    ((TextLogger) Log.getLogger("MyMemoryLogger" )).metaInfo.format.clear()._( " %L [%O]: ");

    // register domains, set DOM as default
    Log.setDomain( "DOM",     Log.Scope.METHOD );
    Log.setDomain( "DOM/CON", Log.Scope.NONE );
    Log.setDomain( "DOM/MEM", Log.Scope.NONE );

    // set level of DOM for all loggers
    Log.setDomain( "DOM",  Log.DomainLevel.ALL );

    // set level of DOM/CON separately for console and memory logger
    Log.setDomain( "~CON", Log.DomainLevel.ALL, "MyConsoleLogger" );
    Log.setDomain( "~CON", Log.DomainLevel.OFF, "MyMemoryLogger"  );

    // set level of DOM/MEM separately for console and memory logger
    Log.setDomain( "~MEM", Log.DomainLevel.OFF, "MyConsoleLogger" );
    Log.setDomain( "~MEM", Log.DomainLevel.ALL, "MyMemoryLogger"  );

    // Log info to each of the domains
    Log.info(         "Domain= DOM      -> This goes to all loggers");
    Log.info( "~CON", "Domain= DOM/CON  -> This goes to ConsoleLogger exclusively");
    Log.info( "~MEM", "Domain= DOM/MEM  -> This goes to MemoryLogger exclusively");

    // To verify the result, we log the contents of the MemoryLogger to the console logger
    Log.info( "~CON", "Here comes the contents of MemoryLogger:");
    Log.info( "~CON", ((MemoryLogger) Log.getLogger("MyMemoryLogger")).memoryLog.toString(), 1);
    //! [Tut_SeparatedLogLevels]

    tutLog.memoryLog.searchAndReplace( "Tutlog", "MyConsoleLogger" );
    SaveTutorialOutput( "Tut_SeparatedLogLevels.txt", tutLog.memoryLog );
}


@Test
public void Tut_LogConfig()
{
    Log.reset();

    //! [Tut_LogConfig]
    // create two different loggers
    Log.addDebugLogger();
    Log.addLogger( new MemoryLogger () );

    // reduce meta information to limit tutorial output width
    ((TextLogger) Log.getLogger("DEBUG_LOGGER")).metaInfo.format.clear()._( "[%t]%L[%O](%#): " );
    ((TextLogger) Log.getLogger("Memory" )).metaInfo.format.clear()._( "[%t]%L[%O](%#): " );

    // Our previous sample
    Log.setDomain( "DOM",     Log.Scope.METHOD );
    Log.setDomain( "DOM/CON", Log.Scope.NONE );
    Log.setDomain( "DOM/MEM", Log.Scope.NONE );
    Log.setDomain( "DOM",  Log.DomainLevel.ALL );
    Log.setDomain( "~CON", Log.DomainLevel.ALL, "Console" );
    Log.setDomain( "~CON", Log.DomainLevel.OFF, "Memory"  );
    Log.setDomain( "~MEM", Log.DomainLevel.OFF, "Console" );
    Log.setDomain( "~MEM", Log.DomainLevel.ALL, "Memory"  );
    Log.mapThreadName( "Thread1" );

    // Log current Log configuration
    Log.logConfig( "DOM", Log.Level.VERBOSE, "Here comes the current Log configuration:" );
    //! [Tut_LogConfig]

    //tutLog.memoryLog.Replace( "Tutlog", "CONSOLE" );
    SaveTutorialOutput( "Tut_LogConfig.txt", ((MemoryLogger) Log.getLogger( "Memory" )).memoryLog );
}

@Test
public void Tut_LogConfig2()
{
    Log.reset();

    // ##### code inclusion version ########
    //! [Tut_LogConfig2]
    // change internal domain ("ALOX") to level 'All'
    Log.addDebugLogger();
    Log.setDomain( "ALOX",  Log.DomainLevel.ALL );

    // Our previous sample
    Log.addLogger( new MemoryLogger () );
                  Log.debugLogger          .metaInfo.format.clear()._( "[%t]%L[%O](%#): " );
    ((TextLogger) Log.getLogger("Memory" )).metaInfo.format.clear()._( "[%t]%L[%O](%#): " );
    Log.setDomain( "DOM",     Log.Scope.METHOD );
    Log.setDomain( "DOM/CON", Log.Scope.NONE );
    Log.setDomain( "DOM/MEM", Log.Scope.NONE );
    Log.setDomain( "DOM",  Log.DomainLevel.ALL );
    Log.setDomain( "~CON", Log.DomainLevel.ALL, "Console" );
    Log.setDomain( "~CON", Log.DomainLevel.OFF, "Memory"  );
    Log.setDomain( "~MEM", Log.DomainLevel.OFF, "Console" );
    Log.setDomain( "~MEM", Log.DomainLevel.ALL, "Memory"  );
    Log.mapThreadName( "Thread1" );

    //! [Tut_LogConfig2]

    // ##### output generation version - the only difference is that memory logger gets all messages ########
    Log.reset();

    // create two different loggers
    tutLog= new MemoryLogger ( "CONSOLE" );
    tutLog     .metaInfo.format.clear()._( "[%t]%L[%O](%#): " );
    tutLog.rootDomain.setLevel( Log.DomainLevel.ALL, Propagation.NONE );
    Log.addLogger( tutLog);
    Log.setDomain( "ALOX",  Log.DomainLevel.ALL );

    // Our previous sample
    Log.addLogger( new ConsoleLogger( "MEMORY" ) );
    ((TextLogger) Log.getLogger("Memory" )).metaInfo.format.clear()._( "[%t]%L[%O](%#): " );
    Log.setDomain( "DOM",     Log.Scope.METHOD );
    Log.setDomain( "DOM/CON", Log.Scope.NONE );
    Log.setDomain( "DOM/MEM", Log.Scope.NONE );
    Log.setDomain( "DOM",  Log.DomainLevel.ALL );
    Log.setDomain( "~CON", Log.DomainLevel.ALL, "Console" );
    Log.setDomain( "~CON", Log.DomainLevel.OFF, "Memory"  );
    Log.setDomain( "~MEM", Log.DomainLevel.OFF, "Console" );
    Log.setDomain( "~MEM", Log.DomainLevel.ALL, "Memory"  );
    Log.mapThreadName( "Thread1" );

    tutLog.memoryLog.searchAndReplace( " (CONSOLE)", "" );

    SaveTutorialOutput( "Tut_LogConfig2.txt", ((MemoryLogger) Log.getLogger( "Console" )).memoryLog );


    //! [Tut_LogConfig3]
    Log.setDomain( "ALOX", Log.DomainLevel.ALL, "Console");
    //! [Tut_LogConfig3]

    //! [Tut_LogConfig4]
    Log.setDomain( Log.LOX.internalDomain, Log.DomainLevel.ALL, "Console");
    //! [Tut_LogConfig4]
}
/** ************************************************************************************************
    * Tut_UsingLogBuffer
    **************************************************************************************************/
@Test
public void Tut_UsingLogBuffer()
{
    Log.reset();
    Log.addLogger( tutLog= new MemoryLogger( "Tutlog" ) );
    tutLog.rootDomain.setLevel( Log.DomainLevel.ALL, Propagation.NONE );
    tutLog.setDomain( Log.LOX.internalDomain, Log.DomainLevel.ERRORS );

    //! [Tut_UsingLogBuffer1]
    //  Create logger and register domain LOGBUF
    Log.addDebugLogger();
    Log.setDomain( "LOGBUF", Log.Scope.METHOD );
    Log.setDomain( "LOGBUF", Log.DomainLevel.ALL );

    //  Let's do some logging using the internal buffer singleton;
    Log.info( Log.buf()._( "Hello Buf!. This is only one string. Not useful to use the buf, however..." ) );
    Log.info( Log.buf()._( "This is a 5-digtit rep of 42: " )._( 42, 5 ) );
    Log.info( Log.buf()._( "***All upper case and stars replaced by dollar signs ***" )
                       .toUpper()
                       .searchAndReplaceAll( "*", "$" ) );
    //! [Tut_UsingLogBuffer1]

    //! [Tut_UsingLogBuffer2]
    // using the log buf outside of the log statement
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
}


} // class
