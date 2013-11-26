package tests.com.aworx.lox;


import com.aworx.util.*;
import com.aworx.lox.*;
import com.aworx.lox.loggers.ConsoleLogger;
import com.aworx.lox.loggers.MemoryLogger;
import com.aworx.lox.tools.LogTools;


public class SimpleTests
{


	// #################################################################################################
	// static entrance (Main)
	// #################################################################################################
	/**
	 *  In-between the different tests, we have to do some System.out.println() here to have at least 
	 *  a minimum output after pruning ALox (as this software does not do anything but logging).
	 *  
	 * @param args
	 */
	public static void main(String[] args)
	{
	
		// create us
		SimpleTests test= new SimpleTests();
		
		// do some release logging tests. 
		System.out.println( "PRINT: Release logging test:" );
			test.testReleaseLogging();
		Log.reset();

		// do some performance tests. 
		System.out.println( "PRINT: Performance test:" );
			test.performanceTest();
		Log.reset();
		
		System.out.println( "PRINT: Thats it!" );
	}

	// #################################################################################################
	// Fields
	// #################################################################################################

	// #################################################################################################
	// Test functions
	// #################################################################################################
	
	void performanceTest()
	{
		ConsoleLogger cl=	new ConsoleLogger( "Console" ); 
		MemoryLogger  ml= new MemoryLogger( "Memory");

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
		long	fastest= 	Long.MAX_VALUE;
		for ( int i= 0 ; i < 500 ; i++ )
		{
			ml.buffer.clear();
			long t= Ticker.now();
				simpleInfoLines( 1000 );
			t= Ticker.now() - t;
			if ( fastest > t )
			{
				fastest= t;
				Log.line( "CON", Log.Level.INFO, Log.buf()	.append( "Pass " ).append( i, 3).append( " is new fastest:  ")
															.append( (int) Ticker.toMillis( fastest ), 0).append( " millis (").append( (int) fastest ).append( " ticks) per 1000 logs.") );
			}

		}

		Log.line( Log.Level.INFO, Log.buf()	.append( "Fastest " ).append( (int) Ticker.toMillis( fastest ), 0).append( " millis (").append( (int) fastest ).append( " ticks)  per 1000 logs.") );
	}

	static void simpleInfoLines( int qty )
	{
		for ( int i= 0 ; i < qty ; i++ )
			Log.info( "MEM", "Test Line" );
	}


	public void testReleaseLogging()
	{
		// create a lox for release logging
		Lox				lox= 	new Lox();
		
		// add and configure a memory logger
		MemoryLogger	ml=			new MemoryLogger();
		ml.lineFormatter.format= 	new MString( "[%TE]%L[%O]: ");
		lox.addLogger( ml, 	Log.DomainLevel.ALL );
		
		// We do not work with default domains, as we will obfuscate the code.
		// Obfuscated code and release logging does not allow default domains, because
		// the rely on caller information and reasonable package, class and method names
		lox.regDomain( "RelLog",	Log.Scope.NONE );
		lox.setDomain( "RelLog",	Log.DomainLevel.ALL  );

		// all log invocations provide the "domain" parameter explicitly to be safe when
		// obfuscation is enabled!
		lox.info( "RelLog", "Hello ALox, thank you for providing release logging!" );
		lox.info( "RelLog", "Let's see if LogTools is available." );
		lox.info( "RelLog", "We need to provide our lox as a parameter to all LogTools methods!" );
		
		// instance() will not give very nice member names, if obfuscated!
		LogTools.instance( "RelLog", Log.Level.INFO, lox, 2, "Logging the Lox:", 0, lox );
		
		// also, the exception stack trace should be not too easy to read. Proguard provides a tool "retrace"...
		lox.info( "RelLog", "Logging exceptions: " );
		LogTools.exception( "RelLog", Log.Level.ERROR, new Exception("This is not a real Exception", new Exception("...unreal inner")), " Logging instance 'this':", 0, lox );

		lox.info( "RelLog", "That's it for now. More release logging tests to come...stay tuned!" );

		// copy the memory logger's output to the console
		if ( ml.buffer.length > 0 ) 
			System.out.println(  ml.buffer.toString() );
		else
			System.out.println(  "  Even release logging got pruned - nothing logged!" );
	}

}
