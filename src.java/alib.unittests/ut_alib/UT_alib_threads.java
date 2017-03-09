// #################################################################################################
//  Unit Tests - AWorx Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
package ut_alib;
import org.junit.Test;

import com.aworx.lib.ALIB;
import com.aworx.lib.lang.LockMode;
import com.aworx.lib.lang.Report;
import com.aworx.lib.lang.Safeness;
import com.aworx.lib.threads.SmartLock;
import com.aworx.lib.threads.ThreadLock;
import com.aworx.lib.time.Ticks;
import com.aworx.lox.Log;
import com.aworx.lox.Scope;

import ut_com_aworx.AWorxUnitTesting;

public class UT_alib_threads  extends AWorxUnitTesting
{
    //--------------------------------------------------------------------------------------------------
    //--- Simple
    //--------------------------------------------------------------------------------------------------
    @SuppressWarnings("static-method")
    @Test
    public void ThreadLock_Simple()
    {
        UT_INIT();
        Report.getDefault().pushHaltFlags( false, false );

        // lock a recursive lock
        ThreadLock aLock= new ThreadLock();
        aLock.acquire();
        aLock.release();

        aLock.acquire();                                UT_TRUE (  aLock.toString().startsWith("Locked")   );
        aLock.acquire();                                UT_TRUE (  aLock.toString().startsWith("Locked")   );
        aLock.release();                                UT_TRUE (  aLock.toString().startsWith("Locked")   );

        aLock.acquire();                                UT_TRUE (  aLock.toString().startsWith("Locked")   );
        aLock.release();                                UT_TRUE (  aLock.toString().startsWith("Locked")   );
        aLock.release();                                UT_TRUE (  aLock.toString().startsWith("Unlocked") );

        // set unsafe
        aLock.setSafeness( Safeness.UNSAFE );           UT_TRUE (  aLock.toString().startsWith("Unlocked") );
                                                        UT_TRUE (  aLock.toString().contains  ("Unsafe")   );
        aLock.setSafeness( Safeness.SAFE );             UT_TRUE ( !aLock.toString().contains  ("Unsafe")   );

        aLock.setSafeness( Safeness.UNSAFE );           UT_TRUE (  aLock.toString().startsWith("Unlocked") );
                                                        UT_TRUE (  aLock.toString().contains  ("Unsafe") );
        aLock.acquire();                                UT_TRUE (  aLock.toString().startsWith("Locked")   );
        aLock.release();                                UT_TRUE (  aLock.toString().startsWith("Unlocked") );
                                                        UT_TRUE (  aLock.toString().contains  ("Unsafe") );

        // unsafe
        aLock.acquire();                                UT_TRUE (  aLock.toString().startsWith("Locked")   );
        UT_PRINT("One warning should come now: ");
        aLock.setSafeness( Safeness.SAFE );             UT_TRUE (  aLock.toString().startsWith("Locked")   );
                                                        UT_TRUE (  aLock.toString().contains  ("Unsafe")   );

        // safe (new lock)
        aLock= new ThreadLock();
        aLock.acquire();                                UT_TRUE (  aLock.toString().startsWith("Locked") );
                                                        UT_TRUE ( !aLock.toString().contains  ("Unsafe")   );
        UT_PRINT("One warning should come now: ");
        aLock.setSafeness( Safeness.UNSAFE );           UT_TRUE ( !aLock.toString().startsWith("null") );
                                                        UT_TRUE ( !aLock.toString().contains  ("Unsafe")   );


        // test warnings (10) locks:
        aLock= new ThreadLock();
        UT_PRINT("Two warnings should come now: ");
        for (int i= 0; i<20; i++)
            aLock.acquire();
        UT_TRUE (  aLock.toString().startsWith("Locked") );
        for (int i= 0; i<20; i++)
            aLock.release();
        UT_TRUE (  aLock.toString().startsWith("Unlocked") );

        // test a non-recursive lock
        aLock= new ThreadLock( LockMode.SINGLE_LOCKS );
        aLock.acquire();                UT_TRUE (  aLock.toString().startsWith("Locked")   );
        aLock.acquire();                UT_TRUE (  aLock.toString().startsWith("Locked")   );
        aLock.release();                UT_TRUE (  aLock.toString().startsWith("Unlocked") );

        UT_PRINT("One warning should come now: ");
        aLock.release();                UT_TRUE (  aLock.toString().startsWith("Unlocked") );
        Report.getDefault().popHaltFlags();
    }

