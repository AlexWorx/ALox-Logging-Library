// #################################################################################################
//  ut_com_aworx - AWorx Unit Test Support using ALib and ALox
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
//
//  Relies on ALox logging library, which in turn relies on ALib. Hence, ALibs' unit
//  tests can only be compiled if ALox library is present.
// #################################################################################################
package ut_com_aworx;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;

import com.aworx.lib.ALIB;
import com.aworx.lib.config.Configuration;
import com.aworx.lib.enums.CurrentData;
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

        ALIB.config= new Configuration();

        ALox.reset();
        Log.mapThreadName( "UTThread" );
        StackTraceElement[]  stElems=   (new Exception()).getStackTrace();
        UT_PRINT( "################### Unit Test: " + this.getClass().getSimpleName() + "."  + stElems[1].getMethodName() + "() ###################");
    }    


    public static void UT_PRINT( Object  msg )    { utWriter.print( Verbosity.INFO, msg );   }


    private AString     ASS= new AString();
    private static void ASM( AString msg )  { msg.insertAt( "UT Failure: Expected: ", 0 );
                                              utWriter.print( Verbosity.ERROR, msg );
                                              assert false : "UT Failure";   
                                            }


    public void UT_EQ( char    exp,       char    c )   {  if (c!=exp)                         ASM(ASS.clear()._("\"")._(exp)        ._("\", Given: \"")._(c)        ._("\".") ); assertEquals( exp            , c             );   }
    public void UT_EQ( String  exp,       String  s )   {  if (!s.equals(exp))                 ASM(ASS.clear()._("\"")._(exp)        ._("\", Given: \"")._(s)        ._("\".") ); assertEquals( exp            , s             );   }
    public void UT_EQ( AString exp,       String  s )   {  if (!exp.equals(s))                 ASM(ASS.clear()._("\"")._(exp)        ._("\", Given: \"")._(s)        ._("\".") ); assertEquals( exp.toString() , s             );   }
    public void UT_EQ( String  exp,       AString s )   {  if (!s.equals(exp))                 ASM(ASS.clear()._("\"")._(exp)        ._("\", Given: \"")._(s)        ._("\".") ); assertEquals( exp            , s.toString()  );   }
    public void UT_EQ( AString exp,       AString s )   {  if (!s.equals(exp))                 ASM(ASS.clear()._("\"")._(exp)        ._("\", Given: \"")._(s)        ._("\".") ); assertEquals( exp.toString() , s.toString()  );   }
                               
    public void UT_EQ( boolean exp,       boolean b )   {  if (b!=exp)                         ASM(ASS.clear()._("\"")._(exp?"T":"F")._("\", Given: \"")._(b?"T":"F")._("\".") ); assertTrue  ( exp           == b             );   }
    public void UT_EQ( int     exp,       int     i )   {  if (i!=exp)                         ASM(ASS.clear()._("\"")._(exp)        ._("\", Given: \"")._(i)        ._("\".") ); assertEquals( exp            , i             );   }
    public void UT_EQ( long    exp,       long    l )   {  if (l!=exp)                         ASM(ASS.clear()._("\"")._(exp)        ._("\", Given: \"")._(l)        ._("\".") ); assertEquals( exp            , l             );   }

    public void UT_EQ( double exp, double d, double p ) {  if ((d < exp ? exp-d : d-exp) > p)  ASM(ASS.clear()._("\"")._(exp)        ._("\", Given: \"")._(d)        ._("\".") ); assertEquals( exp            , d,   p        );   }
    public void UT_EQ( double exp, double d           ) {  if (d!=exp)                         ASM(ASS.clear()._("\"")._(exp)        ._("\", Given: \"")._(d)        ._("\".") ); assertEquals( exp            , d ,0.0        );   }

    public void UT_TRUE ( boolean cond)                 {  if (!cond)                          ASM(ASS.clear()._("true, but false given.") );                                                         assertTrue  ( cond                           );   }
    public void UT_FALSE( boolean cond)                 {  if ( cond)                          ASM(ASS.clear()._("false, but true given.") );                                                         assertFalse ( cond                           );   }
} // class UnitTests

