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

// #################################################################################################
// Tut_ScopeDomains
// #################################################################################################
class TutScopeDom
{
    //! [Tut_ScopeDomains]
    public char[] Extract( String fileName, char[] buffer )
    {
        Log.SetDomain( "ZIP/EXTRACT", Scope.Method ); // set Scope Domain path for this method
        //...
        Log.Info( "Extracting " + fileName );
        //...
        //...
        Log.Info( "Success" ); // a nice, clear, local, copyable log statement!
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
        Log.SetDomain( "ZIP", Scope.Filename ); // set Scope Domain path for this class (filename)
        //...
        Log.Info( "Zipper created" ); // domain "ZIP"
        //...
    }

    public char[] Compress( String fileName, char[] buffer )
    {
        Log.SetDomain( "COMPRESS", Scope.Method ); // set Scope Domain path for this method
        //...
        Log.Info( "Compressing " + fileName );
        //...
        //...
        Log.Info( "Success" ); // domain "ZIP/COMPRESS"
        //...
        return buffer;
    }

    public char[] Extract( String fileName, char[] buffer )
    {
        Log.SetDomain( "EXTRACT", Scope.Method ); // set Scope Domain path for this method
        //...
        Log.Info( "Extracting " + fileName );
        //...
        //...
        Log.Info( "Success" ); // domain "ZIP/EXTRACT"
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
        Log.SetDomain( "READ", Scope.Method );
        Log.Info( "Reading " + fileName );

        int fileVersion= 0;
        //...
        //...
        // Identified file version
        fileVersion= 42;

        Log.Store( new LogData( fileVersion ), "FILE_VERSION" );

        //...
        //...
        Log.Info( "Success" );
    }
};
//! [Tut_LogData]


/** ************************************************************************************************
*  Implements the tutorial code that with snippets markers for doxygen inclusion.
**************************************************************************************************/

#if ALOX_DBG_LOG


#if ALIB_MONO_DEVELOP
    [TestFixture ()]
#endif
#if ALIB_VSTUDIO
    [TestClass]
#endif

public class CS_Tutorial   : AUnitTest
{
    // used with unit test Log_ScopeInfoCacheTest
    public static void ScopeInfoCacheTest() { Log.Info("Test method of CS_Tutorial"); }


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
    UT_INIT();

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
    UT_INIT();


    //! [Tut_ALox_Logger_1]
    Log.AddDebugLogger();
    //! [Tut_ALox_Logger_1]

    Log.RemoveDebugLogger();
    Log.SetVerbosity( tutLog= new MemoryLogger( "Tutlog" ), Verbosity.Verbose );

    //! [Tut_ALox_Logger_2]
    Log.AddDebugLogger();
    Log.Info( "Hello ALox" );
    //! [Tut_ALox_Logger_2]

