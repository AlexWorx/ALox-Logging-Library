// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
/** @file */ // Hello Doxygen


// check for alib.hpp already there but not us
#if !defined (HPP_ALIB)
    #error "include \"alib/alib.hpp\" before including this header"
#endif
#if defined(HPP_COM_ALIB_TEST_INCLUDES) && defined(HPP_ALIB_SYSTEM_SYSTEM)
    #error "Header already included"
#endif

// then, set include guard
#ifndef HPP_ALIB_SYSTEM_SYSTEM
#if !defined( IS_DOXYGEN_PARSER)
#define HPP_ALIB_SYSTEM_SYSTEM 1
#endif

namespace aworx {
namespace           lib {

/**
 *  This namespace of ALib holds classes that interfacing with the operating system.
 */
namespace                   system {

/** ************************************************************************************************
 *  This class represents system information
 **************************************************************************************************/
class System
{
    // #############################################################################################
    // Environment definition/detection
    // #############################################################################################
    public:
        /** ****************************************************************************************
         *  These are definitions to identify within which environment (e.g. IDE) the process
         *  is running.
         *  \see Member #RTE.
         ******************************************************************************************/
        enum class RuntimeEnvironment
        {
            Unknown,                ///< No build system defined/detected
            EclipseCDT,             ///< Eclispe with CDT
            QTCreator,              ///< QT Creator
            VStudio,                ///< Microsoft Visual Studio

            Shell,                  ///< A command shell like bash, ksh, fish, etc.
            Desktop,                ///< GUI applications that most probably are not attached to a console.
            MobileDevice,           ///< GUI applications mobile devices or similar consumer products.
        };

        /** ****************************************************************************************
         * Provides information on the runtime environment (e.g. IDE), that the current process
         * was started in.
         *
         * The value returned can be manipulated by setting configuration variable
         * [ALIB_RTE](../group__GrpALoxConfigVars.html).<br>
         *
         * If this variable was not set, under Unix like OS, it is tried to determined by
         * investigating into parent process names.
         *
         * Otherwise, under Unix like OS, \b RuntimeEnvironment::Unknown is returned. Under
         * Windows OS \b RuntimeEnvironment::Shell is returned if a console window is attached to
         * the process, otherwise RuntimeEnvironment::Desktop.
         *
         * \note By nature, this method might undergo changes in the future. See source code of
         *       ALib version in use for details.
         *
         * @return The \b RuntimeEnvironment detected.
         ******************************************************************************************/
        ALIB_API
        static RuntimeEnvironment   RTE();

        /** ****************************************************************************************
         * This determines if the current process has console output window attached.
         * While this is not detectable in Unix like systems (or just with huge efforts), in
         * windows it is. The determination works as follows
         *  - If configuration variable [ALIB_HAS_CONSOLE_WINDOW](../group__GrpALoxConfigVars.html)
         *    is set, its value is returned.
         *  - Otherwise, on Unix like OS\c true is returned
         *  - On Windows OS it is determined if a console window is attached to the process
         *    using system call \e GetConsoleWindow() and compare its result to \e NULL.
         *  @return \c true if the application has a console window attached.
         ******************************************************************************************/
        ALIB_API
        static bool                 HasConsoleWindow();

        /** ****************************************************************************************
         * If \c true, the current process is under the hood of a debugger. This is evaluated
         * within \ref aworx::lib::ALIB::Init "ALIB::Init".
         * \see Field #DebuggerProcessName.
         *
         * @return \c true if the application is run in a debugger.
         ******************************************************************************************/
        ALIB_API
        static bool                 IsDebuggerPresent();

        /** ****************************************************************************************
         * Available under Unix like OS only. Used by method #IsDebuggerPresent to determine
         * if a debugger process is found in the list of parent processes.<br>
         * Defaults to \e 'gdb' and can be changed on bootstrap of the process if a different
         * debugger is used.
         ******************************************************************************************/
        #if defined(__unix__)
        ALIB_API
        static String               DebuggerProcessName;
        #endif


        /** ****************************************************************************************
         *  Returns the value of an environment variable.
         *
         *  \note While under posix compatible operating systems, environment variable names are
         *        case sensitive, under Microsoft windows they are not. Therefore, the default
         *        behavior of this implementation is also not case sensitive. This means, that
         *        if under a posix OS more than one variable are defined whose names differ only in
         *        lower/upper case writing, this method behaves undefined in respect to which
         *        value is returned.
         *
         *        Parameter \p caseSensitive can be used to switch to case sensitive mode. However,
         *        if used under Microsoft Windows operating system, setting this value to \c true
         *        will throw an assertion in the debug version of this library.
         *
         *  @param varName      The name of the variable to be retrieved.
         *  @param target       An AString to write the result to.
         *  @param targetData   If \c CurrentData::Keep, the parameter \p target is not cleared
         *                      before the result is written. Defaults to \c CurrentData::Clear.
         *  @param sensitivity  Use case sensitive mode for variable names. Not supported under
         *                      Microsoft Windows OS. Defaults to
         *                      \ref aworx::lib::enums::Case::Ignore "Case::Ignore".
         *  @return \c true if variable was found.
         ******************************************************************************************/
        ALIB_API
        static  bool  GetVariable(  const TString& varName,
                                    AString&           target,
                                    enums::CurrentData targetData  =enums::CurrentData::Clear,
                                    enums::Case        sensitivity =enums::Case::Ignore          );


    // #############################################################################################
    // Others
    // #############################################################################################
        /** ****************************************************************************************
         * Receives the name of the process. Evaluated only once, can't change.
         * @return The name of the process.
         ******************************************************************************************/
        inline
        static
        const String& GetProcessName()
        {
            if( processName.IsNull() )
                getProcessName();

            return processName;
        }

    // #############################################################################################
    // Internals
    // #############################################################################################
        protected:

        /** The process name, retrieved once on request  */
        static AString              processName;
        /** ****************************************************************************************
         * Invoked only once in a life-time. Receives the process name.
         ******************************************************************************************/
        ALIB_API
        static void getProcessName();


};// class System

}} // namespace lib::system

/** Type alias name in namespace #aworx. */
using     System=       aworx::lib::system::System;

}  // namespace aworx

#endif // HPP_ALIB_SYSTEM_SYSTEM
