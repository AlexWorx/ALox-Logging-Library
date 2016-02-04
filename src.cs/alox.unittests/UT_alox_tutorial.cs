// #################################################################################################
//  cs.aworx.lox.unittests - ALox Logging Library
//  (Unit Tests to create tutorial sample code and output)
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
using System;
using System.IO;
using System.Threading;
using System.Xml.Linq;
using ut_cs_aworx;

#if ALIB_MONO_DEVELOP
    using NUnit.Framework;
#endif
#if ALIB_VSTUDIO
    using Microsoft.VisualStudio.TestTools.UnitTesting;
#endif


//! [Tut_using_statement]
using cs.aworx.lib;
using cs.aworx.lib.enums;
using cs.aworx.lib.strings;
using cs.aworx.lox;
using cs.aworx.lox.core.textlogger;
using cs.aworx.lox.loggers;
using cs.aworx.lox.tools;
//! [Tut_using_statement]

namespace ut_cs_aworx_lox
{

/** ************************************************************************************************
*
*  Implements the tutorial code that with snippets markers for doxygen inclusion.
*
**************************************************************************************************/
#if ALOX_DBG_LOG


#if ALIB_MONO_DEVELOP
    [TestFixture ()]
#endif
#if ALIB_VSTUDIO
    [TestClass]
#endif

public class CS_Tutorial   : UnitTest
{
    MemoryLogger    tutLog;
    String          outputPath=        UnitTestSampleWriter.GetGeneratedSamplesDir();

