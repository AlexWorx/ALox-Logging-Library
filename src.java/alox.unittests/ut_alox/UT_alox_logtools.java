// #################################################################################################
//  Unit Tests - AWorx Library
//
//  Copyright 2013-2019 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
package ut_alox;

import java.util.LinkedList;

import org.junit.Test;

import com.aworx.lox.Log;
import com.aworx.lox.Scope;
import com.aworx.lox.Verbosity;
import com.aworx.lox.tools.LogTools;

import ut_com_aworx.AWorxUnitTesting;



public class UT_alox_logtools  extends AWorxUnitTesting
{
    /** ****************************************************************************************
     *     Log_Exception.
     ******************************************************************************************/
    @Test
    public void Log_Exception()
    {
        UT_INIT();

        Log.setDomain( "EXCEPT", Scope.METHOD );

        Log.info("*** Test LogTools.exception() ***" );
        Exception testException=  new Exception( "TestException Message", new Exception ("InnerException Message", new Exception("Inner, inner Exception") ) );

        LogTools.exception( Verbosity.WARNING, testException, "Logging an exception: " );
    }

    /** ****************************************************************************************
     *     Log_Exception.
     ******************************************************************************************/
    @Test
    public void Log_StackTrace()
    {
        UT_INIT();

        Log.setDomain( "STTR", Scope.METHOD );

        Log.info("*** Test LogTools.stackTrace() ***" );

        LogTools.stackTrace( Verbosity.ERROR, "The current stacktrace is: " );
    }

    /** ****************************************************************************************
     *     Log_Instance
     ******************************************************************************************/
    @Test
    public void Log_Instance()
    {
        UT_INIT();

        Log.setDomain( "INST", Scope.METHOD );

        // simple type double
        {
            Double o= new Double( 3.14 );

            LogTools.instance( Verbosity.INFO, o, 2, "Logging an object of type 'Double':" );
        }

        // Double array
        {
            double[] o= new double[3];
            o[0]= 12.5;
            o[1]= 123456789.987654321;
            o[2]= 100;

            LogTools.instance( Verbosity.INFO, o, 2, "Logging an object of type 'Double[]':" );
        }

        // byte array
        {
            byte[] o= new byte[3];
            o[0]= 2;
            o[1]= 8;
            o[2]= 16;

            LogTools.instance( Verbosity.INFO, o, 2, "Logging an object of type 'byte[]':" );
        }


        // 2 dimensional char[]
        {
            char[][] o= new char[2][3];
            for ( int x= 0; x < 2 ; x++ )
                for ( int y= 0; y < 3 ; y++ )
                    o[x][y]= (char) ( 'a' + y*2 + x);
            LogTools.instance( Verbosity.INFO, o, 2, "Logging a 2 dimensional char[]:" );
        }

        // 2 dimensional int[]
        {
            int[][] o= new int[2][3];
            for ( int x= 0; x < 2 ; x++ )
                for ( int y= 0; y < 3 ; y++ )
                    o[x][y]=  y*2 + x;
            LogTools.instance( Verbosity.INFO, o, 2, "Logging a 2 dimensional int[]:" );
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
            LogTools.instance( Verbosity.INFO, o, 2, "Logging a 4 dimensional int[]:" );
        }


        // simple type String
        {
            String o= "Hello reflection";
            LogTools.instance( Verbosity.INFO, o, 2, "Logging an object of type 'String':" );
        }


        // String array
        {
            String[] o= new String[3];
            o[0]= "Entry 0";
            o[1]= "Entry 1";
            o[2]= "Entry 2";

            LogTools.instance( Verbosity.INFO, o, 2, "Logging an object of type 'String[]':" );
        }

        // List
        {
            LinkedList<String> o= new LinkedList<String>();
            o.add( "Linked entry 0" );
            o.add( "Linked entry 1" );
            o.add( "Linked entry 2" );

            LogTools.instance( Verbosity.INFO, o, 2, "Logging an object of type 'LinkedList<String>':" );
        }

        // Object array
        {
            Object[] o= new Object[10];
            int i= 0;
            o[i++]= "Entry 0";
            o[i++]= new Double( 3.14 );
            o[i++]= "next is array itself!";
            o[i++]= o;
            o[i++]= "next is console logger";
            o[i++]= Log.debugLogger;
            o[i++]= "last filled object";

            LogTools.instance( Verbosity.INFO, o, 3, "Logging an object of type 'Object[]':" );
        }

        // Lox
        {
            LogTools.instance( Verbosity.INFO, Log.LOX, 5, "The lox of Log:" );
        }

        // This thread
        {
            Thread o= Thread.currentThread();
            LogTools.instance( Verbosity.INFO, o, 5, ("Actual Thread: " + o.getName()) );
        }

    }

}
