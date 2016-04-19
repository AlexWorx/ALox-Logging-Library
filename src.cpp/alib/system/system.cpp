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

#include "alib/config/configuration.hpp"
#include "alib/system/process.hpp"
#include "alib/system/system.hpp"



#if defined (__GLIBCXX__)
    #include <unistd.h>
#elif   defined( _WIN32 )
    #include <direct.h>
#else
    #pragma message ("Unknown Platform in file: " __FILE__ )
#endif

using namespace std;

namespace aworx {
namespace           lib {
namespace                    system {


// #################################################################################################
// static fields
// #################################################################################################
#if defined(__unix__)
    String      System::DebuggerProcessName= "gdb";
#endif

AString         System::processName;

// #################################################################################################
// TerminationCleanUp()
// #################################################################################################

bool System::HasConsoleWindow()
{
    // read configuration
    {
        int found= false;
        bool configValue=   ALIB::Config.IsTrue( ALIB::ConfigCategoryName, "HAS_CONSOLE_WINDOW", &found );
        if ( found != 0 )
            return configValue;
    }

    #if defined(_WIN32)
    {
        // determine if we have a console window
        return GetConsoleWindow() != NULL;
    }
    #else
        return true;
    #endif
}

bool System::IsDebuggerPresent()
{
#if defined(__unix__)

    // Unix: search debugger process in parent processes
    const ProcessInfo& pi= ProcessInfo::Current();
    String16 actPID= pi.PPID;
    while ( actPID.IsNotEmpty() )
    {
        ProcessInfo actPI( actPID );
        if (actPI.ExecName.Equals( DebuggerProcessName ) )
            return true;
        actPID= actPI.PPID;
    }
    return false;

#elif defined(_WIN32)

     return (bool) ( ::IsDebuggerPresent() != 0 ) ;

#else
     #pragma message ("Unknown Platform in file: " __FILE__ )
     return false;
#endif
}

System::RuntimeEnvironment   System::RTE()
{
    RuntimeEnvironment RTE= RuntimeEnvironment::Unknown;

    // lets allow the config system to overwrite the RTE
    {
        String128 convRTE;
        ALIB::Config.Get( ALIB::ConfigCategoryName, "RTE", convRTE );
        if ( convRTE.IsNotEmpty() && !convRTE.Equals( "auto", Case::Ignore ))
        {
            std::pair<String, RuntimeEnvironment> values[]=
            {
                { "none",          RuntimeEnvironment::Unknown        },
                { "eclipse",       RuntimeEnvironment::EclipseCDT     },
                { "qtcreator",     RuntimeEnvironment::QTCreator      },
                { "vstudio",       RuntimeEnvironment::VStudio        },
                { "shell",         RuntimeEnvironment::Shell          },
                { "desktop",       RuntimeEnvironment::Desktop        },
                { "device",        RuntimeEnvironment::MobileDevice   },

                { nullptr,         RuntimeEnvironment::Unknown        },
            };

            for(std::pair<String, RuntimeEnvironment> *v= values; v->first != nullptr ; v++)
                if( convRTE.Equals( v->first, Case::Ignore ) )
                    return v->second;

            ALIB_WARNING_S512(    "Unknown value specified in variable "
                             << ALIB::ConfigCategoryName << "_RTE: \""  << convRTE << '\"' )
        }
    }

    // not set by config? make your own guess

    // unix: search known environmental process in parent list
    #if defined(__unix__)

    std::pair<String, RuntimeEnvironment> values[]=
    {
        { "eclipse",       RuntimeEnvironment::EclipseCDT   },
        { "qtcreator",     RuntimeEnvironment::QTCreator    },
        { "#bash#",        RuntimeEnvironment::Shell        },
        { "#sh#",          RuntimeEnvironment::Shell        },
        { "#ksh#",         RuntimeEnvironment::Shell        },

        // stopper object
        { nullptr,         RuntimeEnvironment::Unknown      },
    };

    const ProcessInfo& pi= ProcessInfo::Current();
    String16 actPID= pi.PPID;
    while ( actPID.IsNotEmpty())
    {
        ProcessInfo actPI( actPID );
        if (actPI.ExecName.IsEmpty() )
            break;
        for(std::pair<String, RuntimeEnvironment> *v= values; v->first != nullptr ; v++)
            if( actPI.ExecName.IndexOf<false>( v->first, 0, Case::Ignore ) >= 0 )
                return  v->second;
        actPID= actPI.PPID;
    }

    #elif defined( _WIN32 )
        // Potential future work: More analytics to add, e.g. check process parent
        if ( RTE == System::RuntimeEnvironment::Unknown )
            RTE= System::HasConsoleWindow() ? System::RuntimeEnvironment::Shell
                                            : System::RuntimeEnvironment::Desktop;
    #endif

    return RTE;
}


bool System::GetVariable( const TString&  name,
                          AString&        target,
                          CurrentData     targetData,
                          Case            sensitivity )
{
    if ( targetData == CurrentData::Clear )
        target.Clear();

    if ( name.IsEmpty() )
        return false;

    #if defined (_WIN32)
        (void) sensitivity;
        ALIB_ASSERT_WARNING( sensitivity == Case::Ignore,
           "Windows OS does not support case sensitive environment variables" );

        char *env;
        errno_t err = _dupenv_s( &env, nullptr, name.ToCString() );
        if ( err  || env == nullptr )
            return false;

        target._( env );
        free( env );
        return false;

    #else
        // case sensitive is easy (but not supported under Windows)
        if ( sensitivity == Case::Sensitive )
        {
            char* env= getenv( name.ToCString() );
            if( env != nullptr )
                target._( env );
            return true;
        }

        // read directly from the global 'environ' variable, to enable case insensitive access
        char** envv=   environ;
        while ( *envv )
        {
            const char* actVar=   *envv;
            if (     0 == lib::strings::CString::strncasecmp( name.Buffer(), actVar, name.Length() )
                 &&  *(actVar + name.Length()) == '='
               )
            {
                actVar+= name.Length() + 1;
                target._( actVar );
                    break;
            }

            envv++;
        }

        return true;
    #endif
}

void System::getProcessName()
{
    // Own global lock and check if still nulled.
    // (If not, this is a very unlikly parallel access )
    OWN( ALIB::Lock );
    if ( processName.IsNotNull() )
        return;

    #if defined (__unix__)
        const ProcessInfo& pi= ProcessInfo::Current();
        processName._( pi.ExecName );

    #elif defined(_WIN32)
        TCHAR szPath[ MAX_PATH ];
        DWORD pathLen= GetModuleFileName( NULL, szPath, MAX_PATH );
        if ( pathLen <= 0)
        {
            ALIB_WARNING( "Error retrieving module name" );
            processName._( "UknProcess");
        }
        else
        {
            // convert to multi byte string and search last dir separator
            String512 moduleFileName;
            moduleFileName._( szPath );
            int sepIdx= moduleFileName.LastIndexOfAny( "/\\", Inclusion::Include );
            if ( sepIdx < 0)
            {
                ALIB_WARNING( "Error retrieving module name" );
                processName._( "UknProcess");
            }
            else
                processName._( moduleFileName, sepIdx + 1 );
        }
    #else
        #pragma message ("Unknown Platform in file: " __FILE__ )
        processName._( "UknProcessPlatform");
    #endif

}

}}}// namespace aworx::lib::system

