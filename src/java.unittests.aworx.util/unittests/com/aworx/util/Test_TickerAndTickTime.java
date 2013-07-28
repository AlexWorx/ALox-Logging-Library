package unittests.com.aworx.util;

import static org.junit.Assert.*;

import java.util.*;

import org.junit.Test;

import com.aworx.util.*;


public class Test_TickerAndTickTime
{

	static	long		nanosPerSecond;
	static	long		nanosPerDay;
	static	long		nanosPerYear;

	// static constructor
	static 
	{
		nanosPerSecond= 1000 * 1000 * 1000;	
		nanosPerDay=	nanosPerSecond * 60 * 60 * 24;	
		nanosPerYear=	nanosPerDay * 365;	
	}

	@SuppressWarnings("static-method")
	@Test 
	public void TickerSpeedTest()
	{
		//Log.RemoveLoggers( );
		//Log.AddLogger( new ConsoleLogger() );
		//Log.RegDomain( "Ticker", true );

		// first let's test if the static ticker frequency value is properly set
		double tNow= Ticker.now();
		AWXU.sleep( 100 );
		tNow= Ticker.now() - tNow;
		double oneTenth= tNow / Ticker.internalFrequency;
		assertTrue ( Math.abs(oneTenth - 0.1d) <= 0.05 );
		

		// now to the speed test
		long tkSum= Ticker.now();
		long dtSum= System.nanoTime();

		for (int runs= 0; runs < 10; runs ++ )
		{
			int aLotOf= 1000 * 1000;
			System.out.println( "doing " + (aLotOf/1000)+ "k Ticker.Now() calls... "  );

			long tkMeasure= Ticker.now();
			long dtMeasure=System.nanoTime();
			for (int i= 0; i < aLotOf; i++ )
			{
				Ticker.now();
			}
			dtMeasure= System.nanoTime() - dtMeasure;
			tkMeasure= Ticker.now() - tkMeasure;
			System.out.println( "This took " + Ticker.toMillis(dtMeasure) +" ms (Measured with Ticker: "  + Ticker.toMillis(tkMeasure) +" ms)" );
			System.out.println( "DateTime diff: " + dtMeasure );
			System.out.println( "Ticker   diff: " + tkMeasure );
			System.out.println( "" );

			//Assert.IsTrue( tkMeasure >= dtMeasure );
		}

		dtSum= System.nanoTime() - dtSum;
		tkSum= Ticker.now() - tkSum;
		System.out.println( "The whole thing was " + Ticker.toMillis(dtSum) +" ms (Measured with Ticker: "  + Ticker.toMillis(tkSum) +" ms)" );
		System.out.println( "DateTime diff: " + dtSum );
		System.out.println( "Ticker   diff: " + tkSum );
	}



	@SuppressWarnings("static-method")
	@Test 
	public void TickerDateTimeConversion()
	{
		//Log.RemoveLoggers( );
		//Log.AddLogger( new ConsoleLogger() );
		//Log.RegDomain( "Ticker", true );

		long ticksNow= Ticker.now();

		// roundtrip 1 
		long millisEpochNow=	Ticker.toEpochMillis	( ticksNow );
		assertTrue ( Math.abs(millisEpochNow - (new Date()).getTime() ) <= 1);
		long ticksNowFromEpoch= Ticker.fromEpochMillis	( millisEpochNow );
		

		// roundtrip 2 
		long millisTodayFromDate=	(new Date()).getTime();
		long ticksTodayFromDate=	Ticker.fromEpochMillis( millisTodayFromDate );
		assertTrue ( Math.abs(ticksTodayFromDate - ticksNow ) <= 50000); // 50 microseconds allowed here 


		long millis5_1_70_3_51=			0 
								  +    (  4L * 24L * 60L * 60L * 1000L )
								  +	   (  3L       * 60L * 60L * 1000L )
								  +	   ( 51L             * 60L * 1000L );

		
		long millis5_1_71_3_51=			millis5_1_70_3_51
								  +    ( 365L * 24L * 60L * 60L * 1000L );

		long ticks5_1_70_3_51= Ticker.fromEpochMillis( millis5_1_70_3_51 );
		long ticks5_1_71_3_51= Ticker.fromEpochMillis( millis5_1_71_3_51 );


		Calendar calendar= new GregorianCalendar();
		calendar.set(1969, 4, 14, 8, 30);
		long millis_14_05_69_8_30= calendar.getTimeInMillis();

		long ticks_14_05_69_8_30=  Ticker.fromEpochMillis( millis_14_05_69_8_30 );
		
		// add 1 day, 2h, 3min and 4sec  days:
		long tomorrow= Ticker.add( ticksNow, 1, 2, 3, 4 );
		

		System.out.println( "Java Date conversion:    ");
		System.out.println( "Today: is:         "	+  ( (new Date()).toString() ) );
		System.out.println( "Today: is:         "	+  ( Ticker.toJavaDate( ticksNow,			null ).toString() ) );
		System.out.println( "Today: is:         "	+  (  ( new Date		  ( millisEpochNow)			 ).toString() ) );
		System.out.println( "Today: is:         "	+  ( Ticker.toJavaDate( ticksNowFromEpoch,	null ).toString() ) );
		System.out.println( "+1d, 2h,3m,4s:     "	+  ( Ticker.toJavaDate( tomorrow,			null ).toString() ) );
		System.out.println( "5.1.70 3:51:00:    " 	+  ( Ticker.toJavaDate( ticks5_1_70_3_51,	null ).toString() ) );
		System.out.println( "5.1.71 3:51:00:    " 	+  ( Ticker.toJavaDate( ticks5_1_71_3_51,	null ).toString() ) );
		System.out.println( "14.5.69 8:30:00:   " 	+  ( Ticker.toJavaDate( ticks_14_05_69_8_30,null ).toString() ) );
		
		GregorianCalendar cal= new GregorianCalendar();
		System.out.println( "Java Calendar conversion:    ");
		System.out.println( "Today: is:         "	+  ( Ticker.toJavaCalendar( ticksNow,			null ).toString() ) );
		cal.setTimeInMillis( millisEpochNow );
		System.out.println( "Today: is:         "	+  (  cal											  .toString() ) );
		System.out.println( "Today: is:         "	+  ( Ticker.toJavaCalendar( ticksNowFromEpoch,	null ).toString() ) );
		System.out.println( "+1d, 2h,3m,4s:     "	+  ( Ticker.toJavaCalendar( tomorrow,			null ).toString() ) );
		System.out.println( "5.1.70 3:51:00:    " 	+  ( Ticker.toJavaCalendar( ticks5_1_70_3_51,	null ).toString() ) );
		System.out.println( "5.1.71 3:51:00:    " 	+  ( Ticker.toJavaCalendar( ticks5_1_71_3_51,	null ).toString() ) );
		System.out.println( "14.5.69 8:30:00:   " 	+  ( Ticker.toJavaCalendar( ticks_14_05_69_8_30,null ).toString() ) );
	}



