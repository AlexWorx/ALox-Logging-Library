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
using namespace aworx::lib::strings;


int main( int argc, char **argv )
{
    ::testing::InitGoogleTest(&argc, argv);

    aworx::lox::Log::Init( aworx::lib::enums::Inclusion::Include, argc, (void**) argv );
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
//    ::testing::GTEST_FLAG(filter) = "CPP_Environment*";
//    ::testing::GTEST_FLAG(filter) = "CPP_Config.IniFiles";

//    ::testing::GTEST_FLAG(filter) = "CPP_ALox_Tutorial*";
//    ::testing::GTEST_FLAG(filter) = "CPP_ALox*";
//    ::testing::GTEST_FLAG(filter) = "CPP_ALox_Log_Debug.*";

//    ::testing::GTEST_FLAG(filter) = "CPP_ALox_Log_Debug.Log_TestMultiline*";
//    ::testing::GTEST_FLAG(filter) = "CPP_ALox_Log_Debug.Log_TestThreads*";


//    ::testing::GTEST_FLAG(filter) = "CPP_ALox_Lox_Release.Lox_DisableLogger";

    auto retval= RUN_ALL_TESTS();

    aworx::lox::Log::TerminationCleanUp();

    return retval;
}



