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



#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define TESTCLASSNAME       CPP_ALox_Loggers
#include "aworx_unittests.hpp"

using namespace std;
using namespace ut_aworx;

using namespace aworx;
using namespace aworx::lib;
using namespace aworx::lox;
using namespace aworx::lox::core;
using namespace aworx::lox::loggers;


namespace ut_alox {

#if defined(ALOX_DBG_LOG)
    /** ********************************************************************************************
     * loggers used
     **********************************************************************************************/
    extern MemoryLogger*   ml_dbg_log;

    /** ********************************************************************************************
     * Creates loggers.
     **********************************************************************************************/
    extern void   deleteLoggers_dbg_log();
    extern void   clearCreateAndAddLoggers_dbg_log( bool memoryLogger= false, bool consoleLogger= true);


UT_CLASS()


    /** ********************************************************************************************
     * Log_ColorsAndStyles.
     **********************************************************************************************/

    #if defined( ALOX_DBG_LOG ) && defined(ALOX_DBG_LOG_CI)
        UT_METHOD(Log_ColorsAndStyles)

            clearCreateAndAddLoggers_dbg_log( true, true );

            Log_SetDomain( "COLORS", Log::DomainLevel::All );
            Log_SetDomain( "COLORS", Log::Scope::Method );

            Log_Info( "Playing with colors. Depending on the test environment, the colors might "
                      "be visible or not" );
            Log_Info( "In the memory logger, all color/style codes have to disappear (by default)" );
            Log_Verbose( "A verbose message" );
            Log_Info   ( "An info message" );
            Log_Warning( "A warning message" );
            Log_Error  ( "An error message" );
            int mlPos= ml_dbg_log->MemoryLog.IndexOf("[COLORS]" );
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

            UT_TRUE( ml_dbg_log->MemoryLog.IndexOf('\033') < 0 ); ml_dbg_log->MemoryLog.Clear();

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

            UT_TRUE( ml_dbg_log->MemoryLog.IndexOf('\033') < 0 ); ml_dbg_log->MemoryLog.Clear();

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

            Log_Prune( Logger* acl= nullptr; )    Log_GetLogger( acl, "ANSI_CONSOLE" );
            Log_Prune( if ( acl != nullptr )  ((AnsiConsoleLogger*)    acl) ->IsBackgroundLight= !((AnsiConsoleLogger*)    acl) ->IsBackgroundLight; )
            #if defined(_WIN32 )
            Log_Prune( Logger* wcl= nullptr; )    Log_GetLogger( wcl, "WINDOWS_CONSOLE" );
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

            Log_Verbose( ml_dbg_log->MemoryLog.ToCString() + mlPos );
            UT_TRUE( ml_dbg_log->MemoryLog.IndexOf('\033') < 0 ); ml_dbg_log->MemoryLog.Clear();
            Log_Info(    String256("Reset FG/BG: ")
                                        << ESC::BG_RED     << "BG RED"
                                        << ESC::GREEN      << "FG REEN"
                                        << ESC::FG_RESET   << "FG Reset"
                                        << ESC::BG_RESET   << "BG Reset"
                                        );
            Log_Verbose( ml_dbg_log->MemoryLog.ToCString() + mlPos );
            UT_TRUE( ml_dbg_log->MemoryLog.IndexOf('\033') < 0 ); ml_dbg_log->MemoryLog.Clear();

            Log_Info(    String256("Reset FG/BG: ")
                                        << ESC::BG_RED     << "BG RED"
                                        << ESC::GREEN      << "FG REEN"
                                        << ESC::BG_RESET   << "BG Reset"
                                        << ESC::FG_RESET   << "FG Reset"
                                        );
            Log_Verbose( ml_dbg_log->MemoryLog.ToCString() + mlPos );
            UT_TRUE( ml_dbg_log->MemoryLog.IndexOf('\033') < 0 ); ml_dbg_log->MemoryLog.Clear();

