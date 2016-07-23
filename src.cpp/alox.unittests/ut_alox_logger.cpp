// #################################################################################################
//  Unit Tests - ALox Logging Library
//  (Unit Tests to create tutorial sample code and output)
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
#include "alib/stdafx_alib.h"

#include "alox/alox_console_loggers.hpp"
#include "alox/loggers/memorylogger.hpp"

#if !defined (HPP_ALIB_CONFIG_INI_FILE)
    #include "alib/config/inifile.hpp"
#endif
#if !defined (HPP_ALIB_CONFIG_CONFIGURATION)
    #include "alib/config/configuration.hpp"
#endif


#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define TESTCLASSNAME       CPP_ALox_Logger
#include "alib.unittests/aworx_unittests.hpp"

using namespace std;
using namespace ut_aworx;

using namespace aworx;


namespace ut_alox {


#if defined(ALOX_DBG_LOG)

class MyObjectConverter : public lox::core::textlogger::ObjectConverter
{
    bool ConvertObject( const lox::core::Logable& logable, AString& result )
    {
        if ( logable.Type == 0 )
        {
            if ( logable.Object != nullptr && ((const TString*) logable.Object )->IsNotNull() )
                result._( "MyObjectConverter: " )._((const TString*) logable.Object );
            else
                result._( "MyObjectConverter: null" );
            return true;
        }

        if ( logable.Type == 10 )
        {
            result._( "my type" );
            return true;
        }

        return false;
    }
};



/** ********************************************************************************************
* UT_CLASS
**********************************************************************************************/
// with GTEST macros it all gets wild. Fix the method name
#undef  ALIB_SRC_INFO_PARAMS
#define ALIB_SRC_INFO_PARAMS     __FILE__, __LINE__, aworxTestName

UT_CLASS()


/** ********************************************************************************************
* Log_ObjectConverter
**********************************************************************************************/
UT_METHOD(Log_TextLogger_ObjectConverter)
{
    UT_INIT();

    Log_AddDebugLogger();

    Log_SetDomain( "OBJECT_CONV",       Scope::Method );
    MemoryLogger ml;
    ml.MetaInfo->Format._();
    Log_SetVerbosity( &ml, Verbosity::Verbose );

    lox::core::textlogger::StringConverter* mainConverter= (lox::core::textlogger::StringConverter*) ml.ObjectConverters[0];

    // test without my converter
    Log_Info( "Test" );      UT_TRUE( ml.MemoryLog.IndexOfSubstring( "Test" ) >= 0 );                                              ml.MemoryLog._();
    Log_Info( nullptr );     UT_TRUE( ml.MemoryLog.IndexOfSubstring( mainConverter->FmtNullObject ) >= 0 );               ml.MemoryLog._();
    Log_Info( this,    10 ); UT_TRUE( ml.MemoryLog.CompareTo( ml.FmtUnknownObject, Case::Sensitive, 0, 10, 0, 10) == 0 );   ml.MemoryLog._();
    Log_Info( nullptr, 10 ); UT_TRUE( ml.MemoryLog.CompareTo( ml.FmtUnknownObject, Case::Sensitive, 0, 10, 0, 10) == 0 );   ml.MemoryLog._();

    // test without my converter
                   ml.ObjectConverters.emplace_back( new MyObjectConverter() );
    Log::DebugLogger->ObjectConverters.emplace_back( new MyObjectConverter() );
    Log_Info( "Test" );      UT_TRUE( ml.MemoryLog.IndexOfSubstring( "Test" ) >= 0 );                                               ml.MemoryLog._();
    Log_Info( nullptr );     UT_EQ  ( "MyObjectConverter: null" , ml.MemoryLog );                                            ml.MemoryLog._();
    Log_Info( this,    10 ); UT_EQ  ( "my type"                 , ml.MemoryLog );                                            ml.MemoryLog._();
    Log_Info( nullptr, 10 ); UT_EQ  ( "my type"                 , ml.MemoryLog );                                            ml.MemoryLog._();

    // cleanup
    Log_RemoveLogger( &ml )
    Log_RemoveDebugLogger()
}

/** ********************************************************************************************
 * Log_Replacements
 **********************************************************************************************/
UT_METHOD(Log_Replacements)
{
    UT_INIT();

    Log_AddDebugLogger();
    Log_SetDomain( "REPL", Scope::Method );
    Log_Prune( MemoryLogger* testML= new MemoryLogger(); )
    Log_SetVerbosity( testML , Verbosity::Verbose);

    Log_Prune( testML->SetReplacement( "F...", "F-Word"   ); )

    Log_Info( "What the F...!" )

    UT_TRUE( testML->MemoryLog.IndexOf( "F...")   < 0 );
    UT_TRUE( testML->MemoryLog.IndexOf( "F-Word") > 0 );

    Log_RemoveLogger( testML );
    Log_Prune( delete testML );
}


/** ********************************************************************************************
 * Log_Exception.
 **********************************************************************************************/
UT_METHOD(Log_Multiline)
{
    UT_INIT();

    Log_AddDebugLogger();

    Log_SetDomain( "/MLine", Scope::Method );
    Log_SetVerbosity( Log::DebugLogger, Verbosity::Verbose );

//        Log::DebugLogger->MetaInfo->MsgPrefixInfo=   "$$$";
//        Log::DebugLogger->MetaInfo->MsgPrefixInfo=   ESC::MAGENTA;
//        Log::DebugLogger->MetaInfo->MsgSuffix=       "###";
//        Log::DebugLogger->MetaInfo->MsgSuffix=       ESC::FG_RESET;
//    Log::DebugLogger->FmtMultiLineSuffix=            "<<";



    Log::DebugLogger->MultiLineMsgMode= 0;
    Log_Info( "" );
    Log_Info( "-------- ML Mode = 0 (single line) --------" );
    Log_LogState( "MLine", Verbosity::Info, "Our Log configuration is:" );

    Log::DebugLogger->MultiLineMsgMode= 0;
    Log::DebugLogger->MultiLineDelimiterRepl= "~|~";
    Log_Info( "" );
    Log_Info( "-------- ML Mode = 0 (single line) with delimiter replacement set to ~|~ --------" );
    Log_LogState( "MLine", Verbosity::Info, "Our Log configuration is:" );

    Log::DebugLogger->MultiLineMsgMode= 0;
    Log::DebugLogger->MultiLineDelimiter= "";
    Log_Info( "" );
    Log_Info( "-------- ML Mode = 0 (single line) with delimiter set to \"\" (stops multi line processing) --------" );
    Log_LogState( "MLine", Verbosity::Info, "Our Log configuration is:" );
    Log::DebugLogger->MultiLineDelimiter= (const char*) nullptr; // reset

    Log::DebugLogger->MultiLineMsgMode= 1;
    Log_Info( "" );
    Log_Info( "-------- ML Mode = 1 (multi line, all meta info per line) --------" );
    Log_LogState( "MLine", Verbosity::Info, "Our Log configuration is:" );

    Log::DebugLogger->MultiLineMsgMode= 2;
    Log_Info( "" );
    Log_Info( "-------- ML Mode = 2 (multi line, meta info blanked) --------" );
    Log_LogState( "MLine", Verbosity::Info, "Our Log configuration is:" );

    Log::DebugLogger->MultiLineMsgMode= 3;
    Log_Info( "" );
    Log_Info( "-------- ML Mode = 3 (multi line, print headline with info, text starts at pos 0) --------" );
    Log_LogState( "MLine", Verbosity::Info, "Our Log configuration is:" );

    Log::DebugLogger->MultiLineMsgMode= 4;
    Log_Info( "" );
    Log_Info( "-------- ML Mode = 4 (pure multi line, no meta info, no headline, starts at pos 0)) --------" );
    Log_LogState( "MLine", Verbosity::Info, "Our Log configuration is:" );
}


/** ********************************************************************************************
* Log_ColorsAndStyles.
**********************************************************************************************/

#if defined( ALOX_DBG_LOG ) && defined(ALOX_DBG_LOG_CI)
UT_METHOD(Log_ColorsAndStyles)
{
    UT_INIT();

    Log_AddDebugLogger();

    Log_SetDomain( "COLORS", Scope::Method );

    Log_Prune( MemoryLogger* testML= new MemoryLogger(); )
    Log_SetVerbosity( testML, Verbosity::Verbose );

    Log_Info( "Playing with colors. Depending on the test environment, the colors might "
              "be visible or not" );
    Log_Info( "In the memory logger, all color/style codes have to disappear (by default)" );
    Log_Verbose( "A verbose message" );
    Log_Info   ( "An info message" );
    Log_Warning( "A warning message" );
    Log_Error  ( "An error message" );
    int mlPos= testML->MemoryLog.IndexOf("/COLORS" );
    UT_TRUE( mlPos > 0 );
    mlPos+= 8;


    Log::DebugLogger->MetaInfo->Format= "";
    Log_Info(    String256("FG Colors:  ")
                                << ">>>" << ESC::RED     << "RED"        << ESC::FG_RESET << "<<<"
                                << ">>>" << ESC::GREEN   << "GREEN"      << ESC::FG_RESET << "<<<"
                                << ">>>" << ESC::BLUE    << "BLUE"       << ESC::FG_RESET << "<<<"
                                << ">>>" << ESC::CYAN    << "CYAN"       << ESC::FG_RESET << "<<<"
                                << ">>>" << ESC::MAGENTA << "MAGENTA"    << ESC::FG_RESET << "<<<"
                                << ">>>" << ESC::YELLOW  << "YELLOW"     << ESC::FG_RESET << "<<<"
                                << ">>>" << ESC::GRAY    << "GRAY"       << ESC::FG_RESET << "<<<"
                                << ">>>" << ESC::WHITE   << "WHITE"      << ESC::FG_RESET << "<<<"
                                << ">>>" << ESC::BLACK   << "BLACK"      << ESC::FG_RESET << "<<<"
                                );

    UT_TRUE( testML->MemoryLog.IndexOf('\033') < 0 ); testML->MemoryLog.Clear();

    Log_Info(    String256("BG Colors:  ")
                                << ">>>" << ESC::BG_RED     << "RED"        << ESC::BG_RESET << "<<<"
                                << ">>>" << ESC::BG_GREEN   << "GREEN"      << ESC::BG_RESET << "<<<"
                                << ">>>" << ESC::BG_BLUE    << "BLUE"       << ESC::BG_RESET << "<<<"
                                << ">>>" << ESC::BG_CYAN    << "CYAN"       << ESC::BG_RESET << "<<<"
                                << ">>>" << ESC::BG_MAGENTA << "MAGENTA"    << ESC::BG_RESET << "<<<"
                                << ">>>" << ESC::BG_YELLOW  << "YELLOW"     << ESC::BG_RESET << "<<<"
                                << ">>>" << ESC::BG_GRAY    << "GRAY"       << ESC::BG_RESET << "<<<"
                                << ">>>" << ESC::BG_WHITE   << "WHITE"      << ESC::BG_RESET << "<<<"
                                << ">>>" << ESC::BG_BLACK   << "BLACK"      << ESC::BG_RESET << "<<<"
                                );

    UT_TRUE( testML->MemoryLog.IndexOf('\033') < 0 ); testML->MemoryLog.Clear();

    Log_Info(    String256("FG/BG same: ")
                            << ">>>" << ESC::RED     << ESC::BG_RED     << "RED"        << ESC::RESET << "<<<"
                            << ">>>" << ESC::GREEN   << ESC::BG_GREEN   << "GREEN"      << ESC::RESET << "<<<"
                            << ">>>" << ESC::BLUE    << ESC::BG_BLUE    << "BLUE"       << ESC::RESET << "<<<"
                            << ">>>" << ESC::CYAN    << ESC::BG_CYAN    << "CYAN"       << ESC::RESET << "<<<"
                            << ">>>" << ESC::MAGENTA << ESC::BG_MAGENTA << "MAGENTA"    << ESC::RESET << "<<<"
                            << ">>>" << ESC::YELLOW  << ESC::BG_YELLOW  << "YELLOW"     << ESC::RESET << "<<<"
                            << ">>>" << ESC::GRAY    << ESC::BG_GRAY    << "GRAY"       << ESC::RESET << "<<<"
                            << ">>>" << ESC::WHITE   << ESC::BG_WHITE   << "WHITE"      << ESC::RESET << "<<<"
                            << ">>>" << ESC::BLACK   << ESC::BG_BLACK   << "BLACK"      << ESC::RESET << "<<<"
                            );

    Log_GetLogger( acl, "ANSI_CONSOLE" );
    Log_Prune( if ( acl != nullptr )  ((AnsiConsoleLogger*)    acl) ->IsBackgroundLight= !((AnsiConsoleLogger*)    acl) ->IsBackgroundLight; )
    #if defined(_WIN32 )
    Log_GetLogger( wcl, "WINDOWS_CONSOLE" );
    Log_Prune( if ( wcl != nullptr )  ((WindowsConsoleLogger*) wcl) ->IsBackgroundLight= !((WindowsConsoleLogger*) wcl) ->IsBackgroundLight; )
    #endif

    Log_Info(    String256("Same rev.:  ")
                            << ">>>" << ESC::RED     << ESC::BG_RED     << "RED"        << ESC::RESET << "<<<"
                            << ">>>" << ESC::GREEN   << ESC::BG_GREEN   << "GREEN"      << ESC::RESET << "<<<"
                            << ">>>" << ESC::BLUE    << ESC::BG_BLUE    << "BLUE"       << ESC::RESET << "<<<"
                            << ">>>" << ESC::CYAN    << ESC::BG_CYAN    << "CYAN"       << ESC::RESET << "<<<"
                            << ">>>" << ESC::MAGENTA << ESC::BG_MAGENTA << "MAGENTA"    << ESC::RESET << "<<<"
                            << ">>>" << ESC::YELLOW  << ESC::BG_YELLOW  << "YELLOW"     << ESC::RESET << "<<<"
                            << ">>>" << ESC::GRAY    << ESC::BG_GRAY    << "GRAY"       << ESC::RESET << "<<<"
                            << ">>>" << ESC::WHITE   << ESC::BG_WHITE   << "WHITE"      << ESC::RESET << "<<<"
                            << ">>>" << ESC::BLACK   << ESC::BG_BLACK   << "BLACK"      << ESC::RESET << "<<<"
                            );
    Log_Prune( if ( acl != nullptr )  ((AnsiConsoleLogger*)    acl) ->IsBackgroundLight= !((AnsiConsoleLogger*)    acl) ->IsBackgroundLight; )
    #if defined(_WIN32 )
    Log_Prune( if ( wcl != nullptr )  ((WindowsConsoleLogger*) wcl) ->IsBackgroundLight= !((WindowsConsoleLogger*) wcl) ->IsBackgroundLight; )
    #endif

    Log_Verbose( testML->MemoryLog.ToCString() + mlPos );
    UT_TRUE( testML->MemoryLog.IndexOf('\033') < 0 ); testML->MemoryLog.Clear();
    Log_Info(    String256("Reset FG/BG: ")
                                << ESC::BG_RED     << "BG RED"
                                << ESC::GREEN      << "FG REEN"
                                << ESC::FG_RESET   << "FG Reset"
                                << ESC::BG_RESET   << "BG Reset"
                                );
    Log_Verbose( testML->MemoryLog.ToCString() + mlPos );
    UT_TRUE( testML->MemoryLog.IndexOf('\033') < 0 ); testML->MemoryLog.Clear();

    Log_Info(    String256("Reset FG/BG: ")
                                << ESC::BG_RED     << "BG RED"
                                << ESC::GREEN      << "FG REEN"
                                << ESC::BG_RESET   << "BG Reset"
                                << ESC::FG_RESET   << "FG Reset"
                                );
    Log_Verbose( testML->MemoryLog.ToCString() + mlPos );
    UT_TRUE( testML->MemoryLog.IndexOf('\033') < 0 ); testML->MemoryLog.Clear();

    Log_Info(    String256("Reset FG/BG: ")
                                << ESC::BG_RED     << "BG RED"
                                << ESC::GREEN      << "FG REEN"
                                << ESC::RESET      << "All Reset"
                                );
    Log_Verbose( testML->MemoryLog.ToCString() + mlPos );
    UT_TRUE( testML->MemoryLog.IndexOf('\033') < 0 ); testML->MemoryLog.Clear();

    Log_Info(    String256("Styles: ")
                                << ">>>" << ESC::BOLD     << "Bold"          << ESC::STYLE_RESET << "<<<"
                                << ">>>" << ESC::ITALICS  << "Italics"       << ESC::STYLE_RESET  << "<<<"
                                << ">>>" << ESC::BOLD
                                << ">>>" << ESC::ITALICS  << "Bold/Italics"   << ESC::STYLE_RESET  << "<<<  Styles do not work in Windows consoles"
                                );
    Log_Verbose( testML->MemoryLog.ToCString() + mlPos );
    UT_TRUE( testML->MemoryLog.IndexOf('\033') < 0 ); testML->MemoryLog.Clear();

    Log_Info(    String256("Reset Style/FG/BG: ")
                                << ESC::BOLD        << "Bold"
                                << ESC::BG_RED      << "BG RED"
                                << ESC::GREEN       << "FG REEN"
                                << ESC::BG_RESET    << "BG Reset"
                                << ESC::FG_RESET    << "FG Reset"
                                << ESC::STYLE_RESET << "Style Reset"
                                );
    Log_Verbose( testML->MemoryLog.ToCString() + mlPos );
    UT_TRUE( testML->MemoryLog.IndexOf('\033') < 0 ); testML->MemoryLog.Clear();

    Log_Info(    String256("Reset Style/FG/BG: ")
                                << ESC::BOLD        << "Bold"
                                << ESC::BG_RED      << "BG RED"
                                << ESC::GREEN       << "FG REEN"
                                << ESC::RESET       << "Reset All"
                                );
    Log_Verbose( testML->MemoryLog.ToCString() + mlPos );
    UT_TRUE( testML->MemoryLog.IndexOf('\033') < 0 ); testML->MemoryLog.Clear();

    Log_Info(    String256("Reset Style/FG/BG: ")
                                << ESC::BOLD        << "Bold"
                                << ESC::BG_RED      << "BG RED"
                                << ESC::GREEN       << "FG REEN"
                                << ESC::STYLE_RESET << "Style Reset"
                                << ESC::BG_RESET    << "BG Reset"
                                << ESC::FG_RESET    << "FG Reset"
                                << "   <<< This does not work on ANSI terminals: Styl reset, resets ALL here"
                                );
    Log_Verbose( testML->MemoryLog.ToCString() + mlPos );
    UT_TRUE( testML->MemoryLog.IndexOf('\033') < 0 ); testML->MemoryLog.Clear();

    Log_Info(    String256("An URL: ")
                                << ESC::URL_START   << "www.darwin.heaven"
                                << ESC::URL_END     << ", your resource for happyness!"
                                );

    Log_Verbose( testML->MemoryLog.ToCString() + mlPos );
    UT_TRUE( testML->MemoryLog.IndexOf('\033') < 0 ); testML->MemoryLog.Clear();

    Log_RemoveLogger( testML );
    Log_Prune( delete testML; );
}
#endif // defined( ALOX_REL_LOG_CI )

/** ********************************************************************************************
* Log_TextLogger_RegisterStdStreamLocks.
**********************************************************************************************/
#if defined( ALOX_DBG_LOG )
UT_METHOD(Log_TextLogger_RegisterStdStreamLocks)
{
    UT_INIT(); // This already registers the uint test logger. Therefore, the console lock in ALib
               // is occupied once already, but not in Safe mode, yet
                                UT_TRUE( ((ThreadLock&)ALIB::StdOutputStreamsLock).GetSafeness() == Safeness::Unsafe );
    Log_AddDebugLogger();
    UT_TRUE( ((ThreadLock&)ALIB::StdOutputStreamsLock).GetSafeness() == Safeness::Safe );
    Log_RemoveDebugLogger();    UT_TRUE( ((ThreadLock&)ALIB::StdOutputStreamsLock).GetSafeness() == Safeness::Unsafe );
    Log_AddDebugLogger();       UT_TRUE( ((ThreadLock&)ALIB::StdOutputStreamsLock).GetSafeness() == Safeness::Safe );

    #if defined( ALOX_REL_LOG )
        #define LOX_LOX lox
        Lox lox("ReleaseLox");

        // a memory logger must not change anything!
        Lox_SetVerbosity( Log::DebugLogger, Verbosity::Verbose );  UT_TRUE( ((ThreadLock&)ALIB::StdOutputStreamsLock).GetSafeness() == Safeness::Safe   );
        MemoryLogger ml;
        Lox_SetVerbosity( &ml,              Verbosity::Verbose );  UT_TRUE( ((ThreadLock&)ALIB::StdOutputStreamsLock).GetSafeness() == Safeness::Safe   );
        Lox_RemoveLogger( Log::DebugLogger);               UT_TRUE( ((ThreadLock&)ALIB::StdOutputStreamsLock).GetSafeness() == Safeness::Safe   );
        Log_RemoveDebugLogger();                           UT_TRUE( ((ThreadLock&)ALIB::StdOutputStreamsLock).GetSafeness() == Safeness::Unsafe );
        Lox_RemoveLogger( &ml )           ;                UT_TRUE( ((ThreadLock&)ALIB::StdOutputStreamsLock).GetSafeness() == Safeness::Unsafe );


        // while a console logger does
        Log_AddDebugLogger();                              UT_TRUE( ((ThreadLock&)ALIB::StdOutputStreamsLock).GetSafeness() == Safeness::Safe   );
        Lox_SetVerbosity( Log::DebugLogger, Verbosity::Verbose );  UT_TRUE( ((ThreadLock&)ALIB::StdOutputStreamsLock).GetSafeness() == Safeness::Safe   );
        ConsoleLogger cl;
        Lox_SetVerbosity( &cl,              Verbosity::Verbose );  UT_TRUE( ((ThreadLock&)ALIB::StdOutputStreamsLock).GetSafeness() == Safeness::Safe   );
        Log_SetVerbosity( &cl,              Verbosity::Verbose );  UT_TRUE( ((ThreadLock&)ALIB::StdOutputStreamsLock).GetSafeness() == Safeness::Safe   );

        Lox_RemoveLogger( Log::DebugLogger);               UT_TRUE( ((ThreadLock&)ALIB::StdOutputStreamsLock).GetSafeness() == Safeness::Safe   );
        Log_RemoveLogger( &cl)                             UT_TRUE( ((ThreadLock&)ALIB::StdOutputStreamsLock).GetSafeness() == Safeness::Safe   );
        Lox_RemoveLogger( &cl );                           UT_TRUE( ((ThreadLock&)ALIB::StdOutputStreamsLock).GetSafeness() == Safeness::Safe );
     #endif
     Log_RemoveDebugLogger();                              UT_TRUE( ((ThreadLock&)ALIB::StdOutputStreamsLock).GetSafeness() == Safeness::Unsafe   );
}
#endif // defined( ALOX_DBG_LOG )

/** ********************************************************************************************
* Log_TextLogger_FormatConfig
**********************************************************************************************/
void testFormatConfig( AWorxUnitTesting& ut, const String& testFormat,
                       const String& expFmt,
                       const String& expFmtError    = NullString,
                       const String& expFmtWarning  = NullString,
                       const String& expFmtInfo     = NullString,
                       const String& expFmtVerbose  = NullString
                     )
{
    Variable var;
    var.Define(ALox::ConfigCategoryName, "TESTML_FORMAT", ',').Store( testFormat  );
    MemoryLogger ml("TESTML");

    Lox lox("T", false );
    lox.SetScopeInfo( "ut_alox_logger.cpp", 425, "testFormatConfig" );
    lox.SetVerbosity( &ml, Verbosity::Info );

                                      UT_EQ( expFmt       , ml.MetaInfo->Format );
    if( expFmtError  .IsNotNull() ) { UT_EQ( expFmtError  , ml.MetaInfo->VerbosityError   ); }
    if( expFmtWarning.IsNotNull() ) { UT_EQ( expFmtWarning, ml.MetaInfo->VerbosityWarning ); }
    if( expFmtInfo   .IsNotNull() ) { UT_EQ( expFmtInfo   , ml.MetaInfo->VerbosityInfo    ); }
    if( expFmtVerbose.IsNotNull() ) { UT_EQ( expFmtVerbose, ml.MetaInfo->VerbosityVerbose ); }

    lox.RemoveLogger(&ml);
    lox.Release();

}


UT_METHOD(Log_TextLogger_FormatConfig)
{
    UT_INIT();
    testFormatConfig( ut, "Test"                                , "Test"                     );
    testFormatConfig( ut, "\"Test"                              , "Test"                     );
    testFormatConfig( ut, "\\\"Test"                            , "\"Test"                   );
    testFormatConfig( ut, "\"Test\""                            , "Test"                     );
    testFormatConfig( ut, "  \" Test \"        X"               , " Test X"                  );

    testFormatConfig( ut, " Test , a ,b,   c,d  "               , "Test", "a","b","c","d"    );
}

/** ********************************************************************************************
 * Log_LogLevelSetting
 **********************************************************************************************/
class TestMetaInfo : public lox::core::textlogger::MetaInfo
{
    public:       void    t(AString& buf, int64_t diff)     { writeTimeDiff( buf, diff ); }
};

UT_METHOD(Log_TextLoggerTimeDiff)
{
    UT_INIT();

    TestMetaInfo t;
    t.TimeDiffMinimum= 0;
    AString ms;
    int64_t diff;
    int64_t micros=     1000L;
    int64_t millis=     1000L * micros;
    int64_t secs=       1000L * millis;
    int64_t mins=          60 * secs;
    int64_t hours=         60 * mins;
    int64_t days=          24 * hours;


    t.TimeDiffMinimum= 0;
    diff= 0;                            ms.Clear(); t.t( ms, diff );
    UT_EQ( String16( "000" )._( t.TimeDiffNanos    ),   ms );
    diff= 15;                           ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "015"  )._( t.TimeDiffNanos    ),    ms );
    diff= 99;                           ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "099"  )._( t.TimeDiffNanos    ),    ms );
    diff= 600;                          ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "600"  )._( t.TimeDiffNanos    ),    ms );
    diff= 999;                          ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "999"  )._( t.TimeDiffNanos    ),    ms );
    diff= 1000;                         ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "001"  )._( t.TimeDiffMicros   ),    ms );
    t.TimeDiffMinimum= 700;
    diff= 600;                          ms.Clear(); t.t( ms, diff ); UT_EQ( String16(          )._( t.TimeDiffNone     ),    ms );
    diff= 700;                          ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "700"  )._( t.TimeDiffNanos    ),    ms );
    diff= 999;                          ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "999"  )._( t.TimeDiffNanos    ),    ms );
    t.TimeDiffMinimum= 1000;
    diff= 1000;                         ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "001"  )._( t.TimeDiffMicros   ),    ms );
    diff= 15 * micros;                  ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "015"  )._( t.TimeDiffMicros   ),    ms );
    diff= 99 * micros;                  ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "099"  )._( t.TimeDiffMicros   ),    ms );
    diff= 600* micros;                  ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "600"  )._( t.TimeDiffMicros   ),    ms );
    diff= 999* micros;                  ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "999"  )._( t.TimeDiffMicros   ),    ms );
    diff= 1   * millis;                 ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "001"  )._( t.TimeDiffMillis   ),    ms );
    diff= 999 * millis;                 ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "999"  )._( t.TimeDiffMillis   ),    ms );
    diff= 1   * secs;                   ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "1.00" )._( t.TimeDiffSecs     ),    ms );

    diff= 2   * secs + 344 * millis;    ms.Clear(); t.t( ms, diff );
    UT_EQ( String16(  "2.34" )._( t.TimeDiffSecs     ),    ms );

    diff= 3   * secs + 345 * millis;    ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "3.35" )._( t.TimeDiffSecs     ),    ms );
    diff= 9   * secs + 994 * millis;    ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "9.99" )._( t.TimeDiffSecs     ),    ms );
    diff= 9   * secs + 995 * millis;    ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "10.0" )._( t.TimeDiffSecs     ),    ms );
    diff= 9   * secs + 999 * millis;    ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "10.0" )._( t.TimeDiffSecs     ),    ms );
    diff= 10  * secs + 940 * millis;    ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "10.9" )._( t.TimeDiffSecs     ),    ms );
    diff= 10  * secs + 950 * millis;    ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "11.0" )._( t.TimeDiffSecs     ),    ms );

    diff= 99  * secs + 900 * millis;    ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "99.9" )._( t.TimeDiffSecs     ),    ms );
    diff= 99  * secs + 949 * millis;    ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "99.9" )._( t.TimeDiffSecs     ),    ms );


    diff= 2  * mins + 0 * secs;         ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "2.00" )._( t.TimeDiffMins     ),    ms );
    diff= 2  * mins + 30 * secs;        ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "2.50" )._( t.TimeDiffMins     ),    ms );
    diff= 9  * mins + 45 * secs;        ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "9.75" )._( t.TimeDiffMins     ),    ms );
    diff= 9  * mins + 59 * secs;        ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "9.98" )._( t.TimeDiffMins     ),    ms );
    diff= 9  * mins + 59500 * millis;   ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "9.99" )._( t.TimeDiffMins     ),    ms );
    diff= 9  * mins + 59999 * millis;   ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "10.0" )._( t.TimeDiffMins     ),    ms );

    diff= 99 * mins + 0 * secs;         ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "99.0" )._( t.TimeDiffMins     ),    ms );
    diff= 99 * mins + 30* secs;         ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "99.5" )._( t.TimeDiffMins     ),    ms );
    diff= 99 * mins + 59* secs;         ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "99.9" )._( t.TimeDiffMins     ),    ms );
    diff= 99 * mins + 59500* millis;    ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "99.9" )._( t.TimeDiffMins     ),    ms );
    diff= 99 * mins + 59999* millis;    ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "1.66" )._( t.TimeDiffHours    ),    ms );
    diff= 1 * hours + 30* mins;         ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "90.0" )._( t.TimeDiffMins     ),    ms );

    diff= 5 * hours + 30* mins;         ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "5.50" )._( t.TimeDiffHours    ),    ms );

    diff= 9 * hours + 45* mins;         ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "9.75" )._( t.TimeDiffHours    ),    ms );
    diff= 9 * hours + 59* mins;         ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "9.98" )._( t.TimeDiffHours    ),    ms );
    diff= 9 * hours + 3540* secs;       ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "9.98" )._( t.TimeDiffHours    ),    ms );
    diff= 9 * hours + 3580* secs;       ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "9.99" )._( t.TimeDiffHours    ),    ms );
    diff= 9 * hours + 3599* secs;       ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "9.99" )._( t.TimeDiffHours    ),    ms );
    diff= 9 * hours + 3600* secs;       ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "10.0" )._( t.TimeDiffHours    ),    ms );

    diff= 50 * hours + 15 *mins;        ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "50.2" )._( t.TimeDiffHours    ),    ms );
    diff= 99 * hours + 45 *mins;        ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "99.7" )._( t.TimeDiffHours    ),    ms );
    diff= 99 * hours + 48 *mins;        ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "99.8" )._( t.TimeDiffHours    ),    ms );
    diff= 99 * hours + 59 *mins;        ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "99.9" )._( t.TimeDiffHours    ),    ms );
    diff= 99 * hours + 3540* secs;      ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "99.9" )._( t.TimeDiffHours    ),    ms );
    diff= 99 * hours + 3580* secs;      ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "99.9" )._( t.TimeDiffHours    ),    ms );
    diff= 99 * hours + 3599* secs;      ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "99.9" )._( t.TimeDiffHours    ),    ms );
    diff= 99 * hours + 3600* secs;      ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "4.16" )._( t.TimeDiffDays     ),    ms );

    diff= 1 * days + 12* hours;         ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "36.0" )._( t.TimeDiffHours    ),    ms );

    diff= 5 * days + 18* hours;         ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "5.75" )._( t.TimeDiffDays     ),    ms );
    diff= 9 * days + 23* hours;         ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "9.95" )._( t.TimeDiffDays     ),    ms );
    diff= 9 * days + 1380 * mins;       ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "9.95" )._( t.TimeDiffDays     ),    ms );
    diff= 9 * days + 1400 * mins;       ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "9.97" )._( t.TimeDiffDays     ),    ms );
    diff= 9 * days + 1439 * mins;       ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "9.99" )._( t.TimeDiffDays     ),    ms );
    diff= 9 * days + 1440 * mins;       ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "10.0" )._( t.TimeDiffDays     ),    ms );
    diff= 15 * days + 6 * hours;        ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "15.2" )._( t.TimeDiffDays     ),    ms );
    diff= 99 * days + 18 * hours;       ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "99.7" )._( t.TimeDiffDays     ),    ms );
    diff= 99 * days + 1439 * mins;      ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "99.9" )._( t.TimeDiffDays     ),    ms );
    diff= 99 * days + 1440 * mins;      ms.Clear(); t.t( ms, diff ); UT_EQ( String16( "100.0" )._( t.TimeDiffDays     ),    ms );

    diff= 13452 * days+ 12* hours;      ms.Clear(); t.t( ms, diff ); UT_EQ( String16("13452.5")._( t.TimeDiffDays     ),    ms );
}


UT_CLASS_END

#endif // defined(ALOX_DBG_LOG)

} // namespace


