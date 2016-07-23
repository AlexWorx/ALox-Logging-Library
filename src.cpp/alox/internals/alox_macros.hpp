// #################################################################################################
//  aworx::lox - ALox Logging Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
/** @file */ //<- needed for Doxygen include

#ifndef HPP_ALOX_MACROS
#define HPP_ALOX_MACROS 1


#if !defined(HPP_ALOX)
    #error "include alox.hpp instead of alox_macros.hpp"
#endif


// #################################################################################################
// Macros not related to logging
// #################################################################################################

// #################################################################################################
// ALOX_SYMBOL_DEBUG
// #################################################################################################

#if !defined( IS_DOXYGEN_PARSER )


#define ALOX_DBG_LOG_VFYBIT                (1 << 0)
#if defined(ALOX_DBG_LOG)
    #define ALOX_DBG_LOG_VFYVAL            ALOX_DBG_LOG_VFYBIT
#else
    #define ALOX_DBG_LOG_VFYVAL            0
#endif

#define ALOX_DBG_LOG_CI_VFYBIT             (1 << 1)
#if defined(ALOX_DBG_LOG_CI)
    #define ALOX_DBG_LOG_CI_VFYVAL         ALOX_DBG_LOG_CI_VFYBIT
#else
    #define ALOX_DBG_LOG_CI_VFYVAL         0
#endif

#define ALOX_REL_LOG_VFYBIT                (1 << 2)
#if defined(ALOX_REL_LOG)
    #define ALOX_REL_LOG_VFYVAL            ALOX_REL_LOG_VFYBIT
#else
    #define ALOX_REL_LOG_VFYVAL            0
#endif

#define ALOX_REL_LOG_CI_VFYBIT             (1 << 3)
#if defined(ALOX_REL_LOG_CI)
    #define ALOX_REL_LOG_CI_VFYVAL         ALOX_REL_LOG_CI_VFYBIT
#else
    #define ALOX_REL_LOG_CI_VFYVAL         0
#endif


#define    ALOX_COMPATIBILITY_VERYFIER  (   ALOX_DBG_LOG_VFYVAL       \
                                          + ALOX_DBG_LOG_CI_VFYVAL    \
                                          + ALOX_REL_LOG_VFYVAL       \
                                          + ALOX_REL_LOG_CI_VFYVAL    \
                                        )
#endif

/**
 * @defgroup GrpALoxMacrosLowLevel    ALox Low level Macros
 *
 * The preprocessor macros listed here are the foundation for
 * \ref GrpMacrosDebugLog and \ref GrpMacrosReleaseLog.
 *
 * The definition of the macros is dependent on \ref GrpALoxCodeSelectorSymbols, which in turn
 * mostly depend on \ref GrpALoxCompilerSymbols.<p>
 *
 * Developers that use ALox in standard use cases do not need to know or even change the macros
 * listed here.
 * @{
 */



// #################################################################################################
// Macros to access the Lox instance
// #################################################################################################


/**
 * \def  LOG_LOX
 * The Lox instance used by all debug logging macros. This can be overwritten (prior or after
 * including alox.hpp) to allow different instances of class Lox for debug logging within
 * different source entities. However, other ways to structure log output and to separate
 * log information into different streams exists in ALox and overwriting this macro is not
 * recommended for standard use cases.<p>
 *
 * Note: The definition must provide a reference (not a pointer) to the \b %Lox object.
 *
 * \def  LOX_LOX
 * The Lox instance used by all release logging macros. This has to be set (prior or after
 * including alox.hpp) to provide access to a, dedicated instance of class Lox created for
 * release logging within a software.<br>
 * It is of-course allowed to use different instances within different source entities.
 * However, other ways to structure log output and separate log streams exists in ALox and should
 * be evaluated prior to introducing different instances of class Lox.<p>
 *
 * Note: The definition must provide a reference (not a pointer) to the \b %Lox object.
 */

#if !defined(LOG_LOX)
    #define LOG_LOX       (*aworx::ALox::Log())
#endif

#if defined(IS_DOXYGEN_PARSER)
    #define LOX_LOX
#endif


// #################################################################################################
// Macros for setting the source code info prior to executing a log
// #################################################################################################


