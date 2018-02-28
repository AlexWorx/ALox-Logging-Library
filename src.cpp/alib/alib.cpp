// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2018 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
#include "alib/alib.hpp"


#if !defined (HPP_ALIB_COMPATIBILITY_STD_IOSTREAM)
    #include "alib/compatibility/std_iostream.hpp"
#endif

#if ALIB_MODULE_STRINGS
    #if !defined (HPP_ALIB_STRINGS_UTIL_SPACES)
        #include "alib/strings/util/spaces.hpp"
    #endif
#endif

#if ALIB_MODULE_CONFIGURATION

    #if !defined (HPP_ALIB_CONFIG_LIB)
    #   include "alib/config/configlib.hpp"
    #endif
    #if !defined (HPP_ALIB_CONFIG_CONFIGURATION)
    #   include "alib/config/configuration.hpp"
    #endif
    #if !defined (HPP_ALIB_TIME_LIB)
    #   include "alib/time/timelib.hpp"
    #endif
    #if !defined (HPP_ALIB_TIME_TICKS)
    #   include "alib/time/ticks.hpp"
    #endif

    #if !defined (HPP_ALIB_SYSTEM_PROCESSINFO)
    #   include "alib/system/process.hpp"
    #endif

    #if !defined (HPP_ALIB_SYSTEM_ENVIRONMENT)
    #   include "alib/system/environment.hpp"
    #endif
#endif

#if ALIB_MODULE_STRINGS
    #if !defined (HPP_ALIB_STRINGS_NUMBERFORMAT)
        #include "alib/strings/numberformat.hpp"
    #endif
#endif


#if ALIB_MODULE_ALL

    #if !defined (HPP_ALIB_THREADS_SMARTLOCK)
        #include "alib/threads/smartlock.hpp"
    #endif

    #if !defined (HPP_ALIB_STRINGS_UTIL_TOKENIZER)
        #include "alib/strings/util/tokenizer.hpp"
    #endif

#endif


#if !defined (_GLIBCXX_THREAD) && !defined (_THREAD_ )
    #include <thread>
#endif

namespace aworx { namespace lib {

#if ALIB_MODULE_STRINGS

// #################################################################################################
// Static instance and constructor
// #################################################################################################
ALib                 ALIB;

ALib::ALib()
: Library( ALIB_VERSION, ALIB_REVISION, "ALIB", ALIB_COMPILATION_FLAGS )
#if ALIB_MODULE_ALL
, StdOutputStreamsLock(* new threads::SmartLock() )
#endif
{
    CompilationFlagMeanings=
    {
        { "ALIB_DEBUG"                  , ALIB_DEBUG_VFYBIT                     },
        { "ALIB_DEBUG_STRINGS"          , ALIB_DEBUG_STRINGS_VFYBIT             },

        { "ALIB_FEAT_THREADS"           , ALIB_FEAT_THREADS_VFYBIT              },
        { "ALIB_FEAT_SINGLETON_MAPPED"  , ALIB_FEAT_SINGLETON_MAPPED_VFYBIT     },
        { "ALIB_FEAT_BOXING_FTYPES"     , ALIB_FEAT_BOXING_FTYPES_VFYBIT        },
        { "ALIB_FEAT_BOXING_STD_VECTOR" , ALIB_FEAT_BOXING_STD_VECTOR_VFYBIT    },

        { "ALIB_MODULE_ALL"             , ALIB_MODULE_ALL_VFYBIT                },
        { "ALIB_MODULE_STRINGS"         , ALIB_MODULE_STRINGS_VFYBIT            },
        { "ALIB_MODULE_BOXING"          , ALIB_MODULE_BOXING_VFYBIT             },
    };

    //############### initialize threads and time ################
    #if ALIB_MODULE_CONFIGURATION
        dependencies.emplace_back( &THREADS );
        dependencies.emplace_back( &TIME    );
    #endif

    #if ALIB_MODULE_BOXING
        dependencies.emplace_back( &BOXING  );
    #endif
    #if ALIB_MODULE_STRINGS
        dependencies.emplace_back( &STRINGS );
    #endif


    dependencies.emplace_back( &LANG );

    #if ALIB_MODULE_SYSTEM
        dependencies.emplace_back( &SYSTEM );
    #endif

    #if ALIB_MODULE_CONFIGURATION
        dependencies.emplace_back( &CONFIG );
    #endif


}


// #################################################################################################
// Environment definition/detection
// #################################################################################################

#if ALIB_MODULE_ALL

//! @cond NO_DOX
    #if defined(__unix__) || defined(__APPLE__)
    namespace {
        String      DebuggerProcessNames= "gdb|debugserver";
    }
    #endif
//! @endcond

