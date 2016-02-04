// #################################################################################################
//  Unit Tests - AWorx Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
package ut_com_aworx_lox;

import java.util.LinkedList;

import org.junit.Test;

import ut_com_aworx_uttools.UnitTest;

import com.aworx.lox.*;
import com.aworx.lox.tools.LogTools;



public class UT_alox_logtools  extends UnitTest
{
    /** ****************************************************************************************
     *     Log_TestException.
     ******************************************************************************************/
    @Test
    public void Log_TestException()
    {
        Log.setDomain( "EXCEPT", Log.Scope.METHOD );
        Log.setDomain( "EXCEPT", Log.DomainLevel.ALL );

        Log.info("*** Test LogTools.exception() ***" );
        Exception testException=  new Exception( "TestException Message", new Exception ("InnerException Message", new Exception("Inner, inner Exception") ) );

        LogTools.exception( Log.Level.WARNING, testException, "Logging an exception: " );
    }

    /** ****************************************************************************************
     *     Log_TestException.
     ******************************************************************************************/
    @Test
    public void Log_TestStackTrace()
    {
        Log.setDomain( "STTR", Log.Scope.METHOD );
        Log.setDomain( "STTR", Log.DomainLevel.ALL );

        Log.info("*** Test LogTools.stackTrace() ***" );

        LogTools.stackTrace( Log.Level.ERROR, "The current stacktrace is: " );
    }

    /** ****************************************************************************************
     *     Log_TestInstance
     ******************************************************************************************/
    @Test
    public void Log_TestInstance()
    {
        Log.setDomain( "INST", Log.Scope.METHOD );
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
            o[i++]= Log.debugLogger;
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

}