/**
 * \def  LOG_ACQUIRE
 * Macro that is placed at the beginning of almost all macros of type \ref GrpMacrosDebugLog.
 * Provides scope information (provided that \ref ALOX_DBG_LOG_CI is set) to the lox and places
 * the debug lox instance access code using \ref LOG_LOX.
 */
#ifdef  ALOX_DBG_LOG_CI
    #define LOG_ACQUIRE     { aworx::Lox& log= LOG_LOX; log.SetScopeInfo( ALIB_SRC_INFO_PARAMS );
#else
    #define LOG_ACQUIRE     { aworx::Lox& log= LOG_LOX; log.SetScopeInfo( nullptr, 0, nullptr );
#endif

/**
 * \def  LOG_RELEASE
 * Macro that is placed at the end of almost all macros of type \ref GrpMacrosDebugLog.
 * Releases the lox which was acquired when passing scope information (in macro \ref LOG_ACQUIRE.).
 */
#define LOG_RELEASE         log.Release(); }

/**
 * \def  LOX_ACQUIRE
 * Macro that is placed at the beginning of almost all macros of type \ref GrpMacrosReleaseLog.
 * Provides scope information (provided that \ref ALOX_REL_LOG_CI is set) to the lox and places
 * the release lox instance access code using \ref LOX_LOX.
 */
#ifdef  ALOX_REL_LOG_CI
    #define LOX_ACQUIRE     LOX_LOX.SetScopeInfo( ALIB_SRC_INFO_PARAMS );
#else
    #define LOX_ACQUIRE     LOX_LOX.SetScopeInfo( nullptr, 0, nullptr );
#endif

/**
 * \def  LOX_RELEASE
 * Macro that is placed at the end of almost all macros of type \ref GrpMacrosDebugLog.
 * Releases the lox which was acquired when passing scope information (in macro \ref LOG_ACQUIRE.).
 */
#define     LOX_RELEASE     LOX_LOX.Release();

/** @} */ // End of GrpALoxMacrosLowLevel


// #################################################################################################
// Debug logging macros
// #################################################################################################

/**
 * @defgroup GrpMacrosDebugLog ALox Macros For Debug Logging
 *
 * The macros listed here, are provided to place debug <em>Log Statements</em> within source code using ALox.
 * Besides that, macros controlling and setting preferences for ALox exists.<p>
 *
 * The exclusive use of these macros should be sufficient to support most of common debug logging
 * statements with ALox. Should some functionality be not available easily with using the macros,
 * of-course, the normal C++ API of ALox can be used in parallel to using the macros.
 * For proper pruning of code that is using the C++ API, such code has to be enclosed by<br>
 \verbatim
 #if defined(ALOX_DBG_LOG)
    ...
 #endif
 \endverbatim
 * lines, or embedded in macro \ref Log_Prune.
 * \note To be clear: When using the macros, the <em>\#if / \#endif</em> statements are \e not needed!
 *
 * All macro names are prefixed "Log_". This implies that they are macros to implement *debug*
 * logging. In contrast to this, a set of similar macros exists for release logging
 * (see \ref GrpMacrosReleaseLog). Those are
 * prefixed "Lox_". (The choice of the prefixes *Log_* and *Lox* provide  maximum source code
 * compatibility of ALox for C++ log lines in comparison to ALox for C# and ALox for Java.<p>
 *
 * Most macros make use of the macro \ref LOG_LOX, which references a singleton
 * object of class \ref aworx::lox::Lox "Lox" that is used for all debug logging.
 * This singleton concept covers most
 * uses cases for debug logging. If more flexibility is wanted, then either the macro
 * \ref LOG_LOX might be changed for different compilation units or the ALox C++
 * API might be used instead of the macros listed here.
 *
 * \note The ALox Scope Domain mechanism as well as other ALox functionality which relies on \e Scopes
 * rely on the information provided by ALib macro \ref ALIB_SRC_INFO_PARAMS.
 * Changing this macro, might cause these mechanism to fail.
 * @{
 */


/**
 * \def  Log_Prune
 * This very simple macro is used for pruning debug <em>Log Statements</em>.
 * While it is used as a building block of all other macros for debug logging, for code entities
 * using ALox, it provides an easy way to prune code lines that get inserted purely to support
 * logging, e.g. to create ALox loggers or to prepare more complex log output. (The alternative
 * way is to enclose such code within
 * <code> \#ifdef ALOX_DBG_LOG </code> / <code> \#endif </code> preprocessor lines.
 * <p>
 *
 * Depends on \ref ALOX_DBG_LOG. If this is set, the macro just copies the code provided, else it
 * does not copy it, hence removes the code.
 */
