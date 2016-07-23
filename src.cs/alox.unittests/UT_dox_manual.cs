// #################################################################################################
//  cs.aworx.lox.unittests - ALox Logging Library
//  (Unit Tests to create tutorial sample code and output)
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
using ut_cs_aworx;
using System;
using cs.aworx.lib.strings;
using System.Collections.Generic;
using cs.aworx.lib.config;

#if ALIB_MONO_DEVELOP
    using NUnit.Framework;
#endif
#if ALIB_VSTUDIO
    using Microsoft.VisualStudio.TestTools.UnitTesting;
#endif


using cs.aworx.lox;
using cs.aworx.lib.enums;
using cs.aworx.lox.loggers;

namespace ut_cs_aworx_lox
{

class ManualSampleCode
{
// #################################################################################################
// ### Log Domains Samples
// #################################################################################################

public void Domains_Hierarchical()
{
//! [Man_DOMAINS___1]
Log.SetVerbosity( Log.DebugLogger, Verbosity.Error,   "/" ); // could also just omit parameter "/"
//! [Man_DOMAINS___1]

//! [Man_DOMAINS___2]
Log.SetVerbosity( Log.DebugLogger, Verbosity.Info,    "/UI" );
Log.SetVerbosity( Log.DebugLogger, Verbosity.Verbose, "/UI/DIALOGS" );
//! [Man_DOMAINS___2]

//! [Man_DOMAINS___2reverse]
Log.SetVerbosity( Log.DebugLogger, Verbosity.Verbose, "/UI/DIALOGS" );
Log.SetVerbosity( Log.DebugLogger, Verbosity.Info,    "/UI" );
//! [Man_DOMAINS___2reverse]
}


//! [Man_DOMAINS___3]
public void MyMethod()
{
    Log.SetDomain( "/MYDOM", Scope.Method );

    Log.Info( "This log statment uses domain /MYDOM" );
}
//! [Man_DOMAINS___3]
}

class ManualSampleCode2
{

//! [Man_DOMAINS___4]
public void MyMethod()
{
    Log.SetDomain( "/MYDOM", Scope.Method );

    Log.Info(           "This log statment uses domain '/MYDOM'" );
    Log.Info( "/MYDOM", "Of-course we can still use domains explicitly" );
}
//! [Man_DOMAINS___4]
}


class ManualSampleCode5
{

//! [Man_DOMAINS___5]
public void MyMethod()
{
    Log.SetDomain( "/MYDOM", Scope.Method );

    Log.Info(          "This log statment uses domain 'MYDOM'" );
    Log.Info( "MYDOM", "Oooops, this goes to '/MYDOM/MYDOM'!" );
}
//! [Man_DOMAINS___5]


public void TrimSource()
{
//! [Man_TRIM_SOURCE_PATH]
    Log.SetSourcePathTrimRule( "*/myapp/src/", Inclusion.Include );
//! [Man_TRIM_SOURCE_PATH]
}
}



// space to reach line 100
// space to reach line 100
// space to reach line 100
// space to reach line 100
// space to reach line 100
// space to reach line 100
// space to reach line 100
// space to reach line 100
// space to reach line 100

class ManualSampleCodeRelativePaths
{

//! [Man_DOMAINS___RelativePaths]
public void ReadChangeAndWriteBack()
{
    Log.SetDomain( "/IO", Scope.Method );

    // Reading file
    Log.Info( "READ",   "Reading file" );
    // ...
    // ...
    // ...

    // Process file
    Log.Info( "PROCESS",  "Processing data" );
    // ...
    // ...
    // ...

    // Writing file
    Log.Info( "./WRITE",  "Writing file" ); // note relative-path-prefix "./", same as if omitted (!)
    // ...
    // ...
    // ...

    Log.Info(  "Success!" );
}
//! [Man_DOMAINS___RelativePaths]

public void unnamed()
{
    //! [Man_DOMAINS___RelativePaths_Set]
    Log.SetVerbosity( Log.DebugLogger, Verbosity.Verbose, "./" );
    //! [Man_DOMAINS___RelativePaths_Set]
}
}

//! [Man_DOMAINS___nested_scope]
class IO
{
    // static constructor, setting the Scope Domain for this file (class) once
    static IO()
    {
        Log.SetDomain( "IO", Scope.Filename );
    }

