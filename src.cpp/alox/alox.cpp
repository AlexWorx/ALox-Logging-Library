// #################################################################################################
//  aworx::lox::core - ALox Logging Library
//
//  Copyright 2013-2018 A-Worx GmbH, Germany
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
// Static instance and constructor
// #################################################################################################
ALox                 ALOX;

ALox::ALox()
: Library( ALIB_VERSION, ALIB_REVISION, "ALOX", ALOX_COMPILATION_FLAGS )
{
    dependencies.emplace_back( &lib::ALIB );
    CompilationFlagMeanings=
    {
        { "ALOX_DBG_LOG"      , ALOX_DBG_LOG_VFYBIT        },
        { "ALOX_DBG_LOG_CI"   , ALOX_DBG_LOG_CI_VFYBIT     },
        { "ALOX_REL_LOG"      , ALOX_REL_LOG_VFYBIT        },
        { "ALOX_REL_LOG_CI"   , ALOX_REL_LOG_CI_VFYBIT     },
    };
}

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



// #################################################################################################
// ALox library initialization
// #################################################################################################

void  ALox::init( Phases phase )
{
    if( phase == Phases::resourceset )
    {

        #define EOS ,

        lib::ALIB.CheckCompatibility( ALIB_VERSION, ALIB_COMPILATION_FLAGS );

        Res->AddBulk( ResourceCategory.ToCString(),

        "Var0" ,  "1|ALOX|NO_IDE_LOGGER|"                           "VD01||||VC01"   ,
        "Var1" ,  "2|ALOX|CONSOLE_TYPE|"                            "VD02||||VC02"   ,
        "Var2" ,  "3|ALOX|%1_%2_VERBOSITY|"                      "VD03|;|=|1|VC03"   ,
        "Var3" ,  "4|ALOX|GLOBAL_SOURCE_PATH_TRIM_RULES|"          "ES|;|=|1|VC04"   ,
        "Var4" ,  "5|ALOX|%1_SOURCE_PATH_TRIM_RULES|"              "ES|;|=|1|VC05"   ,
        "Var5" ,  "6|ALOX|%1_DOMAIN_SUBSTITUTION|"                   "|;|->|1|"      ,
        "Var6" ,  "7|ALOX|%1_PREFIXES|"                            "ES|;|=|1|VC07"   ,
        "Var7" ,  "8|ALOX|%1_DUMP_STATE_ON_EXIT|"                  "VD08|,|||VC08"   ,
        "Var8" , "20|ALOX|%1_AUTO_SIZES|"                               "||||VC20"   ,
        "Var9" , "21|ALOX|%1_FORMAT|"                                 "|,||1|VC21"   ,
        "Var10", "22|ALOX|%1_FORMAT_DATE_TIME|"                        "|,|||VC22"   ,
        "Var11", "23|ALOX|%1_FORMAT_MULTILINE|"                        "|,|||VC23"   ,
        "Var12", "24|ALOX|%1_FORMAT_TIME_DIFF|"                        "|,|||VC24"   ,
        "Var13", "25|ALOX|%1_MAX_ELAPSED_TIME|"                    "VD25|,|||VC25"   ,
        "Var14", "26|ALOX|%1_REPLACEMENTS|"                            "|,|||VC26"   ,
        "Var15", "27|ALOX|CONSOLE_LIGHT_COLORS|"                      "ES||||VC27"   ,
        #if defined(_WIN32)
        "Var16", "28|ALOX|CODEPAGE|"                                "VD28||||VC28"   ,
        #endif


        // Empty string. This is set with variables that want to be written into blank files.
        "ES",   "",

        // configuration variable default values
        "VD01", "false",
        "VD02", "default",
        "VD03", "writeback",
        "VD08", "none, verbosity=info, domain=/ALOX",

        "VD25", "0, limit=59",
        #if defined(_WIN32)
        "VD28", "65001",
        #endif

        // configuration variable comments
        "VC01", "If true, the creation of an additional, ide-specific debug logger is suppressed." "\n"
                "(In particular suppresses DebugLogger (C#) and VStudioLogger (C++))",

        "VC02", "Influences the type of console logger to be created by method"                    "\n"
                "Lox::CreateConsoleLogger which is also used by Log::AddDebugLogger"               "\n"
                "Possible values are: default, plain, ansi, windows, noqtcreator",

        "VC03", "The verbosities of logger \"%2\" in lox \"%1\". Use 'writeback [VAR_NAME] ;'"     "\n"
                "to enable automatic writing on application exit.",

        "VC04", "Defines global source path trim rules (applicable for all Lox instances)."        "\n"
                "   Format: [*]sourcepath [, inclusion, trimoffset, sensitivity, replacement] [ ; … ]",

        "VC05", "Defines source path trim rules for Lox \"%1\". "           "\n"
                "   Format: [*]sourcepath [, inclusion, trimoffset, sensitivity, replacement] [ ; … ]",

        "VC07", "Prefix strings for log domains of lox \"%1\".\n"
                "   Format: [*]domainpath[*] = prefixstring [, inclusion] [ ; … ] ",

        "VC08", "Log information about lox \"%1\" on exit. Comma separated list of arguments define" "\n"
                "verbosity, domain and content of output. Possible values content arguments are:"    "\n"
                "  All, " "Basic, " "Version, " "SPTR, " "Loggers, " "Domains, " "InternalDomains"   "\n"
                "  ScopeDomains, " "DSR, " "PrefixLogables" "Once, " "LogData, " "ThreadMappings, "  "\n"
                "  CompilationFlags." " If NONE is given nothing is dumped.",

        "VC20", "Auto size values of last run of Logger '%1' (generated and temporary values).",

        "VC21", "Meta info format of text logger \"%1\", including signatures for verbosity strings and" "\n"
                "an optional string added to the end of each log statement."                             "\n"
                "   Format: metaInfoFormat [, Error [, Warning [, Info [, Verbose [, MsgSuffix ]]]]]",

        "VC22", "Meta info date and time format of text logger \"%1\"."                         "\n"
                "   Format: DateFormat [, TimeOfDayFormat [, TimeElapsedDays ]]]",

        "VC23", "Multi-line format of text logger \"%1\"."       "\n"
                "   Format: MultiLineMsgMode [, FmtMultiLineMsgHeadline [, FmtMultiLinePrefix [, FmtMultiLineSuffix\n"
                "           [, MultiLineDelimiter [, MultiLineDelimiterRepl ]]]]]",

        "VC24", "Meta info time difference entities of text logger \"%1\"."       "\n"
                "   Format: TimeDiffMinimum [, TimeDiffNone [, TimeDiffNanos [, TimeDiffMicros [, TimeDiffMillis \n"
                "           [, TimeDiffSecs [, TimeDiffMins [, TimeDiffHours [,  TimeDiffDays  ]]]]]]]]",

        "VC25", "Maximum elapsed time of all runs of Logger '%1'. To reset elapsed time display""\n"
                "width, set this to 0 manually. Generated and temporary value.)",

        "VC26", "Pairs of search and replacement strings for text logger \"%1\"."               "\n"
                "   Format: search, replacement [, search, replacement] [,...]",

        "VC27", "Evaluated by colorful loggers that dispose about light and dark colors. Those may"        "\n"
                "adjust their foreground and background color accordingly. If not given, under Windows OS" "\n"
                "the right value is detected. Otherwise the value defaults to \"foreground\". In some"     "\n"
                "occasions, the (detected or set) runtime environment might also indicate a different"     "\n"
                "default value.  Possible values are 'foreground', 'background' and 'never'.",

        #if defined(_WIN32)
        "VC28", "Code page used by class WindowsConsoleLogger. Defaults to 65001."           "\n"
                "(Only used on Windows OS)",
        #endif

        //########################################## Enums ########################################
        "Verbosity",          "0,Verbose,1,"
                              "1,Info,1,"
                              "2,Warning,1,"
                              "2,Warnings,1," //allow with trailing s when reading
                              "3,Error,1,"
                              "3,Errors,1,"   //allow with trailing s when reading
                              "4,Off,1"    EOS

        "Scope",              "0,Global,1,"
                              "1,ThreadOuter,7,"
                              "2,Filename,1,"
                              "3,Method,1,"
                              "4,ThreadInner,7,"
                              "5,Path,7"   EOS

        "StateInfo",  "0" ","   "NONE"              ",1,"
                      "1" ","   "Basic"             ",1,"
                      "2" ","   "Version"           ",1,"
                    "512" ","   "LogData"           ",4,"
                      "4" ","   "Loggers"           ",1,"
                     "64" ","   "DSR"               ",2,"
                      "8" ","   "Domains"           ",1,"
                     "16" ","   "InternalDomains"   ",1,"
               "0x100000" ","   "SPTR"              ",2,"
                     "32" ","   "ScopeDomains"      ",1,"
                    "128" ","   "PrefixLogables"    ",1,"
                    "256" ","   "Once"              ",1,"
                   "1024" ","   "ThreadMappings"    ",1,"
               "0x200000" ","   "CompilationFlags"  ",1,"
             "0xFFFFFFFF" ","   "All"               ",1"  EOS

        "LightColorUsage",    "0,Auto,1,"
                              "1,Never,1,"
                              "2,Foreground,1,"
                              "3,Background,1",

        // end of AddBulk()
        nullptr
        );

        // Add boxing interfaces
        ALIB_BOXING_DEFINE_IAPPLY_FOR_APPLICABLE_TYPE(aworx::lox::Verbosity);
        ALIB_BOXING_DEFINE_IAPPLY_FOR_APPLICABLE_TYPE(aworx::lox::Scope);
        ALIB_BOXING_DEFINE_IAPPLY_FOR_APPLICABLE_TYPE(aworx::lox::core::Logger*);
    }
}

void ALox::terminationCleanUp()
{
    #if ALOX_DBG_LOG

        if ( Log::DebugLogger  != nullptr )
            Log_RemoveDebugLogger();

        if( theLog )
            delete theLog;

        while( loxes.size() > 0 )
            delete *loxes.begin();

    #endif

    lib::ALIB.TerminationCleanUp();
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
    Lox*     ALox::Log()
    {
        Init();
        if ( theLog == nullptr )         theLog= Get("LOG", Create::IfNotExistent );
        return theLog;
    }
#endif


Lox*     ALox::Get( const String& name, Create create )
{
    LOCK_HERE_WITH(loxManagement)

    // search
    for( auto* it : loxes )
        if( it->GetName().Equals<Case::Ignore>( name ) )
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
    LOCK_HERE_WITH(loxManagement)

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
        for( auto* it : loxes )
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
        pLox->Acquire( ALIB_SRCPOS );

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
