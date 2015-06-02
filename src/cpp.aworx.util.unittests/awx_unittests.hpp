// #################################################################################################
//  aworx::util - Unit Tests
//
//  (c) 2013-2015 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################

// This helper header defines some preprocessor macros, so that GTest and MSVC Unit Tests can
// live in the same cpp file.
// Before including this header, the prepro variable "TESTCLASSNAME" has to be defined

#include "alox.hpp"
#include "alox_console_logger.hpp"
#include <iostream>


#define __PREPRO_STRING_X(s) #s
#define __PREPRO_STRING(s)   __PREPRO_STRING_X(s)

#define  A_TEST_METHOD(name)            A_TEST_METHOD_X(name, TESTCLASSNAME)
#define  A_TEST_METHOD_X(m, sc)         A_TEST_METHOD_Y(m, __PREPRO_STRING( m ), __PREPRO_STRING( sc )  )
#define  A_TEST_METHOD_Y(m, sm, sc)     A_TEST_METHOD_Z(m, sm, sc)


// Google GTest Library
#if defined( ALOX_GTEST )

    #include "gtest/gtest.h"
    #include "iostream"
    #include "iomanip"
    #define  A_TEST_CLASS(name)
    #define  A_TEST_CLASS_END
    #define  A_TEST_METHOD_Z(m, sm, sc)     TEST(TESTCLASSNAME, m)              \
                                            { AWXUnitTesting ut( sc, sm );

    #define  PRINT(msg)                     { ut.Print(__FILE__, __LINE__, __func__, 0, (AString256() << msg).Buffer() ); }


// Microsoft Visual Studio UnitTestFramework
#elif defined ( AWORX_VSTUDIO )
    #include "CppUnitTest.h"
    #define  A_TEST_CLASS()                 TEST_CLASS(TESTCLASSNAME) { public:
    #define  A_TEST_CLASS_END               };

    // The prepro is never easy to understand. So do not think too long about why we have
    // to have the sub-macros "_X" and "_Y".
    #define  A_TEST_METHOD_Z(m, sm, sc)     BEGIN_TEST_METHOD_ATTRIBUTE( m )                   \
                                               TEST_METHOD_ATTRIBUTE( L ## sc, L"void")        \
                                            END_TEST_METHOD_ATTRIBUTE()                        \
                                            TEST_METHOD(m)                                     \
                                            { AWXUnitTesting ut( sc, sm );

    #define  EXPECT_TRUE(cond)              Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsTrue( cond )
    #define  EXPECT_EQ(a,b)                 Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual( a, b )
    #define  EXPECT_STREQ(a,b)              Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsTrue( strcmp(a,b) == 0 )
    #define  EXPECT_NEAR(a,b,diff)          Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsTrue( a-b<=diff || b-a<=diff )

    #define  PRINT(msg)                     { ut.Print(__FILE__, __LINE__, __FUNCTION__, 0, (AString256() << msg).Buffer() ); }
#else
    #pragma message ("Uknown Testing platfrom in: " __FILE__ )
#endif



namespace tests_aworx_util {


    class UnitTestLogger : public aworx::lox::core::TextLogger
    {
        public:

                      UnitTestLogger() : TextLogger( "UNITTEST" ) {};
            virtual  ~UnitTestLogger() {};

            void doTextLog( const aworx::util::AString&     domain,     aworx::lox::Log::Level  level,
                            aworx::util::AString&           msg,        int                     indent,
                            aworx::lox::core::CallerInfo*   caller,     int                     lineNumber);

            virtual void notifyMultiLineOp (bool )    {  }

    };



    class AWXUnitTesting : public aworx::util::AWXUErrorHandler
    {
        protected:
            const char*         domain;
            const char*         actTestName;
            AWXUErrorHandler*   origErrorHandler;

        public:
            aworx::lox::Lox     lox;
            UnitTestLogger      utl;

                     AWXUnitTesting(const char* domain, const char* testName);
            virtual ~AWXUnitTesting();

            void Print( const char* file, int line, const char* func, int level, const char* msg );


            virtual void Error   ( const char* msg );
            virtual void Warning ( const char* msg );
            virtual void DebugMsg( const char* msg );
    };
}
