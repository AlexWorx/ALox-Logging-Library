// #################################################################################################
//  aworx - Unit Tests
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
//
//  Defines some preprocessor macros and classes so that GTest and MSVC Unit Tests can live in
//  the same cpp file.
//  Relies on ALox logging library, which in turn relies on ALib. Hence, ALibs' unit
//  tests can only be compiled if ALox library is present.
//  (This is a 'circular dependency', that is taken into account)
//
//  Before including this header, the prepro variable "TESTCLASSNAME" has to be defined.
// #################################################################################################


// include ALox main header first...
#if !defined (HPP_ALOX)
    #include "alox/alox.hpp"
#endif

// then, set include guard
#ifndef HPP_ALIB_ALOX_UNIT_TESTS
#define HPP_ALIB_ALOX_UNIT_TESTS 1

#include "alox/alox_console_loggers.hpp"

#if !defined(HPP_ALIB_SYSTEM_DIRECTORY)
    #include "alib/system/directory.hpp"
#endif

#include <iostream>
#include <fstream>


#define __PREPRO_STRING_X(s) #s
#define __PREPRO_STRING(s)   __PREPRO_STRING_X(s)

#if defined( ALIB_QTCREATOR )
    #define  UT_RESULT_FILE_DIR             "../../../../../docs/ALox.CPP/generated/"
#elif defined( ALIB_VSTUDIO )
    #define  UT_RESULT_FILE_DIR                "../../../../docs/ALox.CPP/generated/"
#else
    #define  UT_RESULT_FILE_DIR             "../../../../../docs/ALox.CPP/generated/"
#endif


#define  UT_METHOD(name)         UT_METHOD_X(name, TESTCLASSNAME)
#define  UT_METHOD_X(m, sc)      UT_METHOD_Y(m, __PREPRO_STRING( m ), __PREPRO_STRING( sc ))
#define  UT_METHOD_Y(m, sm, sc)  UT_METHOD_Z(m, sm, sc)


// Google GTest Library
#if defined( ALIB_GTEST )

    #include "gtest/gtest.h"
    #include "iostream"
    #include "iomanip"
    #define UT_FUNC_MACRO   __func__


    //---------- redefining internal GTest macro GTEST_TEST_, to add test name as field of test class
    // This might get incompatible with future GTest versions, but we have not found any other way.

    #undef GTEST_TEST_
    // Helper macro for defining tests.
    #define GTEST_TEST_(test_case_name, test_name, parent_class, parent_id)\
    class GTEST_TEST_CLASS_NAME_(test_case_name, test_name) : public parent_class {\
     public:\
      GTEST_TEST_CLASS_NAME_(test_case_name, test_name)() {}\
     private:\
      const char* aworxTestName= ALIB_STRINGIFY(test_name);\
      virtual void TestBody();\
      static ::testing::TestInfo* const test_info_ GTEST_ATTRIBUTE_UNUSED_;\
      GTEST_DISALLOW_COPY_AND_ASSIGN_(\
          GTEST_TEST_CLASS_NAME_(test_case_name, test_name));\
    };\
    \
    ::testing::TestInfo* const GTEST_TEST_CLASS_NAME_(test_case_name, test_name)\
      ::test_info_ =\
        ::testing::internal::MakeAndRegisterTestInfo(\
            #test_case_name, #test_name, NULL, NULL, \
            (parent_id), \
            parent_class::SetUpTestCase, \
            parent_class::TearDownTestCase, \
            new ::testing::internal::TestFactoryImpl<\
                GTEST_TEST_CLASS_NAME_(test_case_name, test_name)>);\
    void GTEST_TEST_CLASS_NAME_(test_case_name, test_name)::TestBody()
    //--------------- end of redefining gtest

    #define  UT_CLASS(name) // nothing in it in GTest: every test is is own class
    #define  UT_CLASS_END

    #define  UT_METHOD_Z(m, sm, sc)       GTEST_TEST(TESTCLASSNAME, m)


