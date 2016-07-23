// #################################################################################################
//  ALox Samples
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################


#include "alib/alib.hpp"

#include "alox/alox.hpp"
#include "alox/alox_console_loggers.hpp"
#include "alox/loggers/memorylogger.hpp"
#include "alox/loggers/textfilelogger.hpp"
#include "alib/config/inifile.hpp"
#include "alib/system/system.hpp"

#include <iostream>


using namespace std;
using namespace aworx;

String64 autoSizes;

void DebugLog()
{
    cout << "cout: Do some debug logging:" <<  endl;

    Log_Info("Hello ALox, this is debug logging" );


    #if !defined(ALOX_DBG_LOG)
        cout << "cout: should not have logged something (this is the release version)" <<  endl;
    #endif

    cout <<  endl;
}


void ReleaseLog()
{
    cout << "cout: Do some release logging:" <<  endl;

    Lox_Prune( Lox lox("ReleaseLox"); )
    #define LOX_LOX lox

    // let the system choose an appropriate console logger
    Lox_Prune( TextLogger* releaseLogger= Lox::CreateConsoleLogger(); )

    // In debug compilations, we still install a report writer.
    // Note that we are using debug-macro prefixed "Log_" as in release versions, no ALib reports are written.
    Log_Prune( Log::AddALibReportWriter( &LOX_LOX ); )
    Log_Prune( Lox_SetVerbosity( releaseLogger, Verbosity::Verbose, lox::ALoxReportWriter::LogDomain() ); )

    // if makefile did not specify scope info for release logging (which is standard behavior),
    // we set a format string without scope information.
    #if !defined( ALOX_REL_LOG_CI )
        Lox_Prune( releaseLogger->MetaInfo->Format= "[%TC+%TL][%tN]%V[%D]%A1(%#): "; )
    #endif

    Lox_SetVerbosity( releaseLogger, Verbosity::Info );
    Lox_Info ( "Hello ALox, this is release logging" );


    // shutdown
    Log_Prune( Log::RemoveALibReportWriter() ); // note: using "Log_" -macro as above!

    Lox_RemoveLogger( releaseLogger );
    Lox_Prune( delete releaseLogger; )

    #if !defined(ALOX_REL_LOG)
        cout << "cout: should not have logged something (release logging was disabled, obviously ALOX_REL_LOG_OFF was passed to the compiler)" <<  endl;
    #endif
    cout <<  endl;
}


// #################################################################################################
// performanceTest()
// #################################################################################################
void PerformanceTest()
{
    Log_AddDebugLogger();
    Lox_Prune( MemoryLogger ml( nullptr, true, false); )

    // to align all samples nicely, we are manually adding the autosizes from the config.
    // This is not needed for standard applications that create one debug logger at the start and
    // use this till the end
    Log_Prune( Log::DebugLogger->AutoSizes.Import( Substring(autoSizes), CurrentData::Keep );  )


                                    Log_SetVerbosity( Log::DebugLogger, Verbosity::Off,     "/MEM" )  ;
    Log_Prune( if (Log::IDELogger ) Log_SetVerbosity( Log::IDELogger  , Verbosity::Off,     "/MEM" ) );
                                    Log_SetVerbosity( &ml,              Verbosity::Verbose, "/MEM" );

    Log_Info( "Logging simple info lines" );


    #if defined( _MSC_VER )
        int_fast64_t fastest=       MAXINT;
    #else
        int_fast64_t fastest=       std::numeric_limits<int>::max();
    #endif

    #if !defined(ALIB_DEBUG_STRINGS)
        int qtyLines=   100;
        int qtyLoops=   100;
    #else
        int qtyLines=  100;
        int qtyLoops=   10;
    #endif

    if ( System::IsDebuggerPresent() )
        qtyLoops= 10;


    for ( int i= 0 ; i < qtyLoops ; i++ )
    {
        #if defined(ALOX_REL_LOG)
            ml.MemoryLog.Clear();
        #endif

        Ticks tt;
            for ( int l= 0 ; l < qtyLines ; l++ )
            {
                Log_Info ( "/MEM", String32("Test Line ") << l  );
                Log_Prune( if( i== 0 && l == 0) Log_Info( String256() << "Sample Output: " << NewLine << "  "
                                                                      << ml.MemoryLog.ToCString() ); )
            }
        Ticks t= tt.Age();

        if ( t.Raw() < fastest )
        {
            fastest= t.Raw();
            Log_Info( String128() << "Pass " << i << " is new fastest: " << ESC::TAB
                                  << t.InMicros() << " micros per " <<  qtyLines << " logs." );
        }
    }

    Log_Prune( double microsPerLog=  ( (double) (Ticks(fastest)).InMicros() ) / qtyLines; )
    Log_Prune( int    logsPerSecond= (int)( 1000000.0 / microsPerLog);                    )

    Log_Info( String256()._( "  " )._( ESC::MAGENTA )._( "Fastest Debug Logging: " )
                         ._( microsPerLog  )._( " micros per log (resp " )
                         ._( logsPerSecond )._( " logs per second) " ) );


    Log_RemoveLogger( &ml );
}

