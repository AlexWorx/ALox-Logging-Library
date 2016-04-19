// #################################################################################################
//  cs.aworx.unittests - AWorx Util
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
using System;
using System.IO;
using System.Runtime.CompilerServices;
using cs.aworx.lib;
using cs.aworx.lib.strings;
using cs.aworx.lib.enums;
using cs.aworx.lox;
using cs.aworx.lox.loggers;
using cs.aworx.lox.core.textlogger;


#if ALIB_MONO_DEVELOP
    using NUnit.Framework;
#endif
#if ALIB_VSTUDIO
    using Microsoft.VisualStudio.TestTools.UnitTesting;
#endif

namespace ut_cs_aworx  {


/** ************************************************************************************************
 *  All aworx unit test class are derived from this class.
 *  Ensures alignment and maximum compatibility of unit test methods between C++, C# and Java
 ***************************************************************************************************/
public class AUnitTest
{
    #if ALOX_DBG_LOG 
        static AString lastAutoSizes= new AString();
    #endif 
    public static UTWriter utWriter=  null;

    public AUnitTest()
    {
        // create UTWriter (once) 
        if ( utWriter == null )
            utWriter= new UTWriter();

        // take the most recent auto sizes from the debug logger
        #if ALOX_DBG_LOG 
            if (Log.DebugLogger != null )
            {
                lastAutoSizes.Clear();
                Log.DebugLogger.AutoSizes.Export( lastAutoSizes );
                utWriter.logger.AutoSizes.Import( new Substring( lastAutoSizes ), CurrentData.Keep );
            }
        #endif 
    }

    public void UT_INIT([CallerMemberName] String method="")   
    {
        #if ALOX_DBG_LOG
            // try to clean up, so that ALib is cleaned as well
            if( Log.DebugLogger != null)                Log.RemoveDebugLogger();
            if( Log.GetLogger( "CONSOLE" ) != null )    Log.RemoveLogger( "CONSOLE" );
            if( Log.GetLogger( "MEMORY"  ) != null )    Log.RemoveLogger( "MEMORY" );
            
            if ( utWriter.logger.GetType() == typeof(CLRDebuggerLogger))
                UT_EQ( 0,  ALIB.StdOutputStreamsLock.CntAcquirers() );
            else
                UT_EQ( 1,  ALIB.StdOutputStreamsLock.CntAcquirers() );
            UT_EQ( 0,  ALIB.StdOutputStreamsLock.DbgCountAcquirements(null) );

            ALox.Reset();
            Log.SetSourcePathTrimRule( "*/src.cs/", Inclusion.Include );
            Log.MapThreadName( "UT" );
        #endif
        UT_PRINT( "################### Unit Test: " + this.GetType().Name + "." + method + "() ###################");
    }

