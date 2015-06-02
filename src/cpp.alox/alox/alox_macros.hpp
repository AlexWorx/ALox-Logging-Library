// #################################################################################################
//  aworx::lox - ALox Logging Library
//
//  (c) 2013-2015 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
/** @file */ //<- needed for Doxygen include

#ifndef HPP_AWORX_ALOX_ALOX_MACROS
#define HPP_AWORX_ALOX_ALOX_MACROS 1


#if !defined(HPP_AWORX_ALOX_ALOX)
    #error "include alox.hpp instead of alox_macros.hpp"
#endif

// #################################################################################################
// Macros not related to logging
// #################################################################################################

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


/**
 * \def  ALOX_COMPILED_CLASS_SIZE_VERIFYER
 * This is a helper macro used by the initialization method
 * \ref aworx::lox::Log::InitALox "Log::InitALox" of the ALox library to verify that different
 * compilation units have used the same compilation settings to compile ALox.
 */ // (keep indent like this, for the sake of doxygen formatting)
#define    ALOX_COMPILED_CLASS_SIZE_VERIFYER        \
sizeof(aworx::lox::Lox)              + \
sizeof(aworx::lox::core::CallerInfo) + \
sizeof(aworx::lox::core::LogDomain)  + \
sizeof(aworx::util::ThreadLock)      + \
sizeof(aworx::util::Thread)          + \
sizeof(aworx::util::Ticks)           + \
sizeof(aworx::util::AString)


// #################################################################################################
// ALOX_SYMBOL_DEBUG
// #################################################################################################

/**
 * \def  ALOX_COMPILER_SYMBOL_SETTINGS
 * This is a helper macro that assembles an object named <em>acss</em> of type AString and fills
 * it with debug information about the ALox compilation symbol setting. <br>
 * If compilation or runtime problems occur, this macro can be used to check which symbols have
 * been set for the compilation unit this macro is placed in.<br>
 * For example, a simple code insertion into the bootstrap part of the compilation unit in
 * question could look like this:
 \verbatim
{
    ALOX_COMPILER_SYMBOL_SETTINGS
    cout << "ALox compilation symbols: "    << endl;
    cout << acss.Buffer()  << endl << endl;
}
 \endverbatim
 */

#if !defined( DOXYGEN_OMIT_THIS_PLEASE )
#ifdef ALOX_DLL_EXPORTS
    #define ALOX_CSS_X1 "[X] ALOX_DLL_EXPORTS"
#else
    #define ALOX_CSS_X1 "[ ] ALOX_DLL_EXPORTS"
#endif
#ifdef AWXU_DEBUG
    #define ALOX_CSS_X2 "[X] AWXU_DEBUG"
#else
    #define ALOX_CSS_X2 "[ ] AWXU_DEBUG"
#endif
#ifdef AWXU_DEBUG_ASTRING
    #define ALOX_CSS_X3 "[X] AWXU_DEBUG_ASTRING"
#else
    #define ALOX_CSS_X3 "[ ] AWXU_DEBUG_ASTRING"
#endif
#ifdef AWXU_FEAT_THREADS
    #define ALOX_CSS_X4 "[X] AWXU_FEAT_THREADS"
#else
    #define ALOX_CSS_X4 "[ ] AWXU_FEAT_THREADS"
#endif


#ifdef ALOX_DBG_LOG
    #define ALOX_CSS_L1 "[X] ALOX_DBG_LOG"
#else
    #define ALOX_CSS_L1 "[ ] ALOX_DBG_LOG"
#endif
#ifdef ALOX_DBG_LOG_CI
    #define ALOX_CSS_L2 "[X] ALOX_DBG_LOG_CI"
#else
    #define ALOX_CSS_L2 "[ ] ALOX_DBG_LOG_CI"
#endif
#ifdef ALOX_REL_LOG
    #define ALOX_CSS_L3 "[X] ALOX_REL_LOG"
#else
    #define ALOX_CSS_L3 "[ ] ALOX_REL_LOG"
#endif
#ifdef ALOX_REL_LOG_CI
    #define ALOX_CSS_L4 "[X] ALOX_REL_LOG_CI"
#else
    #define ALOX_CSS_L4 "[ ] ALOX_REL_LOG_CI"
#endif
#endif // DOXYGEN_OMIT_THIS_PLEASE

#define    ALOX_COMPILER_SYMBOL_SETTINGS                \
aworx::util::AString acss;                              \
acss << ALOX_CSS_X1 << aworx::util::AString::NEWLINE    \
     << ALOX_CSS_X2 << aworx::util::AString::NEWLINE    \
     << ALOX_CSS_X3 << aworx::util::AString::NEWLINE    \
     << ALOX_CSS_X4 << aworx::util::AString::NEWLINE    \
     << ALOX_CSS_L1 << aworx::util::AString::NEWLINE    \
     << ALOX_CSS_L2 << aworx::util::AString::NEWLINE    \
     << ALOX_CSS_L3 << aworx::util::AString::NEWLINE    \
     << ALOX_CSS_L4 << aworx::util::AString::NEWLINE    \
    ;



