// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
/** @file */ // Hello Doxyen

// to preserve the right order, we are not includable directly from outside.
#if !defined(FROM_HPP_AWORX_LIB_ALIB) || defined(HPP_AWORX_LIB_ALIB_MACROS)
    #error "include alib/alib.hpp instead of this header"
#endif


#ifndef HPP_AWORX_LIB_ALIB_MACROS
#define HPP_AWORX_LIB_ALIB_MACROS 1


// #################################################################################################
// Compile veryfier flags. Compiled statically into ALIB::CompilationFlags and are used to detect
// incompatible flag settings.
// #################################################################################################

#if !defined( IS_DOXYGEN_PARSER )

#define     ALIB_VERSION_VERYFIER              1601

#if defined(ALIB_DEBUG)
    #define ALIB_DEBUG_VFYBIT                  +(1 << 0)
#else
    #define ALIB_DEBUG_VFYBIT                  +0
#endif

#if defined(ALIB_FEAT_THREADS)
    #define ALIB_FEAT_THREADS_VFYBIT           +(1 << 1)
#else
    #define ALIB_FEAT_THREADS_VFYBIT           +0
#endif

#if defined(ALIB_DEBUG_STRINGS)
    #define ALIB_DEBUG_STRINGS_VFYBIT          +(1 << 2)
#else
    #define ALIB_DEBUG_STRINGS_VFYBIT          +0
#endif

#if defined(ALIB_GTEST)
    #define ALIB_GTEST_VFYBIT                  +(1 << 16)
#else
    #define ALIB_GTEST_VFYBIT                  +0
#endif

#if defined(ALIB_QTCREATOR)
    #define ALIB_QTCREATOR_VFYBIT              +(1 << 17)
#else
    #define ALIB_QTCREATOR_VFYBIT              +0
#endif

#if defined(ALIB_ECLIPSE_CDT)
    #define ALIB_ECLIPSE_CDT_VFYBIT            +(1 << 18)
#else
    #define ALIB_ECLIPSE_CDT_VFYBIT            +0
#endif

#if defined(ALIB_VSTUDIO)
    #define ALIB_VSTUDIO_VFYBIT                +(1 << 19)
#else
    #define ALIB_VSTUDIO_VFYBIT                +0
#endif

#define    ALIB_COMPATIBILITY_VERYFIER  ( ALIB_DEBUG_VFYBIT         \
                                          ALIB_FEAT_THREADS_VFYBIT  \
                                          ALIB_DEBUG_STRINGS_VFYBIT \
                                          ALIB_GTEST_VFYBIT         \
                                          ALIB_QTCREATOR_VFYBIT     \
                                          ALIB_ECLIPSE_CDT_VFYBIT   \
                                          ALIB_VSTUDIO_VFYBIT       \
                               )
#endif



/**
 * @defgroup GrpALibMacros    ALib  Macros
 *
 * The preprocessor macros listed here are utility macros used by A-Worx Library \e ALib and
 * are documented as they might be useful for users of ALib same as ALib itself.
 *
 * The definition of the macros is dependent on \ref GrpALibCodeSelectorSymbols, which in turn
 * mostly depend on \ref GrpALibCompilerSymbols.<p>
 *
 * @{ */

/** ********************************************************************************************
 * @name Low level macros
 * The following macros are fundamental and building blocks for other macros.
 * @{
 **********************************************************************************************/


/**
 *  \def  ALIB_STRINGIFY
 *  Makes as string from a preprocessor macro parameter.
 */
#if !defined( IS_DOXYGEN_PARSER )
    #define ALIB_STRINGIFY_X(a)   #a
#endif
#define     ALIB_STRINGIFY(a)     ALIB_STRINGIFY_X(a)

/**
 *  \def  ALIB_CONCAT
 *  Concatenates two preprocessor macro parameters into one symbol.
 */
#if !defined( IS_DOXYGEN_PARSER )
    #define ALIB_CONCAT_X(a,b)    a ## b