#if defined(ALOX_DBG_LOG)
    #define Log_Prune( ... ) __VA_ARGS__
#else
    #define Log_Prune( ... )
#endif


/** Invokes \ref aworx::lox::Lox::SetSourcePathTrimRule "Lox::SetSourcePathTrimRule" on the debug singleton of class Lox defined in macro \ref LOG_LOX. */
#define Log_SetSourcePathTrimRule(...)          { Log_Prune( LOG_ACQUIRE LOG_LOX.SetSourcePathTrimRule( __VA_ARGS__ );    LOG_RELEASE ) }

/** Invokes \ref aworx::lox::Lox::ClearSourcePathTrimRules "Lox::ClearSourcePathTrimRules" on the debug singleton of class Lox defined in macro \ref LOG_LOX. */
#define Log_ClearSourcePathTrimRules(...)       { Log_Prune( LOG_ACQUIRE LOG_LOX.ClearSourcePathTrimRules( __VA_ARGS__ ); LOG_RELEASE ) }

/** Invokes \ref aworx::lox::Log::AddDebugLogger(aworx::lox::Lox*) "Log::AddDebugLogger" to create, add and configure a default debug logger suitable for the platform and toolset. */
#define Log_AddDebugLogger()                    { Log_Prune( LOG_ACQUIRE    Log::AddDebugLogger   ( &LOG_LOX );           LOG_RELEASE ) }

/** Invokes \ref aworx::lox::Log::RemoveDebugLogger "Log::RemoveDebugLogger" to remove and delete a debug logger created by \ref aworx::lox::Log::AddDebugLogger "Log::AddDebugLogger". */
#define Log_RemoveDebugLogger()                 { Log_Prune( LOG_ACQUIRE    Log::RemoveDebugLogger( &LOG_LOX );           LOG_RELEASE ) }

/** Invokes \ref aworx::lox::Lox::GetLogger "Lox::GetLogger" on the debug singleton of class Lox defined in macro \ref LOG_LOX. */
#define Log_GetLogger( identifier, name )         Log_Prune( aworx::lox::core::Logger* identifier;                                      \
                                                             LOG_ACQUIRE  identifier= log.GetLogger( name );              LOG_RELEASE )

/** Invokes \ref aworx::lox::Lox::RemoveLogger "Lox::RemoveLogger" on the debug singleton of class Lox defined in macro \ref LOG_LOX. */
#define Log_RemoveLogger( logger)               { Log_Prune( LOG_ACQUIRE LOG_LOX.RemoveLogger ( logger );                 LOG_RELEASE ) }

/** Invokes \ref aworx::lox::Lox::SetDomain "Lox::SetDomain" on the debug singleton of class Lox defined in macro \ref LOG_LOX. */
#define Log_SetDomain(...)                      { Log_Prune( LOG_ACQUIRE LOG_LOX.SetDomain    ( __VA_ARGS__ );            LOG_RELEASE ) }

/** Invokes \ref aworx::lox::Lox::RemoveThreadDomain "Lox::RemoveThreadDomain" on the debug singleton of class Lox defined in macro \ref LOG_LOX. */
#define Log_RemoveThreadDomain(...)             { Log_Prune( LOG_ACQUIRE LOG_LOX.RemoveThreadDomain( __VA_ARGS__ );       LOG_RELEASE ) }

/** Invokes \ref aworx::lox::Lox::SetDomainSubstitutionRule "Lox::SetDomainSubstitutionRule" on the debug singleton of class Lox defined in macro \ref LOG_LOX. */
#define Log_SetDomainSubstitutionRule(...)      { Log_Prune( LOG_ACQUIRE LOG_LOX.SetDomainSubstitutionRule( __VA_ARGS__ );         LOG_RELEASE ) }

/** Invokes one of the overloaded methods \ref aworx::lox::Lox::SetVerbosity "Lox::SetVerbosity" on the debug singleton of class Lox defined in macro \ref LOG_LOX. */
#define Log_SetVerbosity(...)                   { Log_Prune( LOG_ACQUIRE LOG_LOX.SetVerbosity    ( __VA_ARGS__ );            LOG_RELEASE ) }

