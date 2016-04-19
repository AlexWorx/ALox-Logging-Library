// #################################################################################################
//  Unit Tests - ALox Logging Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################

#include "alib/alib.hpp"
#include "alox/alox.hpp"

#include "gtest/gtest.h"
#include "aworx_unittests.hpp"

#include "alib/compatibility/std_iostream.hpp"


using namespace std;
using namespace aworx;


int main( int argc, char **argv )
{
    ::testing::InitGoogleTest(&argc, argv);

    aworx::lox::ALox::Init( aworx::lib::enums::Inclusion::Include, argc, (void**) argv );
    //aworx::lib::Report::GetDefault().HaltOnWarning= true;

//    ::testing::GTEST_FLAG(filter) = "CPP_Strings_AString*:CPP_Ticks*:CPP_Thread*:CPP_ALox*:CPP_Tutorial*";

//  ::testing::GTEST_FLAG(filter) = "CPP_Conf*";

//    ::testing::GTEST_FLAG(filter) = "CPP_Strings_AString.*";
//    ::testing::GTEST_FLAG(filter) = "CPP_Strings_AString.WCharConversion";
//    ::testing::GTEST_FLAG(filter) = "CPP_SubstringAndTokenizer.*";
//    ::testing::GTEST_FLAG(filter) = "CPP_Strings_AS.*";

//    ::testing::GTEST_FLAG(filter) = "CPP_Strings_ASBasic.Append*";
//    ::testing::GTEST_FLAG(filter) = "CPP_Strings_ASBasic*";

//    ::testing::GTEST_FLAG(filter) = "CPP_Ticks*";
//    ::testing::GTEST_FLAG(filter) = "CPP_ALib_Threads*";
//    ::testing::GTEST_FLAG(filter) = "CPP_ALib_Threads.ThreadSimple";
//    ::testing::GTEST_FLAG(filter) = "CPP_ALib_Threads.SmartLock";

//    ::testing::GTEST_FLAG(filter) = "CPP_Environment*";
//    ::testing::GTEST_FLAG(filter) = "CPP_Config.IniFiles";

//    ::testing::GTEST_FLAG(filter) = "CPP_ALox_Tutorial*";
//    ::testing::GTEST_FLAG(filter) = "CPP_ALox_Tutorial.Hello*";
//    ::testing::GTEST_FLAG(filter) = "CPP_ALox*";
//    ::testing::GTEST_FLAG(filter) = "CPP_ALox_Logger.*";
//    ::testing::GTEST_FLAG(filter) = "CPP_ALox_Logger.Log_TestMultiline*";
//    ::testing::GTEST_FLAG(filter) = "CPP_ALox_Lox*";
//    ::testing::GTEST_FLAG(filter) = "CPP_ALox_Lox.Log_TestThreads*";
//    ::testing::GTEST_FLAG(filter) = "CPP_ALox_Lox.Log_SetSourcePathTrimRule";
//    ::testing::GTEST_FLAG(filter) = "CPP_ALox_Lox.Log_ScopeInfoCacheTest";

//    ::testing::GTEST_FLAG(filter) = "CPP_ALox_Lox_Release.Lox_LoggerInTwoLoxes*";

//    ::testing::GTEST_FLAG(filter) = "CPP_ALox_Log_Domains.*";
//    ::testing::GTEST_FLAG(filter) = "CPP_ALox_Log_Domains.Log_DomainSubstitutions*";
//    ::testing::GTEST_FLAG(filter) = "CPP_ALox_Log_Domains.Log_Domain_IniFile*";

//    ::testing::GTEST_FLAG(filter) = "CPP_ALox_Log_Scopes.*";
//    ::testing::GTEST_FLAG(filter) = "CPP_ALox_Log_Scopes.Log_ScopeDomains*";
//    ::testing::GTEST_FLAG(filter) = "CPP_ALox_Log_Scopes.Lox_ScopeDomains*";
//    ::testing::GTEST_FLAG(filter) = "CPP_ALox_Log_Scopes.Log_Once*";
//    ::testing::GTEST_FLAG(filter) = "CPP_ALox_Log_Scopes.Log_Store*";
//    ::testing::GTEST_FLAG(filter) = "CPP_ALox_Log_Scopes.Log_Prefix*";

//    ::testing::GTEST_FLAG(filter) = "CPP_ALox_Loggers.Log_TextLogger_RegisterStreamLocks*";
//    ::testing::GTEST_FLAG(filter) = "CPP_ALox_Loggers.Log_TextLogger_ObjectConverter*";


    auto retval= RUN_ALL_TESTS();

    ALox::TerminationCleanUp();

    return retval;
}



