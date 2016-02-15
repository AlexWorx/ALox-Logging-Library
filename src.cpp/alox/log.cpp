// #################################################################################################
//  aworx::lox - ALox Logging Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
#include "alib/stdafx_alib.h"

#if !defined (HPP_ALOX)
    #include "alox/alox.hpp"
#endif

#if !defined (HPP_ALIB_CONFIG_CONFIGURATION)
    #include "alib/config/configuration.hpp"
#endif

#if !defined (HPP_ALIB_SYSTEM_SYSTEMINFO)
    #include "alib/system/system.hpp"
#endif

#if !defined ( HPP_ALOX_CONSOLE_LOGGER )
    #include "alox/alox_console_loggers.hpp"
#endif

#include <iostream>
#include <iomanip>

using namespace std;
using namespace aworx;
using namespace aworx::lox::core;

// #################################################################################################
// Static fields
// #################################################################################################
const int            Log::Version=                                            ALIB_VERSION_VERYFIER;
const int            Log::Revision=                                                               1;
const uint32_t       Log::CompilationFlags=                             ALOX_COMPATIBILITY_VERYFIER;
const uint32_t       Log::ALibCompilationFlags=                         ALIB_COMPATIBILITY_VERYFIER;
std::pair <const char*, uint32_t> Log::CompilationFlagMeanings[]=
{
    { "ALOX_DBG_LOG"            , ALOX_DBG_LOG_VFYBIT         },
    { "ALOX_DBG_LOG_CI"         , ALOX_DBG_LOG_CI_VFYBIT      },
    { "ALOX_REL_LOG"            , ALOX_REL_LOG_VFYBIT         },
    { "ALOX_REL_LOG_CI"         , ALOX_REL_LOG_CI_VFYBIT      },
};


// The lox singletons for debug and release logging
#if defined(ALOX_DBG_LOG)
    Lox  Log::defaultDbgLox;
    Lox* Log::LOX=    &Log::defaultDbgLox;
#endif

// #################################################################################################
// ALoxReportWriter
// #################################################################################################
    lib::ReportWriter*   Log::OrigReportWriter    = nullptr;
lox::ALoxReportWriter*   Log::DebugReportWriter   = nullptr;

lox::ALoxReportWriter::ALoxReportWriter ( Lox* lox )
{
    this->lox= lox;
    lox->Verbose( lox->InternalDomain, "ALoxReportWriter set" );
}

void lox::ALoxReportWriter::Report( const lib::Report::Message& report )
{
    #if defined( ALIB_DEBUG )
        lox->AcquireAndSetCI( report.File, report.Line, report.Func );

            if ( report.Type == 0 )
            {
                lox->Error   ("REPORT", report.Contents );
            }
            else
            {
                lox->Warning ("REPORT", report.Contents );
            }

        lox->Release ();
    #else
        (void) report;
    #endif
}

// #################################################################################################
// ALox library initialization
// #################################################################################################
bool            Log::isInitialized                                                      =false;
const String&   Log::ConfigCategoryName                                                 ="ALOX";

bool Log::VerifyCompilationFlags( uint32_t flags )
{
    if ( flags == Log::CompilationFlags )
        return true;

    // dump out the flags
    cout << std::left << setw(25) <<  "Symbol" << '|' << setw(5) << " Lib" <<'|' << " Comp. Unit"  <<endl;
    for( auto& p : CompilationFlagMeanings )
    {
        cout << setw(25) <<  p.first << '|' << setw(5) << (flags                  & p.second  ? " On" : " Off")
                                     << "|" << setw(5) << (ALIB::CompilationFlags & p.second  ? " On" : " Off")
             << endl;
    }

    return false;
}

void Log::checkLibraryVersions( int alibVersion, int aloxVersion, uint32_t flagsALib,  uint32_t flagsALox )
{
    if (ALIB::Version != alibVersion )
    {
        cout << "!!! Error in ALox library compilation: linked against wrong version of ALib" << endl;
        cout << "!!! ALib library version:  " << ALIB::Version << endl;
        cout << "!!! ALib included version: " << alibVersion   << endl;
        cout << "!!! Exiting with exit(-1)" << endl;
        exit(-1);
    }

    if (Log::Version != aloxVersion )
    {
        cout << "!!! Error in ALox library compilation: linked against wrong version of ALox" << endl;
        cout << "!!! ALox library version:  " << Log::Version << endl;
        cout << "!!! ALox included version: " << aloxVersion  << endl;
        cout << "!!! Exiting with exit(-1)" << endl;
        exit(-1);
    }

    // verify ALib agains ALox
    if (!ALIB::VerifyCompilationFlags( Log::ALibCompilationFlags ) )
    {
        cout << "!!! Error in ALib library compilation: linked library of ALib has different compilation symbols set." << endl;
        exit(-1);
    }

    // verify the given (actual compilation units') flags against ALib
    if (!ALIB::VerifyCompilationFlags( flagsALib ) )
    {
        cout << "!!! Error in ALib library compilation: linked library of ALib has different compilation symbols set." << endl;
        exit(-1);
    }

    // verify the given (actual compilation units') flags against ALox
    if (!Log::VerifyCompilationFlags( flagsALox ) )
    {
        cout << "!!! Error in ALox library compilation: linked library of ALox has different compilation symbols set." << endl;
        exit(-1);
    }
}