// #################################################################################################
// Macros to access the Lox instance
// #################################################################################################


/**
 * \def  ALOX_DBG_LOX_INSTANCE
 * The Lox instance used by all debug logging macros. This can be overwritten (prior or after
 * including alox.hpp) to allow different instances of class Lox for debug logging within
 * different source entities. However, other ways to structure log output and to separate
 * log information into different streams exists in ALox and overwriting this macro is not
 * recommended for standard use cases.<p>
 *
 * Note: The definition must include the access operator "." or "->".
 *
 * \def  ALOX_REL_LOX_INSTANCE
 * The Lox instance used by all release logging macros. This has to be overwritten (prior or after
 * including alox.hpp) to provide access to the dedicated instance of class Lox created for
 * release logging within a software.<br>
 * It is of-course allowed to use different instances logging within different source entities.
 * However, other ways to structure log output and separate log streams exists in ALox and should
 * be evaluated prior to introducing different instances of class Lox.<p>
 *
 * Note: The definition must include the access operator "." or "->".
 */

#if !defined(ALOX_DBG_LOX_INSTANCE)
    #define ALOX_DBG_LOX_INSTANCE  aworx::lox::Log::lox->
#endif

#if !defined(ALOX_REL_LOX_INSTANCE)
   #define ALOX_REL_LOX_INSTANCE  lox->
#endif




// #################################################################################################
// Macros for setting the source code info prior to executing a log
// #################################################################################################

/**
 * \def  ALOX_CI_GET
 * This macro fills in the built-in compiler symbols that provide the current source file,
 * line number and function strings.<p>
 * The macro is used by \ref ALOX_DL_PREFIX and \ref ALOX_RL_PREFIX<p>
 *
 * In standard use cases, there is no need to overwrite this macro. Nevertheless, it might
 * be changed to provide other standard information into debug logging.<p>
 *
 * \note The ALox default domain mechanism as well as the ALox code markers rely on the information
 * provided by this macro. Changing this macro, might cause these mechanism to fail.
 * There is no further documentation given here. Users changing this macro should be familiar
 * with the corresponding ALox implementation details.
 */

#if defined( __GNUC__ )
    #define ALOX_CI_GET     __FILE__, __LINE__, __func__
//  #define ALOX_CI_GET     __FILE__, __LINE__, __PRETTY_FUNCTION__

#elif defined ( _MSC_VER )
    #define ALOX_CI_GET     __FILE__, __LINE__, __FUNCTION__
//  #define ALOX_CI_GET     __FILE__, __LINE__, __FUNCSIG__

#else
    #pragma message ("Unknown Platform in file: " __FILE__ )
#endif


/**
 * \def  ALOX_DL_PREFIX
 * Macro that is placed at the beginning of almost all macros of type \ref GrpMacrosDebugLog.
 * Provides caller information (provided that \ref ALOX_DBG_LOG_CI is set) to the lox and places
 * the debug lox instance access code using \ref ALOX_DBG_LOX_INSTANCE.
 */
#ifdef  ALOX_DBG_LOG_CI
    #define ALOX_DL_PREFIX      ALOX_DBG_LOX_INSTANCE AcquireAndSetCI( ALOX_CI_GET );   ALOX_DBG_LOX_INSTANCE
#else
    #define ALOX_DL_PREFIX                                                              ALOX_DBG_LOX_INSTANCE
#endif

/**
 * \def  ALOX_DL_POSTFIX
 * Macro that is placed at the end of almost all macros of type \ref GrpMacrosDebugLog.
 * Releases the lox which was acquired when passing caller information (in macro \ref ALOX_DL_PREFIX).
 */
#ifdef  ALOX_DBG_LOG_CI
    #define ALOX_DL_POSTFIX     ALOX_DBG_LOX_INSTANCE Release();
#else
    #define ALOX_DL_POSTFIX
#endif

/**
 * \def  ALOX_RL_PREFIX
 * Macro that is placed at the beginning of almost all macros of type \ref GrpMacrosReleaseLog.
 * Provides caller information (provided that \ref ALOX_REL_LOG_CI is set) to the lox and places
 * the release lox instance access code using \ref ALOX_REL_LOX_INSTANCE.
 */
#ifdef  ALOX_REL_LOG_CI
    #define ALOX_RL_PREFIX      ALOX_REL_LOX_INSTANCE AcquireAndSetCI( ALOX_CI_GET );   ALOX_REL_LOX_INSTANCE
#else
    #define ALOX_RL_PREFIX                                                              ALOX_REL_LOX_INSTANCE
#endif