#endif
    #define ALIB_CONCAT(a,b)      ALIB_CONCAT_X(a,b)

/**
 *  \def  ALIB_API
 *  Used to export/import C++ symbols into a dynamic link library.
 *  Defined when compiling ALib classes into a DLL under Windows/MSC.
 *  Dependent on \ref ALIB_DLL_EXPORTS.<br>
 */
#if defined( _MSC_VER )
    #ifdef ALIB_DLL_EXPORTS
        #define ALIB_API  __declspec(dllexport)
    #else
        #define ALIB_API  __declspec(dllimport)
    #endif
#else
    #define ALIB_API
#endif


/**
 * \def  ALIB_SRC_INFO_PARAMS_DECL
 * This macro declares three parameters 'file', 'line' and 'func' for methods that in debug
 * compilations receive these parameters using macro #ALIB_SRC_INFO_PARAMS.
 *
 * \def  ALIB_SRC_INFO_PARAMS
 * This macro fills in the built-in compiler symbols that provide the current source file,
 * line number and function strings.<p>
 * The macro should be used anywhere where this information is passed (as a nested macro in
 * debug macos)<p>
 *
 * In standard use cases, there is no need to overwrite this macro. Nevertheless, it might
 * be changed to provide other standard information.<p>
 */

#define ALIB_SRC_INFO_PARAMS_DECL   const aworx::lib::strings::ASTerminatable& file,   \
                                    int                                        line,   \
                                    const aworx::lib::strings::ASTerminatable& func,

#if defined( __GNUC__ )
    #define ALIB_SRC_INFO_PARAMS     __FILE__, __LINE__, __func__
//  #define ALIB_SRC_INFO_PARAMS     __FILE__, __LINE__, __PRETTY_FUNCTION__

#elif defined ( _MSC_VER )
    #define ALIB_SRC_INFO_PARAMS     __FILE__, __LINE__, __FUNCTION__
//  #define ALIB_SRC_INFO_PARAMS     __FILE__, __LINE__, __FUNCSIG__

#else
    #pragma message ("Unknown Platform in file: " __FILE__ )
#endif


/**
 * \def  ALIB_IDENTIFIER
 * This macro assembles an 'anonymous' identifier using the given prefix and the current
 * line number within the source code file. This macro is used within other macros that
 * need a C/C++ identifier internally.<br>
 * As a sample, see macro \ref OWN.
 */

#define ALIB_IDENTIFIER(prefix)              ALIB_CONCAT(prefix, __LINE__)

/**
 * \def  ALIB_DBG_SRC_INFO_PARAMS_DECL
 * This macro is the same as \ref ALIB_SRC_INFO_PARAMS_DECL but empty if \ref ALIB_DEBUG is not defined.
 *
 * \def  ALIB_DBG_SRC_INFO_PARAMS
 * This macro is the same as \ref ALIB_SRC_INFO_PARAMS but empty if \ref ALIB_DEBUG is not defined.
 */

#if defined( ALIB_DEBUG )
    #define ALIB_DBG_SRC_INFO_PARAMS_DECL      ALIB_SRC_INFO_PARAMS_DECL
    #define ALIB_DBG_SRC_INFO_PARAMS           ALIB_SRC_INFO_PARAMS
#else
    #define ALIB_DBG_SRC_INFO_PARAMS_DECL
    #define ALIB_DBG_SRC_INFO_PARAMS
#endif

/** @} */



/** ********************************************************************************************
 * @name Warning-, Error- and Assertion- Reports for debug compilations
 * The macros listed here invoke methods of the default instance of class
 * \ref aworx::lib::Report "Report".
 * For more information, see
 * \ref aworx::lib::Report "ALib Reports".
 * @{
 **********************************************************************************************/

