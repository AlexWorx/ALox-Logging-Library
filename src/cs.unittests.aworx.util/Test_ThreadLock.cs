using System;
using System.Threading;
using Microsoft.VisualStudio.TestTools.UnitTesting;

using System.Text;
using com.aworx.util;
using com.aworx.lox.loggers;

namespace com.aworx.lox.unittests
{
	[TestClass]
	public class Test_ThreadLock
	{
		[TestMethod]
		#if !WINDOWS_PHONE
			[TestCategory("ThreadLock")]
		#endif
		public void ThreadLock_SimpleTests()
		{
			Log.Reset();
			Log.AddLogger( new ConsoleLogger( "Console" ) );
			Log.MapThreadName( "UnitTest" );
			Log.RegDomain( "TestTLock", Log.Scope.Method );
			Log.SetDomain( "AWXU", Log.DomainLevel.All );

			// lock a recursive lock 
			ThreadLock aLock= new ThreadLock();
			aLock.UseAssertions= false;

			aLock.Aquire();
			aLock.Release();

			aLock.Aquire(); 								Assert.IsTrue ( !aLock.ToString().StartsWith("null") );
			aLock.Aquire();									Assert.IsTrue ( !aLock.ToString().StartsWith("null") );
			aLock.Release();								Assert.IsTrue ( !aLock.ToString().StartsWith("null") );
															                      
			aLock.Aquire();									Assert.IsTrue ( !aLock.ToString().StartsWith("null") );
			aLock.Release();								Assert.IsTrue ( !aLock.ToString().StartsWith("null") );
			aLock.Release();								Assert.IsTrue (  aLock.ToString().StartsWith("null") );

			// set unsafe
			aLock.SetUnsafe( true );						Assert.IsTrue ( aLock.ToString().StartsWith("null") );
			aLock.SetUnsafe( false );						Assert.IsTrue ( aLock.ToString().StartsWith("null") );

			aLock.SetUnsafe( true );						Assert.IsTrue ( aLock.ToString().StartsWith("null") );
			aLock.Aquire();									Assert.IsTrue ( aLock.ToString().StartsWith("null") );
			aLock.Release();								Assert.IsTrue ( aLock.ToString().StartsWith("null") );

			// unsafe
			aLock.Aquire();									Assert.IsTrue ( aLock.ToString().StartsWith("null") );
			Log.Info("One warning should come now: ");
			aLock.SetUnsafe( false );						Assert.IsTrue ( aLock.ToString().StartsWith("null") );
		
			// safe (new lock)
			aLock= new ThreadLock();
			aLock.UseAssertions= false;
			aLock.Aquire();									Assert.IsTrue ( !aLock.ToString().StartsWith("null") );
			Log.Info("One warning should come now: ");
			aLock.SetUnsafe( true );						Assert.IsTrue ( !aLock.ToString().StartsWith("null") );

		
			// test warnings (10) locks:
			aLock= new ThreadLock();
			aLock.UseAssertions= false;
			Log.Info("Two warnings should come now: ");
			for (int i= 0; i<20; i++)	
				aLock.Aquire();
			Assert.IsTrue ( !aLock.ToString().StartsWith("null") );
			for (int i= 0; i<20; i++)	
				aLock.Release();
			Assert.IsTrue ( aLock.ToString().StartsWith("null") );

			// test a non-recursive lock 
			aLock= new ThreadLock( false );
			aLock.UseAssertions= false;
			aLock.Aquire();				Assert.IsTrue ( !aLock.ToString().StartsWith("null") );
			aLock.Aquire();				Assert.IsTrue ( !aLock.ToString().StartsWith("null") );
			aLock.Release();				Assert.IsTrue ( aLock.ToString().StartsWith("null") );
		
			Log.Info("One warning should come now: ");
			aLock.Release();				Assert.IsTrue ( aLock.ToString().StartsWith("null") );

		}

		[TestMethod]
		#if !WINDOWS_PHONE
			[TestCategory("ThreadLock")]
		#endif
		public void ThreadLock_Threaded()
		{
			Log.Reset();

			Log.AddLogger( new ConsoleLogger( "Console" ) );
			Log.MapThreadName( "UnitTest" );
			Log.RegDomain( "TestTLock", Log.Scope.SourceFile );
			Log.SetDomain( "AWXU", Log.DomainLevel.All );

			ThreadLock aLock= new ThreadLock();

			Test_ThreadLock_SharedInt shared= new Test_ThreadLock_SharedInt();

			Log.Info("starting thread locked");
			aLock.Aquire();		
			Test_ThreadLock_TestThreadParams tParam= new Test_ThreadLock_TestThreadParams( aLock, 10, 1, true, shared );

			Thread thread = new Thread( new ParameterizedThreadStart( Test_ThreadLock_Test_run ) );
			thread.Name= "A Thread";
			thread.Start( tParam );

			Log.Info("We wait 1100 ms. This should give a warning! ");
			AWXU.Sleep( 1100 );
			aLock.Release();	
		
			// wait until t ended
			while (thread.IsAlive)
				AWXU.Sleep( 1 );
			
			// now we do the same with a higher wait limit, no erro should come
			aLock.WaitALoxWarningLimit= Ticker.FromMillis( 1200 );
			aLock.Aquire();		
			tParam= new Test_ThreadLock_TestThreadParams( aLock, 10, 1, true, shared );
			thread = new Thread( new ParameterizedThreadStart( Test_ThreadLock_Test_run ) );
			thread.Start( tParam );
			Log.Info("We wait 900 ms. This should NOT give a warning! ");
			AWXU.Sleep( 900 );
			aLock.Release();	
		
			// wait until t ended
			while (thread.IsAlive)
				AWXU.Sleep( 1 );

		}

