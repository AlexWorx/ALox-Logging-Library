// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
/** @file */ // Hello Doxyen

#ifndef HPP_AWORX_LIB_ALIB
#define HPP_AWORX_LIB_ALIB 1

// compiler check
#if defined(__GNUC__)
    #if __cplusplus < 201103L
        #error "ALib Needs C++ 11. Compilation aborted"
    #endif
#endif

#if defined ( _MSC_VER )  &&  _MSC_VER < 1600 // VS 2010 == VC10 == _MSC_VER 1600
    #error "ALib Needs C++ 11. Compilation aborted"
#endif


// #################################################################################################
// First, process external conditional compilation symbols, then define preprocessor macros
// accordingly.
// #################################################################################################

#define FROM_HPP_AWORX_LIB_ALIB

#if defined(HPP_AWORX_LIB_ALIB_CONDCOMPILE)
    #error "aworx_condcomp.hpp must not be included manually. Include alib.hpp instead"
#endif
#include "alib/core/symbols.hpp"


#if defined(HPP_AWORX_LIB_ALIB_MACROS)
    #error "aworx_macros.hpp must not be included manually. Include alib.hpp instead"
#endif

#include "alib/core/macros.hpp"

// #################################################################################################
// basic system headers
// #################################################################################################

#if !defined (_ASSERT_H)
    #include <assert.h>
#endif

#if !defined (_GLIBCXX_CSTDDEF) && !defined(_CSTDDEF_)
    #include <cstddef>
#endif

// GNUC specific
#if defined( __GNUC__ )

    #if !defined (_GLIBCXX_CSTDINT)
        #include <cstdint>
    #endif

// Windows specific
#elif defined ( _MSC_VER )

    // Include windows.h. but exclude rarely-used stuff from Windows headers. If these things are
    // needed by the software that incorporates ALib, then windows has to be
    // included before this header file is.
    #if !defined (_INC_WINDOWS)
        #define WIN32_LEAN_AND_MEAN
        #define NOGDI
        #define NOSERVICE
        #define NOMCX
        #define NOIME
        #define NOSOUND
        #define NOCOMM
        #define NOKANJI
        #define NORPC
        #define NOPROXYSTUB
        #define NOIMAGE
        #define NOTAPE
        #include <windows.h>
    #endif

    #if !defined (_STDINT)
        #include <stdint.h>
    #endif

// other platforms not tested, yet
#else
    #pragma message ("Unknown Platform in file: " __FILE__ )
#endif

// #################################################################################################
// Include those stdlib headers that are absolutely necessary for ALib and in turn their
// necessary includes
// Note: The standard here is that those ALib headers which are included by default (and therefore
//       must not  be included from outside) do not perform any other includes.
//       This way, the following list of stdlib headers can go directly to the documentation of
//       what is needed from stdlib for core ALib.)
// #################################################################################################
#include <type_traits>
#include <utility>

// #################################################################################################
// Include those ALib core headers which are needed before the definition of class ALIB
// #################################################################################################
#include "alib/core/enums.hpp"
#include "alib/core/report.hpp"
#include "alib/strings/cstring.hpp"
#include "alib/strings/as.hpp"

// Include header of base namespace "aworx"
#include "alib/core/ns_aworx.hpp"

// #################################################################################################
// std::/stl fixes
// #################################################################################################
#if defined ( _WIN32 ) && !defined( IS_DOXYGEN_PARSER )
    namespace std
    {
        inline bool isblank( char c ) { return (c == ' ' || c == '\t'); }
    }
#endif


// #################################################################################################
// Documentation of namespace "aworx::lib"
// #################################################################################################

namespace           aworx {

/**
 *  This is the C++ namespace for core utility classes developed by A-Worx GmbH, Germany,
 *  published under the <em>MIT License</em>.
 *
 *  The set of classes and things found within this namespace and its descendants is referred
 *  to as <em>AWorx Utility Classes</em>, <em>AWorx Library</em> or just <em>ALib</em>.
 *
 *  Besides C++, this library is available in C# and Java, with language specific differences.
 *  The design goals are:
 *  - Be small, efficient and easy to understand
 *  - Keep C++, C# and Java versions similar and mimic functionality of core classes of all
 *    three languages whenever this is appropriate.
 *  - Be non-intrusive in the sense that the use of ALib in projects (maybe just because
 *    some minor functionality is wanted) does not force this code to show up many ALib types.
 *  - Do not reinvent the world: There are more comprehensive 'low level' libraries out
 *    there! However, for some reason, we have right to exist.
 */
namespace           lib {


// #################################################################################################
// forwards
// #################################################################################################
namespace config  { class Configuration;    }
namespace threads { class ThreadLockNR;     }


// #################################################################################################
// class ALIB
// #################################################################################################

/** ************************************************************************************************
 * This class is a 100% static placeholder for global methods and fields of
 * \ref aworx::lib "ALib".
 * Among the things implemented here are:
 * - Collecting information on the executed process and its environment.
 * - Initialization of several ALib components with methods #Init and #TerminationCleanUp.
 * - Thread sleep methods
 * \note In C# and Java implementations of this class, debug \e 'shortcuts' to methods of class
 *       \ref aworx::lib::Report "Report" exist. In the C++ version, such methods are provided as
 *       macros named \e 'ALIB_XXX', e.g #ALIB_ASSERT_ERROR.
 **************************************************************************************************/
class ALIB
{
    // #############################################################################################
    // internal statics
    // #############################################################################################
    protected:

