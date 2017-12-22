// #################################################################################################
//  ut_cs_aworx - AWorx Unit Test Support using ALib and ALox
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
//
//  Relies on ALox logging library, which in turn relies on ALib. Hence, ALibs' unit
//  tests can only be compiled if ALox library is present.
// #################################################################################################
using System;
using System.IO;
using System.Runtime.CompilerServices;
using cs.aworx.lib;
using cs.aworx.lib.strings;
using cs.aworx.lib.lang;
using cs.aworx.lox;
using cs.aworx.lox.loggers;
using cs.aworx.lox.core.textlogger;
using cs.aworx.lib.config;


#if ALIB_NUNIT
    using NUnit.Framework;
#endif
#if ALIB_IDE_VSTUDIO
    using Microsoft.VisualStudio.TestTools.UnitTesting;
#endif

namespace ut_cs_aworx  {


/** ************************************************************************************************
 *  All aworx unit test class are derived from this class.
 *  Ensures alignment and maximum compatibility of unit test methods between C++, C# and Java
 ***************************************************************************************************/
public class AWorxUnitTesting
{
    #if ALOX_DBG_LOG
        static AString lastAutoSizes= new AString();
    #endif
    public static UTWriter utWriter=  null;

    public AWorxUnitTesting()
    {
        ALox.Init();

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

    public void UT_INIT([CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="")
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

            ALox.Config.GetPluginTypeSafe<InMemoryPlugin>( Configuration.PrioDefaultValues   ).Reset();
            ALox.Config.GetPluginTypeSafe<InMemoryPlugin>( Configuration.PrioProtectedValues ).Reset();
            ALIB.Config.GetPluginTypeSafe<InMemoryPlugin>( Configuration.PrioDefaultValues   ).Reset();
            ALIB.Config.GetPluginTypeSafe<InMemoryPlugin>( Configuration.PrioProtectedValues ).Reset();

            #if ALIB_IDE_MONODEVELOP || ALIB_IDE_RIDER
                ALox.Config.Store( new Variable( "ALOX", "CONSOLE_TYPE" ), "plain" );
            #endif
            ALox.Reset();
            Log.SetSourcePathTrimRule( "*/src.cs/", Inclusion.Include );
            Log.MapThreadName( "UT" );
        #endif

        UT_PRINT( "################### Unit Test: {}.{}() ###################", this.GetType().Name, cmn,
                   null, csf,cln,cmn );
    }

    public void UT_PRINT( Object msg, Object optLog2= null, Object optLog3= null, Object optLog4= null,
                         [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
    {
        utWriter.Print( csf,cln,cmn, Verbosity.Info, msg, optLog2,optLog3,optLog4 );
    }

    private static void ASM(String csf,int cln,String cmn,  Object exp, Object given )
    {
        Object[] msgs= new Object[] { "UT Failure: Expected: {!Q}, given: {!Q}.", exp, given };
        utWriter.Print(csf,cln,cmn, Verbosity.Error, msgs );
    }

    public void UT_EQ( char    exp,       char    c , [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="")   {  if (c!=exp)                         ASM(csf,cln,cmn,exp, c); Assert.AreEqual( exp            , c             );   }
    public void UT_EQ( String  exp,       String  s , [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="")   {  if (!s.Equals(exp))                 ASM(csf,cln,cmn,exp, s); Assert.AreEqual( exp            , s             );   }
    public void UT_EQ( AString exp,       String  s , [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="")   {  if (!exp.Equals(s))                 ASM(csf,cln,cmn,exp, s); Assert.AreEqual( exp.ToString() , s             );   }
    public void UT_EQ( String  exp,       AString s , [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="")   {  if (!s.Equals(exp))                 ASM(csf,cln,cmn,exp, s); Assert.AreEqual( exp            , s.ToString()  );   }
    public void UT_EQ( AString exp,       AString s , [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="")   {  if (!exp.Equals(s))                 ASM(csf,cln,cmn,exp, s); Assert.AreEqual( exp.ToString() , s.ToString()  );   }

    public void UT_EQ( bool    exp,     bool    b   , [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="")   {  if (b!=exp)                         ASM(csf,cln,cmn,exp, b); Assert.IsTrue  ( exp           == b             );   }
    public void UT_EQ( int     exp,     int     i   , [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="")   {  if (i!=exp)                         ASM(csf,cln,cmn,exp, i); Assert.AreEqual( exp            , i             );   }
    public void UT_EQ( long    exp,     long    l   , [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="")   {  if (l!=exp)                         ASM(csf,cln,cmn,exp, l); Assert.AreEqual( exp            , l             );   }

    public void UT_EQ( double  exp,     double  d   , [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="")   {  if (d!=exp)                         ASM(csf,cln,cmn,exp, d); Assert.IsTrue  ( exp           == d             );   }
    public void UT_EQ( double exp,double d,double p , [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="")   {  if ((d < exp ? exp-d : d-exp) > p)  ASM(csf,cln,cmn,exp, d); Assert.AreEqual( exp            , d,   p        );   }

    public void UT_TRUE ( bool    cond              , [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="")   {  if (!cond)                          ASM(csf,cln,cmn,true, false); Assert.IsTrue  ( cond                      );   }
    public void UT_FALSE( bool    cond              , [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="")   {  if ( cond)                          ASM(csf,cln,cmn,false, true); Assert.IsFalse ( cond                      );   }

} // class UnitTests

/** ****************************************************************************************
 * Used for writing messages is unit tests. Creates an own Lox and adds a text Logger.
 * In addition, implements \b %ALib \b %ReportWriter interface and attaches to \b %ALib.
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
        #if ALIB_IDE_RIDER
            logger= new ConsoleLogger( "UT ALib ReportWriter" );
            logger.MetaInfo.Format.SearchAndReplace( "(%SL):", ":%SL:" );
            logger.MetaInfo.Format.InsertAt( "%SP/", 0 );
        #elif ALIB_IDE_MONODEVELOP
            logger= new ConsoleLogger( "UT ALib ReportWriter" );
        #else
            logger= Lox.CreateConsoleLogger( "UT ALib ReportWriter" );
        #endif

        lox.SetVerbosity( logger, Verbosity.Verbose, "UT" );
        lox.SetVerbosity( logger, Verbosity.Verbose, ALox.InternalDomains);
        lox.SetPrefix( ESC.BG_GRAY, "/" );

        cs.aworx.lib.lang.Report.GetDefault().PushWriter( this );
    }

    public void Print( String csf,int cln,String cmn, Verbosity verbosity, Object msg,
                       Object optLog2= null, Object optLog3= null, Object optLog4= null )
    {
        Object[] logables;
             if( optLog4 != null ) logables= new Object[] { msg, optLog2, optLog3, optLog4 };
        else if( optLog3 != null ) logables= new Object[] { msg, optLog2, optLog3 };
        else if( optLog2 != null ) logables= new Object[] { msg, optLog2 };
        else                       logables= new Object[] { msg };

        lox.Entry( "UT", verbosity, logables, cln,csf,cmn );
    }

    /** ****************************************************************************************
     * Notify activation/deactivation
     * @param phase     Information if activated or deactivated.
     ******************************************************************************************/
    public virtual void NotifyActivation( Phase phase )
    {
    }

    /** ************************************************************************************
     * Write \b %ALib reports using \b %ALox.
     * @param msg  The message to report.
     **************************************************************************************/
    public virtual void Report  (Report.Message msg)
    {
        Object[] logables= {msg.Contents};
        lox.Entry( ALox.InternalDomains + "UT_REPORT",
                   msg.Type == 0 ? Verbosity.Error       :
                   msg.Type == 1 ? Verbosity.Warning     :
                   msg.Type == 2 ? Verbosity.Info        :
                                   Verbosity.Verbose,
                   logables,
                   msg.Line, msg.File, msg.Func );
    }
}


/** ************************************************************************************************
 *  Writes sample output of a unit test to a file used as input source for doxygen
 ***************************************************************************************************/
public class UTSampleWriter
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

    public UTSampleWriter(String filename)
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
