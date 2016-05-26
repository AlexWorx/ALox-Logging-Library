// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
#include "alib/stdafx_alib.h"

#if !defined (HPP_ALIB)
    #include "alib/alib.hpp"
#endif

#include "alib/time/ticks.hpp"
#include "alib/config/configuration.hpp"
#include "alib/system/process.hpp"
#include "alib/system/system.hpp"
#include "alib/compatibility/std_iostream.hpp"
#include "alib/core/util.hpp"

#include <iostream>
#include <iomanip>

using namespace std;

namespace aworx {
namespace           lib {


// #################################################################################################
// static fields
// #################################################################################################
const uint32_t       ALIB::CompilationFlags=                            ALIB_COMPATIBILITY_VERYFIER;
const int            ALIB::Version=                                     ALIB_VERSION_VERYFIER;
const int            ALIB::Revision=                                    1;


bool                 ALIB::initialized                                                     =false;
#if defined(_MSC_VER)
    #pragma warning( push )
    #pragma warning( disable : 4592 )
#endif
String               ALIB::ConfigCategoryName                                              ="ALIB";
#if defined(_MSC_VER)
    #pragma warning( pop )
#endif
Configuration        ALIB::Config;

bool                 ALIB::WaitForKeyPressOnTermination                                    =false;
ThreadLockNR         ALIB::Lock;

SmartLock            ALIB::StdOutputStreamsLock;


std::pair <const char*, uint32_t> ALIB::CompilationFlagMeanings[]=
{
    { "ALIB_DEBUG"                , ALIB_DEBUG_VFYBIT         },    // critical
    { "ALIB_FEAT_THREADS"         , ALIB_FEAT_THREADS_VFYBIT  },
    { "ALIB_DEBUG_STRINGS"        , ALIB_DEBUG_STRINGS_VFYBIT },

    { "ALIB_GTEST"                , ALIB_GTEST_VFYBIT         },    // non critical
    { "ALIB_QTCREATOR"            , ALIB_QTCREATOR_VFYBIT     },
    { "ALIB_ECLIPSE"              , ALIB_ECLIPSE_CDT_VFYBIT   },
    { "ALIB_VSTUDIO"              , ALIB_VSTUDIO_VFYBIT       },

};


bool ALIB::VerifyCompilationFlags( uint32_t flags )
{
    // we verify only the lower 16 bit part of the flags. Higher flags don't make the library
    // binary incompatible
    if ( (flags & 0xFF) == ( ALIB::CompilationFlags  & 0xFF) )
        return true;

    // dump out the flags
    cout << std::left << setw(25) <<  "Symbol" << '|' << setw(5) << " Lib" <<'|' << " Comp. Unit"  <<endl;

    int cnt= 0;
    for( auto& p : CompilationFlagMeanings )
    {
        cnt++;
        cout << setw(25) <<  p.first << '|' << setw(5) << (flags                  & p.second  ? " On" : " Off")
                                     << "|" << setw(5) << (ALIB::CompilationFlags & p.second  ? " On" : " Off")
             << ( cnt > 3 ? "  (not critical)" : "" )
             << endl;
    }

    return false;
}

// #################################################################################################
// Init/ TerminationCleanUp()
// #################################################################################################

void ALIB::Init( Inclusion environment, int argc, void **argv, bool wArgs )
{
    // check for double initialization (this is explicitly allowed, see docs)
    if ( initialized )
        return;

    //############### initialize threads and time ################
    Thread::_Init_ALib();
    Ticks ::_Init_ALib();

    //############### create singletons ###############
    Report::GetDefault();
    Config.AddStandardPlugIns( environment, argc, argv, wArgs );

    initialized= true;

    //############### set locale ###############
    #if defined (__GLIBCXX__)
    {
        String64  locale;
        int receivedFrom= 0;
             if ( Config.Get( ConfigCategoryName, "LOCALE"    ,locale ) != 0 )        receivedFrom= 1;
        else if ( System::GetVariable(             "LANG"      ,locale )      )        receivedFrom= 2;
        else if ( System::GetVariable(             "LANGUAGE"  ,locale )      )        receivedFrom= 3;

        if( receivedFrom > 0 && !locale.Equals( "none", Case::Ignore ) )
        {
            if( !setlocale(LC_ALL, locale.ToCString() ) )
            {
                String256 msg( "ALib Error: setlocale(\""); msg << locale <<"\") failed. Setting read from ";
                msg << (   receivedFrom == 1 ? "config variable 'LOCALE'"        :
                           receivedFrom == 2 ? "environment variable 'LANG'"     :
                           receivedFrom == 3 ? "environment variable 'LANGUAGE'" : "ERROR"  );

                cerr.write( msg.Buffer(), msg.Length() );

                cerr << ". Trying  'setlocale(LC_ALL, \"\")': ";
                if ( setlocale(LC_ALL, ""  ) )
                    cerr << " success.";
                else
                {
                    cerr << "failed. Trying  'setlocale(LC_ALL, \"C\")': ";
                    if ( setlocale(LC_ALL, "C" ) )
                        cerr << " success.";
                    else
                        cerr << endl << "     Panic: No standard locale setting was successful!";
                }
                cerr << endl;
            }
        }
    }
    #endif

    // set the system's locale as the default for our static default number format
    strings::NumberFormat::Global.SetFromLocale();


    // --- determine if we want to wait for a keypress upon termination ---
    {
        // read configuration
        int found;
        bool configValue=   Config.IsTrue( ALIB::ConfigCategoryName, "WAIT_FOR_KEY_PRESS_ON_TERMINATION", &found );
        if ( found != 0 )
            WaitForKeyPressOnTermination= configValue;
        else
        {
            #if defined(ALIB_VSTUDIO) && defined(ALIB_DEBUG)

                WaitForKeyPressOnTermination=  System::HasConsoleWindow() && System::IsDebuggerPresent();

            #else

                WaitForKeyPressOnTermination=  false;

            #endif
        }
    }
}

void ALIB::TerminationCleanUp()
{
    if ( ALIB::WaitForKeyPressOnTermination )
    {
        #if defined(_WIN32)
            OutputDebugStringA( "\r\nALIB: Waiting for 'Enter' key in the console window." \
                                "\r\n     (To disable this, set 'ALIB::WaitForKeyPressOnTermination' to 'false'.)\r\n" );
        #endif

        cout << endl << "ALIB: Press 'Enter' to exit... " \
            "      (To disable this, set 'ALIB::WaitForKeyPressOnTermination to 'false'.)" << endl;
        while ( getchar() != '\n' )
            ;
    }

    // remove singletons
    delete &Report::GetDefault();

    // terminate subcomponents
    Ticks ::_Terminate_ALib();
    Thread::_Terminate_ALib();
}


// #################################################################################################
// SleepX methods
// #################################################################################################

// usleep() (for _WIN32)
#if !defined (ALIB_FEAT_THREADS)
    #if defined( __GLIBCXX__ )
        #include <unistd.h>
    #elif defined ( _WIN32 )
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
        #pragma message ("Unknown Platform in file: " __FILE__ )
    #endif
#endif

void ALIB::SleepMillis( int millisecs )
{
    #ifdef ALIB_FEAT_THREADS
        std::this_thread::sleep_for( std::chrono::milliseconds( millisecs ) );
    #else
        usleep( millisecs * 1000 );
    #endif
}

void ALIB::SleepMicros( int microsecs )
{
    #ifdef ALIB_FEAT_THREADS
        std::this_thread::sleep_for( std::chrono::microseconds( microsecs ) );
    #else
        usleep( microsecs );
    #endif
}

void ALIB::SleepNanos( int nanosecs )
{
    #ifdef ALIB_FEAT_THREADS
        std::this_thread::sleep_for( std::chrono::nanoseconds( nanosecs ) );
    #else
        int micros= nanosecs / 1000;
        usleep( micros > 0 ? micros : 1 );
    #endif
}


}}// namespace aworx::lib

