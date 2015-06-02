// #################################################################################################
//  aworx::util - Classes we need
//
//  (c) 2013-2015 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################

#ifndef HPP_AWORX_UTIL_AWXU
#define HPP_AWORX_UTIL_AWXU 1


// The always need and not doxygen documented macro to stringify stuff
#if !defined( DOXYGEN_OMIT_THIS_PLEASE )
#define AWXU_STRINGIFY_X(a)   #a
#define AWXU_STRINGIFY(a)     AWXU_STRINGIFY_X(a)

#define AWXU_CONCAT_X(a,b)    a ## b
#define AWXU_CONCAT(a,b)      AWXU_CONCAT_X(a,b)
#endif


// compiler check
#if defined(__GNUC__) &&  __cplusplus < 201103L
    #error "AWXU Needs C++ 11. Compilation aborted"
#endif

#if defined ( _MSC_VER )  &&  _MSC_VER < 1600 // VS 2010 == VC10 == _MSC_VER 1600
    #error "AWXU Needs C++ 11. Compilation aborted"
#endif


//**************************************************************************************************
// First we process external conditional compilation symbols
// and then we define our prepro logging macros accordingly.
//**************************************************************************************************

#if defined(HPP_AWORX_UTIL_AWXU_CONDCOMPILE)
    #error "awxu_condcomp.hpp must not be included manually. Include awxu.hpp instead"
#endif
#include "awxu/awxu_symbols.hpp"


#if defined(HPP_AWORX_UTIL_AWXU_MACROS)
    #error "awxu_macros.hpp must not be included manually. Include awxu.hpp instead"
#endif
#include "awxu/awxu_macros.hpp"


//**************************************************************************************************
// Frequently needed headers
//**************************************************************************************************

#if !defined (_ASSERT_H)
    #include <assert.h>
#endif


#if !defined (_GLIBCXX_VECTOR) && !defined (_VECTOR_ )
    #include <vector>
#endif

#if !defined (_GLIBCXX_CSTDDEF) && !defined(_CSTDDEF_)
    #include <cstddef>
#endif


//**************************************************************************************************
// Platform specific headers
//**************************************************************************************************
#if defined( __GNUC__ )
    #if !defined (_GLIBCXX_CSTDINT)
        #include <cstdint>
    #endif

#elif defined ( _MSC_VER )
    #define WIN32_LEAN_AND_MEAN         // Exclude rarely-used stuff from Windows headers
    #define NOMINMAX                    // Avoid problems with std lib
    #define NOGDI                       // conflict: gdi defines ERROR

    // Windows Header Files:
    #if !defined (_INC_WINDOWS)
        #define WIN32_LEAN_AND_MEAN         // Exclude rarely-used stuff from Windows headers
        #define NOMINMAX                    // Avoid problems with std lib
        #define NOGDI                       // conflict: gdi defines ERROR
        #include <windows.h>
    #endif
    #if !defined (_STDINT)
        #include <stdint.h>
    #endif
#else
    #pragma message ("Uknown Platform in file: " __FILE__ )
#endif


/** ************************************************************************************************
 *  This is the outer namespace for all classes published by A-Worx GmbH, Germany. As far as we
 *  have planned today, there is nothing inside this namespace but other namespaces.<p>
 *  \note While the Java language strongly proposes to use the complete 'reverse domain' name
 *  and therefore Java code published by A-Worx GmbH resides Java namespace <em>com.aworx</em>,
 *  for C++ we decided to omit the <em>com.</em>, just to keep it shorter and nicer.<br>
 *  Now, of-course, we very much hope that this will not collide with any other
 *  code constituting "A-grade works"!
 **************************************************************************************************/
