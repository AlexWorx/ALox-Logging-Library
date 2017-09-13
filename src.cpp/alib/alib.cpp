// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
#include "alib/alib.hpp"


#if !defined (HPP_ALIB_COMPATIBILITY_STD_IOSTREAM)
    #include "alib/compatibility/std_iostream.hpp"
#endif

#if ALIB_MODULE_STRINGS
    #if !defined (HPP_ALIB_STRINGS_UTIL_SPACES)
        #include "alib/strings/util/spaces.hpp"
    #endif
#endif

#if ALIB_MODULE_CONFIGURATION

    #if !defined (HPP_ALIB_CONFIG_CONFIGURATION)
        #include "alib/config/configuration.hpp"
    #endif
    #if !defined (HPP_ALIB_TIME_TICKS)
        #include "alib/time/ticks.hpp"
    #endif

    #if !defined (HPP_ALIB_SYSTEM_PROCESSINFO)
        #include "alib/system/process.hpp"
    #endif

    #if !defined (HPP_ALIB_SYSTEM_ENVIRONMENT)
        #include "alib/system/environment.hpp"
    #endif
#endif

#if ALIB_MODULE_STRINGS
    #if !defined (HPP_ALIB_STRINGS_NUMBERFORMAT)
        #include "alib/strings/numberformat.hpp"
    #endif
#endif


#if ALIB_MODULE_ALL

    #if !defined (HPP_ALIB_THREADS_SMARTLOCK)
        #include "alib/threads/smartlock.hpp"
    #endif

    #if !defined (HPP_ALIB_STRINGS_UTIL_TOKENIZER)
        #include "alib/strings/util/tokenizer.hpp"
    #endif

#endif


#if !defined (_GLIBCXX_IOSTREAM) && !defined (_IOSTREAM_ )
    #include <iostream>
#endif
#if !defined (_GLIBCXX_IOMANIP) && !defined (_IOMANIP_ )
    #include <iomanip>
#endif


#if !defined (_GLIBCXX_THREAD) && !defined (_THREAD_ )
    #include <thread>
#endif



// #################################################################################################
// namespace
// #################################################################################################
namespace aworx { namespace lib
{
// #################################################################################################
// General static fields
// #################################################################################################
bool                 ALIB::WaitForKeyPressOnTermination                                      =false;

#if ALIB_MODULE_ALL
threads::SmartLock   ALIB::StdOutputStreamsLock;
#endif

// #################################################################################################
// Compilation verification
// #################################################################################################
const uint64_t       ALIB::CompilationFlags=                            ALIB_COMPATIBILITY_VERIFYER;
const int            ALIB::Version=                                           ALIB_VERSION_VERYFIER;
const int            ALIB::Revision=                                                              0;


bool                 ALIB::initialized                                                       =false;

std::pair <const char*, uint64_t> ALIB::CompilationFlagMeanings[9]=
{
    { "ALIB_DEBUG"                  , ALIB_DEBUG_VFYBIT                     },
    { "ALIB_DEBUG_STRINGS"          , ALIB_DEBUG_STRINGS_VFYBIT             },

    { "ALIB_FEAT_THREADS"           , ALIB_FEAT_THREADS_VFYBIT              },
    { "ALIB_FEAT_SINGLETON_MAPPED"  , ALIB_FEAT_SINGLETON_MAPPED_VFYBIT     },
    { "ALIB_FEAT_BOXING_FTYPES"     , ALIB_FEAT_BOXING_FTYPES_VFYBIT        },
    { "ALIB_FEAT_BOXING_STD_VECTOR" , ALIB_FEAT_BOXING_STD_VECTOR_VFYBIT    },

    { "ALIB_MODULE_ALL"             , ALIB_MODULE_ALL_VFYBIT                },
    { "ALIB_MODULE_STRINGS"         , ALIB_MODULE_STRINGS_VFYBIT            },
    { "ALIB_MODULE_BOXING"          , ALIB_MODULE_BOXING_VFYBIT             },
};


bool ALIB::VerifyCompilationFlags( uint64_t flags )
{
    // verify the flags
    if ( flags == ALIB::CompilationFlags )
        return true;

    // dump out the flags
    std::cout << std::left << std::setw(30) <<  "Symbol" << '|' << std::setw(5) << " Lib" <<'|' << " Comp. Unit"  << std::endl;

    int cnt= 0;
    for( auto& p : CompilationFlagMeanings )
    {
        cnt++;
        std::cout << std::setw(30) <<  p.first << '|' << std::setw(5) << (ALIB::CompilationFlags & p.second  ? " On" : " Off")
                                                << "|" << std::setw(5) << (flags                  & p.second  ? " On" : " Off")
                  << std::endl;
    }

    return false;
}

// #################################################################################################
// Replacement method for ALib Essential Reports
// #################################################################################################
#if ALIB_MODULE_ALL &&  ALIB_DEBUG
    namespace debug {
    /**
     * This method is installed with
     * \ref aworx::lib::debug::DbgSimpleALibMsg_Plugin in method
     * \ref aworx::lib::ALIB::Init "ALIB::Init".
     *
     * The message strings are simply passed to the default
     * \ref aworx::lib::lang::Report "Report".
     * This way, the essential assert, error and message macros are using the \b %ALib report system
     * in the moment that the complete %ALib library is in place (instead of only one of the
     * libraries' modules.
     *
     * @param file    Information about the scope of invocation.
     * @param line    Information about the scope of invocation.
     * @param method  Information about the scope of invocation.
     * @param type    The type of message. See \ref aworx::lib::lang::Report::Message "Report::Message".
     * @param qtyMsgs The number of messages in \p msgs.
     * @param msgs    A list of strings (this is all that the essential versions of \b %ALib reporting
     *                macros provide).
     */
    void ALib_Dbg_Report_Plugin(const char* file, int line, const char* method, int type, int qtyMsgs, const char** msgs);
    void ALib_Dbg_Report_Plugin(const char* file, int line, const char* method, int type, int qtyMsgs, const char** msgs)
    {
        lang::Report::Message message( file,line,method, type, msgs[0] );
        for (int i= 1; i< qtyMsgs; ++i )
            message.Add( msgs[i] );
        lang::Report::GetDefault().DoReport( message );
    }
    } // namespace aworx::lib[::debug]
#endif



// #################################################################################################
// Configuration variable definitions
// #################################################################################################
#if ALIB_MODULE_CONFIGURATION

