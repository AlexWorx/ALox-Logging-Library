// #################################################################################################
//  aworx - Unit Tests
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
#include "alib/stdafx_alib.h"

#include "alib/alib.hpp"

#if !defined (HPP_ALIB_SYSTEM_ENVIRONMENT)
    #include "alib/system/system.hpp"
#endif

#if !defined (HPP_ALIB_SYSTEM_PROCESSINFO)
    #include "alib/system/process.hpp"
#endif

#if !defined (HPP_ALIB_SYSTEM_DIRECTORY)
    #include "alib/system/directory.hpp"
#endif

#if !defined (HPP_ALIB_STRINGS_ASTRING)
    #include "alib/strings/asalloc.hpp"
#endif



#define TESTCLASSNAME       CPP_ALib_Environment
#include "aworx_unittests.hpp"

using namespace std;
using namespace aworx;

namespace ut_aworx {


UT_CLASS()

//---------------------------------------------------------------------------------------------------------
//--- CurrentDir
//---------------------------------------------------------------------------------------------------------

UT_METHOD(CurrentDir)

    UT_PRINT(""); UT_PRINT( "### Environment::CurrentWorkingDir###" );

    String512 cwd;
    Directory::CurrentDirectory( cwd );
    UT_PRINT("The working directory is:" );
    UT_PRINT(cwd);
    UT_TRUE( cwd.IsNotEmpty() );
    UT_TRUE( Directory::Exists( cwd ) );
}



//---------------------------------------------------------------------------------------------------------
//--- GetVariable
//---------------------------------------------------------------------------------------------------------
UT_METHOD(GetVariable)

    UT_PRINT(""); UT_PRINT( "### Environment::GetVariable###" );

    aworx::AString home;
    #if defined(_WIN32)
        System::GetVariable( "HOMEDRIVE", home );
        System::GetVariable( "HOMEPATH" , home, CurrentData::Keep );
    #else
        System::GetVariable( "HOME"    , home );
    #endif

    UT_PRINT("The home directory is:" );
    UT_PRINT(home);
    UT_TRUE( Directory::Exists( home ) );
}

//---------------------------------------------------------------------------------------------------------
//--- Processes
//---------------------------------------------------------------------------------------------------------
UT_METHOD(Processes)

    UT_PRINT(""); UT_PRINT( "### Environment::GetProcessInfo###" );


    String512 output;
    const ProcessInfo& currentProcess= ProcessInfo::Current();
    UT_TRUE( currentProcess.PID.IsNotEmpty() );


    #if defined (__GLIBC__)
        // print process tree of us
        int indent= 0;
        String16 nextPID= currentProcess.PPID;
        while ( nextPID.IsNotEmpty() )
        {
            ProcessInfo pi( nextPID );
            output.Clear().InsertChars(' ', 2* indent); output  << "PID:       " << pi.PID;       UT_PRINT( output )
            output.Clear().InsertChars(' ', 2* indent); output  << "PPID:      " << pi.PPID;      UT_PRINT( output )
            output.Clear().InsertChars(' ', 2* indent); output  << "ExecName:  " << pi.ExecName;  UT_PRINT( output )
            output.Clear().InsertChars(' ', 2* indent); output  << "CmdLine:   " << pi.CmdLine;   UT_PRINT( output )
            output.Clear().InsertChars(' ', 2* indent); output  << "StatState: " << pi.StatState; UT_PRINT( output )
            output.Clear().InsertChars(' ', 2* indent); output  << "statPGRP:  " << pi.statPGRP;  UT_PRINT( output )
            //output.Clear()._(' ', 2* indent); output  << "Stat:      " << pi.Stat;      UT_PRINT( output )

            indent++;
            nextPID= pi.PPID;
        }


    #elif defined(_WIN32)


        output.Clear(); output  << "PID:               " << currentProcess.PID;                      UT_PRINT( output )
        output.Clear(); output  << "CmdLine:           " << currentProcess.CmdLine;                  UT_PRINT( output )
        output.Clear(); output  << "ConsoleTitle:      " << currentProcess.ConsoleTitle;             UT_PRINT( output )

    #else
        #pragma message ("Unknown Platform in file: " __FILE__ )
    #endif
}


UT_CLASS_END

}; //namespace



