// #################################################################################################
//  aworx::lox::core - ALox Logging Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
#include "alib/stdafx_alib.h"

#if !defined (HPP_ALOX)
    #include "alox/alox.hpp"
#endif

#include <iostream>
#include <iomanip>


// check compiler symbols, give warning once (therefore not in HPP)
#if !defined( ALOX_DBG_LOG ) && defined( ALOX_DBG_LOG_CI_ON )
    #warning "ALox compiler symbol mismatch: ALOX_DBG_LOG_CI_ON given while ALOX_DBG_LOG is undefined"
#endif
#if !defined( ALOX_REL_LOG ) && defined( ALOX_REL_LOG_CI_ON )
    #warning "ALox compiler symbol mismatch: ALOX_REL_LOG_CI_ON given while ALOX_REL_LOG is undefined"
#endif


using namespace std;
using namespace aworx;
namespace aworx { namespace lox {


// #################################################################################################
// Version and check flags
// #################################################################################################
const int            ALox::Version=                                           ALIB_VERSION_VERYFIER;
const int            ALox::Revision=                                                              1;
const uint32_t       ALox::CompilationFlags=                            ALOX_COMPATIBILITY_VERYFIER;
const uint32_t       ALox::ALibCompilationFlags=                        ALIB_COMPATIBILITY_VERYFIER;
std::pair <const char*, uint32_t> ALox::CompilationFlagMeanings[]=
{
    { "ALOX_DBG_LOG"            , ALOX_DBG_LOG_VFYBIT         },
    { "ALOX_DBG_LOG_CI"         , ALOX_DBG_LOG_CI_VFYBIT      },
    { "ALOX_REL_LOG"            , ALOX_REL_LOG_VFYBIT         },
    { "ALOX_REL_LOG_CI"         , ALOX_REL_LOG_CI_VFYBIT      },
};

// #################################################################################################
// ALoxReportWriter
// #################################################################################################

ALoxReportWriter::ALoxReportWriter ( Lox* lox )
{
    this->lox= lox;

    #if defined( ALIB_DEBUG )
        lox->Acquire( ALIB_DBG_SRC_INFO_PARAMS );

            lox->Verbose( ALox::InternalDomains, "ALoxReportWriter set" );

        lox->Release ();
    #else

    #endif
}

void ALoxReportWriter::Report( const lib::Report::Message& report )
{
    #if defined( ALIB_DEBUG )
        lox->Acquire( report.File, report.Line, report.Func );

            lox->Entry( ALoxReportWriter::LogDomain(),
                        report.Type == 0 ? Verbosity::Error   :
                        report.Type == 1 ? Verbosity::Warning :
                        report.Type == 2 ? Verbosity::Info    :
                                           Verbosity::Verbose,
                        &report.Contents, 0 );

        lox->Release ();
    #else
        (void) report;
    #endif
}

#if defined(_MSC_VER)
    #pragma warning( push )
    #pragma warning( disable : 4592 )
#endif
String16 ALoxReportWriter::reportDomain;
#if defined(_MSC_VER)
    #pragma warning( pop )
#endif

String& ALoxReportWriter::LogDomain()
{
    if( reportDomain.IsEmpty() )
        reportDomain << ALox::InternalDomains << "REPORT";
    return reportDomain;
}

// #################################################################################################
// Compilation Flags
// #################################################################################################
bool ALox::VerifyCompilationFlags( uint32_t flags )
{
    if ( flags == ALox::CompilationFlags )
        return true;

    // dump out the flags
    cout << std::left << setw(25) <<  "Symbol" << '|' << setw(5) << " Lib" <<'|' << " Comp. Unit"  <<endl;
    for( auto& p : CompilationFlagMeanings )
    {
        cout << setw(25) <<  p.first << '|' << setw(5) << (flags                  & p.second  ? " On" : " Off")
                                     << "|" << setw(5) << (ALIB::CompilationFlags & p.second  ? " On" : " Off")
             << endl;
    }

    return false;
}

void ALox::checkLibraryVersions( int alibVersion, int aloxVersion, uint32_t flagsALib,  uint32_t flagsALox )
{
    if (ALIB::Version != alibVersion )
    {
        cout << "!!! Error in ALox library compilation: linked against wrong version of ALib" << endl;
        cout << "!!! ALib library version:  " << ALIB::Version << endl;
        cout << "!!! ALib included version: " << alibVersion   << endl;
        cout << "!!! Exiting with exit(-1)" << endl;
        exit(-1);
    }

    if (ALox::Version != aloxVersion )
    {
        cout << "!!! Error in ALox library compilation: linked against wrong version of ALox" << endl;
        cout << "!!! ALox library version:  " << ALox::Version << endl;
        cout << "!!! ALox included version: " << aloxVersion  << endl;
        cout << "!!! Exiting with exit(-1)" << endl;
        exit(-1);
    }

    // verify ALib agains ALox
    if (!ALIB::VerifyCompilationFlags( ALox::ALibCompilationFlags ) )
    {
        cout << "!!! Error in ALib library compilation: linked library of ALib has different compilation symbols set." << endl;
        exit(-1);
    }

    // verify the given (actual compilation units') flags against ALib
    if (!ALIB::VerifyCompilationFlags( flagsALib ) )
    {
        cout << "!!! Error in ALib library compilation: linked library of ALib has different compilation symbols set." << endl;
        exit(-1);
    }

    // verify the given (actual compilation units') flags against ALox
    if (!ALox::VerifyCompilationFlags( flagsALox ) )
    {
        cout << "!!! Error in ALox library compilation: linked library of ALox has different compilation symbols set." << endl;
        exit(-1);
    }
}

// #################################################################################################
// ALox library initialization
// #################################################################################################
bool            ALox::isInitialized                                                      =false;
const String&   ALox::ConfigCategoryName                                                 ="ALOX";

bool ALox::initInternal( Inclusion environment, int argc, void** argv, bool wArgs )
{
    //---  initialize ---
    isInitialized= true;

    // initialize ALIB
    ALIB::Init( environment, argc, argv, wArgs );

    // that's it
    return true;
}

void ALox::TerminationCleanUp()
{
    #if defined(ALOX_DBG_LOG)
        if ( Log::DebugLogger  != nullptr )
            Log_RemoveDebugLogger();
    #endif

    ALIB::TerminationCleanUp();
}

// #################################################################################################
// Lox management
// #################################################################################################

// The lox singletons for debug and release logging
#if defined(ALOX_DBG_LOG)
    Lox* ALox::theLog=    nullptr;