        /**  State of initialization, used to avoid double initialization.   */
        static bool                                     initialized;

    // #############################################################################################
    // Public fields
    // #############################################################################################
    public:
        /**
         * These flags are used internally to detect incompatibilities when linking ALib to
         * binaries that use differen compilation flags.
         */
        ALIB_API static    const uint32_t               CompilationFlags;

        /**
         * This is for creationg (debug) output on information about the bits found in
         * field #CompilationFlags.
         */
        ALIB_API static
        std::pair <const char*, uint32_t>               CompilationFlagMeanings[7];

        /**
         * The ALib version. The versioning follows the scheme YYMM (2-digit year, 2-digit month)
         * of the initial release date.
         * Besides this version number, field #Revision indicates if this is a revised version
         * of a former release.
         */
        ALIB_API static    const int                    Version;

        /**
         * The revision number of this release. Each ALib #Version is initially released as
         * revision \e 0. Pure bug-fix releases that do not change the interface of ALib
         * are holding the same #Version but an increased number in this field.
         */
        ALIB_API static    const int                    Revision;

        /**
         * This is a general mutex that is used by ALib internally but also may be used from outside
         * for different purposes. It is non-recursive and supposed to be used seldom and 'shortly',
         * e.g. for one-time initialization tasks. In case of doubt, a separated, problem-specific
         * mutex should be created.
         */
        ALIB_API static    threads::ThreadLockNR         Lock;

        /**
         * This is the configuration singleton for ALib.
         * In method #Init(), this configuration is optionally filled with the default
         * configuration plug-ins
         * \ref aworx::lib::config::EnvironmentPlugIn "EnvironmentPlugIn"
         * and
         * \ref aworx::lib::config::CommandLinePlugIn "CommandLinePlugIn".
         * Further, custom plug-ins may be attached by the software entity using ALib classes.
         *
         * For more information, see #aworx::lib::config.
         */
        ALIB_API static    config::Configuration*         Config;

        /**
         * The name of the configuration category of configuration variables used by ALib.<br>
         * Defaults to "ALIB".<br>
         * This value can be changed to avoid conflicts between applications (especially in
         * respect to environment variable settings). Changes should be placed at very initial
         * bootstrap code, before the invocation of #Init.
         */
        ALIB_API static    strings::AS                    ConfigCategoryName;

        /**
        * If \c true, within #TerminationCleanUp, it is waited for a key press in the console
        * window.<br>
        * By default, this flag is enabled when debugging a console application under Visual Studio.<br>
        * This default behavior can be overruled by setting configuration variable
        * [ALIB_WAIT_FOR_KEY_PRESS_ON_TERMINATION](../group__GrpALoxConfigVars.html).<br>
        * In addition, this public flag may be modified at runtime (after method #Init was invoked).
        */
        ALIB_API static    bool                            WaitForKeyPressOnTermination;


