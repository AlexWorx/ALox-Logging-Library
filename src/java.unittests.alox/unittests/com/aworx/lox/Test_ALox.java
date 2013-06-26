package unittests.com.aworx.lox;

import static org.junit.Assert.*;
import java.util.Locale;

import javax.xml.ws.handler.MessageContext.Scope;

import junit.framework.Assert;
import org.junit.Test;

import com.aworx.lox.*;
import com.aworx.lox.core.CallerInfo;
import com.aworx.util.*;


public class Test_ALox
{
	/** ***********************************************************************************************
	 * <summary>	The loggers. </summary>
	 **************************************************************************************************/
	public static ConsoleLogger		cl;
	public static MemoryLogger		ml;

	/** ***********************************************************************************************
	 * <summary>	Creates loggers. </summary>
	 **************************************************************************************************/
	public void   clearCreateAndAddLoggers( boolean memoryLogger, boolean consoleLogger)
	{
		Log.reset();
		cl= null;
		ml= null;

		if ( consoleLogger )
		{
			cl=		new ConsoleLogger( "Console" );
			cl.tabAfterSourceInfo = 60;
			Log.addLogger( cl, Log.DomainLevel.All );

			//cl.EnableAppConsole=		true;
			//cl.EnableVSDebugConsole=	true;
		}

		if ( memoryLogger )
		{
			ml=		new MemoryLogger( "Memory" );
			ml.tabAfterSourceInfo = 60;
			Log.addLogger( ml, Log.DomainLevel.Off );
		}

		Log.mapThreadName( "UnitTest" );
	}
	public void   clearCreateAndAddLoggers( boolean memoryLogger )	{ clearCreateAndAddLoggers( memoryLogger, true ); }
	public void   clearCreateAndAddLoggers()						{ clearCreateAndAddLoggers( false, true ); }


