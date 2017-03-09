// #################################################################################################
//  aworx::lox::core - ALox Logging Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
#include "alib/alib.hpp"

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
const uint64_t       ALox::CompilationFlags=                            ALOX_COMPATIBILITY_VERYFIER;
const uint64_t       ALox::ALibCompilationFlags=                        ALIB_COMPATIBILITY_VERIFYER;
std::pair <const char*, uint64_t> ALox::CompilationFlagMeanings[]=
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
    "(In particular suppresses DebugLogger (C#) and VStudioLogger (C++))"
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

lib::config::VariableDefinition ALox::CONSOLE_LIGHT_COLORS =
{
    &ALox::ConfigCategoryName,   nullptr,     "CONSOLE_LIGHT_COLORS",
    "",
    '\0', nullptr, Variable::FormatHint_None,
     "Evaluated by colorful loggers that dispose about light and dark colors. Those may"        "\n"
     "adjust their foreground and background color accordingly. If not given, under Windows OS" "\n"
     "the right value is detected. Otherwise the value defaults to \"foreground\". In some"     "\n"
     "occasions, the (detected or set) runtime environment might also indicate a different"     "\n"
     "default value.  Possible values are 'foreground', 'background' and 'never'."
};


lib::config::VariableDefinition ALox::FORMAT =
{
    &ALox::ConfigCategoryName,   nullptr,     "%1_FORMAT",
    nullptr,
    ',', nullptr, Variable::FormatHint_MultLine,
     "Meta info format of text logger \"%1\", including signatures for verbosity strings and"   "\n"
     "an optional string added to the end of each log statement."                               "\n"
     "   Format: metaInfoFormat [, Error [, Warning [, Info [, Verbose [, MsgSuffix ]]]]]"
};


lib::config::VariableDefinition ALox::FORMAT_DATE_TIME =
{
    &ALox::ConfigCategoryName,   nullptr,     "%1_FORMAT_DATE_TIME",
    nullptr,
    ',', nullptr, Variable::FormatHint_None,
     "Meta info date and time format of text logger \"%1\"."       "\n"
     "   Format: DateFormat [, TimeOfDayFormat [, TimeElapsedDays ]]]"
};

lib::config::VariableDefinition ALox::FORMAT_TIME_DIFF =
{
    &ALox::ConfigCategoryName,   nullptr,     "%1_FORMAT_TIME_DIFF",

    nullptr,

    ',', nullptr, Variable::FormatHint_None,
     "Meta info time difference entities of text logger \"%1\"."       "\n"
     "   Format: TimeDiffMinimum [, TimeDiffNone [, TimeDiffNanos [, TimeDiffMicros [, TimeDiffMillis \n"
     "           [, TimeDiffSecs [, TimeDiffMins [, TimeDiffHours [,  TimeDiffDays  ]]]]]]]]"
};

lib::config::VariableDefinition ALox::FORMAT_MULTILINE=
{
    &ALox::ConfigCategoryName,   nullptr,     "%1_FORMAT_MULTILINE",

    nullptr,

    ',', nullptr, Variable::FormatHint_None,
     "Multi-line format of text logger \"%1\"."       "\n"
     "   Format: MultiLineMsgMode [, FmtMultiLineMsgHeadline [, FmtMultiLinePrefix [, FmtMultiLineSuffix\n"
     "           [, MultiLineDelimiter [, MultiLineDelimiterRepl ]]]]]"
};

lib::config::VariableDefinition ALox::REPLACEMENTS=
{
    &ALox::ConfigCategoryName,   nullptr,     "%1_REPLACEMENTS",

    nullptr,

    ',', nullptr, Variable::FormatHint_None,
     "Pairs of search and replacement strings for text logger \"%1\"."       "\n"
     "   Format: search, replacement [, search, replacement] [,...]"
};



// #################################################################################################
// Compilation Flags
// #################################################################################################

// check compiler symbols, give warning once (therefore not in HPP)
#if !ALOX_DBG_LOG && defined( ALOX_DBG_LOG_CI_ON )
    #pragma message ( "Warning: ALox compiler symbol mismatch: ALOX_DBG_LOG_CI_ON given while ALOX_DBG_LOG is undefined" )