/** Invokes \ref aworx::lox::Lox::SetStartTime "Lox::SetStartTime" on the debug singleton of class Lox defined in macro \ref LOG_LOX. */
#define Log_SetStartTime( time, loggerName )    { Log_Prune( LOG_ACQUIRE LOG_LOX.SetStartTime ( time, loggerName);        LOG_RELEASE ) }

/** Invokes \ref aworx::lox::Lox::MapThreadName "Lox::MapThreadName" on the debug singleton of class Lox defined in macro \ref LOG_LOX. */
#define Log_MapThreadName( threadName )         { Log_Prune( LOG_ACQUIRE LOG_LOX.MapThreadName( threadName );             LOG_RELEASE ) }

/** Invokes \ref aworx::lox::Lox::State "Lox::State" on the debug singleton of class Lox defined in macro \ref LOG_LOX. */
#define Log_LogState(...)                      { Log_Prune( LOG_ACQUIRE LOG_LOX.State    ( __VA_ARGS__ );            LOG_RELEASE ) }

/** Invokes \ref aworx::lox::Lox::Verbose "Lox::Verbose" on the debug singleton of class Lox defined in macro \ref LOG_LOX. */
#define Log_Verbose(...)                        { Log_Prune( LOG_ACQUIRE LOG_LOX.Verbose      ( __VA_ARGS__ );            LOG_RELEASE ) }

/** Invokes \ref aworx::lox::Lox::Info "Lox::Info" on the debug singleton of class Lox defined in macro \ref LOG_LOX. */
#define Log_Info(...)                           { Log_Prune( LOG_ACQUIRE LOG_LOX.Info         ( __VA_ARGS__ );            LOG_RELEASE ) }

/** Invokes \ref aworx::lox::Lox::Warning "Lox::Warning" on the debug singleton of class Lox defined in macro \ref LOG_LOX. */
#define Log_Warning(...)                        { Log_Prune( LOG_ACQUIRE LOG_LOX.Warning      ( __VA_ARGS__ );            LOG_RELEASE ) }

/** Invokes \ref aworx::lox::Lox::Error "Lox::Error" on the debug singleton of class Lox defined in macro \ref LOG_LOX. */
#define Log_Error(...)                          { Log_Prune( LOG_ACQUIRE LOG_LOX.Error        ( __VA_ARGS__ );            LOG_RELEASE ) }

/** Invokes \ref aworx::lox::Lox::Assert "Lox::Assert" on the debug singleton of class Lox defined in macro \ref LOG_LOX. */
#define Log_Assert(...)                         { Log_Prune( LOG_ACQUIRE LOG_LOX.Assert       ( __VA_ARGS__ );            LOG_RELEASE ) }

/** Invokes \ref aworx::lox::Lox::If "Lox::If" on the debug singleton of class Lox defined in macro \ref LOG_LOX. */
#define Log_If(...)                             { Log_Prune( LOG_ACQUIRE LOG_LOX.If           ( __VA_ARGS__ );            LOG_RELEASE ) }

/** Invokes \ref aworx::lox::Lox::Once "Lox::Once" on the debug singleton of class Lox defined in macro \ref LOG_LOX. */
#define Log_Once(...)                           { Log_Prune( LOG_ACQUIRE LOG_LOX.Once         ( __VA_ARGS__ );            LOG_RELEASE ) }

/** Invokes \ref aworx::lox::Lox::Entry "Lox::Entry" on the debug singleton of class Lox defined in macro \ref LOG_LOX. */
#define Log_Entry(...)                          { Log_Prune( LOG_ACQUIRE LOG_LOX.Entry         ( __VA_ARGS__ );            LOG_RELEASE ) }

/** Invokes \ref aworx::lox::Lox::SetPrefix "Lox::SetPrefix" on the debug singleton of class Lox defined in macro \ref LOG_LOX. */
#define Log_SetPrefix(...)                      { Log_Prune( LOG_ACQUIRE LOG_LOX.SetPrefix    ( __VA_ARGS__ );            LOG_RELEASE ) }

/** Invokes \ref aworx::lox::Lox::Store "Lox::Store" on the debug singleton of class Lox defined in macro \ref LOG_LOX. */
#define Log_Store(...)                          { Log_Prune( LOG_ACQUIRE LOG_LOX.Store        ( __VA_ARGS__ );            LOG_RELEASE ) }