    // interface
    public void ReadChangeAndWriteBack()
    {
        checkSetup();
        read();
        process();
        write();
        writeStats();
    }

    // private methods
    private  void checkSetup()
    {
        Log.SetDomain( "/CHECKS", Scope.Method );

        Log.Info(  "Setup OK!" );
    }


    private void read()
    {
        Log.SetDomain( "READ", Scope.Method );

        Log.Info("Reading file" );
    }

    private void process()
    {
        Log.SetDomain( "PROCESS", Scope.Method );

        Log.Info( "Processing data" );
    }

    private void write()
    {
        Log.SetDomain( "./WRITE", Scope.Method );

        Log.Info( "Writing file" );
    }

    private void writeStats()
    {
        Log.SetDomain( "../STATS", Scope.Method );

        Log.Info(  "Statistics" );
    }
}
//! [Man_DOMAINS___nested_scope]


// #################################################################################################
// ### Log.Once Samples
// #################################################################################################

class ManualSampleCodeLogOnce
{
public void Log_Once()
{
//! [Man_LogOnce___1]
Log.Once( "Kilroy was here!" );
//! [Man_LogOnce___1]

//! [Man_LogOnce___1_wrapup]
Log.Once( "This is what happened: ..." );
//! [Man_LogOnce___1_wrapup]

//! [Man_LogOnce___2]
Log.Once( "IO", "Directory given in config.ini not found. Using default." );
//! [Man_LogOnce___2]

//! [Man_LogOnce___3]
Log.Once( "IO", Verbosity.Warning, "I warn you... and I don't repeat myself!" );
//! [Man_LogOnce___3]

//! [Man_LogOnce___4]
Log.Once( "This is logged 10 times. After that, never again.", 10 );
//! [Man_LogOnce___4]

//! [Man_LogOnce___5]
Log.Once( "This is logged the first time and then every 100th invocation.", -100 );
//! [Man_LogOnce___5]
}

//! [Man_LogOnce___11]
public void ReadData()
{
    //...

    // directory not found
    Log.Once( "IO", Verbosity.Warning,
              "Directory given in config.ini not found. Using default." );
    //...
}

public void WriteData()
{
    //...

    // directory not found
    Log.Once( "IO", Verbosity.Warning,
              "Directory given in config.ini not found. Using default." );
    //...
}
//! [Man_LogOnce___11]


} // class ManualSampleCodeLogOnce

class ManualSampleCodeLogOnce2
{
//! [Man_LogOnce___12]
public void ReadData()
{
    //...

    // directory not found
    Log.Once( "IO", Verbosity.Warning,
              "Directory given in config.ini not found. Using default.",
              "INI_DIR_ERROR" );
    //...
}
public void WriteData()
{
    //...

    // directory not found
    Log.Once( "IO", Verbosity.Warning,
              "Directory given in config.ini not found. Using default.",
              "INI_DIR_ERROR" );
    //...
}
//! [Man_LogOnce___12]
} // class


//! [Man_LogOnce___21]
class MyIOManager
{
    // static constructor
    static MyIOManager()
    {
        // bind all log statements of this file to domain path 'IO'
        Log.SetDomain( "IO", Scope.Filename );
    }

    public void ReadData()
    {
        //...

        // directory not found
        Log.Once( Verbosity.Warning,
                  "Directory given in config.ini not found. Using default.",
                  Scope.Filename );
        //...
    }
    public void WriteData()
    {
        //...

        // directory not found
        Log.Once( Verbosity.Warning,
                  "Directory given in config.ini not found. Using default.",
                  Scope.Filename );
        //...
    }

} // class
//! [Man_LogOnce___21]



// #################################################################################################
// ### Log.SetPrefix Samples
// #################################################################################################

class RecursiveDataType
{
    public String                  Name;
    public List<RecursiveDataType> Children= new List<RecursiveDataType>();

