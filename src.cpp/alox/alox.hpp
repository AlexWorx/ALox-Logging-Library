// #################################################################################################
//  aworx::lox - ALox Logging Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
/** @file */ //<- needed for Doxygen include

#ifndef HPP_ALOX
#define HPP_ALOX 1


namespace aworx {
/** ************************************************************************************************
 *  This is the C++ namespace for code of the <em>%ALox Logging Library</em>.
 *  Developed by A-Worx GmbH and published under the MIT license.
 **************************************************************************************************/
namespace lox {

    class Lox;
}}

// #################################################################################################
// ALOX_DLL_EXPORTS
// Before including ALIB.h, we have to evaluate the DLL exports symbol to set the corresponding
// flag for ALIB as if it was passed to the compiler.
// #################################################################################################
/**
 * @addtogroup GrpALoxCompilerSymbols
 * @{ \def  ALOX_DLL_EXPORTS
 *  This compiler symbol has to be defined when compiling ALox as a DLL under Windows/MSC.
 *  In addition, also \ref ALIB_DLL_EXPORTS has to be defined.
 *  Within code units that use the ALox DLL, both symbols must not be defined.
 * @}
 *
 * @addtogroup GrpALoxMacrosLowLevel
 * @{ \def  ALOX_API
 *  Used to export/import C++ symbols into a dynamic link library.
 *  Defined when compiling ALox as a DLL under Windows/MSC. Dependent on \ref ALOX_DLL_EXPORTS.
 * @}
 */
#if defined( _MSC_VER )
    #ifdef ALOX_DLL_EXPORTS
        #define ALOX_API  __declspec(dllexport)
    #else
        #define ALOX_API  __declspec(dllimport)
    #endif
#else
    #define ALOX_API
#endif

// #################################################################################################
// include ALIB
// #################################################################################################
#include "alib/alib.hpp"

// #################################################################################################
// Now we first process external conditional compilation symbols
// and then we define our prepro logging macros accordingly.
// #################################################################################################

#if defined(HPP_ALOX_SYMBOLS)
    #error "alox_condcomp.hpp must not be included manually. Include alox.hpp instead"
#endif
#include "internals/alox_symbols.hpp"

#if defined(HPP_ALOX_MACROS)
    #error "macros.hpp must not be included manually. Include alox.hpp instead"
#endif
#include "internals/alox_macros.hpp"

#if !defined (_GLIBCXX_VECTOR) && !defined(_VECTOR_)
    #include <vector>
#endif


namespace aworx {
namespace       lox {


// #############################################################################################
// Forward declarations
// #############################################################################################


/** ************************************************************************************************
 * This is a 100% static class that holds constants and 'global' methods of the
 * ALox Logging Library.
 **************************************************************************************************/
class ALox
{
    /** Protected constructor to avoid users to instantiate this class */
    protected: ALox();

    protected:
        /**  flag indicating that ALox has been initialized */
        ALOX_API static
        bool      isInitialized;

    // #############################################################################################
    // Version, Compilation flags and verification
    // #############################################################################################
    public:
        /**
         * The version of ALox. The versioning follows the scheme YYMM (2-digit year, 2-digit month)
         * of the initial release date.
         * Besides this version number, field #Revision indicates if this is a revised version
         * of a former release.
         */
        ALIB_API static const int               Version;

        /**
         * The revision number of this release. Each ALox #Version is initially released as
         * revision \e 0. Pure maintenance releases that do not change the interface of ALox
         * are holding the same #Version but an increased number in this field.
         */
        ALIB_API static const int               Revision;

         /**
         * These flags are used internally to detect incompatibilities when linking ALox to
         * binaries that use differen compilation flags.
         */
        ALIB_API static    const uint32_t       CompilationFlags;

        /**
         * This is for creationg (debug) output on information about the bits found in
         * field #CompilationFlags.
         */
        ALIB_API static
        std::pair <const char*, uint32_t>       CompilationFlagMeanings[4];


         /**
         * These flags are used internally to detect incompatibilities when linking ALox to
         * ALib (can only be different in the unusual case that ALib exists in a library independent
         * from ALox).
         */
        ALIB_API static    const uint32_t       ALibCompilationFlags;