/**
 * \def  ALOX_RL_POSTFIX
 * Macro that is placed at the end of almost all macros of type \ref GrpMacrosDebugLog.
 * Releases the lox which was acquired when passing caller information (in macro \ref ALOX_DL_PREFIX).
 */
#ifdef  ALOX_REL_LOG_CI
    #define ALOX_RL_POSTFIX     ALOX_REL_LOX_INSTANCE Release();
#else
    #define ALOX_RL_POSTFIX
#endif

/** @} */ // End of GrpALoxMacrosLowLevel


// #################################################################################################
// Debug logging macros
// #################################################################################################

/**
 * @defgroup GrpMacrosDebugLog ALox Macros For Debug Logging
 *
 * The macros listed here, are provided to place debug log statements within source code using ALox.
 * Besides that, macros controlling and setting preferences for ALox exists.<p>
 *
 * The exclusive use of these macros should be sufficient to support most of common debug logging
 * statements with ALox. Should some functionality be not available easily using the macros,
 * of-course, the normal C++ API of ALox can be used in parallel to using the macros.
 * Code that is using the C++ API has to be enclosed by<br>
 \verbatim
 #ifdef ALOX_DBG_LOG
    ...
 #endif
 \endverbatim
 * lines, to remove them when compiling a release version of the software unit.<p>
 *
 * All macro names are prefixed "Log_". This implies that they are macros to implement *debug*
 * logging. In contrast to this, a set of similar macros exists for release logging. Those are
 * prefixed "Lox_". (The choice of the prefixes *Log_* and *Lox* provide  maximum source code
 * compatibility of ALox for C++ log lines in comparison to ALox for C# and ALox for Java.<p>
 *
 * Most macros make use of the macro \ref ALOX_DBG_LOX_INSTANCE, which references a singleton
 * object of class # Lox that is used for all debug logging. This singleton concept covers most
 * uses cases for debug logging. If more flexibility is wanted, then either the macro
 * \ref ALOX_DBG_LOX_INSTANCE might be changed for different compilation units or the ALox C++
 * API might be used instead of the macros listed here.
 *
 * @{
 */


/**
 * \def  Log_Prune
 * This very simple macro is used for pruning debug log statements.
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
    #define Log_Prune( debugLogCode  ) debugLogCode
#else
    #define Log_Prune( debugLogCode  )
#endif


/** Invokes \ref aworx::lox::Lox::AddLogger "Lox::AddLogger" on the debug singleton of class Lox defined in macro \ref ALOX_DBG_LOX_INSTANCE. */
#define Log_AddLogger(      logger                           )  { Log_Prune( ALOX_DL_PREFIX AddLogger    ( logger                            );  ALOX_DL_POSTFIX ) }

/** Invokes \ref aworx::lox::Lox::AddLogger "Lox::AddLogger" on the debug singleton of class Lox defined in macro \ref ALOX_DBG_LOX_INSTANCE. */
#define Log_AddLoggerD(     logger, internalDomainLevel      )  { Log_Prune( ALOX_DL_PREFIX AddLogger    ( logger, internalDomainLevel       );  ALOX_DL_POSTFIX ) }

/** Invokes \ref aworx::lox::Lox::RemoveLoggers "Lox::RemoveLoggers" on the debug singleton of class Lox defined in macro \ref ALOX_DBG_LOX_INSTANCE. */
#define Log_RemoveLoggers(  filter                           )  { Log_Prune( ALOX_DL_PREFIX RemoveLoggers( filter                            );  ALOX_DL_POSTFIX ) }

/** Invokes \ref aworx::lox::Lox::RemoveLoggers "Lox::RemoveLoggers" on the debug singleton of class Lox defined in macro \ref ALOX_DBG_LOX_INSTANCE. */
#define Log_RemoveLogger(   logger                           )  { Log_Prune( ALOX_DL_PREFIX RemoveLogger ( logger                            );  ALOX_DL_POSTFIX ) }


/** Invokes \ref aworx::lox::Lox::RegDomain "Lox::RegDomain" on the debug singleton of class Lox
 * defined in macro \ref ALOX_DBG_LOX_INSTANCE.
 *  \attention If \ref ALOX_DBG_LOG_CI is not defined (by passing the precompiler symbol
 *             \ref ALOX_DBG_LOG_CI_OFF when compiling the source entity), the parameter scope
 *             is ignored due to the lack of caller information.
 *             As a result, this call in this case can not be used to set a default domain.
 *             Instead, a domain name has to be specified explicitly with each log invocation.<br>
 */

#if defined( ALOX_DBG_LOG_CI )
    #define Log_RegDomain(      domain, scope                )  { Log_Prune( ALOX_DL_PREFIX RegDomain    ( domain, scope                     );  ALOX_DL_POSTFIX ) }
