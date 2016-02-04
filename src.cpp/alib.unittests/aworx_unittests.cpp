// #################################################################################################
//  aworx - Unit Tests
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################

// This helper header defines some preprocessor macros, so that GTest and MSVC Unit Tests can
// live in the same cpp file.
// Before including this header, the prepro variable "TESTCLASSNAME" has to be defined

#include "alib/stdafx_alib.h"
#include "alib/strings/assubstring.hpp"
#include "alib/system/directory.hpp"
#include "alib/compatibility/std_iostream.hpp"

#include "aworx_unittests.hpp"

using namespace std;
using namespace aworx;
using namespace aworx::lib;
using namespace aworx::lib::enums;
using namespace aworx::lib::strings;
using namespace aworx::lib::system;
using namespace aworx::lox;
using namespace aworx::lox::loggers;

namespace ut_aworx {


// #################################################################################################
// Fields
// #################################################################################################
String128 ALIBUnitTesting::LastAutoSizes;
AString   ALIBUnitTesting::GeneratedSamplesDir;
String    ALIBUnitTesting::GeneratedSamplesSearchDir= "docs/ALox.CPP/";

// #################################################################################################
// Constructors/destructor
// #################################################################################################
ALIBUnitTesting::ALIBUnitTesting( const String& domain, const String& testName)
{
    this->domain=       domain;
    this->actTestName=  testName;

    #if defined ( ALIB_VSTUDIO )
        utl= new VStudioUnitTestLogger();
    #else
        utl= Lox::CreateConsoleLogger();
    #endif

    if ( LastAutoSizes.IsNotEmpty() )
    {
        utl->AutoSizes.Import( LastAutoSizes, CurrentData::Keep );
    }

    lox.AddLogger( utl );
    utl->SetDomain( lox.InternalDomain, Log::DomainLevel::WarningsAndErrors );

    lox.SetDomain( domain, Log::DomainLevel::All );

    origReportWriter=  Report::GetDefault().ReplaceReportWriter( this, false );
}

ALIBUnitTesting::~ALIBUnitTesting()
{
    lox.RemoveLogger( utl );
    LastAutoSizes.Clear();
    utl->AutoSizes.Export( LastAutoSizes );

    delete utl;
    Report::GetDefault().ReplaceReportWriter( origReportWriter, false );
};


// #################################################################################################
// Print
// #################################################################################################
void ALIBUnitTesting::Print( const String& file, int line, const String& func, int level, const TString& msg  )
{
    lox.AcquireAndSetCI(file, line, func);

             if ( level == 0 )  lox.Info    ( domain, msg );
        else if ( level == 1 )  lox.Warning ( domain, msg );
        else
                                lox.Error   ( domain, msg );

    lox.Release();
}

void ALIBUnitTesting::Failed( const String& file, int line, const String& func,           const TString& msg )
{
    Print( file, line, func, 2, msg );
    assert(!AssertOnFailure);
}

void ALIBUnitTesting::WriteResultFile(const String& name, const String& outputRaw, const String& doxyTag )
{
    AString output(outputRaw);
    int start= 0;
    for(;;)
    {
        start= output.IndexOf( "/home", start );
        if ( start < 0 )
            break;
        int end= output.IndexOf( "/ALox", start );
        ALIB_ASSERT_ERROR( end >0 && end - start < 25, "Error pruning home directory" );
        if (end < 0 )
            end= output.Length();
        output.Delete( start + 5, end - start - 5 );
        start++;
    }

    // if invoked the first time, search the right directory
    if ( GeneratedSamplesDir.IsNull() )
    {
        GeneratedSamplesDir= "";
        String128 testDir; testDir << "../" << GeneratedSamplesSearchDir;
        for( int depth= 0; depth < 10 ; depth++ )
        {
            if ( Directory::Exists( testDir ) )
            {
                GeneratedSamplesDir << testDir << "/generated/";
                GeneratedSamplesDir.SearchAndReplace( "//", "/" );
                Directory::Create( GeneratedSamplesDir );
                break;
            }
            testDir.InsertAt( "../", 0 );
        }
    }

    if ( GeneratedSamplesDir.IsNotNull() && GeneratedSamplesDir.IsEmpty() )
        return;

    String256 fileName( GeneratedSamplesDir );
    fileName._( name );
    ofstream outputFile;
    outputFile.open ( fileName.ToCString() );
    if ( doxyTag.IsNotEmpty() )
        outputFile << doxyTag <<endl;
    outputFile << output;
    if ( doxyTag.IsNotEmpty() )
        outputFile << doxyTag <<endl;
    outputFile.close();
}

// #################################################################################################
// Error/Warning
// #################################################################################################
#if defined( ALIB_DEBUG )
    void ALIBUnitTesting::Report  ( const Report::Message& msg ) {  Print( msg.File, msg.Line, msg.Func , msg.Type == 0 ? 2 : 1, msg.Contents );  }
#else
    void ALIBUnitTesting::Report  ( const Report::Message& msg ) {  Print( nullptr,0,nullptr,             msg.Type == 0 ? 2 : 1, msg.Contents );  }
#endif

#if defined ( ALIB_VSTUDIO )

