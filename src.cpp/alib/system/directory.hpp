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
#if defined(HPP_COM_ALIB_TEST_INCLUDES) && defined(HPP_ALIB_SYSTEM_DIRECTORY)
    #error "Header already included"
#endif

// then, set include guard
#ifndef HPP_ALIB_SYSTEM_DIRECTORY
#if !defined( IS_DOXYGEN_PARSER)
#define HPP_ALIB_SYSTEM_DIRECTORY 1
#endif

namespace aworx {
namespace           lib {
namespace                   system {

/** ************************************************************************************************
 *  Represents a directory (folder) in a file system.
 **************************************************************************************************/
class Directory
{
    public:

        /** ****************************************************************************************
         * Denotes upper and lower case character conversions
         ******************************************************************************************/
        enum class SpecialFolder
        {
            /** The root directory .*/
            Root,

            /** The current directory of the process.*/
            Current,

            /** The user's home directory */
            Home,

            /**
             * The user's configuration directory. This is evaluated as follows:
             * - Using environment variable \e HOME (under WindowsOS a combination of \e HOMEDRIVE
             *   and \e HOMEPATH), the home directory is determined.
             * - If within this a directory \e ".config" exists, it is used, otherwise
             * - if within this the directories \e "AppData/Roaming" exist, this is used.
             */
            HOME_CONFIG,

            /** The directory of the executable. (Not implemented, yet) */
            Module

        };

    public:
    // #############################################################################################
    // Fields
    // #############################################################################################
    public:
        /// The path of the directory represented by this instance
        String256      Path;

    // #############################################################################################
    // Constructors
    // #############################################################################################
    public:
        /** ****************************************************************************************
         * Constructs an object representing one of the known special directories.
         * @param special  The special directory to initialize this instance to.
         * @returns \c true if the change was successfull, \c false otherwise.
         ******************************************************************************************/
        inline                  Directory( SpecialFolder special )
        {
            Change( special );
        }


        /** ****************************************************************************************
         * Constructs an object representing the given path.
         * @param path  The initial path. If this is a relative path, it relates to the processes
         *              current directory.
         ******************************************************************************************/
        inline                  Directory( const String& path )
        {
            Path._( path );
        }


    // #############################################################################################
    // Interface
    // #############################################################################################
    public:
        /** ****************************************************************************************
         * @returns \c true if the directory represented by #Path is existing
         ******************************************************************************************/
        ALIB_API   bool         IsValid();

        /** ****************************************************************************************
         * Changes the directory. If the given path is relative (e.g. a name of a sub directory
         * or ".."), such path is added to the current #Path. Otherwise, field #Path is replaced.
         * If the resulting destination directory is not valid, \c false is returned and the
         * field #Path stays intact.
         * @param    path  The relative or absolute path to change to.
         * @returns \c true if the change was successfull, \c false otherwise.
         ******************************************************************************************/
        ALIB_API   bool         Change( const String& path );


        /** ****************************************************************************************
         * Changes the directory to one of the known special directories.
         * @param special  The special directory to change this instance to.
         ******************************************************************************************/
        ALIB_API   void         Change( SpecialFolder special );


    // #############################################################################################
    // static interface
    // #############################################################################################
    public:
        /** ****************************************************************************************
         *  Returns the actual directory in the file system associated with the current process.
         *  @param target The target AString to store the directory. Will be cleared in any case
         *  @return \c true on success, \c false on failure.
         ******************************************************************************************/
        ALIB_API static  bool           CurrentDirectory( AString& target );

        /** ****************************************************************************************
         *  Tests if the given (absolute or relative) path represents a directory in the file system.
         *  @param path     The path to test.
         *  @return \c true if a directory was found.
         ******************************************************************************************/
        ALIB_API static  bool           Exists( const TString& path );

        /** ****************************************************************************************
         *  Creates the directory of the given (absolute or relative) path.
         *  @param path     The path to test.
         *  @return \b Result::OK if a directory was found. Common errors codes are:
         *          - \ref aworx::lib::enums::Result::InvalidPath "Result::InvalidPath"
         *          - \ref aworx::lib::enums::Result::FileExists  "Result::FileExists"
         *          but other errors might occur as well (OS dependent).
         ******************************************************************************************/
        ALIB_API static enums::Result   Create( const TString& path );
}; //class Directory

}} // namespace lib::system

/** Type alias name in namespace #aworx. */
using     Directory=       aworx::lib::system::Directory;

/**
 * The standard path separator character. Defaults to '\\' on Windows OS, '/' else.
 * Note: Available only with including "alib/system/directory.hpp"
 */
constexpr char    PathSeparator
#if defined(IS_DOXYGEN_PARSER)
    ;
#else
    =
                                                                    #if defined( _WIN32 )
                                                                        '\\';
                                                                    #else
                                                                        '/';
                                                                    #endif
#endif
}  // namespace aworx

#endif // HPP_ALIB_SYSTEM_DIRECTORY
