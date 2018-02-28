// #################################################################################################
//  ut_com_aworx - AWorx Unit Test Support using ALib and ALox
//
//  Copyright 2013-2018 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
//
//  Relies on ALox logging library, which in turn relies on ALib. Hence, ALibs' unit
//  tests can only be compiled if ALox library is present.
// #################################################################################################
package ut_com_aworx;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;

import com.aworx.lib.ALIB;
import com.aworx.lib.config.InMemoryPlugin;
import com.aworx.lib.config.Configuration;
import com.aworx.lib.lang.CurrentData;
import com.aworx.lib.strings.AString;
import com.aworx.lib.strings.Substring;
import com.aworx.lox.ALox;
import com.aworx.lox.Log;
import com.aworx.lox.Verbosity;

/** ************************************************************************************************
 *  All aworx unit test class are derived from this class.
 *  Ensures alignment and maximum compatibility of unit test methods between C++, C# and Java
 ***************************************************************************************************/
public class AWorxUnitTesting
{
    public static AString  lastAutoSizes= new AString();
    public static UTWriter utWriter;
    public static int      checkUT_INITCalled= 1;


    public AWorxUnitTesting()
    {
        ALox.init();

        // create UTWriter (once)
        if ( utWriter == null )
            utWriter= new UTWriter();

        // take the most recent auto sizes from the debug logger
        if (Log.debugLogger != null )
        {
            lastAutoSizes.clear();
            Log.debugLogger.autoSizes.exportValues( lastAutoSizes );
            utWriter.logger.autoSizes.importValues( new Substring( lastAutoSizes ), CurrentData.KEEP );
        }

        if ( checkUT_INITCalled != 1)
            UT_PRINT( "################## !!!Recent Test did not invoke UT_INIT!!! ##################");
        checkUT_INITCalled= 0;
    }

    public void UT_INIT()
    {
        checkUT_INITCalled++;

        // try to clean up, so that ALib is cleaned as well
        if( Log.debugLogger != null)                Log.removeDebugLogger();
        if( Log.getLogger( "CONSOLE" ) != null )    Log.removeLogger( "CONSOLE" );
        if( Log.getLogger( "MEMORY"  ) != null )    Log.removeLogger( "MEMORY" );
        UT_EQ( 1,  ALIB.stdOutputStreamsLock.cntAcquirers() );
        UT_EQ( 0,  ALIB.stdOutputStreamsLock.dbgCountAcquirements(null) );

        ALox.config.getPluginTypeSafe( Configuration.PRIO_DEFAULT_VALUES  , InMemoryPlugin.class ).reset();
        ALox.config.getPluginTypeSafe( Configuration.PRIO_PROTECTED_VALUES, InMemoryPlugin.class ).reset();
        ALIB.config.getPluginTypeSafe( Configuration.PRIO_DEFAULT_VALUES  , InMemoryPlugin.class ).reset();
        ALIB.config.getPluginTypeSafe( Configuration.PRIO_PROTECTED_VALUES, InMemoryPlugin.class ).reset();

        ALox.reset();
        Log.mapThreadName( "UTThread" );
        StackTraceElement[]  stElems=   (new Exception()).getStackTrace();

        UT_PRINT( "################### Unit Test: " + this.getClass().getSimpleName() + "."  + stElems[1].getMethodName() + "() ###################");
    }

    public static void UT_PRINT( Object... msgs )
    {
        utWriter.printx( Verbosity.INFO, msgs );
    }

    private static void ASM( Object exp, Object given )
    {
        Object[] msgs= new Object[] { "UT Failure: Expected: {!Q}, given: {!Q}.", exp, given };
        utWriter.printx( Verbosity.ERROR, msgs );
        assert false : "UT Failure";
    }


    public static void UT_EQ( char    exp,       char    c )   {  if (c!=exp)                         ASM(exp, c); assertEquals( exp            , c             );   }
    public static void UT_EQ( String  exp,       String  s )   {  if (!s.equals(exp))                 ASM(exp, s); assertEquals( exp            , s             );   }
    public static void UT_EQ( AString exp,       String  s )   {  if (!exp.equals(s))                 ASM(exp, s); assertEquals( exp.toString() , s             );   }
    public static void UT_EQ( String  exp,       AString s )   {  if (!s.equals(exp))                 ASM(exp, s); assertEquals( exp            , s.toString()  );   }
    public static void UT_EQ( AString exp,       AString s )   {  if (!s.equals(exp))                 ASM(exp, s); assertEquals( exp.toString() , s.toString()  );   }

    public static void UT_EQ( boolean exp,       boolean b )   {  if (b!=exp)                         ASM(exp, b); assertTrue  ( exp           == b             );   }
    public static void UT_EQ( int     exp,       int     i )   {  if (i!=exp)                         ASM(exp, i); assertEquals( exp            , i             );   }
    public static void UT_EQ( long    exp,       long    l )   {  if (l!=exp)                         ASM(exp, l); assertEquals( exp            , l             );   }

    public static void UT_EQ( double exp, double d, double p ) {  if ((d < exp ? exp-d : d-exp) > p)  ASM(exp, d); assertEquals( exp            , d,   p        );   }
    public static void UT_EQ( double exp, double d           ) {  if (d!=exp)                         ASM(exp, d); assertEquals( exp            , d ,0.0        );   }

    public static void UT_TRUE ( boolean cond)                 {  if (!cond)                          ASM(true, false);assertTrue  ( cond                       );   }
    public static void UT_FALSE( boolean cond)                 {  if ( cond)                          ASM(false,true );assertFalse ( cond                       );   }
} // class UnitTests

