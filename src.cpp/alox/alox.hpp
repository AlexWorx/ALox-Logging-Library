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

#if defined(HPP_ALOX_COND_COMP_SYMBOLS)
    #error "alox_condcomp.hpp must not be included manually. Include alox.hpp instead"
#endif
#include "internals/alox_symbols.hpp"


#if defined(HPP_ALOX_MACROS)
    #error "macros.hpp must not be included manually. Include alox.hpp instead"
#endif
#include "internals/alox_macros.hpp"



// #################################################################################################
// include Log and Lox classes
// #################################################################################################
#include "log.hpp"
#include "lox.hpp"


namespace aworx {
namespace       lox {

/** ************************************************************************************************
 * This class defines "escape sequences" that influence the formatting of log output.
 * Specific implementations of class
 * \ref aworx::lox::core::Logger "Logger"
 * have to convert or interpret this classes definitions of escape sequences
 * when processing log data. If no formatting of the output is supported by a specific Logger
 * implementation, such logger should filter and discard escape sequences defined here.
 *
 * The sequences are similar to ANSI Escape sequences and logger classes that
 * log to 'VT100' compatible terminals will simply convert them.
 *
 * The name of the class was intentionally chosen to be short, because the escape codes
 * defined with this class will be concatenated to log strings like that:
 *
 * \snippet "ut_alox_documentation_samples.cpp"     DOX_ALOX_ESC
 **************************************************************************************************/
class ESC
{
    public:
    #if defined(_MSC_VER)
    // MSC  (as of 12/2015):
    // C4579: in-class initialization for type 'const aworx::SLiteral<10>'
    // is not yet implemented; static member will remain uninitialized at runtime but
    // use in constant-expressions is supported

    ALIB_API static     SLiteral<3>  RED                    ; ///< Select red color for foreground.
    ALIB_API static     SLiteral<3>  GREEN                  ; ///< Select green color for foreground.
    ALIB_API static     SLiteral<3>  YELLOW                 ; ///< Select yellow color for foreground.
    ALIB_API static     SLiteral<3>  BLUE                   ; ///< Select blue color for foreground.
    ALIB_API static     SLiteral<3>  MAGENTA                ; ///< Select magenta color for foreground.
    ALIB_API static     SLiteral<3>  CYAN                   ; ///< Select cyan color for foreground.
    ALIB_API static     SLiteral<3>  BLACK                  ; ///< Select black color for foreground.
    ALIB_API static     SLiteral<3>  WHITE                  ; ///< Select white color for foreground.
    ALIB_API static     SLiteral<3>  GRAY                   ; ///< Select gray color for foreground.
    ALIB_API static     SLiteral<3>  FG_RESET               ; ///< Select std color for foreground.

    ALIB_API static     SLiteral<3>  BG_RED                 ; ///< Select red color for background.
    ALIB_API static     SLiteral<3>  BG_GREEN               ; ///< Select green color for background.
    ALIB_API static     SLiteral<3>  BG_YELLOW              ; ///< Select yellow color for background.
    ALIB_API static     SLiteral<3>  BG_BLUE                ; ///< Select blue color for background.
    ALIB_API static     SLiteral<3>  BG_MAGENTA             ; ///< Select blue color for background.
    ALIB_API static     SLiteral<3>  BG_CYAN                ; ///< Select blue color for background.
    ALIB_API static     SLiteral<3>  BG_BLACK               ; ///< Select red color for background.
    ALIB_API static     SLiteral<3>  BG_WHITE               ; ///< Select blue color for background.
    ALIB_API static     SLiteral<3>  BG_GRAY                ; ///< Select gray color for background.
    ALIB_API static     SLiteral<3>  BG_RESET               ; ///< Select std color for background.

    ALIB_API static     SLiteral<3>  BOLD                   ; ///< Select bold font style.
    ALIB_API static     SLiteral<3>  ITALICS                ; ///< Select italics font style.
    ALIB_API static     SLiteral<3>  STYLE_RESET            ; ///< Select standard font style.
    ALIB_API static     SLiteral<3>  RESET                  ; ///< Reset color and style.