namespace aworx {

/** ************************************************************************************************
 *  This is the C++ namespace for <em>%AWXU</em> code. %AWXU comprises a bunch of utility classes
 *  developed by A-Worx GmbH, published under the MIT license.
 **************************************************************************************************/
namespace       util {


// #################################################################################################
// forwards
// #################################################################################################
class ThreadLock;

// #################################################################################################
// ErrorHandler
// #################################################################################################

/** ************************************************************************************************
 *  Interface for AWXU error handler. The AWXU error handler is invoked on internal AWXU errors
 *  caused by illegal arguments or other wrong AWXU use. By default is a simple implementation is
 *  installed that just uses cout/cerr to print the error and warning messages to
 *  the application's standard output.
 *  Applications may implement their own AWXUErrorHandler and attach this to
 *  AWXU using AWXU::ReplaceErrorHandler. Of-course, the AWXUErrorHandler may be used also
 *  by software based on AWXU. For the use of the error handler, see documentation of
 *  # AWXU::AcquireErrorHandler, # AWXU::Error, # AWXU::Warning and # AWXU::AbortErrorHandler.
 **************************************************************************************************/
class AWXUErrorHandler
{
    public:
        /** ****************************************************************************************
         *  Report an AWXU error. Pure virtual abstract interface method.
         * @param msg    The error message.
         ******************************************************************************************/
        virtual void Error  ( const char* msg )    =0;

        /** ****************************************************************************************
         *  Report an AWXU warning. Pure virtual abstract interface method.
         * @param msg    The warning message.
         ******************************************************************************************/
        virtual void Warning( const char* msg )    =0;

        /** ****************************************************************************************
         *  Report a AWXU debug message. Pure virtual abstract interface method.
         * @param msg    The warning message.
         ******************************************************************************************/
        virtual void DebugMsg( const char* msg )    =0;
};

// #################################################################################################
// class ConsoleErrorHandler
// #################################################################################################

/** ************************************************************************************************
 *  Report an AWXU error. Pure virtual abstract interface method.
 * @param msg    The error message.
 **************************************************************************************************/
class ConsoleErrorHandler : public AWXUErrorHandler
{
    /** ********************************************************************************************
     *  Just writes the prefix \"AWXU Error: \" and the error message to the console.
     * @param msg    The error message.
     **********************************************************************************************/
    virtual void Error  ( const char* msg );

    /** ********************************************************************************************
     *  Just writes the prefix \"AWXU Warning: \" and the warning message to the console.
     * @param msg    The warning message.
     **********************************************************************************************/
    virtual void Warning( const char* msg );

    /** ****************************************************************************************
     *  Report a AWXU debug message. Pure virtual abstract interface method.
     * @param msg    The warning message.
     ******************************************************************************************/
    virtual void DebugMsg( const char* msg );
};



// #################################################################################################
// class AWXU
// #################################################################################################

/** ************************************************************************************************
 *  Static methods and fields of A-Worx Utility library (AWXU).
 **************************************************************************************************/
class AWXU
{
    // #############################################################################################
    // static functionality
    // #############################################################################################
    protected:
        /**  flag indicating that AWXU has been initialized (if not equals 0) */
        static int                      isInitialized;

        /**  our lock  */
        static ThreadLock               tlock;

        /**  The handler for AWXU errors and warnings.  */
        static AWXUErrorHandler*        errorHandler;

        /**  The default error handler. This gets set when initializing AWXU  */
        static ConsoleErrorHandler      defaultErrorHandler;



    // #############################################################################################
    // TerminationCleanUp()
    // #############################################################################################
    public:
        /** ****************************************************************************************
         * This method must be called prior to using the AWXU library, e.g. at the beginning of
         * the main() method of an application. It is OK, to call this method more than once, which
         * allows independent code blocks (e.g. libraries) to bootstrap AWXU without interfering.
         * Nevertheless, the very first invocation should not be interrupted by a parallel invocation
         * of a second thread. So, it has to be assured that this method is invoked once on the
         * real bootstrap an app.
         *
         * Note: AWXU must not be used before all global/static variables are created. Hence, it
         * is not allowed to initialize AWXU within static variable initialization code. This
         * restriction is wanted by design, because different platforms and compilers implement the
         * initialization phase of static and global code differently and it is not considered
         * good programming style to rely on C++ bootstrap. Using AWXU within C++ bootstrap is
         * undefined behavior.
         ******************************************************************************************/
         AWXU_API static void     Init();

        /** ****************************************************************************************
         * Cleans up memory on termination. This method is useful if using memory analysis tools
         * (such as Valgrind) to remove any internal allocations before a program terminates.
         ******************************************************************************************/
        AWXU_API  static void     TerminationCleanUp();

    // #############################################################################################
    // Error handler interface
    // #############################################################################################
    public:

        /** ****************************************************************************************
         *  Flag, which if set to true, causes calls to #Error to halt program execution.
         *  Can be set at runtime by just overwriting the value.
         *   If !NDEBUG this 'assert(false)'. If NDEBUG, this defaults to false.
         ******************************************************************************************/
        AWXU_API  static bool                 HaltOnError;

