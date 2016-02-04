// #################################################################################################
//  Unit Tests - AWorx Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
package ut_com_aworx_uttools;

import static org.junit.Assert.*;

import com.aworx.lib.enums.CurrentData;
import com.aworx.lib.strings.AString;
import com.aworx.lib.strings.Substring;
import com.aworx.lox.Log;
import com.aworx.lox.Log.DomainLevel;
import com.aworx.lox.core.textlogger.TextLogger;
import com.aworx.lox.Lox;



/** ************************************************************************************************
 *  All aworx unit test class are derived from this class.
 *  Ensures alignment and maximum compatibility of unit test methods between C++, C# and Java
 ***************************************************************************************************/
public class UnitTest
{
    static AString              lastAutoSizes= new AString();
    static UnitTestReportWriter reportWriter=  null;


    public UnitTest()
    {
        if ( reportWriter == null )
        {
            reportWriter= new UnitTestReportWriter();
            reportWriter.lox.omittablePackagePrefixes.add( "ut_com_aworx_uttools" );
            
            TextLogger utLogger= Lox.createConsoleLogger( "Unittest Logger" );
            utLogger.setDomain( reportWriter.lox.internalDomain, Log.DomainLevel.WARNINGS_AND_ERRORS );

            reportWriter.lox.addLogger( utLogger );
            reportWriter.lox.setDomain( "UT", DomainLevel.ALL );
        }

        resetLoxAndCreateDebugLogger();
    }

    public void resetLoxAndCreateDebugLogger()
    {
        if (Log.debugLogger != null )
        {
            lastAutoSizes.clear();
            Log.debugLogger.autoSizes.exportValues( lastAutoSizes );
        }

        Log.reset();

        Log.addDebugLogger();
        if ( lastAutoSizes.isNotEmpty() )
        {
            Substring s= new Substring( lastAutoSizes );
            Log.debugLogger.autoSizes.importValues( s, CurrentData.KEEP );
        }

        Log.mapThreadName( "UT" );
    }

    public  void UT_PRINT( String  msg )    { reportWriter.print( 0, msg );   }


    private AString     ASS= new AString();
    private void        ASM( AString msg )  { reportWriter.print( 2, msg.toString() );   }


    public void UT_EQ( char    exp,       char    c )   {  if (c!=exp)                         ASM(ASS.clear()._("UT Failure: Expected: \"")._(exp)        ._("\", Given: \"")._(c)        ._("\".") ); assertEquals( exp            , c             );   }
    public void UT_EQ( String  exp,       String  s )   {  if (!s.equals(exp))                 ASM(ASS.clear()._("UT Failure: Expected: \"")._(exp)        ._("\", Given: \"")._(s)        ._("\".") ); assertEquals( exp            , s             );   }
    public void UT_EQ( AString exp,       String  s )   {  if (!s.equals(exp))                 ASM(ASS.clear()._("UT Failure: Expected: \"")._(exp)        ._("\", Given: \"")._(s)        ._("\".") ); assertEquals( exp.toString() , s             );   }
    public void UT_EQ( String  exp,       AString s )   {  if (!s.equals(exp))                 ASM(ASS.clear()._("UT Failure: Expected: \"")._(exp)        ._("\", Given: \"")._(s)        ._("\".") ); assertEquals( exp            , s.toString()  );   }
    public void UT_EQ( AString exp,       AString s )   {  if (!s.equals(exp))                 ASM(ASS.clear()._("UT Failure: Expected: \"")._(exp)        ._("\", Given: \"")._(s)        ._("\".") ); assertEquals( exp.toString() , s.toString()  );   }
                               
    public void UT_EQ( boolean exp,       boolean b )   {  if (b!=exp)                         ASM(ASS.clear()._("UT Failure: Expected: \"")._(exp?"T":"F")._("\", Given: \"")._(b?"T":"F")._("\".") ); assertEquals( exp            , b             );   }
    public void UT_EQ( int     exp,       int     i )   {  if (i!=exp)                         ASM(ASS.clear()._("UT Failure: Expected: \"")._(exp)        ._("\", Given: \"")._(i)        ._("\".") ); assertEquals( exp            , i             );   }
    public void UT_EQ( long    exp,       long    l )   {  if (l!=exp)                         ASM(ASS.clear()._("UT Failure: Expected: \"")._(exp)        ._("\", Given: \"")._(l)        ._("\".") ); assertEquals( exp            , l             );   }

    public void UT_EQ( double exp, double d, double p ) {  if ((d < exp ? exp-d : d-exp) > p)  ASM(ASS.clear()._("UT Failure: Expected: \"")._(exp)        ._("\", Given: \"")._(d)        ._("\".") ); assertEquals( exp            , d,   p        );   }
    public void UT_EQ( double exp, double d           ) {  if (d!=exp)                         ASM(ASS.clear()._("UT Failure: Expected: \"")._(exp)        ._("\", Given: \"")._(d)        ._("\".") ); assertEquals( exp            , d ,0.0        );   }

    public void UT_TRUE ( boolean cond)                 {  if (!cond)                          ASM(ASS.clear()._("UT Failure: Expected: true, but false given.") );                                                         assertTrue  ( cond                           );   }
    public void UT_FALSE( boolean cond)                 {  if ( cond)                          ASM(ASS.clear()._("UT Failure: Expected: false, but true given.") );                                                         assertFalse ( cond                           );   }
} // class UnitTests