        /** ****************************************************************************************
         * Verifies a given sets of ALox compilation flags with the internal set
         * \ref ALox::CompilationFlags. In case they are different in a way
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
        ALIB_API  static
        bool      VerifyCompilationFlags( uint32_t flags );

    // #############################################################################################
    // Public fields
    // #############################################################################################
    public:
        /**
         * This is the path for logging to the internal domain. By manipulating this
         *  <em>Log Domains' Verbosity</em>, the verbosity of ALox itself can be controlled.
         * For example, with \e Verbosity.INFO, the 'on the fly' creation of <em>Log Domains</em>
         * are logged, which can be helpful to determine the <em>Log Domains</em> that are
         * created by libraries and larger projects.
         *
         * The following sub-domains are used by ALox:
         *
         *   Sub-Domain | Description
         *   - - - - - -| - - - - - - - - - - - - - - - - - - -
         *   LGR        | Used when \e %Loggers are registered, retrieved or removed from a \b %Lox and when the \e Verbosity of a <em>Log Domain</em> for a \e %Logger is changed.<br>In addition used with method \b %Lox::SetStartTime.
         *   DMN        | Used when <em>Log Domains</em> are registered (on first use), when <em>Scope Domains</em> are set or removed and when <em>Domain Substitution Rules</em> are set.
         *   PFX        | Used when <em>Prefix Logables</em> are set or removed.
         *   THR        | Used with method \b %Lox::MapThreadName.
         *   LGD        | Used with storing and retrieving <em>Log Data</em> objects.
         *
         * In addition, class
         * \ref aworx::lox::ALoxReportWriter "ALoxReportWriter" logs into sub-domain
         * <c>'REPORT'</c>.
         *
         * \note For internal logging an separated <em>domain tree</em> is used. This means, that
         *       setting the root domain of a \b %Lox to a certain \e Verbosity does \e not affect
         *       the internal domains. In other words, the \e Verbosity of the internal domain
         *       (or one of its sub-domains) has to be set explicitly.
         */
        #if defined(_MSC_VER)
            // MSC  (as of 12/2015):
            // C4579: in-class initialization for type 'const aworx::SLiteral<2>'
            // is not yet implemented; static member will remain uninitialized at runtime but
            // use in constant-expressions is supported

            ALIB_API static     SLiteral<2>  InternalDomains;
        #else
            static constexpr    SLiteral<2>  InternalDomains                        {"$/"};
        #endif

        /**
         * The name of the configuration category of configuration variables used by ALox.<br>
         * Defaults to "ALOX".<br>
         * This value can be changed to avoid conflicts between applications (especially in
         * respect to environment variable settings). Changes should be placed at very initial
         * bootstrap code, before the invocation of #Init.<br>
         * See also \ref aworx::lib::ALIB::ConfigCategoryName "ALIB::ConfigCategoryName".
         */
        ALIB_API static const String&        ConfigCategoryName;


    // #############################################################################################
    // Protected fields
    // #############################################################################################
    protected:
        /** The Lox singleton for debug logging. Created on request. */
        #if defined(ALOX_DBG_LOG)
            ALIB_API static Lox*             theLog;
        #endif

        /** The Lox objects registered with us. */
        ALIB_API static std::vector<Lox*>    loxes;