    VStudioUnitTestLogger::VStudioUnitTestLogger()
    : MemoryLogger( "VSTUDIO_UNITTEST_CONSOLE" )
    {
        // prevent cutting off filenames
        MetaInfo->ConsumableSourcePathPrefix= "";
        wCharBuffer= new wchar_t[ wCharBufferSize= 512 ];
    }

    VStudioUnitTestLogger::~VStudioUnitTestLogger()
    {
        if ( wCharBuffer != nullptr )
            delete[] wCharBuffer;
    }

    void VStudioUnitTestLogger::doTextLog( const TString&       domain, Log::Level     level,
                                           AString&             msg,    int            indent,
                                           core::CallerInfo*    caller, int            lineNumber )

    {
        MemoryLogger::doTextLog( domain, level, msg, indent, caller, lineNumber );
        while( MemoryLog.ToWString( wCharBuffer, wCharBufferSize ) == -2 )
        {
            delete wCharBuffer;
            wCharBuffer= new wchar_t[ wCharBufferSize*= 2 ];
        }

        Microsoft::VisualStudio::CppUnitTestFramework::Logger::WriteMessage( wCharBuffer );
        MemoryLog.Clear();
    }
#endif


// #################################################################################################
// EQ
// #################################################################################################

#if defined( ALIB_GTEST )
    void ALIBUnitTesting::EQ( const TString& file, int line, const TString& func, int32_t        exp, int32_t         i )        { if (i!=exp)                          Failed(file,line,func,String128("UT Failure: Expected: \"") << exp << "\", \"" << i << "\" given."); EXPECT_EQ   ( exp, i            ); }
    void ALIBUnitTesting::EQ( const TString& file, int line, const TString& func, uint32_t       exp, uint32_t        i )        { if (i!=exp)                          Failed(file,line,func,String128("UT Failure: Expected: \"") << exp << "\", \"" << i << "\" given."); EXPECT_EQ   ( exp, i            ); }
    void ALIBUnitTesting::EQ( const TString& file, int line, const TString& func, int64_t        exp, int64_t         i )        { if (i!=exp)                          Failed(file,line,func,String128("UT Failure: Expected: \"") << exp << "\", \"" << i << "\" given."); EXPECT_EQ   ( exp, i            ); }
    void ALIBUnitTesting::EQ( const TString& file, int line, const TString& func, uint64_t       exp, uint64_t        i )        { if (i!=exp)                          Failed(file,line,func,String128("UT Failure: Expected: \"") << exp << "\", \"" << i << "\" given."); EXPECT_EQ   ( exp, i            ); }
    void ALIBUnitTesting::EQ( const TString& file, int line, const TString& func, int32_t        exp, int32_t  i, int32_t   p )  { if ((i < exp ? exp-i : i-exp) > p)   Failed(file,line,func,String128("UT Failure: Expected: \"") << exp << "\", \"" << i << "\" given."); EXPECT_NEAR ( exp, i, p         ); }
    void ALIBUnitTesting::EQ( const TString& file, int line, const TString& func, uint32_t       exp, uint32_t i, uint32_t  p )  { if ((i < exp ? exp-i : i-exp) > p)   Failed(file,line,func,String128("UT Failure: Expected: \"") << exp << "\", \"" << i << "\" given."); EXPECT_NEAR ( exp, i, p         ); }
    void ALIBUnitTesting::EQ( const TString& file, int line, const TString& func, int64_t        exp, int64_t  i, int64_t   p )  { if ((i < exp ? exp-i : i-exp) > p)   Failed(file,line,func,String128("UT Failure: Expected: \"") << exp << "\", \"" << i << "\" given."); EXPECT_NEAR ( exp, i, p         ); }
    void ALIBUnitTesting::EQ( const TString& file, int line, const TString& func, uint64_t       exp, uint64_t i, uint64_t  p )  { if ((i < exp ? exp-i : i-exp) > p)   Failed(file,line,func,String128("UT Failure: Expected: \"") << exp << "\", \"" << i << "\" given."); EXPECT_NEAR ( exp, i, p         ); }
    void ALIBUnitTesting::EQ( const TString& file, int line, const TString& func, double         exp, double          d )        { if (d!=exp)                          Failed(file,line,func,String128("UT Failure: Expected: \"") << exp << "\", \"" << d << "\" given."); EXPECT_EQ   ( exp, d            ); }
    void ALIBUnitTesting::EQ( const TString& file, int line, const TString& func, const String&  exp, const String&   s )        { if (!exp.Equals(s))                  Failed(file,line,func,String128("UT Failure: Expected: \"") << exp << "\", \"" << s << "\" given."); EXPECT_TRUE ( exp.Equals(s)     ); }
    void ALIBUnitTesting::EQ( const TString& file, int line, const TString& func, const wchar_t* exp, const wchar_t*  s )        { if (wcscmp(exp,s)!=0)                Failed(file,line,func,String128("UT Failure: Expected: \"") << exp << "\", \"" << s << "\" given."); EXPECT_STREQ( exp, s            ); }
    void ALIBUnitTesting::EQ( const TString& file, int line, const TString& func, double    exp, double d,   double   p )        { if ((d < exp ? exp-d : d-exp) > p)   Failed(file,line,func,String128("UT Failure: Expected: \"") << exp << "\", \"" << d << "\" given."); EXPECT_NEAR ( exp, d, p         ); }

