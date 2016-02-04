// #################################################################################################
//  cs.aworx.lox.unittests - ALox Logging Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
using System;
using System.Threading;
using System.Xml.Linq;
using ut_cs_aworx;

#if ALIB_MONO_DEVELOP
    using NUnit.Framework;
#endif
#if ALIB_VSTUDIO
    using Microsoft.VisualStudio.TestTools.UnitTesting;
#endif

using cs.aworx.lib;
using cs.aworx.lox;
using cs.aworx.lox.core;
using cs.aworx.lox.loggers;
using cs.aworx.lox.tools;
using System.Collections.Generic;

#if !WINDOWS_PHONE
    using cs.aworx.lox.tools.json;
#endif

namespace ut_cs_aworx_lox
{
    #if ALIB_MONO_DEVELOP
        [TestFixture ()]
    #endif
    #if ALIB_VSTUDIO
        [TestClass]
    #endif
    public class CS_ALox_Tools   : UnitTest
    {
    /** ********************************************************************************************
     * The loggers.
     **********************************************************************************************/
    #if ALOX_DBG_LOG || ALOX_REL_LOG
        public static ConsoleLogger       cl;
        public static MemoryLogger        ml;
    #endif  // ALOX_DBG_LOG || ALOX_REL_LOG

    /** ********************************************************************************************
     * Creates loggers.
     **********************************************************************************************/
    public void   clearCreateAndAddLoggers( bool memoryLogger= false, bool consoleLogger= true)
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            Log.Reset();
            cl= null;
            ml= null;

            if ( consoleLogger )
            {
                cl= new ConsoleLogger("UNITTESTLOGGER");
                Log.AddLogger( cl );
            }

            if ( memoryLogger )
            {
                ml= new MemoryLogger();
                Log.AddLogger( ml );
            }

            Log.MapThreadName( "UnitTest" );
        #endif  // ALOX_DBG_LOG || ALOX_REL_LOG
    }


    /** ********************************************************************************************
     * Log_TestException.
     **********************************************************************************************/
    #if ALIB_MONO_DEVELOP
        [Test ()]
    #endif
    #if ALIB_VSTUDIO
        [TestMethod]
        #if !WINDOWS_PHONE
            [TestCategory("CS_ALox_LogTools")]
        #endif
    #endif
    public void Log_TestException()
    {
        clearCreateAndAddLoggers();

        Log.SetDomain( "EXCEPT", Log.Scope.Method );
        Log.SetDomain( "EXCEPT", Log.DomainLevel.All );


        Exception testException=  new Exception( "TestException Message", new Exception ("InnerException Message", new Exception("Inner, inner Exception") ) );

        LogTools.Exception( null, Log.Level.Warning, testException, "Logging an exception: " );
    }


