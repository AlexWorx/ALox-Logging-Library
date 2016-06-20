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

#if !defined (HPP_ALIB_COMPATIBILITY_STD_IOSTREAM)
    #include "alib/compatibility/std_iostream.hpp"
#endif

#include <fstream>
#include <cstdio>   // gives us FILENAME_MAX


using namespace std;

namespace aworx {
namespace           lib {
namespace                   system {


// #################################################################################################
// Static variables
// #################################################################################################
AString         Directory::evaluatedTempDir;
AString         Directory::evaluatedVarTempDir;

// #################################################################################################
// Change
// #################################################################################################
#if !defined(IS_DOXYGEN_PARSER)
void createTempFolderInHomeDir( const String& folderName, AString& resultPath, const String& reasonMsg )
{
    // get home directory and set this as fallback result value
    Directory homeTemp( Directory::SpecialFolder::Home );
    resultPath=   homeTemp.Path;

    // add given folder name and check if already exists
    homeTemp.Path._( DirectorySeparator )._( folderName );
    bool exists= Directory::Exists( homeTemp.Path );
    if( !exists )
    {
        if( Directory::Create( homeTemp.Path ) == Result::OK )
        {
            exists= true;
            AString fileName( homeTemp.Path ); fileName._( DirectorySeparator )._( "readme.txt" );

            ofstream file ( fileName.ToCString() );
            if ( file.is_open() )
            {
                const ProcessInfo& pi= ProcessInfo::Current();
                file << "This folder was created by \"" << pi.CmdLine
                     << "\"" << endl
                     << "to be used for temporary files." << endl
                     << reasonMsg
                     << endl;
                file.close();
            }
        }
    }

    // if existed or got created
    if( exists )
        resultPath=   homeTemp.Path;
}
#endif

void Directory::Change( SpecialFolder special )
{
    switch( special )
    {
        case SpecialFolder::Root:       Path._( DirectorySeparator );
                                        break;
        case SpecialFolder::Current:    Directory::CurrentDirectory( Path );
                                        break;
        case SpecialFolder::Home:
        {

            #if defined (__unix__)
                // get home path
                if ( !System::GetVariable( "HOME", Path ) )
                    Path._( "~/" );

            #elif defined(_WIN32)
                if ( !System::GetVariable( "USERPROFILE", Path ) || !Directory::Exists( Path ) )
                {
                    System::GetVariable( "HOMEDRIVE", Path );
                    System::GetVariable( "HOMEPATH",  Path, CurrentData::Keep );
                }
            #else
                #pragma message ("Unknown Platform in file: " __FILE__ )
            #endif
        }
        break;

        case SpecialFolder::HomeConfig:
        {
            Change( SpecialFolder::Home );
            // try ".config" and "AppData/Roaming" subdirectories.
            if ( !Change( ".config" ) )
                  Change( String16("AppData") << DirectorySeparator << "Roaming" );
        }
        break;


        case SpecialFolder::Module:
        {
            Path._()._( ProcessInfo::Current().ExecFilePath );
        }
        break;

        case SpecialFolder::Temp:
        {

            if ( evaluatedTempDir.IsEmpty() )
            {
                #if defined (__unix__)

                    const String reasonMsg=  "(The default temporary folder \"/tmp\" could not be found.)";

                    if ( Directory::Exists( "/tmp" ) )
                        evaluatedTempDir= "/tmp";

                #elif defined(_WIN32)
                    const String reasonMsg=  "(Environment variables TMP and TEMP either not set or not containing valid paths.)";
                    AString testDir;
                    if (     ( System::GetVariable( "TMP" , testDir ) && Directory::Exists( testDir ) )
                         ||  ( System::GetVariable( "TEMP", testDir ) && Directory::Exists( testDir ) ) )
                    {
                        evaluatedTempDir= testDir;
                    }
                #else
                    #pragma message ("Unknown Platform in file: " __FILE__ )
                #endif


                if( evaluatedTempDir.IsEmpty() )
                {
                    createTempFolderInHomeDir( ".tmp", evaluatedTempDir, reasonMsg );

                    // If this did not work, use home
                    if( evaluatedTempDir.IsEmpty() )
                    {
                        Change( SpecialFolder::Home );
                        evaluatedTempDir= Path;
                    }
                }

            }

            // set path to evaluated dir name
            Path= evaluatedTempDir;
        }
        break;

        case SpecialFolder::VarTemp:
        {
            if ( evaluatedVarTempDir.IsEmpty() )
            {
                #if defined (__unix__)
                    const String reasonMsg=  "(The default temporary folder \"/var/tmp\" could not be found.)";

                    if ( Directory::Exists( "/var/tmp" ) )
                        evaluatedVarTempDir= "/var/tmp";
                #elif defined(_WIN32)
                    const String reasonMsg=  "(Environment variables TMP and TEMP either not set or not containing valid paths.)";
                    AString testDir;
                    if (     ( System::GetVariable( "TMP" , testDir ) && Directory::Exists( testDir ) )
                         ||  ( System::GetVariable( "TEMP", testDir ) && Directory::Exists( testDir ) ) )
                    {
                        evaluatedVarTempDir= testDir;
                    }
                #else
                    #pragma message ("Unknown Platform in file: " __FILE__ )
                #endif


                if( evaluatedVarTempDir.IsEmpty() )
                {
                    createTempFolderInHomeDir( ".var.tmp", evaluatedVarTempDir, reasonMsg );

                    // If this did not work, use home
                    if( evaluatedVarTempDir.IsEmpty() )
                    {
                        Change( SpecialFolder::Home );
                        evaluatedVarTempDir= Path;
                    }
                }

            }
            // now path to evaluated dir name
            Path= evaluatedVarTempDir;
        }
        break;
    }
}

bool Directory::Change( const String& path )
{
    int origLength= Path.Length();
    Path._<false>( DirectorySeparator )
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

bool Directory::Exists( const TString& path )
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

Result Directory::Create( const TString& path )
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