#else
    #define Log_RegDomain(      domain, scope                )  { Log_Prune( ALOX_DL_PREFIX RegDomain    ( domain                            );  ALOX_DL_POSTFIX ) }
#endif

/** Invokes \ref aworx::lox::Lox::SetDomain "Lox::SetDomain" on the debug singleton of class Lox defined in macro \ref ALOX_DBG_LOX_INSTANCE. */
#define Log_SetDomain(      domain, domainLevel              )  { Log_Prune( ALOX_DL_PREFIX SetDomain    ( domain, domainLevel               );  ALOX_DL_POSTFIX ) }

/** Invokes \ref aworx::lox::Lox::SetDomain "Lox::SetDomain" on the debug singleton of class Lox defined in macro \ref ALOX_DBG_LOX_INSTANCE. */
#define Log_SetDomainR(     domain, domainLevel, rec         )  { Log_Prune( ALOX_DL_PREFIX SetDomain    ( domain, domainLevel, rec          );  ALOX_DL_POSTFIX ) }

/** Invokes \ref aworx::lox::Lox::SetDomain "Lox::SetDomain" on the debug singleton of class Lox defined in macro \ref ALOX_DBG_LOX_INSTANCE. */
#define Log_SetDomainF(     domain, domainLevel,      filter )  { Log_Prune( ALOX_DL_PREFIX SetDomain    ( domain, domainLevel, true, filter );  ALOX_DL_POSTFIX ) }

/** Invokes \ref aworx::lox::Lox::SetDomain "Lox::SetDomain" on the debug singleton of class Lox defined in macro \ref ALOX_DBG_LOX_INSTANCE. */
#define Log_SetDomainRF(    domain, domainLevel, rec, filter )  { Log_Prune( ALOX_DL_PREFIX SetDomain    ( domain, domainLevel, rec,  filter );  ALOX_DL_POSTFIX ) }

/** Invokes \ref aworx::lox::Lox::SetDisabled "Lox::SetDisabled" on the debug singleton of class Lox defined in macro \ref ALOX_DBG_LOX_INSTANCE. */
#define Log_SetDisabled(    disabled, filter                 )  { Log_Prune( ALOX_DL_PREFIX SetDisabled  ( disabled, filter                  );  ALOX_DL_POSTFIX ) }

/** Invokes \ref aworx::lox::Lox::SetStartTime "Lox::SetStartTime" on the debug singleton of class Lox defined in macro \ref ALOX_DBG_LOX_INSTANCE. */
#define Log_SetStartTime(   time, filter                     )  { Log_Prune( ALOX_DL_PREFIX SetStartTime ( time, filter                      );  ALOX_DL_POSTFIX ) }

/** Invokes \ref aworx::lox::Lox::MapThreadName "Lox::MapThreadName" on the debug singleton of class Lox defined in macro \ref ALOX_DBG_LOX_INSTANCE. */
#define Log_MapThreadName(  threadName                       )  { Log_Prune( ALOX_DL_PREFIX MapThreadName( threadName                        );  ALOX_DL_POSTFIX ) }

/** Invokes \ref aworx::lox::Lox::LogConfig "Lox::LogConfig" on the debug singleton of class Lox defined in macro \ref ALOX_DBG_LOX_INSTANCE. */
#define Log_LogConfig(      domain, logLevel, headl          )  { Log_Prune( ALOX_DL_PREFIX LogConfig    ( domain, logLevel, headl           );  ALOX_DL_POSTFIX ) }

/** Invokes \ref aworx::lox::Lox::LogConfig "Lox::LogConfig" on the debug singleton of class Lox defined in macro \ref ALOX_DBG_LOX_INSTANCE. */
#define Log_LogConfigF(     domain, logLevel, headl, filter  )  { Log_Prune( ALOX_DL_PREFIX LogConfig    ( domain, logLevel, headl, filter   );  ALOX_DL_POSTFIX ) }

/** Invokes \ref aworx::lox::Lox::Verbose "Lox::Verbose" on the debug singleton of class Lox defined in macro \ref ALOX_DBG_LOX_INSTANCE. */
#define Log_Verbose(                msg                      )  { Log_Prune( ALOX_DL_PREFIX Verbose      (            msg                    );  ALOX_DL_POSTFIX ) }

/** Invokes \ref aworx::lox::Lox::Verbose "Lox::Verbose" on the debug singleton of class Lox defined in macro \ref ALOX_DBG_LOX_INSTANCE. */
#define Log_VerboseD(       domain, msg                      )  { Log_Prune( ALOX_DL_PREFIX Verbose      (    domain, msg                    );  ALOX_DL_POSTFIX ) }

/** Invokes \ref aworx::lox::Lox::Info "Lox::Info" on the debug singleton of class Lox defined in macro \ref ALOX_DBG_LOX_INSTANCE. */
#define Log_Info(                   msg                      )  { Log_Prune( ALOX_DL_PREFIX Info         (            msg                    );  ALOX_DL_POSTFIX ) }