// Microsoft Visual Studio UnitTestFramework
#elif defined ( ALIB_VSTUDIO )
    #include "CppUnitTest.h"
    #include "alox/loggers/memorylogger.hpp"
    #define UT_FUNC_MACRO   __FUNCTION__

    #define  UT_CLASS()                   TEST_CLASS(TESTCLASSNAME)                                             \
                                           {  private:  const char* aworxTestName= ALIB_STRINGIFY(test_name);   \
                                              public:                                                           

    #define  UT_CLASS_END                  };

    // The prepro is never easy to understand. So do not think too long about why we have
    // to have the sub-macros "_X" and "_Y".
    #define  UT_METHOD_Z(m, sm, sc)       BEGIN_TEST_METHOD_ATTRIBUTE( m )                   \
                                             TEST_METHOD_ATTRIBUTE( L ## sc, L"void")        \
                                          END_TEST_METHOD_ATTRIBUTE()                        \
                                          TEST_METHOD(m)

#else
    #pragma message ("Unknown Testing platform in: " __FILE__ )
#endif


#define UT_INIT(...)        aworx::AString sc (__FILE__);                       \
                            int idx= sc.LastIndexOf( aworx::PathSeparator );    \
                            sc.DeleteStart( idx + 1 );                          \
                            idx= sc.LastIndexOf( '.' );                         \
                            if( idx > 0 )                                       \
                                sc.Delete( idx );                               \
                            ALIBUnitTesting ut( sc, aworxTestName );            \
                            UT_PRINT( "################### Unit Test: " << sc << '.' << aworxTestName << "() ###################" );


#define  UT_PRINT(msg)                { ut.Print (__FILE__, __LINE__, UT_FUNC_MACRO, aworx::Verbosity::Info, aworx::String512() << msg ); }
#define  UT_EQ(    a,b  )             ut.EQ      (__FILE__, __LINE__, UT_FUNC_MACRO,  a,b    );
#define  UT_NEAR( a,b,d )             ut.EQ      (__FILE__, __LINE__, UT_FUNC_MACRO,  a,b, d );
#define  UT_TRUE(  cond  )            ut.ISTRUE  (__FILE__, __LINE__, UT_FUNC_MACRO,  cond   );
#define  UT_FALSE( cond  )            ut.ISFALSE (__FILE__, __LINE__, UT_FUNC_MACRO,  cond   );

namespace ut_aworx {


    #if defined ( ALIB_VSTUDIO )
        class VStudioUnitTestLogger : public aworx::lox::loggers::MemoryLogger
        {
            wchar_t*      wCharBuffer       =nullptr;
            int           wCharBufferSize   =0;

            public:

                          VStudioUnitTestLogger();
                virtual  ~VStudioUnitTestLogger();

                virtual int   AddAcquirer( ThreadLock* newAcquirer );
                virtual int   RemoveAcquirer( ThreadLock* acquirer );

                virtual void logText( aworx::lox::core::Domain&     domain,     aworx::lox::Verbosity verbosity,
                                      aworx::AString&               msg,
                                      aworx::lox::core::ScopeInfo&  scope,      int                     lineNumber);

                virtual void notifyMultiLineOp (aworx::lib::enums::Phase )    {  }

        };
    #endif


    class ALIBUnitTesting : public aworx::lib::ReportWriter
    {
        protected:
            aworx::TString          domain;
            aworx::String           actTestName;
        public:
            bool                    AssertOnFailure= true;
            static aworx::String128 LastAutoSizes;
            static aworx::AString   GeneratedSamplesDir;

            // defaults to "docs/ALox.CPP/".
            // Set this to a suitable value in your bootstrap code, before using this class with
            // other projects!
            static aworx::String    GeneratedSamplesSearchDir;

        public:
            aworx::lox::Lox                              lox;
            aworx::lox::core::textlogger::TextLogger*    utl;

                     ALIBUnitTesting( const aworx::TString& domain,  const aworx::TString& testName);
            virtual ~ALIBUnitTesting();

            void Print (  const aworx::String& file, int line,  const aworx::String& func, aworx::Verbosity verbosity,  const aworx::TString& msg );
            void Failed(  const aworx::String& file, int line,  const aworx::String& func,                   aworx::AString& msg );
            void WriteResultFile(const aworx::String& name, const aworx::String& output, const aworx::String& doxyTag );

            virtual void NotifyActivation  ( aworx::Phase ) { }
            virtual void Report  (  const aworx::lib::Report::Message& msg );

            void EQ     ( const aworx::TString& file, int line,  const aworx::TString& func, int32_t          a,  int32_t           b );
            void EQ     ( const aworx::TString& file, int line,  const aworx::TString& func, uint32_t         a,  uint32_t          b );
            void EQ     ( const aworx::TString& file, int line,  const aworx::TString& func, int64_t          a,  int64_t           b );
            void EQ     ( const aworx::TString& file, int line,  const aworx::TString& func, uint64_t         a,  uint64_t          b );
            void EQ     ( const aworx::TString& file, int line,  const aworx::TString& func, int32_t          a,  int32_t           b,    int32_t     prec );
            void EQ     ( const aworx::TString& file, int line,  const aworx::TString& func, uint32_t         a,  uint32_t          b,    uint32_t    prec );
            void EQ     ( const aworx::TString& file, int line,  const aworx::TString& func, int64_t          a,  int64_t           b,    int64_t     prec );
            void EQ     ( const aworx::TString& file, int line,  const aworx::TString& func, uint64_t         a,  uint64_t          b,    uint64_t    prec );
            void EQ     ( const aworx::TString& file, int line,  const aworx::TString& func, double           a,  double            b );
            void EQ     ( const aworx::TString& file, int line,  const aworx::TString& func, double           a,  double            b,    double      prec );
            void EQ     ( const aworx::TString& file, int line,  const aworx::TString& func, const aworx::String&  a,  const aworx::String&   b );
            void EQ     ( const aworx::TString& file, int line,  const aworx::TString& func, const wchar_t*   a,  const wchar_t*    b );

            void ISTRUE ( const aworx::TString& file, int line,  const aworx::TString& func, bool cond );
            void ISFALSE( const aworx::TString& file, int line,  const aworx::TString& func, bool cond );
    };
}


#endif // HPP_ALIB_ALOX_UNIT_TESTS
