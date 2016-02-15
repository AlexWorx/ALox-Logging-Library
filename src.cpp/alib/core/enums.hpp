// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
/** @file */ // Hello Doxygen

// to preserve the right order, we are not includable directly from outside.
#if !defined(FROM_HPP_ALIB_ALIB) || defined(HPP_ALIB_ENUMS)
    #error "include alib/alib.hpp instead of this header"
#endif

// Due to our blocker above, this include will never be executed. But having it, allows IDEs
// (e.g. QTCreator) to read the symbols when opening this file
#if !defined (HPP_ALIB_ALIB)
    #include "alib/alib.hpp"
#endif

#ifndef HPP_ALIB_ENUMS
#define HPP_ALIB_ENUMS 1

namespace aworx {
namespace           lib {

/** ************************************************************************************************
 * This namespace of the A-Worx Library (ALib) is used to declare general enumerations.
 * \note
 *   It is arguable and a matter of taste, whether enumerations should be declared near or inside
 *   the class which is using it, or in a separated place like this namespace introduced here.<br>
 *   ALib follows the second approach (not strictly, domain specific enums might appear also inside
 *   classes) and this has the following reasons:
 *   - To shorten the code when using the enums.
 *   - To reach a maximum degree of source compatibility between the different programming language
 *     versions of ALib.
 *   - To make the enums reusable with different classes.
 **************************************************************************************************/
namespace                   enums {


/** ************************************************************************************************
 * Denotes if sth. is switched on or off
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
 * Denotes whether the responsiblity for something is kept or passed. This is useful, e.g. in
 * situations where objects are shared to determine if the responsiblity for the deletion
 * of object is transfered over to the receiver or kept by the sender of the object.
 **************************************************************************************************/
enum class Responsibility
{
    KeepWithSender,  ///<  Keeps responsibility, e.g. when passing an object.
    Transfer,        ///<  Transfers responsiblitiy to the receiving party.
};

/** ************************************************************************************************
 * Denotes whether a time is defined as beeing local time or UTC.
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
    None,          ///< Do not propagate changes.
    ToDescendants  ///< Propagate changes to descendants/childs/subcomponents.
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

    #if defined (__GLIBC__)
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



}} // namespace lib::enums

/** Type alias name in namespace #aworx. */
using     Switch=           aworx::lib::enums::Switch;

/** Type alias name in namespace #aworx. */
using     Case=             aworx::lib::enums::Case;

/** Type alias name in namespace #aworx. */
using     Alignment=        aworx::lib::enums::Alignment;

/** Type alias name in namespace #aworx. */
using     Inclusion=        aworx::lib::enums::Inclusion;

/** Type alias name in namespace #aworx. */
using     CurrentData=      aworx::lib::enums::CurrentData;

/** Type alias name in namespace #aworx. */
using     Safeness=         aworx::lib::enums::Safeness;

/** Type alias name in namespace #aworx. */
using     Responsibility=   aworx::lib::enums::Responsibility;

/** Type alias name in namespace #aworx. */
using     Timezone=         aworx::lib::enums::Timezone;

/** Type alias name in namespace #aworx. */
using     LockMode=         aworx::lib::enums::LockMode;

/** Type alias name in namespace #aworx. */
using     Whitespaces=      aworx::lib::enums::Whitespaces;

/** Type alias name in namespace #aworx. */
using     Create=           aworx::lib::enums::Create;

/** Type alias name in namespace #aworx. */
using     Propagation=      aworx::lib::enums::Propagation;

/** Type alias name in namespace #aworx. */
using     Phase=            aworx::lib::enums::Phase;

/** Type alias name in namespace #aworx. */
using     Result=           aworx::lib::enums::Result;

}  // namespace aworx

#endif // HPP_ALIB_ENUMS
