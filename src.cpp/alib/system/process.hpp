// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
/** @file */ // Hello Doxygen

// check for alib.hpp already there but not us
#if !defined (HPP_ALIB_ALIB)
    #error "include \"alib/alib.hpp\" before including this header"
#endif
#if defined(HPP_COM_ALIB_TEST_INCLUDES) && defined(HPP_ALIB_SYSTEM_PROCESSINFO)
    #error "Header already included"
#endif

// then, set include guard
#ifndef HPP_ALIB_SYSTEM_PROCESSINFO
#if !defined( IS_DOXYGEN_PARSER)
#define HPP_ALIB_SYSTEM_PROCESSINFO 1
#endif

namespace aworx {
namespace           lib {
namespace                   system {

/** ************************************************************************************************
 *  This class represents process information
 **************************************************************************************************/
class ProcessInfo
{
    // #############################################################################################
    // Fields
    // #############################################################################################
    protected:
        /** Information on the current process. This is initialized once, with the first invocation
         *  of #Current.   */
        ALIB_API static ProcessInfo    current;

    // #############################################################################################
    // Fields under unix like OS
    // #############################################################################################
    #if defined( __unix__ )
        friend class Environment;

        public:
            /** The process id as AString.  */
            String16    PID;

            /** The parent's process id as AString. (Unix like OS only.)   */
            String16    PPID;

            /** The name of the process' executable. (Unix like OS only.)   */
            String32    ExecName;

            /** The command line which invoked this process.      */
            AString     CmdLine;

            /** The contents of /proc/PID/stat file. (Unix like OS only.)   */
            AString     Stat;

            /** The state field (2) within \ref Stat. (Unix like OS only.)   */
            AString     StatState;

            /** The process group field (4) within \ref Stat. (Unix like OS only.)   */
            AString     statPGRP;
    #endif

    // #############################################################################################
    // Fields under Windows OS
    // #############################################################################################
    #if defined( _WIN32 )
        public:
            String16    PID;        // already doxed above

            AString     CmdLine;    // already doxed above

            /** For console processes, this is the title displayed in the title bar. (Windows OS only.) */
            AString     ConsoleTitle;
    #endif

    // we must not work with #elif here, as doxygen would not document the else part
    #if !defined( __unix__ ) && !defined( _WIN32 )
        #pragma message ("Unknown Platform in file: " __FILE__ )
    #endif

    // #############################################################################################
    // Protected methods
    // #############################################################################################
    protected:
        /** ****************************************************************************************
         * Default constructor to create an empty instance
         ******************************************************************************************/
                              ProcessInfo()                   {}


        #if defined( __unix__ )
            /** ************************************************************************************
             * Reads a field from the data found in /proc/PID/stat.
             *  @param fieldNo  The field number to read
             *  @param result   The variable to store the result in
             *  @returns \c true if successful.
             **************************************************************************************/
            bool        getStatField( int fieldNo, AString& result );
        #endif

        /** ************************************************************************************
         * Internal get() method with different platform implementations.
         *
         * @param PID  The ID of the process information is requested on.
         *             If a nulled string is provided, the current process is addressed.
         *
         * @return \c true on success, \c false otherwise.
         **************************************************************************************/
        ALIB_API bool          get( const String& PID  );

    // #############################################################################################
    // Interface
    // #############################################################################################
    public:
        #if defined( __unix__ )
            /** ************************************************************************************
             * Constructor that initializes this instance according to the process information
             * received from the system.
             *
             * \note This method is implemented for Unix like OS only.
             *       On other platforms, only information about the current process can be received
             *       using static method #Current.
             *
             * @param PID          The ID of the process information is requested on as string.
             *                     If a nulled string is provided, the current process is addressed.
             ***************************************************************************************/
                                   ProcessInfo( const String& PID  ) { get( PID ); }

            /** ************************************************************************************
             * Fills the fields of this instance according to the process information received from
             * the system.
             *
             * \note This method is implemented for Unix like OS only.
             *       On other platforms, only information about the current process can be received
             *       using static method #Current.
             *
             * @param PID  The ID of the process information is requested on.
             *             If a nulled string is provided, the current process is addressed.
             *
             * @return \c true on success, \c false otherwise.
             **************************************************************************************/
            ALIB_API bool          Get( const String& PID  ) { return get( PID ); }
        #endif

        /** ****************************************************************************************
         * Static method that receives information on the current process.
         *
         * @return A constant reference to a \c %ProcessInfo object representing the current process.
         ******************************************************************************************/
        static const ProcessInfo&         Current()
        {
            if ( current.PID.IsEmpty() )
                current.get(nullptr);
            return current;
        }
};

}} // namespace lib::system

/** Type alias name in namespace #aworx. */
using     ProcessInfo=       aworx::lib::system::ProcessInfo;

}  // namespace aworx

#endif // HPP_ALIB_SYSTEM_PROCESSINFO