        /** ****************************************************************************************
         *    Flag, which if set to true, causes calls to #Warning to halt program execution.
         *  Can be set at runtime by just overwriting the value.
         *    If !NDEBUG this 'assert(false)'. If NDEBUG, this defaults to false.
         ******************************************************************************************/
        AWXU_API  static bool                 HaltOnWarning;

        /** ****************************************************************************************
         *  Returns true, if an error handler singleton was set. In this case, an internal mutex remains
         *  locked. A subsequent call to #Error or #Warning will release the mutex. Alternatively,
         *  #AbortErrorHandler has to be called. The reason for this design is, that the assembly of a
         *  merely complex error string should happen only if an error handler is available. The usual way
         *  to use the error handler is:<br>if ( AWXU::AcquireErrorHandler() ) AWXU::Error( ... );<br> In the case
         *  that no error handler is available, false is returned and the internal mutex is not acquired
         *  and must not be released.
         *
         * @return true if successful.
         ******************************************************************************************/
        AWXU_API  static bool                 AcquireErrorHandler();

        /** ****************************************************************************************
         *  Forwards the given message to the current error handler in place. The default error
         *  handler of AWXU will print the message on the process console. Furthermore, in debug
         *  execution the flag HaltOnError is checked. If this is set the program halts or
         *  suspends into the debugger (platform and language specific).
         *
         * @param msg The error message.
         ******************************************************************************************/
        AWXU_API  static void                 Error( const char* msg );

        /** ****************************************************************************************
         *  Forwards the given message to the current error handler in place. The default error
         *  handler of AWXU will print the message on the process console. Furthermore, in debug
         *  execution the flag HaltOnWarning is checked. If this is set the program halts or
         *  suspends into the debugger (platform and language specific).
         *
         * @param msg The warning message.
         ******************************************************************************************/
        AWXU_API  static void                 Warning( const char* msg );

        /** ****************************************************************************************
         *  Forwards the given message to the current error handler in place. The default error
         *  handler of AWXU will print the message on the process console.
         *
         * @param msg The warning message.
         ******************************************************************************************/
        AWXU_API  static void                 DebugMsg( const char* msg );

        /** ****************************************************************************************
         *     Releases the internal mutex which gets acquired calling #AcquireErrorHandler. This method
         *  can be used to avoid calling #Warning or #Error.
         *
         ******************************************************************************************/
        AWXU_API  static void                 AbortErrorHandler();

        /** ****************************************************************************************
         *     Replaces the current (if any) error handler singleton by the one provided. If a different
         *  error handler was set before, the former one, will be returned (e.g. for deletion).
         *  If nullptr is provided, the error handler will be unset.
         *
         * @param newErrorHandler The error handler to set.
         * @return The former error handler.
         ******************************************************************************************/
        AWXU_API  static AWXUErrorHandler*    ReplaceErrorHandler( AWXUErrorHandler* newErrorHandler );

    // #############################################################################################
    // Other static interface methods
    // #############################################################################################
    public:
        /** ****************************************************************************************
         *  This is calling Thread.Sleep(). This is for compatibility with other platform
         *  versions of A-Worx Utility Classes.
         *  Variants of this method are #SleepMicros and #SleepNanos.
         *
         *  @param millisecs    Sleep time in milliseconds.
         ******************************************************************************************/
        AWXU_API  static void SleepMillis( int millisecs );

        /** ****************************************************************************************
         *
         *    This is calling Thread.Sleep(). This is for compatibility with other platform
         *    versions of A-Worx Utility Classes.
         *    Variants of this method are #SleepMillis and #SleepNanos.
         *
         * @param microsecs    Sleep time in milliseconds.
         ******************************************************************************************/
        AWXU_API  static void SleepMicros( int microsecs );

        /** ****************************************************************************************
         *  This is calling Thread.Sleep(). This is for compatibility with other platform
         *  versions of A-Worx Utility Classes.
         *  Variants of this method are #SleepMicros and #SleepMillis.
         *
         * @param nanosecs    Sleep time in nanoseconds.
         ******************************************************************************************/
        AWXU_API  static void SleepNanos( int nanosecs );

};// class AWXU


}} // namespace aworx::util




#endif // HPP_AWORX_UTIL_AWXU