// #################################################################################################
// performanceTest()
// #################################################################################################
void PerformanceTestRL()
{
    Lox_Prune( Lox lox("ReleaseLox"); )
    #define LOX_LOX lox

    Lox_Prune( TextLogger*  releaseLogger= Lox::CreateConsoleLogger();  )
    Lox_Prune( MemoryLogger ml( nullptr, true, false);                  )

    // if makefile did not specify scope info for release logging (which is standard behavior),
    // we set a format string without scope information.
    #if !defined( ALOX_REL_LOG_CI )
        Lox_Prune( releaseLogger->MetaInfo->Format= "[%TC+%TL][%tN]%V[%D]%A1(%#): "; )
        Lox_Prune( ml.            MetaInfo->Format= "[%TC+%TL][%tN]%V[%D]%A1(%#): "; )
    #endif

    Lox_SetVerbosity( releaseLogger, Verbosity::Verbose,   "/CON" );
    Lox_SetVerbosity( &ml,           Verbosity::Verbose,   "/MEM" );

    // to align all samples nicely, we are manually adding the autosizes from the config.
    // This is not needed for standard applications that create one debug logger at the start and
    // use this till the end
    Lox_Prune(     releaseLogger->AutoSizes.Import( Substring(autoSizes) );                           )

    Lox_Info( "/CON", "Logging simple info lines (release logging)" );

    #if defined( _MSC_VER )
        int_fast64_t fastest=       MAXINT;
    #else
        int_fast64_t fastest=       std::numeric_limits<int>::max();
    #endif
    #if !defined(ALIB_DEBUG_STRINGS)
        int qtyLines=   100;
        int qtyLoops=   100;
    #else
        int qtyLines=  100;
        int qtyLoops=   10;
    #endif
    if ( System::IsDebuggerPresent() )
        qtyLoops= 10;

    for ( int i= 0 ; i < qtyLoops ; i++ )
    {
        #if defined(ALOX_DBG_LOG) || defined(ALOX_REL_LOG)
            ml.MemoryLog.Clear();
        #endif
        Ticks tt;
            for ( int l= 0 ; l < qtyLines ; l++ )
            {
                Lox_Info ( "/MEM", String32("Test Line ") << l );
                Lox_Prune( if( i== 0 && l == 0) Lox_Info( String256() << "Sample Output: " << NewLine << "  "
                                                                      << ml.MemoryLog.ToCString() ); )
            }
        Ticks t= tt.Age();

        if ( t.Raw() < fastest )
        {
            fastest= t.Raw();
            Lox_Info ( "/CON", String128()  << "Pass "  << i  << " is new fastest: " << ESC::TAB
                                            << t.InMicros() << " micros per " <<  qtyLines << " logs." );
        }
    }

    double microsPerLog=  ( (double) (Ticks(fastest)).InMicros() ) / qtyLines;
    int    logsPerSecond= (int)( 1000000.0 / microsPerLog);
    Lox_Info( "/CON", String256()._( "  " )._( ESC::MAGENTA )._( "Fastest Release Logging: " )
                                 ._( microsPerLog  )._( " micros per log (resp " )
                                 ._( logsPerSecond )._( " logs per second) " ) );

    Lox_RemoveLogger( &ml );
    Lox_RemoveLogger( releaseLogger );
    Lox_Prune( delete releaseLogger; )
}