    String               ALIB::ConfigCategoryName                                           ="ALIB";

    config::VariableDefinition ALIB::RTE =
    {
        &ALIB::ConfigCategoryName,   nullptr,     "RTE",
        "auto",
        '\0', nullptr, Variable::FormatHint_None,
        "Defines runtime environment. Defaults to 'auto' which enables detection. Other"        "\n"
        "allowed values are: eclipse, " "qtcreator, " "vstudio, " "shell, " "desktop, " "device, "
    };

    config::VariableDefinition ALIB::LOCALE =
    {
        &ALIB::ConfigCategoryName,   nullptr,     "LOCALE",
        "",
        '\0', nullptr, Variable::FormatHint_None,
        "Defines the locale of the application. If empty or not set, the systems' locale is used."
    };

    config::VariableDefinition ALIB::WAIT_FOR_KEY_PRESS =
    {
        &ALIB::ConfigCategoryName,   nullptr,     "WAIT_FOR_KEY_PRESS",
        "",
        '\0', nullptr, Variable::FormatHint_None,
        "If true, the process waits for a key stroke on termination. If empty, under Windows"   "\n"
        "behavior is detected, under other OSes, defaults to false."
    };

    config::VariableDefinition ALIB::HAS_CONSOLE_WINDOW =
    {
        &ALIB::ConfigCategoryName,   nullptr,     "HAS_CONSOLE_WINDOW",
        "",
        '\0', nullptr, Variable::FormatHint_None,
        "Boolean value that denotes what its name indicates. If empty, under Windows value is " "\n"
        "detected, under other OSes, defaults to true."
    };
#endif

// #################################################################################################
// Environment definition/detection
// #################################################################################################

#if ALIB_MODULE_ALL

    #if defined(__unix__) || defined(__APPLE__)
        String      ALIB::DebuggerProcessNames= "gdb|debugserver";
    #endif