	/** ***********************************************************************************************
	 * <summary>	Log_TestLogLevelSetting </summary>
	 **************************************************************************************************/
	@Test 
	public void Log_TestTextLoggerTimeDiff()
	{
		class T extends TextLogger
		{
						protected 		T()												{ super( "TLTest" );}
			@Override 	protected void 	doTextLog(MString domain, Log.Level level, 
												  MString msg, int indent,
												  CallerInfo caller, int lineNumber)	{}
						public 	  void 	t(MString buf, long diff) 						{ logBuf= buf; logTimeDiff( diff ); }
		}
		
		T t= new T();
		MString ms= new MString();
		long diff;
		int lenFMT_TimeDiffPrefix= 	t.FMT_TimeDiffPrefix .length();
		int lenFMT_TimeDiffPostfix= t.FMT_TimeDiffPostfix.length();
		long millis= 	1000L;
		long secs=		1000L * millis;
		long mins=		60 * secs;
		long hours=		60 * mins;
		long days=		24 * hours;
		
		
		diff= 0; 							ms.clear(); t.t( ms, diff ); assertEquals(  "000" + t.FMT_TimeDiffMicros,	ms.toString(lenFMT_TimeDiffPrefix, ms.length - lenFMT_TimeDiffPrefix - lenFMT_TimeDiffPostfix) );
		diff= 15; 							ms.clear(); t.t( ms, diff ); assertEquals(  "015" + t.FMT_TimeDiffMicros,	ms.toString(lenFMT_TimeDiffPrefix, ms.length - lenFMT_TimeDiffPrefix - lenFMT_TimeDiffPostfix) );
		diff= 99; 							ms.clear(); t.t( ms, diff ); assertEquals(  "099" + t.FMT_TimeDiffMicros,	ms.toString(lenFMT_TimeDiffPrefix, ms.length - lenFMT_TimeDiffPrefix - lenFMT_TimeDiffPostfix) );
		diff= 600; 							ms.clear(); t.t( ms, diff ); assertEquals(  "600" + t.FMT_TimeDiffMicros,	ms.toString(lenFMT_TimeDiffPrefix, ms.length - lenFMT_TimeDiffPrefix - lenFMT_TimeDiffPostfix) );
		diff= 999; 							ms.clear(); t.t( ms, diff ); assertEquals(  "999" + t.FMT_TimeDiffMicros,	ms.toString(lenFMT_TimeDiffPrefix, ms.length - lenFMT_TimeDiffPrefix - lenFMT_TimeDiffPostfix) );
		diff= 1   * millis;					ms.clear(); t.t( ms, diff ); assertEquals(  "001" + t.FMT_TimeDiffMillis,	ms.toString(lenFMT_TimeDiffPrefix, ms.length - lenFMT_TimeDiffPrefix - lenFMT_TimeDiffPostfix) );
		diff= 999 * millis;					ms.clear(); t.t( ms, diff ); assertEquals(  "999" + t.FMT_TimeDiffMillis,	ms.toString(lenFMT_TimeDiffPrefix, ms.length - lenFMT_TimeDiffPrefix - lenFMT_TimeDiffPostfix) );
		diff= 1   * secs;					ms.clear(); t.t( ms, diff ); assertEquals(  "1.00" + t.FMT_TimeDiffSecs,		ms.toString(lenFMT_TimeDiffPrefix, ms.length - lenFMT_TimeDiffPrefix - lenFMT_TimeDiffPostfix) );
		diff= 2   * secs + 344 * millis;	ms.clear(); t.t( ms, diff ); assertEquals(  "2.34" + t.FMT_TimeDiffSecs,		ms.toString(lenFMT_TimeDiffPrefix, ms.length - lenFMT_TimeDiffPrefix - lenFMT_TimeDiffPostfix) );
		diff= 3   * secs + 345 * millis;	ms.clear(); t.t( ms, diff ); assertEquals(  "3.35" + t.FMT_TimeDiffSecs,		ms.toString(lenFMT_TimeDiffPrefix, ms.length - lenFMT_TimeDiffPrefix - lenFMT_TimeDiffPostfix) );
		diff= 9   * secs + 994 * millis;	ms.clear(); t.t( ms, diff ); assertEquals(  "9.99" + t.FMT_TimeDiffSecs,		ms.toString(lenFMT_TimeDiffPrefix, ms.length - lenFMT_TimeDiffPrefix - lenFMT_TimeDiffPostfix) );
		diff= 9   * secs + 995 * millis;	ms.clear(); t.t( ms, diff ); assertEquals(  "10.0" + t.FMT_TimeDiffSecs,		ms.toString(lenFMT_TimeDiffPrefix, ms.length - lenFMT_TimeDiffPrefix - lenFMT_TimeDiffPostfix) );
		diff= 9   * secs + 999 * millis;	ms.clear(); t.t( ms, diff ); assertEquals(  "10.0" + t.FMT_TimeDiffSecs,		ms.toString(lenFMT_TimeDiffPrefix, ms.length - lenFMT_TimeDiffPrefix - lenFMT_TimeDiffPostfix) );
		diff= 10  * secs + 940 * millis;	ms.clear(); t.t( ms, diff ); assertEquals(  "10.9" + t.FMT_TimeDiffSecs,		ms.toString(lenFMT_TimeDiffPrefix, ms.length - lenFMT_TimeDiffPrefix - lenFMT_TimeDiffPostfix) );
		diff= 10  * secs + 950 * millis;	ms.clear(); t.t( ms, diff ); assertEquals(  "11.0" + t.FMT_TimeDiffSecs,		ms.toString(lenFMT_TimeDiffPrefix, ms.length - lenFMT_TimeDiffPrefix - lenFMT_TimeDiffPostfix) );
		
		diff= 99  * secs + 900 * millis;	ms.clear(); t.t( ms, diff ); assertEquals(  "99.9" + t.FMT_TimeDiffSecs,		ms.toString(lenFMT_TimeDiffPrefix, ms.length - lenFMT_TimeDiffPrefix - lenFMT_TimeDiffPostfix) );
		diff= 99  * secs + 949 * millis;	ms.clear(); t.t( ms, diff ); assertEquals(  "99.9" + t.FMT_TimeDiffSecs,		ms.toString(lenFMT_TimeDiffPrefix, ms.length - lenFMT_TimeDiffPrefix - lenFMT_TimeDiffPostfix) );

//		diff= 99  * secs + 950 * millis;	ms.Clear(); t.t( ms, diff ); assertEquals(  "99.9" + t.FMT_TimeDiffSecs,		ms.toString(lenFMT_TimeDiffPrefix, ms.Length - lenFMT_TimeDiffPrefix - lenFMT_TimeDiffPostfix) );

		diff= 2  * mins + 0 * secs;			ms.clear(); t.t( ms, diff ); assertEquals(  "2.00" + t.FMT_TimeDiffMins,		ms.toString(lenFMT_TimeDiffPrefix, ms.length - lenFMT_TimeDiffPrefix - lenFMT_TimeDiffPostfix) );
		diff= 2  * mins + 30 * secs;		ms.clear(); t.t( ms, diff ); assertEquals(  "2.50" + t.FMT_TimeDiffMins,		ms.toString(lenFMT_TimeDiffPrefix, ms.length - lenFMT_TimeDiffPrefix - lenFMT_TimeDiffPostfix) );
		diff= 9  * mins + 45 * secs;		ms.clear(); t.t( ms, diff ); assertEquals(  "9.75" + t.FMT_TimeDiffMins,		ms.toString(lenFMT_TimeDiffPrefix, ms.length - lenFMT_TimeDiffPrefix - lenFMT_TimeDiffPostfix) );
		diff= 9  * mins + 59 * secs;		ms.clear(); t.t( ms, diff ); assertEquals(  "9.98" + t.FMT_TimeDiffMins,		ms.toString(lenFMT_TimeDiffPrefix, ms.length - lenFMT_TimeDiffPrefix - lenFMT_TimeDiffPostfix) );
		diff= 9  * mins + 59500 * millis;	ms.clear(); t.t( ms, diff ); assertEquals(  "9.99" + t.FMT_TimeDiffMins,		ms.toString(lenFMT_TimeDiffPrefix, ms.length - lenFMT_TimeDiffPrefix - lenFMT_TimeDiffPostfix) );
		diff= 9  * mins + 59999 * millis;	ms.clear(); t.t( ms, diff ); assertEquals(  "10.0" + t.FMT_TimeDiffMins,		ms.toString(lenFMT_TimeDiffPrefix, ms.length - lenFMT_TimeDiffPrefix - lenFMT_TimeDiffPostfix) );

		diff= 99 * mins + 0 * secs;			ms.clear(); t.t( ms, diff ); assertEquals(  "99.0" + t.FMT_TimeDiffMins,		ms.toString(lenFMT_TimeDiffPrefix, ms.length - lenFMT_TimeDiffPrefix - lenFMT_TimeDiffPostfix) );
		diff= 99 * mins + 30* secs;			ms.clear(); t.t( ms, diff ); assertEquals(  "99.5" + t.FMT_TimeDiffMins,		ms.toString(lenFMT_TimeDiffPrefix, ms.length - lenFMT_TimeDiffPrefix - lenFMT_TimeDiffPostfix) );
		diff= 99 * mins + 59* secs;			ms.clear(); t.t( ms, diff ); assertEquals(  "99.9" + t.FMT_TimeDiffMins,		ms.toString(lenFMT_TimeDiffPrefix, ms.length - lenFMT_TimeDiffPrefix - lenFMT_TimeDiffPostfix) );
		diff= 99 * mins + 59500* millis;	ms.clear(); t.t( ms, diff ); assertEquals(  "99.9" + t.FMT_TimeDiffMins,		ms.toString(lenFMT_TimeDiffPrefix, ms.length - lenFMT_TimeDiffPrefix - lenFMT_TimeDiffPostfix) );
		diff= 99 * mins + 59999* millis;	ms.clear(); t.t( ms, diff ); assertEquals(  "1.66" + t.FMT_TimeDiffHours,		ms.toString(lenFMT_TimeDiffPrefix, ms.length - lenFMT_TimeDiffPrefix - lenFMT_TimeDiffPostfix) );
		diff= 1 * hours + 30* mins;			ms.clear(); t.t( ms, diff ); assertEquals(  "90.0" + t.FMT_TimeDiffMins,		ms.toString(lenFMT_TimeDiffPrefix, ms.length - lenFMT_TimeDiffPrefix - lenFMT_TimeDiffPostfix) );

		diff= 5 * hours + 30* mins;			ms.clear(); t.t( ms, diff ); assertEquals(  "5.50" + t.FMT_TimeDiffHours,		ms.toString(lenFMT_TimeDiffPrefix, ms.length - lenFMT_TimeDiffPrefix - lenFMT_TimeDiffPostfix) );
	
		diff= 9 * hours + 45* mins;			ms.clear(); t.t( ms, diff ); assertEquals(  "9.75" + t.FMT_TimeDiffHours,		ms.toString(lenFMT_TimeDiffPrefix, ms.length - lenFMT_TimeDiffPrefix - lenFMT_TimeDiffPostfix) );
		diff= 9 * hours + 59* mins;			ms.clear(); t.t( ms, diff ); assertEquals(  "9.98" + t.FMT_TimeDiffHours,		ms.toString(lenFMT_TimeDiffPrefix, ms.length - lenFMT_TimeDiffPrefix - lenFMT_TimeDiffPostfix) );
		diff= 9 * hours + 3540* secs;		ms.clear(); t.t( ms, diff ); assertEquals(  "9.98" + t.FMT_TimeDiffHours,		ms.toString(lenFMT_TimeDiffPrefix, ms.length - lenFMT_TimeDiffPrefix - lenFMT_TimeDiffPostfix) );
		diff= 9 * hours + 3580* secs;		ms.clear(); t.t( ms, diff ); assertEquals(  "9.99" + t.FMT_TimeDiffHours,		ms.toString(lenFMT_TimeDiffPrefix, ms.length - lenFMT_TimeDiffPrefix - lenFMT_TimeDiffPostfix) );
		diff= 9 * hours + 3599* secs;		ms.clear(); t.t( ms, diff ); assertEquals(  "9.99" + t.FMT_TimeDiffHours,		ms.toString(lenFMT_TimeDiffPrefix, ms.length - lenFMT_TimeDiffPrefix - lenFMT_TimeDiffPostfix) );
		diff= 9 * hours + 3600* secs;		ms.clear(); t.t( ms, diff ); assertEquals(  "10.0" + t.FMT_TimeDiffHours,		ms.toString(lenFMT_TimeDiffPrefix, ms.length - lenFMT_TimeDiffPrefix - lenFMT_TimeDiffPostfix) );
		
		diff= 50 * hours + 15 *mins;		ms.clear(); t.t( ms, diff ); assertEquals(  "50.2" + t.FMT_TimeDiffHours,		ms.toString(lenFMT_TimeDiffPrefix, ms.length - lenFMT_TimeDiffPrefix - lenFMT_TimeDiffPostfix) );
		diff= 99 * hours + 45 *mins;		ms.clear(); t.t( ms, diff ); assertEquals(  "99.7" + t.FMT_TimeDiffHours,		ms.toString(lenFMT_TimeDiffPrefix, ms.length - lenFMT_TimeDiffPrefix - lenFMT_TimeDiffPostfix) );
		diff= 99 * hours + 48 *mins;		ms.clear(); t.t( ms, diff ); assertEquals(  "99.8" + t.FMT_TimeDiffHours,		ms.toString(lenFMT_TimeDiffPrefix, ms.length - lenFMT_TimeDiffPrefix - lenFMT_TimeDiffPostfix) );
		diff= 99 * hours + 59 *mins;		ms.clear(); t.t( ms, diff ); assertEquals(  "99.9" + t.FMT_TimeDiffHours,		ms.toString(lenFMT_TimeDiffPrefix, ms.length - lenFMT_TimeDiffPrefix - lenFMT_TimeDiffPostfix) );
		diff= 99 * hours + 3540* secs;		ms.clear(); t.t( ms, diff ); assertEquals(  "99.9" + t.FMT_TimeDiffHours,		ms.toString(lenFMT_TimeDiffPrefix, ms.length - lenFMT_TimeDiffPrefix - lenFMT_TimeDiffPostfix) );
		diff= 99 * hours + 3580* secs;		ms.clear(); t.t( ms, diff ); assertEquals(  "99.9" + t.FMT_TimeDiffHours,		ms.toString(lenFMT_TimeDiffPrefix, ms.length - lenFMT_TimeDiffPrefix - lenFMT_TimeDiffPostfix) );
		diff= 99 * hours + 3599* secs;		ms.clear(); t.t( ms, diff ); assertEquals(  "99.9" + t.FMT_TimeDiffHours,		ms.toString(lenFMT_TimeDiffPrefix, ms.length - lenFMT_TimeDiffPrefix - lenFMT_TimeDiffPostfix) );
		diff= 99 * hours + 3600* secs;		ms.clear(); t.t( ms, diff ); assertEquals(  "4.16" + t.FMT_TimeDiffDays,		ms.toString(lenFMT_TimeDiffPrefix, ms.length - lenFMT_TimeDiffPrefix - lenFMT_TimeDiffPostfix) );

		diff= 1 * days + 12* hours;			ms.clear(); t.t( ms, diff ); assertEquals(  "36.0" + t.FMT_TimeDiffHours,		ms.toString(lenFMT_TimeDiffPrefix, ms.length - lenFMT_TimeDiffPrefix - lenFMT_TimeDiffPostfix) );

		diff= 5 * days + 18* hours;			ms.clear(); t.t( ms, diff ); assertEquals(  "5.75" + t.FMT_TimeDiffDays,		ms.toString(lenFMT_TimeDiffPrefix, ms.length - lenFMT_TimeDiffPrefix - lenFMT_TimeDiffPostfix) );
		diff= 9 * days + 23* hours;			ms.clear(); t.t( ms, diff ); assertEquals(  "9.95" + t.FMT_TimeDiffDays,		ms.toString(lenFMT_TimeDiffPrefix, ms.length - lenFMT_TimeDiffPrefix - lenFMT_TimeDiffPostfix) );
		diff= 9 * days + 1380 * mins;		ms.clear(); t.t( ms, diff ); assertEquals(  "9.95" + t.FMT_TimeDiffDays,		ms.toString(lenFMT_TimeDiffPrefix, ms.length - lenFMT_TimeDiffPrefix - lenFMT_TimeDiffPostfix) );
		diff= 9 * days + 1400 * mins;		ms.clear(); t.t( ms, diff ); assertEquals(  "9.97" + t.FMT_TimeDiffDays,		ms.toString(lenFMT_TimeDiffPrefix, ms.length - lenFMT_TimeDiffPrefix - lenFMT_TimeDiffPostfix) );
		diff= 9 * days + 1439 * mins;		ms.clear(); t.t( ms, diff ); assertEquals(  "9.99" + t.FMT_TimeDiffDays,		ms.toString(lenFMT_TimeDiffPrefix, ms.length - lenFMT_TimeDiffPrefix - lenFMT_TimeDiffPostfix) );
		diff= 9 * days + 1440 * mins;		ms.clear(); t.t( ms, diff ); assertEquals(  "10.0" + t.FMT_TimeDiffDays,		ms.toString(lenFMT_TimeDiffPrefix, ms.length - lenFMT_TimeDiffPrefix - lenFMT_TimeDiffPostfix) );
		diff= 15 * days + 6 * hours;		ms.clear(); t.t( ms, diff ); assertEquals(  "15.2" + t.FMT_TimeDiffDays,		ms.toString(lenFMT_TimeDiffPrefix, ms.length - lenFMT_TimeDiffPrefix - lenFMT_TimeDiffPostfix) );
		diff= 99 * days + 18 * hours;		ms.clear(); t.t( ms, diff ); assertEquals(  "99.7" + t.FMT_TimeDiffDays,		ms.toString(lenFMT_TimeDiffPrefix, ms.length - lenFMT_TimeDiffPrefix - lenFMT_TimeDiffPostfix) );
		diff= 99 * days + 1439 * mins;		ms.clear(); t.t( ms, diff ); assertEquals(  "99.9" + t.FMT_TimeDiffDays,		ms.toString(lenFMT_TimeDiffPrefix, ms.length - lenFMT_TimeDiffPrefix - lenFMT_TimeDiffPostfix) );
		diff= 99 * days + 1440 * mins;		ms.clear(); t.t( ms, diff ); assertEquals(  "100.0" + t.FMT_TimeDiffDays,			ms.toString(lenFMT_TimeDiffPrefix, ms.length - lenFMT_TimeDiffPrefix - lenFMT_TimeDiffPostfix) );

		diff= 13452 * days + 12* hours;		ms.clear(); t.t( ms, diff ); assertEquals(  "13452.5" + t.FMT_TimeDiffDays,		ms.toString(lenFMT_TimeDiffPrefix, ms.length - lenFMT_TimeDiffPrefix - lenFMT_TimeDiffPostfix) );
		//System.out.println(ms.toString());		
	}
	
