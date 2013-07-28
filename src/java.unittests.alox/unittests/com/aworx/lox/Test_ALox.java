package unittests.com.aworx.lox;

import static org.junit.Assert.*;

import java.util.LinkedList;

import org.junit.Test;

import com.aworx.lox.*;
import com.aworx.lox.core.TextLoggerLineFormatter;
import com.aworx.lox.loggers.ConsoleLogger;
import com.aworx.lox.loggers.MemoryLogger;
import com.aworx.util.*;


public class Test_ALox
{
	/** ***********************************************************************************************
	 * 	The loggers.
	 **************************************************************************************************/
	public ConsoleLogger	cl;
	public MemoryLogger		ml;

	/** ***********************************************************************************************
	 * 	Creates loggers.
	 **************************************************************************************************/
	public void   clearCreateAndAddLoggers( boolean memoryLogger, boolean consoleLogger)
	{
		Log.reset();
		cl= null;
		ml= null;

		if ( consoleLogger )
		{
			cl=		new ConsoleLogger();
			Log.addLogger( cl, Log.DomainLevel.ALL );

			//cl.EnableAppConsole=		true;
			//cl.EnableVSDebugConsole=	true;
		}

		if ( memoryLogger )
		{
			ml=		new MemoryLogger( "Memory" );
			Log.addLogger( ml, Log.DomainLevel.OFF );
		}

		Log.mapThreadName( "UnitTest" );
	}
	public void   clearCreateAndAddLoggers( boolean memoryLogger )	{ clearCreateAndAddLoggers( memoryLogger, true ); }
	public void   clearCreateAndAddLoggers()						{ clearCreateAndAddLoggers( false, true ); }


