// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
#include "alib/alib.hpp"


#if ALIB_DEBUG
    #include <iostream>
    #include <cassert>

    #if defined( _WIN32 )
        #include <string>
    #endif
#endif


// #################################################################################################
// Debug functions
// #################################################################################################
#if ALIB_DEBUG

namespace aworx { namespace lib { namespace debug {


void (*DbgSimpleALibMsg_Plugin)(const char* file, int line, const char* method, int type, int qtyMsgs, const char** msgs)     =nullptr;


void DbgSimpleALibMsg( const char* file, int line, const char* method,
                       int type, const char* msg1, const char* msg2, const char* msg3, const char* msg4 )
{

    int         qtyMsgs=  msg2 != nullptr ? (msg3 != nullptr ? (msg4 != nullptr ? 4 : 3) : 2) : 1;
    const char* msgs[4]= { msg1, msg2, msg3, msg4 };

    if( DbgSimpleALibMsg_Plugin )
    {
        DbgSimpleALibMsg_Plugin( file, line, method, type, qtyMsgs, msgs  );
        return;
    }

    // internal implementation
    for (int i= 0; i< qtyMsgs; i++ )
        std::cout << msgs[i];
    std::cout << std::endl;
    assert(type);
}

void DbgSimpleALibMsg( const char* file, int line, const char* method,
                       int type, const char* msg, int intVal )
{

    std::string sIntVal= std::to_string( intVal );

    if( DbgSimpleALibMsg_Plugin )
    {
        const char* msgs[2]= { msg, sIntVal.c_str() };
        DbgSimpleALibMsg_Plugin( file, line, method, type, 2, msgs  );
        return;
    }

    // internal implementation
    std::cout << msg << sIntVal << std::endl;
    assert(type);
}

}}}// namespace aworx::lib::lang

#endif

// #################################################################################################
// Set 'flags' for pretty printers by defining global symbols.
// See file $ALOX_LIB_PATH/ALox/tools/ideplugins/gdb/alibpp.py for more information
// #################################################################################################
#if ALIB_DEBUG
    #if defined(DOX_PARSER)
        #define ALIB_GDB_PP_SUPPRESS_CHILDREN
        #define ALIB_GDB_PP_FIND_POINTER_TYPES
    #endif

    /**
     * @addtogroup GrpALibCompilerSymbols
     * @{ \def  ALIB_GDB_PP_SUPPRESS_CHILDREN
     *  This symbol may be passed to the compiler to control the behavior of pretty printers scripts
     *  for GDB. If defined, external symbol \e "ALIB_PP_SUPPRESS_CHILDREN"
     *  is created in debug compilations. This will be detected by pretty printer python script
     *  provided with ALib/ALox.
     *
     *  \see Documentation of pretty printers in tools section of \b %ALib documentation.
     * @}
     */

    #if  defined(ALIB_GDB_PP_SUPPRESS_CHILDREN)
        extern int ALIB_PRETTY_PRINTERS_SUPPRESS_CHILDREN;
               int ALIB_PRETTY_PRINTERS_SUPPRESS_CHILDREN;
    #endif

    /**
     * @addtogroup GrpALibCompilerSymbols
     * @{ \def  ALIB_GDB_PP_FIND_POINTER_TYPES
     *  This symbol may be passed to the compiler to control the behavior of pretty printers scripts
     *  for GDB. If defined, external symbol \e "ALIB_PP_FIND_POINTER_TYPES"
     *  is created in debug compilations. This will be detected by pretty printer python script
     *  provided with ALib/ALox.
     *
     *  \see Documentation of pretty printers in tools section of \b %ALib documentation.
     * @}
     */

    #if  defined(ALIB_GDB_PP_FIND_POINTER_TYPES)
        extern int ALIB_PRETTY_PRINTERS_FIND_POINTER_TYPES;
               int ALIB_PRETTY_PRINTERS_FIND_POINTER_TYPES;
    #endif

#endif


// #################################################################################################
// static assertions for the platform
// #################################################################################################

static_assert(         sizeof(aworx::integer )       ==  sizeof(aworx::uinteger  ),         "Error in ALib type definitions" );
static_assert(         sizeof(aworx::integer )       ==         sizeof(std::size_t    ),         "Error in ALib type definitions" );
static_assert(std::is_signed< aworx::integer>::value == std::is_signed<std::ptrdiff_t >::value,  "Error in ALib type definitions" );
static_assert(std::is_signed< aworx::integer>::value != std::is_signed<std::size_t    >::value,  "Error in ALib type definitions" );
static_assert(std::is_signed<aworx::uinteger>::value == std::is_signed<std::size_t    >::value,  "Error in ALib type definitions" );
static_assert(std::is_signed<aworx::uinteger>::value != std::is_signed<std::ptrdiff_t >::value,  "Error in ALib type definitions" );