/**
 *  \def  ALIB_ERROR
 *  Invokes \ref aworx::lib::Report::DoReport "Report::DoReport".
 *  This macro is pruned from release code.
 *
 *  \def  ALIB_ERROR_AS
 *  Invokes \ref aworx::lib::Report::DoReport "Report::DoReport".<br>
 *  This macro is pruned from release code.<br>
 *  This macro variant having the postfix <em>_AS</em> in its name, creates a
 *  \ref aworx::lib::strings::ASPreAlloc "String512". Parameter \p msg can consist of sequences of
 *  strings and values concatenated using <em>operator<<</em>.
 *
 *
 *  \def  ALIB_WARNING
 *  Invokes \ref aworx::lib::Report::DoReport "Report::DoReport".
 *  This macro is pruned from release code.
 *
 *  \def  ALIB_WARNING_AS
 *  Invokes \ref aworx::lib::Report::DoReport "Report::DoReport".<br>
 *  This macro is pruned from release code.<br>
 *  This macro variant having the postfix <em>_AS</em> in its name, creates a
 *  \ref aworx::lib::strings::ASPreAlloc "String512". Parameter \p msg can consist of sequences of
 *  strings and values concatenated using <em>operator<<</em>.
 *
 *
 *  \def  ALIB_ASSERT
 *  If given condition is \c false, method
 *  \ref aworx::lib::Report::DoReport "Report::DoReport" gets invoked with the standard message
 *  "Internal Error".
 *  This macro is pruned from release code.
 *
 *
 *  \def  ALIB_ASSERT_ERROR
 *  If given condition is \c false, method
 *  \ref aworx::lib::Report::DoReport "Report::DoReport" gets invoked with the given message.
 *  This macro is pruned from release code.
 *
 *  \def  ALIB_ASSERT_ERROR_AS
 *  If given condition is \c false, method
 *  \ref aworx::lib::Report::DoReport "Report::DoReport" gets invoked with the given message.<br>
 *  This macro is pruned from release code.<br>
 *  This macro variant having the postfix <em>_AS</em> in its name, creates a
 *  \ref aworx::lib::strings::ASPreAlloc "String512". Parameter \p msg can consist of sequences of
 *  strings and values concatenated using <em>operator<<</em>.
 *
 *
 *  \def  ALIB_ASSERT_WARNING
 *  If given condition is \c false, method
 *  \ref aworx::lib::Report::DoReport "Report::DoReport" gets invoked with the given message.
 *  This macro is pruned from release code.
 *
 *  \def  ALIB_ASSERT_WARNING_AS
 *  If given condition is \c false, method
 *  \ref aworx::lib::Report::DoReport "Report::DoReport" gets invoked with the given message.<br>
 *  This macro is pruned from release code.<br>
 *  This macro variant having the postfix <em>_AS</em> in its name, creates a
 *  \ref aworx::lib::strings::ASPreAlloc "String512". Parameter \p msg can consist of sequences of
 *  strings and values concatenated using <em>operator<<</em>.
 *
 *
 */