	/** ***********************************************************************************************
	 * 	Log_TestLogLevelSetting
	 **************************************************************************************************/
	@SuppressWarnings("static-method")
	@Test 
	public void Log_TestTextLoggerTimeDiff()
	{
		class T extends TextLoggerLineFormatter
		{
			public 	  void 	t( MString buf, long diff ) 		{ writeTimeDiff( buf, diff ); }
		}
		
		T t= new T();
		MString ms= new MString();
		long diff;
		long millis= 	1000L;
		long secs=		1000L * millis;
		long mins=		60 * secs;
		long hours=		60 * mins;
		long days=		24 * hours;
		
		
		diff= 0; 							ms.clear(); t.t( ms, diff ); assertEquals(  "000"  + t.timeDiffMicros,	ms.toString(0,  ms.length ) );
		diff= 15; 							ms.clear(); t.t( ms, diff ); assertEquals(  "015"  + t.timeDiffMicros,	ms.toString(0,  ms.length ) );
		diff= 99; 							ms.clear(); t.t( ms, diff ); assertEquals(  "099"  + t.timeDiffMicros,	ms.toString(0,  ms.length ) );
		diff= 600; 							ms.clear(); t.t( ms, diff ); assertEquals(  "600"  + t.timeDiffMicros,	ms.toString(0,  ms.length ) );
		diff= 999; 							ms.clear(); t.t( ms, diff ); assertEquals(  "999"  + t.timeDiffMicros,	ms.toString(0,  ms.length ) );
		diff= 1   * millis;					ms.clear(); t.t( ms, diff ); assertEquals(  "001"  + t.timeDiffMillis,	ms.toString(0,  ms.length ) );
		diff= 999 * millis;					ms.clear(); t.t( ms, diff ); assertEquals(  "999"  + t.timeDiffMillis,	ms.toString(0,  ms.length ) );
		diff= 1   * secs;					ms.clear(); t.t( ms, diff ); assertEquals(  "1.00" + t.timeDiffSecs,		ms.toString(0,  ms.length ) );
		diff= 2   * secs + 344 * millis;	ms.clear(); t.t( ms, diff ); assertEquals(  "2.34" + t.timeDiffSecs,		ms.toString(0,  ms.length ) );
		diff= 3   * secs + 345 * millis;	ms.clear(); t.t( ms, diff ); assertEquals(  "3.35" + t.timeDiffSecs,		ms.toString(0,  ms.length ) );
		diff= 9   * secs + 994 * millis;	ms.clear(); t.t( ms, diff ); assertEquals(  "9.99" + t.timeDiffSecs,		ms.toString(0,  ms.length ) );
		diff= 9   * secs + 995 * millis;	ms.clear(); t.t( ms, diff ); assertEquals(  "10.0" + t.timeDiffSecs,		ms.toString(0,  ms.length ) );
		diff= 9   * secs + 999 * millis;	ms.clear(); t.t( ms, diff ); assertEquals(  "10.0" + t.timeDiffSecs,		ms.toString(0,  ms.length ) );
		diff= 10  * secs + 940 * millis;	ms.clear(); t.t( ms, diff ); assertEquals(  "10.9" + t.timeDiffSecs,		ms.toString(0,  ms.length ) );
		diff= 10  * secs + 950 * millis;	ms.clear(); t.t( ms, diff ); assertEquals(  "11.0" + t.timeDiffSecs,		ms.toString(0,  ms.length ) );
		
		diff= 99  * secs + 900 * millis;	ms.clear(); t.t( ms, diff ); assertEquals(  "99.9" + t.timeDiffSecs,		ms.toString(0,  ms.length ) );
		diff= 99  * secs + 949 * millis;	ms.clear(); t.t( ms, diff ); assertEquals(  "99.9" + t.timeDiffSecs,		ms.toString(0,  ms.length ) );

//		diff= 99  * secs + 950 * millis;	ms.Clear(); t.t( ms, diff ); assertEquals(  "99.9" + t.fmtTimeDiffSecs,		ms.toString(0,  ms.Length ) );

		diff= 2  * mins + 0 * secs;			ms.clear(); t.t( ms, diff ); assertEquals(  "2.00" + t.timeDiffMins,		ms.toString(0,  ms.length ) );
		diff= 2  * mins + 30 * secs;		ms.clear(); t.t( ms, diff ); assertEquals(  "2.50" + t.timeDiffMins,		ms.toString(0,  ms.length ) );
		diff= 9  * mins + 45 * secs;		ms.clear(); t.t( ms, diff ); assertEquals(  "9.75" + t.timeDiffMins,		ms.toString(0,  ms.length ) );
		diff= 9  * mins + 59 * secs;		ms.clear(); t.t( ms, diff ); assertEquals(  "9.98" + t.timeDiffMins,		ms.toString(0,  ms.length ) );
		diff= 9  * mins + 59500 * millis;	ms.clear(); t.t( ms, diff ); assertEquals(  "9.99" + t.timeDiffMins,		ms.toString(0,  ms.length ) );
		diff= 9  * mins + 59999 * millis;	ms.clear(); t.t( ms, diff ); assertEquals(  "10.0" + t.timeDiffMins,		ms.toString(0,  ms.length ) );

		diff= 99 * mins + 0 * secs;			ms.clear(); t.t( ms, diff ); assertEquals(  "99.0" + t.timeDiffMins,		ms.toString(0,  ms.length ) );
		diff= 99 * mins + 30* secs;			ms.clear(); t.t( ms, diff ); assertEquals(  "99.5" + t.timeDiffMins,		ms.toString(0,  ms.length ) );
		diff= 99 * mins + 59* secs;			ms.clear(); t.t( ms, diff ); assertEquals(  "99.9" + t.timeDiffMins,		ms.toString(0,  ms.length ) );
		diff= 99 * mins + 59500* millis;	ms.clear(); t.t( ms, diff ); assertEquals(  "99.9" + t.timeDiffMins,		ms.toString(0,  ms.length ) );
		diff= 99 * mins + 59999* millis;	ms.clear(); t.t( ms, diff ); assertEquals(  "1.66" + t.timeDiffHours,	ms.toString(0,  ms.length ) );
		diff= 1 * hours + 30* mins;			ms.clear(); t.t( ms, diff ); assertEquals(  "90.0" + t.timeDiffMins,		ms.toString(0,  ms.length ) );

		diff= 5 * hours + 30* mins;			ms.clear(); t.t( ms, diff ); assertEquals(  "5.50" + t.timeDiffHours,	ms.toString(0,  ms.length ) );
	
		diff= 9 * hours + 45* mins;			ms.clear(); t.t( ms, diff ); assertEquals(  "9.75" + t.timeDiffHours,	ms.toString(0,  ms.length ) );
		diff= 9 * hours + 59* mins;			ms.clear(); t.t( ms, diff ); assertEquals(  "9.98" + t.timeDiffHours,	ms.toString(0,  ms.length ) );
		diff= 9 * hours + 3540* secs;		ms.clear(); t.t( ms, diff ); assertEquals(  "9.98" + t.timeDiffHours,	ms.toString(0,  ms.length ) );
		diff= 9 * hours + 3580* secs;		ms.clear(); t.t( ms, diff ); assertEquals(  "9.99" + t.timeDiffHours,	ms.toString(0,  ms.length ) );
		diff= 9 * hours + 3599* secs;		ms.clear(); t.t( ms, diff ); assertEquals(  "9.99" + t.timeDiffHours,	ms.toString(0,  ms.length ) );
		diff= 9 * hours + 3600* secs;		ms.clear(); t.t( ms, diff ); assertEquals(  "10.0" + t.timeDiffHours,	ms.toString(0,  ms.length ) );
		
		diff= 50 * hours + 15 *mins;		ms.clear(); t.t( ms, diff ); assertEquals(  "50.2" + t.timeDiffHours,	ms.toString(0,  ms.length ) );
		diff= 99 * hours + 45 *mins;		ms.clear(); t.t( ms, diff ); assertEquals(  "99.7" + t.timeDiffHours,	ms.toString(0,  ms.length ) );
		diff= 99 * hours + 48 *mins;		ms.clear(); t.t( ms, diff ); assertEquals(  "99.8" + t.timeDiffHours,	ms.toString(0,  ms.length ) );
		diff= 99 * hours + 59 *mins;		ms.clear(); t.t( ms, diff ); assertEquals(  "99.9" + t.timeDiffHours,	ms.toString(0,  ms.length ) );
		diff= 99 * hours + 3540* secs;		ms.clear(); t.t( ms, diff ); assertEquals(  "99.9" + t.timeDiffHours,	ms.toString(0,  ms.length ) );
		diff= 99 * hours + 3580* secs;		ms.clear(); t.t( ms, diff ); assertEquals(  "99.9" + t.timeDiffHours,	ms.toString(0,  ms.length ) );
		diff= 99 * hours + 3599* secs;		ms.clear(); t.t( ms, diff ); assertEquals(  "99.9" + t.timeDiffHours,	ms.toString(0,  ms.length ) );
		diff= 99 * hours + 3600* secs;		ms.clear(); t.t( ms, diff ); assertEquals(  "4.16" + t.timeDiffDays,		ms.toString(0,  ms.length ) );

		diff= 1 * days + 12* hours;			ms.clear(); t.t( ms, diff ); assertEquals(  "36.0" + t.timeDiffHours,	ms.toString(0,  ms.length ) );

		diff= 5 * days + 18* hours;			ms.clear(); t.t( ms, diff ); assertEquals(  "5.75" + t.timeDiffDays,		ms.toString(0,  ms.length ) );
		diff= 9 * days + 23* hours;			ms.clear(); t.t( ms, diff ); assertEquals(  "9.95" + t.timeDiffDays,		ms.toString(0,  ms.length ) );
		diff= 9 * days + 1380 * mins;		ms.clear(); t.t( ms, diff ); assertEquals(  "9.95" + t.timeDiffDays,		ms.toString(0,  ms.length ) );
		diff= 9 * days + 1400 * mins;		ms.clear(); t.t( ms, diff ); assertEquals(  "9.97" + t.timeDiffDays,		ms.toString(0,  ms.length ) );
		diff= 9 * days + 1439 * mins;		ms.clear(); t.t( ms, diff ); assertEquals(  "9.99" + t.timeDiffDays,		ms.toString(0,  ms.length ) );
		diff= 9 * days + 1440 * mins;		ms.clear(); t.t( ms, diff ); assertEquals(  "10.0" + t.timeDiffDays,		ms.toString(0,  ms.length ) );
		diff= 15 * days + 6 * hours;		ms.clear(); t.t( ms, diff ); assertEquals(  "15.2" + t.timeDiffDays,		ms.toString(0,  ms.length ) );
		diff= 99 * days + 18 * hours;		ms.clear(); t.t( ms, diff ); assertEquals(  "99.7" + t.timeDiffDays,		ms.toString(0,  ms.length ) );
		diff= 99 * days + 1439 * mins;		ms.clear(); t.t( ms, diff ); assertEquals(  "99.9" + t.timeDiffDays,		ms.toString(0,  ms.length ) );
		diff= 99 * days + 1440 * mins;		ms.clear(); t.t( ms, diff ); assertEquals(  "100.0"+ t.timeDiffDays,	ms.toString(0,  ms.length ) );

		diff= 13452 * days + 12* hours;		ms.clear(); t.t( ms, diff ); assertEquals("13452.5"+ t.timeDiffDays,	ms.toString(0,  ms.length ) );
		//System.out.println(ms.toString());		
	}
	
