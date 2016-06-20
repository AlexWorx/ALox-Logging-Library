// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
#include "alib/stdafx_alib.h"


#if !defined (HPP_ALIB_STRINGS_TOKENIZER)
    #include "alib/strings/tokenizer.hpp"
#endif

#if !defined (HPP_ALIB_SYSTEM_PROCESSINFO)
    #include "alib/system/process.hpp"
#endif

#if !defined (HPP_ALIB_THREADS_THREADLOCK)
    #include "alib/threads/threadlock.hpp"
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

namespace aworx {
namespace           lib {
namespace                   system {

// static instance representing current process
ProcessInfo    ProcessInfo::current;

const ProcessInfo&    ProcessInfo::Current()
{
    if( current.PID.IsEmpty()  )
    {
        // Own global lock and check if still nulled.
        // (If not, this is a very unlikely parallel access )
        OWN( ALIB::Lock );
        if ( ProcessInfo::current.PID.IsEmpty() )
            ProcessInfo::current.get(nullptr);
    }
    return current;
}


#if defined(__GLIBC__) && defined(__unix__)
    bool readProcFile( const TString& fileName, AString& result  )
    {
        result.Clear();
        ifstream file( fileName.ToCString() );
        string buffer;
        getline(file, buffer);

        // spaces are replaced with '\0'. Revert this.
        for( int i= buffer.size() -2 ; i>=0 ; --i )
            if ( buffer[i] == '\0' )
                buffer[i]= ' ';

        result.Clear()._( buffer.c_str() );
        file.close();
        return true;
    }

    bool ProcessInfo::getStatField( int fieldNo, AString& result )
    {
        result.Clear();
        Tokenizer tok( Stat, ' ');
        bool retval= true;
        while ( --fieldNo >= 0 && (retval= tok.HasNext()) )
            tok.Next();

        result._( tok.Next() );
        return retval;
    }

    bool ProcessInfo::get( const String& pid )
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
        String64 procDir("/proc/");  procDir._<false>( PID )._( '/' );
        int      procPathLen= procDir.Length();
        {

            // read things
            procDir << "cmdline"; readProcFile( procDir,  CmdLine  );  procDir.SetLength(procPathLen);
            procDir << "stat";    readProcFile( procDir,  Stat     );  procDir.SetLength(procPathLen);
        }

        getStatField( 3, PPID );
        getStatField( 1, Name );
        ALIB_ASSERT_ERROR(                 Name.IsEmpty()
                                ||   (     Name.Length() >= 2
                                        && Name.CharAtStart<false>()=='('
                                        && Name.CharAtEnd  <false>()==')' ),
                                "Error reading process Info" )

        if ( Name.CharAtEnd  () == ')' ) Name.DeleteEnd  <false>( 1 );
        if ( Name.CharAtStart() == '(' ) Name.DeleteStart<false>( 1 );
        getStatField( 2, StatState );
        getStatField( 4, statPGRP );

        // get executable path and name
        ExecFileName._();
        ExecFilePath._();

        procDir << "exe";
            char buffer[2048];
            ssize_t length= readlink( procDir.ToCString(), buffer, 2048 );
        procDir.SetLength(procPathLen);

        if( length > 0 )
        {
            ExecFilePath.Append( buffer, length );
            int idx= ExecFilePath.LastIndexOf( '/' );
            ALIB_ASSERT_ERROR( idx>= 0,
                                String256() << "Executable path does not contain directory separator character: "
                                            << ExecFilePath );
            ExecFileName._( ExecFilePath, idx + 1 );
            ExecFilePath.SetLength( idx );
        }
        else
        {
            // obviously no rights to read the link. We use the process name
            ExecFileName._( Name );
        }
        return true;
    }

#elif defined (_WIN32)

    bool ProcessInfo::get( const String& pid )
    {
        // get pid
        if (pid  != nullptr )
            return false;

        DWORD wPID= GetCurrentProcessId();
        PID    .Clear()._( (int)  wPID          );


        // get command line
        CmdLine._()._( GetCommandLine() );

        // get executable filename and path
        ExecFileName._();
        ExecFilePath._();
        Name._();


        char buf[MAX_PATH];
        GetModuleFileNameA( NULL, buf, MAX_PATH );
        ExecFilePath._()._( (const char*) buf );
        int idx= ExecFilePath.LastIndexOf( '\\' );
        ALIB_ASSERT_ERROR( idx>= 0,
                            String256() << "Executable path does not contain directory separator character: "
                                        << ExecFilePath );
        Name= ExecFileName._( ExecFilePath, idx + 1 );
        ExecFilePath.SetLength( idx );

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