    ALIB_API static     SLiteral<3>  URL_START              ; ///< Mark the start of an URL.
    ALIB_API static     SLiteral<3>  URL_END                ; ///< Mark the end of an URL.
    ALIB_API static     SLiteral<3>  TAB                    ; ///< Go to next tab. Usually, text loggers will increase the tab position automatically.

    ALIB_API static     SLiteral<3>  EOMETA                 ; ///< End of meta information in log string

    #else
    static constexpr    SLiteral<3>  RED        { "\033c0" }; ///< Select red color for foreground.
    static constexpr    SLiteral<3>  GREEN      { "\033c1" }; ///< Select green color for foreground.
    static constexpr    SLiteral<3>  YELLOW     { "\033c2" }; ///< Select yellow color for foreground.
    static constexpr    SLiteral<3>  BLUE       { "\033c3" }; ///< Select blue color for foreground.
    static constexpr    SLiteral<3>  MAGENTA    { "\033c4" }; ///< Select magenta color for foreground.
    static constexpr    SLiteral<3>  CYAN       { "\033c5" }; ///< Select cyan color for foreground.
    static constexpr    SLiteral<3>  BLACK      { "\033c6" }; ///< Select black color for foreground.
    static constexpr    SLiteral<3>  WHITE      { "\033c7" }; ///< Select white color for foreground.
    static constexpr    SLiteral<3>  GRAY       { "\033c8" }; ///< Select gray color for foreground.
    static constexpr    SLiteral<3>  FG_RESET   { "\033c9" }; ///< Select std color for foreground.

    static constexpr    SLiteral<3>  BG_RED     { "\033C0" }; ///< Select red color for background.
    static constexpr    SLiteral<3>  BG_GREEN   { "\033C1" }; ///< Select green color for background.
    static constexpr    SLiteral<3>  BG_YELLOW  { "\033C2" }; ///< Select yellow color for background.
    static constexpr    SLiteral<3>  BG_BLUE    { "\033C3" }; ///< Select blue color for background.
    static constexpr    SLiteral<3>  BG_MAGENTA { "\033C4" }; ///< Select blue color for background.
    static constexpr    SLiteral<3>  BG_CYAN    { "\033C5" }; ///< Select blue color for background.
    static constexpr    SLiteral<3>  BG_BLACK   { "\033C6" }; ///< Select red color for background.
    static constexpr    SLiteral<3>  BG_WHITE   { "\033C7" }; ///< Select blue color for background.
    static constexpr    SLiteral<3>  BG_GRAY    { "\033C8" }; ///< Select gray color for background.
    static constexpr    SLiteral<3>  BG_RESET   { "\033C9" }; ///< Select std color for background.

    static constexpr    SLiteral<3>  BOLD       { "\033sB" }; ///< Select bold font style.
    static constexpr    SLiteral<3>  ITALICS    { "\033sI" }; ///< Select italics font style.
    static constexpr    SLiteral<3>  STYLE_RESET{ "\033sr" }; ///< Select standard font style.
    static constexpr    SLiteral<3>  RESET      { "\033sa" }; ///< Reset color and style.

    static constexpr    SLiteral<3>  URL_START  { "\033lS" }; ///< Mark the start of an URL.
    static constexpr    SLiteral<3>  URL_END    { "\033lE" }; ///< Mark the end of an URL.
    static constexpr    SLiteral<3>  TAB        { "\033t0" }; ///< Go to next tab. Usually, text loggers will increase the tab position automatically.

    static constexpr    SLiteral<3>  EOMETA     { "\033A0" }; ///< End of meta information in log string

    #endif
};

} // namespace lox

/** Type alias name in namespace #aworx. */
using     ESC=           aworx::lox::ESC;

}  // namespace aworx
#endif // HPP_ALOX