/** Invokes \ref aworx::lox::Lox::Info "Lox::Info" on the debug singleton of class Lox defined in macro \ref ALOX_DBG_LOX_INSTANCE. */
#define Log_InfoD(          domain, msg                      )  { Log_Prune( ALOX_DL_PREFIX Info         (    domain, msg                    );  ALOX_DL_POSTFIX ) }

/** Invokes \ref aworx::lox::Lox::Warning "Lox::Warning" on the debug singleton of class Lox defined in macro \ref ALOX_DBG_LOX_INSTANCE. */
#define Log_Warning(                msg                      )  { Log_Prune( ALOX_DL_PREFIX Warning      (            msg                    );  ALOX_DL_POSTFIX ) }

/** Invokes \ref aworx::lox::Lox::Warning "Lox::Warning" on the debug singleton of class Lox defined in macro \ref ALOX_DBG_LOX_INSTANCE. */
#define Log_WarningD(       domain, msg                      )  { Log_Prune( ALOX_DL_PREFIX Warning      (    domain, msg                    );  ALOX_DL_POSTFIX ) }

/** Invokes \ref aworx::lox::Lox::Error "Lox::Error" on the debug singleton of class Lox defined in macro \ref ALOX_DBG_LOX_INSTANCE. */
#define Log_Error(                  msg                      )  { Log_Prune( ALOX_DL_PREFIX Error        (            msg                    );  ALOX_DL_POSTFIX ) }

/** Invokes \ref aworx::lox::Lox::Error "Lox::Error" on the debug singleton of class Lox defined in macro \ref ALOX_DBG_LOX_INSTANCE. */
#define Log_ErrorD(         domain, msg                      )  { Log_Prune( ALOX_DL_PREFIX Error        (    domain, msg                    );  ALOX_DL_POSTFIX ) }

/** Invokes \ref aworx::lox::Lox::Assert "Lox::Assert" on the debug singleton of class Lox defined in macro \ref ALOX_DBG_LOX_INSTANCE. */
#define Log_Assert(     c,          msg                      )  { Log_Prune( ALOX_DL_PREFIX Assert       ( c,         msg                    );  ALOX_DL_POSTFIX ) }

/** Invokes \ref aworx::lox::Lox::Assert "Lox::Assert" on the debug singleton of class Lox defined in macro \ref ALOX_DBG_LOX_INSTANCE. */
#define Log_AssertD(    c,  domain, msg                      )  { Log_Prune( ALOX_DL_PREFIX Assert       ( c, domain, msg                    );  ALOX_DL_POSTFIX ) }


/** Invokes \ref aworx::lox::Lox::Line "Lox::Line" on the debug singleton of class Lox defined in macro \ref ALOX_DBG_LOX_INSTANCE. */
#define Log_Line(   c,  domain, level, obj, type             )  { Log_Prune( ALOX_DL_PREFIX Line         ( c, domain, level, obj, type         );  ALOX_DL_POSTFIX ) }

/** Invokes \ref aworx::lox::Lox::Line "Lox::Line" on the debug singleton of class Lox defined in macro \ref ALOX_DBG_LOX_INSTANCE. */
#define Log_LineI(  c,  domain, level, obj, type, indent     )  { Log_Prune( ALOX_DL_PREFIX Line         ( c, domain, level, obj, type, indent );  ALOX_DL_POSTFIX ) }

/** Invokes \ref aworx::lox::Lox::Line "Lox::Line" on the debug singleton of class Lox defined in macro \ref ALOX_DBG_LOX_INSTANCE. */
#define Log_LineIF( c, domain, level, obj, type, indent, filter){ Log_Prune( ALOX_DL_PREFIX Line         ( c, domain, level, obj, type, indent, filter );  ALOX_DL_POSTFIX ) }


/** Invokes \ref aworx::lox::Lox::SetMarker "Lox::SetMarker" on the debug singleton of class Lox defined in macro \ref ALOX_DBG_LOX_INSTANCE. */
#define Log_SetMarker(  marker, scope  )  { Log_Prune( ALOX_DBG_LOX_INSTANCE SetMarker ( marker, scope );  ) }

/** Invokes \ref aworx::lox::Lox::GetMarker "Lox::GetMarker" on the debug singleton of class Lox defined in macro \ref ALOX_DBG_LOX_INSTANCE. */
#define Log_GetMarker(  marker, scope  )  { Log_Prune( marker= ALOX_DBG_LOX_INSTANCE GetMarker ( scope );  ) }

/** @} */


