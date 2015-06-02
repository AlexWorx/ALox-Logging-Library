// #################################################################################################
//  Unit Tests - ALox Logging Library
//  (Unit Tests to create tutorial sample code and output)
//
//  (c) 2013-2015 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
package unittests.com.aworx.lox;


import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;

import org.junit.Test;




//! [Tut_using_statement]
import com.aworx.lox.*;
import com.aworx.lox.loggers.*;
import com.aworx.lox.tools.LogTools;
//! [Tut_using_statement]
import com.aworx.lox.core.TextLogger;
import com.aworx.util.*;


//! [Tut_Placing_Part2]
class MyClass
{
    // static initializer to register log domains
    static
    {
        Log.regDomain( "MYDOM",            Log.Scope.PACKAGE );
        Log.regDomain( "MYDOM/PERF",    Log.Scope.NONE);
    }

    // Here comes the class
    //...
    //...
}
//! [Tut_Placing_Part2]


/** ************************************************************************************************
*  Implements the tutorial code that with snippets markers for doxygen inclusion.
**************************************************************************************************/
public class Tests_Tutorial
{

MemoryLogger    tutLog;
String          outputPath=        "../../../src/docs/ALox.Java/generated/";

void SaveTutorialOutput( String fileName, AString log )
{
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
public void Tut_Hello_ALox()
{
    Log.reset();
    Log.addLogger( tutLog= new MemoryLogger( "Tutlog" ) );
    tutLog.rootDomain.setLevel( Log.DomainLevel.ALL, false );


    //! [Tut_Hello_ALox]
    //! [Tut_Hello_ALox_Line1]
    Log.addLogger( new ConsoleLogger() );
    //! [Tut_Hello_ALox_Line1]
    //! [Tut_Hello_ALox_Line2]
    Log.setDomain( "APP",    Log.DomainLevel.INFO_WARNINGS_AND_ERRORS );
    //! [Tut_Hello_ALox_Line2]

    //! [Tut_Hello_ALox_Line3]
    Log.info( "APP",    "Hello ALox" );
    //! [Tut_Hello_ALox_Line3]
    //! [Tut_Hello_ALox]

    SaveTutorialOutput( "Tut_Hello_ALox.txt", tutLog.buffer );
}

@Test
public void Tut_LogLevels()
{
    Log.reset();
    Log.addLogger( tutLog= new MemoryLogger( "Tutlog"  ) );
    tutLog.rootDomain.setLevel( Log.DomainLevel.ALL, false );

    //! [Tut_LogLevels]
    Log.addLogger( new ConsoleLogger() );
    //! [Tut_LogLevels_SetDomain]
    Log.setDomain( "APP",    Log.DomainLevel.INFO_WARNINGS_AND_ERRORS );
    //! [Tut_LogLevels_SetDomain]

    Log.error  ( "APP",    "A severe error happened :-(" );
    Log.warning( "APP",    "This is a warning :-/ Maybe an error follows?" );
    Log.info   ( "APP",    "Just for your further information!" );
    Log.verbose( "APP",    "Today, I am in the mood to talk..." );
    //! [Tut_LogLevels]

    SaveTutorialOutput( "Tut_LogLevels.txt", tutLog.buffer );
}

@Test
public void Tut_DefaultDomains()
{
    Log.reset();
    Log.addLogger( tutLog= new MemoryLogger( "Tutlog"  ) );
    tutLog.rootDomain.setLevel( Log.DomainLevel.ALL, false );

    //! [Tut_DefaultDomains]
    Log.addLogger( new ConsoleLogger() );
    Log.regDomain( "APP", Log.Scope.PACKAGE );
    Log.setDomain( "APP", Log.DomainLevel.INFO_WARNINGS_AND_ERRORS );

    Log.error  ( "A severe error happened :-(" );
    Log.warning( "This is a warning :-/ Maybe an error follows?" );
    Log.info   ( "Just for your further information!" );
    Log.verbose( "Today, I am in the mood to talk..." );
    //! [Tut_DefaultDomains]

    SaveTutorialOutput( "Tut_DefaultDomains.txt", tutLog.buffer );

    Log.reset();
    Log.addLogger( tutLog= new MemoryLogger( "Tutlog" ));
    tutLog.rootDomain.setLevel( Log.DomainLevel.ALL, false );

    //! [Tut_DefaultDomains_part2]
    Log.addLogger( new ConsoleLogger() );
    Log.info  ( "APP", "Hallo ALox" );
    //! [Tut_DefaultDomains_part2]

    tutLog.buffer.replace( "Tutlog", "CONSOLE" );
    SaveTutorialOutput( "Tut_DefaultDomains_part2.txt", tutLog.buffer );
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
    Log.addLogger( tutLog= new MemoryLogger( "Tutlog" ), Log.DomainLevel.OFF  );
    Log.setDomain( "MYDOM", Log.DomainLevel.ALL );
    tutLog.rootDomain.setLevel( Log.DomainLevel.ALL, false );
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
        idx= tutLog.buffer.indexOf( AString.NEWLINE, idx + AString.NEWLINE.length() );
        if ( idx < 0 )
            break;
    }
    if (idx > 0)
        tutLog.buffer.setLength( idx + AString.NEWLINE.length() );
    tutLog.buffer.append( "..." ).append( AString.NEWLINE );
    tutLog.buffer.append( "..." ).append( AString.NEWLINE );
    tutLog.buffer.append( "..." ).append( AString.NEWLINE );
    SaveTutorialOutput( "Tut_Instance.txt", tutLog.buffer );
}

@Test
public void Tut_Exception()
{
    Log.reset();
    Log.addLogger( tutLog= new MemoryLogger( "Tutlog" ), Log.DomainLevel.OFF  );
    tutLog.rootDomain.setLevel( Log.DomainLevel.WARNINGS_AND_ERRORS, false );

    //! [Tut_Exceptions]
    Exception testException=  new Exception( "TestException Message",
                                                new Exception ( "InnerException Message",
                                                                new Exception("Inner, inner Exception") ) );
    LogTools.exception( "MYDOM", Log.Level.WARNING, testException, "Logging an exception: " );
    //! [Tut_Exceptions]

    tutLog.buffer.replace( "Tutlog", "CONSOLE" );
    SaveTutorialOutput( "Tut_Exceptions.txt", tutLog.buffer );
}

//@Test
//public void Tut_XML()
//{
//    Log.reset();
//    Log.addLogger( tutLog= new MemoryLogger( "Tutlog" ), Log.DomainLevel.OFF  );
//    tutLog.rootDomain.setLevel( Log.DomainLevel.ALL, false );
//
//    //! [Tut_XML]
//    String xmltext= "<MainTag>"
//                        +"<SubTag>Hallo ALox XML</SubTag>"
//                        +"<SubTag2>"
//                            +"<SubsubTag>A sub tags' string</SubsubTag>"
//                        +"</SubTag2>"
//                    +"</MainTag>";
//    XDocument xdoc= XDocument.Parse( xmltext );
//
//    LogTools.XML("MYDOM", Log.Level.INFO, xdoc, "Logging an xml document: " );
//    //! [Tut_XML]
//
//    tutLog.buffer.Replace( "Tutlog", "CONSOLE" );
//    SaveTutorialOutput( "Tut_XML.txt", tutLog.buffer );
//}


@Test
public void Tut_SeparatedLogLevels()
{
    Log.reset();
    Log.addLogger( tutLog= new MemoryLogger( "Tutlog" ), Log.DomainLevel.OFF  );
    Log.setDomain( "MYDOM", Log.DomainLevel.ALL );
    tutLog.rootDomain.setLevel( Log.DomainLevel.OFF, false );
    tutLog.multiLineMsgMode= 4;
    tutLog.lineFormatter.format.clear().append( "%L [%O]: ");

    Log.setDomain( "DOM",  Log.DomainLevel.ALL );
    Log.setDomain( "DOM/CON", Log.DomainLevel.ALL, false, "Tutlog" );
    Log.setDomain( "DOM/MEM", Log.DomainLevel.OFF, false, "Tutlog" );


    //! [Tut_SeparatedLogLevels]
    // create two different loggers
    Log.addLogger( new ConsoleLogger( "MyConsoleLogger" ) );
    Log.addLogger( new MemoryLogger ( "MyMemoryLogger" ) );

    // reduce meta information to limit tutorial output width
    ((TextLogger) Log.getLogger("MyConsoleLogger")).lineFormatter.format.clear().append( " %L [%O]: ");
    ((TextLogger) Log.getLogger("MyMemoryLogger" )).lineFormatter.format.clear().append( " %L [%O]: ");

    // register domains, set DOM as default
    Log.regDomain( "DOM",     Log.Scope.METHOD );
    Log.regDomain( "DOM/CON", Log.Scope.NONE );
    Log.regDomain( "DOM/MEM", Log.Scope.NONE );

    // set level of DOM for all loggers
    Log.setDomain( "DOM",  Log.DomainLevel.ALL, false );

    // set level of DOM/CON separately for console and memory logger
    Log.setDomain( "~CON", Log.DomainLevel.ALL, false, "MyConsoleLogger" );
    Log.setDomain( "~CON", Log.DomainLevel.OFF, false, "MyMemoryLogger"  );

    // set level of DOM/MEM separately for console and memory logger
    Log.setDomain( "~MEM", Log.DomainLevel.OFF, false, "MyConsoleLogger" );
    Log.setDomain( "~MEM", Log.DomainLevel.ALL, false, "MyMemoryLogger"  );

    // Log info to each of the domains
    Log.info(         "Domain= DOM      -> This goes to all loggers");
    Log.info( "~CON", "Domain= DOM/CON  -> This goes to ConsoleLogger exclusively");
    Log.info( "~MEM", "Domain= DOM/MEM  -> This goes to MemoryLogger exclusively");

    // To verify the result, we log the contents of the MemoryLogger to the console logger
    Log.info( "~CON", "Here comes the contents of MemoryLogger:");
    Log.info( "~CON", ((MemoryLogger) Log.getLogger("MyMemoryLogger")).buffer.toString(), 1);
    //! [Tut_SeparatedLogLevels]

    tutLog.buffer.replace( "Tutlog", "MyConsoleLogger" );
    SaveTutorialOutput( "Tut_SeparatedLogLevels.txt", tutLog.buffer );
}


@Test
public void Tut_LogConfig()
{
    Log.reset();

    //! [Tut_LogConfig]
    // create two different loggers
    Log.addLogger( new ConsoleLogger() );
    Log.addLogger( new MemoryLogger () );

    // reduce meta information to limit tutorial output width
    ((TextLogger) Log.getLogger("Console")).lineFormatter.format.clear().append( " %L [%O]: ");
    ((TextLogger) Log.getLogger("Memory" )).lineFormatter.format.clear().append( " %L [%O]: ");

    // register domains, set DOM as default
    Log.regDomain( "DOM",     Log.Scope.METHOD );
    Log.regDomain( "DOM/CON", Log.Scope.NONE );
    Log.regDomain( "DOM/MEM", Log.Scope.NONE );

    // set level of DOM for all loggers
    Log.setDomain( "DOM", Log.DomainLevel.ALL );

    // set level of DOM/CON separately for console and memory logger
    Log.setDomain( "~CON", Log.DomainLevel.ALL, false, "Console" );
    Log.setDomain( "~CON", Log.DomainLevel.OFF, false, "Memory"  );

    // set level of DOM/MEM separately for console and memory logger
    Log.setDomain( "~MEM", Log.DomainLevel.OFF, false, "Console" );
    Log.setDomain( "~MEM", Log.DomainLevel.ALL, false, "Memory"  );

    // Log current Log configuration
    Log.logConfig( "DOM", Log.Level.VERBOSE, "Here comes the current Log configuration:" );
    //! [Tut_LogConfig]

    //tutLog.buffer.Replace( "Tutlog", "CONSOLE" );
    SaveTutorialOutput( "Tut_LogConfig.txt", ((MemoryLogger) Log.getLogger( "Memory" )).buffer );
}



@Test
public void Tut_LogConfig2()
{
    Log.reset();

    // ##### code inclusion version ########
    //! [Tut_LogConfig2]
    // create two different loggers, add console Logger verbosely
    Log.addLogger( new ConsoleLogger(), Log.DomainLevel.ALL );
    Log.addLogger( new MemoryLogger () );

    // register domains, set DOM as default
    Log.regDomain( "DOM",     Log.Scope.METHOD );
    Log.regDomain( "DOM/CON", Log.Scope.NONE );
    Log.regDomain( "DOM/MEM", Log.Scope.NONE );

    // set level of DOM for all loggers
    Log.setDomain( "DOM", Log.DomainLevel.ALL );

    // set level of DOM/CON separately for console and memory logger
    Log.setDomain( "~CON", Log.DomainLevel.ALL, false, "Console" );
    Log.setDomain( "~CON", Log.DomainLevel.OFF, false, "Memory"  );

    // set level of DOM/MEM separately for console and memory logger
    Log.setDomain( "~MEM", Log.DomainLevel.OFF, false, "Console" );
    Log.setDomain( "~MEM", Log.DomainLevel.ALL, false, "Memory"  );

    //! [Tut_LogConfig2]

    // ##### output generation version - the only difference is that memory logger gets all messages ########
    Log.reset();

    // create two different loggers, add console Logger verbosely
    tutLog= new MemoryLogger ( "CONSOLE" );
    tutLog.rootDomain.setLevel( Log.DomainLevel.ALL, false );
    Log.addLogger( tutLog, Log.DomainLevel.ALL );
    Log.addLogger( new ConsoleLogger( "MEMORY" ) );

    // register domains, set DOM as default
    Log.regDomain( "DOM",     Log.Scope.METHOD );
    Log.regDomain( "DOM/CON", Log.Scope.NONE );
    Log.regDomain( "DOM/MEM", Log.Scope.NONE );

    // set level of DOM for all loggers
    Log.setDomain( "DOM", Log.DomainLevel.ALL );

    // set level of DOM/CON separately for console and memory logger
    Log.setDomain( "~CON", Log.DomainLevel.ALL, false, "Console" );
    Log.setDomain( "~CON", Log.DomainLevel.OFF, false, "Memory"  );

    // set level of DOM/MEM separately for console and memory logger
    Log.setDomain( "~MEM", Log.DomainLevel.OFF, false, "Console" );
    Log.setDomain( "~MEM", Log.DomainLevel.ALL, false, "Memory"  );

    //tutLog.buffer.Replace( "Tutlog", "CONSOLE" );
    SaveTutorialOutput( "Tut_LogConfig2.txt", ((MemoryLogger) Log.getLogger( "Console" )).buffer );


    //! [Tut_LogConfig3]
    Log.setDomain( "ALOX", Log.DomainLevel.ALL, true, "Console");
    //! [Tut_LogConfig3]

    //! [Tut_LogConfig4]
    Log.setDomain( Log.LOX.internalDomain, Log.DomainLevel.ALL, true, "Console");
    //! [Tut_LogConfig4]
}
/** ************************************************************************************************
    * <summary>    Tut_UsingLogBuffer </summary>
    **************************************************************************************************/
@Test
public void Tut_UsingLogBuffer()
{
    Log.reset();
    Log.addLogger( tutLog= new MemoryLogger( "Tutlog" ), Log.DomainLevel.OFF  );
    tutLog.rootDomain.setLevel( Log.DomainLevel.ALL, false );

    //! [Tut_UsingLogBuffer1]
    //  Create logger and register domain LOGBUF
    Log.addLogger( new ConsoleLogger(), Log.DomainLevel.WARNINGS_AND_ERRORS );
    Log.regDomain( "LOGBUF", Log.Scope.METHOD );
    Log.setDomain( "LOGBUF", Log.DomainLevel.ALL );

    //  Let's do some logging using the internal buffer singleton;
    Log.info( Log.buf().append( "Hallo Buf!. This is only one string. Not useful to use the buf, however..." ) );
    Log.info( Log.buf().append( "This is a 5-digtit rep of 42: " ).append( 42, 5 ) );
    Log.info( Log.buf().append( "***All upper case and stars replaced by dollar signs ***" ).convertCase( true ).replace( "*", "$" ) );
    //! [Tut_UsingLogBuffer1]

    //! [Tut_UsingLogBuffer2]
    // using the log buf outside of the log statement
    LogBuf logBuf= Log.buf();
    logBuf.append( "Lets see if school math is correct: " );
    int a= 4;
    int b= 2;
    if( a/b == 3)
    {
        // shout it out loud!
        logBuf.append( "They taught me wrong in school!" );
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
    tutLog.buffer.replace( "Tutlog", "CONSOLE" );
    SaveTutorialOutput( "Tut_UsingLogBuffer.txt", tutLog.buffer );
}


} // class