#endif
#if !ALOX_REL_LOG && defined( ALOX_REL_LOG_CI_ON )
    #pragma message ( "Warning: ALox compiler symbol mismatch: ALOX_REL_LOG_CI_ON given while ALOX_REL_LOG is undefined" )
#endif


bool ALox::VerifyCompilationFlags( uint64_t flags )
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

void ALox::checkLibraryVersions( int alibVersion, int aloxVersion, uint64_t flagsALib,  uint64_t flagsALox )
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

    // verify ALib against ALox
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
ThreadLockNR    ALox::lock;
bool            ALox::isInitialized                                                         = false;
String          ALox::ConfigCategoryName                                                   = "ALOX";

void  ALox::initImpl()
{
    ALIB_BOXING_DEFINE_IAPPLY_FOR_APPLICABLE_TYPE(aworx::lox::core::Logger*);
    isInitialized= true;
}

void ALox::TerminationCleanUp()
{
    #if ALOX_DBG_LOG

        if ( Log::DebugLogger  != nullptr )
            Log_RemoveDebugLogger();

        if( theLog )
            delete theLog;

        while( loxes.size() > 0 )
            delete *loxes.begin();

    #endif

    ALIB::TerminationCleanUp();
}

// #################################################################################################
// Lox management
// #################################################################################################

#if defined(_MSC_VER)
    // MSC  (as of 12/2015):
    // C4579: in-class initialization for type 'const aworx::SLiteral<10>'
    // is not yet implemented; static member will remain uninitialized at runtime but
    // use in constant-expressions is supported
    SLiteral<2>  ALox::InternalDomains {"$/" };
#else
    constexpr SLiteral<2>  ALox::InternalDomains;
#endif


// The lox singletons for debug and release logging
#if ALOX_DBG_LOG
    Lox* ALox::theLog=    nullptr;

    Lox*     ALox::Log()
    {
        if ( !isInitialized )            Init();
        if ( theLog == nullptr )         theLog= Get("LOG", Create::IfNotExistent );
        return theLog;
    }
#endif


std::vector<Lox*> ALox::loxes;

Lox*     ALox::Get( const String& name, Create create )
{
    OWN(lock)

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
    OWN(lock)

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
        ALIB_WARNING( "A lox named {!Q} could not be found for removal.", (lox != nullptr ? lox->GetName() : "<null>") )
    }

    // insert
    else
    {
        for( auto it : loxes )
            if( it->GetName().Equals( lox->GetName() ) )
            {
                ALIB_ERROR( "A lox named {!Q} was already registered. Registration ignored.",
                            lox->GetName() );
                return;
            }
        loxes.emplace_back( lox );
   }
}

void        ALox::Reset()
{
    Lox("trimruleresetlox", false).Reset(); // this clears the global source path trim rules

    #if ALOX_DBG_LOG
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
ALoxReportWriter::ALoxReportWriter ( Lox* pLox )
{
    this->lox= pLox;

    #if ALIB_DEBUG
        pLox->Acquire( ALIB_SRC_INFO_PARAMS );

            pLox->GetLogableContainer().Add( "ALoxReportWriter set" );
            pLox->Entry( ALoxReportWriter::LogDomain(), Verbosity::Verbose );

        pLox->Release ();
    #else

    #endif
}

void ALoxReportWriter::Report( const lib::lang::Report::Message& msg )
{
    #if ALIB_DEBUG
        lox->Acquire( msg.File, msg.Line, msg.Func );

            lox->GetLogableContainer().Add( static_cast<const Boxes&>( msg ) );
            lox->Entry( ALoxReportWriter::LogDomain(),
                        msg.Type == 0 ? Verbosity::Error   :
                        msg.Type == 1 ? Verbosity::Warning :
                        msg.Type == 2 ? Verbosity::Info    :
                                           Verbosity::Verbose     );

        lox->Release ();
    #else
        (void) msg;
    #endif
}

String16 ALoxReportWriter::reportDomain;

String& ALoxReportWriter::LogDomain()
{
    if( reportDomain.IsEmpty() )
        reportDomain << ALox::InternalDomains << "REPORT";
    return reportDomain;
}

}} //namespace aworx::lox