    void SaveTutorialOutput( string fileName, AString log )
    {
        if ( outputPath.Length == 0 )
            return;
        #if !WINDOWS_PHONE
            System.IO.File.WriteAllText( outputPath + fileName,  log.ToString() );
        #endif
    }

#if ALIB_MONO_DEVELOP
    [Test ()]
#endif
#if ALIB_VSTUDIO
    [TestMethod]
    #if !WINDOWS_PHONE
        [TestCategory("CS_Tutorial")]
    #endif
#endif
public void Tut_Hello_ALox_Minimum()
{
    (new HelloALox()).SayHello();
}


#if ALIB_MONO_DEVELOP
    [Test ()]
#endif
#if ALIB_VSTUDIO
    [TestMethod]
    #if !WINDOWS_PHONE
        [TestCategory("CS_Tutorial")]
    #endif
#endif
public void Tut_Hello_ALox()
{
    Log.Reset();
    Log.AddLogger( tutLog= new MemoryLogger( "Tutlog" ) );

    //! [Tut_Hello_ALox]
    //! [Tut_Hello_ALox_Line1]
    Log.AddDebugLogger();
    //! [Tut_Hello_ALox_Line1]
    //! [Tut_Hello_ALox_Line2]
    Log.SetDomain( "APP", Log.DomainLevel.InfoWarningsAndErrors );
    //! [Tut_Hello_ALox_Line2]

    //! [Tut_Hello_ALox_Line3]
    Log.Info( "APP", "Hello ALox" );
    //! [Tut_Hello_ALox_Line3]
    //! [Tut_Hello_ALox]

    #if (ALOX_DBG_LOG || ALOX_REL_LOG)
        SaveTutorialOutput( "Tut_Hello_ALox.txt", tutLog.MemoryLog );
    #endif
}

#if ALIB_MONO_DEVELOP
    [Test ()]
#endif
#if ALIB_VSTUDIO
    [TestMethod]
    #if !WINDOWS_PHONE
        [TestCategory("CS_Tutorial")]
    #endif
#endif
public void Tut_LogLevels()
{
    Log.Reset();
    Log.AddLogger( tutLog= new MemoryLogger( "Tutlog"  ) );

    //! [Tut_LogLevels]
    Log.AddDebugLogger();
    //! [Tut_LogLevels_SetDomain]
    Log.SetDomain( "APP", Log.DomainLevel.InfoWarningsAndErrors );
    //! [Tut_LogLevels_SetDomain]

    Log.Error  ( "APP", "A severe error happened :-(" );
    Log.Warning( "APP", "This is a warning :-/ Maybe an error follows?" );
    Log.Info   ( "APP", "Just for your further information!" );
    Log.Verbose( "APP", "Today, I am in the mood to talk..." );
    //! [Tut_LogLevels]

    #if (ALOX_DBG_LOG || ALOX_REL_LOG)
        SaveTutorialOutput( "Tut_LogLevels.txt", tutLog.MemoryLog );
    #endif
}

#if ALIB_MONO_DEVELOP
    [Test ()]
#endif
#if ALIB_VSTUDIO
    [TestMethod]
    #if !WINDOWS_PHONE
        [TestCategory("CS_Tutorial")]
    #endif
#endif
public void Tut_DefaultDomains()
{
    Log.Reset();
    Log.AddLogger( tutLog= new MemoryLogger( "Tutlog"  ) );

    //! [Tut_DefaultDomains]
    Log.AddLogger( new ConsoleLogger() );
    Log.SetDomain( "APP", Log.Scope.SourceFile );
    Log.SetDomain( "APP", Log.DomainLevel.InfoWarningsAndErrors );

    Log.Error  ( "A severe error happened :-(" );
    Log.Warning( "This is a warning :-/ Maybe an error follows?" );
    Log.Info   ( "Just for your further information!" );
    Log.Verbose( "Today, I am in the mood to talk..." );
    //! [Tut_DefaultDomains]

    #if (ALOX_DBG_LOG || ALOX_REL_LOG)
        SaveTutorialOutput( "Tut_DefaultDomains.txt", tutLog.MemoryLog );
    #endif

    Log.Reset();
    Log.AddLogger( tutLog= new MemoryLogger( "Tutlog" ));
    #if (ALOX_DBG_LOG || ALOX_REL_LOG)
        tutLog.RootDomain.SetLevel( Log.DomainLevel.All, Propagation.None );
        tutLog.SetDomain( Log.LOX.InternalDomain, Log.DomainLevel.WarningsAndErrors );
    #endif

    //! [Tut_DefaultDomains_part2]
    Log.Info  ( "APP", "Hello ALox" );
    //! [Tut_DefaultDomains_part2]

    #if (ALOX_DBG_LOG || ALOX_REL_LOG)
        tutLog.MemoryLog.SearchAndReplace( "Tutlog", "Console" );
        SaveTutorialOutput( "Tut_DefaultDomains_part2.txt", tutLog.MemoryLog );
    #endif
}

public void Tut_Placing()
{
    //! [Tut_Placing_Part1]
    Log.AddLogger( new ConsoleLogger() );

    Log.SetDomain( "MYAPP",   Log.DomainLevel.All);
    Log.SetDomain( "SOCKETS", Log.DomainLevel.WarningsAndErrors );
    Log.SetDomain( "UI",      Log.DomainLevel.Errors );
    Log.SetDomain( "UI/DLGS", Log.DomainLevel.InfoWarningsAndErrors );
    Log.SetDomain( "3DCALC",  Log.DomainLevel.Off  );
    //! [Tut_Placing_Part1]

    //! [Tut_Placing_Part3]
    Log.Info( "MYDOM/PERF", "Heavy calculation started..." );
        heavyCalculation();
    Log.Info( "MYDOM/PERF", "Heavy calculation finished!" );
    //! [Tut_Placing_Part3]

    //! [Tut_Placing_Part3b]
    Log.Info( "~PERF", "Heavy calculation started..." );
        heavyCalculation();
    Log.Info( "~PERF", "Heavy calculation finished!" );
    //! [Tut_Placing_Part3b]
}
void heavyCalculation() {}

public void Tut_ConditionalLogging()
{
    String[] array= new string[5];
    int len= 5;
    string search= null;

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
        Log.Error( "Nothing found :-(" );
    //! [Tut_ConditionalLogging]

    //! [Tut_ConditionalLogging2]
    Log.Assert( i < len, "Nothing found :-(" );
    //! [Tut_ConditionalLogging2]
}
private void process(int i) {}

#if ALIB_MONO_DEVELOP
    [Test ()]
#endif
#if ALIB_VSTUDIO
    [TestMethod]
    #if !WINDOWS_PHONE
        [TestCategory("CS_Tutorial")]
    #endif
#endif
public void Tut_Instance()
{
#if ALOX_DBG_LOG || ALOX_REL_LOG
    Log.Reset();
    Log.AddLogger( new ConsoleLogger() );
    Log.AddLogger( tutLog= new MemoryLogger( "Tutlog" )  );
    Log.SetDomain( "MYDOM", Log.DomainLevel.All );
    tutLog.RootDomain.SetLevel( Log.DomainLevel.All, Propagation.None );
    tutLog.MultiLineMsgMode= 4;

    //! [Tut_Instance]
    // Log multi-lines without indent
    #if ALOX_DBG_LOG
        ((TextLogger) Log.GetLogger( "Console" )).MultiLineMsgMode= 4;
    #endif

    // Log current thread instance
    LogTools.Instance( "MYDOM", Log.Level.Info, Thread.CurrentThread, 2, "Actual Thread: ", 1 );
    //! [Tut_Instance]

    int lines= 32;
    int idx= 0;
    while (lines-- != 0)
    {
        idx= tutLog.MemoryLog.IndexOf( Environment.NewLine, idx + Environment.NewLine.Length );
        if ( idx < 0 )
            break;
    }
    if (idx > 0)
        tutLog.MemoryLog.SetLength( idx + Environment.NewLine.Length );
    tutLog.MemoryLog._( "..." )._( Environment.NewLine );
    tutLog.MemoryLog._( "..." )._( Environment.NewLine );
    tutLog.MemoryLog._( "..." )._( Environment.NewLine );
    SaveTutorialOutput( "Tut_Instance.txt", tutLog.MemoryLog );
#endif
}

#if ALIB_MONO_DEVELOP
    [Test ()]
#endif
#if ALIB_VSTUDIO
    [TestMethod]
    #if !WINDOWS_PHONE
        [TestCategory("CS_Tutorial")]
    #endif
#endif
public void Tut_Exception()
{
#if ALOX_DBG_LOG || ALOX_REL_LOG
    Log.Reset();
    Log.AddLogger( tutLog= new MemoryLogger( "Tutlog" )  );
    tutLog.RootDomain.SetLevel( Log.DomainLevel.WarningsAndErrors, Propagation.None );

    //! [Tut_Exceptions]
    Exception testException=  new Exception( "TestException Message",
                                                new Exception ( "InnerException Message",
                                                                new Exception("Inner, inner Exception") ) );
    LogTools.Exception( "MYDOM", Log.Level.Warning, testException, "Logging an exception: " );
    //! [Tut_Exceptions]

    tutLog.MemoryLog.SearchAndReplace( "Tutlog", "CONSOLE" );
    SaveTutorialOutput( "Tut_Exceptions.txt", tutLog.MemoryLog );
#endif
}

#if ALIB_MONO_DEVELOP
    [Test ()]
#endif
#if ALIB_VSTUDIO
    [TestMethod]
    #if !WINDOWS_PHONE
        [TestCategory("CS_Tutorial")]
    #endif
#endif
public void Tut_XML()
{
#if ALOX_DBG_LOG || ALOX_REL_LOG
    Log.Reset();
    Log.AddLogger( tutLog= new MemoryLogger( "Tutlog" ) );
    tutLog.RootDomain.SetLevel( Log.DomainLevel.All, Propagation.None );

    //! [Tut_XML]
    String xmltext= "<MainTag>"
                        +"<SubTag>Hello ALox XML</SubTag>"
                        +"<SubTag2>"
                            +"<SubsubTag>A sub tags' string</SubsubTag>"
                        +"</SubTag2>"
                    +"</MainTag>";
    XDocument xdoc= XDocument.Parse( xmltext );

    LogTools.XML("MYDOM", Log.Level.Info, xdoc, "Logging an xml document: " );
    //! [Tut_XML]

    tutLog.MemoryLog.SearchAndReplace( "Tutlog", "CONSOLE" );
    SaveTutorialOutput( "Tut_XML.txt", tutLog.MemoryLog );
#endif
}

#if ALIB_MONO_DEVELOP
    [Test ()]
#endif
#if ALIB_VSTUDIO
    [TestMethod]
    #if !WINDOWS_PHONE
        [TestCategory("CS_Tutorial")]
    #endif
#endif
public void Tut_SeparatedLogLevels()
{
#if ALOX_DBG_LOG || ALOX_REL_LOG
    Log.Reset();
    Log.AddLogger( tutLog= new MemoryLogger( "Tutlog" )  );
    Log.SetDomain( "MYDOM", Log.DomainLevel.All );
    tutLog.RootDomain.SetLevel( Log.DomainLevel.Off, Propagation.None );
    tutLog.MultiLineMsgMode= 4;
    tutLog.MetaInfo.Format.Clear()._( "%L [%O]: ");

    Log.SetDomain( "DOM",  Log.DomainLevel.All );
    Log.SetDomain( "DOM/CON", Log.DomainLevel.All, "Tutlog" );
    Log.SetDomain( "DOM/MEM", Log.DomainLevel.Off, "Tutlog" );


    //! [Tut_SeparatedLogLevels]
    // create two different loggers
    Log.AddLogger( new ConsoleLogger( "MyConsoleLogger" ) );
    Log.AddLogger( new MemoryLogger ( "MyMemoryLogger"  ) );

    // switch some log information off with memory logger
    #if ALOX_DBG_LOG
        ((TextLogger) Log.GetLogger("MyConsoleLogger")).MetaInfo.Format.Clear()._( "%L [%O]: ");
        ((TextLogger) Log.GetLogger("MyMemoryLogger" )).MetaInfo.Format.Clear()._( "%L [%O]: ");
    #endif

    // register domains, set DOM as default
    Log.SetDomain( "DOM",     Log.Scope.Method );
    Log.SetDomain( "DOM/CON", Log.Scope.None   );
    Log.SetDomain( "DOM/MEM", Log.Scope.None   );

    // set level of DOM for all loggers
    Log.SetDomain( "DOM",  Log.DomainLevel.All );

    // set level of DOM/CON separately for console and memory logger
    Log.SetDomain( "~CON", Log.DomainLevel.All, "MyConsoleLogger" );
    Log.SetDomain( "~CON", Log.DomainLevel.Off, "MyMemoryLogger"  );

    // set level of DOM/MEM separately for console and memory logger
    Log.SetDomain( "~MEM", Log.DomainLevel.Off, "MyConsoleLogger" );
    Log.SetDomain( "~MEM", Log.DomainLevel.All, "MyMemoryLogger"  );

    // Log info to each of the domains
    Log.Info(         "Domain= DOM      -> This goes to all loggers");
    Log.Info( "~CON", "Domain= DOM/CON  -> This goes to ConsoleLogger exclusively");
    Log.Info( "~MEM", "Domain= DOM/MEM  -> This goes to MemoryLogger exclusively");

    // To verify the result, we log the contents of the MemoryLogger to the console logger
    Log.Info( "~CON", "Here comes the contents of MemoryLogger:");
    #if ALOX_DBG_LOG
        Log.Info( "~CON", ((MemoryLogger) Log.GetLogger("MyMemoryLogger")).MemoryLog.ToString(), 1);
    #endif
    //! [Tut_SeparatedLogLevels]

    tutLog.MemoryLog.SearchAndReplace( "Tutlog", "MyConsoleLogger" );
    SaveTutorialOutput( "Tut_SeparatedLogLevels.txt", tutLog.MemoryLog );
#endif
}

#if ALIB_MONO_DEVELOP
    [Test ()]
#endif
#if ALIB_VSTUDIO
    [TestMethod]
    #if !WINDOWS_PHONE
        [TestCategory("CS_Tutorial")]
    #endif
#endif
public void Tut_LogConfig()
{
#if ALOX_DBG_LOG || ALOX_REL_LOG
    Log.Reset();

    //! [Tut_LogConfig]
    // create two different loggers
    Log.AddDebugLogger();
    Log.AddLogger( new MemoryLogger () );

    // reduce meta information to limit tutorial output width
    #if ALOX_DBG_LOG
                                Log.DebugLogger.MetaInfo.Format.Clear()._( " %L [%O]: " );
        ((TextLogger) Log.GetLogger("Memory" )).MetaInfo.Format.Clear()._( " %L [%O]: " );
    #endif

    // Our previous sample
    Log.SetDomain( "DOM",     Log.Scope.Method    );
    Log.SetDomain( "DOM/CON", Log.Scope.None      );
    Log.SetDomain( "DOM/MEM", Log.Scope.None      );
    Log.SetDomain( "DOM",     Log.DomainLevel.All );
    Log.SetDomain( "~CON",    Log.DomainLevel.All, "Console" );
    Log.SetDomain( "~CON",    Log.DomainLevel.Off, "Memory"  );
    Log.SetDomain( "~MEM",    Log.DomainLevel.Off, "Console" );
    Log.SetDomain( "~MEM",    Log.DomainLevel.All, "Memory"  );
    Log.MapThreadName( "Thread1" );

    // Log current Log configuration
    Log.LogConfig( "DOM", Log.Level.Verbose, "Here comes the current Log configuration:" );
    //! [Tut_LogConfig]

    //tutLog.MemoryLog.Replace( "Tutlog", "CONSOLE" );
    #if ALOX_DBG_LOG
        SaveTutorialOutput( "Tut_LogConfig.txt", ((MemoryLogger) Log.GetLogger( "Memory" )).MemoryLog );
    #endif
#endif
}


#if ALIB_MONO_DEVELOP
    [Test ()]
#endif
#if ALIB_VSTUDIO
    [TestMethod]
    #if !WINDOWS_PHONE
        [TestCategory("CS_Tutorial")]
    #endif
#endif
public void Tut_LogConfig2()
{
#if ALOX_DBG_LOG || ALOX_REL_LOG
    Log.Reset();

    // ##### code inclusion version ########
    //! [Tut_LogConfig2]
    // change internal domain ("ALOX") to level 'All'
    Log.AddDebugLogger();
    Log.SetDomain( "ALOX",  Log.DomainLevel.All );

    // Our previous sample
    #if ALOX_DBG_LOG
        // also, reduce meta information width (for tutorial output readability)
        Log.DebugLogger.MetaInfo.Format.Clear()._( "[%t]%L[%O](%#): " );
    #endif
    Log.AddLogger( new MemoryLogger () );
    Log.SetDomain( "DOM",     Log.Scope.Method    );
    Log.SetDomain( "DOM/CON", Log.Scope.None      );
    Log.SetDomain( "DOM/MEM", Log.Scope.None      );
    Log.SetDomain( "DOM",     Log.DomainLevel.All );
    Log.SetDomain( "~CON",    Log.DomainLevel.All, "Console" );
    Log.SetDomain( "~CON",    Log.DomainLevel.Off, "Memory"  );
    Log.SetDomain( "~MEM",    Log.DomainLevel.Off, "Console" );
    Log.SetDomain( "~MEM",    Log.DomainLevel.All, "Memory"  );
    Log.MapThreadName( "Thread1" );
    //! [Tut_LogConfig2]

    // ##### output generation version - the only difference is that memory logger gets all messages ########
    Log.Reset();
    Log.MapThreadName( "MAIN" );

    tutLog= new MemoryLogger ("CONSOLE");
    tutLog.MetaInfo.Format.Clear()._( "[%t]%L[%O](%#): " );

    Log.AddLogger( tutLog );
    Log.SetDomain( "ALOX",  Log.DomainLevel.All );
    tutLog.RootDomain.SetLevel( Log.DomainLevel.All, Propagation.None );

    // Our previous sample
    Log.AddLogger( new ConsoleLogger("MEMORY") );
    Log.SetDomain( "DOM",     Log.Scope.Method    );
    Log.SetDomain( "DOM/CON", Log.Scope.None      );
    Log.SetDomain( "DOM/MEM", Log.Scope.None      );
    Log.SetDomain( "DOM",     Log.DomainLevel.All );
    Log.SetDomain( "~CON",    Log.DomainLevel.All, "Console" );
    Log.SetDomain( "~CON",    Log.DomainLevel.Off, "Memory"  );
    Log.SetDomain( "~MEM",    Log.DomainLevel.Off, "Console" );
    Log.SetDomain( "~MEM",    Log.DomainLevel.All, "Memory"  );
    Log.MapThreadName( "Thread1" );

    //tutLog.MemoryLog.Replace( "Tutlog", "CONSOLE" );
    #if ALOX_DBG_LOG
        tutLog.MemoryLog.SearchAndReplace( " (CONSOLE)", "" );
        SaveTutorialOutput( "Tut_LogConfig2.txt", tutLog.MemoryLog );
    #endif
#endif
}


/** ************************************************************************************************
* Tut_UsingLogBuffer
**************************************************************************************************/
#if ALIB_MONO_DEVELOP
    [Test ()]
#endif
#if ALIB_VSTUDIO
    [TestMethod]
    #if !WINDOWS_PHONE
        [TestCategory("CS_Tutorial")]
    #endif
#endif
public void Tut_UsingLogBuffer()
{
#if ALOX_DBG_LOG || ALOX_REL_LOG
    Log.Reset();
    Log.AddLogger( tutLog= new MemoryLogger( "Tutlog" ) );
    tutLog.RootDomain.SetLevel( Log.DomainLevel.All, Propagation.None );
    tutLog.SetDomain( Log.LOX.InternalDomain, Log.DomainLevel.Errors );

    //! [Tut_UsingLogBuffer1]
    //  Create logger and register domain LOGBUF
    Log.AddDebugLogger();
    Log.SetDomain( "LOGBUF", Log.Scope.Method );
    Log.SetDomain( "LOGBUF", Log.DomainLevel.All);

    //  Let's do some logging using the internal buffer singleton;
    Log.Info( Log.Buf()._( "Hello Buf!. This is only one string. Not useful to use the buf, however..." ) );
    Log.Info( Log.Buf()._( "This is a 5-digtit rep of 42: " )._( 42, 5 ) );
    Log.Info( Log.Buf()._( "***All upper case and stars replaced by dollar signs ***" )
                       .ToUpper()
                       .SearchAndReplaceAll( "*", "$" )
            );
    //! [Tut_UsingLogBuffer1]

    //! [Tut_UsingLogBuffer2]
    // using the log buf outside of the log statement
    #if ALOX_DBG_LOG

        AString logBuf= Log.Buf();
        logBuf._( "Lets see if school math is correct: " );
        int a= 4;
        int b= 2;
        if( a/b == 3)
        {
            // shout it out loud!
            logBuf._( "They taught me wrong in school!" );
            Log.Error( logBuf );
        }
        else
        {
            // we better say nothing
            Log.BufAbort();
        }

    #endif
    //! [Tut_UsingLogBuffer2]

    bool oldHaltOnError=    Report.GetDefault().HaltOnError;
    bool oldHaltOnWarning=  Report.GetDefault().HaltOnWarning;
    Report.GetDefault().HaltOnError=
    Report.GetDefault().HaltOnWarning= false;

    //! [Tut_UsingLogBuffer3]
    // causing trouble
    Log.Info( "Let's create an internal error by accessing the buffer twice:" );
    Log.Buf();
    Log.Buf();
    //! [Tut_UsingLogBuffer3]

    Report.GetDefault().HaltOnError=      oldHaltOnError;
    Report.GetDefault().HaltOnWarning=    oldHaltOnWarning;

    // END OF TUTORIAL
    tutLog.MemoryLog.SearchAndReplace( "Tutlog", "CONSOLE" );
    SaveTutorialOutput( "Tut_UsingLogBuffer.txt", tutLog.MemoryLog );
    #endif
}

    }
#endif// ALOX_DBG_LOG
}
