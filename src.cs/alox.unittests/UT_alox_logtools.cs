// #################################################################################################
//  cs.aworx.lox.unittests - ALox Logging Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
using System;
using System.Threading;
using System.Xml.Linq;
using ut_cs_aworx;

#if ALIB_NUNIT
    using NUnit.Framework;
#endif
#if ALIB_IDE_VSTUDIO
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
    #if ALIB_NUNIT
        [TestFixture ()]
    #endif
    #if ALIB_IDE_VSTUDIO
        [TestClass]
    #endif
    public class CS_ALox_Tools   : AWorxUnitTesting
    {
        // used with unit test Log_ScopeInfoCacheTest
        public static void ScopeInfoCacheTest() { Log.Info("Test method of CS_ALox_Tools"); }

    /** ********************************************************************************************
     * Log_Exception.
     **********************************************************************************************/
    #if ALIB_NUNIT
        [Test ()]
    #endif
    #if ALIB_IDE_VSTUDIO
        [TestMethod]
        #if !WINDOWS_PHONE
            [TestCategory("CS_ALox_LogTools")]
        #endif
    #endif
    public void Log_Exception()
    {
        UT_INIT();

        Log.AddDebugLogger();

        Log.SetDomain( "EXCEPT", Scope.Method );

        Exception testException=  new Exception( "TestException Message", new Exception ("InnerException Message", new Exception("Inner, inner Exception") ) );

        LogTools.Exception( null, Verbosity.Warning, testException, "Logging an exception: " );
    }


    /** ********************************************************************************************
     * Log_Instance
     **********************************************************************************************/
    #if ALIB_NUNIT
        [Test ()]
    #endif
    #if ALIB_IDE_VSTUDIO
        [TestMethod]
        #if !WINDOWS_PHONE
            [TestCategory("CS_ALox_LogTools")]
        #endif
    #endif
    public void Log_Instance()
    {
        UT_INIT();

        Log.SetDomain( "INST", Scope.Method );

        // simple type double
        {
            Double o= 3.14;

            LogTools.Instance( Verbosity.Info, o, 2, "Logging an object of type 'Double':" );
        }

        // Double array
        {
            Double[] o= new Double[3];
            o[0]= 12.5;
            o[1]= 123456789.987654321;
            o[2]= 100;

            LogTools.Instance( Verbosity.Info, o, 2, "Logging an object of type 'Double[]':" );
        }

        // byte array
        {
            byte[] o= new byte[3];
            o[0]= 2;
            o[1]= 8;
            o[2]= 16;

            LogTools.Instance( Verbosity.Info, o, 2, "Logging an object of type 'byte[]':" );
        }

        // 2 dimensional char[]
        {
            char[,] o= new char[3, 7];
            int val= 0;
            for ( int x= 0; x < o.GetLength( 0 ) ; x++ )
                for ( int y= 0; y < o.GetLength( 1 ) ; y++ )
                    o[x, y]= (char) ( ((int)'a') + val++ );
            LogTools.Instance( Verbosity.Info, o, 2, "Logging a 2 dimensional char[]:" );
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
            LogTools.Instance( Verbosity.Info, o, 2, "Logging a 4 dimensional int[]:" );
        }


        // simple type String
        {
            String o= "Hello reflection";
            LogTools.Instance( Verbosity.Info, o, 2, "Logging an object of type 'String':" );
        }


        //// String array
        {
            String[] o= new String[3];
            o[0]= "Entry 0";
            o[1]= "Entry 1";
            o[2]= "Entry 2";

            LogTools.Instance( Verbosity.Info, o, 2, "Logging an object of type 'String[]':" );
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
                o[i++]= Log.DebugLogger;
            #endif  // ALOX_DBG_LOG || ALOX_REL_LOG
            o[i++]= "last filled object";

            LogTools.Instance( Verbosity.Info, o, 2, "Logging an object of type 'Object[]':" );
        }

        // Lox
        {
            #if ALOX_DBG_LOG
                LogTools.Instance( Verbosity.Info, Log.LOX, 2, "The lox of Log:" );
            #endif  // ALOX_DBG_LOG || ALOX_REL_LOG
        }

        // This thread
        {
            Thread o= Thread.CurrentThread;
            LogTools.Instance( Verbosity.Info, o, 2, ("Actual Thread: " + o.Name) );
        }


    }


    /** ********************************************************************************************
     * Log_XML
     **********************************************************************************************/
    #if ALIB_NUNIT
        [Test ()]
    #endif
    #if ALIB_IDE_VSTUDIO
        [TestMethod]
        #if !WINDOWS_PHONE
            [TestCategory("CS_ALox_LogTools")]
        #endif
    #endif
    public void Log_XML()
    {
        UT_INIT();

        Log.SetDomain( "XML", Scope.Method );

        String xmltext= "<MainTag> <SubTag>Hello ALox XML</SubTag> <SubTag2> <SubsubTag>A sub tags' string</SubsubTag> </SubTag2> </MainTag>";
        XDocument xdoc= XDocument.Parse( xmltext );

        LogTools.XML(Verbosity.Info, xdoc, "Logging an xml document: " );
    }

    /** ********************************************************************************************
     * Log_JSON
     **********************************************************************************************/
    #if !WINDOWS_PHONE
        #if ALIB_NUNIT
            [Test ()]
        #endif
        #if ALIB_IDE_VSTUDIO
            [TestMethod]
            #if !WINDOWS_PHONE
                [TestCategory("CS_ALox")]
            #endif
        #endif
        public void Log_JSON()
        {
            UT_INIT();

            Log.SetDomain( "JSON", Scope.Method );

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

            LogTools.Instance(Verbosity.Info, dict, 100, "Logging a JSON based object: " );
        }
    #endif
    } // class
} // namespace
