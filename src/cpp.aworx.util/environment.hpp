// #################################################################################################
//  aworx::util - Classes we need
//
//  (c) 2013-2015 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################

// include AWXU main header first...
#if !defined (HPP_AWORX_UTIL_AWXU)
    #include "awxu.hpp"
#endif

// then, set include guard
#ifndef HPP_AWORX_UTIL_ENVIRONMENT
#define HPP_AWORX_UTIL_ENVIRONMENT 1


// -------------------------------------------------------------------------------------------------
// --- includes
// -------------------------------------------------------------------------------------------------
#if !defined (_GLIBCXX_STRING ) && !defined(_STRING_)
    #include <string>
#endif

namespace aworx {
namespace       util {

// #################################################################################################
// Preprocessor definitions
// #################################################################################################
#ifdef    NDEBUG
#else
#endif


// #################################################################################################
// class Environment
// #################################################################################################

/** ************************************************************************************************
 *  This class mimics some functionality of C# Environment class.
 **************************************************************************************************/
class Environment
{
    // #############################################################################################
    // static interface
    // #############################################################################################
    public:
        /**  Returns an object representing the thread that executed the code to invoke
         *  this call the current Thread object.
            @return A pointer to the current Thread.
         */
        AWXU_API static  std::string        CurrentDirectory();

};



}}  // namespace aworx::util




#endif // HPP_AWORX_UTIL_ENVIRONMENT
