// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
/** @file */ // Hello Doxygen

// to preserve the right order, we are not includable directly from outside.
#if !defined(ALIB_PROPER_INCLUSION) || defined(HPP_ALIB_LANG_ENUMS)
    #error "include alib/alib.hpp instead of this header"
#endif

#ifndef HPP_ALIB_LANG_ENUMS
#define HPP_ALIB_LANG_ENUMS 1

namespace aworx { namespace lib { namespace lang {


/** ************************************************************************************************
 * Denotes if sth. is switched on or off.
 **************************************************************************************************/
enum class Switch
{
    Off,    ///< Switch it off, switched off, etc.
    On      ///< Switch it on, switched on, etc.
};

/** ************************************************************************************************
 * Denotes upper and lower case character treatment.
 **************************************************************************************************/
enum class Case
{
    Sensitive, ///< Chooses an operation mode which differs between lower and upper case letters
               ///  (usually the default).
    Ignore     ///< Chooses an operation mode which does not differ between between lower and
               ///  upper case letters.
};

/** ************************************************************************************************
 * Denotes Alignments.
 **************************************************************************************************/
enum class Alignment
{
    Left,   ///<  Chooses left alignment.
    Right,  ///<  Chooses right alignment.
    Center  ///<  Chooses centered alignment.
};

/** ************************************************************************************************
 * Denotes how members of a set something should be taken into account.
 **************************************************************************************************/
enum class Inclusion
{
    Include,  ///<  Chooses inclusion.
    Exclude,  ///<  Chooses exclusion.
};

/** ************************************************************************************************
 * Denotes the reach of something.
 **************************************************************************************************/
enum class Reach
{
    Global,    ///< Denotes global reach.
    Local      ///< Denotes local reach.
};

/** ************************************************************************************************
 * Denotes if current, existing data should be cleared or if new data should be
 * appended or otherwise added.
 **************************************************************************************************/
enum class CurrentData
{
    Keep,    ///<  Chooses not no clear existing data.
    Clear,   ///<  Chooses to clear existing data.
};

/** ************************************************************************************************
 * Denotes whether something should be performed in a safe or unsafe fashion.
 **************************************************************************************************/
enum class Safeness
{
    Safe,    ///<  Do it or treat it with safety
    Unsafe,  ///<  Omit checks or perform unsafe operations
};

/** ************************************************************************************************
 * Denotes whether the responsibility for something is kept or passed. This is useful, e.g. in
 * situations where objects are shared to determine if the responsibility for the deletion
 * of object is transferred over to the receiver or kept by the sender of the object.
 **************************************************************************************************/
enum class Responsibility
{
    KeepWithSender,  ///<  Keeps responsibility, e.g. when passing an object.
    Transfer,        ///<  Transfers responsibility to the receiving party.
};

/** ************************************************************************************************
 * Denotes whether a time value represents local time or UTC.
 **************************************************************************************************/
enum class Timezone
{
    Local,  ///<  Denotes local time.
    UTC,    ///<  Denotes UTC (coordinated universal time).
};

/** ************************************************************************************************
 * Denotes whether a lock should allow recursive locks (count them) or not.
 **************************************************************************************************/

enum class LockMode
{
    Recursive,    ///< Allow nested locks.
    SingleLocks   ///< Nested locks are ignored. First unlock, unlocks.
};

/** ************************************************************************************************
 * Denotes whether a string is trimmed or not
 **************************************************************************************************/
enum class Whitespaces
{
    Trim,       ///< Trim whitespaces away.
    Keep        ///< Keep whitespaces in string.
};


/** ************************************************************************************************
 * Denotes whether something should be created if it does not exist.
 **************************************************************************************************/
enum class Create
{
    Never,          ///< Do not create.
    IfNotExistent   ///< Create if something does not exist.
};


/** ************************************************************************************************
 * Denotes whether a e.g a setting should be propagated.
 **************************************************************************************************/
enum class Propagation
{
    Omit,          ///< Do not propagate changes.
    ToDescendants  ///< Propagate changes to descendants/children/sub-components.
};

/** ************************************************************************************************
 * Denotes a phase, e.g. of a transaction.
 **************************************************************************************************/
enum class Phase
{
    Begin,    ///< The start of a transaction.
    End       ///< The end of a transaction.
};

/** ************************************************************************************************
 * Denotes standard container operations.
 **************************************************************************************************/
enum class ContainerOp
{
    Insert,    ///< Denotes insertions.
    Remove,    ///< Denotes removals.
    Get,       ///< Denotes to search data.
    GetCreate, ///< Denotes to create data if not found.
    Create     ///< Denotes to create data.
};


/** ************************************************************************************************
 * Denotes result values across ALib functions
 **************************************************************************************************/
enum class Result
{
    OK,          ///< Everything is fine.
    Error,       ///< An unspecified error occurred.

    // ####### Files, Directories, IO #######

    // Directory::Create
    FileExists,                ///< File or directory already exists. This includes the case where pathname is a symbolic link, dangling or not.
    InvalidPath,               ///< A directory component in pathname does not exist or is a dangling symbolic link