    //--------------------------------------------------------------------------------------------------
    //--- Threaded
    //--------------------------------------------------------------------------------------------------
    @Test
    public void ThreadLock_Threaded()
    {
        UT_INIT();

        Log.setDomain( "TL_Threaded", Scope.METHOD );

        ThreadLock aLock= new ThreadLock();
        Test_ThreadLock_SharedInt shared= new Test_ThreadLock_SharedInt();
        UT_PRINT("starting thread locked");
        aLock.acquire();
        Test_ThreadLock_TestThread t= new Test_ThreadLock_TestThread( "TT", aLock, 10, 1, true, shared );
        t.start();
        UT_PRINT("We wait 1100 ms. This should give a warning! ");
        ALIB.sleepMillis( 1100 );
        aLock.release();

        // wait until t ended
        while (t.isAlive())
            ALIB.sleepMillis( 1 );

        // now we do the same with a lower wait limit, no error should come
        aLock.waitWarningTimeLimitInMillis= 5;
        aLock.acquire();
        t= new Test_ThreadLock_TestThread( "TT", aLock, 10, 1, true, shared );
        t.start();
        UT_PRINT("We wait 1 ms. This should NOT give a warning! ");
        ALIB.sleepMillis( 1 );
        aLock.release();

        // wait until t ended
        while (t.isAlive())
            ALIB.sleepMillis( 1 );
    }