    bool ALIB::IsDebuggerPresent()
    {
    #if defined(__unix__) || defined(__APPLE__)

        // Unix: search debugger process in parent processes
        const ProcessInfo& pi= ProcessInfo::Current();
        uinteger parentPID= pi.PPID;
        if ( parentPID == 0 )
            return false;

        ProcessInfo actPI( parentPID );
        Tokenizer tknzr( DebuggerProcessNames, '|' );
        while(tknzr.HasNext() )
        {
            Substring& debuggerName= tknzr.Next();
            if (actPI.Name.StartsWith( debuggerName ) )
                return true;
        }
        return false;

    #elif defined(_WIN32)

         return (bool) ( ::IsDebuggerPresent() != 0 ) ;

    #else
         #pragma message ("Unknown Platform in file: " __FILE__ )
         return false;
    #endif
    }

#endif // ALIB_MODULE_ALL

#if ALIB_MODULE_CONFIGURATION
    bool ALIB::HasConsoleWindow()
    {
        // read configuration
        bool returnValue;
        Variable variable( ALIB::HAS_CONSOLE_WINDOW );
        Configuration::Default.Load( variable );
        if ( variable.Size() > 0  && variable.GetString()->Length() > 0 )
            returnValue=  variable.IsTrue();
        else

        #if defined(_WIN32)
            // determine if we have a console window
            returnValue= GetConsoleWindow() != NULL;
        #else
            returnValue= true;
        #endif
        return returnValue;
    }
#endif // ALIB_MODULE_CONFIGURATION



// #################################################################################################
// Init/ TerminationCleanUp()
// #################################################################################################

void ALIB::Init( int argc, char    **argv )
{
    #if ALIB_MODULE_CONFIGURATION
        Configuration::Default.SetCommandLineArgs( argc, argv );
    #endif
    init();
}

void ALIB::Init( int argc, wchar_t **argv )
{
    #if ALIB_MODULE_CONFIGURATION
        Configuration::Default.SetCommandLineArgs( argc, argv );
    #endif
    init();
}


void ALIB::init()
{
    // check for double initialization (this is explicitly allowed, see docs)
    if ( initialized )
        return;

    //############### initialize threads and time ################
    #if ALIB_MODULE_CONFIGURATION
        aworx::lib::threads::Init();
        aworx::lib::time::Init();
    #endif

    //############### create singletons ###############
    #if ALIB_MODULE_ALL &&  ALIB_DEBUG
        debug::DbgSimpleALibMsg_Plugin= debug::ALib_Dbg_Report_Plugin;
    #endif


    initialized= true;

//! [DOX_ALIB_BOXING_BOOTSTRAP]
//############### Initialize boxing ###############
#if ALIB_MODULE_BOXING
    aworx::lib::boxing::Init();
#endif
#if ALIB_MODULE_STRINGS
    aworx::lib::strings::Init();
#endif
#if ALIB_MODULE_CONFIGURATION
    aworx::lib::time::InitBoxing();
#endif
//! [DOX_ALIB_BOXING_BOOTSTRAP]

    #if ALIB_MODULE_CONFIGURATION
        Variable variable;
    #endif

    //############### set locale ###############
    #if ALIB_MODULE_CONFIGURATION && ( defined (__GLIBCXX__)  || defined(__APPLE__) )
    {
        int receivedFrom= 0;
        variable.Define( ALIB::LOCALE );
        AString locale;
        if (     variable.Load() != 0
             &&  variable.GetString()->IsNotEmpty()        )
        {
            receivedFrom= 1;
            locale._( variable.GetString() );
        }
        else if ( system::GetEnvironmentVariable( "LANG"      ,locale ) )        receivedFrom= 2;
        else if ( system::GetEnvironmentVariable( "LANGUAGE"  ,locale ) )        receivedFrom= 3;

        if( receivedFrom > 0 && !locale.Equals( "none", Case::Ignore ) )
        {
            if( !setlocale(LC_ALL, locale.ToCString() ) )
            {
                String256 msg( "ALib Error: setlocale(\""); msg << locale <<"\") failed. Setting read from ";
                msg << (   receivedFrom == 1 ? "config variable 'LOCALE'"        :
                           receivedFrom == 2 ? "environment variable 'LANG'"     :
                           receivedFrom == 3 ? "environment variable 'LANGUAGE'" : "ERROR"  );

                std::cerr.write( msg.Buffer(), msg.Length() );

                std::cerr << ". Trying  'setlocale(LC_ALL, \"\")': ";
                if ( setlocale(LC_ALL, ""  ) )
                    std::cerr << " success.";
                else
                {
                    std::cerr << "failed. Trying  'setlocale(LC_ALL, \"C\")': ";
                    if ( setlocale(LC_ALL, "C" ) )
                        std::cerr << " success.";
                    else
                        std::cerr << std::endl << "     Panic: No standard locale setting was successful!";
                }
                std::cerr << std::endl;
            }
        }
    }
    #endif

    // set the system's locale as the default for our static default number format
    #if ALIB_MODULE_STRINGS
        strings::NumberFormat::Global.SetFromLocale();
        strings::NumberFormat::Global.WriteGroupChars= true;
    #endif


    // --- determine if we want to wait for a keypress upon termination ---
    {
        #if ALIB_MODULE_CONFIGURATION
            variable.Define( ALIB::WAIT_FOR_KEY_PRESS );
            Configuration::Default.Load( variable );
            if ( variable.Size() > 0 )
                WaitForKeyPressOnTermination= variable.IsTrue();
            else
            {
                #if defined(_WIN32) && ALIB_DEBUG
                    WaitForKeyPressOnTermination=  ALIB::HasConsoleWindow() && ALIB::IsDebuggerPresent();
                #else
                    WaitForKeyPressOnTermination=  false;
                #endif
            }
        #else
                #if defined(_WIN32) && ALIB_DEBUG
                    WaitForKeyPressOnTermination=  ALIB::HasConsoleWindow() && ALIB::IsDebuggerPresent();
                #else
                    WaitForKeyPressOnTermination=  false;
                #endif
        #endif
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

        std::cout << std::endl << "ALIB: Press 'Enter' to exit... " \
            "      (To disable this, set 'ALIB::WaitForKeyPressOnTermination to 'false'.)" << std::endl;
        while ( getchar() != '\n' )
            ;
    }

    // terminate subcomponents
    #if ALIB_MODULE_CONFIGURATION
        aworx::lib::time::TerminationCleanUp();
        aworx::lib::threads::TerminationCleanUp();
    #endif

    #if ALIB_MODULE_ALL && ALIB_DEBUG
        lang::Report::TerminationCleanUp();
    #endif

    #if ALIB_MODULE_STRINGS
        aworx::lib::strings::TerminationCleanUp();
    #endif

    #if ALIB_MODULE_BOXING
        aworx::lib::boxing::TerminationCleanUp();
    #endif

    // remove singletons
    lang::DeleteSingletons();

}


// #################################################################################################
// SleepX methods
// #################################################################################################

// usleep() (for _WIN32)
#if !ALIB_FEAT_THREADS
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

void ALIB::SleepMillis( int milliseconds )
{
    #if ALIB_FEAT_THREADS
        std::this_thread::sleep_for( std::chrono::milliseconds( milliseconds ) );
    #else
        usleep( milliseconds * 1000 );
    #endif
}

void ALIB::SleepMicros( int microseconds )
{
    #if ALIB_FEAT_THREADS
        std::this_thread::sleep_for( std::chrono::microseconds( microseconds ) );
    #else
        usleep( microseconds );
    #endif
}

void ALIB::SleepNanos( int nanoseconds )
{
    #if ALIB_FEAT_THREADS
        std::this_thread::sleep_for( std::chrono::nanoseconds( nanoseconds ) );
    #else
        int micros= nanoseconds / 1000;
        usleep( micros > 0 ? micros : 1 );
    #endif
}

#if ALIB_MODULE_CONFIGURATION
    void ALIB::Sleep( const time::Ticks& ticks )
    {
         ALIB::SleepNanos( static_cast<int>( ticks.InNanos() ) );
    }
#endif

// #################################################################################################
//  String helpers
// #################################################################################################

#if ALIB_MODULE_BOXING || ALIB_MODULE_STRINGS
    #if defined(__WCHAR_MAX__)  && ( __WCHAR_MAX__ > 0x10000 )
        size_t   ALIB::strlen16( const char16_t* s )
        {
            static_assert( sizeof(wchar_t) == sizeof( char32_t ), "Error: Platform not supported" );
            if ( s == nullptr ) return 0;
            const char16_t* p= s;
            while(*p != 0 )
                p++;
            return static_cast<size_t>( p - s );
        }
    #else
        size_t   ALIB::strlen32( const char32_t* s )
        {
            static_assert( sizeof(wchar_t) == sizeof( char16_t ), "Error: Platform not supported" );

            if ( s == nullptr ) return 0;
            const char32_t* p= s;
            while(*p != 0 )
                p++;
            return static_cast<size_t>( p - s );
        }
    #endif
#endif

}}// namespace aworx::lib