// #################################################################################################
// Namespace documentation aworx and aworx::lib
// #################################################################################################

/**
 * Namespace
 *  - \c aworx
 *
 *  is the outer namespace for C++ software published by A-Worx GmbH, Germany. <p>
 * While the Java language strongly proposes to use the complete 'reverse domain' name
 * and therefore Java code published by A-Worx GmbH resides in namespace
 * - \c com.aworx,
 *
 * for C# the prefix \b 'com.' is changed to \b 'cs.'. This way, the C# version of this namespace is
 * - \c cs.aworx
 *
 * This distinction is needed to avoid ambiguities within the documentation system
 * ([Doxygen](http://www.stack.nl/~dimitri/doxygen)) which is used in scenarios of mixed
 * documentation of similar code written in different languages.
 *
 * Besides nested namespaces, there are no functions or types defined in this namespace.
 * The C++ language, has one important exception to this rule, as described in the next paragraph.
 *
 *  \anchor CPP_AWORX_NS_SHORTCUTS
 * <b>Type Shortcuts of C++ Namespace aworx</b><p>
 * ALib and other software of A-Worx GmbH, \e \"mirror\" important types into <b>namespace %aworx</b>
 * with \c using statements. For example, by having
 *
 *      using  String =  aworx::lib::strings::String;
 *               1
 * stated within namespace \c %aworx but in the header file of class String (!), this class is
 * made available with just adding
 *
 *      using aworx;
 *
 * to a source file. This is convenient when ALib is \e used in 3rd party code outside of the
 * \c %aworx namespace, and also for the classes of ALib itself and for 'sibling'
 * libraries that reside next to each other underneath namespace \c %aworx.<br>
 * For example logging library \b %ALox with namespace \c %aworx::lox. Such classes may refer to all
 * mirrored sibling-classes already within the header files without providing any namespace,
 * because in C++, code that is located inside a namespace 'sees' all types defined in parent
 * namespaces.<br>
 * Therefore, header files become clear and simple without using full qualified type names.
 *
 * In contrast to this, C++ sources that are \"\e using\" a sub-namespace do \b not automatically
 * 'see' classes in parent namespaces of such used namespace.
 * This is an important difference and a great design decision of the C++ language!
 * As a conclusion, a user of libraries (types) residing
 * in sub-namespaces of \b %aworx, has different choices on selecting namespaces with \c using statement:
 * - <c>using namespace %aworx; // see all types as 'mirror' types </c>
 * - <c>using namespace %aworx::abc::xyz; // see only types of distinct namespace </c>
 * - or: do not 'use' any namespace but select A-Worx types by full qualified name.
 *
 * Unfortunately, with template classes this mechanism has a limit. It is not allowed to use the
 * same type name for the 'mirrored' classes. Therefore, for example class
 * \ref aworx::lib::strings::PreallocatedString "PreallocatedString<int TCapacity>" gets mirrored to
 * \b %PAString as follows:
 *
 *      template<aworx::lib::lang::integer TCapacity>
 *      using PAString =   aworx::lib::strings::PreallocatedString<TCapacity>
 *
 * To summarize, the effect of mirroring the main interface classes is as follows:
 * - Inside header files of sub-namespaces (and their sub-namespaces) of \e aworx, e.g. \e aworx::lib and \e aworx::lox,
 *   these names are visible and used.
 * - Inside external header files, they are not visible but might be quite shortly accessed
 *   using namespace prefix <b>aworx::</b>.
 * - Inside external cpp-files, if no collision with other libraries or local classes exist,
 *   all types of all A-Worx libraries used, can be made visible with one single using statement for
 *   namespace \b aworx. Should collisions occur, then still selected classes of A-Worx libraries
 *   that do not collide can be made visible by choosing the complete namespace name for the
 *   \e using statement.
 * - The mirrored class names appear only in this <b>namespace aworx</b>, if the corresponding
 *   header file of the original class is included in a compilation unit.
 *
 * <b>Domain-Specific Constants and Variables</b><p>
 * Similar to the concept of mirroring important interface classes into this <b>namespace aworx</b>
 * (which is described in the previous paragraph), it is also agreed to place important global
 * constants here. The impact and benefits are quite the same.<br>
 * As a sample, see
 * \ref aworx::DirectorySeparator which appears in this namespace as soon as header
 * "alib/system/directory.hpp" is included.
 *
 */