            Log_Info(    String256("Reset FG/BG: ")
                                        << ESC::BG_RED     << "BG RED"
                                        << ESC::GREEN      << "FG REEN"
                                        << ESC::RESET      << "All Reset"
                                        );
            Log_Verbose( ml_dbg_log->MemoryLog.ToCString() + mlPos );
            UT_TRUE( ml_dbg_log->MemoryLog.IndexOf('\033') < 0 ); ml_dbg_log->MemoryLog.Clear();

            Log_Info(    String256("Styles: ")
                                        << ">>>" << ESC::BOLD     << "Bold"          << ESC::STYLE_RESET << "<<<"
                                        << ">>>" << ESC::ITALICS  << "Italics"       << ESC::STYLE_RESET  << "<<<"
                                        << ">>>" << ESC::BOLD
                                        << ">>>" << ESC::ITALICS  << "Bold/Italics"   << ESC::STYLE_RESET  << "<<<  Styles do not work in Windows consoles"
                                        );
            Log_Verbose( ml_dbg_log->MemoryLog.ToCString() + mlPos );
            UT_TRUE( ml_dbg_log->MemoryLog.IndexOf('\033') < 0 ); ml_dbg_log->MemoryLog.Clear();

            Log_Info(    String256("Reset Style/FG/BG: ")
                                        << ESC::BOLD        << "Bold"
                                        << ESC::BG_RED      << "BG RED"
                                        << ESC::GREEN       << "FG REEN"
                                        << ESC::BG_RESET    << "BG Reset"
                                        << ESC::FG_RESET    << "FG Reset"
                                        << ESC::STYLE_RESET << "Style Reset"
                                        );
            Log_Verbose( ml_dbg_log->MemoryLog.ToCString() + mlPos );
            UT_TRUE( ml_dbg_log->MemoryLog.IndexOf('\033') < 0 ); ml_dbg_log->MemoryLog.Clear();

            Log_Info(    String256("Reset Style/FG/BG: ")
                                        << ESC::BOLD        << "Bold"
                                        << ESC::BG_RED      << "BG RED"
                                        << ESC::GREEN       << "FG REEN"
                                        << ESC::RESET       << "Reset All"
                                        );
            Log_Verbose( ml_dbg_log->MemoryLog.ToCString() + mlPos );
            UT_TRUE( ml_dbg_log->MemoryLog.IndexOf('\033') < 0 ); ml_dbg_log->MemoryLog.Clear();

            Log_Info(    String256("Reset Style/FG/BG: ")
                                        << ESC::BOLD        << "Bold"
                                        << ESC::BG_RED      << "BG RED"
                                        << ESC::GREEN       << "FG REEN"
                                        << ESC::STYLE_RESET << "Style Reset"
                                        << ESC::BG_RESET    << "BG Reset"
                                        << ESC::FG_RESET    << "FG Reset"
                                        << "   <<< This does not work on ANSI terminals: Styl reset, resets ALL here"
                                        );
            Log_Verbose( ml_dbg_log->MemoryLog.ToCString() + mlPos );
            UT_TRUE( ml_dbg_log->MemoryLog.IndexOf('\033') < 0 ); ml_dbg_log->MemoryLog.Clear();

            Log_Info(    String256("An URL: ")
                                        << ESC::URL_START   << "www.darwin.heaven"
                                        << ESC::URL_END     << ", your resource for happyness!"
                                        );

            Log_Verbose( ml_dbg_log->MemoryLog.ToCString() + mlPos );
            UT_TRUE( ml_dbg_log->MemoryLog.IndexOf('\033') < 0 ); ml_dbg_log->MemoryLog.Clear();



            deleteLoggers_dbg_log();

        }
    #endif // defined( ALOX_REL_LOG_CI )

UT_CLASS_END

#endif // defined(ALOX_DBG_LOG)

} // namespace


