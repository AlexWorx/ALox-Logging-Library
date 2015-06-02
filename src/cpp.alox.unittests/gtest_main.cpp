// #################################################################################################
//  Unit Tests - ALox Logging Library
//
//  (c) 2013-2015 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################

#include "awxu.hpp"
#include "alox.hpp"

#include "gtest/gtest.h"
#include "awx_unittests.hpp"

using namespace std;


int main( int argc, char **argv )
{
    {
        ALOX_COMPILER_SYMBOL_SETTINGS
        cout << "ALox compilation symbols: "    << endl;
        cout << acss.Buffer()  << endl << endl;
    }

    ::testing::InitGoogleTest(&argc, argv);

    aworx::util::AWXU::Init();
    aworx::util::AWXU::HaltOnWarning= true;
//    ::testing::GTEST_FLAG(filter) = "CPP_AString*:CPP_Ticks*:CPP_Thread*:CPP_ALox*:CPP_Tutorial*";

//    ::testing::GTEST_FLAG(filter) = "CPP_AString*";
//    ::testing::GTEST_FLAG(filter) = "CPP_Ticks*";
//    ::testing::GTEST_FLAG(filter) = "CPP_Thread*";
//    ::testing::GTEST_FLAG(filter) = "CPP_Tutorial*";
//    ::testing::GTEST_FLAG(filter) = "CPP_ALox*";

    auto retval= RUN_ALL_TESTS();

    aworx::lox::Log::TerminationCleanUp();

    return retval;
}