    Lox*     ALox::Log()
    {
        if ( !isInitialized )            Init();
        if ( theLog == nullptr )         theLog= Get("LOG", Create::IfNotExistent );
        return theLog;
    }
#endif


std::vector<Lox*> ALox::loxes;

Lox*     ALox::Get( const TString& name, Create create )
{
    OWN(ALIB::Lock)

    // search
    for( auto it : loxes )
        if( it->GetName().Equals( name, Case::Ignore ) )
            return it;


    // create?
    if ( create == Create::IfNotExistent )
    {
        Lox* newLox= new Lox ( name, false );
        loxes.emplace_back( newLox );
        return newLox;
    }

    // not found
    return nullptr;
}

void     ALox::Register( Lox* lox, ContainerOp operation )
{
    OWN(ALIB::Lock)

    // check
    if ( lox == nullptr )
    {
        ALIB_ERROR( "Nullptr given" );
        return;
    }

    // remove
    if( operation == ContainerOp::Remove )
    {
        for( auto search= loxes.begin() ; search != loxes.end() ; ++search )
            if ( *search == lox )
            {
                loxes.erase( search );
                return;
            }
        ALIB_WARNING_S512(   "A lox named \"" << (lox != nullptr ? lox->GetName() : "<null>")
                          << "\" could not be found for removal." );
    }

    // insert
    else
    {
        for( auto it : loxes )
            if( it->GetName().Equals( lox->GetName() ) )
            {
                ALIB_ERROR_S512(    "A lox named \"" << lox->GetName()
                                 << "\" was already registered. Registration ignored" );
                return;
            }
        loxes.emplace_back( lox );
   }
}

void        ALox::Reset()
{
    #if defined(ALOX_DBG_LOG)
        if (Log::DebugLogger != nullptr )
            Log_RemoveDebugLogger();

        if ( theLog != nullptr )
        {
            delete theLog;
            theLog= nullptr;
        }
    #endif

    loxes.clear();
}


}} //namespace aworx::lox