void LogColors()
{
    Log_AddDebugLogger();
    // to align all samples nicely, we are manually adding the autosizes from the config.
    // This is not needed for standard applications that create one debug logger at the start and
    // use this till the end
    Log_Prune( Log::DebugLogger->AutoSizes.Import( Substring(autoSizes), CurrentData::Keep );  )

    cout << "cout: Colorful logging:" <<  endl;

    Log_Info(    "We hope within your IDE, you can doubleclick this line?" );
    Log_Warning( "And is this line colored?" );
    Log_Error(   "And is this line colored?" );
    Log_Info(    "Color table:");
    Log_Info( String256() << "FG Colors:  "
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

    Log_Info( String256() << "BG Colors:  "
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

    Log_Info( String256() << "FG/BG same: "
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

    #if !defined(ALOX_DBG_LOG)
        cout << "cout: should not have logged something (this is the release version)" <<  endl;
    #endif

    cout <<  endl;
}

void WCharTest()
{
    Log_AddDebugLogger();
    // to align all samples nicely, we are manually adding the autosizes from the config.
    // This is not needed for standard applications that create one debug logger at the start and
    // use this till the end
    Log_Prune( Log::DebugLogger->AutoSizes.Import( Substring(autoSizes), CurrentData::Keep );  )

    Log_SetDomain( "WCHAR", Scope::Method );

    String256 ms;
    ms.Clear() << "ASCII String as wide: " <<  L"AString";                          Log_Info( ms );



    ms.Clear() << "Euro sign:            " <<  L"\u20AC";                           Log_Info( ms );


    ms.Clear() << "Greek characters:     " <<  L"\u03B1\u03B2\u03B3\u03B4\u03B5";   Log_Info( ms );


    // from https://msdn.microsoft.com/en-us/library/69ze775t.aspx
    ms.Clear() << "Smileys:              " <<  L"😉 = \U0001F609 is ;-)";           Log_Info( ms );
    ms.Clear() << "                      " <<  L"😇 = \U0001F607 is O:-)";          Log_Info( ms );
    ms.Clear() << "                      " <<  L"😃 = \U0001F603 is :-D";           Log_Info( ms );
    ms.Clear() << "                      " <<  L"😎 = \U0001F60E is B-)";           Log_Info( ms );
    ms.Clear() << "                      " <<  L"( ͡° ͜ʖ ͡°) = ( \U00000361\U000000b0 \U0000035c\U00000296 \U00000361\U000000b0)";            Log_Info( ms );


    Log_Info( String64() << "sizeof wchar: "  << sizeof(wchar_t) );
    Log_Info( String64() << "Max wchar:    "  << WCHAR_MAX);
    Log_Info( String64() << "Min wchar:    "  << WCHAR_MIN);
}

void textFileLogger()
{
    Log_AddDebugLogger();
    // to align all samples nicely, we are manually adding the autosizes from the config.
    // This is not needed for standard applications that create one debug logger at the start and
    // use this till the end
    Log_Prune( Log::DebugLogger->AutoSizes.Import( Substring(autoSizes), CurrentData::Keep );  )

    Log_Info( "Creating a text file logger with file 'Test.log.txt'" );

    Log_SetDomain( "TEXTFILE_TEST", Scope::Method    );

    Log_Prune( TextFileLogger tfl( "Test.log.txt" ) );
    Log_SetVerbosity( &tfl, Verbosity::Verbose );
    Log_SetVerbosity( &tfl, Verbosity::Error, ALox::InternalDomains );

    Log_Verbose( "A verbose message (goes to textfile logger as well)" );
    Log_Info   ( "An info message  (goes to textfile logger as well)" );
    Log_Warning( "A warning message  (goes to textfile logger as well)" );
    Log_Error  ( "An error message (goes to textfile logger as well)" );
    Log_Info   ( "Multiline part 1...\n....part 2" );

    Log_RemoveLogger( &tfl )
}

void SampleALibReport()
{
    Log_AddDebugLogger();
    // to align all samples nicely, we are manually adding the autosizes from the config.
    // This is not needed for standard applications that create one debug logger at the start and
    // use this till the end
    Log_Prune( Log::DebugLogger->AutoSizes.Import( Substring(autoSizes), CurrentData::Keep );  )

    Log_Info( "Sample: ALib Report Writer\n"
              "Method \"Log::AddDebugLogger()\" by default creates a replacement for the\n"
              "standard ALib report writer. If this is a debug compiliation, let's have a try and\n"
              "create an 3 Messages:"  );

    // must be done only in debug compiles
    #if defined(ALIB_DEBUG)

    lib::Report::GetDefault().PushHaltFlags( false, false );

        ALIB_ERROR(   "This is an error report!" );
        ALIB_WARNING( "And this is a warning!"   );
        AString test("Four");
        test.SetLength<false>(10);

    lib::Report::GetDefault().PopHaltFlags();

    #endif

    Log_SetVerbosity( Log::DebugLogger, Verbosity::Verbose, ALox::InternalDomains );
    ALIB_REPORT( 2, "This is an ALib Report. Types other than '0' and '1' are user defined.\n"
                    "Verbosity of ALox::InternalDomains has to be increased to see them when using"
                    " ALoxReportWriter." );

    Log_Info( String256() <<   "Note the domain prefix '" << ALox::InternalDomains << "'. This addresses "
             << "the tree of internal domains\nof the Lox, which the report writer is just "
             << "using." );
}


void ALoxSampleReset()
{
    #if defined(ALOX_DBG_LOG)
        if ( Log::DebugLogger != nullptr )
        {
            Log::DebugLogger->AutoSizes.Export( autoSizes.Clear() );
            Log_RemoveDebugLogger();
        }
    #endif

    Log_Prune( LOG_LOX.Reset(); )
    Log_SetSourcePathTrimRule( "*/src.cpp/", Inclusion::Include );
}


int main( int argc, char *argv[] )
{
    // first attach INI file to config system...
    IniFile iniFile;
    if ( iniFile.FileComments.IsEmpty() )
    {
        iniFile.FileComments._(
        "##################################################################################################\n"
        "# ALox Samples INI file (created when running ALox Samples)\n"
        "#\n"
        "# (c) 2013-2016 A-Worx GmbH, Germany\n"
        "# Published under MIT License (Open Source License, see LICENSE.txt)\n"
        "##################################################################################################\n"
        );
    }


    ALIB::Config.InsertPlugin( &iniFile, Configuration::PrioIniFile );

    //... and then initialize ALox Logging Library
    ALox::Init( argc, argv );

    Log_SetSourcePathTrimRule( "*/src.cpp/", Inclusion::Include );

    // Suppress setting "writeback" as default verbosities. We need to do this as this main()
    // method invokes a list of independent samples. Those would now read from the INI file wrong
    // values written in other sample methods and thus the samples would not work any more
    // (because INI file settings overrules settings in the code)
    Variable var;
    var.Define( "ALOX", "LOG_DEBUG_LOGGER_VERBOSITY"  ).Store( "" );
    var.Define( "ALOX", "RELEASELOX_CONSOLE_VERBOSITY").Store( "" );
    var.Define( "ALOX", "LOG_MEMORY_VERBOSITY"        ).Store( "" );
    var.Define( "ALOX", "RELEASELOX_MEMORY_VERBOSITY" ).Store( "" );
    var.Define( "ALOX", "LOG_TEXTFILE_VERBOSITY"      ).Store( "" );

    DebugLog();                 ALoxSampleReset();
    ReleaseLog();               ALoxSampleReset();
    PerformanceTest();          ALoxSampleReset();
    PerformanceTestRL();        ALoxSampleReset();
    LogColors();                ALoxSampleReset();
    SampleALibReport();         ALoxSampleReset();
    WCharTest();                ALoxSampleReset();
    textFileLogger();           ALoxSampleReset();

    // cleanup resources to make Valgrind happy
    ALIB::Config.RemovePlugin( &iniFile );
    ALIB::Config.FetchFromDefault( iniFile );
    iniFile.WriteFile();

    ALox::TerminationCleanUp();
    cout << "ALox Samples finished" << endl;
    return 0;
}