    // #############################################################################################
    // Init/TerminationCleanUp()
    // #############################################################################################
    public:
        /** ****************************************************************************************
         * This method must be called prior to using ALib, e.g. at the beginning of
         * the main() method of an application. It is OK, to call this method more than once, which
         * allows independent code blocks (e.g. libraries) to bootstrap %ALIB without interfering.
         * However, only the first invocation is effective in respect to the provided variables.
         * Also, the very first invocation should not be interrupted by a parallel invocation of a
         * second thread. So, it has to be assured that this method is invoked once on the real
         * bootstrap an app.
         *
         * The following actions are performed:
         * - The configuration object is created
         * - Classes of ALib namespace \ref aworx::lib::threads are prepared to work properly
         * - Classes of ALib namespace \ref aworx::lib::time are prepared to work properly
         * - glibc versions of ALib (GNU/unix) probably invoke glibc method
         *   <em>setlocale()</em>, depending on the setting of the environment variables
         *   <em>LANG</em> and <em>LANGUAGE</em>
         *   and depending on ALib configuration variable
         *   [ALIB_LOCALE](../group__GrpALoxConfigVars.html).
         *
         * \note %ALIB must not be used before all global/static variables are created. Hence, it
         *       is not allowed to initialize %ALIB within static variable initialization code.
         *       This restriction is wanted by design, because different platforms and compilers
         *       implement the initialization phase of static and global code differently and it is
         *       not considered good programming style to rely on C++ bootstrap.
         *       Using %ALIB within C++ bootstrap is undefined behavior.
         *
         * \note On the Windows platform, the Microsoft compiler provides the global variables
         *       <em>__argc</em> and <em>__argv</em> (respectively <em>__wargv</em> for wide
         *       character binaries. These variables a can be used if this method is invoked
         *       outside of the <em>main()</em> method.
         *
         *  @param environment  If \c Inclusion::Include (the default), an
         *                 \ref aworx::lib::config::EnvironmentPlugIn "EnvironmentPlugIn"
         *                 is attached to the
         *                 \ref aworx::lib::ALIB::Config "ALIB::Config" singleton. Hence,
         *                 environment variables are read and potentially do overwrite
         *                 configuration variables in other configuration plug-ins.<br>
         *  @param argc    Parameter which in the standard case is taken from  C/C++ main()
         *                 method (Provides the number of command line arguments in argv).
         *                 If this greater than 0, a
         *                 \ref aworx::lib::config::CommandLinePlugIn "CommandLinePlugIn"
         *                 is attached to the
         *                 \ref aworx::lib::ALIB::Config "ALIB::Config" singleton. Hence,
         *                 command line options are read and those potentially overwrite
         *                 configuration variables in other configuration plug-ins.<br>
         *                 Defaults to 0.
         *  @param argv    Parameter which in the standard case is taken from  C/C++ main()
         *                 method (Provides a pointer to a list of command line arguments).
         *                 Defaults to nullptr.
         *  @param wArgs   If \c true, parameter argv is of type '<em>wchar_t **</em>', otherwise
         *                 of type '<em>char **</em>'.
         *                 Defaults to \c false.
         ******************************************************************************************/
        ALIB_API static void     Init(  enums::Inclusion environment= enums::Inclusion::Include,
                                        int  argc=    0, void **argv= nullptr, bool wArgs= false );

        /** ****************************************************************************************
         * Cleans up memory on termination. This method is useful if using memory analysis tools
         * (such as Valgrind) to remove any internal allocations before a program terminates.
         ******************************************************************************************/
        ALIB_API  static void    TerminationCleanUp();


        /** ****************************************************************************************
         * Verifies a given sets of ALib compilation flags with the internal set
         * \ref ALIB::CompilationFlags. In case they are different in a way
         * that alib gets incompatible (e.g. different class sizes, which results in errors that are
         * very hard to debug), the flags are written to \e cout for comparison and \c false is
         * returned.
         *
         * This method should be called on bootstrap to detect if incompatible library types were
         * built. If several libraries that use ALib are linked together, each should invoke this
         * test against separatedly. The macro \c ALIB_COMPATIBILITY_VERYFIER will provide the
         * flags.
         *
         * @param flags The flags externally grabed using macro \c ALIB_COMPATIBILITY_VERYFIER.
         *
         * @return \c true if compatible, \c false else.
         ******************************************************************************************/
        ALIB_API  static bool    VerifyCompilationFlags( uint32_t flags );

    // #############################################################################################
    // Other static interface methods
    // #############################################################################################
    public:
        /** ****************************************************************************************
         *  This is calling <em>std::this_thread::sleep_for</em>.
         *  This is for compatibility with other platform versions of ALib.
         *  Variants of this method are #SleepMicros and #SleepNanos.
         *
         *  @param millisecs    Sleep time in milliseconds.
         ******************************************************************************************/
        ALIB_API  static void SleepMillis( int millisecs );

        /** ****************************************************************************************
         *  This is calling <em>std::this_thread::sleep_for</em>.
         *  This is for compatibility with other platform versions of ALib.
         *    Variants of this method are #SleepMillis and #SleepNanos.
         *
         * @param microsecs    Sleep time in milliseconds.
         ******************************************************************************************/
        ALIB_API  static void SleepMicros( int microsecs );

        /** ****************************************************************************************
         *  This is calling <em>std::this_thread::sleep_for</em>.
         *  This is for compatibility with other platform versions of ALib.
         *  Variants of this method are #SleepMicros and #SleepMillis.
         *
         * @param nanosecs    Sleep time in nanoseconds.
         ******************************************************************************************/
        ALIB_API  static void SleepNanos( int nanosecs );

};// class ALIB

}} // namespace aworx::lib


// #################################################################################################
// Includes of header files which must always be present.
// (...and which must not be included directly. Therefore all headers listed here, have an include
// prevention #error set, based on FROM_HPP_AWORX_LIB_ALIB and their own include guard
// #################################################################################################

#include "alib/strings/namespace.hpp"

// disallow others to include our headers directly
#undef FROM_HPP_AWORX_LIB_ALIB

#endif // HPP_AWORX_LIB_ALIB