#if !defined( IS_DOXYGEN_PARSER )
#if defined(ALIB_DEBUG)
    #define ALIB_ERROR(   msg )                     {                aworx::lib::Report::GetDefault().DoReport( ALIB_DBG_SRC_INFO_PARAMS, 0, msg );                         }
    #define ALIB_WARNING( msg )                     {                aworx::lib::Report::GetDefault().DoReport( ALIB_DBG_SRC_INFO_PARAMS, 1, msg );                         }
    #define ALIB_ERROR_AS(   msg )                  {                aworx::lib::Report::GetDefault().DoReport( ALIB_DBG_SRC_INFO_PARAMS, 0, aworx::String512() << msg );   }
    #define ALIB_WARNING_AS( msg )                  {                aworx::lib::Report::GetDefault().DoReport( ALIB_DBG_SRC_INFO_PARAMS, 1, aworx::String512() << msg );   }

    #define ALIB_ASSERT( cond )                     { if (!(cond)) { aworx::lib::Report::GetDefault().DoReport( ALIB_DBG_SRC_INFO_PARAMS, 0, "Internal Error" );          } }
    #define ALIB_ASSERT_ERROR( cond, msg )          { if (!(cond)) { aworx::lib::Report::GetDefault().DoReport( ALIB_DBG_SRC_INFO_PARAMS, 0, msg );                       } }
    #define ALIB_ASSERT_WARNING( cond, msg )        { if (!(cond)) { aworx::lib::Report::GetDefault().DoReport( ALIB_DBG_SRC_INFO_PARAMS, 1, msg );                       } }
    #define ALIB_ASSERT_ERROR_AS( cond, msg )       { if (!(cond)) { aworx::lib::Report::GetDefault().DoReport( ALIB_DBG_SRC_INFO_PARAMS, 0, aworx::String512() << msg ); } }
    #define ALIB_ASSERT_WARNING_AS( cond, msg )     { if (!(cond)) { aworx::lib::Report::GetDefault().DoReport( ALIB_DBG_SRC_INFO_PARAMS, 1, aworx::String512() << msg ); } }
#else
    #define ALIB_ERROR(   msg )                     {}
    #define ALIB_WARNING( msg )                     {}
    #define ALIB_ERROR_AS(   msg )                  {}
    #define ALIB_WARNING_AS( msg )                  {}

    #define ALIB_ASSERT( cond )                     {}
    #define ALIB_ASSERT_ERROR( cond, msg )          {}
    #define ALIB_ASSERT_WARNING( cond, msg )        {}
    #define ALIB_ASSERT_ERROR_AS( cond, msg )       {}
    #define ALIB_ASSERT_WARNING_AS( cond, msg )     {}
#endif

// doxygen version
#else
    #define ALIB_ERROR(   msg )                     {}
    #define ALIB_WARNING( msg )                     {}
    #define ALIB_ERROR_AS(   msg )                  {}
    #define ALIB_WARNING_AS( msg )                  {}
    #define ALIB_ASSERT( cond )                     {}
    #define ALIB_ASSERT_ERROR( cond, msg )          {}
    #define ALIB_ASSERT_WARNING( cond, msg )        {}
    #define ALIB_ASSERT_ERROR_AS( cond, msg )       {}
    #define ALIB_ASSERT_WARNING_AS( cond, msg )     {}
#endif

/**
 *  \def  ALIB_ASSERT_RESULT_EQUALS
 *  Asserts that a return value of a function call equals the given expected value.
 *  In release compilation, the function is still invoked, but no check is performed.
 *
 *
 *  \def  ALIB_ASSERT_RESULT_NOT_EQUALS
 *  Asserts that a return value of a function call is not equal to the given value.
 *  In release compilation, the function is still invoked, but no check is performed.
 *
 *
 *  \def  ALIB_ASSERT_RESULT_GREATER_THAN
 *  Asserts that a return value of a function call is greater than the given value.
 *  In release compilation, the function is still invoked, but no check is performed.
 *
 *
 *  \def  ALIB_ASSERT_RESULT_LESS_THAN
 *  Asserts that a return value of a function call is less than the given expected value.
 *  In release compilation, the function is still invoked, but no check is performed.
 *
 */
#if !defined( IS_DOXYGEN_PARSER )
    #if defined(ALIB_DEBUG)
        #define ALIB_ASSERT_RESULT_EQUALS(      func, value ) { auto result= func; assert(result == value); ((void) result); }
        #define ALIB_ASSERT_RESULT_NOT_EQUALS(  func, value ) { auto result= func; assert(result != value); ((void) result); }
        #define ALIB_ASSERT_RESULT_GREATER_THAN(func, value ) { auto result= func; assert(result >  value); ((void) result); }
        #define ALIB_ASSERT_RESULT_LESS_THAN(   func, value ) { auto result= func; assert(result <  value); ((void) result); }
    #else
        #define ALIB_ASSERT_RESULT_EQUALS(      func, value ) { func; }
        #define ALIB_ASSERT_RESULT_NOT_EQUALS(  func, value ) { func; }
        #define ALIB_ASSERT_RESULT_GREATER_THAN(func, value ) { func; }
        #define ALIB_ASSERT_RESULT_LESS_THAN(   func, value ) { func; }
    #endif