    #if defined (__GLIBC__) || defined(__APPLE__)
      Directory_Create_EACCES         , ///< The parent directory does not allow write permission to the process, or one of the directories in pathname did not allow search permission.
      Directory_Create_EDQUOT         , ///< The user's quota of disk blocks or inodes on the file system has been exhausted.
      Directory_Create_EFAULT         , ///< Pathname points outside your accessible address space.
      Directory_Create_ELOOP          , ///< Too many symbolic links were encountered in resolving pathname.
      Directory_Create_EMLINK         , ///< The number of links to the parent directory would exceed LINK_MAX.
      Directory_Create_ENAMETOOLONG   , ///< Pathname was too long.
      Directory_Create_ENOMEM         , ///< Insufficient kernel memory was available.
      Directory_Create_ENOSPC         , ///< The device containing pathname has no room for the new directory (or that the user's disk quota is exhausted).
      Directory_Create_ENOTDIR        , ///< A component used as a directory in pathname is not, in fact, a directory.
      Directory_Create_EPERM          , ///< The file system containing pathname does not support the creation of directories.
      Directory_Create_EROFS          , ///< Pathname refers to a file on a read-only file system.
   #endif

};

// #################################################################################################
// Methods to 'parse' ALib enum values from strings.
// #################################################################################################
#if ALIB_MODULE_STRINGS

    // forward declaration of class strings
    } namespace strings { class String; } namespace lang {

    /** ********************************************************************************************
     * Interprets given \p src as a boolean value.
     * If the case insensitive comparison of the first non-whitespace characters of the string with
     * with values "t", "1", "y", "on", "ok"
     * matches, \c true is returned.
     * Otherwise, including the case that \p src is 'nulled', \c false is returned.
     *
     * @param src The string to 'parse'.
     *
     * @returns The \b %Case value read.
     **********************************************************************************************/
    ALIB_API
    bool         ReadBoolean( const strings::String& src );

    /** ********************************************************************************************
     * Interprets given \p src as a value of enum type
     * \ref aworx::lib::lang::Case "lang::Case".
     * If the case insensitive comparison of the first non-whitespace characters of the string
     * with values "s", "y", "t", "1"
     * matches, \b %Case::Sensitive is returned.
     * Otherwise, including the case that \p src is 'nulled', \b %Case::Ignore is returned.
     *
     * @param src The string to 'parse'.
     *
     * @returns The \b %Case value read.
     **********************************************************************************************/
    ALIB_API
    Case        ReadCase( const strings::String& src );

    /** ********************************************************************************************
     * Interprets given \p src as a value of enum type
     * \ref aworx::lib::lang::Inclusion "lang::Inclusion".
     * If the case insensitive comparison of the first non-whitespace characters of the string
     * with values "i", "y", "t", "1"
     * matches, \b %Inclusion::Include is returned.
     * Otherwise, including the case that \p src is 'nulled', \b %Inclusion::Exclude is returned.
     *
     * @param src The string to 'parse'.
     *
     * @returns The \b %Inclusion value read.
     **********************************************************************************************/
    ALIB_API
    Inclusion   ReadInclusion( const strings::String& src );

#endif // ALIB_MODULE_STRINGS


}} // namespace lib::lang

/** Type alias name in namespace #aworx. */
using     Switch=           aworx::lib::lang::Switch;

/** Type alias name in namespace #aworx. */
using     Case=             aworx::lib::lang::Case;

/** Type alias name in namespace #aworx. */
using     Alignment=        aworx::lib::lang::Alignment;

/** Type alias name in namespace #aworx. */
using     Inclusion=        aworx::lib::lang::Inclusion;

/** Type alias name in namespace #aworx. */
using     Reach=            aworx::lib::lang::Reach;

/** Type alias name in namespace #aworx. */
using     CurrentData=      aworx::lib::lang::CurrentData;

/** Type alias name in namespace #aworx. */
using     Safeness=         aworx::lib::lang::Safeness;

/** Type alias name in namespace #aworx. */
using     Responsibility=   aworx::lib::lang::Responsibility;

/** Type alias name in namespace #aworx. */
using     Timezone=         aworx::lib::lang::Timezone;

/** Type alias name in namespace #aworx. */
using     LockMode=         aworx::lib::lang::LockMode;

/** Type alias name in namespace #aworx. */
using     Whitespaces=      aworx::lib::lang::Whitespaces;

/** Type alias name in namespace #aworx. */
using     Create=           aworx::lib::lang::Create;

/** Type alias name in namespace #aworx. */
using     Propagation=      aworx::lib::lang::Propagation;

/** Type alias name in namespace #aworx. */
using     Phase=            aworx::lib::lang::Phase;

/** Type alias name in namespace #aworx. */
using     ContainerOp=      aworx::lib::lang::ContainerOp;

/** Type alias name in namespace #aworx. */
using     Result=           aworx::lib::lang::Result;

}  // namespace aworx


#endif // HPP_ALIB_LANG_ENUMS
