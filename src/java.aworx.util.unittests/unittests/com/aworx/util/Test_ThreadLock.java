// #################################################################################################
//  Unit Tests - aworx::util
//
//  (c) 2013-2015 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
package unittests.com.aworx.util;

import static org.junit.Assert.*;

import org.junit.Test;

import com.aworx.lox.Log;
import com.aworx.lox.loggers.ConsoleLogger;
import com.aworx.util.*;


public class Test_ThreadLock
{
    //---------------------------------------------------------------------------------------------------------
    //--- Simple
    //---------------------------------------------------------------------------------------------------------
    @SuppressWarnings("static-method")
    @Test
    public void ThreadLock_Simple()
    {
        // lock a recursive lock
        ThreadLock aLock= new ThreadLock();
        aLock.acquire();
        aLock.release();

        aLock.acquire();           assertTrue ( !aLock.toString().startsWith("null") );
        aLock.acquire();           assertTrue ( !aLock.toString().startsWith("null") );
        aLock.release();           assertTrue ( !aLock.toString().startsWith("null") );

        aLock.acquire();           assertTrue ( !aLock.toString().startsWith("null") );
        aLock.release();           assertTrue ( !aLock.toString().startsWith("null") );
        aLock.release();           assertTrue (  aLock.toString().startsWith("null") );

        // set unsafe
        aLock.setUnsafe( true  );  assertTrue (  aLock.toString().startsWith("null") );
        aLock.setUnsafe( false );  assertTrue (  aLock.toString().startsWith("null") );
                                                 
        aLock.setUnsafe( true  );  assertTrue (  aLock.toString().startsWith("null") );
        aLock.acquire();           assertTrue (  aLock.toString().startsWith("null") );
        aLock.release();           assertTrue (  aLock.toString().startsWith("null") );

        // unsafe
        aLock.acquire();           assertTrue (  aLock.toString().startsWith("null") );
        System.out.println("One error should come now: ");
        aLock.setUnsafe( false );  assertTrue (  aLock.toString().startsWith("null") );

        // safe (new lock)
        aLock= new ThreadLock();
        aLock.acquire();           assertTrue ( !aLock.toString().startsWith("null") );
        System.out.println("Another error should come now: ");
        aLock.setUnsafe( true );   assertTrue ( !aLock.toString().startsWith("null") );


        // test warnings (10) locks:
        aLock= new ThreadLock();
        System.out.println("Two warnings should come now: ");
        for (int i= 0; i<20; i++)
            aLock.acquire();
        assertTrue ( !aLock.toString().startsWith("null") );
        for (int i= 0; i<20; i++)
            aLock.release();
        assertTrue ( aLock.toString().startsWith("null") );

        // test a non-recursive lock
        aLock= new ThreadLock( false );
        aLock.acquire();           assertTrue ( !aLock.toString().startsWith("null") );
        aLock.acquire();           assertTrue ( !aLock.toString().startsWith("null") );
        aLock.release();           assertTrue (  aLock.toString().startsWith("null") );

        System.out.println("One warning should come now: ");
        aLock.release();           assertTrue (  aLock.toString().startsWith("null") );
    }

    //---------------------------------------------------------------------------------------------------------
    //--- Threaded
    //---------------------------------------------------------------------------------------------------------
    @Test
    public void ThreadLock_Threaded()
    {
        Log.addLogger( new ConsoleLogger() );

        ThreadLock aLock= new ThreadLock();
        Test_ThreadLock_SharedInt shared= new Test_ThreadLock_SharedInt();
        System.out.println("starting thread locked");
        aLock.acquire();
        Test_ThreadLock_TestThread t= new Test_ThreadLock_TestThread( "A Thread", aLock, 10, 1, true, shared );
        t.start();
        System.out.println("We wait 1100 ms. This should give a warning! ");
        AWXU.sleepMillis( 1100 );
        aLock.release();

        // wait until t ended
        while (t.isAlive())
            AWXU.sleepMillis( 1 );

        // now we do the same with a lower wait limit, no error should come
        aLock.waitWarningTimeLimitInMillis= 5;
        aLock.acquire();
        t= new Test_ThreadLock_TestThread( "A Thread", aLock, 10, 1, true, shared );
        t.start();
        System.out.println("We wait 1 ms. This should NOT give a warning! ");
        AWXU.sleepMillis( 1 );
        aLock.release();

        // wait until t ended
        while (t.isAlive())
            AWXU.sleepMillis( 1 );
    }

    //---------------------------------------------------------------------------------------------------------
    //--- HeavyLoad
    //---------------------------------------------------------------------------------------------------------
    @Test
    public void ThreadLock_HeavyLoad()
    {
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
        System.out.println("starting three threads");
        t1.start();
        t2.start();
        t3.start();

        // wait until all ended
        while ( t1.isAlive() || t2.isAlive() || t3.isAlive() )
            AWXU.sleepMillis( 1 );

        System.out.println("All threads ended. Shared value=" + shared.val );

        assertTrue( shared.val == 0 );
    }


    //---------------------------------------------------------------------------------------------------------
    //--- SpeedTest
    //---------------------------------------------------------------------------------------------------------
    @SuppressWarnings("static-method")
    @Test
    public void ThreadLock_SpeedTest()
    {
        ThreadLock aLock= new ThreadLock();

        int        repeats=    100000;
        int        rrepeats=    5;


        Ticks stopwatch= new Ticks();
        for ( int r= 0; r < rrepeats; r ++)
        {
            System.out.println( );
            System.out.println("Run " + rrepeats );

            aLock.setUnsafe( false );
            stopwatch.set();
            for ( int i= 0; i < repeats; i++ )
            {
                aLock.acquire();
                aLock.release();
            }
            long time= stopwatch.age().inMillis();
            System.out.println("Safe mode, " + repeats + " lock/unlock ops: " + time + " ms" );

            aLock.setUnsafe( true );
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
            System.out.println("Unsafe mode, " + repeats + " lock/unlock ops: " + time + " ms" );
        }
    }


//---------------------------------------------------------------------------------------------------------
//--- helper classes
//---------------------------------------------------------------------------------------------------------


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
        for ( int i= 0; i < repeats ; i++ )
        {
            if (verbose) { System.out.println("Thread: "+ getName() +" acuiring lock..."); }
            lock.acquire();
            if (verbose) { System.out.println("Thread: "+ getName() +" has lock."); }

                int sVal= ++shared.val;

                AWXU.sleepMillis( holdTime );

                shared.val= sVal -1;

            if (verbose) { System.out.println("Thread: "+ getName() +" releasing lock."); }
            lock.release();
            if (verbose) { System.out.println("Thread: "+ getName() +" released lock."); }
        }

        result= 0;
        System.out.println("Thread: "+ getName() +" terminates.");
    }
}

}