    //--------------------------------------------------------------------------------------------------
    //--- SmartLock
    //--------------------------------------------------------------------------------------------------
    @Test
    public void ThreadLock_SmartLock()
    {
        UT_INIT();
        Report.getDefault().pushHaltFlags( false, false );

            // SmartLock with null-users
            {
                                                                                                                                              utWriter.lox.cntLogCalls= 0;
                SmartLock sl= new SmartLock();      UT_TRUE( sl.getSafeness() == Safeness.UNSAFE );  UT_TRUE( utWriter.lox.cntLogCalls== 0 ); utWriter.lox.cntLogCalls= 0;
                sl.addAcquirer   ( null );          UT_TRUE( sl.getSafeness() == Safeness.UNSAFE );  UT_TRUE( utWriter.lox.cntLogCalls== 0 ); utWriter.lox.cntLogCalls= 0;
                sl.addAcquirer   ( null );          UT_TRUE( sl.getSafeness() == Safeness.SAFE   );  UT_TRUE( utWriter.lox.cntLogCalls== 0 ); utWriter.lox.cntLogCalls= 0;
                sl.addAcquirer   ( null );          UT_TRUE( sl.getSafeness() == Safeness.SAFE   );  UT_TRUE( utWriter.lox.cntLogCalls== 0 ); utWriter.lox.cntLogCalls= 0;
                sl.removeAcquirer( null );          UT_TRUE( sl.getSafeness() == Safeness.SAFE   );  UT_TRUE( utWriter.lox.cntLogCalls== 0 ); utWriter.lox.cntLogCalls= 0;
                sl.removeAcquirer( null );          UT_TRUE( sl.getSafeness() == Safeness.UNSAFE );  UT_TRUE( utWriter.lox.cntLogCalls== 0 ); utWriter.lox.cntLogCalls= 0;
                sl.removeAcquirer( null );          UT_TRUE( sl.getSafeness() == Safeness.UNSAFE );  UT_TRUE( utWriter.lox.cntLogCalls== 0 ); utWriter.lox.cntLogCalls= 0;
                UT_PRINT( "One warning should follow" ); utWriter.lox.cntLogCalls= 0;
                sl.removeAcquirer( null );          UT_TRUE( sl.getSafeness() == Safeness.UNSAFE );  UT_TRUE( utWriter.lox.cntLogCalls== 1 ); utWriter.lox.cntLogCalls= 0;
            }

            // SmartLock with threadlocks
            {
                ThreadLock tl1 = new ThreadLock();
                ThreadLock tl2 = new ThreadLock();
                ThreadLock tl3 = new ThreadLock();
                SmartLock  sl= new SmartLock();    UT_TRUE( sl.getSafeness() == Safeness.UNSAFE );  UT_TRUE( utWriter.lox.cntLogCalls== 0 ); utWriter.lox.cntLogCalls= 0;
                sl.addAcquirer   ( tl1 );          UT_TRUE( sl.getSafeness() == Safeness.UNSAFE );  UT_TRUE( utWriter.lox.cntLogCalls== 0 ); utWriter.lox.cntLogCalls= 0;
                sl.addAcquirer   ( tl2 );          UT_TRUE( sl.getSafeness() == Safeness.SAFE   );  UT_TRUE( utWriter.lox.cntLogCalls== 0 ); utWriter.lox.cntLogCalls= 0;
                sl.addAcquirer   ( tl3 );          UT_TRUE( sl.getSafeness() == Safeness.SAFE   );  UT_TRUE( utWriter.lox.cntLogCalls== 0 ); utWriter.lox.cntLogCalls= 0;
                sl.removeAcquirer( tl3 );          UT_TRUE( sl.getSafeness() == Safeness.SAFE   );  UT_TRUE( utWriter.lox.cntLogCalls== 0 ); utWriter.lox.cntLogCalls= 0;
                UT_PRINT( "One warning should follow" ); utWriter.lox.cntLogCalls= 0;
                sl.removeAcquirer( tl3 );          UT_TRUE( sl.getSafeness() == Safeness.SAFE   );  UT_TRUE( utWriter.lox.cntLogCalls== 1 ); utWriter.lox.cntLogCalls= 0;
                sl.removeAcquirer( tl2 );          UT_TRUE( sl.getSafeness() == Safeness.UNSAFE );  UT_TRUE( utWriter.lox.cntLogCalls== 0 ); utWriter.lox.cntLogCalls= 0;
                sl.removeAcquirer( tl1 );          UT_TRUE( sl.getSafeness() == Safeness.UNSAFE );  UT_TRUE( utWriter.lox.cntLogCalls== 0 ); utWriter.lox.cntLogCalls= 0;
                UT_PRINT( "One warning should follow" ); utWriter.lox.cntLogCalls= 0;
                sl.removeAcquirer( tl1 );          UT_TRUE( sl.getSafeness() == Safeness.UNSAFE );  UT_TRUE( utWriter.lox.cntLogCalls== 1 ); utWriter.lox.cntLogCalls= 0;
            }

            // mixed
            {
                ThreadLock tl1 = new ThreadLock();
                ThreadLock tl2 = new ThreadLock();
                ThreadLock tl3 = new ThreadLock();
                UT_PRINT( "Some error messages should follow" ); utWriter.lox.cntLogCalls= 0;
                SmartLock  sl= new SmartLock();     UT_TRUE( sl.getSafeness() == Safeness.UNSAFE );  UT_TRUE( utWriter.lox.cntLogCalls== 0 );
                utWriter.lox.cntLogCalls= 0;
                sl.addAcquirer   ( tl1  );          UT_TRUE( sl.getSafeness() == Safeness.UNSAFE );  UT_TRUE( utWriter.lox.cntLogCalls== 0 );
                sl.addAcquirer   ( null );          UT_TRUE( sl.getSafeness() == Safeness.SAFE   );  UT_TRUE( utWriter.lox.cntLogCalls== 0 );
                sl.addAcquirer   ( null );          UT_TRUE( sl.getSafeness() == Safeness.SAFE   );  UT_TRUE( utWriter.lox.cntLogCalls== 0 );
                sl.addAcquirer   ( tl2  );          UT_TRUE( sl.getSafeness() == Safeness.SAFE   );  UT_TRUE( utWriter.lox.cntLogCalls== 0 );
                sl.addAcquirer   ( null );          UT_TRUE( sl.getSafeness() == Safeness.SAFE   );  UT_TRUE( utWriter.lox.cntLogCalls== 0 );
                UT_PRINT( "One warning should follow" ); utWriter.lox.cntLogCalls= 0;
                sl.addAcquirer   ( tl2  );          UT_TRUE( sl.getSafeness() == Safeness.SAFE   );  UT_TRUE( utWriter.lox.cntLogCalls== 1 ); utWriter.lox.cntLogCalls= 0;
                sl.addAcquirer   ( null );          UT_TRUE( sl.getSafeness() == Safeness.SAFE   );  UT_TRUE( utWriter.lox.cntLogCalls== 0 );
                sl.addAcquirer   ( tl3  );          UT_TRUE( sl.getSafeness() == Safeness.SAFE   );  UT_TRUE( utWriter.lox.cntLogCalls== 0 );
                sl.removeAcquirer( null );          UT_TRUE( sl.getSafeness() == Safeness.SAFE   );  UT_TRUE( utWriter.lox.cntLogCalls== 0 );
                sl.removeAcquirer( tl1  );          UT_TRUE( sl.getSafeness() == Safeness.SAFE   );  UT_TRUE( utWriter.lox.cntLogCalls== 0 );
                UT_PRINT( "One warning should follow" ); utWriter.lox.cntLogCalls= 0;
                sl.removeAcquirer( tl1  );          UT_TRUE( sl.getSafeness() == Safeness.SAFE   );  UT_TRUE( utWriter.lox.cntLogCalls== 1 ); utWriter.lox.cntLogCalls= 0;
                sl.removeAcquirer( null );          UT_TRUE( sl.getSafeness() == Safeness.SAFE   );  UT_TRUE( utWriter.lox.cntLogCalls== 0 );
                sl.removeAcquirer( tl3  );          UT_TRUE( sl.getSafeness() == Safeness.SAFE   );  UT_TRUE( utWriter.lox.cntLogCalls== 0 );
                sl.removeAcquirer( null );          UT_TRUE( sl.getSafeness() == Safeness.SAFE   );  UT_TRUE( utWriter.lox.cntLogCalls== 0 );
                sl.removeAcquirer( null );          UT_TRUE( sl.getSafeness() == Safeness.UNSAFE );  UT_TRUE( utWriter.lox.cntLogCalls== 0 );
                UT_PRINT( "Three warnings should follow" ); utWriter.lox.cntLogCalls= 0;
                sl.removeAcquirer( null );          UT_TRUE( sl.getSafeness() == Safeness.UNSAFE );  UT_TRUE( utWriter.lox.cntLogCalls== 1 ); utWriter.lox.cntLogCalls= 0;
                sl.removeAcquirer( null );          UT_TRUE( sl.getSafeness() == Safeness.UNSAFE );  UT_TRUE( utWriter.lox.cntLogCalls== 1 ); utWriter.lox.cntLogCalls= 0;
                sl.removeAcquirer( tl3  );          UT_TRUE( sl.getSafeness() == Safeness.UNSAFE );  UT_TRUE( utWriter.lox.cntLogCalls== 1 ); utWriter.lox.cntLogCalls= 0;
                sl.removeAcquirer( tl2  );          UT_TRUE( sl.getSafeness() == Safeness.UNSAFE );  UT_TRUE( utWriter.lox.cntLogCalls== 0 );
                UT_PRINT( "One warning should follow" ); utWriter.lox.cntLogCalls= 0;
                sl.removeAcquirer( null );          UT_TRUE( sl.getSafeness() == Safeness.UNSAFE );  UT_TRUE( utWriter.lox.cntLogCalls== 1 ); utWriter.lox.cntLogCalls= 0;
            }
            Report.getDefault().popHaltFlags();
    }