// #################################################################################################
// Release logging macros
// #################################################################################################
/**
 * @defgroup GrpMacrosReleaseLog        ALox Macros For Release Logging
 *
 * The macros listed here, are provided to place release log statements within source code using
 * ALox. Besides that, macros controlling and setting preferences for ALox exists.<p>
 *
 * The exclusive use of these macros should be sufficient to support most of common release logging
 * statements with ALox. Should some functionality be not available easily using the macros,
 * of-course, the normal C++ API of ALox can be used in parallel to using the macros.
 * Code that is using the C++ API has to be enclosed by<br>
 \verbatim
 #ifdef ALOX_REL_LOG
    ...
 #endif
 \endverbatim
 * lines, to remove them when compiling a release version of the software unit with pruned
 * release log macros. (Such compilation would be made by passing \ref ALOX_REL_LOG_OFF to the
 * compiler and could be useful in certain situations.) <p>
 *
 * All macro names are prefixed with the term <b>Lox_</b>. This implies that they are macros to
 * implement <EM>release logging</EM>. In contrast to this, a set of similar macros exists for
 * <EM>debug logging</EM>. Those are
 * prefixed <b>Log_</b>.
 * \note The choice of the prefixes <b>Log_</b> and <b>Lox_</b> was made to provide  maximum source
 * code compatibility of <EM>ALox for C++</EM> log lines in comparison to other ALox implementations
 * in other programming languages, which provide a class Log as a kind of 'mirror' class of
 * class Lox. Invocations to class Log get pruned in these languages. <p>
 *
 * Most macros make use of the macro \ref ALOX_REL_LOX_INSTANCE, which references a singleton
 * object of class \ref aworx::lox::Lox "Lox" that is used for all debug logging. This singleton
 * concept covers most uses cases for debug logging. If more flexibility is wanted, then either the
 * macro \ref ALOX_REL_LOX_INSTANCE might be changed for different compilation units or the ALox C++
 * API might be used instead of the macros listed here.
 *
 * @{
 */


/**
 * \def  Lox_Prune
 * This very simple macro is used for pruning release log statements in the moment release logging
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
    #define Lox_Prune( releaseLogCode  ) releaseLogCode
#else
    #define Lox_Prune( releaseLogCode  )
#endif



/** Invokes \ref aworx::lox::Lox::AddLogger "Lox::AddLogger" on the object defined in macro \ref ALOX_REL_LOX_INSTANCE. */
#define Lox_AddLogger(      logger                           )  { Lox_Prune( ALOX_RL_PREFIX AddLogger    ( logger                            );  ALOX_RL_POSTFIX ) }

/** Invokes \ref aworx::lox::Lox::AddLogger "Lox::AddLogger" on the object defined in macro \ref ALOX_REL_LOX_INSTANCE. */
#define Lox_AddLoggerD(     logger, internalDomainLevel      )  { Lox_Prune( ALOX_RL_PREFIX AddLogger    ( logger, internalDomainLevel       );  ALOX_RL_POSTFIX ) }

/** Invokes \ref aworx::lox::Lox::RemoveLoggers "Lox::RemoveLoggers" on the object defined in macro \ref ALOX_REL_LOX_INSTANCE. */
#define Lox_RemoveLoggers(  filter                           )  { Lox_Prune( ALOX_RL_PREFIX RemoveLoggers( filter                            );  ALOX_RL_POSTFIX ) }

/** Invokes \ref aworx::lox::Lox::RemoveLoggers "Lox::RemoveLoggers" on the object defined in macro \ref ALOX_REL_LOX_INSTANCE. */
#define Lox_RemoveLogger(   logger                           )  { Lox_Prune( ALOX_RL_PREFIX RemoveLogger ( logger                            );  ALOX_RL_POSTFIX ) }


/** Invokes \ref aworx::lox::Lox::RegDomain "Lox::RegDomain" on the object defined in macro \ref ALOX_REL_LOX_INSTANCE.
 *  \attention If \ref ALOX_REL_LOG_CI is not set, which is the default for release logging
 *             statements, the parameter scope is ignored due to the lack of caller information.
 *             Therefore, this call can not be used to set a default domain. In release logging it
 *             is advised to provide a domain name explicitly with every release log call.<br>
 *             If default domains should be supported, the software entity has to be compiled
 *             with precompiler symbol \ref ALOX_REL_LOG_CI_ON. Note that one effect of setting
 *             this symbol is, that information on source code paths and file names, as well as
 *             method names make their way into the release executable. This may not be wanted.
 *             */
#if defined( ALOX_REL_LOG_CI )
    #define Lox_RegDomain(      domain, scope                )  { Lox_Prune( ALOX_RL_PREFIX RegDomain    ( domain, scope                     );  ALOX_RL_POSTFIX ) }
#else
    #define Lox_RegDomain(      domain, scope                )  { Lox_Prune( ALOX_RL_PREFIX RegDomain    ( domain                            );  ALOX_RL_POSTFIX ) }
#endif


