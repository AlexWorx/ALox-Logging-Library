// #################################################################################################
//  aworx - Unit Tests
//
//  Copyright 2013-2018 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################

#include "alox/alox.hpp"
#include "alib/strings/substring.hpp"
#include "alib/system/environment.hpp"
#include "alib/compatibility/std_iostream.hpp"

#include "aworx_unittests.hpp"

#if defined(__clang__)
    #pragma message "Clang Compiler (not a warning, just for an information)"
#elif defined(__GNUC__)
    #pragma message "GNU Compiler (not a warning, just for an information)"
#elif defined(_MSC_VER)
    #pragma message ("MS Compiler (not a warning, just for an information)")
#endif


using namespace std;
using namespace aworx;
using namespace aworx::lox::core;

namespace ut_aworx {


// #################################################################################################
// Fields
// #################################################################################################
String128 AWorxUnitTesting::LastAutoSizes;
AString   AWorxUnitTesting::GeneratedSamplesDir;
String    AWorxUnitTesting::GeneratedSamplesSearchDir= "docs/ALox.CPP/";
AString   AWorxUnitTesting::CustomMetaInfoFormat;


// #################################################################################################
// Constructors/destructor
// #################################################################################################
AWorxUnitTesting::AWorxUnitTesting( const TString& pdomain, const TString& testName)
: initializer(lox::ALOX.Init())
, lox( "UTLox", false )
{
    this->Domain=  pdomain;
    this->Domain.ToUpper();
    this->ActTestName=  testName;

    Log_SetSourcePathTrimRule( "*/src.cpp/", Inclusion::Include );

    #if !ALIB_GTEST
        utl= new UTVStudioLogger();
    #elif defined(ALOX_UNITTESTS_QMAKE_BUILD)
        {
            utl= new ConsoleLogger();

            // if QTCreator/ QMake was detected, then use absolute paths
            utl->MetaInfo->Format= "   Loc: [%SP/%SF(%SL)]:%A3%SM %A3{%TC +%TL}{%tN}{%D}%A1#%#: ";
            utl->MetaInfo->VerbosityError=   "{ERR}";
            utl->MetaInfo->VerbosityWarning= "{WRN}";
            utl->MetaInfo->VerbosityInfo=    "     ";
            utl->MetaInfo->VerbosityVerbose= "{***}";

            Directory moduleName( Directory::SpecialFolder::Module );
            integer idx= moduleName.Path.IndexOf( "/ALox/" );
            if ( idx > 0 )
            {
                moduleName.Path.SetLength( idx + 5 );
                lox.ClearSourcePathTrimRules( Reach::Global, false );
                lox.SetSourcePathTrimRule( "*/src.cpp/", Inclusion::Exclude, 0, Case::Ignore, moduleName.Path,
                                           Reach::Global  );
            }

            utl->SetReplacement( "[", "{" );
            utl->SetReplacement( "]", "}" );
        }
    #else
        utl= Lox::CreateConsoleLogger();

        // check if we are in CLion. Here it is important to switch off the use of dark/light colors
        if( utl->GetName().Equals("ANSI_CONSOLE") )
        {
            AString classPath;
            aworx::lib::system::GetEnvironmentVariable( "CLASSPATH", classPath );
            if ( classPath.IndexOf<Case::Ignore>("CLion", 0) >= 0 )
                dynamic_cast<AnsiConsoleLogger*>(utl)->UseLightColors= AnsiLogger::LightColorUsage::Never;
        }
    #endif

    if ( CustomMetaInfoFormat.IsNotEmpty() )
        utl->MetaInfo->Format= CustomMetaInfoFormat;

    if ( LastAutoSizes.IsNotEmpty() )
        utl->AutoSizes.Import( LastAutoSizes, CurrentData::Keep );

    lox.Acquire(ALIB_SRCPOS);
        lox.SetVerbosity( utl, Verbosity::Verbose, "/" );
        lox.SetVerbosity( utl, Verbosity::Verbose, Domain);
        lox.SetVerbosity( utl, Verbosity::Warning, ALox::InternalDomains );
        lox.SetVerbosity( utl, Verbosity::Info,    String64() << ALox::InternalDomains << "UT_REPORT" );
    lox.Release();

    lib::lang::Report::GetDefault().PushWriter( this );
}

AWorxUnitTesting::~AWorxUnitTesting()
{
    lox.Acquire(ALIB_SRCPOS);
        lox.RemoveLogger( utl );
    lox.Release();

    LastAutoSizes.Clear();
    utl->AutoSizes.Export( LastAutoSizes );

    // clean debug lox and ALox
    Log_Prune( lox::ALOX.Reset() );

    lib::ALIB.Config->GetPluginTypeSafe<aworx::InMemoryPlugin>( Priorities::DefaultValues   )->Reset();
    lib::ALIB.Config->GetPluginTypeSafe<aworx::InMemoryPlugin>( Priorities::ProtectedValues )->Reset();
    if( lox::ALOX.Config != lib::ALIB.Config )
    {
        lox::ALOX.Config->GetPluginTypeSafe<aworx::InMemoryPlugin>( Priorities::DefaultValues   )->Reset();
        lox::ALOX.Config->GetPluginTypeSafe<aworx::InMemoryPlugin>( Priorities::ProtectedValues )->Reset();
    }



    // check if ALib SmartLock for std I/O was released properly
    this->EQ (__FILE__, __LINE__, 0, lib::ALIB.StdOutputStreamsLock.CntAcquirers() );
    this->EQ (__FILE__, __LINE__, 0, lib::ALIB.StdOutputStreamsLock.DbgCountAcquirements() );

    lib::lang::Report::GetDefault().PopWriter( this );
    delete utl;
}


// #################################################################################################
// Print
// #################################################################################################

void AWorxUnitTesting::Failed( const String& file, int line, const Box& exp, const Box& given )
{
    Print( file, line, aworx::Verbosity::Error, "UT Failure: Expected: \"{!ESC}\"\\n"
                                                "               given: \"{!ESC}\"", exp, given );
    assert(!AssertOnFailure);
}

void AWorxUnitTesting::WriteResultFile(const String& name, const String& outputRaw, const String& doxyTag )
{
    AString output(outputRaw);
    integer start= 0;
    for(;;)
    {
        start= output.IndexOf( "/home", start );
        if ( start < 0 )
            break;
        integer end= output.IndexOf( "/ALox", start );
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
    {
        ALIB_ERROR( "Samples directory \"/generated\" not found in upward path search" )
        return;
    }

    String256 fileName( GeneratedSamplesDir );
    fileName._( name );
    ofstream outputFile;
    outputFile.open ( fileName.ToCString() );
    if ( doxyTag.IsNotEmpty() )   outputFile << doxyTag <<endl;
    outputFile << output;
    if ( doxyTag.IsNotEmpty() )   outputFile << doxyTag <<endl;
    outputFile.close();
}

// #################################################################################################
// Error/Warning
// #################################################################################################
void AWorxUnitTesting::Report  ( const lib::lang::Report::Message& msg )
{
        lox.Acquire(msg.File, msg.Line, msg.Func);
            lox.GetLogableContainer().Add( static_cast<const Boxes&>( msg ) );
            lox.Entry( String16() << ALox::InternalDomains << "UT_REPORT",
                       msg.Type == 0 ? Verbosity::Error    :
                       msg.Type == 1 ? Verbosity::Warning  :
                       msg.Type == 2 ? Verbosity::Info     :
                                       Verbosity::Verbose                         );

        lox.Release();
}

#if !ALIB_GTEST

    UTVStudioLogger::UTVStudioLogger()
    : MemoryLogger( "VSTUDIO_UNITTEST_CONSOLE" )
    {
        // prevent cutting off filenames
        MetaInfo->Format.SearchAndReplace( "%Sp", "%SP" );
        wCharBuffer= new wchar_t[ wCharBufferSize= 512 ];
    }

    UTVStudioLogger::~UTVStudioLogger()
    {
        if ( wCharBuffer != nullptr )
            delete[] wCharBuffer;
    }

    int   UTVStudioLogger::AddAcquirer( ThreadLock* newAcquirer )
    {
        // when added to a lox, we register as std output stream user. This would not be necessary, because
        // we do not write to the std output stream. But in other environments, the unit test logger does
        // so, and therefore, if we dont do it, the unit test which tests the whole concept would fail.
         lib::ALIB.StdOutputStreamsLock.AddAcquirer( this );

        // call parents' implementation
        return Logger::AddAcquirer( newAcquirer );
    }

    int   UTVStudioLogger::RemoveAcquirer( ThreadLock* acquirer )
    {
         lib::ALIB.StdOutputStreamsLock.RemoveAcquirer( this );

        // call parents' implementation
        return Logger::RemoveAcquirer( acquirer );
    }



    void UTVStudioLogger::logText( Domain&       domain,
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

#if ALIB_GTEST
    void AWorxUnitTesting::EQ     ( const TString& file, int line, double         exp, double    d )                         { double p= 0.00000000000001; if ((d < exp ? exp-d : d-exp) > p)
                                                                                                                                                                    Failed(file,line,exp,d); EXPECT_NEAR ( exp, d, p     ); }
    void AWorxUnitTesting::EQ     ( const TString& file, int line, const String&  exp, const String&   s )                   { if (!exp.Equals(s))                  Failed(file,line,exp,s); EXPECT_TRUE ( exp.Equals(s) ); }
    void AWorxUnitTesting::EQ     ( const TString& file, int line, wchar_t*       exp, wchar_t*        s )                   { if (wcscmp(exp,s)!=0)                Failed(file,line,exp,s); EXPECT_STREQ( exp, s        ); }

    void AWorxUnitTesting::IsTrue ( const TString& file, int line, bool cond )                                               {                        if (!cond )   Failed(file,line, true , false ); EXPECT_TRUE ( cond ); }
    void AWorxUnitTesting::IsFalse( const TString& file, int line, bool cond )                                               {                        if (cond )    Failed(file,line, false, true  ); EXPECT_FALSE( cond ); }

#elif defined(_WIN32)
    void AWorxUnitTesting::EQ     ( const TString& file, int line, double         exp, double          v )                   { if (v!=exp)                                      Failed(file,line,exp,v);    Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual( exp, v ); }
    void AWorxUnitTesting::EQ     ( const TString& file, int line, const String&  exp, const String&   v )                   { if (!exp.Equals(v))                              Failed(file,line,exp,v);    Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsTrue  ( exp.Equals(v) ); }
    void AWorxUnitTesting::EQ     ( const TString& file, int line, wchar_t*       exp,       wchar_t*  v )                   { bool c= wcscmp( v, exp )==0;              if(!c) Failed(file,line,"","Differences in wchar string."); Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsTrue  ( c      ); }

    void AWorxUnitTesting::IsTrue ( const TString& file, int line, bool c )                                                  {                                           if(!c) Failed(file,line,true ,false);Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsTrue  ( c      ); }
    void AWorxUnitTesting::IsFalse( const TString& file, int line, bool c )                                                  {                                           if( c) Failed(file,line,false,true );Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsFalse ( c      ); }

#else
    #pragma message ("Unknown Testing platform in: " __FILE__ )
#endif


}//namespace


#if !ALIB_GTEST
namespace Microsoft {  namespace VisualStudio {   namespace CppUnitTestFramework     {
            template<> std::wstring ToString<int64_t>(const int64_t& t)
            {
                wstringstream convert;
                convert << t;
                return convert.str();
            }
}}}
#endif
