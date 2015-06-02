// #################################################################################################
//  aworx::lox - ALox Logging Library
//
//  (c) 2013-2015 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
/** @file */ //<- needed for Doxygen include

#ifndef HPP_AWORX_ALOX_ALOX
#define HPP_AWORX_ALOX_ALOX 1



namespace aworx {
/** ************************************************************************************************
 *  This is the C++ namespace for code of the <em>%ALox Logging Library</em>.
 *  Developed by A-Worx GmbH and published under the MIT license.
 **************************************************************************************************/
namespace lox {
}}

// #################################################################################################
// ALOX_DLL_EXPORTS
// Before including AWXU.h, we have to evaluate the DLL exports symbol to set the corresponding
// flag for AWXU as if it was passed to the compiler.
// #################################################################################################
/**
 * @addtogroup GrpALoxCompilerSymbols
 * @{ \def  ALOX_DLL_EXPORTS
 *  This compiler symbol has to be defined when compiling ALox as a DLL under Windows/MSC.
 *  In addition, also \ref AWXU_DLL_EXPORTS has to be defined.
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
// include AWXU
// #################################################################################################
#include "awxu.hpp"

// #################################################################################################
// Now we first process external conditional compilation symbols
// and then we define our prepro logging macros accordingly.
// #################################################################################################

#if defined(HPP_AWORX_ALOX_ALOX_COND_COMP_SYMBOLS)
    #error "alox_condcomp.hpp must not be included manually. Include alox.hpp instead"
#endif
#include "alox/alox_symbols.hpp"


#if defined(HPP_AWORX_ALOX_ALOX_MACROS)
    #error "macros.hpp must not be included manually. Include alox.hpp instead"
#endif
#include "alox/alox_macros.hpp"


// #################################################################################################
// include Log and Lox classes
// #################################################################################################
#if defined(HPP_AWORX_ALOX_LOG)
    #error "log.hpp must not be included manually"
#endif
#include "alox/log.hpp"


#if defined(HPP_AWORX_ALOX_LOX)
    #error "lox.hpp must not be included manually"
#endif
#include "alox/lox.hpp"

#endif // HPP_AWORX_ALOX_ALOX