#else // doxygen version
    #define ALIB_ASSERT_RESULT_EQUALS(      func, value ) {}
    #define ALIB_ASSERT_RESULT_NOT_EQUALS(  func, value ) {}
    #define ALIB_ASSERT_RESULT_GREATER_THAN(func, value ) {}
    #define ALIB_ASSERT_RESULT_LESS_THAN(   func, value ) {}
#endif


/** @} */


/** ************************************************************************************************
 * \name Macros for One time warnings
 *
 * This group of macros enable the implementation of "one-time warnings", which
 * are warnings that are issued only once per debug session.

 * The warnings are executed using
 * \ref aworx::lib::Report::DoReport "Report::DoReport" (on the \b Report instance received by
 * \ref aworx::lib::Report::GetDefault "Report::GetDefault")
 * and are effective only in debug compilations. They are pruned in release code
 * (dependent on symbol #ALIB_DEBUG).
 *
 * <b> Declaration of an one-time warning </b><p>
 * If an one-time warning is declared per type using \ref ALIB_WARN_ONCE_PER_TYPE_DECL only one
 * warning for all objects will occur and the warnings can be enabled or disabled only for all
 * instances of a class together.
 *
 * In contrast to this, declaring an one-time warning per instance using
 * \ref ALIB_WARN_ONCE_PER_INSTANCE_DECL, a warning will occur once for each object.
 *
 * Both macros have to be placed in the public member section of a class. In addtion to that,
 * per type declarations need to be completed with a definition using macro
 * \ref ALIB_WARN_ONCE_PER_TYPE_DEFINE in the implementation file of the type.
 *
 * <b> Raise Warnings </b><p>
 * Within the implementation of a class that has OTW-declarations, the macros
 * #ALIB_WARN_ONCE, #ALIB_WARN_ONCE_IF and #ALIB_WARN_ONCE_IF_NOT is used to issue the warning.
 *
 * <b> Controlling the warnings</b>
 * The using code of a class that has OTW-declarations can enable and disable (or re-enable)
 * one-time warnings using macros
 * - \ref ALIB_WARN_ONCE_PER_TYPE_ENABLE,
 * - \ref ALIB_WARN_ONCE_PER_TYPE_DISABLE,
 * - \ref ALIB_WARN_ONCE_PER_INSTANCE_ENABLE and
 * - \ref ALIB_WARN_ONCE_PER_INSTANCE_DISABLE.
 *
 * For example, if a certain warning or condition seems right for a specific situation,
 * an one-time warning can be disabled and re-enabled after that situation. Or if it is a per
 * instance warning, it can be disabled after creating that instance.
 *
 * <b> Parameters of the macros</b>
 * The following parameters are expected by the macros:
 *
 * - <em>libdecl:</em><br>
 *   Must match a macro that defines the import/export declaration of the source code entity
 *   (see \ref ALIB_API for a sample of how this symbol is declared in ALib itself).
 * - <em>identifier</em><br>
 *   Identifies the one-time warning. Has to apply to the rules of C++ variable names and can
 *   other wise be chosen freely.
 * - <em>className</em><br>
 *   Names the class when defining or setting a per class one-time warnings.
 * - <em>instance</em><br>
 *   Names a reference to the instance when using per instance one-time warnings.
 *   Within a method of the the corresponding type, use \c *this.
 * - <em>default</em><br>
 *   The default value when declaring, respectively implementing the variable. Can be \c true for
 *   enabled by default, or \c false for disabled.
 **************************************************************************************************/