    #if (ALOX_DBG_LOG || ALOX_REL_LOG)
        SaveTutorialOutput( "Tut_ALox_Logger.txt", tutLog.MemoryLog );
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
public void Tut_Verbosity()
{
    UT_INIT();

    Log.SetVerbosity( tutLog= new MemoryLogger( "Tutlog" ), Verbosity.Verbose );

    //! [Tut_Verbosity]
    Log.AddDebugLogger();

    Log.Error  ( "A severe error happened :-(" );
    Log.Warning( "This is a warning :-/ Maybe an error follows?" );
    Log.Info   ( "Just for your further information!" );
    Log.Verbose( "Today, I am in the mood to talk..." );
    //! [Tut_Verbosity]


    //! [Tut_Verbosity_SetVerbosity]
    Log.SetVerbosity( Log.DebugLogger, Verbosity.Warning );
    //! [Tut_Verbosity_SetVerbosity]

    //! [Tut_Verbosity_SetVerbosity_2]
    Log.SetVerbosity( "DEBUG_LOGGER", Verbosity.Warning );
    //! [Tut_Verbosity_SetVerbosity_2]

    #if (ALOX_DBG_LOG || ALOX_REL_LOG)
        SaveTutorialOutput( "Tut_Verbosity.txt", tutLog.MemoryLog );
        tutLog.MemoryLog.Clear(); tutLog.CntLogs= 0;
        Log.SetVerbosity( tutLog, Verbosity.Warning);
    #endif

    Log.RemoveDebugLogger();

    //! [Tut_Verbosity_2]
    Log.AddDebugLogger();

    Log.SetVerbosity( Log.DebugLogger, Verbosity.Warning );

    Log.Error  ( "A severe error happened :-(" );
    Log.Warning( "This is a warning :-/ Maybe an error follows?" );
    Log.Info   ( "Just for your further information!" );
    Log.Verbose( "Today, I am in the mood to talk..." );
    //! [Tut_Verbosity_2]

    #if (ALOX_DBG_LOG || ALOX_REL_LOG)
        SaveTutorialOutput( "Tut_Verbosity_2.txt", tutLog.MemoryLog );
    #endif
    Log.RemoveLogger( tutLog );
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
public void Tut_Domains()
{
    UT_INIT();

    Log.SetVerbosity( tutLog= new MemoryLogger( "Tutlog" ), Verbosity.Verbose );

    //! [Tut_Domains]
    Log.AddDebugLogger();
    Log.SetVerbosity( Log.DebugLogger, Verbosity.Verbose ); // the default anyhow
    //...
    Log.Verbose( "HTTP", "Connected" );
    //...
    //...
    //...
    Log.Verbose( "UI",   "Somebody moved the mouse!" );
    //...
    //! [Tut_Domains]


    #if (ALOX_DBG_LOG || ALOX_REL_LOG)
        SaveTutorialOutput( "Tut_Domains.txt", tutLog.MemoryLog );
        tutLog.MemoryLog.Clear(); tutLog.CntLogs= 0;
        Log.RemoveDebugLogger();
    #endif
    Log.SetVerbosity( tutLog, Verbosity.Verbose,  "HTTP" ); // our interest
    Log.SetVerbosity( tutLog, Verbosity.Error,    "UI"   ); // only if ouch!

    //! [Tut_Domains_2]
    Log.AddDebugLogger();

    Log.SetVerbosity( Log.DebugLogger, Verbosity.Verbose,  "HTTP" ); // our interest
    Log.SetVerbosity( Log.DebugLogger, Verbosity.Error,    "UI"   ); // only if ouch!
    //...
    Log.Verbose( "HTTP", "Connected" );
    //...
    //...
    //...
    Log.Verbose( "UI",   "Somebody moved the mouse!" );
    //...
    //! [Tut_Domains_2]


    #if (ALOX_DBG_LOG || ALOX_REL_LOG)
        SaveTutorialOutput( "Tut_Domains_2.txt", tutLog.MemoryLog );
    #endif
    Log.RemoveLogger( tutLog );
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
public void Tut_HierDom()
{
    UT_INIT();

    Log.SetVerbosity( tutLog= new MemoryLogger( "Tutlog" ), Verbosity.Verbose );

    //! [Tut_DomainsHierarchical]
    Log.AddDebugLogger();
    Log.SetVerbosity( Log.DebugLogger, Verbosity.Verbose ); // the default anyhow
    //...
    Log.Info   ( "UI/MOUSE",   "A mouse click" );
    //...
    Log.Verbose( "UI/MOUSE",   "Somebody moved the mouse!" );
    //...
    //...
    Log.Info   ( "UI/DLG",     "About dialog opend" );
    //...
    Log.Verbose( "UI/DLG",     "About dialog, link to product page pressed." );
    //...
    //! [Tut_DomainsHierarchical]


    #if (ALOX_DBG_LOG || ALOX_REL_LOG)
        SaveTutorialOutput( "Tut_DomainsHierarchical.txt", tutLog.MemoryLog );
        tutLog.MemoryLog.Clear(); tutLog.CntLogs= 0;
        Log.RemoveDebugLogger();
    #endif

    //! [Tut_DomainsHierarchical_2]
    Log.SetVerbosity( Log.DebugLogger, Verbosity.Warning, "UI"  ); // Always sets all sub-domains!
    //! [Tut_DomainsHierarchical_2]

    //! [Tut_DomainsHierarchical_3]
    Log.SetVerbosity( Log.DebugLogger, Verbosity.Warning, "UI"       ); // First set parent...
    Log.SetVerbosity( Log.DebugLogger, Verbosity.Verbose, "UI/MOUSE" ); // ...then children!
    //! [Tut_DomainsHierarchical_3]

    Log.RemoveLogger( tutLog );
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
public void Tut_ScopeDomains()
{
    UT_INIT();

    Log.SetVerbosity( tutLog= new MemoryLogger( "Tutlog" ), Verbosity.Verbose );
    Log.AddDebugLogger();

    TutScopeDom tsd= new TutScopeDom();
    tsd.Extract( "myfile.zip", null );

    #if (ALOX_DBG_LOG || ALOX_REL_LOG)
    SaveTutorialOutput( "Tut_ScopeDomains.txt", tutLog.MemoryLog );
    tutLog.MemoryLog.Clear(); tutLog.CntLogs= 0;
    #endif

    // do it once to set the tab positions of the meta info...
    {
        Zipper zip= new Zipper();
        zip.Compress( "myfile.zip", null );
        zip.Extract( "myfile.zip", null );
        #if (ALOX_DBG_LOG || ALOX_REL_LOG)
        tutLog.MemoryLog.Clear(); tutLog.CntLogs= 0;
        #endif
    }
    // ...and again
    {
        Zipper zip= new Zipper();
        zip.Compress( "myfile.zip", null );
        zip.Extract( "myfile.zip", null );
    }

    #if (ALOX_DBG_LOG || ALOX_REL_LOG)
    SaveTutorialOutput( "Tut_ScopeDomains_Zipper.txt", tutLog.MemoryLog );
    #endif

    //---------- with scope path ---------------

    //! [Tut_ScopeDomains_Path]
    Log.SetDomain( "UTIL", Scope.Path );
    //! [Tut_ScopeDomains_Path]

    #if (ALOX_DBG_LOG || ALOX_REL_LOG)
    tutLog.MemoryLog.Clear(); tutLog.CntLogs= 0;
    #endif
    // do it once to set the tab positions of the meta info...
    {
        Zipper zip= new Zipper();
        zip.Compress( "myfile.zip", null );
        zip.Extract( "myfile.zip", null );
        #if (ALOX_DBG_LOG || ALOX_REL_LOG)
        tutLog.MemoryLog.Clear(); tutLog.CntLogs= 0; tutLog.CntLogs= 0;
        #endif
    }
    // ...and again
    {
        Zipper zip= new Zipper();
        zip.Compress( "myfile.zip", null );
        zip.Extract( "myfile.zip", null );
    }
    #if (ALOX_DBG_LOG || ALOX_REL_LOG)
    SaveTutorialOutput( "Tut_ScopeDomains_Zipper_Path.txt", tutLog.MemoryLog );
    tutLog.MemoryLog.Clear(); tutLog.CntLogs= 0;
    #endif

    Log.SetDomain( null, Scope.Path );
    Log.SetDomain( null, Scope.Filename );

    //! [Tut_ScopeDomains_ParamDom]
    Log.SetDomain( "METHOD", Scope.Method );
    Log.Info(          "No domain parameter given" );
    Log.Info( "PARAM", "Domain parameter \"PARAM\" given" );
    //! [Tut_ScopeDomains_ParamDom]

    // clear autosizes, repeat it twice
    #if (ALOX_DBG_LOG || ALOX_REL_LOG)
    tutLog.AutoSizes.Reset();
    #endif
    Log.Info(          "No domain parameter given" );
    Log.Info( "PARAM", "Domain parameter \"PARAM\" given" );
    tutLog.MemoryLog.Clear(); tutLog.CntLogs= 0;
    Log.Info(          "No domain parameter given" );
    Log.Info( "PARAM", "Domain parameter \"PARAM\" given" );

    #if (ALOX_DBG_LOG || ALOX_REL_LOG)
    SaveTutorialOutput( "Tut_ScopeDomains_ParamDom.txt", tutLog.MemoryLog );
    tutLog.MemoryLog.Clear(); tutLog.CntLogs= 0;
    #endif


    //! [Tut_ScopeDomains_ParamDom_2]
    Log.SetDomain( "READ", Scope.Method );
    Log.Info( "Reading file" );
    //...
    //...
    Log.Info( "/CONFIG",   "Path not found." );
    //...
    //! [Tut_ScopeDomains_ParamDom_2]

    #if (ALOX_DBG_LOG || ALOX_REL_LOG)
    SaveTutorialOutput( "Tut_ScopeDomains_ParamDom_2.txt", tutLog.MemoryLog );
    #endif

    Log.RemoveLogger( tutLog );
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
public void Tut_Prefix()
{
    UT_INIT();

    Log.SetVerbosity( tutLog= new MemoryLogger( "Tutlog" ), Verbosity.Verbose );
    Log.AddDebugLogger();

    //! [Tut_Prefix]
    Log.SetPrefix( "ALOX TUTORIAL: ", Scope.Method );

    Log.Info( "Well, just a sample" );
    //! [Tut_Prefix]


    #if (ALOX_DBG_LOG || ALOX_REL_LOG)
    SaveTutorialOutput( "Tut_Prefix.txt", tutLog.MemoryLog );
    #endif

    //! [Tut_Prefix_2]
    Log.SetPrefix( ESC.BG_MAGENTA, Scope.Filename );
    //! [Tut_Prefix_2]

    Log.Warning( "magenta" );

    Log.RemoveLogger( tutLog );
}


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

    //! [Tut_ConditionalLogging3]
    Log.If( i == len, Verbosity.Error, "Nothing found :-(" );
    //! [Tut_ConditionalLogging3]

    //! [Tut_ConditionalLoggingOnce]
    Log.Once( "I tell you this now only once!" );
    //! [Tut_ConditionalLoggingOnce]
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
    UT_INIT();

    Log.SetVerbosity( new ConsoleLogger(), Verbosity.Verbose, "/" );
    Log.SetVerbosity( tutLog= new MemoryLogger( "Tutlog" ), Verbosity.Verbose, "/" );
    tutLog.MultiLineMsgMode= 4;

    //! [Tut_Instance]
    // Log multi-lines without meta info
    #if ALOX_DBG_LOG
        ((TextLogger) Log.GetLogger( "Console" )).MultiLineMsgMode= 4;
    #endif

    // Log current thread instance
    LogTools.Instance( "MYDOM", Verbosity.Info, Thread.CurrentThread, 2, "Actual Thread: " );
    //! [Tut_Instance]

    // cut the output to 30 lines
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
    UT_INIT();

    Log.SetVerbosity( tutLog= new MemoryLogger( "Tutlog" ), Verbosity.Warning, "/" );
    #if ALOX_DBG_LOG
        ((TextLogger) Log.GetLogger( "Tutlog" )).MultiLineMsgMode= 4;
    #endif

    //! [Tut_Exceptions]
    Exception testException=  new Exception( "TestException Message",
                                                new Exception ( "InnerException Message",
                                                                new Exception("Inner, inner Exception") ) );
    LogTools.Exception( "MYDOM", Verbosity.Warning, testException, "Logging an exception: " );
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
    UT_INIT();
    Log.SetVerbosity( tutLog= new MemoryLogger( "Tutlog" ), Verbosity.Verbose, "/" );
    tutLog.MultiLineMsgMode= 4;

    //! [Tut_XML]
    String xmltext= "<MainTag>"
                        +"<SubTag>Hello ALox XML</SubTag>"
                        +"<SubTag2>"
                            +"<SubsubTag>A sub tags' string</SubsubTag>"
                        +"</SubTag2>"
                    +"</MainTag>";
    XDocument xdoc= XDocument.Parse( xmltext );

    LogTools.XML("MYDOM", Verbosity.Info, xdoc, "Logging an xml document: " );
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
public void Tut_LogConfig()
{
#if ALOX_DBG_LOG || ALOX_REL_LOG
    UT_INIT();

    //! [Tut_LogConfig]
    // create two different loggers
    Log.AddDebugLogger();
    Log.SetVerbosity( new MemoryLogger(),  Verbosity.Verbose );

    // reduce meta information to limit tutorial output width
    #if ALOX_DBG_LOG
        Log.DebugLogger                         .MetaInfo.Format._()._( "[%tN]%V[%D](%#): " );
        ((MemoryLogger) Log.GetLogger("MEMORY")).MetaInfo.Format._()._( "[%tN]%V[%D](%#): " );
        ((MemoryLogger) Log.GetLogger("MEMORY")).MultiLineMsgMode= 3;
    #endif
    // OK, let's use ALox
    Log.SetDomain( "PNS"   ,   Scope.Path, 1 );
    Log.SetDomain( "PATH",     Scope.Path );
    Log.SetDomain( "FN",       Scope.Filename );
    Log.SetDomain( "THREAD",   Scope.ThreadOuter );

    Log.SetVerbosity( "MEMORY",        Verbosity.Off      , "/CON"    );
    Log.SetVerbosity( "DEBUG_LOGGER" , Verbosity.Verbose              );
    Log.SetVerbosity( "DEBUG_LOGGER" , Verbosity.Off      , "/MEM"    );
    Log.SetVerbosity( "DEBUG_LOGGER" , Verbosity.Error    , "/UI"     );
    Log.SetVerbosity( "DEBUG_LOGGER" , Verbosity.Info     , "/UI/DLG" );

    Log.Info( "This goes to both loggers" );
    Log.Info( "/MEM", "This goes only to the memory logger" );
    Log.Info( "/CON", "This goes only to the console logger" );

    Log.Once( "Will we see this in the config?" );
    Log.Once( "Will we see this in the config?", "ONCEKEY", Scope.Filename );

    Log.Store( new LogData("MyData 1"), Scope.Method );
    Log.Store( new LogData("MyData 2"), "DataKey", Scope.Method );
    Log.Store( new LogData("MyData 3"), "DataKey", Scope.Filename );
    Log.Store( new LogData("MyData 4"), "DataKey", Scope.ThreadOuter );

    Log.SetPrefix( "TPre: "  , Scope.ThreadOuter );
    Log.SetPrefix( "MPre: "  , Scope.Method );
    Log.SetPrefix( "DomPre: " );
    Log.SetPrefix( "Mouse: ", "/UI/MOUSE" );
    Log.SetPrefix( ESC.RED,  "/ERRORS", Inclusion.Exclude );

    Log.MapThreadName( "TUTORIAL" );

    // now, log the current config
    Log.LogConfig( null, Verbosity.Info, "The current configuration of this Lox is:" );
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
public void Tut_LogInternalDomains()
{
#if ALOX_DBG_LOG || ALOX_REL_LOG
    UT_INIT();

    //! [Tut_LogInternalDomains]
    // This is the very same code as above...
    Log.AddDebugLogger();
    Log.SetVerbosity( new MemoryLogger(),  Verbosity.Verbose );

    #if ALOX_DBG_LOG
        Log.DebugLogger                         .MetaInfo.Format._()._( "[%tN]%V[%D](%#): " );
        ((MemoryLogger) Log.GetLogger("MEMORY")).MetaInfo.Format._()._( "[%tN]%V[%D](%#): " );
    #endif

    // ... with one difference: we are activating the internal domain
    Log.SetVerbosity( ((MemoryLogger) Log.GetLogger("MEMORY")), Verbosity.Verbose, ALox.InternalDomains );
    Log.SetVerbosity( Log.DebugLogger,                          Verbosity.Verbose, ALox.InternalDomains );

    Log.SetDomain( "PNS"   ,   Scope.Path, 1 );
    Log.SetDomain( "PATH",     Scope.Path );
    Log.SetDomain( "FN",       Scope.Filename );
    Log.SetDomain( "THREAD",   Scope.ThreadOuter );

    Log.SetVerbosity( "MEMORY",        Verbosity.Off      , "/CON"    );
    Log.SetVerbosity( "DEBUG_LOGGER" , Verbosity.Verbose              );
    Log.SetVerbosity( "DEBUG_LOGGER" , Verbosity.Off      , "/MEM"    );
    Log.SetVerbosity( "DEBUG_LOGGER" , Verbosity.Error    , "/UI"     );
    Log.SetVerbosity( "DEBUG_LOGGER" , Verbosity.Info     , "/UI/DLG" );

    Log.Info( "This goes to both loggers" );
    Log.Info( "/MEM", "This goes only to the memory logger" );
    Log.Info( "/CON", "This goes only to the console logger" );

    Log.Once( "Will we see this in the config?" );
    Log.Once( "Will we see this in the config?", "ONCEKEY", Scope.Filename );

    Log.Store( new LogData("MyData 1"), Scope.Method );
    Log.Store( new LogData("MyData 2"), "DataKey", Scope.Method );
    Log.Store( new LogData("MyData 3"), "DataKey", Scope.Filename );
    Log.Store( new LogData("MyData 4"), "DataKey", Scope.ThreadOuter );

    Log.SetPrefix( "TPre: "  , Scope.ThreadOuter );
    Log.SetPrefix( "MPre: "  , Scope.Method );
    Log.SetPrefix( "DomPre: " );
    Log.SetPrefix( "Mouse: ", "/UI/MOUSE" );
    Log.SetPrefix( ESC.RED,  "/ERRORS", Inclusion.Exclude );

    Log.MapThreadName( "TUTORIAL" );
    //! [Tut_LogInternalDomains]

    SaveTutorialOutput( "Tut_LogInternalDomains.txt", ((MemoryLogger) Log.GetLogger("MEMORY")).MemoryLog );

    Log.RemoveDebugLogger();
    Log.RemoveLogger("MEMORY");

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
    UT_INIT();
    Log.SetVerbosity( tutLog= new MemoryLogger( "Tutlog" ), Verbosity.Verbose );

    //! [Tut_UsingLogBuffer1]
    //  Create logger and register domain LOGBUF
    Log.AddDebugLogger();
    Log.SetDomain( "LOGBUF", Scope.Method );

    //  Let's do some logging using the internal buffer singleton;
    Log.Info( Log.Buf()._( "Hello Buf!. This is only one string. Not useful to use the buf, however..." ) );
    Log.Info( Log.Buf()._( "This is a 5-digtit rep of 42: " )._( 42, 5 ) );
    Log.Info( Log.Buf()._( "***All upper case and stars replaced by dollar signs ***" )
                       .ToUpper()
                       .SearchAndReplaceAll( "*", "$" )
            );
    //! [Tut_UsingLogBuffer1]

    //! [Tut_UsingLogBuffer2]
    // using the log buf outside of the <em>Log Statement</em>
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

    Report.GetDefault().PushHaltFlags( false, false );

    //! [Tut_UsingLogBuffer3]
    // causing trouble
    Log.Info( "Let's create an internal error by accessing the buffer twice:" );
    Log.Buf();
    Log.Buf();
    //! [Tut_UsingLogBuffer3]

    Report.GetDefault().PopHaltFlags();

    tutLog.MemoryLog.SearchAndReplace( "Tutlog", "CONSOLE" );
    SaveTutorialOutput( "Tut_UsingLogBuffer.txt", tutLog.MemoryLog );
#endif
}

/** ************************************************************************************************
* Tut_LogData
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
public void Tut_LogData()
{
    UT_INIT();
    Log.AddDebugLogger();
    Log.SetVerbosity( tutLog= new MemoryLogger( "Tutlog" ), Verbosity.Verbose );

    Log.SetVerbosity( Log.DebugLogger, Verbosity.Verbose, ALox.InternalDomains );

    // access without prior setting
    {
        Log.Info( "Working on file version " + Log.Retrieve( "FILE_VERSION" ).IntegerValue );
        SaveTutorialOutput( "Tut_LogData2.txt", tutLog.MemoryLog );
        tutLog.MemoryLog.Clear();
    }

    FileIO fileIo = new FileIO();
    fileIo.Read( "myfile.dat" );

    //! [Tut_LogData_2]
    Log.Info( "Working on file version " + Log.Retrieve( "FILE_VERSION" ).IntegerValue );
    //! [Tut_LogData_2]

    SaveTutorialOutput( "Tut_LogData.txt", tutLog.MemoryLog );

    Log.RemoveDebugLogger();
    Log.RemoveLogger( "MEMORY" );
}

}// class  CS_Tutorial

#endif 

}// namespace