namespace aworx {


/**
 * <b>Introduction:</b><br>
 * This is the C++ base namespace for \b %ALib - a set of core utility classes developed by
 * A-Worx GmbH, Germany, published under <em>Boost Software License</em>.
 *
 * Besides C++, this library is available in C# and Java, with language specific
 * differences. The design goals are:
 * - Be small, efficient and easy to understand
 * - Keep C++, C# and Java versions similar and mimic functionality of core classes of all
 *   three languages whenever this is appropriate, with the intent to keep source code building
 *   upon the library to a certain degree similar and exchangeable.
 * - Be non-intrusive in the sense that the use of ALib in projects (maybe just because
 *   some minor functionality is wanted) does not force to show up many ALib types.
 *
 *  \anchor alib_namespace_organization_of_code
 * <b>Organization of Code:</b><br>
 * The C++ version is the most complex language version of \b %ALib. The reason is that Java and
 * C# languages are equipped with many built-in classes that do not need a replacement.
 * This comfortable situation is different with C++. Therefore, <b>"ALib for C++"</b> has a
 * much more comprehensive mandate and it is more likely that <b>%ALib for C++</b> is used in
 * single language (hence C++ only) projects. In other words, the
 * Java and C# versions of ALib are especially useful, if multi-language software is written
 * (e.g. a phone device app, available as a set of different, native incarnations)
 * to reach a certain degree of code compatibility.
 *
 * Currently, the full version of \b %ALib is \b not available as a "stand-alone library".
 * With GitHub project
 * - [ALox Logging Library](http://alexworx.github.io/ALox-Logging-Library/index.html),
 *
 * \b %ALib is distributed in a bundle with \b %ALox, a library for debug- and release logging,
 * again available in C++, C# and Java.
 *
 * However, on the other hand, subsets of \b %ALib are available with so called <b>ALib Modules</b>.
 * Modules can be used separately from the rest of the library and for a users convenience they are
 * exposed in separated \b GitHub projects.
 *
 * The following portions of \b %ALib are extracted and maintained as modules:
 * - [ALib for C++ Singleton](https://github.com/AlexWorx/ALib-Singleton)
 * - [ALib for C++ %Boxing](https://github.com/AlexWorx/ALib-Boxing)
 * - [ALib for C++ Strings](https://github.com/AlexWorx/ALib-Strings)
 * - [ALib for C++ %Boxing & Strings](https://github.com/AlexWorx/ALib-Boxing-And-Strings)
 * - [ALib for C++ %Configuration](https://github.com/AlexWorx/ALib-Configuration)
 *
 * The rational for this deployment strategy (to have either a subset of \b %ALib or a bundle with \b %ALox )
 * is that we anticipate users to either want to use just a specific \b %ALib innovation, or just
 * all of it. In the latter case, \b ALox is a perfect extension to what \b %ALib offers.<br>
 *
 * \note
 *   In the rare case that full \b %ALib is wanted without \b %ALox, then it is quite simple to
 *   extract full \b %ALib from the \b %ALox project, because
 *   - The sources are separated in different folders.
 *   - There are no dependencies from \b %ALib sources to \b %ALox.
 *   - Two separated CMake build files for \b %ALib and \b %ALox exists.
 *
 *
 * <b>Usage</b><br>
 * Regardless of using full \b %ALib or using an <b>ALib Module</b>, header file \ref alib/alib.hpp
 * is to be to be included prior to including necessary specific other headers.
 * The distribution-specific header file \c alib/distribution.hpp
 * will select the right (available) module header files.
 * In the case of modules, source files have to be \b 'manually' added to the build process
 * (either to a library or directly to a main executable) as demonstrated in the samples deployed
 * with the modules.
 *
 * Furthermore, some initialization method specific to the <b>ALib Module</b>
 * in question might be needed to be invoked during bootstrapping. With the complete distribution
 * of \b %ALib, such initialization is performed in aggregated method
 * \ref aworx::lib::ALIB::Init "ALIB::Init".
 *
 * \note
 *   When - as recommended - the full version of ALib is used bundled with ALox, then the
 *   correct header file and initialization method are
 *   \ref alox/alox.hpp and
 *   \ref aworx::lox::ALox::Init "ALox::Init".
 *
 *
 * <b>Platforms/Toolchains:</b><br>
 * As of today, <b>%ALib for C++</b> is compiled and tested under the following platforms and
 * compiler toolchains:
 * - GNU/Linux, GNU C++ 11, 32-Bit / 64-Bit
 * - GNU/Linux, Clang C++ 11, 32-Bit / 64-Bit
 * - Windows 10, Microsoft Compiler (MSVC) C++11, 32-Bit / 64-Bit
 * - macOS 10, 64-Bit
 *
 * Adoptions to other platforms should be implementable with limited efforts. All relevant
 * code which selects platform/toolchain specific libraries, intrinsics, etc., will expose a
 * preprocessor error if section fails due to unknown environment.
 * This allows to quickly insert the right platform/toolchain specific code at these places.
 */
namespace lib { }}



