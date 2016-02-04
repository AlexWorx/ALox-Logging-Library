// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
/** @file */ // Hello Doxyen

// to preserve the right order, we are not includable directly from outside.
#if !defined(FROM_HPP_AWORX_LIB_ALIB) || defined(HPP_NAMESPACE_AWORX)
    #error "include alib/alib.hpp instead of this header"
#endif

// Due to our blocker above, this include will never be executed. But having it, allows IDEs
// (e.g. QTCreator) to read the symbols when opening this file
#if !defined (HPP_AWORX_LIB_ALIB)
    #include "alib/alib.hpp"
#endif

// then, set include guard
#ifndef HPP_NAMESPACE_AWORX
#define HPP_NAMESPACE_AWORX 1


/**
 * This is the outer C++ namespace for all classes published by A-Worx GmbH, Germany. <p>
 * \note While the Java language strongly proposes to use the complete 'reverse domain' name
 * and therefore Java code published by A-Worx GmbH resides in namespace <em>com.aworx</em>,
 * for C# we replaced the prefix <em>com.</em> with <em>cs.</em>, which leads to <em>cs.aworx</em>.<br>
 * This is for having classes with the same names existing in C++, C# and Java not collide
 * within the Doxygen documentation system.
 *
 * As far as it is planned today, there is nothing inside this namespace but other namespaces
 * and - and this is true only for the  \e C++ side of things - type definitions used as
 * shortcuts.
 *
*  \anchor CPP_AWORX_NS_SHORTCUTS
  * <b>Type Shortcuts in the aworx Namespace</b><p>
 * Introducing new names without good reasons should in general by avoided as it \e pollutes
 * any namespace. Furthermore it should be avoided to use identifier names that are so general
 * that conflicts are foreseeable. However, in this namespace \e ::aworx there is an exclamation.
 * It introduces <em>shortcut types</em> only for the sake of making the code more readable.
 * And, even more, those shortcuts are allowed to have quite general names. For example, the
 * following type is defined:
   \verbatim
   using  String =  aworx::lib::strings::AS;
   \endverbatim
 * The impact of this is as follows:
 * - Inside header files of sub-namespaces (and their sub-namespaces) of \e aworx, e.g. \e aworx::lib and \e aworx::lox,
 *   these names are visible and used.
 * - Inside external header files, they are not visible but might be quite shortly accessed
 *   using postfix \e aworx::.
 * - Inside cpp files that use aworx libraries they are \e not visible, even if a using statement
 *   for the corresponding namespace is added
 *
 * As a sample, in a source file which includes ALib and 'uses' the \e strings namespace by having
 * statement
   \verbatim
   using  aworx::lib::strings;
   \endverbatim
 * defined, still type alias \e String is not visible and therefore does not collide with any other
 * identifier that is named "String".
 *
 */
namespace aworx {

// #################################################################################################
// 'Import' types from aworx::alib::strings
// #################################################################################################

// ###### forwards ######
namespace lib { namespace strings {
                                class ASAlloc;
    template<int TCapacity>     class ASPreAlloc;
                                class ASSubstring;
    template<size_t TLength>    class ASLiteral;
}}

// ######  Type definitions: Shortcuts to ALib string classes ######

/** Type shortcut visible only in sub namespaces. */
using     String    =       aworx::lib::strings::AS;

/** Type shortcut visible only in sub namespaces. */
using     TString   =       aworx::lib::strings::ASTerminatable;

/** Type shortcut visible only in sub namespaces. */
using     AString   =       aworx::lib::strings::ASAlloc;

///** Type shortcut visible only in sub namespaces. */

template<size_t TLength>
using     StringLiteral =   aworx::lib::strings::ASLiteral<TLength>;

/** Type shortcut visible only in sub namespaces. */
using     Substring =       aworx::lib::strings::ASSubstring;


/// A shortcut to \ref aworx::lib::strings::ASPreAlloc "ASPreAlloc" providing an internal preallocated buffer of size 8.
using String8  =  aworx::lib::strings::ASPreAlloc<   8>;

/// A shortcut to \ref aworx::lib::strings::ASPreAlloc "ASPreAlloc" providing an internal preallocated buffer of size 16.
using String16 =  aworx::lib::strings::ASPreAlloc<  16>;

/// A shortcut to \ref aworx::lib::strings::ASPreAlloc "ASPreAlloc" providing an internal preallocated buffer of size 32.
using String32 =  aworx::lib::strings::ASPreAlloc<  32>;

/// A shortcut to \ref aworx::lib::strings::ASPreAlloc "ASPreAlloc" providing an internal preallocated buffer of size 64.
using String64 =  aworx::lib::strings::ASPreAlloc<  64>;

/// A shortcut to \ref aworx::lib::strings::ASPreAlloc "ASPreAlloc" providing an internal preallocated buffer of size 128.
using String128=  aworx::lib::strings::ASPreAlloc< 128>;

/// A shortcut to \ref aworx::lib::strings::ASPreAlloc "ASPreAlloc" providing an internal preallocated buffer of size 256.
using String256=  aworx::lib::strings::ASPreAlloc< 256>;

/// A shortcut to \ref aworx::lib::strings::ASPreAlloc "ASPreAlloc" providing an internal preallocated buffer of size 512.
using String512=  aworx::lib::strings::ASPreAlloc< 512>;

/// A shortcut to \ref aworx::lib::strings::ASPreAlloc "ASPreAlloc" providing an internal preallocated buffer of size 1024.
using String1K =  aworx::lib::strings::ASPreAlloc<1024>;

/// A shortcut to \ref aworx::lib::strings::ASPreAlloc "ASPreAlloc" providing an internal preallocated buffer of size 2048.
using String2K =  aworx::lib::strings::ASPreAlloc<2048>;

/// A shortcut to \ref aworx::lib::strings::ASPreAlloc "ASPreAlloc" providing an internal preallocated buffer of size 4096.
using String4K =  aworx::lib::strings::ASPreAlloc<4096>;


//  ###### NullString, EmptyString ######
/**
 * A constant \e nulled ALib string.
 * E.g. useful to provide as parameter to methods or to use as default value for method
 * parameters.
 * @return A constant \e nulled ALib string.
 */
constexpr String   NullString;

/**
 * A constant empty (but not \e nulled) ALib string
 * E.g. useful to provide as parameter to methods or to use as default value for method
 * parameters.
 * @return A constant empty (but not \e nulled) ALib string.
 */
constexpr String   EmptyString("", 0);

} // namespace aworx

#endif // HPP_NAMESPACE_AWORX