/**
 *
 * @{ \def  ALIB_WARN_ONCE_PER_TYPE_DECL
 * Declares a static boolean field in a class (struct) to store information about whether a one-time
 * warning was already issued or not.
 * Needs to be placed in the public section of a type declaration.
 * \note This macro needs a corresponding \ref ALIB_WARN_ONCE_PER_TYPE_DEFINE in the implementation
 *       source of that type.
 *
 * \def  ALIB_WARN_ONCE_PER_TYPE_DEFINE
 * Defines a boolean field in a class (struct) to store information about whether a one-time warning
 * was already issued for an object or not. Declaration of the field is done using
 * \ref ALIB_WARN_ONCE_PER_TYPE_DECL.
 *
 * @{ \def  ALIB_WARN_ONCE_PER_TYPE_ENABLE
 * Enables a type-wide one-time warning.
 *
 * @{ \def  ALIB_WARN_ONCE_PER_TYPE_DISABLE
 * Disables a type-wide one-time warning.
 *
 * \def  ALIB_WARN_ONCE_PER_INSTANCE_DECL
 * Defines a boolean field in a class (struct) to store information about whether a one-time warning
 * was already issued for an object or not.
 * This macro needs to be placed in the public section of a class (struct) declaration.
 *
 * \def  ALIB_WARN_ONCE_PER_INSTANCE_ENABLE
 * Enables a per-instance one-time warning.
 *
 * \def  ALIB_WARN_ONCE_PER_INSTANCE_DISABLE
 * Disables a per-instance one-time warning.
 *
 * \def  ALIB_WARN_ONCE
 * Used to 'raise' an one-time warning using the named variable which has to be declared using either
 * \ref ALIB_WARN_ONCE_PER_TYPE_DECL or
 * \ref ALIB_WARN_ONCE_PER_INSTANCE_DECL.
 *
 * \def  ALIB_WARN_ONCE_IF
 * Used to 'raise' an one-time warning, dependent on the given condition and of the state of the
 * named variable which has to be declared using either
 * \ref ALIB_WARN_ONCE_PER_TYPE_DECL or
 * \ref ALIB_WARN_ONCE_PER_INSTANCE_DECL.
 *
 * \def  ALIB_WARN_ONCE_IF_NOT
 * Used to 'raise' an one-time warning, dependent on the given condition and of the state of the
 * named variable which has to be declared using either
 * \ref ALIB_WARN_ONCE_PER_TYPE_DECL or
 * \ref ALIB_WARN_ONCE_PER_INSTANCE_DECL.
 */