    public void UT_PRINT( Object  msg, [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )   
    {
        utWriter.Print( csf,cln,cmn, Verbosity.Info, msg );  
    }

    private AString     ASS= new AString();
    private void        ASM(String csf,int cln,String cmn,  AString msg )  
    {
        msg.InsertAt( "UT Failure: Expected: ", 0 );
        utWriter.Print(csf,cln,cmn, Verbosity.Error, msg );   
    }

    public void UT_EQ( char    exp,       char    c , [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="")   {  if (c!=exp)                         ASM(csf,cln,cmn,ASS.Clear()._("\"")._(exp)        ._("\", Given: \"")._(c)        ._("\".") ); Assert.AreEqual( exp            , c             );   }
    public void UT_EQ( String  exp,       String  s , [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="")   {  if (!s.Equals(exp))                 ASM(csf,cln,cmn,ASS.Clear()._("\"")._(exp)        ._("\", Given: \"")._(s)        ._("\".") ); Assert.AreEqual( exp            , s             );   }
    public void UT_EQ( AString exp,       String  s , [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="")   {  if (!exp.Equals(s))                 ASM(csf,cln,cmn,ASS.Clear()._("\"")._(exp)        ._("\", Given: \"")._(s)        ._("\".") ); Assert.AreEqual( exp.ToString() , s             );   }
    public void UT_EQ( String  exp,       AString s , [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="")   {  if (!s.Equals(exp))                 ASM(csf,cln,cmn,ASS.Clear()._("\"")._(exp)        ._("\", Given: \"")._(s)        ._("\".") ); Assert.AreEqual( exp            , s.ToString()  );   }
    public void UT_EQ( AString exp,       AString s , [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="")   {  if (!exp.Equals(s))                 ASM(csf,cln,cmn,ASS.Clear()._("\"")._(exp)        ._("\", Given: \"")._(s)        ._("\".") ); Assert.AreEqual( exp.ToString() , s.ToString()  );   }

    public void UT_EQ( bool    exp,     bool    b   , [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="")   {  if (b!=exp)                         ASM(csf,cln,cmn,ASS.Clear()._("\"")._(exp?"T":"F")._("\", Given: \"")._(b?"T":"F")._("\".") ); Assert.AreEqual( exp            , b             );   }
    public void UT_EQ( int     exp,     int     i   , [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="")   {  if (i!=exp)                         ASM(csf,cln,cmn,ASS.Clear()._("\"")._(exp)        ._("\", Given: \"")._(i)        ._("\".") ); Assert.AreEqual( exp            , i             );   }
    public void UT_EQ( long    exp,     long    l   , [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="")   {  if (l!=exp)                         ASM(csf,cln,cmn,ASS.Clear()._("\"")._(exp)        ._("\", Given: \"")._(l)        ._("\".") ); Assert.AreEqual( exp            , l             );   }

    public void UT_EQ( double  exp,     double  d   , [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="")   {  if (d!=exp)                         ASM(csf,cln,cmn,ASS.Clear()._("\"")._(exp)        ._("\", Given: \"")._(d)        ._("\".") ); Assert.AreEqual( exp            , d             );   }
    public void UT_EQ( double exp,double d,double p , [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="")   {  if ((d < exp ? exp-d : d-exp) > p)  ASM(csf,cln,cmn,ASS.Clear()._("\"")._(exp)        ._("\", Given: \"")._(d)        ._("\".") ); Assert.AreEqual( exp            , d,   p        );   }

    public void UT_TRUE ( bool    cond              , [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="")   {  if (!cond)                          ASM(csf,cln,cmn,ASS.Clear()._("true, but false given.") );                                                         Assert.IsTrue  ( cond                           );   }
    public void UT_FALSE( bool    cond              , [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="")   {  if ( cond)                          ASM(csf,cln,cmn,ASS.Clear()._("false, but true given.") );                                                         Assert.IsFalse ( cond                           );   }

} // class UnitTests

/** ****************************************************************************************
 * Used for writing messages is unit tests. Creates an own Lox and adds a text Logger.
 * In addition, implements ALib \b %ReportWriter interface and attaches to ALib.
 * 
 * Only one singleton of this class is (and should be) created in class \b UnitTest. 
 ******************************************************************************************/
public class UTWriter : ReportWriter
{
    public Lox          lox;
    public TextLogger   logger;

    public UTWriter()
    {
        lox= new Lox( "UTLox" );
        // This does not work/make sense with MonoDevelop. 
        //if( System.Diagnostics.Debugger.IsAttached )
        //    logger= new CLRDebuggerLogger();
        //else
            logger= Lox.CreateConsoleLogger( "UT ALib ReportWriter" );

        lox.SetVerbosity( logger, Verbosity.Verbose, "UT" );
        lox.SetVerbosity( logger, Verbosity.Verbose, ALox.InternalDomains);
        lox.SetPrefix( ESC.BG_GRAY, "/" );

        cs.aworx.lib.Report.GetDefault().PushWriter( this );
    }

    public void Print( String csf,int cln,String cmn, Verbosity verbosity, Object msg )
    {
        lox.Entry( "UT", verbosity, msg, cln,csf,cmn );
    }

    /** ****************************************************************************************
     * Notify activation/deactivation
     * @param phase     Information if activated or deactivated.
     ******************************************************************************************/
    public virtual void NotifyActivation( Phase phase )
    {
    }

    /** ************************************************************************************
     * Write ALib reports using ALox.
     * @param report The report.
     **************************************************************************************/
    public virtual void Report  (Report.Message report)
    {
        lox.Entry( ALox.InternalDomains + "UT_REPORT",
                   report.Type == 0 ? Verbosity.Error       :
                   report.Type == 1 ? Verbosity.Warning     :
                   report.Type == 2 ? Verbosity.Info        :
                                      Verbosity.Verbose,
                   report.Contents, 
                   report.Line, report.File, report.Func );
    }
}


/** ************************************************************************************************
 *  Writes sample output of a unit test to a file used as input source for doxygen
 ***************************************************************************************************/
public class UnitTestSampleWriter
{
    protected System.IO.TextWriter      origOut;
    protected System.IO.StreamWriter    utWriter;
    protected static String             GeneratedSamplesDir= null;   

    // defaults to "docs/ALox.CS/".
    // Set this to a suitable value in your bootstrap code, before using this class with
    // other projects!
    public    static String             GeneratedSamplesSearchDir= "docs/ALox.CS";
    
    public static String GetGeneratedSamplesDir()
    {
        // if invoked the first time, search the right directory
        if ( GeneratedSamplesDir == null )
        {
            GeneratedSamplesDir= "";
            String testDir= "../" + GeneratedSamplesSearchDir;
            for( int depth= 0; depth < 10 ; depth++ )
            {
                if ( Directory.Exists( testDir ) )
                {
                    GeneratedSamplesDir= testDir + "/generated";
                    if ( !Directory.Exists( GeneratedSamplesDir ) )
                        Directory.CreateDirectory( GeneratedSamplesDir );
                    GeneratedSamplesDir= GeneratedSamplesDir + "/";

                    break;
                }
                testDir=  "../" + testDir;
            }
        }
        return GeneratedSamplesDir;
    }

    public UnitTestSampleWriter(String filename)
    {
        if ( GetGeneratedSamplesDir().Length == 0 )
            return;

        origOut= Console.Out;

        utWriter= new StreamWriter( GeneratedSamplesDir +  filename );
        Console.SetOut( utWriter );

        Console.WriteLine( "//! [OUTPUT]" );
    }

    public void FlushAndResetConsole()
    {
        if ( GetGeneratedSamplesDir().Length == 0 )
            return;
        Console.WriteLine( "//! [OUTPUT]" );
        utWriter.Flush();
        utWriter.Close();
        Console.SetOut( origOut );
    }

} // class UnitTestSampleWriter

} //namespace