/** Invokes \ref aworx::lox::Lox::SetDomain "Lox::SetDomain" on the object defined in macro \ref ALOX_REL_LOX_INSTANCE. */
#define Lox_SetDomain(      domain, domainLevel              )  { Lox_Prune( ALOX_RL_PREFIX SetDomain    ( domain, domainLevel               );  ALOX_RL_POSTFIX ) }

/** Invokes \ref aworx::lox::Lox::SetDomain "Lox::SetDomain" on the object defined in macro \ref ALOX_REL_LOX_INSTANCE. */
#define Lox_SetDomainR(     domain, domainLevel, rec         )  { Lox_Prune( ALOX_RL_PREFIX SetDomain    ( domain, domainLevel, rec          );  ALOX_RL_POSTFIX ) }

/** Invokes \ref aworx::lox::Lox::SetDomain "Lox::SetDomain" on the object defined in macro \ref ALOX_REL_LOX_INSTANCE. */
#define Lox_SetDomainF(     domain, domainLevel,      filter )  { Lox_Prune( ALOX_RL_PREFIX SetDomain    ( domain, domainLevel, true, filter );  ALOX_RL_POSTFIX ) }

/** Invokes \ref aworx::lox::Lox::SetDomain "Lox::SetDomain" on the object defined in macro \ref ALOX_REL_LOX_INSTANCE. */
#define Lox_SetDomainRF(    domain, domainLevel, rec, filter )  { Lox_Prune( ALOX_RL_PREFIX SetDomain    ( domain, domainLevel, rec,  filter );  ALOX_RL_POSTFIX ) }

/** Invokes \ref aworx::lox::Lox::SetDisabled "Lox::SetDisabled" on the object defined in macro \ref ALOX_REL_LOX_INSTANCE. */
#define Lox_SetDisabled(    disabled, filter                 )  { Lox_Prune( ALOX_RL_PREFIX SetDisabled( disabled, filter                    );  ALOX_RL_POSTFIX ) }

/** Invokes \ref aworx::lox::Lox::SetStartTime "Lox::SetStartTime" on the object defined in macro \ref ALOX_REL_LOX_INSTANCE. */
#define Lox_SetStartTime(   time, filter                     )  { Lox_Prune( ALOX_RL_PREFIX SetStartTime( time, filter                       );  ALOX_RL_POSTFIX ) }

/** Invokes \ref aworx::lox::Lox::MapThreadName "Lox::MapThreadName" on the object defined in macro \ref ALOX_REL_LOX_INSTANCE. */
#define Lox_MapThreadName(  threadName                       )  { Lox_Prune( ALOX_RL_PREFIX MapThreadName( threadName                        );  ALOX_RL_POSTFIX ) }

/** Invokes \ref aworx::lox::Lox::LogConfig "Lox::LogConfig" on the object defined in macro \ref ALOX_REL_LOX_INSTANCE. */
#define Lox_LogConfig(      domain, logLevel, headl          )  { Lox_Prune( ALOX_RL_PREFIX LogConfig    ( domain, logLevel, headl           );  ALOX_RL_POSTFIX ) }

/** Invokes \ref aworx::lox::Lox::LogConfig "Lox::LogConfig" on the object defined in macro \ref ALOX_REL_LOX_INSTANCE. */
#define Lox_LogConfigF(     domain, logLevel, headll, filter )  { Lox_Prune( ALOX_RL_PREFIX LogConfig    ( domain, logLevel, headl, filter   );  ALOX_RL_POSTFIX ) }

/** Invokes \ref aworx::lox::Lox::Verbose "Lox::Verbose" on the object defined in macro \ref ALOX_REL_LOX_INSTANCE. */
#define Lox_Verbose(                    msg                  )  { Lox_Prune( ALOX_RL_PREFIX Verbose      (            msg                    );  ALOX_RL_POSTFIX ) }

/** Invokes \ref aworx::lox::Lox::Verbose "Lox::Verbose" on the object defined in macro \ref ALOX_REL_LOX_INSTANCE. */
#define Lox_VerboseD(           domain, msg                  )  { Lox_Prune( ALOX_RL_PREFIX Verbose      (    domain, msg                    );  ALOX_RL_POSTFIX ) }

/** Invokes \ref aworx::lox::Lox::Info "Lox::Info" on the object defined in macro \ref ALOX_REL_LOX_INSTANCE. */
#define Lox_Info(                       msg                  )  { Lox_Prune( ALOX_RL_PREFIX Info         (            msg                    );  ALOX_RL_POSTFIX ) }

/** Invokes \ref aworx::lox::Lox::Info "Lox::Info" on the object defined in macro \ref ALOX_REL_LOX_INSTANCE. */
#define Lox_InfoD(              domain, msg                  )  { Lox_Prune( ALOX_RL_PREFIX Info         (    domain, msg                    );  ALOX_RL_POSTFIX ) }

