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




using namespace std;
using namespace aworx;
namespace aworx { namespace lox {


// #################################################################################################
// Version and check flags
// #################################################################################################
const int            ALox::Version=                                           ALIB_VERSION_VERYFIER;
const int            ALox::Revision=                                                              0;
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
// Configuration variables
// #################################################################################################
lib::config::VariableDefinition ALox::CONSOLE_TYPE =
{
    &ALox::ConfigCategoryName,   nullptr,     "CONSOLE_TYPE",
    "default",
    '\0', nullptr, Variable::FormatHint_None,
    "Influences the type of console logger to be created by method"         "\n"
    "Lox::CreateConsoleLogger which is also used by Log::AddDebugLogger"    "\n"
    "Possible values are: default, plain, ansi, windows, noqtcreator"
};

lib::config::VariableDefinition ALox::NO_IDE_LOGGER =
{
    &ALox::ConfigCategoryName,   nullptr,     "NO_IDE_LOGGER",
    "false",
    '\0', nullptr, Variable::FormatHint_None,
    "If true, the creation of an additional, ide-specific debug logger is suppressed." "\n"
    "(In particular suppresses VebugLogger (C#) and VStudioLogger (C++))"
};

lib::config::VariableDefinition ALox::AUTO_SIZES =
{
    &ALox::ConfigCategoryName,   nullptr,     "%1_AUTO_SIZES",
    nullptr,
    '\0', nullptr, Variable::FormatHint_None,
    "Auto size values of last run of Logger '%1' (generated and temporary values)."
};

lib::config::VariableDefinition ALox::MAX_ELAPSED_TIME =
{
    &ALox::ConfigCategoryName,   nullptr,     "%1_MAX_ELAPSED_TIME",
    "0, limit=59",
    ',', nullptr, Variable::FormatHint_None,
    "Maximum elapsed time of all runs of Logger '%1'. To reset elapsed time display\n"
    "width, set this to 0 manually. Generated and temporary value.)"
};


lib::config::VariableDefinition ALox::DOMAIN_SUBSTITUTION =
{
    &ALox::ConfigCategoryName,   nullptr,     "%1_DOMAIN_SUBSTITUTION",
    nullptr,
    ';', "->", Variable::FormatHint_MultLine,
    ""
};

lib::config::VariableDefinition ALox::VERBOSITY =
{
    &ALox::ConfigCategoryName,   nullptr,     "%1_%2_VERBOSITY",
    "writeback",
    ';', "=", Variable::FormatHint_MultLine,
    "The verbosities of logger \"%2\" in lox \"%1\". Use 'writeback [VAR_NAME] ;'\n"
    "to enable automatic writing on application exit."
};

lib::config::VariableDefinition ALox::PREFIXES =
{
    &ALox::ConfigCategoryName,   nullptr,     "%1_PREFIXES",
    "",
    ';', "=", Variable::FormatHint_MultLine,
    "Prefix strings for log domains of lox \"%1\".\n"
    "   Format: [*]domainpath[*] = prefixstring [, inclusion] [ ; … ] "
};

lib::config::VariableDefinition ALox::DUMP_STATE_ON_EXIT =
{
    &ALox::ConfigCategoryName,   nullptr,     "%1_DUMP_STATE_ON_EXIT",
    "none, verbosity=info, domain=/ALOX",
    ',', nullptr, Variable::FormatHint_None,
    "Log information about lox \"%1\" on exit. Comma separated list of arguments define"       "\n"
    "verbosity, domain and content of output. Possible values content arguments are:"          "\n"
    "  " "All, " "Basic, " "Version, " "SPTR, " "Loggers, " "Domains, " "InternalDomains"      "\n"
    "  " "ScopeDomains, " "DSR, " "PrefixLogables" "Once, " "LogData, " "ThreadMappings, "     "\n"
    "  " "CompilationFlags." " If NONE is given nothing is dumped."
};



lib::config::VariableDefinition ALox::SPTR_GLOBAL =
{
    &ALox::ConfigCategoryName,   nullptr,     "GLOBAL_SOURCE_PATH_TRIM_RULES",
    "",
    ';', "=", Variable::FormatHint_MultLine,
     "Defines global source path trim rules (applicable for all Lox instances)."   "\n"
     "   Format: [*]sourcepath [, inclusion, trimoffset, sensitivity, replacement] [ ; … ]"
};

lib::config::VariableDefinition ALox::SPTR_LOX =
{
    &ALox::ConfigCategoryName,   nullptr,     "%1_SOURCE_PATH_TRIM_RULES",
    "",
    ';', "=", Variable::FormatHint_MultLine,
     "Defines global source path trim rules for Lox \"%1\". "           "\n"
     "   Format: [*]sourcepath [, inclusion, trimoffset, sensitivity, replacement] [ ; … ]"
};

#if defined(_WIN32)
lib::config::VariableDefinition ALox::CODEPAGE =
{
    &ALox::ConfigCategoryName,   nullptr,     "CODEPAGE",
    "65001",
    '\0', nullptr, Variable::FormatHint_None,
     "Code page used by class WindowsConsoleLogger. Defaults to 65001."           "\n"
     "(Only used on Windows OS)"
};
#endif

lib::config::VariableDefinition ALox::CONSOLE_HAS_LIGHT_BACKGROUND =
{
    &ALox::ConfigCategoryName,   nullptr,     "CONSOLE_HAS_LIGHT_BACKGROUND",
    "",
    '\0', nullptr, Variable::FormatHint_None,
     "Evaluated by colorful loggers that dispose about light and dark colors. Those"        "\n"
     "adjust their foreground color accordingly. If not given, under Windows OS the right"  "\n"
     "value is detected. Otherwise the value defaults to false. In some occasions, the"     "\n"
     "(detected or set) runtime environment might also indicate a default value."
};


lib::config::VariableDefinition ALox::FORMAT =
{
    &ALox::ConfigCategoryName,   nullptr,     "%1_FORMAT",
    nullptr, // default value must stay nullptr, because 2 variables are requested. If was given here,
             // the second is never tried!
    ',', nullptr, Variable::FormatHint_MultLine,
     "Meta info format of text logger \"%1\", including signatures for verbosity strings."       "\n"
     "   Format: format [, Error [, Warning [, Info [, Verbose ]]]]"
};


lib::config::VariableDefinition ALox::FORMAT_DATE_TIME =
{
    &ALox::ConfigCategoryName,   nullptr,     "%1_FORMAT_DATE_TIME",
    nullptr, // default value must stay nullptr, because 2 variables are requested. If was given here,
             // the second is never tried!
    ',', nullptr, Variable::FormatHint_None,
     "Meta info date and time format of text logger \"%1\"."       "\n"
     "   Format: DateFormat [, TimeOfDayFormat [, TimeElapsedDays ]]]"
};

lib::config::VariableDefinition ALox::FORMAT_TIME_DIFF =
{
    &ALox::ConfigCategoryName,   nullptr,     "%1_FORMAT_TIME_DIFF",

    nullptr, // default value must stay nullptr, because 2 variables are requested. If was given here,
             // the second is never tried!

    ',', nullptr, Variable::FormatHint_None,
     "Meta info time difference entities of text logger \"%1\"."       "\n"
     "   Format: TimeDiffMinimum [, TimeDiffNone [, TimeDiffNanos [, TimeDiffMicros [, TimeDiffMillis \n"
     "           [, TimeDiffSecs [, TimeDiffMins [, TimeDiffHours [,  TimeDiffDays  ]]]]]]]]"
};

lib::config::VariableDefinition ALox::FORMAT_MULTILINE=
{
    &ALox::ConfigCategoryName,   nullptr,     "%1_FORMAT_MULTILINE",

    nullptr, // default value must stay nullptr, because 2 variables are requested. If was given here,
             // the second is never tried!

    ',', nullptr, Variable::FormatHint_None,
     "Multi-line format of text logger \"%1\"."       "\n"
     "   Format: MultiLineMsgMode [, FmtMultiLineMsgHeadline [, FmtMultiLinePrefix [, FmtMultiLineSuffix\n"
     "           [, MultiLineDelimiter [, MultiLineDelimiterRepl ]]]]]"
};


// #################################################################################################
// Compilation Flags
// #################################################################################################

// check compiler symbols, give warning once (therefore not in HPP)
#if !defined( ALOX_DBG_LOG ) && defined( ALOX_DBG_LOG_CI_ON )
    #warning "ALox compiler symbol mismatch: ALOX_DBG_LOG_CI_ON given while ALOX_DBG_LOG is undefined"
#endif
#if !defined( ALOX_REL_LOG ) && defined( ALOX_REL_LOG_CI_ON )
    #warning "ALox compiler symbol mismatch: ALOX_REL_LOG_CI_ON given while ALOX_REL_LOG is undefined"
#endif


bool ALox::VerifyCompilationFlags( uint32_t flags )
{
    if ( flags == ALox::CompilationFlags )
        return true;

    // dump out the flags
    cout << std::left << setw(25) <<  "Symbol" << '|' << setw(5) << " Lib" <<'|' << " Comp. Unit"  <<endl;
    for( auto& p : CompilationFlagMeanings )
    {
        cout << setw(25) <<  p.first << '|' << setw(5) << (ALox::CompilationFlags & p.second  ? " On" : " Off")
                                     << "|" << setw(5) << (flags                  & p.second  ? " On" : " Off")
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
String          ALox::ConfigCategoryName                                                 ="ALOX";

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
    Lox("trimruleresetlox", false).Reset(); // this clears the global source path trim rules

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

// #################################################################################################
// ALoxReportWriter
// #################################################################################################
ALoxReportWriter::ALoxReportWriter ( Lox* lox )
{
    this->lox= lox;

    #if defined( ALIB_DEBUG )
        lox->Acquire( ALIB_DBG_SRC_INFO_PARAMS );

            lox->Verbose( ALoxReportWriter::LogDomain(), "ALoxReportWriter set" );

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

}} //namespace aworx::lox
