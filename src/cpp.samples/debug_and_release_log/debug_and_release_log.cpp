// #################################################################################################
//  aworx::util - Unit Tests
//  Private, not published in git ( I hope! )
//  (c) 2013-2015 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################


#include "alox.hpp"
#include "alox_console_logger.hpp"
#include "alox_memory_logger.hpp"

#include <iostream>


using namespace std;
using namespace aworx::util;
using namespace aworx::lox;
using namespace aworx::lox::loggers;


void helloWorldDebugLog()
{
    cout << "cout: Do some debug logging:" <<  endl;

    Log_Prune( ConsoleLogger myConsoleLogger; )

    // prevent the cut of the source path if run in VSTUDIO
    #if defined(AWXU_DEBUG) && defined(AWORX_VSTUDIO) && defined(ALOX_DBG_LOG)
        myConsoleLogger.LineFormatter->ConsumableSourcePathPrefix= "";
    #endif
    Log_AddLogger( &myConsoleLogger );


    Log_SetDomain( "SIMPLE", Log::DomainLevel::INFO_WARNINGS_AND_ERRORS );
    Log_InfoD( "SIMPLE", "Hello ALox, this is debug logging" );
    Log_InfoD( "SIMPLE", "I hope within your ide, you can doubleclick this line?" );
    Log_RemoveLoggers( nullptr );


    #if !defined(ALOX_DBG_LOG)
        cout << "cout: should not have logged something (this is the release version)" <<  endl;
    #endif

    cout <<  endl;
}


void helloWorldReleaseLog()
{
    cout << "cout: Do some release logging:" <<  endl;


    #undef  ALOX_REL_LOX_INSTANCE
    #define ALOX_REL_LOX_INSTANCE   lox.
    Lox_Prune( Lox lox; )

    Lox_Prune( ConsoleLogger myConsoleLogger; )

    // if makefile did not specify caller info for release logging (which is standard behaviour),
    // we remove the caller info from the format string
    #ifndef ALOX_REL_LOG_CI
        Lox_Prune( myConsoleLogger.LineFormatter->Format= "[%TE +%TI] [%t] %L [%O]: "; )
    #endif

    Lox_AddLogger( &myConsoleLogger );
    Lox_SetDomain( "SIMPLE", Log::DomainLevel::INFO_WARNINGS_AND_ERRORS );
    Lox_InfoD( "SIMPLE", "Hello ALox, this is release logging" );
    Lox_RemoveLoggers( nullptr );


    #if !defined(ALOX_REL_LOG)
        cout << "cout: should not have logged something (release logging was disabled, obviously ALOX_REL_LOG_OFF was passed to the compiler)" <<  endl;
    #endif
    cout <<  endl;
}

int main()
{
    helloWorldDebugLog();
    helloWorldReleaseLog();

    // cleanup resources to make Valgrind happy
    Log::TerminationCleanUp();
    return 0;
}
