// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################

/** ************************************************************************************************
 * This namespace collects very basic utilities, close to the C# language.
 * In other words, elements found in this namespace are not complex enough to justify a
 * dedicated sub-namespace, but are also not essential enough to be placed in
 * #cs::aworx::lib itself. The latter namespace is reserved for elements that are essential to
 * and included by separated <b>ALib Modules</b>. (Modules are available in the C++ version
 * of \b %ALib only.
 *
 * \note
 *   A list of <b>general enumerations</b> is found in this namespace.
 *   It is arguable and a matter of taste, whether enumerations should be declared near or inside
 *   the class which is using it, or in a separated place like this namespace introduced here.<br>
 *   ALib follows the second approach (not strictly, domain specific enums might appear also inside
 *   classes) and this has the following reasons:
 *   - To shorten the code when using the enums.
 *   - To reach a maximum degree of source compatibility between the different programming language
 *     versions of ALib.
 *   - To make the enums reusable with different classes.
 **************************************************************************************************/
namespace cs.aworx.lib.lang {

/** ************************************************************************************************
 * Denotes if sth. is switched on or off
 **************************************************************************************************/
public enum Switch
{
    Off,    ///< Switch it off, switched off, etc.
    On      ///< Switch it on, switched on, etc.
}

/** ************************************************************************************************
 * Denotes Alignments
 **************************************************************************************************/
public enum Alignment
{
    Left,   ///<  Chooses left alignment.
    Right,  ///<  Chooses right alignment.
    Center  ///<  Chooses centered alignment.
}

/** ************************************************************************************************
 * Denotes sort order.
 **************************************************************************************************/
public enum SortOrder
{
    Ascending,   ///<  Chooses ascending sort oder.
    Descending   ///<  Chooses descending sort oder.
}

/** ************************************************************************************************
 * Denotes how members of a set something should be taken into account.
 **************************************************************************************************/
public enum Inclusion
{
    Include,  ///<  Chooses inclusion.
    Exclude   ///<  Chooses exclusion.
}

/** ************************************************************************************************
 * Denotes the reach of something.
 **************************************************************************************************/
public enum Reach
{
    Global,    ///< Denotes global reach.
    Local      ///< Denotes local reach.
};

/** ************************************************************************************************
 * Denotes upper and lower case character treatment.
 **************************************************************************************************/
public enum Case
{
    Sensitive, ///< Chooses an operation mode which differs between lower and upper case letters
               ///  (usually the default).
    Ignore     ///< Chooses an operation mode which does not differ between between lower and
               ///  upper case letters.
}


/** ************************************************************************************************
 * Denotes whether something should be performed in a safe or unsafe fashion.
 **************************************************************************************************/
public enum Safeness
{
    Safe,    ///<  Do it or treat it with safety
    Unsafe,  ///<  Omit checks or perform unsafe operations
};

/** ************************************************************************************************
 * Denotes whether a lock should allow recursive locks (count them) or not.
 **************************************************************************************************/
public enum LockMode
{
    Recursive,    ///< Allow nested locks
    SingleLocks   ///< Nested locks are ignored. First unlock, unlocks.
}

/** ************************************************************************************************
 * Denotes whether a string is trimmed or not
 **************************************************************************************************/
public enum Whitespaces
{
    Trim,       ///< Trim whitespaces away
    Keep        ///< Keep whitespaces in string
};

/** ************************************************************************************************
 * Denotes if the source data should be moved or copied.
 **************************************************************************************************/
public enum CurrentData
{
    Keep,    ///<  Chooses not no clear existing data.
    Clear    ///<  Chooses to clear existing data.
}

/** ************************************************************************************************
 * Denotes if current, existing data should be cleared or if new data should be
 * appended or otherwise added.
 **************************************************************************************************/
public enum SourceData
{
    Copy,   ///<  Chooses not to clear existing data.
    Move,   ///<  Chooses to clear existing data.
}

/** ************************************************************************************************
 * Denotes whether something should be created if it does not exist.
 **************************************************************************************************/
public enum Create
{
    Never,          ///< Do not create.
    IfNotExistent   ///< Create if something does not exist.
}

/** ************************************************************************************************
 * Denotes whether a e.g a setting should be propagated.
 **************************************************************************************************/
public enum Propagation
{
    Omit,          ///< Do not propagate changes.
    ToDescendants  ///< Propagate changes to descendants/children/subcomponents.
}

/** ****************************************************************************************
 * Denotes a phase, e.g. of a transaction.
 ******************************************************************************************/
public enum Phase
{
    Begin,    ///< The start of a transaction.
    End       ///< The end of a transaction.
}

/** ************************************************************************************************
 * Denotes standard container operations.
 **************************************************************************************************/
public enum ContainerOp
{
    Insert,    ///< Denotes insertions.
    Remove,    ///< Denotes removals.
    Get,       ///< Denotes to search data.
    GetCreate, ///< Denotes to create data if not found.
    Create     ///< Denotes to create data.
}



} // namespace / EOF