    void ALIBUnitTesting::ISTRUE ( const TString& file, int line, const TString& func, bool cond )                               { if (  !cond )                        Failed(file,line,func,"UT Failure: expected true, false given."                               ); EXPECT_TRUE ( cond              ); }
    void ALIBUnitTesting::ISFALSE( const TString& file, int line, const TString& func, bool cond )                               { if (  cond )                         Failed(file,line,func,"UT Failure: expected false, true given."                               ); EXPECT_FALSE( cond              ); }

#elif defined ( ALIB_VSTUDIO )
    void ALIBUnitTesting::EQ     ( const TString& file, int line, const TString& func, int32_t        i, int32_t         exp )  { if (i!=exp)                                              Failed(file,line,func,String128("UT Failure: Expected: \"") << exp << "\", \"" << i << "\" given."); Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual( exp, i ); }
    void ALIBUnitTesting::EQ     ( const TString& file, int line, const TString& func, uint32_t       i, uint32_t        exp )  { if (i!=exp)                                              Failed(file,line,func,String128("UT Failure: Expected: \"") << exp << "\", \"" << i << "\" given."); Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual( exp, i ); }
    void ALIBUnitTesting::EQ     ( const TString& file, int line, const TString& func, int64_t        i, int64_t         exp )  { bool c= i!=exp;                                   if(!c) Failed(file,line,func,String128("UT Failure: Expected: \"") << exp << "\", \"" << i << "\" given."); Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual( exp, i, NULL, NULL ); }
    void ALIBUnitTesting::EQ     ( const TString& file, int line, const TString& func, uint64_t       i, uint64_t        exp )  { bool c= i!=exp;                                   if(!c) Failed(file,line,func,String128("UT Failure: Expected: \"") << exp << "\", \"" << i << "\" given."); Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsTrue  ( c      ); }
    void ALIBUnitTesting::EQ     ( const TString& file, int line, const TString& func, int32_t  i, int32_t  exp, int32_t   p )  { bool c= (i < exp ? exp-i : i-exp) <= p;           if(!c) Failed(file,line,func,String128("UT Failure: Expected: \"") << exp << "\", \"" << i << "\" given."); Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsTrue  ( c      ); }
    void ALIBUnitTesting::EQ     ( const TString& file, int line, const TString& func, uint32_t i, uint32_t exp, uint32_t  p )  { bool c= (i < exp ? exp-i : i-exp) <= p;           if(!c) Failed(file,line,func,String128("UT Failure: Expected: \"") << exp << "\", \"" << i << "\" given."); Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsTrue  ( c      ); }
    void ALIBUnitTesting::EQ     ( const TString& file, int line, const TString& func, int64_t  i, int64_t  exp, int64_t   p )  { bool c= (i < exp ? exp-i : i-exp) <= p;           if(!c) Failed(file,line,func,String128("UT Failure: Expected: \"") << exp << "\", \"" << i << "\" given."); Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsTrue  ( c      ); }
    void ALIBUnitTesting::EQ     ( const TString& file, int line, const TString& func, uint64_t i, uint64_t exp, uint64_t  p )  { bool c= (i < exp ? exp-i : i-exp) <= p;           if(!c) Failed(file,line,func,String128("UT Failure: Expected: \"") << exp << "\", \"" << i << "\" given."); Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsTrue  ( c      ); }
    void ALIBUnitTesting::EQ     ( const TString& file, int line, const TString& func, double         d, double          exp )  { if (d!=exp)                                              Failed(file,line,func,String128("UT Failure: Expected: \"") << exp << "\", \"" << d << "\" given."); Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual( exp, d ); }
    void ALIBUnitTesting::EQ     ( const TString& file, int line, const TString& func, const String&  s, const String&   exp )  { if (!exp.Equals(s))                                      Failed(file,line,func,String128("UT Failure: Expected: \"") << exp << "\", \"" << s << "\" given."); Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsTrue  ( exp.Equals(s) ); }
    void ALIBUnitTesting::EQ     ( const TString& file, int line, const TString& func, double  d,   double  exp,    double  p)  { bool c= (d < exp ? exp-d : d-exp) <= p;           if(!c) Failed(file,line,func,String128("UT Failure: Expected: \"") << exp << "\", \"" << d << "\" given."); Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsTrue  ( c      ); }
    void ALIBUnitTesting::EQ     ( const TString& file, int line, const TString& func, const wchar_t* s, const wchar_t*  exp )  { bool c= wcscmp( s, exp                      )==0; if(!c) Failed(file,line,func,      "UT Failure: Differences in wide characters."                     ); Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsTrue  ( c      ); }

    void ALIBUnitTesting::ISTRUE ( const TString& file, int line, const TString& func, bool c )                            {                                                   if(!c) Failed(file,line,func,"UT Failure"); Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsTrue  ( c      ); }
    void ALIBUnitTesting::ISFALSE( const TString& file, int line, const TString& func, bool c )                            {                                                   if( c) Failed(file,line,func,"UT Failure"); Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsFalse ( c      ); }

#else
    #pragma message ("Unknown Testing platform in: " __FILE__ )
#endif


}//namespace


#if defined ( ALIB_VSTUDIO )
namespace Microsoft {  namespace VisualStudio {   namespace CppUnitTestFramework     {
            template<> std::wstring ToString<int64_t>(const int64_t& t)
            {
                wstringstream convert;
                convert << t;
                return convert.str();
            }
}}}
#endif
