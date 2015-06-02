// #################################################################################################
//  aworx::util - Classes we need
//
//  (c) 2013-2015 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
#include "stdafx_awxu.h"

#if !defined (HPP_AWORX_UTIL_AWXU)
    #include "awxu.hpp"
#endif

#if !defined (HPP_AWORX_UTIL_THREADLOCK)
    #include "threadlock.hpp"
#endif

#if !defined (HPP_AWORX_UTIL_TICKS)
    #include "ticks.hpp"
#endif

#if !defined(_GLIBCXX_IOSTREAM) && !defined(_IOSTREAM_)
    #include <iostream>
#endif


// #################################################################################################
// usleep() (for WIN32)
// #################################################################################################
#if !defined (AWXU_FEAT_THREADS)
    #if defined( __GNUC__ )
        #include <unistd.h>
    #elif defined ( _MSC_VER )
        void usleep(__int64 usec)
        {
            HANDLE timer;
            LARGE_INTEGER ft;

            ft.QuadPart = -(10*usec); // Convert to 100 nanosecond interval, negative value indicates relative time

            timer = CreateWaitableTimer(NULL, TRUE, NULL);
            SetWaitableTimer(timer, &ft, 0, NULL, NULL, 0);
            WaitForSingleObject(timer, INFINITE);
            CloseHandle(timer);
        }
    #else
        #pragma message ("Uknown Platform in file: " __FILE__ )
    #endif
#endif


using namespace std;

namespace aworx {
namespace       util {


// #################################################################################################
// class ConsoleErrorHandler
// #################################################################################################

void ConsoleErrorHandler::Error   ( const char* msg ) { cerr << "AWXU Error: " << msg << endl; }
void ConsoleErrorHandler::Warning ( const char* msg ) { cout << "AWXU Warng: " << msg << endl; }
void ConsoleErrorHandler::DebugMsg( const char* msg ) { cout << "AWXU Debug: " << msg << endl; }


// #################################################################################################
// local globals
// #################################################################################################


int                   AWXU::isInitialized=    0;
ConsoleErrorHandler   AWXU::defaultErrorHandler;
AWXUErrorHandler*     AWXU::errorHandler;
ThreadLock            AWXU::tlock;

#if defined(AWXU_DEBUG)
    bool              AWXU::HaltOnError=      true;
    bool              AWXU::HaltOnWarning=    false;
#else
    bool              AWXU::HaltOnError=      false;
    bool              AWXU::HaltOnWarning=    false;
#endif

// #################################################################################################
// TerminationCleanUp()
// #################################################################################################

void AWXU::Init()
{
    // check for double initialization (this is explicitly allowed, see docs)
    if ( isInitialized != 0 )
        return;
    isInitialized= 1;

    // do our own startup initialization
    errorHandler=   &defaultErrorHandler;

    // invoke initialization methods of sub components
    #ifdef AWXU_FEAT_THREADS
        Thread::_awxu_init_lib_thread();
    #endif
    Ticks:: _awxu_init_lib_ticks();

    isInitialized= 2;
}

void AWXU::TerminationCleanUp()
{
    #ifdef AWXU_FEAT_THREADS
        Thread::_awxu_destruct_lib_thread();
    #endif
    Ticks:: _awxu_destruct_lib_ticks();
}

// #################################################################################################
// class AWXUErrorHandler
// #################################################################################################
bool AWXU::AcquireErrorHandler()
{
    if ( isInitialized == 2 )
    {
        tlock.Acquire();
            if ( errorHandler != nullptr )
                return true; // keep lock acquired!
        tlock.Release();
    }
    return false;
}

void AWXU::Error( const char* msg )
{
        if ( !tlock.IsAcquired() ) errorHandler->Error( AString256( "Error handler not acquired. Original Message: ").Append(msg).Buffer() );
        errorHandler->Error( msg );
    tlock.Release();
    if ( tlock.IsAcquired() )      errorHandler->Error( AString256( "Error handler acquired multiple times. Original Message: ").Append(msg).Buffer() );

    assert( !AWXU::HaltOnError ); // must not use AWXU_ASSERT because of recursion
}

void AWXU::Warning( const char* msg )
{
        if ( !tlock.IsAcquired() ) errorHandler->Error( AString256( "Error handler not acquired. Original Message: ").Append(msg).Buffer() );
        errorHandler->Warning( msg );
    tlock.Release();
    if ( tlock.IsAcquired() )      errorHandler->Error( AString256( "Error handler acquired multiple times. Original Message: ").Append(msg).Buffer() );
    assert( !AWXU::HaltOnWarning ); // must not use AWXU_ASSERT because of recursion
}

void AWXU::DebugMsg( const char* msg )
{
        if ( !tlock.IsAcquired() ) errorHandler->Error( AString256( "Error handler not acquired. Original Message: ").Append(msg).Buffer() );
        errorHandler->DebugMsg( msg );
    tlock.Release();
    if ( tlock.IsAcquired() )      errorHandler->Error( AString256( "Error handler acquired multiple times. Original Message: ").Append(msg).Buffer() );
    assert( !AWXU::HaltOnWarning ); // must not use AWXU_ASSERT because of recursion
}

void AWXU::AbortErrorHandler()
{
        if ( !tlock.IsAcquired() )  errorHandler->Error( "Error handler not acquired before invoking AWXU::AbortErrorHandler().");
    tlock.Release();
    if ( tlock.IsAcquired() )       errorHandler->Error( "Error handler acquired multiple times before invoking AWXU::AbortErrorHandler()." );
    assert( !AWXU::HaltOnError );
}

AWXUErrorHandler* AWXU::ReplaceErrorHandler( AWXUErrorHandler* newErrorHandler )
{
    tlock.Acquire();
        AWXUErrorHandler* oldEH=    errorHandler;
        errorHandler=                newErrorHandler;
    tlock.Release();
    return oldEH;
}

// #################################################################################################
// class AWX
// #################################################################################################

void AWXU::SleepMillis( int millisecs )
{
    #ifdef AWXU_FEAT_THREADS
        std::this_thread::sleep_for( std::chrono::milliseconds( millisecs ) );
    #else
        usleep( millisecs * 1000 );
    #endif
}

void AWXU::SleepMicros( int microsecs )
{
    #ifdef AWXU_FEAT_THREADS
        std::this_thread::sleep_for( std::chrono::microseconds( microsecs ) );
    #else
        usleep( microsecs );
    #endif
}

void AWXU::SleepNanos( int nanosecs )
{
    #ifdef AWXU_FEAT_THREADS
        std::this_thread::sleep_for( std::chrono::nanoseconds( nanosecs ) );
    #else
        int micros= nanosecs / 1000;
        usleep( micros > 0 ? micros : 1 );
    #endif
}



}}// namespace aworx::util