	@SuppressWarnings("static-method")
	@Test 
	public void TickerMicroSecsOutput()
	{
		//Log.RemoveLoggers( );
		//Log.AddLogger( new ConsoleLogger() );
		//Log.RegDomain( "Ticker", true );
		
		//((ConsoleLogger) Log.GetLogger( "Console" )).EnableVSDebugConsole=
		//((ConsoleLogger) Log.GetLogger( "Console" )).EnableAppConsole=		false;

		String quatschString= "--------------------------------------------#";

		System.out.println( "Lookout for microsecond output!" );

		for (int run= 10; run < 30; run ++ )
		{
			int actLoops= run * 200;

			long tickerTime= Ticker.now();

			int quatsch= 0;
			for (int i= 0; i < actLoops; i++ )
			{
				quatsch+= quatschString.indexOf( '#' ) ;
			}

			if ((run % 2) == 0 )
				Ticker.now() ;

			tickerTime= Ticker.now() - tickerTime;

			System.out.println( "Loop endend, run=" + run +" quatsch is=" + quatsch + " Ticker Time: " + Ticker.toMillis( tickerTime ) );

			//Assert.IsTrue( tkMeasure >= dtMeasure );
		}
		//((ConsoleLogger) Log.GetLogger( "Console" )).EnableVSDebugConsole=
		//((ConsoleLogger) Log.GetLogger( "Console" )).EnableAppConsole=		true;
		System.out.println( "Thats it!" );
	}


	@SuppressWarnings("static-method")
	@Test 
	public void Ticktime()
	{
		//Log.RemoveLoggers( );
		//Log.AddLogger( new ConsoleLogger() );
		//Log.RegDomain( "Ticker", true );

		System.out.println( "Nanos per 2013 years:    "			+ (nanosPerYear*2013) );

		TickTime tt= new TickTime();
		tt.setToNow();
		System.out.println( "TickTime value ticks:    --"			+ tt.get() );
		System.out.println( "TickTime value nanos:    "				+ Ticker.toNanos ( tt.get() ) );
		System.out.println( "TickTime value micros:   ---"			+ Ticker.toMicros( tt.get() ) );
		System.out.println( "TickTime value millis:   ---+++"		+ Ticker.toMillis( tt.get() ) );


		tt= new TickTime();
		tt.setToNow();
		AWXU.sleep( 50 );
		tt.measure();
		System.out.println( "TickTime age ticks  after 50ms wait:   --"		+ tt.age() );
		System.out.println( "TickTime age nanos  after 50ms wait:   "			+ Ticker.toNanos( tt.age() ) );
		System.out.println( "TickTime age micros after 50ms wait:   ---"		+ tt.ageInMicros() );
		System.out.println( "TickTime age millis after 50ms wait:   ---+++"	+ tt.ageInMillis() );
		
		tt.setToNow();
		AWXU.sleep( 50 );
		tt.measure();
		System.out.println(  "TickTime average ms after 2 times 50ms sleep: "	+ tt.getAverageMillis() );
		System.out.println(  "                                    in Hertz: "	+ tt.getAverageHertz() );

	}


}
