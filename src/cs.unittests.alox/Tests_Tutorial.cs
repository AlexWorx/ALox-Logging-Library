using System;
using System.IO;
using System.Threading;
using System.Xml.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using com.aworx.lox.core;
using com.aworx.util;

//! [Tut_using_statement]
using com.aworx.lox;
//! [Tut_using_statement]

namespace com.aworx.unittests.lox
{

/** ***********************************************************************************************
* <summary>
*  Implements the tutorial code that with snippets markers for doxygen inclusion.
* </summary>
**************************************************************************************************/
[TestClass]
public class TestsTutorial
{
MemoryLogger	tutLog;
String			outputPath=		"../../../../src/doxygen.alox/generated_cstut/";

void SaveTutorialOuput( string fileName, MString log )
{
#if !WINDOWS_PHONE
	System.IO.File.WriteAllText( outputPath + "CS_" + fileName,  log.ToString() );
#endif
}

[TestMethod]
#if !WINDOWS_PHONE
	[TestCategory("Tutorial")]
#endif
public void Tut_Hello_ALox()
{
	Log.Reset(); 
	Log.AddLogger( tutLog= new MemoryLogger( "Tutlog" ) );
	tutLog.RootDomain.SetLevel( Log.DomainLevel.All, false );


	//! [Tut_Hello_ALox]
	//! [Tut_Hello_ALox_Line1]
	Log.AddLogger( new ConsoleLogger( "Console" ) );
	//! [Tut_Hello_ALox_Line1]
	//! [Tut_Hello_ALox_Line2]
	Log.SetDomain( "APP",	Log.DomainLevel.InfoWarningsAndErrors );
	//! [Tut_Hello_ALox_Line2]

	//! [Tut_Hello_ALox_Line3]
	Log.Info( "APP",	"Hello ALox" );
	//! [Tut_Hello_ALox_Line3]
	//! [Tut_Hello_ALox]
			
 	SaveTutorialOuput( "Tut_Hello_ALox.txt", tutLog.Buffer );
}

[TestMethod]
#if !WINDOWS_PHONE
	[TestCategory("Tutorial")]
#endif
public void Tut_LogLevels()
{
	Log.Reset(); 
	Log.AddLogger( tutLog= new MemoryLogger( "Tutlog"  ) );
	tutLog.RootDomain.SetLevel( Log.DomainLevel.All, false );

	//! [Tut_LogLevels]
	Log.AddLogger( new ConsoleLogger( "Console" ) );
	//! [Tut_LogLevels_SetDomain]
	Log.SetDomain( "APP",	Log.DomainLevel.InfoWarningsAndErrors );
	//! [Tut_LogLevels_SetDomain]

	Log.Error  ( "APP",	"A severe error happened :-(" );
	Log.Warning( "APP",	"This is a warning :-/ Maybe an error follows?" );
	Log.Info   ( "APP",	"Just for your further information!" );
	Log.Verbose( "APP",	"Today, I am in the mood to talk..." );
	//! [Tut_LogLevels]

 	SaveTutorialOuput( "Tut_LogLevels.txt", tutLog.Buffer );
}

[TestMethod]
#if !WINDOWS_PHONE
	[TestCategory("Tutorial")]
#endif
public void Tut_DefaultDomains()
{
	Log.Reset(); 
	Log.AddLogger( tutLog= new MemoryLogger( "Tutlog"  ) );
	tutLog.RootDomain.SetLevel( Log.DomainLevel.All, false );

	//! [Tut_DefaultDomains]
	Log.AddLogger( new ConsoleLogger( "Console" ) );
	Log.RegDomain( "APP", Log.Scope.SourceFile );
	Log.SetDomain( "APP", Log.DomainLevel.InfoWarningsAndErrors );

	Log.Error  ( "A severe error happened :-(" );
	Log.Warning( "This is a warning :-/ Maybe an error follows?" );
	Log.Info   ( "Just for your further information!" );
	Log.Verbose( "Today, I am in the mood to talk..." );
	//! [Tut_DefaultDomains]

 	SaveTutorialOuput( "Tut_DefaultDomains.txt", tutLog.Buffer );

	Log.Reset(); 
	Log.AddLogger( tutLog= new MemoryLogger( "Tutlog" ));
	tutLog.RootDomain.SetLevel( Log.DomainLevel.All, false );

	//! [Tut_DefaultDomains_part2]
	Log.AddLogger( new ConsoleLogger( "Console" ) );
	Log.Info  ( "APP", "Hallo ALox" );
	//! [Tut_DefaultDomains_part2]

	tutLog.Buffer.Replace( "Tutlog", "Console" );
 	SaveTutorialOuput( "Tut_DefaultDomains_part2.txt", tutLog.Buffer );
}

public void Tut_Placing()
{
	//! [Tut_Placing_Part1]
	Log.AddLogger( new ConsoleLogger( "Console" ) );

	Log.SetDomain( "MYAPP",     Log.DomainLevel.All);
	Log.SetDomain( "SOCKETS",   Log.DomainLevel.WarningsAndErrors );
	Log.SetDomain( "UI",        Log.DomainLevel.Errors );
	Log.SetDomain( "UI/DLGS",   Log.DomainLevel.InfoWarningsAndErrors );
	Log.SetDomain( "3DCALC",    Log.DomainLevel.Off  );
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

//! [Tut_Placing_Part2]
class MyClass
{
	// static constructor to register log domains
	static MyClass() 
	{
		Log.RegDomain( "MYDOM",			Log.Scope.SourceFile );		
		Log.RegDomain( "MYDOM/PERF",	Log.Scope.None);		
	}

	// Here comes the class
	//...
	//...
}
//! [Tut_Placing_Part2]
		
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

[TestMethod]
#if !WINDOWS_PHONE
	[TestCategory("Tutorial")]
#endif
public void Tut_Instance()
{
#if ALOX_DEBUG || ALOX_REL_LOG
	Log.Reset(); 
	Log.AddLogger( new ConsoleLogger( "Console" ) );
	Log.AddLogger( tutLog= new MemoryLogger( "Tutlog" ), Log.DomainLevel.Off  );
	Log.SetDomain( "MYDOM", Log.DomainLevel.All );
	tutLog.RootDomain.SetLevel( Log.DomainLevel.All, false );
	tutLog.MultiLineMsgMode= 4;

	//! [Tut_Instance]
	// Log multi-lines without indent 
	((TextLogger) Log.GetLogger( "Console" )).MultiLineMsgMode= 4; 

	// Log current thread instance
	LogTools.Instance( "MYDOM", Log.Level.Info, Thread.CurrentThread, 2, "Actual Thread: ", 1 );
	//! [Tut_Instance]

	int lines= 32;
	int idx= 0;
	while (lines-- != 0)
	{
		idx= tutLog.Buffer.IndexOf( Environment.NewLine, idx + Environment.NewLine.Length );
		if ( idx < 0 )
			break;
	}
	if (idx > 0)
		tutLog.Buffer.Length= idx + Environment.NewLine.Length;
	tutLog.Buffer.Append( "..." ).Append( Environment.NewLine );
	tutLog.Buffer.Append( "..." ).Append( Environment.NewLine );
	tutLog.Buffer.Append( "..." ).Append( Environment.NewLine );
 	SaveTutorialOuput( "Tut_Instance.txt", tutLog.Buffer );
#endif
}

[TestMethod]
#if !WINDOWS_PHONE
	[TestCategory("Tutorial")]
#endif
public void Tut_Exception()
{
#if ALOX_DEBUG || ALOX_REL_LOG
	Log.Reset(); 
	Log.AddLogger( tutLog= new MemoryLogger( "Tutlog" ), Log.DomainLevel.Off  );
	tutLog.RootDomain.SetLevel( Log.DomainLevel.WarningsAndErrors, false );

	//! [Tut_Exceptions]
	Exception testException=  new Exception( "TestException Message", 
												new Exception ( "InnerException Message", 
																new Exception("Inner, inner Exception") ) );
	LogTools.Exception( "MYDOM", Log.Level.Warning, testException, "Logging an exception: " );
	//! [Tut_Exceptions]

	tutLog.Buffer.Replace( "Tutlog", "Console" );
 	SaveTutorialOuput( "Tut_Exceptions.txt", tutLog.Buffer );
#endif
}

[TestMethod]
#if !WINDOWS_PHONE
	[TestCategory("Tutorial")]
#endif
public void Tut_XML()
{
#if ALOX_DEBUG || ALOX_REL_LOG
	Log.Reset(); 
	Log.AddLogger( tutLog= new MemoryLogger( "Tutlog" ), Log.DomainLevel.Off  );
	tutLog.RootDomain.SetLevel( Log.DomainLevel.All, false );

	//! [Tut_XML]
	String xmltext= "<MainTag>" 
						+"<SubTag>Hallo ALox XML</SubTag>"
						+"<SubTag2>"
							+"<SubsubTag>A sub tags' string</SubsubTag>"
						+"</SubTag2>"
					+"</MainTag>";
	XDocument xdoc= XDocument.Parse( xmltext );
    
	LogTools.XML("MYDOM", Log.Level.Info, xdoc, "Logging an xml document: " );
	//! [Tut_XML]

	tutLog.Buffer.Replace( "Tutlog", "Console" );
 	SaveTutorialOuput( "Tut_XML.txt", tutLog.Buffer );
#endif
}


[TestMethod]
#if !WINDOWS_PHONE
	[TestCategory("Tutorial")]
#endif
public void Tut_SeparatedLogLevels()
{
#if ALOX_DEBUG || ALOX_REL_LOG
	Log.Reset(); 
	Log.AddLogger( tutLog= new MemoryLogger( "Tutlog" ), Log.DomainLevel.Off  );
	Log.SetDomain( "MYDOM", Log.DomainLevel.All );
	tutLog.RootDomain.SetLevel( Log.DomainLevel.Off, false );
	tutLog.MultiLineMsgMode= 4;
	Log.SetDomain( "DOM",  Log.DomainLevel.All );
	Log.SetDomain( "DOM/CON", Log.DomainLevel.All, false, "Tutlog" );
	Log.SetDomain( "DOM/MEM", Log.DomainLevel.Off, false, "Tutlog" );


	//! [Tut_SeparatedLogLevels]
	// create two different loggers
	Log.AddLogger( new ConsoleLogger( "Console" ) );
	Log.AddLogger( new MemoryLogger ( "Memory" ) );
    
	// switch some log information off with memory logger
	#if ALOX_DEBUG
		(Log.GetLogger("Console")).LogCallerInfo= false;
		MemoryLogger memLogger= (MemoryLogger) Log.GetLogger("Memory");
		memLogger.LogCallerInfo= 
		memLogger.LogTimeElapsed= 
		memLogger.LogTimeDiff= 
		memLogger.LogLogLevel= 
		memLogger.LogThreadInfo= false;
	#endif
    
	// register domains, set DOM as default
	Log.RegDomain( "DOM",     Log.Scope.Method );
	Log.RegDomain( "DOM/CON", Log.Scope.None );
	Log.RegDomain( "DOM/MEM", Log.Scope.None );
    
	// set level of DOM for all loggers
	Log.SetDomain( "DOM",  Log.DomainLevel.All, false );
    
	// set level of DOM/CON separately for console and memory logger
	Log.SetDomain( "~CON", Log.DomainLevel.All, false, "Console" );
	Log.SetDomain( "~CON", Log.DomainLevel.Off, false, "Memory"  );
    
	// set level of DOM/MEM separately for console and memory logger
	Log.SetDomain( "~MEM", Log.DomainLevel.Off, false, "Console" );
	Log.SetDomain( "~MEM", Log.DomainLevel.All, false, "Memory"  );
    
	// Log info to each of the domains
	Log.Info(         "Domain= DOM      -> This goes to all loggers");
	Log.Info( "~CON", "Domain= DOM/CON  -> This goes to ConsoleLogger exclusively");
	Log.Info( "~MEM", "Domain= DOM/MEM  -> This goes to MemoryLogger exclusively");
    
	// To verify the result, we log the contents of the MemoryLogger to the console logger
	Log.Info( "~CON", "Here comes the contents of MemoryLogger:");
	Log.Info( "~CON", memLogger.Buffer.ToString(), 1);
	//! [Tut_SeparatedLogLevels]

	tutLog.Buffer.Replace( "Tutlog", "Console" );
	SaveTutorialOuput( "Tut_SeparatedLogLevels.txt", tutLog.Buffer );
#endif
}


[TestMethod]
#if !WINDOWS_PHONE
	[TestCategory("Tutorial")]
#endif
public void Tut_LogConfig()
{
#if ALOX_DEBUG || ALOX_REL_LOG
	Log.Reset(); 

	//! [Tut_LogConfig]
	// create two different loggers
	Log.AddLogger( new ConsoleLogger( "Console" ) );
	Log.AddLogger( new MemoryLogger ( "Memory" ) );
    
	// register domains, set DOM as default
	Log.RegDomain( "DOM",     Log.Scope.Method );
	Log.RegDomain( "DOM/CON", Log.Scope.None );
	Log.RegDomain( "DOM/MEM", Log.Scope.None );
    
	// set level of DOM for all loggers
	Log.SetDomain( "DOM", Log.DomainLevel.All );
    
	// set level of DOM/CON separately for console and memory logger
	Log.SetDomain( "~CON", Log.DomainLevel.All, false, "Console" );
	Log.SetDomain( "~CON", Log.DomainLevel.Off, false, "Memory"  );
    
	// set level of DOM/MEM separately for console and memory logger
	Log.SetDomain( "~MEM", Log.DomainLevel.Off, false, "Console" );
	Log.SetDomain( "~MEM", Log.DomainLevel.All, false, "Memory"  );
    
	// Log current Log configuration 
	Log.LogConfig( "DOM", Log.Level.Verbose, "Here comes the current Log configuration:" );
	//! [Tut_LogConfig]

	//tutLog.Buffer.Replace( "Tutlog", "Console" );
	SaveTutorialOuput( "Tut_LogConfig.txt", ((MemoryLogger) Log.GetLogger( "Memory" )).Buffer );
#endif
}



[TestMethod]
#if !WINDOWS_PHONE
	[TestCategory("Tutorial")]
#endif
public void Tut_LogConfig2()
{
#if ALOX_DEBUG || ALOX_REL_LOG
	Log.Reset(); 

	// ##### code inclusion version ########
	//! [Tut_LogConfig2]
	// create two different loggers, add console Logger verbosely
	Log.AddLogger( new ConsoleLogger( "Console" ), Log.DomainLevel.All );
	Log.AddLogger( new MemoryLogger ( "Memory" )  );
    
	// register domains, set DOM as default
	Log.RegDomain( "DOM",     Log.Scope.Method );
	Log.RegDomain( "DOM/CON", Log.Scope.None );
	Log.RegDomain( "DOM/MEM", Log.Scope.None );
    
	// set level of DOM for all loggers
	Log.SetDomain( "DOM", Log.DomainLevel.All );
    
	// set level of DOM/CON separately for console and memory logger
	Log.SetDomain( "~CON", Log.DomainLevel.All, false, "Console" );
	Log.SetDomain( "~CON", Log.DomainLevel.Off, false, "Memory"  );
    
	// set level of DOM/MEM separately for console and memory logger
	Log.SetDomain( "~MEM", Log.DomainLevel.Off, false, "Console" );
	Log.SetDomain( "~MEM", Log.DomainLevel.All, false, "Memory"  );

	//! [Tut_LogConfig2]

	// ##### output generation version - the only difference is that memory logger gets all messages ########
	Log.Reset(); 

	// create two different loggers, add console Logger verbosely
	tutLog= new MemoryLogger ( "Console" );
	tutLog.RootDomain.SetLevel( Log.DomainLevel.All, false );
	Log.AddLogger( tutLog, Log.DomainLevel.All ); 
	Log.AddLogger( new ConsoleLogger( "Memory" ) );
    
	// register domains, set DOM as default
	Log.RegDomain( "DOM",     Log.Scope.Method );
	Log.RegDomain( "DOM/CON", Log.Scope.None );
	Log.RegDomain( "DOM/MEM", Log.Scope.None );
    
	// set level of DOM for all loggers
	Log.SetDomain( "DOM", Log.DomainLevel.All );
    
	// set level of DOM/CON separately for console and memory logger
	Log.SetDomain( "~CON", Log.DomainLevel.All, false, "Console" );
	Log.SetDomain( "~CON", Log.DomainLevel.Off, false, "Memory"  );
    
	// set level of DOM/MEM separately for console and memory logger
	Log.SetDomain( "~MEM", Log.DomainLevel.Off, false, "Console" );
	Log.SetDomain( "~MEM", Log.DomainLevel.All, false, "Memory"  );

	//tutLog.Buffer.Replace( "Tutlog", "Console" );
	SaveTutorialOuput( "Tut_LogConfig2.txt", ((MemoryLogger) Log.GetLogger( "Console" )).Buffer );


	//! [Tut_LogConfig3]
	Log.SetDomain( "ALOX", Log.DomainLevel.All, true, "Console");
	//! [Tut_LogConfig3]

	//! [Tut_LogConfig4]
	Log.SetDomain( Log.LOX.InternalDomain, Log.DomainLevel.All, true, "Console");
	//! [Tut_LogConfig4]
#endif
}
	}
}
