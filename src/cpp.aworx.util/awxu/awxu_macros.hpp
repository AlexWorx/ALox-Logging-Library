// #################################################################################################
//  aworx::util - Classes we need
//
//  (c) 2013-2015 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################

#ifndef HPP_AWORX_UTIL_AWXU_MACROS
#define HPP_AWORX_UTIL_AWXU_MACROS 1

#if !defined(HPP_AWORX_UTIL_AWXU)
    #error "include awxu.hpp instead of awxu_macros.hpp"
#endif


/**
 * @defgroup GrpAWXUMacros    AWXU Macros
 *
 * The preprocessor macros listed here are utility macros used by AWXU library and available to
 * source code units that incorporate the AWXU library.
 *
 * The definition of the macros is dependent on \ref GrpAWXUCodeSelectorSymbols, which in turn
 * mostly depend on \ref GrpAWXUCompilerSymbols.<p>
*
 * @{
 */


/**
 * @{ \def  AWXU_ASSERT
 *  Invokes code in macro \ref AWXU_ASSERT_MSG providing the standard message "Internal AWXU error".
 * @}
 *
 * @{ \def  AWXU_ASSERT_MSG
 *  If given condition is false, method
 *  \ref aworx::util::AWXU::Error "Error" of the current
 *  \ref aworx::util::AWXUErrorHandler "AWXUErrorHandler" gets invoked with the given message.
 * @}
 */

#if defined(AWXU_DEBUG)
    #define AWXU_ASSERT( cond )             { AWXU_ASSERT_MSG( cond, "Internal AWXU error" ); }
    #define AWXU_ASSERT_MSG( cond, msg )    { if (!(cond)) { if(AWXU::AcquireErrorHandler()) AWXU::Error(msg);  } }
#else
    #define AWXU_ASSERT( cond )
    #define AWXU_ASSERT_MSG( cond, msg )
#endif

/**
 * @{ \def  AWXU_ASSERT_RESULT_EQUALS
 *  Asserts that a return value of a function call equals the given expected value.
 *  In release compilation, the function is still invoked, but no check is performed.
 * @}
 *
 * @{ \def  AWXU_ASSERT_RESULT_NOT_EQUALS
 *  Asserts that a return value of a function call is not equal to the given value.
 *  In release compilation, the function is still invoked, but no check is performed.
 * @}
 *
 * @{ \def  AWXU_ASSERT_RESULT_GREATER_THAN
 *  Asserts that a return value of a function call is greater than the given value.
 *  In release compilation, the function is still invoked, but no check is performed.
 * @}
 *
 * @{ \def  AWXU_ASSERT_RESULT_LESS_THAN
 *  Asserts that a return value of a function call is less than the given expected value.
 *  In release compilation, the function is still invoked, but no check is performed.
 * @}
 */
#if defined(AWXU_DEBUG)
    #define AWXU_ASSERT_RESULT_EQUALS(      func, value ) { auto result= func; assert(result == value); ((void) result); }
    #define AWXU_ASSERT_RESULT_NOT_EQUALS(  func, value ) { auto result= func; assert(result != value); ((void) result); }
    #define AWXU_ASSERT_RESULT_GREATER_THAN(func, value ) { auto result= func; assert(result >  value);  ((void) result); }
    #define AWXU_ASSERT_RESULT_LESS_THAN(   func, value ) { auto result= func; assert(result <  value);  ((void) result); }
#else
    #define AWXU_ASSERT_RESULT_EQUALS(      func, value ) { func; }
    #define AWXU_ASSERT_RESULT_NOT_EQUALS(  func, value ) { func; }
    #define AWXU_ASSERT_RESULT_GREATER_THAN(func, value ) { func; }
    #define AWXU_ASSERT_RESULT_LESS_THAN(   func, value ) { func; }
#endif


