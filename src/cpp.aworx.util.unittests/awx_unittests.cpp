// #################################################################################################
//  aworx::util - Unit Tests
//
//  (c) 2013-2015 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################

// This helper header defines some preprocessor macros, so that GTest and MSVC Unit Tests can
// live in the same cpp file.
// Before including this header, the prepro variable "TESTCLASSNAME" has to be defined

#include "stdafx_awxu.h"
#include "awx_unittests.hpp"


using namespace std;
using namespace aworx::util;
using namespace aworx::lox;
using namespace aworx::lox::loggers;

namespace tests_aworx_util {



AWXUnitTesting::AWXUnitTesting(const char* domain, const char* testName)
{
    this->domain=       domain;
    this->actTestName=  testName;
    lox.AddLogger( &utl, aworx::lox::Log::DomainLevel::ERRORS );
    lox.SetDomain( domain, Log::DomainLevel::ALL );

    origErrorHandler=  AWXU::ReplaceErrorHandler( this );
}
AWXUnitTesting::~AWXUnitTesting()
{
    lox.RemoveLoggers();
    AWXU::ReplaceErrorHandler( origErrorHandler );
};


void AWXUnitTesting::Print( const char* file, int line, const char* func, int level, const char* msg )
{
    lox.AcquireAndSetCI(file, line, func);

        if ( level == 0 )
            lox.Info( domain, msg );
        else if (level == 1 )
            lox.Warning( domain, msg );
        else
            lox.Error( domain, msg );

    //    #if defined( ALOX_GTEST )
    //         cout << '[' << domain << ']' << '[' << actTestName << "]: " <<  msg << endl;
    //    #elif defined ( AWORX_VSTUDIO )
    //        Microsoft::VisualStudio::CppUnitTestFramework::Logger::WriteMessage( (AString128() << '[' << domain << ']' << '[' << actTestName << "]: " << msg).Buffer() );
    //    #else
    //        #pragma message ("Uknown Testing platfrom in: " __FILE__ )
    //    #endif

    lox.Release();
}



void AWXUnitTesting::Error   ( const char* msg ) {  Print( nullptr,0,nullptr,2, msg );  }
void AWXUnitTesting::Warning ( const char* msg ) {  Print( nullptr,0,nullptr,1, msg );  }
void AWXUnitTesting::DebugMsg( const char* msg ) {  Print( nullptr,0,nullptr,0, msg );  }


void UnitTestLogger::doTextLog( const aworx::util::AString&,                aworx::lox::Log::Level,
                                aworx::util::AString&           msg,        int,
                                aworx::lox::core::CallerInfo*,              int)
{
    #if defined( ALOX_GTEST )
        cout << msg.Buffer() << endl;
    #elif defined ( AWORX_VSTUDIO )
        Microsoft::VisualStudio::CppUnitTestFramework::Logger::WriteMessage(  msg.Buffer() );
    #else
        #pragma message ("Uknown Testing platfrom in: " __FILE__ )
    #endif
}

}//namespace