    public RecursiveDataType() { Name= ""; }

public void Log_SetPrefix()
{
//! [Man_LogSetPrefix___1]
Log.SetPrefix( "Data File: ", Scope.Filename );
//...
//...
Log.Info( "Opened." );
//...
//...
Log.Info( "Read." );
//...
//...
Log.Info( "Closed." );
//! [Man_LogSetPrefix___1]

}

//! [Man_LogSetPrefix___2]
public RecursiveDataType Search( String name )
{
    Log.SetPrefix( "  ", Scope.ThreadOuter ); // add indent

    Log.Info( "Inspecting object: " + Name );

    if ( Name.Equals ( name ) )
    {
        Log.SetPrefix( null, Scope.ThreadOuter ); // remove indent
        return this;
    }

    // recursion
    RecursiveDataType returnValue= null;
    foreach( RecursiveDataType child in Children )
        if( (returnValue= child.Search( name )) != null )
            break;

    Log.SetPrefix( null, Scope.ThreadOuter ); // remove indent
    return returnValue;
}
//! [Man_LogSetPrefix___2]

}//class ManualSampleCodeSetPrefix


// #################################################################################################
// ### Man.InternalDomains Samples
// #################################################################################################

class Manual_InternalDomains
{
public void x()
{
//! [Man_InternalDomains___1]
Log.SetVerbosity( "DEBUG_LOGGER", Verbosity.Verbose, "/" );
//! [Man_InternalDomains___1]

//! [Man_InternalDomains___2]
Log.SetVerbosity( "DEBUG_LOGGER", Verbosity.Verbose, ALox.InternalDomains );
//! [Man_InternalDomains___2]

//! [Man_InternalDomains___3]
Log.SetVerbosity( "DEBUG_LOGGER", Verbosity.Verbose, "$/" );
//! [Man_InternalDomains___3]

//! [Man_InternalDomains___4]
Log.SetVerbosity( "DEBUG_LOGGER", Verbosity.Off    , ALox.InternalDomains );
Log.SetVerbosity( "DEBUG_LOGGER", Verbosity.Verbose, ALox.InternalDomains + "DMN" );
//! [Man_InternalDomains___4]

//! [Man_InternalDomains_ext___3]
Log.Info( ALox.InternalDomains + "MYDOM", "Hello, this logs 'on' internal domain '$/MYDOM'!" );
//! [Man_InternalDomains_ext___3]

}

}//class Manual_InternalDomains



// #################################################################################################
// ### Create manual sample output
// #################################################################################################

public class CS_Manual   : AWorxUnitTesting
{
    static MemoryLogger    memLog;
    static String          outputPath= UTSampleWriter.GetGeneratedSamplesDir();

    static CS_Manual()
    {
        CS_Manual.memLog = new MemoryLogger();
        memLog.MetaInfo.Format._()._( "%SF(%SL):%SM()%A3%V[%D]: " );
    }

    void SaveOutput( string fileName )
    {
        if ( outputPath.Length == 0 )
            return;
        #if !WINDOWS_PHONE
            System.IO.File.WriteAllText( outputPath + fileName,  memLog.MemoryLog.ToString() );
        #endif
        memLog.MemoryLog.Clear();
    }

    #if ALIB_MONO_DEVELOP
        [Test ()]
    #endif
    #if ALIB_VSTUDIO
        [TestMethod]
        #if !WINDOWS_PHONE
            [TestCategory("CS_ALox_Manual")]
        #endif
    #endif
    public void Man_Domains()
    {
        UT_INIT();

        // 3
        Log.SetVerbosity( memLog, Verbosity.Verbose );

        ManualSampleCode msc= new ManualSampleCode();
        msc.MyMethod();

        SaveOutput( "Man_Domains_3.txt" );



        // 5
        Log.Reset();
        Log.SetVerbosity( memLog, Verbosity.Verbose );

        // trick to pre-size domain field
        Log.Info("/MYDOM/MYDOM", "x" );
        memLog.MemoryLog.Clear();

        ManualSampleCode5 msc5= new ManualSampleCode5();
        msc5.MyMethod();

        SaveOutput( "Man_Domains_5.txt" );


        // relativePaths
        Log.Reset();
        Log.SetVerbosity( memLog, Verbosity.Verbose );

        // trick to pre-size domain field
        Log.Info("/IO/PROCESS", "x" );
        memLog.MemoryLog.Clear();

        ManualSampleCodeRelativePaths mscRP= new ManualSampleCodeRelativePaths();
        mscRP.ReadChangeAndWriteBack();

        SaveOutput( "Man_Domains_RelativePaths.txt" );

        // Man_DOMAINS___nested_scope
        Log.Reset();
        Log.SetVerbosity( memLog, Verbosity.Verbose );

        // trick to pre-size domain field
        memLog.AutoSizes.Reset();
        Log.Info("/IO/PROCESS", "x" );
        memLog.MemoryLog.Clear();

        IO io= new IO();
        io.ReadChangeAndWriteBack();

        SaveOutput( "Man_DOMAINS___nested_scope.txt" );
    }


