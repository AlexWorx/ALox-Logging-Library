using System;
using System.Threading;
using Microsoft.VisualStudio.TestTools.UnitTesting;

using System.Text;
using com.aworx.util;
using com.aworx.lox.loggers;

namespace com.aworx.lox.unittests
{

	[TestClass]
	public class Test_TickerAndTickTime
	{
		static	long		nanosPerSecond;
		static	long		nanosPerDay;
		static	long		nanosPerYear;

		// static constructor
		static Test_TickerAndTickTime()
		{
			nanosPerSecond= 1000 * 1000 * 1000;	
			nanosPerDay=	nanosPerSecond * 60 * 60 * 24;	
			nanosPerYear=	nanosPerDay * 365;	
		}

		[TestMethod]
		#if !WINDOWS_PHONE
			[TestCategory("Ticker")]
		#endif
		public void TickerSpeedTest()
		{
			Log.Reset();

			Log.AddLogger( new ConsoleLogger( "Console" ) );
			Log.MapThreadName( "UnitTest" );
			Log.RegDomain( "Ticker", Log.Scope.Method );

			// now to the speed test
			long tkSum= Ticker.Now();
			long dtSum= DateTime.Now.Ticks;

			for (int runs= 0; runs < 10; runs ++ )
			{
				int aLotOf= 1000 * 1000;
				Log.Info( "doing " + (aLotOf/1000)+ "k Ticker.Now() calls... "  );

				long tkMeasure= Ticker.Now();
				long dtMeasure= DateTime.Now.Ticks;
				for (int i= 0; i < aLotOf; i++ )
				{
					Ticker.Now();
				}
				dtMeasure= DateTime.Now.Ticks - dtMeasure;
				tkMeasure= Ticker.Now() - tkMeasure;
				Log.Info( "This took " + Ticker.ToMillis(dtMeasure) +" ms (Measured with Ticker: "  + Ticker.ToMillis(tkMeasure) +" ms)" );
				Log.Info( "DateTime diff: " + dtMeasure );
				Log.Info( "Ticker   diff: " + tkMeasure );
				Log.Info( "" );

				//Assert.IsTrue( tkMeasure >= dtMeasure );
			}

			dtSum= DateTime.Now.Ticks - dtSum;
			tkSum= Ticker.Now() - tkSum;
			Log.Info( "The whole thing was " + Ticker.ToMillis(dtSum) +" ms (Measured with Ticker: "  + Ticker.ToMillis(tkSum) +" ms)" );
			Log.Info( "DateTime diff: " + dtSum );
			Log.Info( "Ticker   diff: " + tkSum );
		}



		[TestMethod]
		#if !WINDOWS_PHONE
			[TestCategory("Ticker")]
		#endif
		public void TickerDateTimeConversion()
		{
			Log.Reset();

			Log.AddLogger( new ConsoleLogger( "Console" ) );
			Log.MapThreadName( "UnitTest" );
			Log.RegDomain( "Ticker", Log.Scope.Method );

			Log.Info( "DateTime.MinValue(): "	+ ( DateTime.MinValue.ToString() )	 );
			Log.Info( "DateTime.MaxValue(): "	+ ( DateTime.MaxValue.ToString() )	 );

			long ticksNow= Ticker.Now();

			// roundtrip 1 
			long millisEpochNow=	Ticker.ToEpochMillis	( ticksNow );
			long ticksNowFromEpoch= Ticker.FromEpochMillis	( millisEpochNow );

			Assert.IsTrue( Math.Abs( ticksNow - ticksNowFromEpoch ) < 50000 );


			// roundtrip 2
			long millis5_1_70_3_51=			0 
									  +    (  4L * 24L * 60L * 60L * 1000L )
									  +	   (  3L       * 60L * 60L * 1000L )
									  +	   ( 51L             * 60L * 1000L );

			
			long millis5_1_71_3_51=			millis5_1_70_3_51
									  +    ( 365L * 24L * 60L * 60L * 1000L );

			long ticks5_1_70_3_51= Ticker.FromEpochMillis( millis5_1_70_3_51 );
			long ticks5_1_71_3_51= Ticker.FromEpochMillis( millis5_1_71_3_51 );
			Assert.IsTrue( ticks5_1_70_3_51 < ticks5_1_71_3_51 );

			long millis5_1_70_3_51_back= Ticker.ToEpochMillis( ticks5_1_70_3_51 );
			long millis5_1_71_3_51_back= Ticker.ToEpochMillis( ticks5_1_71_3_51 );

			Assert.IsTrue( millis5_1_70_3_51_back == millis5_1_70_3_51 );
			Assert.IsTrue( millis5_1_71_3_51_back == millis5_1_71_3_51 );

			// add 1 day, 2h, 3min and 4sec  days:
			long tomorrow= Ticker.Add( ticksNow, 1, 2, 3, 4 );

			Log.Info( "Today: is:        "	+  ( DateTime.Now.ToString()								 ) );
			Log.Info( "Today: is:        "	+  ( Ticker.ToDotNetDateTime (ticksNow			).ToString() ) );
			Log.Info( "Today: is:        "	+  ( Ticker.ToDotNetDateTime (ticksNowFromEpoch	).ToString() ) );
			Log.Info( "+1d, 2h,3m,4s:    "	+  ( Ticker.ToDotNetDateTime (tomorrow			).ToString() ) );
			Log.Info( "5.1.70 3:51:00:   "	+  ( Ticker.ToDotNetDateTime (ticks5_1_70_3_51	).ToString() ) );
			Log.Info( "5.1.71 3:51:00:   "	+  ( Ticker.ToDotNetDateTime (ticks5_1_71_3_51	).ToString() ) );
		}
	