/** Invokes \ref aworx::lox::Lox::Retrieve "Lox::Retrieve" on the debug singleton of class Lox defined in macro \ref LOG_LOX. */
#define Log_Retrieve(data,...)                    Log_Prune( LogData* data;                                                             \
                                                             LOG_ACQUIRE data= log.Retrieve( __VA_ARGS__ );               LOG_RELEASE )

/** @} */


// #################################################################################################
// Release logging macros
// #################################################################################################
/**
 * @defgroup GrpMacrosReleaseLog        ALox Macros For Release Logging
 *
 * The macros listed here, are provided to place release <em>Log Statements</em> within source code using
 * ALox. Besides that, macros controlling and setting preferences for ALox exists.<p>
 *
 * The exclusive use of these macros should be sufficient to support most of common release logging
 * statements with ALox. Should some functionality be not available easily using the macros,
 * of-course, the normal C++ API of ALox can be used in parallel to using the macros.
 * Code that is using the C++ API might be enclosed by<br>
 \verbatim
 #if defined(ALOX_REL_LOG)
    ...
 #endif
 \endverbatim
 * lines, to remove them when compiling a release version of the software unit with pruned
 * release log macros. Alternatively, such code might be embedded in macro \ref Lox_Prune.
 * (Such compilation would be made by passing \ref ALOX_REL_LOG_OFF to the
 * compiler and could be useful in certain situations.) <p>
 *
 * Prior to using the macros, each code entity has to set the preprocessor macro \ref LOX_LOX
 * This can be done in a general header file of the software,
 * (e.g. the same that exposes the release-Lox object to that source), or, in more complex
 * scenarios with more than one release-Lox object, at any other appropriate source location.
 *
 * All macro names are prefixed with the term <b>Lox_</b>. This implies that they are macros to
 * implement <em>release logging</em>. In contrast to this, a set of similar macros exists for
 * <em>debug logging</em> (see \ref GrpMacrosDebugLog). Those are
 * prefixed <b>Log_</b>.
 * \note The choice of the prefixes <b>Log_</b> and <b>Lox_</b> was made to provide  maximum source
 * code compatibility of <em>ALox for C++</em> log lines in comparison to other ALox implementations
 * in other programming languages, which provide a class Log as a kind of 'mirror' class of
 * class Lox. Invocations to class Log get pruned in these languages. <p>
 *
 * Most macros make use of the macro \ref LOX_LOX, which references a singleton
 * object of class \ref aworx::lox::Lox "Lox" that is used for all release logging.
 * This singleton concept covers most
 * uses cases for release logging. If more flexibility is wanted, then either the macro
 * \ref LOX_LOX might be changed for different compilation units or the ALox C++
 * API might be used instead of the macros listed here.
 * @{
 */


/**
 * \def  Lox_Prune
 * This very simple macro is used for pruning release <em>Log Statements</em> in the moment release logging
 * gets disabled (what in standard release scenarios is not done).<p>
 *
 * While it is used as a building block of all other macros for release logging, for code entities
 * using ALox, it provides an easy way to prune code lines that get inserted purely to support
 * logging, e.g. to create ALox loggers or to prepare more complex log output. (The alternative
 * way is to enclose such code within
 * <code> \#ifdef ALOX_REL_LOG </code> / <code> \#endif </code> preprocessor lines.
 * <p>
 *
 * Depends on \ref ALOX_REL_LOG. If this is set, the macro just copies the code provided, else it
 * does not copy it, hence removes the code.
 */

#if defined(ALOX_REL_LOG)
    #define Lox_Prune( releaseLogCode ) releaseLogCode
#else
    #define Lox_Prune( releaseLogCode )
#endif



/** Invokes \ref aworx::lox::Lox::SetSourcePathTrimRule "Lox::SetSourcePathTrimRule" on the object of type Lox defined in macro \ref LOX_LOX. */
#define Lox_SetSourcePathTrimRule(...)      { Lox_Prune( LOX_ACQUIRE LOX_LOX.SetSourcePathTrimRule( __VA_ARGS__ ); LOX_RELEASE ) }

