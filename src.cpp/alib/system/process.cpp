// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
#include "alib/stdafx_alib.h"

#if !defined (HPP_AWORX_LIB_SYSTEM_PROCESSINFO)
    #include "alib/system/process.hpp"
#endif

#if defined (__GLIBCXX__)
    #include <unistd.h>
#elif   defined( _WIN32 )
    #include <direct.h>
#else
    #pragma message ("Unknown Platform in file: " __FILE__ )
#endif

#if !defined(_GLIBCXX_FSTREAM) && !defined(_FSTREAM_)
    #include <fstream>
#endif

using namespace std;
using namespace aworx::lib::strings;
using namespace aworx::lib::enums;

namespace aworx {
namespace           lib {
namespace                   system {

// static instance representing current process
ProcessInfo    ProcessInfo::current;

#if defined(__GLIBC__) && defined(__unix__)
    bool readProcFile( const AString& fileName, AString& result  )
    {
        result.Clear();
        ifstream file( fileName.ToCString() );
        string buffer;
        getline(file, buffer);

        // there might be double zeros at the end of the string. This is why we are appending
        // the string using its c_str method instead of passing the string (which would be more
        // efficient otherwise).
        result.Clear()._( buffer.c_str() );
        file.close();
        return true;
    }

    bool ProcessInfo::getStatField( int fieldNo, AString& result )
    {
        result.Clear();
        // search startidx
        int startIdx= 0;
        for ( int i= 0; i < fieldNo; i++ )
        {
            startIdx= Stat.IndexOf( ' ', startIdx + 1 );
            if( startIdx < 0 )
                return false;
        }
        startIdx++;

        // search end
        int endIdx=  Stat.IndexOf( ' ', startIdx );
        if ( endIdx < 0)
            endIdx= Stat.Length();

        result._<false>( Stat, startIdx, endIdx - startIdx );
        return true;
    }

    bool ProcessInfo::get( const AS& pid )
    {
        // use current thread if no PID given
        String32 newPID;
        if ( pid.IsNull() )
            newPID << getpid();
        else
            newPID << pid;

        if ( newPID.IsEmpty() )
            return false;


        PID.Clear()._( newPID );

        // cmdline, stat from proc
        {
            String64 procDir("/proc/");
            procDir._<false>( PID )._( '/' );

            // read things
            int procPathLen= procDir.Length();   procDir << "cmdline";
            readProcFile( procDir,  CmdLine  );
            procDir.SetLength(procPathLen);      procDir << "stat";
            readProcFile( procDir,  Stat     );
        }

        getStatField( 3, PPID );
        getStatField( 1, ExecName );
        AString& execName= ExecName;
        ALIB_ASSERT_ERROR(                 execName.IsEmpty()
                                ||   (     execName.Length() >= 2
                                        && execName.CharAtStart<false>()=='('
                                        && execName.CharAtEnd  <false>()==')' ),
                                "Error reading process Info" )

        if ( execName.CharAtEnd  () == ')' ) execName.DeleteEnd  <false>( 1 );
        if ( execName.CharAtStart() == '(' ) execName.DeleteStart<false>( 1 );

        getStatField( 2, StatState );
        getStatField( 4, statPGRP );

        return true;
    }

#elif defined (_WIN32)

    bool ProcessInfo::get( const AS& pid )
    {
        // get pid
        if (pid  != nullptr )
            return false;

        DWORD wPID= GetCurrentProcessId();
        PID    .Clear()._( (int)  wPID          );

        // get command line
        char buf[256];
        GetModuleFileNameA( NULL, buf, 256 );
        CmdLine.Clear()._( buf );

        // get console title
        STARTUPINFOA startupInfo;
        GetStartupInfoA( &startupInfo );
        ConsoleTitle.Clear()._( startupInfo.lpTitle );

        return true;
    }

#else
    #pragma message ("Unknown Platform in file: " __FILE__ )
#endif



}}}// namespace aworx::lib::system