bool Log::initInternal( Inclusion environment, int argc, void** argv, bool wArgs )
{
    //---  initialize ---
    isInitialized= true;

    // initialize ALIB
    ALIB::Init( environment, argc, argv, wArgs );

    // that's it
    return true;
}

void Log::TerminationCleanUp()
{
    #if defined(ALOX_DBG_LOG)
        if ( LOX != nullptr && LOX != &defaultDbgLox )
            delete LOX;
        if ( DebugLogger != nullptr )
            delete DebugLogger;
    #endif

    ALIB::TerminationCleanUp();
}

// #################################################################################################
// Auto detection of DEBUG environment
// #################################################################################################
#if defined(ALOX_DBG_LOG)

    TextLogger*   Log::DebugLogger= nullptr;


    void Log::AddDebugLogger( Lox* lox, bool replaceDefaultReportWriter )
    {
        ALIB_ASSERT_ERROR( DebugLogger == nullptr, "Log::AddDebugLogger(): called twice." );

        // add a VStudio logger if this a VStudio debug session
        #if defined(ALIB_VSTUDIO) &&  defined(ALIB_DEBUG)
            if(      System::IsDebuggerPresent()
                 && !ALIB::Config->IsTrue( Log::ConfigCategoryName, "CL_NO_ADDITONAL_IDE_LOGGER" ))
            {
                VStudioLogger* vsl= new VStudioLogger();
                lox->AddLogger( vsl );

                // get auto sizes from last session
                String64 autoSizes;
                if ( ALIB::Config->Get( Log::ConfigCategoryName, "CL_AUTO_SIZES_IDE_LOGGER", autoSizes ) != 0 )
                    vsl->AutoSizes.Import( Substring( autoSizes ) );
            }
        #endif

        // add a default console logger
        DebugLogger= Lox::CreateConsoleLogger("DEBUG_LOGGER");
        if ( DebugLogger != nullptr )
        {
            lox->AddLogger( DebugLogger );

            // replace ALibs' ReportWriter by an ALox ReportWriter
            if ( replaceDefaultReportWriter )
                OrigReportWriter= lib::Report::GetDefault().ReplaceReportWriter( DebugReportWriter= new ALoxReportWriter( lox ), false );
            else
                DebugReportWriter= nullptr;

            // get auto sizes from last session
            String64 autoSizes;
            if( ALIB::Config->Get( Log::ConfigCategoryName, "CL_AUTO_SIZES", autoSizes ) != 0 )
                DebugLogger->AutoSizes.Import( Substring(autoSizes) );
        }
    }

    void Log::RemoveDebugLogger( Lox* lox )
    {
        // replace the report writer (if we replaced it before)
        if ( DebugReportWriter != nullptr )
        {
            lib::Report::GetDefault().ReplaceReportWriter( OrigReportWriter, false );
            delete DebugReportWriter;
            DebugReportWriter=  nullptr;
            OrigReportWriter=   nullptr;
        }

        ALIB_ASSERT_WARNING( DebugLogger != nullptr, "Log::RemoveDebugLogger(): no debug logger to remove." );

        if ( DebugLogger != nullptr )
        {
            lox->RemoveLogger( DebugLogger );

            // save auto sizes
            String64 autoSizes;
            DebugLogger->AutoSizes.Export( autoSizes );
            ALIB::Config->Save( Log::ConfigCategoryName, "CL_AUTO_SIZES", autoSizes,
                                 "Auto size values of last debug logger instance" );


            delete DebugLogger;
            DebugLogger= nullptr;
        }

        #if defined(ALIB_VSTUDIO) && defined(ALIB_DEBUG)
            TextLogger* vsl= (TextLogger*) lox->GetLogger( "VSTUDIO_CONSOLE" );
            if ( vsl != nullptr )
            {
                String64 autoSizes;
                vsl->AutoSizes.Export( autoSizes );
                ALIB::Config->Save( Log::ConfigCategoryName, "CL_AUTO_SIZES_IDE_LOGGER", autoSizes,
                                     "Auto size values of last visual studio debug logger instance" );

                lox->RemoveLogger( vsl );
                delete vsl;
            }
        #endif
    }
#endif // ALOX_DBG_LOG


// #################################################################################################
// ToString() methods for ALox public enums
// #################################################################################################

#define CASE_RETURN(enum,field)  { case enum::  field : return #field; }

    //static
    const String Log::ToString( Log::DomainLevel level )
    {
        switch( level )
        {
                        CASE_RETURN( DomainLevel, Off                      )
                        CASE_RETURN( DomainLevel, Errors                   )
                        CASE_RETURN( DomainLevel, WarningsAndErrors        )
                        CASE_RETURN( DomainLevel, InfoWarningsAndErrors    )
                        CASE_RETURN( DomainLevel, All                      )
            default:    CASE_RETURN( DomainLevel, Inherit                  )
        }
    }

    //static
    const String Log::ToString( Log::Level level )
    {
        switch( level )
        {
                        CASE_RETURN( Level, Verbose  )
                        CASE_RETURN( Level, Info     )
                        CASE_RETURN( Level, Warning  )
            default:    CASE_RETURN( Level, Error    )
        }
    }

    //static
    const String Log::ToString( Log::Scope scope )
    {
        switch( scope )
        {
                        CASE_RETURN( Scope, None         )
                        CASE_RETURN( Scope, SourceFile   )
            default:    CASE_RETURN( Scope, Method       )
        }
    }