/** Invokes \ref aworx::lox::Lox::ClearSourcePathTrimRules "Lox::ClearSourcePathTrimRules" on the object of type Lox defined in macro \ref LOX_LOX. */
#define Lox_ClearSourcePathTrimRules(...)   { Lox_Prune( LOX_ACQUIRE LOX_LOX.ClearSourcePathTrimRules( __VA_ARGS__ ); LOX_RELEASE ) }

/** Invokes \ref aworx::lox::Lox::GetLogger "Lox::GetLogger" on the object of type Lox defined in macro \ref LOX_LOX. */
#define Lox_GetLogger( identifier, name )     Lox_Prune( LOX_ACQUIRE aworx::lox::core::Logger* identifier= LOX_LOX.GetLogger ( name ); LOX_RELEASE )

/** Invokes \ref aworx::lox::Lox::RemoveLogger "Lox::RemoveLogger" on the object of type Lox defined in macro \ref LOX_LOX. */
#define Lox_RemoveLogger( logger )          { Lox_Prune( LOX_ACQUIRE LOX_LOX.RemoveLogger ( logger );        LOX_RELEASE ) }


/** Invokes \ref aworx::lox::Lox::SetDomain "Lox::SetDomain" on the object of type Lox defined in macro \ref LOX_LOX.
 * \attention
 *  If \ref ALOX_REL_LOG_CI is not set, which is the default for release logging, and when used with language-related
 *  \e Scopes, this method will log an internal warning and will not be effective in respect to
 *  \e %Scope.Path, \e %Scope.Filename, and \e %Scope.Method. See ALox user manual for detailed information.
 *  If Scope Domains based on source-related scopes should be supported in release logging, the
 *  software entity has to be compiled with precompiler symbol \ref ALOX_REL_LOG_CI_ON.
 *  Note that one effect of setting this symbol is, that information on source code paths and file names, as well as
 *  method names make their way into the release executable. This may not be wanted.
 */
#define Lox_SetDomain(...)                  { Lox_Prune( LOX_ACQUIRE LOX_LOX.SetDomain(__VA_ARGS__);            LOX_RELEASE ) }

/** Invokes \ref aworx::lox::Lox::RemoveThreadDomain "Lox::RemoveThreadDomain" on the object of type Lox defined in macro \ref LOX_LOX. */
#define Lox_RemoveThreadDomain(...)         { Lox_Prune( LOX_ACQUIRE LOX_LOX.RemoveThreadDomain( __VA_ARGS__ ); LOX_RELEASE ) }

/** Invokes \ref aworx::lox::Lox::SetDomainSubstitutionRule "Lox::SetDomainSubstitutionRule" on the object of type Lox defined in macro \ref LOX_LOX. */
#define Lox_SetDomainSubstitutionRule(...)  { Lox_Prune( LOX_ACQUIRE LOX_LOX.SetDomainSubstitutionRule( __VA_ARGS__ );   LOX_RELEASE ) }

/** Invokes one of the overloaded methods \ref aworx::lox::Lox::SetVerbosity "Lox::SetVerbosity" on the object of type Lox defined in macro \ref LOX_LOX. */
#define Lox_SetVerbosity(...)               { Lox_Prune( LOX_ACQUIRE LOX_LOX.SetVerbosity    ( __VA_ARGS__ );   LOX_RELEASE ) }

/** Invokes \ref aworx::lox::Lox::SetStartTime "Lox::SetStartTime" on the object of type Lox defined in macro \ref LOX_LOX. */
#define Lox_SetStartTime( time, loggerName ){ Lox_Prune( LOX_ACQUIRE LOX_LOX.SetStartTime ( time, loggerName ); LOX_RELEASE ) }

/** Invokes \ref aworx::lox::Lox::MapThreadName "Lox::MapThreadName" on the object of type Lox defined in macro \ref LOX_LOX. */
#define Lox_MapThreadName( threadName )     { Lox_Prune( LOX_ACQUIRE LOX_LOX.MapThreadName( threadName );       LOX_RELEASE ) }

/** Invokes \ref aworx::lox::Lox::State "Lox::State" on the object of type Lox defined in macro \ref LOX_LOX. */
#define Lox_LogState(...)                  { Lox_Prune( LOX_ACQUIRE LOX_LOX.State    ( __VA_ARGS__ );      LOX_RELEASE ) }