    #if ALIB_MONO_DEVELOP
        [Test ()]
    #endif
    #if ALIB_VSTUDIO
        [TestMethod]
        #if !WINDOWS_PHONE
            [TestCategory("CS_ALox_Manual")]
        #endif
    #endif
    public void Man_Prefix()
    {
        UT_INIT();

        memLog.MemoryLog.Clear();
        memLog.AutoSizes.Reset();

        Log.SetVerbosity( memLog, Verbosity.Verbose );

        RecursiveDataType msc= new RecursiveDataType();
        msc.Log_SetPrefix();

        SaveOutput( "Man_LogSetPrefix_1.txt" );
    }

    #if ALIB_MONO_DEVELOP
        [Test ()]
    #endif
    #if ALIB_VSTUDIO
        [TestMethod]
        #if !WINDOWS_PHONE
            [TestCategory("CS_ALox_Manual")]
        #endif
    #endif
    public void Man_ExtVerbosityConfig()
    {
        UT_INIT();

        memLog.AutoSizes.Reset();


//! [Man_ExtVerbosityConfig___1]
Log.SetVerbosity( "DEBUG_LOGGER", Verbosity.Info, "/MYDOM", Configuration.PrioDefault + 1 );
Log.Info( "MYDOM", "This line will be logged" );

Log.SetVerbosity( "DEBUG_LOGGER", Verbosity.Off, "/MYDOM" );
Log.Info( "MYDOM", "This line will still be logged" );
//! [Man_ExtVerbosityConfig___1]

memLog.MemoryLog.Clear();

// Log.SetVerbosity( "DEBUG_LOGGER", Verbosity.Verbose, "$/" );

    Log.SetVerbosity( memLog, Verbosity.Info, "/MYDOM", Configuration.PrioDefault + 1 );
    Log.Info( "MYDOM", "This line will be logged" );
    
    Log.SetVerbosity( memLog, Verbosity.Off, "/MYDOM" );
    Log.Info( "MYDOM", "This line will still be logged" );

    SaveOutput( "Man_ExtVerbosityConfig_1.txt" );


//! [Man_ExtVerbosityConfig___2]
Log.SetVerbosity( "DEBUG_LOGGER", Verbosity.Verbose, ALox.InternalDomains );
//! [Man_ExtVerbosityConfig___2]

    Log.RemoveDebugLogger();
    Log.RemoveLogger(memLog);

    memLog.MemoryLog.Clear();
    Log.SetVerbosity( memLog, Verbosity.Verbose, ALox.InternalDomains );

    Log.SetVerbosity( memLog, Verbosity.Info, "/MYDOM", Configuration.PrioDefault + 1 );
    Log.Info( "MYDOM", "This line will be logged" );

    Log.SetVerbosity( memLog, Verbosity.Off, "/MYDOM" );
    Log.Info( "MYDOM", "This line will still be logged" );

    memLog.MemoryLog.SearchAndReplaceAll( "\"MEMORY\":      ", "\"DEBUG_LOGGER\":" );
    SaveOutput( "Man_ExtVerbosityConfig_2.txt" );

//! [Man_ExtVerbosityConfig___3]
Log.SetVerbosity( "DEBUG_LOGGER", Verbosity.Verbose, "/UI/MOUSE"        , Configuration.PrioDefault + 1 );
Log.SetVerbosity( "DEBUG_LOGGER", Verbosity.Verbose, "/UI/DIALOGS/MOUSE", Configuration.PrioDefault + 1 );
//! [Man_ExtVerbosityConfig___3]

    }




}

}
