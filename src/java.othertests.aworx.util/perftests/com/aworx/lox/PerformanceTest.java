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
		cl=	new ConsoleLogger( "Console" ); 
		ml= new MemoryLogger( "Memory");

		Log.addLogger( cl, Log.DomainLevel.WARNINGS_AND_ERRORS );
		Log.addLogger( ml, Log.DomainLevel.OFF );

		Log.regDomain( "CON", Log.Scope.METHOD );
		Log.regDomain( "MEM", Log.Scope.NONE  );
		Log.regDomain( "BOTH",Log.Scope.NONE );

		Log.setDomain( "CON", Log.DomainLevel.ALL, true, "Console" );
		Log.setDomain( "MEM", Log.DomainLevel.OFF, true, "Console" );
		Log.setDomain( "MEM", Log.DomainLevel.ALL, true, "Memory" );
		Log.setDomain( "CON", Log.DomainLevel.OFF, true, "Memory" );
		Log.setDomain( "BOTH",Log.DomainLevel.ALL, true  );

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

			Log.line( Log.Level.INFO, msgBuf.clear().append( "Pass " ).append( i, 3).append( " finished") );
		}

		Log.line( Log.Level.INFO, msgBuf.clear().append( "Fastest " ).append( (int) Ticker.toMillis( fastest ), 0).append( " millis (").append( (int) fastest ).append( " ticks)  per 1000 logs.") );
	}

	static void simpleInfoLines( int qty )
	{
		for ( int i= 0 ; i < qty ; i++ )
			Log.info( "MEM", "Test Line" );
	}

}