    /** ********************************************************************************************
     * Log_TestInstance
     **********************************************************************************************/
    #if ALIB_MONO_DEVELOP
        [Test ()]
    #endif
    #if ALIB_VSTUDIO
        [TestMethod]
        #if !WINDOWS_PHONE
            [TestCategory("CS_ALox_LogTools")]
        #endif
    #endif
    public void Log_TestInstance()
    {
        clearCreateAndAddLoggers();

        Log.SetDomain( "INST", Log.Scope.Method );
        Log.SetDomain( "INST", Log.DomainLevel.All );

        // simple type double
        {
            Double o= 3.14;

            LogTools.Instance( Log.Level.Info, o, 2, "Logging an object of type 'Double':", 1 );
        }

        // Double array
        {
            Double[] o= new Double[3];
            o[0]= 12.5;
            o[1]= 123456789.987654321;
            o[2]= 100;

            LogTools.Instance( Log.Level.Info, o, 2, "Logging an object of type 'Double[]':", 1 );
        }

        // byte array
        {
            byte[] o= new byte[3];
            o[0]= 2;
            o[1]= 8;
            o[2]= 16;

            LogTools.Instance( Log.Level.Info, o, 2, "Logging an object of type 'byte[]':", 1 );
        }

        // 2 dimensional char[]
        {
            char[,] o= new char[3, 7];
            int val= 0;
            for ( int x= 0; x < o.GetLength( 0 ) ; x++ )
                for ( int y= 0; y < o.GetLength( 1 ) ; y++ )
                    o[x, y]= (char) ( ((int)'a') + val++ );
            LogTools.Instance( Log.Level.Info, o, 2, "Logging a 2 dimensional char[]:", 1 );
        }

        // 4 dimensional int[]
        {
            int[,,,] o= new int[2, 3, 4,5];
            int val= 0;
            for ( int i1= 0; i1 < o.GetLength( 0 ) ; i1++ )
                for ( int i2= 0; i2 < o.GetLength( 1 ) ; i2++ )
                    for ( int i3= 0; i3 < o.GetLength( 2 ) ; i3++ )
                        for ( int i4= 0; i4 < o.GetLength( 3 ) ; i4++ )
                            o[i1, i2, i3, i4]=  val++;
            LogTools.Instance( Log.Level.Info, o, 2, "Logging a 4 dimensional int[]:", 1 );
        }


        // simple type String
        {
            String o= "Hello reflection";
            LogTools.Instance( Log.Level.Info, o, 2, "Logging an object of type 'String':", 1 );
        }


        //// String array
        {
            String[] o= new String[3];
            o[0]= "Entry 0";
            o[1]= "Entry 1";
            o[2]= "Entry 2";

            LogTools.Instance( Log.Level.Info, o, 2, "Logging an object of type 'String[]':", 1 );
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
            #if ALOX_DBG_LOG || ALOX_REL_LOG
                o[i++]= cl;
            #endif  // ALOX_DBG_LOG || ALOX_REL_LOG
            o[i++]= "last filled object";

            LogTools.Instance( Log.Level.Info, o, 2, "Logging an object of type 'Object[]':", 1 );
        }

        // Lox
        {
            #if ALOX_DBG_LOG
                LogTools.Instance( Log.Level.Info, Log.LOX, 2, "The lox of Log:", 1 );
            #endif  // ALOX_DBG_LOG || ALOX_REL_LOG
        }

        // This thread
        {
            Thread o= Thread.CurrentThread;
            LogTools.Instance( Log.Level.Info, o, 2, ("Actual Thread: " + o.Name), 1 );
        }


    }


    /** ********************************************************************************************
     * Log_TestXML
     **********************************************************************************************/
    #if ALIB_MONO_DEVELOP
        [Test ()]
    #endif
    #if ALIB_VSTUDIO
        [TestMethod]
        #if !WINDOWS_PHONE
            [TestCategory("CS_ALox_LogTools")]
        #endif
    #endif
    public void Log_TestXML()
    {
        clearCreateAndAddLoggers();

        Log.SetDomain( "XML", Log.Scope.Method );
        Log.SetDomain( "XML", Log.DomainLevel.All );


        String xmltext= "<MainTag> <SubTag>Hello ALox XML</SubTag> <SubTag2> <SubsubTag>A sub tags' string</SubsubTag> </SubTag2> </MainTag>";
        XDocument xdoc= XDocument.Parse( xmltext );

        LogTools.XML(Log.Level.Info, xdoc, "Logging an xml document: " );
    }

    /** ********************************************************************************************
     * Log_JSON
     **********************************************************************************************/
    #if !WINDOWS_PHONE
        #if ALIB_MONO_DEVELOP
            [Test ()]
        #endif
        #if ALIB_VSTUDIO
            [TestMethod]
            #if !WINDOWS_PHONE
                [TestCategory("CS_ALox")]
            #endif
        #endif
        public void Log_JSON()
        {
            clearCreateAndAddLoggers();

            Log.SetDomain( "JSON", Log.Scope.Method );
            Log.SetDomain( "JSON", Log.DomainLevel.All );


            String    jsonString=
                "{\"glossary\": "
                    + "{\"title\": \"example glossary\",\"GlossDiv\":"
                        + "{\"title\": \"S\",\"GlossList\": "
                            + "{\"GlossEntry\":"
                                + "{\"ID\": \"SGML\",\"SortAs\": \"SGML\",\"GlossTerm\": \"Standard Generalized Markup Language\","
                                + "\"Acronym\": \"SGML\",\"Abbrev\": \"ISO 8879:1986\",\"GlossDef\":"
                                    + "{\"para\": \"A meta-markup language, used to create markup languages such as DocBook.\",\"GlossSeeAlso\": [\"GML\", \"XML\"]"
                                    + "},"
                                + "\"GlossSee\": \"markup\""
                                + "}"
                            + "}"
                        + "}"
                    + "}"
                + "}";
            //Log.Info(jsonString);
            IDictionary<string, object> dict= DynamicJSONDeserializer.FromString( jsonString );

            Log.Info("asdfhsldakfasdf" );
            LogTools.Instance(Log.Level.Info, dict, 100, "Logging a JSON based object: " );
        }
    #endif
    } // class
} // namespace
