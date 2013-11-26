using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using com.aworx.util;
using com.aworx.lox;
using com.aworx.lox.loggers;
using com.aworx.lox.tools;

namespace ALox_CS_Test_Perf	 {

class SimpleTests
{
	// #################################################################################################
	// static entrance (Main)
	// #################################################################################################
	static void Main( string[] args )
	{
		// create us
		SimpleTests test= new SimpleTests();
		
		// do some release logging tests. 
		Console.WriteLine( "PRINT: Release logging test:" );
			test.testReleaseLogging();
		Log.Reset();

		// do some performance tests. 
		Console.WriteLine( "PRINT: Performance test:" );
			test.performanceTest();
		Log.Reset();
		
		Console.WriteLine( "PRINT: Thats it!" );

	}

	// #################################################################################################
	// Fields
	// #################################################################################################
	ConsoleLogger cl;
	MemoryLogger  ml;

	// #################################################################################################
	// Test functions
	// #################################################################################################
	
	void performanceTest()
	{
		cl=	new ConsoleLogger();
		#if ALOX_DEBUG || ALOX_REL_LOG
			cl.EnableAppConsole=		true;
			cl.EnableVSDebugConsole=	false;
		#endif
		ml= new MemoryLogger();

		Log.AddLogger( cl, Log.DomainLevel.WarningsAndErrors );
		Log.AddLogger( ml, Log.DomainLevel.Off );

		Log.RegDomain( "CON", Log.Scope.SourceFile );
		Log.RegDomain( "MEM", Log.Scope.None  );
		Log.RegDomain( "BOTH",Log.Scope.None );

		Log.SetDomain( "CON", Log.DomainLevel.All, true, "Console" );
		Log.SetDomain( "MEM", Log.DomainLevel.Off, true, "Console" );
		Log.SetDomain( "MEM", Log.DomainLevel.All, true, "Memory" );
		Log.SetDomain( "CON", Log.DomainLevel.Off, true, "Memory" );
		Log.SetDomain( "BOTH",Log.DomainLevel.All, true  );


		Log.Info( "Logging simple info lines" );

		MString	msgBuf=		new MString( );
		long	fastest=	long.MaxValue;
		for ( int i= 0 ; i < 500 ; i++ )
		{
			#if ALOX_DEBUG || ALOX_REL_LOG
				ml.Buffer.Clear();
			#endif

			long t= Ticker.Now();
				simpleInfoLines( 1000 );
			t= Ticker.Now() - t;

			if ( fastest > t )
			{
				fastest= t;
				Log.Line( Log.Level.Info, msgBuf.Clear().Append( "Pass " ).Append( i, 3).Append( " is new fastest:  ")
														.Append( (int) Ticker.ToMillis( fastest ), 0).Append( " millis (").Append( (int) fastest ).Append( " ticks) per 1000 logs.") );
			}
		}

		Log.Line( Log.Level.Info, msgBuf.Clear().Append( "Fastest " ).Append( (int) Ticker.ToMillis( fastest ), 0).Append( " millis (").Append( (int) fastest ).Append( " ticks) per 1000 logs.") );
	}

	void simpleInfoLines( int qty )
	{
		for ( int i= 0 ; i < qty ; i++ )
			Log.Info( "MEM", "Test Line" );
	}

	public void testReleaseLogging()
	{
		// create a lox for release logging
		Lox				lox= 	new Lox();
		
		// add and configure a memory logger
		MemoryLogger	ml=			new MemoryLogger();
		#if ALOX_DEBUG || ALOX_REL_LOG
			ml.LineFormatter.Format= 	new MString( "[%TE]%L[%O]: ");
		#endif
		lox.AddLogger( ml, 	Log.DomainLevel.All );
		
		// We do not work with default domains, as we will obfuscate the code.
		// Obfuscated code and release logging does not allow default domains, because
		// the rely on caller information and reasonable package, class and method names
		lox.RegDomain( "RelLog",	Log.Scope.None );
		lox.SetDomain( "RelLog",	Log.DomainLevel.All  );

		// all log invocations provide the "domain" parameter explicitly to be safe when
		// obfuscation is enabled!
		lox.Info( "RelLog", "Hello ALox, thank you for providing release logging!" );
		lox.Info( "RelLog", "Let's see if LogTools is available." );
		lox.Info( "RelLog", "We need to provide our lox as a parameter to all LogTools methods!" );
		
		// instance() will not give very nice member names, if obfuscated!
		LogTools.Instance( "RelLog", Log.Level.Info, lox, 2, "Logging the Lox:", 0, lox );
		
		// also, the exception stack trace should be not too easy to read. Proguard provides a tool "retrace"...
		lox.Info( "RelLog", "Logging exceptions: " );
		LogTools.Exception( "RelLog", Log.Level.Error, new Exception("This is not a real Exception", new Exception("...unreal inner")), " Logging instance 'this':", 0, lox );

		lox.Info( "RelLog", "That's it for now. More release logging tests to come...stay tuned!" );

		// copy the memory logger's output to the console
		if ( ml.Buffer.Length > 0 ) 
			Console.WriteLine(  ml.Buffer.ToString() );
		else
			Console.WriteLine(  "  Even release logging got pruned - nothing logged!" );
	}


} // class
}
