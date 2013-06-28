package perftests.com.aworx.lox;

import com.aworx.util.*;
import com.aworx.lox.*;
import com.aworx.lox.loggers.ConsoleLogger;
import com.aworx.lox.loggers.MemoryLogger;

public class PerformanceTest
{


	// #################################################################################################
	// static entrance (Main)
	// #################################################################################################
	/**
	 * @param args
	 */
	public static void main(String[] args)
	{
		PerformanceTest test= new PerformanceTest();
		test.test();
	}

	// #################################################################################################
	// Fields
	// #################################################################################################
	ConsoleLogger cl;
	MemoryLogger  ml;

	// #################################################################################################
	// Test functions
	// #################################################################################################
	
	void test()
	{
		cl=	new ConsoleLogger( "Console" ); cl.tabAfterSourceInfo = 60;
		cl.enableAppConsole= true;
		ml= new MemoryLogger( "Memory");

		Log.addLogger( cl, Log.DomainLevel.WarningsAndErrors );
		Log.addLogger( ml, Log.DomainLevel.Off );

		Log.regDomain( "CON", Log.Scope.Method );
		Log.regDomain( "MEM", Log.Scope.None  );
		Log.regDomain( "BOTH",Log.Scope.None );

		Log.setDomain( "CON", Log.DomainLevel.All, true, "Console" );
		Log.setDomain( "MEM", Log.DomainLevel.Off, true, "Console" );
		Log.setDomain( "MEM", Log.DomainLevel.All, true, "Memory" );
		Log.setDomain( "CON", Log.DomainLevel.Off, true, "Memory" );
		Log.setDomain( "BOTH",Log.DomainLevel.All, true  );

		//Log.LogConfig( "CON", Log.Level.Info, "Log Config follows..." );
		

		Log.info( "Logging simple info lines" );
		MString msgBuf=		new MString( );
		long	fastest= 	Long.MAX_VALUE;
		for ( int i= 0 ; i < 200 ; i++ )
		{
			ml.buffer.clear();
			long t= Ticker.now();
				simpleInfoLines( 1000 );
			t= Ticker.now() - t;
			if ( fastest > t )
 				fastest= t;

			Log.line( Log.Level.Info, msgBuf.clear().append( "Pass " ).append( i, 3).append( " finished") );
		}

		Log.line( Log.Level.Info, msgBuf.clear().append( "Fastest " ).append( (int) Ticker.toMillis( fastest ), 0).append( " millis (").append( (int) fastest ).append( " ticks)  per 1000 logs.") );
	}

	void simpleInfoLines( int qty )
	{
		for ( int i= 0 ; i < qty ; i++ )
			Log.info( "MEM", "Test Line" );
	}

}