		[TestMethod]
		#if !WINDOWS_PHONE
			[TestCategory("Ticker")]
		#endif
		public void TickerMicroSecsOutput()
		{
			Log.Reset();

			Log.AddLogger( new ConsoleLogger( "Console" ) );
			Log.MapThreadName( "UnitTest" );
			Log.RegDomain( "Ticker", Log.Scope.Method );

			#if ALOX_DEBUG 
				((ConsoleLogger) Log.GetLogger( "Console" )).EnableVSDebugConsole=
				((ConsoleLogger) Log.GetLogger( "Console" )).EnableAppConsole=		false;
			#endif
			String quatschString= "--------------------------------------------#";

			Log.Info( "Lookout for microsecond output!" );

			for (int run= 10; run < 30; run ++ )
			{
				int actLoops= run * 200;

				long tickerTime= Ticker.Now();

				int quatsch= 0;
				for (int i= 0; i < actLoops; i++ )
				{
					quatsch+= quatschString.IndexOf( '#' ) ;
				}

				if ((run % 2) == 0 )
					Ticker.Now() ;

				tickerTime= Ticker.Now() - tickerTime;

				Log.Info( "Loop endend, run=" + run +" quatsch is=" + quatsch + " Ticker Time: " + Ticker.ToMillis( tickerTime ) );

				//Assert.IsTrue( tkMeasure >= dtMeasure );
			}
			#if ALOX_DEBUG 
				((ConsoleLogger) Log.GetLogger( "Console" )).EnableVSDebugConsole=
				((ConsoleLogger) Log.GetLogger( "Console" )).EnableAppConsole=		true;
			#endif
			Log.Info( "Thats it!" );
		}


		[TestMethod]
		#if !WINDOWS_PHONE
			[TestCategory("Ticker")]
		#endif
		public void Ticktime()
		{
			Log.Reset();

			Log.AddLogger( new ConsoleLogger( "Console" ) );
			Log.MapThreadName( "UnitTest" );
			Log.RegDomain( "Ticker", Log.Scope.Method );

			Log.Info( "Nanos per 2013 years:    "			+ (nanosPerYear*2013) );

			TickTime tt= new TickTime();
			tt.SetToNow();
			Log.Info( "TickTime value ticks:    --"			+ tt.Get() );
			Log.Info( "TickTime value nanos:    "			+ Ticker.ToNanos ( tt.Get() ) );
			Log.Info( "TickTime value micros:   ---"		+ Ticker.ToMicros( tt.Get() ) );
			Log.Info( "TickTime value millis:   ---+++"		+ Ticker.ToMillis( tt.Get() ) );


			tt= new TickTime();
			tt.SetToNow();
			AWXU.Sleep( 50 );
			tt.Measure();
			Log.Info( "TickTime age ticks  after 50ms wait:   --"		+ tt.Age() );
			Log.Info( "TickTime age nanos  after 50ms wait:   "			+ Ticker.ToNanos( tt.Age() ) );
			Log.Info( "TickTime age micros after 50ms wait:   ---"		+ tt.AgeInMicros() );
			Log.Info( "TickTime age millis after 50ms wait:   ---+++"	+ tt.AgeInMillis() );

			tt.SetToNow();
			AWXU.Sleep( 50 );
			tt.Measure();
			Log.Info( "TickTime average ms after 2 times 50ms sleep: "	+ tt.GetAverageMillis() );
			Log.Info( "                                    in Hertz: "	+ tt.GetAverageHertz() );
		}



	}
}