    bool ALib::IsDebuggerPresent()
    {
    #if defined(__unix__) || defined(__APPLE__)

        // Unix: search debugger process in parent processes
        const ProcessInfo& pi= ProcessInfo::Current();
        uinteger parentPID= pi.PPID;
        if ( parentPID == 0 )
            return false;

        ProcessInfo actPI( parentPID );
        Tokenizer tknzr( DebuggerProcessNames, '|' );
        while(tknzr.HasNext() )
        {
            Substring& debuggerName= tknzr.Next();
            if (actPI.Name.StartsWith( debuggerName ) )
                return true;
        }
        return false;

    #elif defined(_WIN32)

         return (bool) ( ::IsDebuggerPresent() != 0 ) ;

    #else
         #pragma message ("Unknown Platform in file: " __FILE__ )
         return false;
    #endif
    }

#endif // ALIB_MODULE_ALL

#if ALIB_MODULE_CONFIGURATION
    bool ALib::HasConsoleWindow()
    {
        // read configuration
        bool returnValue;
        Variable variable( Variables::HAS_CONSOLE_WINDOW );
        Config->Load( variable );
        if ( variable.Size() > 0  && variable.GetString()->Length() > 0 )
            returnValue=  variable.IsTrue();
        else

        #if defined(_WIN32)
            // determine if we have a console window
            returnValue= GetConsoleWindow() != NULL;
        #else
            returnValue= true;
        #endif
        return returnValue;
    }
#endif // ALIB_MODULE_CONFIGURATION



// #################################################################################################
// Init/ TerminationCleanUp()
// #################################################################################################

void ALib::init( Phases phase )
{
    if( phase == Phases::resourceset )
    {
        Res->AddBulk( ResourceCategory.ToCString(),


        "Var0",    "1|ALIB|LOCALE|ES||||VC1",
        "Var1",    "2|ALIB|WAIT_FOR_KEY_PRESS|VD2||||VC2",
        "Var2",    "3|ALIB|HAS_CONSOLE_WINDOW|ES||||VC3",


        "VC1",
            "Defines the locale of the application. If empty or not set, the systems' locale is used."
        ,
        "VC2",
            "If true, the process waits for a key stroke on termination. If empty, under Windows"   "\n"
            "behavior is detected, under other OSes, defaults to false."
        ,
        "VC3",
            "Boolean value that denotes what its name indicates. If empty, under Windows value is " "\n"
            "detected, under other OSes, defaults to true."
        ,

        // Empty string. This is set with variables that want to be written into blank files.
        "ES",   "",

        // default values
        "VD2",  "",


        // end of AddBulk()
        nullptr );
    }

    else if( phase == Phases::final )
    {
        //############### set locale ###############
        #if ALIB_MODULE_CONFIGURATION
        Variable variable;
        #endif

        #if ALIB_MODULE_CONFIGURATION && ( defined (__GLIBCXX__)  || defined(__APPLE__) )
        {
            int receivedFrom= 0;
            variable.Declare( Variables::LOCALE );
            AString locale;
            if (     Config->Load( variable ) != Priorities::NONE
                 &&  variable.GetString()->IsNotEmpty()        )
            {
                receivedFrom= 1;
                locale._( variable.GetString() );
            }
            else if ( system::GetEnvironmentVariable( "LANG"      ,locale ) )        receivedFrom= 2;
            else if ( system::GetEnvironmentVariable( "LANGUAGE"  ,locale ) )        receivedFrom= 3;

            if( receivedFrom > 0 && !locale.Equals<Case::Ignore>( "none" ) )
            {
                if( !setlocale(LC_ALL, locale.ToCString() ) )
                {
                    String256 msg( "ALib Error: setlocale(\""); msg << locale <<"\") failed. Setting read from ";
                    msg << (   receivedFrom == 1 ? "config variable 'LOCALE'"        :
                               receivedFrom == 2 ? "environment variable 'LANG'"     :
                               receivedFrom == 3 ? "environment variable 'LANGUAGE'" : "ERROR"  );

                    std::cerr.write( msg.Buffer(), msg.Length() );

                    std::cerr << ". Trying  'setlocale(LC_ALL, \"\")': ";
                    if ( setlocale(LC_ALL, ""  ) )
                        std::cerr << " success.";
                    else
                    {
                        std::cerr << "failed. Trying  'setlocale(LC_ALL, \"C\")': ";
                        if ( setlocale(LC_ALL, "C" ) )
                            std::cerr << " success.";
                        else
                            std::cerr << std::endl << "     Panic: No standard locale setting was successful!";
                    }
                    std::cerr << std::endl;
                }
            }
        }
        #endif

        // set the system's locale as the default for our static default number format
        #if ALIB_MODULE_STRINGS
            strings::NumberFormat::Global.SetFromLocale();
            strings::NumberFormat::Global.WriteGroupChars= true;
        #endif


        // --- determine if we want to wait for a keypress upon termination ---
        #if ALIB_MODULE_CONFIGURATION
            variable.Declare( Variables::WAIT_FOR_KEY_PRESS );
            Config->Load( variable );
            if ( variable.Size() > 0 )
                WaitForKeyPressOnTermination= variable.IsTrue();
            else
            {
                #if defined(_WIN32) && ALIB_DEBUG
                    WaitForKeyPressOnTermination=  ALib::HasConsoleWindow() && ALib::IsDebuggerPresent();
                #else
                    WaitForKeyPressOnTermination=  false;
                #endif
            }
        #else
                #if defined(_WIN32) && ALIB_DEBUG
                    WaitForKeyPressOnTermination=  ALib::HasConsoleWindow() && ALib::IsDebuggerPresent();
                #else
                    WaitForKeyPressOnTermination=  false;
                #endif
        #endif
    }
}


void ALib::terminationCleanUp()
{
    if ( ALIB.WaitForKeyPressOnTermination )
    {
        #if defined(_WIN32)
            OutputDebugStringA( "\r\nALIB: Waiting for 'Enter' key in the console window." \
                                "\r\n     (To disable this, set 'ALIB.WaitForKeyPressOnTermination' to 'false'.)\r\n" );
        #endif

        std::cout << std::endl << "ALIB: Press 'Enter' to exit... " \
            "      (To disable this, set 'ALIB.WaitForKeyPressOnTermination to 'false'.)" << std::endl;
        while ( getchar() != '\n' )
            ;
    }


    // remove singletons
    lang::DeleteSingletons();

    // and the cout/cerr lock
    #if ALIB_MODULE_ALL
        delete &StdOutputStreamsLock;
    #endif
}


void ALib::CheckCompatibility( int alibVersion, volatile uint64_t compilationFlags )
{
    if (Version != alibVersion )
    {
        std::cout << "!!! Error in ALox library compilation: linked against wrong version of ALib" << std::endl;
        std::cout << "!!! ALib library version:   " << Version       << std::endl;
        std::cout << "!!! ALib requested version: " << alibVersion   << std::endl;
        std::cout << "!!! Exiting with exit(-1)" << std::endl;
        exit(-1);
    }

    // verify the given (actual compilation units') flags against ALib
    if (!VerifyCompilationFlags( compilationFlags ) )
    {
        std::cout << "!!! Error in ALib library compilation: linked library of ALib has different compilation symbols set." << std::endl;
        exit(-1);
    }
}

// #################################################################################################
// SleepX methods
// #################################################################################################

// usleep() (for _WIN32)
#if !ALIB_FEAT_THREADS
    #if defined( __GLIBCXX__ )
        #include <unistd.h>
    #elif defined ( _WIN32 )
        void usleep(__int64 usec)
        {
            HANDLE timer;
            LARGE_INTEGER ft;

            ft.QuadPart = -(10*usec); // Convert to 100 nanosecond interval, negative value indicates relative time

            timer = CreateWaitableTimer(NULL, TRUE, NULL);
            SetWaitableTimer(timer, &ft, 0, NULL, NULL, 0);
            WaitForSingleObject(timer, INFINITE);
            CloseHandle(timer);
        }
    #else
        #pragma message ("Unknown Platform in file: " __FILE__ )
    #endif
#endif

void ALib::SleepMillis( int milliseconds )
{
    #if ALIB_FEAT_THREADS
        std::this_thread::sleep_for( std::chrono::milliseconds( milliseconds ) );
    #else
        usleep( milliseconds * 1000 );
    #endif
}

void ALib::SleepMicros( int microseconds )
{
    #if ALIB_FEAT_THREADS
        std::this_thread::sleep_for( std::chrono::microseconds( microseconds ) );
    #else
        usleep( microseconds );
    #endif
}

void ALib::SleepNanos( int nanoseconds )
{
    #if ALIB_FEAT_THREADS
        std::this_thread::sleep_for( std::chrono::nanoseconds( nanoseconds ) );
    #else
        int micros= nanoseconds / 1000;
        usleep( micros > 0 ? micros : 1 );
    #endif
}

#if ALIB_MODULE_CONFIGURATION
    void ALib::Sleep( const time::Ticks& ticks )
    {
         ALib::SleepNanos( static_cast<int>( ticks.InNanos() ) );
    }
#endif

#endif //ALIB_MODULE_STRINGS


// #################################################################################################
//  String helpers
// #################################################################################################

#if ALIB_MODULE_BOXING || ALIB_MODULE_STRINGS
namespace detail {
    #if defined(__WCHAR_MAX__)  && ( __WCHAR_MAX__ > 0x10000 )
        size_t   strlen16( const char16_t* s )
        {
            static_assert( sizeof(wchar_t) == sizeof( char32_t ), "Error: Platform not supported" );
            if ( s == nullptr ) return 0;
            const char16_t* p= s;
            while(*p != 0 )
                p++;
            return static_cast<size_t>( p - s );
        }
    #else
        size_t   strlen32( const char32_t* s )
        {
            static_assert( sizeof(wchar_t) == sizeof( char16_t ), "Error: Platform not supported" );

            if ( s == nullptr ) return 0;
            const char32_t* p= s;
            while(*p != 0 )
                p++;
            return static_cast<size_t>( p - s );
        }
    #endif
}  // namespace aworx::lib[::detail]
#endif

}} // namespace [aworx::lib]