/**
 * @{ \def  AWXU_ONE_TIME_WARNING
 *  This macro, together with macros
 *  \ref AWXU_ONE_TIME_WARNING_DECL, \ref AWXU_ONE_TIME_WARNING_DEF and \ref AWXU_ONE_TIME_WARNING_SET
 *  form a set of macros to implement mechanism that issues
 *  \ref aworx::util::AWXU::Warning "AWXU::Warning" once when a certain condition is met.
 *  If multiple warnings should occur, it is possible to reset the warning flag.<br>
 *  In release compilation, all related code is pruned.
 *  The use of the set of macros is as follows:<br>
 *
 *  - Within the declaration of a class (normally in the header file), place the macro
 *    \ref AWXU_ONE_TIME_WARNING_DECL. The parameter <em>libdecl</em> must match a macro that defines
 *    the import/export declaration of the source code entity (see \ref AWXU_API for a sample how
 *    this identifier looks in AWXU itself). The parameter <em>identifier</em> can be chosen freely,
 *    and must be the same in the following steps.
 *
 *  - Within a source file that holds the class definition, the macro
 *    \ref AWXU_ONE_TIME_WARNING_DEF has to be placed.
 *
 *  - Within the methods of the class that are supposed to check a condition and issue the
 *    warning once, the macro \ref AWXU_ONE_TIME_WARNING is to be placed. This can be done more than
 *    one time, if different pieces of code should check the same or different conditions, while still
 *    only one warning should be issued.
 *
 *  - Optionally, anywhere in the code (also from within methods of other classes), the macro
 *    \ref AWXU_ONE_TIME_WARNING_SET can be used to enable (re-enable) or disable the warning.
 *
 * @}
 *
 * @{ \def  AWXU_ONE_TIME_WARNING_DECL
 * See \ref AWXU_ONE_TIME_WARNING for more information.  * @}
 *
 * @{ \def  AWXU_ONE_TIME_WARNING_DEF
 * See \ref AWXU_ONE_TIME_WARNING for more information.  * @}
 *
 * @{ \def  AWXU_ONE_TIME_WARNING_SET
 * See \ref AWXU_ONE_TIME_WARNING for more information.  * @}
 */
#if defined(AWXU_DEBUG)
    #define AWXU_ONE_TIME_WARNING_DECL(libdecl, identifier)         public: libdecl static bool AWXU_OTW_##identifier;
    #define AWXU_ONE_TIME_WARNING_DEF(className,identifier)         bool className::AWXU_OTW_##identifier= true;
    #define AWXU_ONE_TIME_WARNING_SET(className,identifier,enable)  className::AWXU_OTW_##identifier= enable;
    #define AWXU_ONE_TIME_WARNING(cond,msg,identifier)    \
{                                                \
    if( AWXU_OTW_##identifier && ( cond ) )      \
    {                                            \
        AWXU_OTW_##identifier= false;            \
        if( AWXU::AcquireErrorHandler()    )     \
            AWXU::Warning( msg );                \
    }                                            \
}

#else
    #define AWXU_ONE_TIME_WARNING_DECL(libdecl, identifier)
    #define AWXU_ONE_TIME_WARNING_DEF(className,identifier)
    #define AWXU_ONE_TIME_WARNING_SET(className,identifier,enable)
    #define AWXU_ONE_TIME_WARNING(cond,msg,identifier)
#endif


/**
 * @{ \def  AWXU_IDENTIFIER
 *  This macro assembles an 'anonymous' identifier using the given prefix and the current
 *  line number within the source code file. This macro is used within other macros that
 *  need a C/C++ identifier internally.<br>
 *  As a sample, see macro \ref OWN.
 * @}
 */

#define AWXU_IDENTIFIER(prefix)              AWXU_CONCAT(prefix, __LINE__)


/**
 * @{ \def  OWN
 *  This preprocessor defines an object of class
 *  \ref aworx::util::Owner "Owner". The special thing about it is, that using this macro
 *  there is no need to invent an (otherwise useless) identifier for that definition.
 *  Basically, this macro exists, because C++ does not support anonymous objects.<br>
 *  As a sample, without using this macros a piece of code code using classes
 *  \ref aworx::util::Owner "Owner"/
 *  \ref aworx::util::Ownable "Ownable"
 *  could look like this:<br>
\verbatim
{
    Owner myOwner( myOwnable );

    // do stuff
    ...
}
\endverbatim
 *  With the use of this macro, the code changes to:<br>
\verbatim
{
    OWN( myOwnable );

    // do stuff
    ...
}
\endverbatim
 * @}
 */
#define   OWN(ownable) Owner AWXU_IDENTIFIER(owner) (ownable);



/** @} */ // GrpAWXUMacros



#endif // HPP_AWORX_UTIL_AWXU_MACROS