/** Invokes \ref aworx::lox::Lox::Verbose "Lox::Verbose" on the object of type Lox defined in macro \ref LOX_LOX. */
#define Lox_Verbose(...)                    { Lox_Prune( LOX_ACQUIRE LOX_LOX.Verbose      ( __VA_ARGS__ );      LOX_RELEASE ) }

/** Invokes \ref aworx::lox::Lox::Info "Lox::Info" on the object of type Lox defined in macro \ref LOX_LOX. */
#define Lox_Info(...)                       { Lox_Prune( LOX_ACQUIRE LOX_LOX.Info         ( __VA_ARGS__ );      LOX_RELEASE ) }

/** Invokes \ref aworx::lox::Lox::Warning "Lox::Warning" on the object of type Lox defined in macro \ref LOX_LOX. */
#define Lox_Warning(...)                    { Lox_Prune( LOX_ACQUIRE LOX_LOX.Warning      ( __VA_ARGS__ );      LOX_RELEASE ) }

/** Invokes \ref aworx::lox::Lox::Error "Lox::Error" on the object of type Lox defined in macro \ref LOX_LOX. */
#define Lox_Error(...)                      { Lox_Prune( LOX_ACQUIRE LOX_LOX.Error        ( __VA_ARGS__ );      LOX_RELEASE ) }

/** Invokes \ref aworx::lox::Lox::Assert "Lox::Assert" on the object of type Lox defined in macro \ref LOX_LOX. */
#define Lox_Assert(...)                     { Lox_Prune( LOX_ACQUIRE LOX_LOX.Assert       ( __VA_ARGS__);       LOX_RELEASE ) }

/** Invokes \ref aworx::lox::Lox::If "Lox::Assert" on the object of type Lox defined in macro \ref LOX_LOX. */
#define Lox_If(...)                         { Lox_Prune( LOX_ACQUIRE LOX_LOX.If           ( __VA_ARGS__);       LOX_RELEASE ) }

/** Invokes \ref aworx::lox::Lox::Once "Lox::Once" on the object of type Lox defined in macro \ref LOX_LOX. */
#define Lox_Once(...)                       { Lox_Prune( LOX_ACQUIRE LOX_LOX.Once         ( __VA_ARGS__ );      LOX_RELEASE ) }

/** Invokes \ref aworx::lox::Lox::Entry "Lox::Entry" on the object of type Lox defined in macro \ref LOX_LOX. */
#define Lox_Entry(...)                      { Lox_Prune( LOX_ACQUIRE LOX_LOX.Entry         ( __VA_ARGS__ );      LOX_RELEASE ) }


/** Invokes \ref aworx::lox::Lox::Store "Lox::Store" on the object of type Lox defined in macro \ref LOX_LOX.
 *  \attention  If \ref ALOX_REL_LOG_CI is not set, which is the default for release logging
 *             statements, Log Data can not be used in conjunction with language-related \e Scopes.<br>
 *             If <em>Log Data</em> should be supported in release logging, the software entity has to be compiled
 *             with precompiler symbol \ref ALOX_REL_LOG_CI_ON. Note that one effect of setting
 *             this symbol is, that information on source code paths and file names, as well as
 *             method names make their way into the release executable. This may not be wanted.<br>
 *             In general, methods \b Lox::Store and \b Lox::Retrieve should exclusively be used for
 *             debug logging. See user manual for more information.
 */
#define Lox_Store(...)                      { Lox_Prune( LOX_ACQUIRE LOX_LOX.Store        ( __VA_ARGS__ );      LOX_RELEASE ) }

/** Invokes \ref aworx::lox::Lox::Retrieve "Lox::Retrieve" on the object of type Lox defined in macro \ref LOX_LOX. */
#define Lox_Retrieve(data,...)                Lox_Prune( LOX_ACQUIRE LogData* data= LOX_LOX.Retrieve( __VA_ARGS__ );  LOX_RELEASE )

/** Invokes \ref aworx::lox::Lox::SetPrefix "Lox::SetPrefix" on the object of type Lox defined in macro \ref LOX_LOX. */
#define Lox_SetPrefix(...)                  { Lox_Prune( LOX_ACQUIRE LOX_LOX.SetPrefix     ( __VA_ARGS__ );     LOX_RELEASE ) }

/** @} */ // GrpMacrosReleaseLog



#endif // HPP_ALOX_MACROS