    // #############################################################################################
    // Initialization
    // #############################################################################################
    public:
        /** ****************************************************************************************
         * This method should be called prior to using the ALox library, e.g. at the beginning of
         * the main() method of an application. It is OK, to call this method more than once, which
         * allows independent code entities (e.g. libraries) to bootstrap ALox without having to
         * rely on other code entities to do so.
         * Nevertheless, the very first invocation should not be interrupted by a parallel invocation
         * of a second thread. So, it has to be assured that this method is invoked once on the
         * bootstrap of an application before other threads are active.
         *
         * \note This method invokes
         *       \ref aworx::lib::ALIB::Init "ALIB::Init", hence no explicit initialization of
         *       underlying ALib is needed.
         *
         * If command line parameters should be used for configuring ALox, then the very first
         * call to this method has to provide the argc and argv parameters. In addition, the
         * first invocation decides if environment variables are used for the configuration
         * of ALox as well (see parameter 'useEnv'). Subsequent calls to this method with different
         * parameters do not change the setup.
         *
         * \note If other, custom configuration data sources should be used already with this method
         *       (to read the configuration variables as described in
         *       \ref aworx::lib::ALIB::Init "ALIB::Init"),
         *       according configuration plug-ins have to be added attached to public, static field
         *       \ref aworx::lib::ALIB::Config prior to invoking this method.
         *
         * <p>
         *
         * \note On the Windows platform, the Microsoft compiler provides the global variables
         *       <em>__argc</em> and <em>__argv</em> (respectively <em>__wargv</em> for wide
         *       character binaries. These variables a can be used if this method is invoked
         *       outside of the <em>main()</em> method.
         *
         * For convenience, several ALox classes call this method implicitly on construction
         * or when using them, e.g. Lox and Logger. Therefore, when using ALox, there is no need
         * to to call this method, unless aforementioned command line parameters should be passed.
         *
         * \note ALox must not be used before all global/static variables are created. Hence, it
         * is not allowed to initialize ALox within static variable initialization code. This
         * restriction is wanted by design, because different platforms and compilers implement the
         * bootstrap of static and global data differently and it is not considered a good
         * programming style to rely on C++ bootstrap. Using ALox/ALIB within C++ bootstrap is
         * undefined behavior. (This is true for any C++ library.)
         *
         *  @param environment  If \c Inclusion::Include (the default), an
         *                    \ref aworx::lib::config::EnvironmentPlugIn "EnvironmentPlugIn"
         *                    is attached to the
         *                    \ref aworx::lib::ALIB::Config "ALIB::Config" singleton. Hence,
         *                    environment variables are read and potentially do overwrite
         *                    configuration variables in other configuration plug-ins.<br>
         *                    Defaults to \c true.
         *  @param argc       Parameter which in the standard case is taken from  C/C++ main()
         *                    method (Provides the number of command line arguments in argv).
         *                    If this greater than 0, a
         *                    \ref aworx::lib::config::CommandLinePlugIn "CommandLinePlugIn"
         *                    is attached to the
         *                    \ref aworx::lib::ALIB::Config "ALIB::Config" singleton. Hence,
         *                    environment variables are read and potentially overwrite
         *                    configuration variables in other configuration plug-ins.<br>
         *                    Defaults to 0.
         *  @param argv       Parameter which in the standard case is taken from  C/C++ main()
         *                    method (Provides a pointer to a list of command line arguments).
         *                    Defaults to nullptr.
         *
         *  @param wArgs      If \c true, parameter argv is of type '<em>wchar_t **</em>', otherwise
         *                    of type '<em>char **</em>'.
         *                    Defaults to \c false.
         *
         * @returns Returns \c true if ALox was initialized before, \c false if not.
         ******************************************************************************************/
         inline static
         bool     Init( lib::enums::Inclusion environment =lib::enums::Inclusion::Include,
                        int argc =0, void** argv =nullptr, bool wArgs =false )
        {
            if ( isInitialized )
                return false;

            ALox::checkLibraryVersions();
            return initInternal( environment, argc, argv, wArgs );
        }

        /** ****************************************************************************************
         *  Cleans up static/global ALox memory on termination. This method is useful if using
         *  memory analysis tools (such as valgrind) to remove any internal allocations before a
         *  program terminates.
         ******************************************************************************************/
        ALOX_API static
        void      TerminationCleanUp();

    // #############################################################################################
    // Lox management
    // #############################################################################################
        /** ****************************************************************************************
         * Returns a singleton of class \b %Lox used for debug logging
         * @return The debug-logging Lox of ALox :-)
         ******************************************************************************************/
        ALOX_API static
        Lox*     Log();

        /** ****************************************************************************************
         * Returns the \b Lox with the given name.
         * A lox is only found if it was created and registered with ALox using #Register.
         * If not found, and parameter \p create is \c true (the default), a new \b Lox is created,
         * registered and returned.
         *
         * @param name      The name of the \b %Lox to search and optionally to create.
         *                  Comparison is case insensitive.
         * @param create    Denotes whether a \b %Lox that was not found is created.
         *                  Optional and defaults to \b %Create::Never.
         * @return The \b Lox found, \c nullptr in case of failure.
         ******************************************************************************************/
        ALOX_API static
        Lox*     Get( const TString& name, Create create= Create::Never );

