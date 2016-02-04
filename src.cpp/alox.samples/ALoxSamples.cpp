// #################################################################################################
//  aworx - Unit Tests
//  Private, not published in git ( I hope! )
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################


#include "alib/alib.hpp"

#include "alox/alox.hpp"
#include "alox/alox_console_loggers.hpp"
#include "alox/loggers/memorylogger.hpp"
#include "alox/loggers/textfilelogger.hpp"
#include "alib/config/inifile.hpp"

#include <iostream>


using namespace std;
using namespace aworx;
using namespace aworx::lib;
using namespace aworx::lib::enums;
using namespace aworx::lib::time;
using namespace aworx::lox;
using namespace aworx::lox::core::textlogger;
using namespace aworx::lox::loggers;

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

    // let the system choose an appropriate console logger
    Lox_Prune( TextLogger* releaseLogger= Lox::CreateConsoleLogger(); )

    // to align all samples nicely, we are manually adding the autosizes from the config.
    // This is not needed for standard applications that create one debug logger at the start and
    // use this till the end
    Lox_Prune(  String64 autoSizes;                                                                 )
    Lox_Prune(  if( ALIB::Config->Get( Log::ConfigCategoryName, "CL_AUTO_SIZES", autoSizes ) != 0 ) )
    Lox_Prune(     releaseLogger->AutoSizes.Import( Substring(autoSizes) );                           )

    // if makefile did not specify caller info for release logging (which is standard behavior),
    // we set a format string without caller information.
    #ifndef ALOX_REL_LOG_CI
        Lox_Prune( releaseLogger->MetaInfo->Format= "[%TE +%TI] [%t] %L [%O] %A1(%#): "; )
    #endif

    Lox_AddLogger( releaseLogger );
    Lox_SetDomain( "A_DOMAIN", Log::DomainLevel::InfoWarningsAndErrors );
    Lox_Info ( "A_DOMAIN", "Hello ALox, this is release logging" );
    Lox_RemoveLoggers( nullptr );
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
    MemoryLogger ml( nullptr, true, false);
    Log_AddLogger( &ml );

    Log_SetDomain( "CON", Log::Scope::SourceFile );
    Log_SetDomain( "MEM", Log::Scope::None  );
    Log_SetDomain( "BOTH",Log::Scope::None );

    Log_SetDomain ( "CON", Log::DomainLevel::All, Log::DebugLogger->Name.ToCString() );
    Log_SetDomain ( "MEM", Log::DomainLevel::Off, Log::DebugLogger->Name.ToCString() );
    Log_SetDomain ( "MEM", Log::DomainLevel::Off, "VSTUDIO_CONSOLE" );
    Log_SetDomain ( "MEM", Log::DomainLevel::All, "Memory" );
    Log_SetDomain ( "CON", Log::DomainLevel::Off, "Memory" );
    Log_SetDomain ( "BOTH",Log::DomainLevel::All  );


    Log_Info( "Logging simple info lines" );

    AString msgBuf;
    #if defined( _MSC_VER )
        int_fast64_t fastest=       MAXINT;
    #else
        int_fast64_t fastest=       std::numeric_limits<int>::max();
    #endif

    #if !defined(ALIB_DEBUG_STRINGS)
        const int qtyLines=  100;
        const int qtyLoops= 1000;
    #else
        const int qtyLines=  100;
        const int qtyLoops=   10;
    #endif
    for ( int i= 0 ; i < qtyLoops ; i++ )
    {
        #if defined(ALOX_DBG_LOG) || defined(ALOX_REL_LOG)
            ml.MemoryLog.Clear();
        #endif

        Ticks tt;
            for ( int l= 0 ; l < qtyLines ; l++ )
            {
                Log_Info ( "MEM", String32("Test Line ") << l  );
            }
        Ticks t= tt.Age();

        if ( t.Raw() < fastest )
        {
            fastest= t.Raw();
            Log_Info( msgBuf.Clear() << "Pass " << i << " is new fastest: " //<< ESC::TAB
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
    aworx::lox::core::textlogger::TextLogger*    releaseLogger= Lox::CreateConsoleLogger();
    releaseLogger->SetDomain( LOG_REL_LOX.InternalDomain, Log::DomainLevel::WarningsAndErrors );
    Lox_AddLogger( releaseLogger );
    // to align all samples nicely, we are manually adding the autosizes from the config.
    // This is not needed for standard applications that create one debug logger at the start and
    // use this till the end
    Lox_Prune(  String64 autoSizes;                                                                 )
    Lox_Prune(  if( ALIB::Config->Get( Log::ConfigCategoryName, "CL_AUTO_SIZES", autoSizes ) != 0 ) )
    Lox_Prune(     releaseLogger->AutoSizes.Import( Substring(autoSizes) );                           )

    MemoryLogger ml( nullptr, true, false);

    Lox_AddLogger( &ml );

    Lox_SetDomain( "CON", Log::Scope::SourceFile );
    Lox_SetDomain( "MEM", Log::Scope::None  );
    Lox_SetDomain( "BOTH",Log::Scope::None );

    Lox_SetDomain( "CON", Log::DomainLevel::All,  releaseLogger->Name.ToCString() );
    Lox_SetDomain( "MEM", Log::DomainLevel::Off,  releaseLogger->Name.ToCString() );
    Lox_SetDomain( "MEM", Log::DomainLevel::All, "Memory" );
    Lox_SetDomain( "CON", Log::DomainLevel::Off, "Memory" );
    Lox_SetDomain( "BOTH",Log::DomainLevel::All );


    Lox_Info( "Logging simple info lines (release logging)" );

    AString msgBuf;
    #if defined( _MSC_VER )
        int_fast64_t fastest=       MAXINT;
    #else
        int_fast64_t fastest=       std::numeric_limits<int>::max();
    #endif
    #if !defined(ALIB_DEBUG_STRINGS)
        const int qtyLines=   100;
        const int qtyLoops= 10000;
    #else
        const int qtyLines=  100;
        const int qtyLoops=   10;
    #endif
    for ( int i= 0 ; i < qtyLoops ; i++ )
    {
        #if defined(ALOX_DBG_LOG) || defined(ALOX_REL_LOG)
            ml.MemoryLog.Clear();
        #endif
        Ticks tt;
            for ( int l= 0 ; l < qtyLines ; l++ )
                Lox_Info ( "MEM", String32("Test Line ") << l );
        Ticks t= tt.Age();

        if ( t.Raw() < fastest )
        {
            fastest= t.Raw();
            Lox_Info ( "CON",
                       msgBuf.Clear() << "Pass "  << i  << " is new fastest: " << ESC::TAB
                                      << t.InMicros() << " micros per " <<  qtyLines << " logs." );
        }
    }

    double microsPerLog=  ( (double) (Ticks(fastest)).InMicros() ) / qtyLines;
    int    logsPerSecond= (int)( 1000000.0 / microsPerLog);
    Lox_Info( String256()._( "  " )._( ESC::MAGENTA )._( "Fastest Release Logging: " )
                         ._( microsPerLog  )._( " micros per log (resp " )
                         ._( logsPerSecond )._( " logs per second) " ) );

    Lox_RemoveLoggers( nullptr );
    Lox_Prune( delete releaseLogger; )
}

void LogColors()
{
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
    Log_SetDomain( "WCHAR", Log::Scope::Method, Log::DomainLevel::All );

    String128 ms;
    ms.Clear() << "ASCII String as wide: " <<  L"AString";                          Log_Info( ms );



    ms.Clear() << "Euro sign:            " <<  L"\u20AC";                           Log_Info( ms );


    ms.Clear() << "Greek characters:     " <<  L"\u03B1\u03B2\u03B3\u03B4\u03B5";   Log_Info( ms );


    // from https://msdn.microsoft.com/en-us/library/69ze775t.aspx
    ms.Clear() << "Smileys:              " <<  L"😉 = \U0001F609 is ;-)";           Log_Info( ms );
    ms.Clear() << "                      " <<  L"😇 = \U0001F607 is O:-)";          Log_Info( ms );
    ms.Clear() << "                      " <<  L"😃 = \U0001F603 is :-D";           Log_Info( ms );
    ms.Clear() << "                      " <<  L"😎 = \U0001F60E is B-)";           Log_Info( ms );
    ms.Clear() << "                      " <<  L"( ͡° ͜ʖ ͡°) = ( \U00000361\U000000b0 \U0000035c\U00000296 \U00000361\U000000b0)";            Log_Info( ms );


    Log_Info( String32() << "sizeof wchar: "  << sizeof(wchar_t) );
    Log_Info( String32() << "Max wchar:    "  << WCHAR_MAX);
    Log_Info( String32() << "Min wchar:    "  << WCHAR_MIN);
}

void textFileLogger()
{
    Log_Info( "Creating a text file logger with file 'Test.log.txt'" );
    Log_Prune( TextFileLogger tfl( "Test.log.txt" ) );
    Log_Prune( tfl.SetDomain( LOG_LOX.InternalDomain, Log::DomainLevel::Errors ) );
    Log_AddLogger( &tfl );
    Log_SetDomain( "TEXTFILE_TEST", Log::Scope::Method    );
    Log_SetDomain( "TEXTFILE_TEST", Log::DomainLevel::All );

    Log_Verbose( "A verbose message (goes to textfile logger as well)" );
    Log_Info   ( "An info message  (goes to textfile logger as well)" );
    Log_Warning( "A warning message  (goes to textfile logger as well)" );
    Log_Error  ( "An error message (goes to textfile logger as well)" );
    Log_Info   ( "Multiline part 1...\n....part 2" );
}

void SampleALibReport()
{
    Log_Info( "Sample: ALib Report via using ALox\n"
              "Method \"Log::AddDebugLogger()\" by default creates a replacement for ALib\n"
              "error/warning reporter. If this is a debug compiliation, let's have a try and\n"
              "create an ALib error:"  );

    // must be done only in debug compiles
    #if defined(ALIB_DEBUG)
    bool haltOnErrorOrig=    Report::GetDefault().HaltOnError;
    bool haltOnWarningOrig=  Report::GetDefault().HaltOnWarning;
    Report::GetDefault().HaltOnError=   false;
    Report::GetDefault().HaltOnWarning= false;

        ALIB_ERROR(   "This is an error report!" );
        ALIB_WARNING( "And this is a warning!"   );


    Report::GetDefault().HaltOnError  = haltOnErrorOrig;
    Report::GetDefault().HaltOnWarning= haltOnWarningOrig;

    #endif
    Log_Info( "Note the domain 'REPORT' used by ALib reporter." );
}


int main( int argc, char *argv[] )
{
    Log::Init( Inclusion::Include, argc, (void**) argv );
    config::IniFile iniFile;
    ALIB::Config->InsertPlugin( &iniFile, 30 );


    DebugLog();
    ReleaseLog();
    PerformanceTest();
    PerformanceTestRL();
    LogColors();
    SampleALibReport();
    WCharTest();
    textFileLogger();

    // cleanup resources to make Valgrind happy
    ALIB::Config->RemovePlugin( &iniFile );
    Log::TerminationCleanUp();
    return 0;
}