// #################################################################################################
//  Doxygen documentation of general macros. (All gathered in one place for technical reasons.)
// #################################################################################################
/**
 * @addtogroup GrpALibMacros
 * @{
 * @name Macros Supporting Various ALib Concepts
 * The macros listed here have a direct relationship with classes defined in \b %ALib
 * and with their use.
 * @{
 *
 * \def  OWN
 * This preprocessor macro defines an object of class
 * \ref aworx::lib::lang::Owner "Owner". The special thing about it is, that with using this macro
 * there is no need to "invent" an (otherwise unreferenced) identifier for that definition.
 * Basically, this macro exists, because C++ does not support anonymous local instances.<br>
 * As a sample, without using this macros a piece of code code using classes
 * \ref aworx::lib::lang::Owner   "Owner"/
 * \ref aworx::lib::lang::Ownable "Ownable"
 * could look like this:<br>
 *
 *      {
 *          Owner myOwner( myOwnable );
 *
 *          // do stuff
 *          ...  (this code never refers to "myOwner")
 *      }
 *
 *  With the use of this macro, the code changes to:<br>
 *
 *      {
 *          OWN( myOwnable ); // internal identifier replacing "myOwner" not shown
 *
 *          // do stuff
 *          ...
 *      }
 *
 * \see Macros \ref LOCK_HERE and \ref LOCK_HERE_WITH.
 *
 *  @param ownable   The \b %Ownable to acquire and release.
 *
 *
 *
 * \def  LOCK_HERE
 * Shortcut to macro \ref OWN, providing <c>*this</c> as the owner. Usually used with
 * methods of types derived from classes \alib{threads,ThreadLock} or \alib{threads,ThreadLockNR}
 *
 *
 * \def  LOCK_HERE_WITH
 * Alias name for macro \ref OWN to have better readable code if parameter \p owner of macro
 * \b %OWN is of type \alib{threads,ThreadLock} or \alib{threads,ThreadLockNR}.
 *
 *  @param lock   The \b %Ownable to acquire and release.
 *
 *
 * \def  ALIB_LANG_RESOURCED
 *   Macro used to specialize TMP struct \alib{lang,T_Resourced,T_Resourced<TResourced>}
 *   for given type \p TResourced.
 *
 *   This macro is for example used with \alib{lang,T_EnumMetaDataDecl,ALib Enum Meta Data}.
 *
 *   @param TResourced      The type to specialize TMP struct \b %T_Resourced for.
 *   @param ResourceLibrary A reference to the library the type is associated with.
 *   @param NameString      The name of the resources.
 *
 *
 *
 * \def  ALIB_LANG_EXCEPTIONS
 *   Macro used to declare enumeration type \p TEnum to be compatible with class
 *   \b %Exception.
 *
 *   \see Class \alib{lang,Exception} for details.
 *
 *   @param TEnum            The enumeration type that is to be declared as an error code compatible
 *                           with class \alib{lang,Exception}.
 *   @param ResourceLibrary  A reference to the \alib{lang,Library} the enum meta data is loaded
 *                           from.
 *   @param ResourceName     The resource name of the meta information of the \p TEnum.
 *
 *
 *
 * \def  ALIB_CONFIG_VARIABLES
 *   Macro used to declare enumeration type \p TEnum to denote
 *   \ref aworx::lib::config "ALib Configuration Variables".
 *   In particular, the macro includes the following code:
 *   - Specializes TMP struct \alib{lang,T_EnumMetaDataDecl} for type \p TEnum and associate
 *     type \alib{config,VariableDecl::TTuple} for its meta data.
 *   - Passes parameters \p ResourceLibrary and \p ResourceName to macro \ref ALIB_LANG_RESOURCED.
 *   - Specializes method \alib{lang,EnumMetaData::CheckLoad} to use a detail method
 *     for loading the meta data from the resources.
 *
 *   With this - and the corresponding resource data! - in place, elements of \p TEnum can be
 *   used to declare configuration variables by passing them to one of following constructors and
 *   methods:
 *   - \alib{config,VariableDecl::VariableDecl(TEnum)}
 *   - \alib{config,Variable::Variable(TEnum)}
 *   - \alib{config,Variable::Variable(TEnum),Variable::Variable(TEnum\,const StringTypes&...)}
 *   - \alib{config,Variable::Declare(TEnum)}
 *   - \alib{config,Variable::Declare(TEnum),Variable::Declare(TEnum\,const StringTypes&...)}
 *
 *   The resource data is a table of values separated by character <b>'|'</b> ("pipe" character), which
 *   has to contain the eight values of tuple type \alib{config,VariableDecl::TTuple}. Elements
 *   \c 3 ("DefaultValue") and \c 7 ("Comments"), in the resources are interpreted as a
 *   resource name. This way, both values are loaded from separated resource strings.
 *   This has the following advantages:
 *   - The values may contain the separation character <b>'|'</b>.
 *   - The values can be manipulated within the resources more easily.
 *
 *   Note that for loading the resources, static template method
 *   \alib{lang,ResourcedTupleLoader::LoadTable} is used.
 *   As documented, this method (optionally) allows to separate each variable declaration entry
 *   into an own, numbered resource string.
 *
 *
 *   \see Namespace documentation \ref aworx::lib::config for information on configuration
 *        data and variables.
 *
 *   @param TEnum            The enumeration type that is to be declared for denoting configuration
 *                           variables.
 *   @param ResourceLibrary  A reference to the \alib{lang,Library} the enum meta data is loaded
 *                           from.
 *   @param ResourceName     The resource name of the meta information of the \p TEnum.
 *
 * @}
 * @} */ // GrpALibMacros