	/** ***********************************************************************************************
	 * <summary>	Log_TestLogLevelSetting </summary>
	 **************************************************************************************************/
	@Test 
	public void Log_TestLogLevelSetting()
	{
			clearCreateAndAddLoggers();

			Log.regDomain( "TLLS", Log.Scope.Method );
			Log.setDomain( Log.LOX.internalDomain, Log.DomainLevel.Off );

			// Test log level setting
			int logLinesBefore= cl.cntLogs;
			Log.setDomain( "TLLS", Log.DomainLevel.All );
			Log.verbose	   ( "TLLS", "This Verbose line should be logged" );
			Log.info	   ( "TLLS", "This Info    line should be logged" );
			Log.warning	   ( "TLLS", "This WARN    line should be logged" );
			Log.error	   ( "TLLS", "This Error   line should be logged" );

			Log.setDomain( "TLLS", Log.DomainLevel.InfoWarningsAndErrors );
			Log.verbose	   ( "TLLS", "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
			Log.info	   ( "TLLS", "This Info    line should be logged" );
			Log.warning	   ( "TLLS", "This Warning line should be logged" );
			Log.error	   ( "TLLS", "This Error   line should be logged" );


			Log.setDomain( "TLLS", Log.DomainLevel.WarningsAndErrors );
			Log.verbose	   ( "TLLS", "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
			Log.info	   ( "TLLS", "This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
			Log.warning	   ( "TLLS", "This Warning line should be logged" );
			Log.error	   ( "TLLS", "This Error   line should be logged" );

			Log.setDomain( "TLLS", Log.DomainLevel.Errors );
			Log.verbose	   ( "TLLS", "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
			Log.info	   ( "TLLS", "This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
			Log.warning	   ( "TLLS", "This Warning line should NOT be logged. !!!!!Test Error!!!!!" );
			Log.error	   ( "TLLS", "This Error   line should be logged" );
			
			Log.setDomain( "TLLS", Log.DomainLevel.Off );
			Log.verbose	   ( "TLLS", "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
			Log.info	   ( "TLLS", "This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
			Log.warning	   ( "TLLS", "This Warning line should NOT be logged. !!!!!Test Error!!!!!" );
			Log.error	   ( "TLLS", "This Error   line should NOT be logged. !!!!!Test Error!!!!!" );

			assertEquals( 10, cl.cntLogs - logLinesBefore );
	}
	
	/** ***********************************************************************************************
	 * <summary>	Log_TestDefaultDomain </summary>
	 **************************************************************************************************/
	@Test 
	public void Log_TestDefaultDomain()
	{
			int cntLL;

			clearCreateAndAddLoggers( true );
			Log.error("No domain and nothing set");

			Log.regDomain( "DFLT", Log.Scope.Method );
			Log.setDomain( "DFLT", Log.DomainLevel.InfoWarningsAndErrors );
			Log.info( "***Log_TestDefaultDomain***" );
			
			
			String testOK=  "OK";
			String testERR= "Error";

			// Test log level setting
			cntLL= cl.cntLogs;
			Log.setDomain( "DFLT", Log.DomainLevel.InfoWarningsAndErrors );
			cntLL= cl.cntLogs;	Log.verbose	   ( testERR );	assertEquals ( 0, cl.cntLogs - cntLL );
			cntLL= cl.cntLogs;	Log.info	   ( testOK  );	assertEquals ( 1, cl.cntLogs - cntLL );

			Log.setDomain( "~", Log.DomainLevel.WarningsAndErrors );
			cntLL= cl.cntLogs;	Log.info	   ( testERR );	assertEquals ( 0, cl.cntLogs - cntLL );
			cntLL= cl.cntLogs;	Log.warning	   ( testOK  );	assertEquals ( 1, cl.cntLogs - cntLL );

			Log.setDomain( "~/",Log.DomainLevel.Errors );
			cntLL= cl.cntLogs;	Log.warning	   ( testERR );	assertEquals ( 0, cl.cntLogs - cntLL );
			cntLL= cl.cntLogs;	Log.error	   ( testOK  );	assertEquals ( 1, cl.cntLogs - cntLL );


			// test sub domains
			Log.regDomain( "DFLT/WARN",	Log.Scope.None );
			Log.regDomain(    "~/ERR",	Log.Scope.None );
			Log.logConfig( "TEST", Log.Level.Info, "Dumping Log Configuration:", cl.name );

			Log.setDomain( "DFLT",		Log.DomainLevel.InfoWarningsAndErrors,	true );
			Log.setDomain( "DFLT/WARN",	Log.DomainLevel.WarningsAndErrors,		true );
			Log.setDomain(    "~/ERR",	Log.DomainLevel.Errors,						true );

			Log.logConfig( "TEST",	Log.Level.Info, "Dumping Log Configuration:", cl.name );
	
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
		 * <summary>	Log_TestDefaultDomain </summary>
		 **************************************************************************************************/
		@Test 
		public void Log_TestAssertAndConditional()
		{
			//#if ALOX_DEBUG || ALOX_REL_LOG
			clearCreateAndAddLoggers( true );

			Log.regDomain( "ASSERT", Log.Scope.Method );

			String testOK=  "OK";
			String testERR= "Error";

			// Test log level setting
			int cntLL= cl.cntLogs;
			Log.setDomain( "ASSERT", Log.DomainLevel.InfoWarningsAndErrors);

				cntLL= cl.cntLogs;	Log.Assert( true,  testERR );							assertEquals(  0, cl.cntLogs - cntLL );
				cntLL= cl.cntLogs;	Log.Assert( false, testOK  );							assertEquals(  1, cl.cntLogs - cntLL );
				cntLL= cl.cntLogs;	Log.line   ( false, null, Log.Level.Info, testERR );	assertEquals(  0, cl.cntLogs - cntLL );
				cntLL= cl.cntLogs;	Log.line   ( true,  null, Log.Level.Info, testOK  );	assertEquals(  1, cl.cntLogs - cntLL );
			//#endif
		}

		/** ***********************************************************************************************
		 * <summary>	Log_TestDefaultDomain </summary>
		 **************************************************************************************************/
		@Test 
		public void Log_TestOutputFlags()
		{
			//#if ALOX_DEBUG || ALOX_REL_LOG
			clearCreateAndAddLoggers();

			Log.regDomain( "FMT", Log.Scope.Method );
			Log.setDomain( "FMT", Log.DomainLevel.All);
			
			Log.info( "This is the default ConsoleLogger log line" );

			cl.logDate=			true;  
			cl.logTimeOfDay=	true;		Log.info( "LogDate= on, LogTimeOfDay= on" );
			cl.logLogCounter=	true;		Log.info( "LogLogCounter= true" ); Log.info( "LogLogCounter= true" ); Log.info( "LogLogCounter= true" );
			cl.logThreadInfo=	false;  	Log.info( "LogThreadInfo= false" );
			cl.logDomainName=	false;  	Log.info( "LogDomainName= false" );
			cl.logLogLevel=		false;  	Log.info( "LogLogLevel= false" );
			cl.logTimeDiff=		false;  	Log.info( "LogTimeDiff= false" );
			cl.logTimeElapsed=	false;  	Log.info( "LogTimeElapsed= false" );
			cl.logCallerInfo=	false;  	Log.info( "LogCallerInfo= false" );
			cl.logDate=			false;		Log.info( "LogDate= false" );
			cl.logTimeOfDay=	false;  	Log.info( "LogTimeOfDay= false" );
			cl.logLogCounter=	false;		Log.info( "LogLogCounter= false" ); Log.info( "LogLogCounter= false" ); Log.info( "LogLogCounter= false" );

			cl.FMT_MessagePrefix=MString.empty;	Log.info( "cl.FMT_MessagePrefix=\"\""); Log.info( "cl.FMT_MessagePrefix=\"\""); Log.info( "cl.FMT_MessagePrefix=\"\"");
			//#endif
		}


		/** ***********************************************************************************************
		 * <summary>	Log_TestMarker </summary>
		 **************************************************************************************************/
		@Test 
		public void Log_TestMarker()
		{
			clearCreateAndAddLoggers();

			Log.regDomain( "MARKER", Log.Scope.Method );
			Log.setDomain( "MARKER", Log.DomainLevel.All );


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
			Log.setMarker( markerDisposedGlobal,Log.Scope.None );
			Log.setMarker( markerGlobal,		Log.Scope.None );
			Log.setMarker( markerDisposedPkg,	Log.Scope.Package );
			Log.setMarker( markerPkg,			Log.Scope.Package );
			Log.setMarker( markerDisposedClass,	Log.Scope.Class );
			Log.setMarker( markerClass,			Log.Scope.Class );
			Log.setMarker( markerDisposedMethod,Log.Scope.Method );
			Log.setMarker( markerMethod,		Log.Scope.Method );

			Object[] markerpointer= new Object[1];

			Log.getMarker( markerpointer, Log.Scope.None );			Log.info( "The current global        marker is: " + markerpointer[0] );	 assertTrue( (String) markerpointer[0] == markerGlobal	);
			Log.getMarker( markerpointer, Log.Scope.Package );		Log.info( "The current package level marker is: " + markerpointer[0] );	 assertTrue( (String) markerpointer[0] == markerPkg		);
			Log.getMarker( markerpointer, Log.Scope.Class );		Log.info( "The current class   level marker is: " + markerpointer[0] );	 assertTrue( (String) markerpointer[0] == markerClass	);
			Log.getMarker( markerpointer, Log.Scope.Method );		Log.info( "The current method  level marker is: " + markerpointer[0] );	 assertTrue( (String) markerpointer[0] == markerMethod	);
		}


		/** ***********************************************************************************************
		 * <summary>	Log_TestThreads </summary>
		 **************************************************************************************************/
		@Test 
		public void Log_TestThreads()
		{
			clearCreateAndAddLoggers();

			Log.regDomain ( "TEST/THREAD1", Log.Scope.Method );
			Log.setDomain( "TEST/THREAD1", Log.DomainLevel.All );

			//#if ALOX_DEBUG || ALOX_REL_LOG
				cl.logThreadInfo=	true;
			//#endif  // ALOX_DEBUG || ALOX_REL_LOG

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
				Log.regDomain ( "TEST/THREAD2", Log.Scope.Method );
				Log.setDomain( "TEST/THREAD2", Log.DomainLevel.All );
	
				for ( int i= 0 ; i < 20 ; i++ )
				{ 
					Log.info( "This is a different Thread. Cnt= " + i );
					AWXU.sleep( 3 );
				}
			}
		}


		/** ***********************************************************************************************
		 * <summary>	Log_TestException. </summary>
		 **************************************************************************************************/
/* NIY		 
		@Test 
		public void Log_TestException()
		{
			clearCreateAndAddLoggers();

			Log.regDomain( "EXCEPT", Log.Scope.Method );
			Log.setDomain( "EXCEPT", Log.DomainLevel.All );


			Exception testException=  new Exception( "TestException Message", new Exception ("InnerException Message", new Exception("Inner, inner Exception") ) );

			LogTools.Exception( null, Log.Level.Warning, testException, "Logging an exception: " );
		}
*/
		/** ***********************************************************************************************
		 * <summary>	Log_TestException. </summary>
		 **************************************************************************************************/
		@Test 
		public void Log_TestMultiline()
		{
			clearCreateAndAddLoggers();

			//#if ALOX_DEBUG || ALOX_REL_LOG
				Log.regDomain( "MLine", Log.Scope.Method );
				Log.setDomain( "MLine", Log.DomainLevel.All );


				cl.multiLineMsgMode= 0;
				Log.info( "" );
				Log.info( "-------- ML Mode = 0 (single line) --------" );
				Log.logConfig( "MLine", Log.Level.Info, "Our Log configuration is:" );

				cl.multiLineMsgMode= 0;
				cl.multiLineDelimiterRepl= "~|~";
				Log.info( "" );
				Log.info( "-------- ML Mode = 0 (single line) with delimiter replacement set to ~|~ --------" );
				Log.logConfig( "MLine", Log.Level.Info, "Our Log configuration is:" );

				cl.multiLineMsgMode= 0;
				cl.multiLineDelimiter= "";
				Log.info( "" );
				Log.info( "-------- ML Mode = 0 (single line) with delimiter set to \"\" (stops multi line processing) --------" );
				Log.logConfig( "MLine", Log.Level.Info, "Our Log configuration is:" );
				cl.multiLineDelimiter= null; // reset

				cl.multiLineMsgMode= 1;
				Log.info( "" );
				Log.info( "-------- ML Mode = 1 (multi line, all meta info per line) --------" );
				Log.logConfig( "MLine", Log.Level.Info, "Our Log configuration is:" );
			
				cl.multiLineMsgMode= 2;
				Log.info( "" );
				Log.info( "-------- ML Mode = 2 (multi line, meta info blanked) --------" );
				Log.logConfig( "MLine", Log.Level.Info, "Our Log configuration is:" );

				cl.multiLineMsgMode= 3;
				Log.info( "" );
				Log.info( "-------- ML Mode = 3 (multi line, just caller info) --------" );
				Log.logConfig( "MLine", Log.Level.Info, "Our Log configuration is:" );

				cl.multiLineMsgMode= 4;
				Log.info( "" );
				Log.info( "-------- ML Mode = 4 (multi line, no meta, no caller, starts at pos 0)) --------" );
				Log.logConfig( "MLine", Log.Level.Info, "Our Log configuration is:" );
			//#endif
		}

		/** ***********************************************************************************************
		 * <summary>	Log_TestXML </summary>
		 **************************************************************************************************/
/*	NIY	 
		@Test 
		public void Log_TestInstance()
		{
			clearCreateAndAddLoggers();

			Log.regDomain( "INST", Log.Scope.Method );
			Log.setDomain( "INST", Log.DomainLevel.All );

			// simple type double
			{
				Double o= 3.14;
				
				LogTools.Instance( Log.Level.Info, o, 2, "Logging an object of type 'Double':", 1 );
			}

			// Double array
			{
				Double[] o= new Double[3];
				o[0]= 12.5;
				o[1]= 123456789.987654321;
				o[2]= 100;

				LogTools.Instance( Log.Level.Info, o, 2, "Logging an object of type 'Double[]':", 1 );
			}

			// byte array
			{
				byte[] o= new byte[3];
				o[0]= 2;
				o[1]= 8;
				o[2]= 16;

				LogTools.Instance( Log.Level.Info, o, 2, "Logging an object of type 'byte[]':", 1 );
			}


			// simple type String
			{
				String o= "Hello reflection";
				LogTools.Instance( Log.Level.Info, o, 2, "Logging an object of type 'String':", 1 );
			}


			// String array
			{
				String[] o= new String[3];
				o[0]= "Entry 0";
				o[1]= "Entry 1";
				o[2]= "Entry 2";

				LogTools.Instance( Log.Level.Info, o, 2, "Logging an object of type 'String[]':", 1 );
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
				//#if ALOX_DEBUG || ALOX_REL_LOG
					o[i++]= cl;
				//#endif  // ALOX_DEBUG || ALOX_REL_LOG
				o[i++]= "last filled object";

				LogTools.Instance( Log.Level.Info, o, 2, "Logging an object of type 'Object[]':", 1 );
			}

			// This thread
			{
				Thread o= Thread.currentThread();
				LogTools.Instance( Log.Level.Info, o, 2, ("Actual Thread: " + o.Name), 1 );
			}
		}
*/

		/** ***********************************************************************************************
		 * <summary>	Log_TestXML </summary>
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