/** Invokes \ref aworx::lox::Lox::Warning "Lox::Warning" on the object defined in macro \ref ALOX_REL_LOX_INSTANCE. */
#define Lox_Warning(                    msg                  )  { Lox_Prune( ALOX_RL_PREFIX Warning      (            msg                    );  ALOX_RL_POSTFIX ) }

/** Invokes \ref aworx::lox::Lox::Warning "Lox::Warning" on the object defined in macro \ref ALOX_REL_LOX_INSTANCE. */
#define Lox_WarningD(           domain, msg                  )  { Lox_Prune( ALOX_RL_PREFIX Warning      (    domain, msg                    );  ALOX_RL_POSTFIX ) }

/** Invokes \ref aworx::lox::Lox::Error "Lox::Error" on the object defined in macro \ref ALOX_REL_LOX_INSTANCE. */
#define Lox_Error(                      msg                  )  { Lox_Prune( ALOX_RL_PREFIX Error        (            msg                    );  ALOX_RL_POSTFIX ) }

/** Invokes \ref aworx::lox::Lox::Error "Lox::Error" on the object defined in macro \ref ALOX_REL_LOX_INSTANCE. */
#define Lox_ErrorD(             domain, msg                  )  { Lox_Prune( ALOX_RL_PREFIX Error        (    domain, msg                    );  ALOX_RL_POSTFIX ) }

/** Invokes \ref aworx::lox::Lox::Assert "Lox::Assert" on the object defined in macro \ref ALOX_REL_LOX_INSTANCE. */
#define Lox_Assert(         c,          msg                  )  { Lox_Prune( ALOX_RL_PREFIX Assert       ( c,         msg                    );  ALOX_RL_POSTFIX ) }

/** Invokes \ref aworx::lox::Lox::Assert "Lox::Assert" on the object defined in macro \ref ALOX_REL_LOX_INSTANCE. */
#define Lox_AssertD(        c,  domain, msg                  )  { Lox_Prune( ALOX_RL_PREFIX Assert       ( c, domain, msg                    );  ALOX_RL_POSTFIX ) }

/** Invokes \ref aworx::lox::Lox::Line "Lox::Line" on the object defined in macro \ref ALOX_REL_LOX_INSTANCE. */
#define Lox_Line(   c, domain, level, obj, type             )  { Lox_Prune( ALOX_RL_PREFIX Line         ( c, domain, level, obj, type        );  ALOX_RL_POSTFIX ) }

/** Invokes \ref aworx::lox::Lox::Line "Lox::Line" on the object defined in macro \ref ALOX_REL_LOX_INSTANCE. */
#define Lox_LineI(  c, domain, level, obj, type, indent     )  { Lox_Prune( ALOX_RL_PREFIX Line         ( c, domain, level, obj, type, indent);  ALOX_RL_POSTFIX ) }

/** Invokes \ref aworx::lox::Lox::Line "Lox::Line" on the object defined in macro \ref ALOX_REL_LOX_INSTANCE. */
#define Lox_LineIF( c, domain, level, obj, type, indent, filter){Lox_Prune( ALOX_RL_PREFIX Line         ( c, domain, level, obj, type, indent, filter );  ALOX_RL_POSTFIX ) }


/** Invokes \ref aworx::lox::Lox::SetMarker "Lox::SetMarker" on the object defined in macro \ref ALOX_REL_LOX_INSTANCE.
 *  \attention If \ref ALOX_REL_LOG_CI is not set, which is the default for release logging
 *             statements, code markers can not be used.<br>
 *             If markers should be supported in release logging, the software entity has to be compiled
 *             with precompiler symbol \ref ALOX_REL_LOG_CI_ON. Note that one effect of setting
 *             this symbol is, that information on source code paths and file names, as well as
 *             method names make their way into the release executable. This may not be wanted.<br>
 */
#define Lox_SetMarker(  marker, scope  )  { Lox_Prune( ALOX_REL_LOX_INSTANCE SetMarker ( marker, scope );  ) }

/** Invokes \ref aworx::lox::Lox::GetMarker "Lox::GetMarker" on the object defined in macro \ref ALOX_REL_LOX_INSTANCE.
 *  \attention If \ref ALOX_REL_LOG_CI is not set, which is the default for release logging
 *             statements, code markers can not be used.<br>
 *             If markers should be supported in release logging, the software entity has to be compiled
 *             with precompiler symbol \ref ALOX_REL_LOG_CI_ON. Note that one effect of setting
 *             this symbol is, that information on source code paths and file names, as well as
 *             method names make their way into the release executable. This may not be wanted.<br>
 */
#define Lox_GetMarker(  marker, scope  )  { Lox_Prune( marker= ALOX_REL_LOX_INSTANCE GetMarker ( scope );  ) }



/** @} */ // GrpMacrosReleaseLog



#endif // HPP_AWORX_ALOX_ALOX_MACROS