        /** ****************************************************************************************
         * Registers or un-registers a \b %Lox object statically with ALox.
         * Once registered,  any code entity of the same process is enabled to retrieve
         * the \b %Lox using #Get.<br>
         * No two objects with the same name must be registered. If this is done, the latter
         * will not be registered and not be found by #Get. In debug-compilations, an ALib
         * error report is written (by default raises 'assert') if a name is registered twice.<br>
         * Note that name comparisson is performed case <b>in</b>-sensitive.
         *
         * If debug-logging is enabled (depends on compilation symbols) and used, the singleton
         * of type \% Lox provided for debug-logging is registered. This uses the name \c "Log"
         *
         * Registration is \e not mandatory but done by default by the constructor of class \b %Lox.
         * Therefore, to keep a \b Lox private, an optional parameter is available.
         *
         * @param lox       The \b %Lox to register.
         * @param operation If \b %ContainerOp::Remove, the given \p Lox is unregistered.
         *                  Defaults to \b %ContainerOp::Insert.
         ******************************************************************************************/
        ALOX_API static
        void     Register( Lox* lox, ContainerOp operation );

        /** ****************************************************************************************
         * Resets this object. Concretely the following steps are performed:
         * - All \b %Lox objects are removed.
         * - If the debug lox singleton exists, it is deleted.
         *
         * \attention
         *   This method was introduced to support resetting ALox in the unit tests.
         *   In real applications, this method should NOT be used.
         *   Side effects might appear using this method and it is not tested otherwise than
         *   used in tests!
         ******************************************************************************************/
        ALOX_API static
        void     Reset();


    // #############################################################################################
    // Internals
    // #############################################################################################
    protected:
        /** ****************************************************************************************
         * Internal, main part of the Init function. (The method is split into two parts, because
         * a portion of it has to be inlined. This allows to veryfy if the ALib/ALox library that
         * a binary is linked to, has the same compilation flags set. This check may avoid a lot of
         * unnecessary debugging trouble.
         *  @param environment  Passed from method #Init
         *  @param argc         Passed from method #Init
         *  @param argv         Passed from method #Init
         *  @param wArgs        Passed from method #Init
         * @returns Returns \c true if ALox was initialized before, \c false if not.
         ******************************************************************************************/
        ALOX_API static
        bool     initInternal( Inclusion environment, int argc, void** argv, bool wArgs );

        /** ****************************************************************************************
         * Checks if versions of ALib, ALox and the actual compilation unit share compatible
         * compilation symbols.
         * This method is invoked automatically by method #Init.
         * @param alibVersion Defaults to a value defined by the currently included headers.
         * @param aloxVersion Defaults to a value defined by the currently included headers.
         * @param flagsALib   Defaults to a value defined by the currently included headers.
         * @param flagsALox   Defaults to a value defined by the currently included headers.
         ******************************************************************************************/
        ALOX_API static
        void     checkLibraryVersions( int alibVersion    =ALIB_VERSION_VERYFIER,
                                       int aloxVersion    =ALIB_VERSION_VERYFIER,
                                       uint32_t flagsALib =ALIB_COMPATIBILITY_VERYFIER,
                                       uint32_t flagsALox =ALOX_COMPATIBILITY_VERYFIER  );
};// class ALox

/** ************************************************************************************************
 * The \b %ReportWriter for ALib when using ALox. An instance of this class is created
 * in method \ref aworx::lox::Log::AddDebugLogger "Log::AddDebugLogger"
 * and registered with ALib.<br>
 * Uses internal domain <c>'$/REPORT'</c> for logging.
 **************************************************************************************************/
class    ALoxReportWriter : public aworx::lib::ReportWriter
{
    protected:
        /** The \b Lox to report to */
        Lox*        lox;

        /** The internal domain to report into */
        static String16                    reportDomain;

    public:
    /** ********************************************************************************************
     * Constructs an \b %ALoxReportWriter.
     * @param lox    The \b Lox to report to.
     **********************************************************************************************/
     ALOX_API
     ALoxReportWriter ( Lox* lox );

    /** ********************************************************************************************
     * Notify activation/deactivation
     **********************************************************************************************/
    virtual void NotifyActivation  ( Phase ) { }


    /** ********************************************************************************************
     * Write ALib reports using ALox.
     * @param report The report to log.
     **********************************************************************************************/
     virtual void Report  ( const lib::Report::Message& report );

    /** ********************************************************************************************
     * Returns the domain used to write reports.
     * @return The report log domain.
     **********************************************************************************************/
     ALOX_API
     static String& LogDomain();
};// class ALoxReportWriter



} // namespace lox

/** Type alias name in namespace #aworx. */
using     ALox=         aworx::lox::ALox;

}  // namespace aworx



// #################################################################################################
// include Log and Lox classes
// #################################################################################################
#include "aloxtypesandenums.hpp"
#include "log.hpp"
#include "lox.hpp"


#endif // HPP_ALOX
