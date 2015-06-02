// #################################################################################################
//  aworx::lox - ALox Logging Library
//
//  (c) 2013-2015 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
#include "stdafx_awxu.h"

#if !defined (HPP_AWORX_ALOX_ALOX)
    #include "alox.hpp"
#endif

#if !defined (_GLIBCXX_IOSTREAM) && !defined(_IOSTREAM_)
    #include <iostream>
#endif


using namespace std;
using namespace aworx::util;
using namespace aworx::lox;

// #################################################################################################
// The lox singleton for debug logging
// #################################################################################################
#if defined(ALOX_DBG_LOG)
    Lox* Log::lox= nullptr;
#endif

bool Log::isInitialized= false;
bool Log::InitALox( int classSizeVeryfier )
{
    if ( classSizeVeryfier != ALOX_COMPILED_CLASS_SIZE_VERIFYER )
    {
        cout << "!!! Error in ALox library compilation: internal size of classes are different " << endl
             << "!!! to external ones." << endl
             << "!!! Make sure, that all compilation units have the same compile settings!" << endl
             << "!!! Exiting with exit(-1)!!!"
             << endl;
        exit(-1);
    }

    if ( !isInitialized )
    {
        isInitialized= true;

        // initialize AWXU
        AWXU::Init();

        // create the debug lox singleton
        #if defined(ALOX_DBG_LOG)
            Log::lox=   new Lox();
        #endif
        return true;
    }
    return false;
}

void Log::TerminationCleanUp()
{
    #if defined(ALOX_DBG_LOG)
        if ( lox != nullptr )
            delete lox;
    #endif

    AWXU::TerminationCleanUp();
}



// #################################################################################################
// ToString() methods for ALox public enums
// #################################################################################################

#define CASE_RETURN(enum,field)  { case enum::  field : return #field; }

    //static
    const char* Log::ToString( Log::DomainLevel level )
    {
        switch( level )
        {
                        CASE_RETURN( DomainLevel, OFF                      )
                        CASE_RETURN( DomainLevel, ERRORS                   )
                        CASE_RETURN( DomainLevel, WARNINGS_AND_ERRORS      )
                        CASE_RETURN( DomainLevel, INFO_WARNINGS_AND_ERRORS )
                        CASE_RETURN( DomainLevel, ALL                      )
            default:    CASE_RETURN( DomainLevel, INHERIT                  )
        }
    }

    //static
    const char* Log::ToString( Log::Level level )
    {
        switch( level )
        {
                        CASE_RETURN( Level, VERBOSE  )
                        CASE_RETURN( Level, INFO     )
                        CASE_RETURN( Level, WARNING  )
            default:    CASE_RETURN( Level, ERROR    )
        }
    }

    //static
    const char* Log::ToString( Log::Scope scope )
    {
        switch( scope )
        {
                        CASE_RETURN( Scope, NONE         )
                        CASE_RETURN( Scope, SOURCE_FILE  )
            default:    CASE_RETURN( Scope, METHOD       )
        }
    }

#undef CASE_RETURN