    //--------------------------------------------------------------------------------------------------
    //--- HeavyLoad
    //--------------------------------------------------------------------------------------------------
    @Test
    public void ThreadLock_HeavyLoad()
    {
        UT_INIT();

        Log.setDomain( "TL_HeavyLoad", Scope.METHOD );
        ThreadLock aLock= new ThreadLock();

        // uncomment this for unsafe mode
        // lock.setUnsafe( true );

        Test_ThreadLock_SharedInt    shared=        new Test_ThreadLock_SharedInt();
        int                            holdTime=    0;
        int                            repeats=    5000;
        boolean                        verbose=    false;

        Test_ThreadLock_TestThread t1= new Test_ThreadLock_TestThread( "A", aLock, holdTime, repeats, verbose, shared );
        Test_ThreadLock_TestThread t2= new Test_ThreadLock_TestThread( "B", aLock, holdTime, repeats, verbose, shared );
        Test_ThreadLock_TestThread t3= new Test_ThreadLock_TestThread( "C", aLock, holdTime, repeats, verbose, shared );
        UT_PRINT("starting three threads");
        t1.start();
        t2.start();
        t3.start();

        // wait until all ended
        while ( t1.isAlive() || t2.isAlive() || t3.isAlive() )
            ALIB.sleepMillis( 1 );

        UT_PRINT("All threads ended. Shared value=" + shared.val );

        UT_TRUE( shared.val == 0 );
    }


