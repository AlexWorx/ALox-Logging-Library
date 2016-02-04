// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
#include "alib/stdafx_alib.h"

#include "alib/system/directory.hpp"
#include "alib/system/process.hpp"
#include "alib/system/system.hpp"

#if   defined(__GLIBCXX__)
    #include <unistd.h>
    #include <dirent.h>
    #include <sys/stat.h>
    #include <sys/types.h>
    #include <errno.h>
#elif defined ( _WIN32 )
    #include <direct.h>
#else
    #pragma message ("Unknown Platform in file: " __FILE__ )
#endif

#include <cstdio>   // gives us FILENAME_MAX


using namespace std;
using namespace aworx::lib::strings;
using namespace aworx::lib::enums;

namespace aworx {
namespace           lib {
namespace                   system {


// #################################################################################################
// Change
// #################################################################################################

void Directory::Change( SpecialFolder special )
{
    switch( special )
    {
        case SpecialFolder::Root:       Path._( PathSeparator );
                                        break;
        case SpecialFolder::Current:    Directory::CurrentDirectory( Path );
                                        break;
        case SpecialFolder::Home:
        {

            #if defined (__GLIBC__)

                // get home path
                if ( !System::GetVariable( "HOME", Path ) )
                    Path._( "~/" );

            #elif defined(_WIN32)
                system::System::GetVariable( "HOMEDRIVE", Path );
                system::System::GetVariable( "HOMEPATH",  Path, CurrentData::Keep );
            #else
                #pragma message ("Unknown Platform in file: " __FILE__ )
            #endif
        }
        break;

        case SpecialFolder::HOME_CONFIG:
        {
            #if defined (__GLIBC__)

                // get home path, append '.config'
                if ( !System::GetVariable( "HOME", Path ) )
                    Path._( "~/" );

            #elif defined(_WIN32)
                system::System::GetVariable( "HOMEDRIVE", Path );
                system::System::GetVariable( "HOMEPATH",  Path, CurrentData::Keep );
            #else
                #pragma message ("Unknown Platform in file: " __FILE__ )
            #endif

            // try ".config" and "AppData/Roaming" subdirectories.
            if ( !Change( ".config" ) )
                  Change( String16("AppData") << PathSeparator << "Roaming" );
        }
        break;


        case SpecialFolder::Module:
        {
            const ProcessInfo& pi= ProcessInfo::Current();
            #if defined (__GLIBC__)
                ALIB_ASSERT_ERROR( pi.CmdLine.EndsWith( pi.ExecName), "Error in ALib (wrong assumption)" );
                Path._(pi.CmdLine, 0, pi.CmdLine.Length() -  pi.ExecName.Length() - 1 );
            #elif defined(_WIN32)
                Path._(pi.CmdLine, 0, pi.CmdLine.LastIndexOf( PathSeparator ) );
            #else
                #pragma message ("Unknown Platform in file: " __FILE__ )
            #endif
        }
        break;
    }
}

bool Directory::Change( const String& path )
{
    int origLength= Path.Length();
    Path._<false>( PathSeparator )
        ._( path );

    if( Directory::Exists( Path ) )
        return true;

    Path.SetLength<false>( origLength );
    return false;
}

// #################################################################################################
// Static methods
// #################################################################################################

bool Directory::CurrentDirectory( AString& target )
{
    target.Clear();
    char charbuf[FILENAME_MAX];

    #if   defined(__GLIBCXX__)
        if ( !getcwd( charbuf, sizeof(charbuf ) ) )
    #elif defined ( _WIN32 )
        if ( !_getcwd( charbuf, sizeof(charbuf ) ) )
    #else
        #pragma message ("Unknown Platform in file: " __FILE__ )
    #endif
    {
        return false;
    }

    charbuf[ sizeof(charbuf) - 1 ] = '\0'; // not really required, but who knows

    target._( (const char*) charbuf );
    return true;
}

bool Directory::Exists( const ASTerminatable& path )
{
    #if defined (__GLIBC__)
        DIR* dir= opendir( path.ToCString() );
        if ( dir != nullptr )
        {
            closedir( dir );
            return true;
        }
        return false;

    #elif defined(_WIN32)

        DWORD dwAttrib = GetFileAttributesA( path.ToCString() );
        if( dwAttrib == INVALID_FILE_ATTRIBUTES )
            return false;
        if ( dwAttrib & FILE_ATTRIBUTE_DIRECTORY )
            return true;
        return false;

    #else
        #pragma message ("Unknown Platform in file: " __FILE__ )
    #endif
}

Result Directory::Create( const ASTerminatable& path )
{
    #if defined (__GLIBC__)

        if ( mkdir( path.ToCString(), S_IRWXU | S_IRGRP | S_IROTH
                                              | S_IXGRP | S_IXOTH  ) == 0 )
            return Result::OK;

        switch( errno )
        {
              case ENOENT      : return Result::InvalidPath                  ; break;
              case EEXIST      : return Result::FileExists                   ; break;

              case EACCES      : return Result::Directory_Create_EACCES      ; break;
              case EDQUOT      : return Result::Directory_Create_EDQUOT      ; break;
              case EFAULT      : return Result::Directory_Create_EFAULT      ; break;
              case ELOOP       : return Result::Directory_Create_ELOOP       ; break;
              case EMLINK      : return Result::Directory_Create_EMLINK      ; break;
              case ENAMETOOLONG: return Result::Directory_Create_ENAMETOOLONG; break;
              case ENOMEM      : return Result::Directory_Create_ENOMEM      ; break;
              case ENOSPC      : return Result::Directory_Create_ENOSPC      ; break;
              case ENOTDIR     : return Result::Directory_Create_ENOTDIR     ; break;
              case EPERM       : return Result::Directory_Create_EPERM       ; break;
              case EROFS       : return Result::Directory_Create_EROFS       ; break;

              default:           ALIB_ASSERT( "Unknown Error code returned by 'mkdir'" );
                                 return Result::Error;
        }

    #elif defined(_WIN32)
        wchar_t* wcharPath= new wchar_t[ path.Length() + 1];
        path.ToWString( wcharPath, path.Length() + 1);
        BOOL result= CreateDirectory( wcharPath, NULL );
        delete wcharPath;


        if( result )
            return Result::OK;
        switch ( GetLastError() )
        {
            case  ERROR_ALREADY_EXISTS: return Result::FileExists;
            case  ERROR_PATH_NOT_FOUND: return Result::InvalidPath;
            default:                    ALIB_ASSERT( "Unknown Error code returned by 'CreateDirectory' (Win32)" );
                                        return Result::Error;
        }

    #else
        #pragma message ("Unknown Platform in file: " __FILE__ )
    #endif
}



}}}// namespace aworx::lib::system

