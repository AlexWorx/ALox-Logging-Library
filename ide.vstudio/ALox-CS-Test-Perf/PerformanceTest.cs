using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using com.aworx.lox;
using com.aworx.util;

namespace ALox_CS_Test_Perf	 {

class PerformanceTest
{
	// #################################################################################################
	// static entrance (Main)
	// #################################################################################################
	static void Main( string[] args )
	{
		PerformanceTest test= new PerformanceTest();
		test.test();
	}

	#if ALOX_DEBUG || ALOX_REL_LOG

	// #################################################################################################
	// Fields
	// #################################################################################################
	ConsoleLogger cl;
	MemoryLogger  ml;

	#endif

	// #################################################################################################
	// Test functions
	// #################################################################################################
	
	void test()
	{
		#if ALOX_DEBUG || ALOX_REL_LOG
			cl=	new ConsoleLogger( "Console" ) { TabAfterSourceInfo = 60 };
			cl.EnableAppConsole=		true;
			cl.EnableVSDebugConsole=	false;
			ml= new MemoryLogger( "Memory");

			Log.AddLogger( cl, Log.DomainLevel.WarningsAndErrors );
			Log.AddLogger( ml, Log.DomainLevel.Off );
		#endif

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
		for ( int i= 0 ; i < 200 ; i++ )
		{
			#if ALOX_DEBUG || ALOX_REL_LOG
				ml.Buffer.Clear();
			#endif

			long t= Ticker.Now();
				simpleInfoLines( 1000 );
			t= Ticker.Now() - t;

			if ( fastest > t )
				fastest= t;

			Log.Line( Log.Level.Info, msgBuf.Clear().Append( "Pass " ).Append( i, 3).Append( " finished") );
		}

		Log.Line( Log.Level.Info, msgBuf.Clear().Append( "Fastest " ).Append( (int) Ticker.ToMillis( fastest ), 0).Append( " millis (").Append( (int) fastest ).Append( " ticks) per 1000 logs.") );
	}

	void simpleInfoLines( int qty )
	{
		for ( int i= 0 ; i < qty ; i++ )
			Log.Info( "MEM", "Test Line" );
	}


} // class
}