    //--------------------------------------------------------------------------------------------------
    //--- SpeedTest
    //--------------------------------------------------------------------------------------------------
    @SuppressWarnings("static-method")
    @Test
    public void ThreadLock_SpeedTest()
    {
        UT_INIT();

        Log.setDomain( "TL_SpeedTest", Scope.METHOD );
        ThreadLock aLock= new ThreadLock();

        int        repeats=    100000;
        int        rrepeats=    5;


        Ticks stopwatch= new Ticks();
        for ( int r= 0; r < rrepeats; r ++)
        {
            UT_PRINT( "" );
            UT_PRINT("Run " + rrepeats );

            aLock.setSafeness( Safeness.SAFE );
            stopwatch.set();
            for ( int i= 0; i < repeats; i++ )
            {
                aLock.acquire();
                aLock.release();
            }
            long time= stopwatch.age().inMillis();
            UT_PRINT("Safe mode, " + repeats + " lock/unlock ops: " + time + " ms" );

            aLock.setSafeness( Safeness.UNSAFE );
            stopwatch.set();
            for ( int i= 0; i < repeats; i++ )
            {
                aLock.acquire();
                aLock.release();

                // in java, adding the following two loops, results in similar execution speed
                for ( int tt= 0; tt < 70; tt++ )
                    i+= tt;
                for ( int tt= 0; tt < 70; tt++ )
                    i-= tt;
            }
            time= stopwatch.age().inMillis();
            UT_PRINT("Unsafe mode, " + repeats + " lock/unlock ops: " + time + " ms" );
        }
    }


//--------------------------------------------------------------------------------------------------
//--- helper classes
//--------------------------------------------------------------------------------------------------


public class Test_ThreadLock_SharedInt
{
    int val= 0;
}

public class Test_ThreadLock_TestThread extends Thread
{
    public  ThreadLock                lock;
    public  int                       holdTime;
    public  int                       repeats;
    public  boolean                   verbose;
    public  int                       result= 1;
    public  Test_ThreadLock_SharedInt shared;

    public Test_ThreadLock_TestThread( String name, ThreadLock lock, int holdTime, int repeats, boolean verbose, Test_ThreadLock_SharedInt shared )
    {
        super( name );
        this.lock=        lock;
        this.holdTime=  holdTime;
        this.repeats=    repeats;
        this.verbose=    verbose;
        this.shared=    shared;
    }

    @Override public void run()
    {
        Log.setDomain( "TestThread", Scope.METHOD );
        for ( int i= 0; i < repeats ; i++ )
        {
            if (verbose) { UT_PRINT("Thread: "+ getName() +" acuiring lock..."); }
            lock.acquire();
            if (verbose) { UT_PRINT("Thread: "+ getName() +" has lock."); }

                int sVal= ++shared.val;

                ALIB.sleepMillis( holdTime );

                shared.val= sVal -1;

            if (verbose) { UT_PRINT("Thread: "+ getName() +" releasing lock."); }
            lock.release();
            if (verbose) { UT_PRINT("Thread: "+ getName() +" released lock."); }
        }

        result= 0;
        UT_PRINT("Thread: "+ getName() +" terminates.");
    }
}

}