#if defined(ALIB_DEBUG) && !defined( IS_DOXYGEN_PARSER )

    #define ALIB_WARN_ONCE_PER_INSTANCE_DECL(            identifier, default )  public: bool ALIB_OTW_##identifier= default;
    #define ALIB_WARN_ONCE_PER_INSTANCE_ENABLE(   instance, identifier       )  instance. ALIB_OTW_##identifier= true;
    #define ALIB_WARN_ONCE_PER_INSTANCE_DISABLE(   instance, identifier      )  instance. ALIB_OTW_##identifier= false;

    #define ALIB_WARN_ONCE_PER_TYPE_DECL(     libdecl,   identifier          )  public: libdecl static bool ALIB_OTW_##identifier;
    #define ALIB_WARN_ONCE_PER_TYPE_DEFINE(   className, identifier, default )  bool className::ALIB_OTW_##identifier= default;
    #define ALIB_WARN_ONCE_PER_TYPE_ENABLE(   className, identifier          )  className::ALIB_OTW_##identifier= true;
    #define ALIB_WARN_ONCE_PER_TYPE_DISABLE(  className, identifier          )  className::ALIB_OTW_##identifier= false;

    #define ALIB_WARN_ONCE(msg, instance, identifier)                                       \
    {                                                                                       \
        if( (instance).ALIB_OTW_##identifier )                                              \
        {                                                                                   \
            ALIB_OTW_##identifier= false;                                                   \
            aworx::lib::Report::GetDefault().DoReport( ALIB_DBG_SRC_INFO_PARAMS, 1, msg);   \
        }                                                                                   \
    }
    #define ALIB_WARN_ONCE_IF(cond, msg, instance, identifier)                              \
    {                                                                                       \
        if( (instance).ALIB_OTW_##identifier && (cond) )                                    \
        {                                                                                   \
            ALIB_OTW_##identifier= false;                                                   \
            aworx::lib::Report::GetDefault().DoReport( ALIB_DBG_SRC_INFO_PARAMS, 1, msg);   \
        }                                                                                   \
    }
    #define ALIB_WARN_ONCE_IF_NOT(cond, msg, instance, identifier)                          \
    {                                                                                       \
        if( (instance).ALIB_OTW_##identifier && !(cond) )                                   \
        {                                                                                   \
            ALIB_OTW_##identifier= false;                                                   \
            aworx::lib::Report::GetDefault().DoReport( ALIB_DBG_SRC_INFO_PARAMS, 1, msg);   \
        }                                                                                   \
    }
#else
    #define ALIB_WARN_ONCE_PER_INSTANCE_DECL(              identifier, default )
    #define ALIB_WARN_ONCE_PER_INSTANCE_ENABLE(  instance, identifier          ) {}
    #define ALIB_WARN_ONCE_PER_INSTANCE_DISABLE( instance, identifier          ) {}

    #define ALIB_WARN_ONCE_PER_TYPE_DECL(        libdecl,  identifier          )
    #define ALIB_WARN_ONCE_PER_TYPE_DEFINE(     className, identifier, default )
    #define ALIB_WARN_ONCE_PER_TYPE_ENABLE(     className, identifier          ) {}
    #define ALIB_WARN_ONCE_PER_TYPE_DISABLE(    className, identifier          ) {}

    #define ALIB_WARN_ONCE(                          msg, instance, identifier ) {}
    #define ALIB_WARN_ONCE_IF(                 cond, msg, instance, identifier ) {}
    #define ALIB_WARN_ONCE_IF_NOT(             cond, msg, instance, identifier ) {}
#endif

/** @} */


/** ********************************************************************************************
 * @name Further macros for debug releases
 * The macros listed here are supporting debug versions of source code and generally
 * depend on preprocessor symbol #ALIB_DEBUG.
 * @{
 **********************************************************************************************/

/**
 * \def  ALIB_DEBUG_CODE
 * This simple macro may be used for placing debug statements into source code. Those get 'pruned'
 * in release versions of ALib (respectively of the software that uses ALib and then this macro).
 * It replaces
 \verbatim
    #if defined(ALIB_DEBUG)
        // do stuff
    #endif
\endverbatim
 * and is useful especially for single line statements.
 */

#if defined(ALIB_DEBUG)
    #define ALIB_DEBUG_CODE(...)    __VA_ARGS__
#else
    #define ALIB_DEBUG_CODE(...)
#endif

/** @} */

/** ********************************************************************************************
 * @name Macros supporting ALib classes
 * The macros listed here have a direct relationship with classes defined in ALib
 * and with their use.
 * @{
 **********************************************************************************************/

/**
 * \def  OWN
 * This preprocessor defines an object of class
 * \ref aworx::lib::Owner "Owner". The special thing about it is, that using this macro
 * there is no need to invent an (otherwise useless) identifier for that definition.
 * Basically, this macro exists, because C++ does not support anonymous objects.<br>
 * As a sample, without using this macros a piece of code code using classes
 * \ref aworx::lib::Owner "Owner"/
 * \ref aworx::lib::Ownable "Ownable"
 * could look like this:<br>
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
 */
#define   OWN(ownable) aworx::lib::Owner ALIB_IDENTIFIER(owner) (ownable);


/** @} */

/** @} */ // GrpALibMacros



#endif // HPP_AWORX_LIB_ALIB_MACROS
