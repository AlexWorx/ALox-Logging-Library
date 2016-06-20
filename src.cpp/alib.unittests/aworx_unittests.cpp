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
#include "alib/strings/substring.hpp"
#include "alib/system/directory.hpp"
#include "alib/compatibility/std_iostream.hpp"

#include "aworx_unittests.hpp"

using namespace std;
using namespace aworx;
using namespace aworx::lox::core;

namespace ut_aworx {


// #################################################################################################
// Fields
// #################################################################################################
#if defined(_MSC_VER)
    #pragma warning( push )
    #pragma warning( disable : 4592 )
#endif
String128 ALIBUnitTesting::LastAutoSizes;
AString   ALIBUnitTesting::GeneratedSamplesDir;
String    ALIBUnitTesting::GeneratedSamplesSearchDir= "docs/ALox.CPP/";
#if defined(_MSC_VER)
    #pragma warning( pop )
#endif

// #################################################################################################
// Constructors/destructor
// #################################################################################################
ALIBUnitTesting::ALIBUnitTesting( const TString& domain, const TString& testName)
: lox( "UTLox", false )
{
    this->domain=       domain;
    this->actTestName=  testName;

    Log_SetSourcePathTrimRule( "*/src.cpp/", Inclusion::Include );

    #if defined ( ALIB_VSTUDIO )
        utl= new VStudioUnitTestLogger();
    #else
//! [IDESetupGuide_ADD_ABSOLUTE_PATH]
        utl= Lox::CreateConsoleLogger();

        // if QTCreator with QMake was detected, then use absolute paths
        if( utl->MetaInfo->Format.IndexOf( "   Loc:" ) >= 0  )
        {
            Directory moduleName( Directory::SpecialFolder::Module );
            int idx= moduleName.Path.IndexOf( "/ALox/" );
            if ( idx > 0 )
            {
                moduleName.Path.SetLength( idx + 5 );
                lox.ClearSourcePathTrimRules( Inclusion::Include, false );
                lox.SetSourcePathTrimRule( "*/src.cpp/", Inclusion::Exclude, 0, Case::Ignore, Inclusion::Include,
                                           moduleName.Path  );
            }
        }
//! [IDESetupGuide_ADD_ABSOLUTE_PATH]
    #endif

    if ( LastAutoSizes.IsNotEmpty() )
    {
        utl->AutoSizes.Import( LastAutoSizes, CurrentData::Keep );
    }

    lox.SetScopeInfo(ALIB_SRC_INFO_PARAMS);
        lox.SetVerbosity( utl, Verbosity::Verbose, domain);
        lox.SetVerbosity( utl, Verbosity::Warning, ALox::InternalDomains );
        lox.SetPrefix( ESC::BG_GRAY, "/" );
    lox.Release();

    lib::Report::GetDefault().PushWriter( this );

}

ALIBUnitTesting::~ALIBUnitTesting()
{
    lox.SetScopeInfo(ALIB_SRC_INFO_PARAMS);
        lox.RemoveLogger( utl );
    lox.Release();

    LastAutoSizes.Clear();
    utl->AutoSizes.Export( LastAutoSizes );

    // clean debug lox and ALox
    Log_Prune( ALox::Reset() );

    // check if ALib smartlock for std I/O was released properly
    this->EQ (__FILE__, __LINE__, actTestName,     0, ALIB::StdOutputStreamsLock.CntAcquirers() );
    this->EQ (__FILE__, __LINE__, actTestName,     0, ((ThreadLock&)ALIB::StdOutputStreamsLock).DbgCountAcquirements() );

    lib::Report::GetDefault().PopWriter( this );
    delete utl;
}


// #################################################################################################
// Print
// #################################################################################################
void ALIBUnitTesting::Print( const String& file, int line, const String&, Verbosity verbosity, const TString& msg  )
{
    lox.SetScopeInfo(file, line, actTestName);

        lox.Entry( domain, verbosity, msg );

    lox.Release();
}

void ALIBUnitTesting::Failed( const String& file, int line, const String& func,  AString& msg )
{
    msg.InsertAt( "UT Failure: Expected: ", 0 );
    Print( file, line, func, aworx::Verbosity::Error, msg );
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
    void ALIBUnitTesting::Report  ( const lib::Report::Message& msg )
    {
            lox.SetScopeInfo(msg.File, msg.Line, msg.Func);

                lox.Entry( String16() << ALox::InternalDomains << "UT_REPORT",
                           msg.Type == 0 ? Verbosity::Error    :
                           msg.Type == 1 ? Verbosity::Warning  :
                           msg.Type == 2 ? Verbosity::Info     :
                                           Verbosity::Verbose,
                           msg.Contents                                          );

            lox.Release();
    }

#if defined ( ALIB_VSTUDIO )

    VStudioUnitTestLogger::VStudioUnitTestLogger()
    : MemoryLogger( "VSTUDIO_UNITTEST_CONSOLE" )
    {
        // prevent cutting off filenames
        MetaInfo->Format.SearchAndReplace( "%Sp", "%SP" );
        wCharBuffer= new wchar_t[ wCharBufferSize= 512 ];
    }

    VStudioUnitTestLogger::~VStudioUnitTestLogger()
    {
        if ( wCharBuffer != nullptr )
            delete[] wCharBuffer;
    }

    int   VStudioUnitTestLogger::AddAcquirer( ThreadLock* newAcquirer )
    {
        // when added to a lox, we register as std output stream user. This would not be necessary, because
        // we do not write to the std output stream. But in other environments, the unit test logger does
        // so, and therefore, if we dont do it, the unit test which tests the whole concept would fail.
         ALIB::StdOutputStreamsLock.AddAcquirer( this );

        // call parents' implementation
        return Logger::AddAcquirer( newAcquirer );
    }

    int   VStudioUnitTestLogger::RemoveAcquirer( ThreadLock* acquirer )
    {
         ALIB::StdOutputStreamsLock.RemoveAcquirer( this );

        // call parents' implementation
        return Logger::RemoveAcquirer( acquirer );
    }



    void VStudioUnitTestLogger::logText( Domain&       domain,
                                         Verbosity     verbosity,
                                         AString&      msg,
                                         ScopeInfo&    scope,
                                         int           lineNumber )

    {
        MemoryLogger::logText( domain, verbosity, msg, scope, lineNumber );
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
    void ALIBUnitTesting::EQ( const TString& file, int line, const TString& func, int32_t        exp, int32_t         i )        { if (i!=exp)                          Failed(file,line,func,String128("\"") << exp << "\", \"" << i << "\" given."); EXPECT_EQ   ( exp, i            ); }
    void ALIBUnitTesting::EQ( const TString& file, int line, const TString& func, uint32_t       exp, uint32_t        i )        { if (i!=exp)                          Failed(file,line,func,String128("\"") << exp << "\", \"" << i << "\" given."); EXPECT_EQ   ( exp, i            ); }
    void ALIBUnitTesting::EQ( const TString& file, int line, const TString& func, int64_t        exp, int64_t         i )        { if (i!=exp)                          Failed(file,line,func,String128("\"") << exp << "\", \"" << i << "\" given."); EXPECT_EQ   ( exp, i            ); }
    void ALIBUnitTesting::EQ( const TString& file, int line, const TString& func, uint64_t       exp, uint64_t        i )        { if (i!=exp)                          Failed(file,line,func,String128("\"") << exp << "\", \"" << i << "\" given."); EXPECT_EQ   ( exp, i            ); }
    void ALIBUnitTesting::EQ( const TString& file, int line, const TString& func, int32_t        exp, int32_t  i, int32_t   p )  { if ((i < exp ? exp-i : i-exp) > p)   Failed(file,line,func,String128("\"") << exp << "\", \"" << i << "\" given."); EXPECT_NEAR ( exp, i, p         ); }
    void ALIBUnitTesting::EQ( const TString& file, int line, const TString& func, uint32_t       exp, uint32_t i, uint32_t  p )  { if ((i < exp ? exp-i : i-exp) > p)   Failed(file,line,func,String128("\"") << exp << "\", \"" << i << "\" given."); EXPECT_NEAR ( exp, i, p         ); }
    void ALIBUnitTesting::EQ( const TString& file, int line, const TString& func, int64_t        exp, int64_t  i, int64_t   p )  { if ((i < exp ? exp-i : i-exp) > p)   Failed(file,line,func,String128("\"") << exp << "\", \"" << i << "\" given."); EXPECT_NEAR ( exp, i, p         ); }
    void ALIBUnitTesting::EQ( const TString& file, int line, const TString& func, uint64_t       exp, uint64_t i, uint64_t  p )  { if ((i < exp ? exp-i : i-exp) > p)   Failed(file,line,func,String128("\"") << exp << "\", \"" << i << "\" given."); EXPECT_NEAR ( exp, i, p         ); }
    void ALIBUnitTesting::EQ( const TString& file, int line, const TString& func, double         exp, double          d )        { if (d!=exp)                          Failed(file,line,func,String128("\"") << exp << "\", \"" << d << "\" given."); EXPECT_EQ   ( exp, d            ); }
    void ALIBUnitTesting::EQ( const TString& file, int line, const TString& func, const String&  exp, const String&   s )        { if (!exp.Equals(s))                  Failed(file,line,func,String128("\"") << exp << "\", \"" << s << "\" given."); EXPECT_TRUE ( exp.Equals(s)     ); }
    void ALIBUnitTesting::EQ( const TString& file, int line, const TString& func, const wchar_t* exp, const wchar_t*  s )        { if (wcscmp(exp,s)!=0)                Failed(file,line,func,String128("\"") << exp << "\", \"" << s << "\" given."); EXPECT_STREQ( exp, s            ); }
    void ALIBUnitTesting::EQ( const TString& file, int line, const TString& func, double    exp, double d,   double   p )        { if ((d < exp ? exp-d : d-exp) > p)   Failed(file,line,func,String128("\"") << exp << "\", \"" << d << "\" given."); EXPECT_NEAR ( exp, d, p         ); }

    void ALIBUnitTesting::ISTRUE ( const TString& file, int line, const TString& func, bool cond )                               { if (  !cond )                        Failed(file,line,func,String128() << "true"                                     ); EXPECT_TRUE ( cond              ); }
    void ALIBUnitTesting::ISFALSE( const TString& file, int line, const TString& func, bool cond )                               { if (  cond )                         Failed(file,line,func,String128() << "false"                                    ); EXPECT_FALSE( cond              ); }

#elif defined ( ALIB_VSTUDIO )
    void ALIBUnitTesting::EQ     ( const TString& file, int line, const TString& func, int32_t        i, int32_t         exp )  { if (i!=exp)                                              Failed(file,line,func,String128("\"") << exp << "\", \"" << i << "\" given.");    Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual( exp, i ); }
    void ALIBUnitTesting::EQ     ( const TString& file, int line, const TString& func, uint32_t       i, uint32_t        exp )  { if (i!=exp)                                              Failed(file,line,func,String128("\"") << exp << "\", \"" << i << "\" given.");    Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual( exp, i ); }
    void ALIBUnitTesting::EQ     ( const TString& file, int line, const TString& func, int64_t        i, int64_t         exp )  { bool c= i!=exp;                                   if(!c) Failed(file,line,func,String128("\"") << exp << "\", \"" << i << "\" given.");    Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual( exp, i, NULL, NULL ); }
    void ALIBUnitTesting::EQ     ( const TString& file, int line, const TString& func, uint64_t       i, uint64_t        exp )  { bool c= i!=exp;                                   if(!c) Failed(file,line,func,String128("\"") << exp << "\", \"" << i << "\" given.");    Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsTrue  ( c      ); }
    void ALIBUnitTesting::EQ     ( const TString& file, int line, const TString& func, int32_t  i, int32_t  exp, int32_t   p )  { bool c= (i < exp ? exp-i : i-exp) <= p;           if(!c) Failed(file,line,func,String128("\"") << exp << "\", \"" << i << "\" given.");    Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsTrue  ( c      ); }
    void ALIBUnitTesting::EQ     ( const TString& file, int line, const TString& func, uint32_t i, uint32_t exp, uint32_t  p )  { bool c= (i < exp ? exp-i : i-exp) <= p;           if(!c) Failed(file,line,func,String128("\"") << exp << "\", \"" << i << "\" given.");    Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsTrue  ( c      ); }
    void ALIBUnitTesting::EQ     ( const TString& file, int line, const TString& func, int64_t  i, int64_t  exp, int64_t   p )  { bool c= (i < exp ? exp-i : i-exp) <= p;           if(!c) Failed(file,line,func,String128("\"") << exp << "\", \"" << i << "\" given.");    Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsTrue  ( c      ); }
    void ALIBUnitTesting::EQ     ( const TString& file, int line, const TString& func, uint64_t i, uint64_t exp, uint64_t  p )  { bool c= (i < exp ? exp-i : i-exp) <= p;           if(!c) Failed(file,line,func,String128("\"") << exp << "\", \"" << i << "\" given.");    Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsTrue  ( c      ); }
    void ALIBUnitTesting::EQ     ( const TString& file, int line, const TString& func, double         d, double          exp )  { if (d!=exp)                                              Failed(file,line,func,String128("\"") << exp << "\", \"" << d << "\" given.");    Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual( exp, d ); }
    void ALIBUnitTesting::EQ     ( const TString& file, int line, const TString& func, const String&  s, const String&   exp )  { if (!exp.Equals(s))                                      Failed(file,line,func,String128("\"") << exp << "\", \"" << s << "\" given.");    Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsTrue  ( exp.Equals(s) ); }
    void ALIBUnitTesting::EQ     ( const TString& file, int line, const TString& func, double  d,   double  exp,    double  p)  { bool c= (d < exp ? exp-d : d-exp) <= p;           if(!c) Failed(file,line,func,String128("\"") << exp << "\", \"" << d << "\" given.");    Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsTrue  ( c      ); }
    void ALIBUnitTesting::EQ     ( const TString& file, int line, const TString& func, const wchar_t* s, const wchar_t*  exp )  { bool c= wcscmp( s, exp                      )==0; if(!c) Failed(file,line,func,String128() << "UT Failure: Differences in wchar string."); Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsTrue  ( c      ); }

    void ALIBUnitTesting::ISTRUE ( const TString& file, int line, const TString& func, bool c )                                 {                                                   if(!c) Failed(file,line,func,String128() << "true"                                 );    Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsTrue  ( c      ); }
    void ALIBUnitTesting::ISFALSE( const TString& file, int line, const TString& func, bool c )                                 {                                                   if( c) Failed(file,line,func,String128() << "false"                                );    Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsFalse ( c      ); }

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
