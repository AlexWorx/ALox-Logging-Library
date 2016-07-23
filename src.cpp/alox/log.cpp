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

#if !defined (HPP_ALIB_SYSTEM_SYSTEM)
    #include "alib/system/system.hpp"
#endif

#if !defined ( HPP_ALOX_CONSOLE_LOGGER )
    #include "alox/alox_console_loggers.hpp"
#endif

using namespace std;
namespace aworx {
    namespace lox   {

    using namespace core;

// #################################################################################################
// Static fields
// #################################################################################################
#if defined(ALOX_DBG_LOG)
    ALoxReportWriter*   Log::DebugReportWriter   = nullptr;
#endif


#if defined(_MSC_VER)
    // MSC  (as of 12/2015):
    // C4579: in-class initialization for type 'const aworx::SLiteral<10>'
    // is not yet implemented; static member will remain uninitialized at runtime but
    // use in constant-expressions is supported
    SLiteral<2>  ALox::InternalDomains {"$/" };
#else
    constexpr SLiteral<2>  ALox::InternalDomains;
#endif

// #################################################################################################
// Auto detection of DEBUG environment
// #################################################################################################
#if defined(ALOX_DBG_LOG)

    TextLogger*   Log::DebugLogger= nullptr;
    TextLogger*   Log::IDELogger  = nullptr;


    void Log::AddDebugLogger( Lox* lox )
    {
        if ( DebugLogger != nullptr )
        {
            ALIB_WARNING( "Log::AddDebugLogger(): called twice." );
            return;
        }

        // add a VStudio logger if this a VStudio debug session
        #if defined(ALIB_VSTUDIO) &&  defined(ALIB_DEBUG)
            if( System::IsDebuggerPresent() )
            {
                Variable variable( ALox::NO_IDE_LOGGER );
                if( variable.Load() == 0 || ! variable.IsTrue() )
                {
                    IDELogger= new VStudioLogger("IDE_LOGGER");

                    // add logger
                    lox->SetVerbosity( IDELogger, Verbosity::Verbose              , "/"                  );
                    lox->SetVerbosity( IDELogger, Verbosity::Warning, ALox::InternalDomains );
                }
           }
        #endif

        // add a default console logger
        DebugLogger= Lox::CreateConsoleLogger("DEBUG_LOGGER");

        // add logger
        lox->SetVerbosity( DebugLogger, Verbosity::Verbose );
        lox->SetVerbosity( DebugLogger, Verbosity::Warning, ALox::InternalDomains );

        // replace ALibs' ReportWriter by an ALox ReportWriter
        Log::AddALibReportWriter( lox );

    }

    void Log::RemoveDebugLogger( Lox* lox )
    {
        // remove ALox specific report writer of ALib
        Log::RemoveALibReportWriter();

        // remove debug logger(s)
        ALIB_ASSERT_WARNING( DebugLogger != nullptr, "Log::RemoveDebugLogger(): no debug logger to remove." );

        if ( DebugLogger != nullptr )
        {
            lox->RemoveLogger( DebugLogger );

            delete DebugLogger;
            DebugLogger= nullptr;
        }

        #if defined(ALIB_VSTUDIO) && defined(ALIB_DEBUG)
            if ( IDELogger != nullptr )
            {
                lox->RemoveLogger( IDELogger );

                delete IDELogger;
                IDELogger= nullptr;
            }
        #endif
    }

#endif // ALOX_DBG_LOG

// #################################################################################################
// ALib Report Writer installation
// #################################################################################################
#if defined(ALOX_DBG_LOG)

    void Log::AddALibReportWriter( Lox* lox )
    {
        ALIB_ASSERT_WARNING( DebugReportWriter == nullptr, "Log::AddReportWriter(): ALoxReportWriter already created." );

        // replace ALibs' ReportWriter by an ALox ReportWriter
        if ( lib::Report::GetDefault().PeekWriter() == &lib::ConsoleReportWriter::Singleton  )
            lib::Report::GetDefault().PushWriter( DebugReportWriter= new ALoxReportWriter( lox ) );
    }

    void Log::RemoveALibReportWriter()
    {
        // replace the report writer (if we replaced it before)
        if ( DebugReportWriter != nullptr )
        {
            lib::Report::GetDefault().PopWriter( DebugReportWriter );
            delete DebugReportWriter;
            DebugReportWriter=  nullptr;
        }
    }
#endif // ALOX_DBG_LOG

}}// namespace aworx::lox