		[TestMethod]
		#if !WINDOWS_PHONE
			[TestCategory("ThreadLock")]
		#endif
		public void ThreadLock_HeavyLoad()
		{
			Log.Reset();
			Log.AddLogger( new ConsoleLogger( "Console" ) );
			Log.MapThreadName( "UnitTest" );
			Log.RegDomain( "TestTLock", Log.Scope.SourceFile );
			Log.SetDomain( "AWXU", Log.DomainLevel.All );

			ThreadLock aLock= new ThreadLock();

			// uncomment this for unsafe mode
			// lock.setUnsafe( true );

			Test_ThreadLock_SharedInt	shared=		new Test_ThreadLock_SharedInt();
			int							holdTime=	0;
			int							repeats=	5000;
			bool						verbose=	false;
		
			Test_ThreadLock_TestThreadParams p1= new Test_ThreadLock_TestThreadParams( aLock, holdTime, repeats, verbose, shared );
			Test_ThreadLock_TestThreadParams p2= new Test_ThreadLock_TestThreadParams( aLock, holdTime, repeats, verbose, shared );
			Test_ThreadLock_TestThreadParams p3= new Test_ThreadLock_TestThreadParams( aLock, holdTime, repeats, verbose, shared );
			Log.Info("starting three threads");

			Thread t1= new Thread( new ParameterizedThreadStart( Test_ThreadLock_Test_run ) );
			Thread t2= new Thread( new ParameterizedThreadStart( Test_ThreadLock_Test_run ) );
			Thread t3= new Thread( new ParameterizedThreadStart( Test_ThreadLock_Test_run ) );
			t1.Start( p1 );
			t2.Start( p2 );
			t3.Start( p3 );
		
			// wait until all ended
			while ( t1.IsAlive || t2.IsAlive || t3.IsAlive )
				AWXU.Sleep( 1 );
			
			Log.Info("All threads ended. Shared value=" + shared.val );
			
			Assert.IsTrue( shared.val == 0 );

		}

		[TestMethod]
		#if !WINDOWS_PHONE
			[TestCategory("ThreadLock")]
		#endif
		public void ThreadLock_SpeedTest()
		{
			Log.Reset();

			Log.AddLogger( new ConsoleLogger( "Console" ) );
			Log.MapThreadName( "UnitTest" );
			Log.RegDomain( "TestTLock", Log.Scope.Method );
			Log.SetDomain( "AWXU", Log.DomainLevel.All );

			ThreadLock aLock= new ThreadLock();

			int		repeats=	100000;
			int		rrepeats=	5;
		
			TickTime stopwatch= new TickTime();
			for ( int r= 0; r < rrepeats; r ++)
			{
				Log.Info("Run " + rrepeats );
			
				aLock.SetUnsafe( false );
				stopwatch.SetToNow();
				for ( int i= 0; i < repeats; i++ )
				{
					aLock.Aquire();
					aLock.Release();
				}
				long time= stopwatch.AgeInMillis();
				Log.Info("Safe mode, " + repeats + " lock/unlock ops: " + time + " ms" );
			
				aLock.SetUnsafe( true );
				stopwatch.SetToNow();
				for ( int i= 0; i < repeats; i++ )
				{
					//aLock.aquire();
					//aLock.release();

					// in java, adding the following two loops, results in similar execution speed
					for ( int tt= 0; tt < 70; tt++ )
						i+= tt;
					for ( int tt= 0; tt < 70; tt++ )
						i-= tt;
				}
				time= stopwatch.AgeInMillis();
				Log.Info("Unsafe mode, " + repeats + " lock/unlock ops: " + time + " ms" );
			}
		}

		public class Test_ThreadLock_SharedInt
		{
			public int val= 0;
		}

		public class Test_ThreadLock_TestThreadParams
		{
			public		ThreadLock	aLock;
			public		int 		holdTime;
			public		int			repeats;
			public		bool		verbose;
			public 		int 		result= 1;
			public		Test_ThreadLock_SharedInt shared;
	
			public Test_ThreadLock_TestThreadParams( ThreadLock aLock, int holdTime, int repeats, bool verbose, Test_ThreadLock_SharedInt shared )
			{
				this.aLock=		aLock;
				this.holdTime=  holdTime;
				this.repeats=	repeats;
				this.verbose=	verbose;	
				this.shared=	shared;
			}
		}
	
		public void Test_ThreadLock_Test_run( Object o)
		{
			Test_ThreadLock_TestThreadParams p= o as Test_ThreadLock_TestThreadParams;
			for ( int i= 0; i < p.repeats ; i++ )
			{
				if (p.verbose) { Log.Info("Thread: "+ Thread.CurrentThread.Name +" acuiring lock..."); }
				p.aLock.Aquire();
				if (p.verbose) { Log.Info("Thread: "+ Thread.CurrentThread.Name +" has lock."); }
				
					int sVal= ++p.shared.val;
				
					AWXU.Sleep( p.holdTime );
				
					p.shared.val= sVal -1;
				
				if (p.verbose) { Log.Info("Thread: "+ Thread.CurrentThread.Name +" releasing lock."); }
				p.aLock.Release();
				if (p.verbose) { Log.Info("Thread: "+ Thread.CurrentThread.Name +" released lock."); }
			}
		
			p.result= 0;
			Log.Info("Thread: "+ Thread.CurrentThread.Name +" terminates.");
		}

	}
}