	/** ***********************************************************************************************
	 * 	Log_TestLogLevelSetting
	 **************************************************************************************************/
	@Test 
	public void Log_TestLogLevelSetting()
	{
			clearCreateAndAddLoggers();

			Log.regDomain( "TLLS", Log.Scope.METHOD );
			Log.setDomain( Log.LOX.internalDomain, Log.DomainLevel.OFF );

			// Test log level setting
			int logLinesBefore= cl.cntLogs;
			Log.setDomain( "TLLS", Log.DomainLevel.ALL );
			Log.verbose	   ( "TLLS", "This Verbose line should be logged" );
			Log.info	   ( "TLLS", "This Info    line should be logged" );
			Log.warning	   ( "TLLS", "This WARN    line should be logged" );
			Log.error	   ( "TLLS", "This Error   line should be logged" );

			Log.setDomain( "TLLS", Log.DomainLevel.INFO_WARNINGS_AND_ERRORS );
			Log.verbose	   ( "TLLS", "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
			Log.info	   ( "TLLS", "This Info    line should be logged" );
			Log.warning	   ( "TLLS", "This Warning line should be logged" );
			Log.error	   ( "TLLS", "This Error   line should be logged" );


			Log.setDomain( "TLLS", Log.DomainLevel.WARNINGS_AND_ERRORS );
			Log.verbose	   ( "TLLS", "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
			Log.info	   ( "TLLS", "This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
			Log.warning	   ( "TLLS", "This Warning line should be logged" );
			Log.error	   ( "TLLS", "This Error   line should be logged" );

			Log.setDomain( "TLLS", Log.DomainLevel.ERRORS );
			Log.verbose	   ( "TLLS", "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
			Log.info	   ( "TLLS", "This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
			Log.warning	   ( "TLLS", "This Warning line should NOT be logged. !!!!!Test Error!!!!!" );
			Log.error	   ( "TLLS", "This Error   line should be logged" );
			
			Log.setDomain( "TLLS", Log.DomainLevel.OFF );
			Log.verbose	   ( "TLLS", "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
			Log.info	   ( "TLLS", "This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
			Log.warning	   ( "TLLS", "This Warning line should NOT be logged. !!!!!Test Error!!!!!" );
			Log.error	   ( "TLLS", "This Error   line should NOT be logged. !!!!!Test Error!!!!!" );

			assertEquals( 10, cl.cntLogs - logLinesBefore );
	}
	
	/** ***********************************************************************************************
	 * 	Log_TestDefaultDomain
	 **************************************************************************************************/
	@Test 
	public void Log_TestDefaultDomain()
	{
			int cntLL;

			clearCreateAndAddLoggers( true );
			Log.error("No domain and nothing set");

			Log.regDomain( "DFLT", Log.Scope.METHOD );
			Log.setDomain( "DFLT", Log.DomainLevel.INFO_WARNINGS_AND_ERRORS );
			Log.info( "***Log_TestDefaultDomain***" );
			
			
			String testOK=  "OK";
			String testERR= "Error";

			// Test log level setting
			cntLL= cl.cntLogs;
			Log.setDomain( "DFLT", Log.DomainLevel.INFO_WARNINGS_AND_ERRORS );
			cntLL= cl.cntLogs;	Log.verbose	   ( testERR );	assertEquals ( 0, cl.cntLogs - cntLL );
			cntLL= cl.cntLogs;	Log.info	   ( testOK  );	assertEquals ( 1, cl.cntLogs - cntLL );

			Log.setDomain( "~", Log.DomainLevel.WARNINGS_AND_ERRORS );
			cntLL= cl.cntLogs;	Log.info	   ( testERR );	assertEquals ( 0, cl.cntLogs - cntLL );
			cntLL= cl.cntLogs;	Log.warning	   ( testOK  );	assertEquals ( 1, cl.cntLogs - cntLL );

			Log.setDomain( "~/",Log.DomainLevel.ERRORS );
			cntLL= cl.cntLogs;	Log.warning	   ( testERR );	assertEquals ( 0, cl.cntLogs - cntLL );
			cntLL= cl.cntLogs;	Log.error	   ( testOK  );	assertEquals ( 1, cl.cntLogs - cntLL );


			// test sub domains
			Log.regDomain( "DFLT/WARN",	Log.Scope.NONE );
			Log.regDomain(    "~/ERR",	Log.Scope.NONE );
			Log.logConfig( "TEST", Log.Level.INFO, "Dumping Log Configuration:", cl.name );

			Log.setDomain( "DFLT",		Log.DomainLevel.INFO_WARNINGS_AND_ERRORS,	true );
			Log.setDomain( "DFLT/WARN",	Log.DomainLevel.WARNINGS_AND_ERRORS,		true );
			Log.setDomain(    "~/ERR",	Log.DomainLevel.ERRORS,						true );

			Log.logConfig( "TEST",	Log.Level.INFO, "Dumping Log Configuration:", cl.name );
	
			// log with leading "/" on domain
			cntLL= ml.cntLogs;	Log.verbose	   ( "/DFLT",		testERR );	assertEquals ( 0, ml.cntLogs - cntLL );
			cntLL= ml.cntLogs;	Log.verbose	   ( "/DFLT/ERR",	testERR );	assertEquals ( 0, ml.cntLogs - cntLL );
			cntLL= ml.cntLogs;	Log.verbose	   ( "/DFLT/WARN",	testERR );	assertEquals ( 0, ml.cntLogs - cntLL );

			cntLL= ml.cntLogs;	Log.info	   ( "/DFLT",		testOK  );	assertEquals ( 1, ml.cntLogs - cntLL );
			cntLL= ml.cntLogs;	Log.info	   ( "/DFLT/ERR",	testERR );	assertEquals ( 0, ml.cntLogs - cntLL );
			cntLL= ml.cntLogs;	Log.info	   ( "/DFLT/WARN",	testERR );	assertEquals ( 0, ml.cntLogs - cntLL );

			cntLL= ml.cntLogs;	Log.warning	   ( "/DFLT",		testOK  );	assertEquals ( 1, ml.cntLogs - cntLL );
			cntLL= ml.cntLogs;	Log.warning	   ( "/DFLT/WARN",	testOK  );	assertEquals ( 1, ml.cntLogs - cntLL );
			cntLL= ml.cntLogs;	Log.warning	   ( "/DFLT/ERR",	testERR );	assertEquals ( 0, ml.cntLogs - cntLL );

			cntLL= ml.cntLogs;	Log.error	   ( "/DFLT",		testOK  );	assertEquals ( 1, ml.cntLogs - cntLL );
			cntLL= ml.cntLogs;	Log.error	   ( "/DFLT/WARN",	testOK  );	assertEquals ( 1, ml.cntLogs - cntLL );
			cntLL= ml.cntLogs;	Log.error	   ( "/DFLT/ERR",	testOK  );	assertEquals ( 1, ml.cntLogs - cntLL );

			// log without leading "/" on domain, still absolute
			cntLL= ml.cntLogs;	Log.verbose	   ( "DFLT",		testERR );	assertEquals ( 0, ml.cntLogs - cntLL );
			cntLL= ml.cntLogs;	Log.verbose	   ( "DFLT/ERR",	testERR );	assertEquals ( 0, ml.cntLogs - cntLL );
			cntLL= ml.cntLogs;	Log.verbose	   ( "DFLT/WARN",	testERR );	assertEquals ( 0, ml.cntLogs - cntLL );

			cntLL= ml.cntLogs;	Log.info	   ( "DFLT",		testOK  );	assertEquals ( 1, ml.cntLogs - cntLL );
			cntLL= ml.cntLogs;	Log.info	   ( "DFLT/ERR",	testERR );	assertEquals ( 0, ml.cntLogs - cntLL );
			cntLL= ml.cntLogs;	Log.info	   ( "DFLT/WARN",	testERR );	assertEquals ( 0, ml.cntLogs - cntLL );

			cntLL= ml.cntLogs;	Log.warning	   ( "DFLT",		testOK  );	assertEquals ( 1, ml.cntLogs - cntLL );
			cntLL= ml.cntLogs;	Log.warning	   ( "DFLT/WARN",	testOK  );	assertEquals ( 1, ml.cntLogs - cntLL );
			cntLL= ml.cntLogs;	Log.warning	   ( "DFLT/ERR",	testERR );	assertEquals ( 0, ml.cntLogs - cntLL );

			cntLL= ml.cntLogs;	Log.error	   ( "DFLT",		testOK  );	assertEquals ( 1, ml.cntLogs - cntLL );
			cntLL= ml.cntLogs;	Log.error	   ( "DFLT/WARN",	testOK  );	assertEquals ( 1, ml.cntLogs - cntLL );
			cntLL= ml.cntLogs;	Log.error	   ( "DFLT/ERR",	testOK  );	assertEquals ( 1, ml.cntLogs - cntLL );


			// relative addressing with "~"domain
			cntLL= ml.cntLogs;	Log.verbose	   (				testERR );	assertEquals ( 0, ml.cntLogs - cntLL );
			cntLL= ml.cntLogs;	Log.verbose	   ( "~",			testERR );	assertEquals ( 0, ml.cntLogs - cntLL );
			cntLL= ml.cntLogs;	Log.verbose	   ( "~ERR",		testERR );	assertEquals ( 0, ml.cntLogs - cntLL );
			cntLL= ml.cntLogs;	Log.verbose	   ( "~WARN",		testERR );	assertEquals ( 0, ml.cntLogs - cntLL );

			cntLL= ml.cntLogs;	Log.info	   (				testOK  );	assertEquals ( 1, ml.cntLogs - cntLL );
			cntLL= ml.cntLogs;	Log.info	   ( "~",			testOK  );	assertEquals ( 1, ml.cntLogs - cntLL );
			cntLL= ml.cntLogs;	Log.info	   ( "~ERR",		testERR );	assertEquals ( 0, ml.cntLogs - cntLL );
			cntLL= ml.cntLogs;	Log.info	   ( "~WARN",		testERR );	assertEquals ( 0, ml.cntLogs - cntLL );

			cntLL= ml.cntLogs;	Log.warning	   ( 				testOK  );	assertEquals ( 1, ml.cntLogs - cntLL );
			cntLL= ml.cntLogs;	Log.warning	   ( "~",			testOK  );	assertEquals ( 1, ml.cntLogs - cntLL );
			cntLL= ml.cntLogs;	Log.warning	   ( "~WARN",		testOK  );	assertEquals ( 1, ml.cntLogs - cntLL );
			cntLL= ml.cntLogs;	Log.warning	   ( "~ERR",		testERR );	assertEquals ( 0, ml.cntLogs - cntLL );

			cntLL= ml.cntLogs;	Log.error	   (				testOK  );	assertEquals ( 1, ml.cntLogs - cntLL );
			cntLL= ml.cntLogs;	Log.error	   ( "~",			testOK  );	assertEquals ( 1, ml.cntLogs - cntLL );
			cntLL= ml.cntLogs;	Log.error	   ( "~WARN",		testOK  );	assertEquals ( 1, ml.cntLogs - cntLL );
			cntLL= ml.cntLogs;	Log.error	   ( "~ERR",		testOK  );	assertEquals ( 1, ml.cntLogs - cntLL );
		}

		/** ***********************************************************************************************
		 * 	Log_TestDefaultDomain
		 **************************************************************************************************/
		@Test 
		public void Log_TestAssertAndConditional()
		{
			//#if ALOX_DEBUG || ALOX_REL_LOG
			clearCreateAndAddLoggers( true );

			Log.regDomain( "ASSERT", Log.Scope.METHOD );

			String testOK=  "OK";
			String testERR= "Error";

			// Test log level setting
			int cntLL= cl.cntLogs;
			Log.setDomain( "ASSERT", Log.DomainLevel.INFO_WARNINGS_AND_ERRORS);

				cntLL= cl.cntLogs;	Log.Assert( true,  testERR );							assertEquals(  0, cl.cntLogs - cntLL );
				cntLL= cl.cntLogs;	Log.Assert( false, testOK  );							assertEquals(  1, cl.cntLogs - cntLL );
				cntLL= cl.cntLogs;	Log.line   ( false, null, Log.Level.INFO, testERR );	assertEquals(  0, cl.cntLogs - cntLL );
				cntLL= cl.cntLogs;	Log.line   ( true,  null, Log.Level.INFO, testOK  );	assertEquals(  1, cl.cntLogs - cntLL );
			//#endif
		}

		/** ***********************************************************************************************
		 * 	Log_TestDefaultDomain
		 **************************************************************************************************/
		@Test 
		public void Log_TestLineFormat()
		{
			//#if ALOX_DEBUG || ALOX_REL_LOG
			clearCreateAndAddLoggers();

			Log.regDomain( "FMT", Log.Scope.METHOD );
			Log.setDomain( "FMT", Log.DomainLevel.ALL);
			
			Log.info( "This is the default ConsoleLogger log line" );

			MString  lf;
			lf= new MString( "(%CF) %CP.%CC.%CM():%A3[%DD][%TD][%TE +%TI] [%t] %L [%O] <%#>: ");	cl.lineFormatter.format= lf;	Log.info( "LineFormat set to= \"" + lf + "\"" );
			lf= new MString(     "(%CF) %CC.%CM():%A3[%DD][%TD][%TE +%TI] [%t] %L [%O] <%#>: ");	cl.lineFormatter.format= lf;	Log.info( "LineFormat set to= \"" + lf + "\"" );
			lf= new MString(         "(%CF) %CM():%A3[%DD][%TD][%TE +%TI] [%t] %L [%O] <%#>: ");	cl.lineFormatter.format= lf;	Log.info( "LineFormat set to= \"" + lf + "\"" );
			lf= new MString(         "(%CF) %CM():%A3[%TD][%TE +%TI] [%t] %L [%O] <%#>: ");			cl.lineFormatter.format= lf;	Log.info( "LineFormat set to= \"" + lf + "\"" );
			lf= new MString(         "(%CF) %CM():%A3[%TE +%TI] [%t] %L [%O] <%#>: ");				cl.lineFormatter.format= lf;	Log.info( "LineFormat set to= \"" + lf + "\"" );
			lf= new MString(         "(%CF) %CM():%A3[+%TI] [%t] %L [%O] <%#>: ");					cl.lineFormatter.format= lf;	Log.info( "LineFormat set to= \"" + lf + "\"" );
			lf= new MString(         "(%CF) %CM():%A3[%t] %L [%O] <%#>: ");							cl.lineFormatter.format= lf;	Log.info( "LineFormat set to= \"" + lf + "\"" );
			lf= new MString(         "(%CF) %CM():%A3%L [%O] <%#>: ");								cl.lineFormatter.format= lf;	Log.info( "LineFormat set to= \"" + lf + "\"" );
			lf= new MString(         "(%CF) %CM():%A3[%O] <%#>: ");									cl.lineFormatter.format= lf;	Log.info( "LineFormat set to= \"" + lf + "\"" );
			lf= new MString(         "(%CF) %CM():%A3[%O]: ");										cl.lineFormatter.format= lf;	Log.info( "LineFormat set to= \"" + lf + "\"" );
			lf= new MString(         "(%CF):%A3[%O]: ");											cl.lineFormatter.format= lf;	Log.info( "LineFormat set to= \"" + lf + "\"" );
			lf= new MString( "[%O]: ");																cl.lineFormatter.format= lf;	Log.info( "LineFormat set to= \"" + lf + "\"" );
			lf= new MString( "");																	cl.lineFormatter.format= lf;	Log.info( "LineFormat set to= \"" + lf + "\"" );
			//#endif
		}


		/** ***********************************************************************************************
		 * 	Log_TestMarker
		 **************************************************************************************************/
		@Test 
		public void Log_TestMarker()
		{
			clearCreateAndAddLoggers();

			Log.regDomain( "MARKER", Log.Scope.METHOD );
			Log.setDomain( "MARKER", Log.DomainLevel.ALL );


			Log.info( "*** Testing markers ***" );
			final String markerDisposedGlobal=	"overwritten global marker (should NOT appear in the test log)";
			final String markerGlobal=			"global marker (this is right to appear in the test log!)";
			final String markerDisposedPkg=		"overwritten package level marker (should NOT appear in the test log)";
			final String markerPkg=				"package level marker (this is right to appear in the test log!)";
			final String markerDisposedClass=	"overwritten class marker (should NOT appear in the test log)";
			final String markerClass=			"class marker (this is right to appear in the test log!)";
			final String markerDisposedMethod=	"overwritten method marker (should NOT appear in the test log)";
			final String markerMethod=			"method marker (this is right to appear in the test log!)";


			/*#/AWX_LOG// Log.setMarker( markerDisposedSrc,	true );		//#/AWX_LOG*/
			Log.setMarker( markerDisposedGlobal,Log.Scope.NONE );
			Log.setMarker( markerGlobal,		Log.Scope.NONE );
			Log.setMarker( markerDisposedPkg,	Log.Scope.PACKAGE );
			Log.setMarker( markerPkg,			Log.Scope.PACKAGE );
			Log.setMarker( markerDisposedClass,	Log.Scope.CLASS );
			Log.setMarker( markerClass,			Log.Scope.CLASS );
			Log.setMarker( markerDisposedMethod,Log.Scope.METHOD );
			Log.setMarker( markerMethod,		Log.Scope.METHOD );

			Object[] markerpointer= new Object[1];

			Log.getMarker( markerpointer, Log.Scope.NONE );			Log.info( "The current global        marker is: " + markerpointer[0] );	 assertTrue( (String) markerpointer[0] == markerGlobal	);
			Log.getMarker( markerpointer, Log.Scope.PACKAGE );		Log.info( "The current package level marker is: " + markerpointer[0] );	 assertTrue( (String) markerpointer[0] == markerPkg		);
			Log.getMarker( markerpointer, Log.Scope.CLASS );		Log.info( "The current class   level marker is: " + markerpointer[0] );	 assertTrue( (String) markerpointer[0] == markerClass	);
			Log.getMarker( markerpointer, Log.Scope.METHOD );		Log.info( "The current method  level marker is: " + markerpointer[0] );	 assertTrue( (String) markerpointer[0] == markerMethod	);
		}


		/** ***********************************************************************************************
		 * 	Log_TestThreads
		 **************************************************************************************************/
		@Test 
		public void Log_TestThreads()
		{
			clearCreateAndAddLoggers();

			Log.regDomain ( "TEST/THREAD1", Log.Scope.METHOD );
			Log.setDomain( "TEST/THREAD1", Log.DomainLevel.ALL );

			// if this gets commented out, the test might crash. At least the console will
			// become scrambled!
			//Log.LOX.Lock.setUnsafe( true );
			

			Thread thread = new Thread( new TestDifferentThreadMethod() ); 
			thread.setName( "Thread2" );
			thread.start();

			for ( int i= 0 ; i < 50 ; i++ )
			{
				Log.info( "This is the main thread ");// + i );
				AWXU.sleep( 4 );
			}
		}

		class TestDifferentThreadMethod implements Runnable
		{
			@Override public void run()
			{
				Log.regDomain ( "TEST/THREAD2", Log.Scope.METHOD );
				Log.setDomain( "TEST/THREAD2", Log.DomainLevel.ALL );
	
				for ( int i= 0 ; i < 20 ; i++ )
				{ 
					Log.info( "This is a different Thread. Cnt= " + i );
					AWXU.sleep( 3 );
				}
			}
		}


		/** ***********************************************************************************************
		 * 	Log_TestException.
		 **************************************************************************************************/
		@Test 
		public void Log_TestException()
		{
			clearCreateAndAddLoggers();

			Log.regDomain( "EXCEPT", Log.Scope.METHOD );
			Log.setDomain( "EXCEPT", Log.DomainLevel.ALL );

			Log.info("*** Test LogTools.exception() ***" );
			Exception testException=  new Exception( "TestException Message", new Exception ("InnerException Message", new Exception("Inner, inner Exception") ) );

			LogTools.exception( Log.Level.WARNING, testException, "Logging an exception: " );
		}

		/** ***********************************************************************************************
		 * 	Log_TestException.
		 **************************************************************************************************/
		@Test 
		public void Log_TestStackTrace()
		{
			clearCreateAndAddLoggers();

			Log.regDomain( "STTR", Log.Scope.METHOD );
			Log.setDomain( "STTR", Log.DomainLevel.ALL );

			Log.info("*** Test LogTools.stackTrace() ***" );

			LogTools.stackTrace( Log.Level.ERROR, "The current stacktrace is: " );
		}

		/** ***********************************************************************************************
		 * 	Log_TestInstance
		 **************************************************************************************************/
		@Test
		public void Log_TestInstance()
		{
			clearCreateAndAddLoggers();

			Log.regDomain( "INST", Log.Scope.METHOD );
			Log.setDomain( "INST", Log.DomainLevel.ALL );

			// simple type double
			{
				double o= 3.14;
				
				LogTools.instance( Log.Level.INFO, o, 2, "Logging an object of type 'Double':", 1 );
			}

			// Double array
			{
				double[] o= new double[3];
				o[0]= 12.5;
				o[1]= 123456789.987654321;
				o[2]= 100;

				LogTools.instance( Log.Level.INFO, o, 2, "Logging an object of type 'Double[]':", 1 );
			}

			// byte array
			{
				byte[] o= new byte[3];
				o[0]= 2;
				o[1]= 8;
				o[2]= 16;

				LogTools.instance( Log.Level.INFO, o, 2, "Logging an object of type 'byte[]':", 1 );
			}


			// 2 dimensional char[] 
			{
				char[][] o= new char[2][3];
				for ( int x= 0; x < 2 ; x++ )
					for ( int y= 0; y < 3 ; y++ )
						o[x][y]= (char) ( 'a' + y*2 + x);
				LogTools.instance( Log.Level.INFO, o, 2, "Logging a 2 dimensional char[]:", 1 );
			}

			// 2 dimensional int[] 
			{
				int[][] o= new int[2][3];
				for ( int x= 0; x < 2 ; x++ )
					for ( int y= 0; y < 3 ; y++ )
						o[x][y]=  y*2 + x;
				LogTools.instance( Log.Level.INFO, o, 2, "Logging a 2 dimensional int[]:", 1 );
			}

			// 4 dimensional int[] 
			{
				int[][][][] o= new int[2][3][4][5];
				int val= 0;
				for ( int i1= 0; i1 < 2; i1++ )
					for ( int i2= 0; i2 < 3 ; i2++ )
						for ( int i3= 0; i3 < 4 ; i3++ )
							for ( int i4= 0; i4 < 5 ; i4++ )
								o[i1][i2][i3][i4]=  val++;
				LogTools.instance( Log.Level.INFO, o, 2, "Logging a 4 dimensional int[]:", 1 );
			}


			// simple type String
			{
				String o= "Hello reflection";
				LogTools.instance( Log.Level.INFO, o, 2, "Logging an object of type 'String':", 1 );
			}


			// String array
			{
				String[] o= new String[3];
				o[0]= "Entry 0";
				o[1]= "Entry 1";
				o[2]= "Entry 2";

				LogTools.instance( Log.Level.INFO, o, 2, "Logging an object of type 'String[]':", 1 );
			}

			// List
			{
				LinkedList<String> o= new LinkedList<String>();
				o.add( "Linked entry 0" );
				o.add( "Linked entry 1" );
				o.add( "Linked entry 2" );

				LogTools.instance( Log.Level.INFO, o, 2, "Logging an object of type 'LinkedList<String>':", 1 );
			}

			// Object array
			{
				Object[] o= new Object[10];
				int i= 0;
				o[i++]= "Entry 0";
				o[i++]= 3.14;
				o[i++]= "next is array itself!";
				o[i++]= o;
				o[i++]= "next is console logger";
				o[i++]= cl;
				o[i++]= "last filled object";

				LogTools.instance( Log.Level.INFO, o, 3, "Logging an object of type 'Object[]':", 1 );
			}

			// Lox 
			{
				LogTools.instance( Log.Level.INFO, Log.LOX, 5, "The lox of Log:", 1 );
			}

			// This thread
			{
				Thread o= Thread.currentThread();
				LogTools.instance( Log.Level.INFO, o, 5, ("Actual Thread: " + o.getName()), 1 );
			}

		}


		/** ***********************************************************************************************
		 * 	Log_TestException.
		 **************************************************************************************************/
		@Test 
		public void Log_TestMultiline()
		{
			clearCreateAndAddLoggers();

			//#if ALOX_DEBUG || ALOX_REL_LOG
				Log.regDomain( "MLine", Log.Scope.METHOD );
				Log.setDomain( "MLine", Log.DomainLevel.ALL );


				cl.multiLineMsgMode= 0;
				Log.info( "" );
				Log.info( "-------- ML Mode = 0 (single line) --------" );
				Log.logConfig( "MLine", Log.Level.INFO, "Our Log configuration is:" );

				cl.multiLineMsgMode= 0;
				cl.multiLineDelimiterRepl= "~|~";
				Log.info( "" );
				Log.info( "-------- ML Mode = 0 (single line) with delimiter replacement set to ~|~ --------" );
				Log.logConfig( "MLine", Log.Level.INFO, "Our Log configuration is:" );

				cl.multiLineMsgMode= 0;
				cl.multiLineDelimiter= "";
				Log.info( "" );
				Log.info( "-------- ML Mode = 0 (single line) with delimiter set to \"\" (stops multi line processing) --------" );
				Log.logConfig( "MLine", Log.Level.INFO, "Our Log configuration is:" );
				cl.multiLineDelimiter= null; // reset

				cl.multiLineMsgMode= 1;
				Log.info( "" );
				Log.info( "-------- ML Mode = 1 (multi line, all meta info per line) --------" );
				Log.logConfig( "MLine", Log.Level.INFO, "Our Log configuration is:" );
			
				cl.multiLineMsgMode= 2;
				Log.info( "" );
				Log.info( "-------- ML Mode = 2 (multi line, meta info blanked) --------" );
				Log.logConfig( "MLine", Log.Level.INFO, "Our Log configuration is:" );

				cl.multiLineMsgMode= 3;
				Log.info( "" );
				Log.info( "-------- ML Mode = 3 (multi line, print headline with info, text starts at pos 0) --------" );
				Log.logConfig( "MLine", Log.Level.INFO, "Our Log configuration is:" );

				cl.multiLineMsgMode= 4;
				Log.info( "" );
				Log.info( "-------- ML Mode = 4 (pure multi line, no meta info, no headline, starts at pos 0)) --------" );
				Log.logConfig( "MLine", Log.Level.INFO, "Our Log configuration is:" );
			//#endif
		}


		/** ***********************************************************************************************
		 * 	Log_TestXML
		 **************************************************************************************************/
/* NIY		 
		@Test 
		public void Log_TestXML()
		{
			clearCreateAndAddLoggers();

			Log.regDomain( "XML", Log.Scope.Method );
			Log.setDomain( "XML", Log.DomainLevel.All );


			String xmltext= "<MainTag> <SubTag>Hallo ALox XML</SubTag> <SubTag2> <SubsubTag>A sub tags' string</SubsubTag> </SubTag2> </MainTag>";
			XDocument xdoc= XDocument.Parse( xmltext );

			LogTools.XML(Log.Level.Info, xdoc, "Logging an xml document: " );
		}
*/

}
