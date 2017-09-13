# #################################################################################################
#  ALib.cmake - CMake file for projects using ALib
#
#  Copyright 2017 A-Worx GmbH, Germany
#  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
#
#  Note: ALox.cmake will include this file automatically.
# #################################################################################################

# --------------------------------------------------------------------------------------------------
# set cache variables
# --------------------------------------------------------------------------------------------------
    set( ALIB_VERSION                   "1709R0"                                        CACHE STRING
         "The ALib version. Not modifiable (will be overwritten on generation!)"        FORCE )

    set( temp "${CMAKE_CURRENT_LIST_DIR}/../.." )
    get_filename_component(temp ${temp} ABSOLUTE)
    set( ALIB_BASE_DIR                  ${temp}                                         CACHE   PATH
         "The base path to ALib containing source code, project files, tools, docs, etc.")

    if( NOT DEFINED  ALIB_DEBUG )
        if( CMAKE_BUILD_TYPE STREQUAL "Debug" )
             set( ALIB_DEBUG   "ON" )
        else()
             set( ALIB_DEBUG   "OFF" )
        endif()
    endif()

    if ( CMAKE_BUILD_TYPE STREQUAL "Debug" )
        set( tmp_default_val   "On" )
    else()
        set( tmp_default_val   "Off" )
    endif()
    set( ALIB_DEBUG                     ${tmp_default_val}                              CACHE   BOOL
         "Enable/disable ALib debug code. Defaults to true in debug compilations, otherwise to false." )

    set( ALIB_DEBUG_GLIB                "Off"                                           CACHE   BOOL
         "Defaults to false. If true, compiler symbols '_GLIBCXX_DEBUG', '_GLIBCXX_DEBUG_PEDANTIC' and '_GLIBCPP_CONCEPT_CHECKS' are set." )
    set( ALIB_DEBUG_STRINGS             "Off"                                           CACHE   BOOL
         "Defaults to false. Adds consistency checks to ALib string classes. Useful when developing code to manipulate strings externally, i.e T_Apply to specializations.")

    set( ALIB_FEAT_THREADS              "On"                                            CACHE   BOOL
         "Defaults to true. If false, multi-threading support is removed from ALib. Thread/Lock classes still exist and compile but are not effective.")

    if ( ${WIN32} )
        set( tmp_default_val   "On" )
    else()
        set( tmp_default_val   "Off" )
    endif()
    set( ALIB_FEAT_SINGLETON_MAPPED     ${tmp_default_val}                              CACHE   BOOL
         "Defaults to true on Windows OS, which then selects code to implement class Singleton to work with multiple data segments, as imposed by the use of Windows DLLs.")

    set( ALIB_FEAT_BOXING_FTYPES        "On"                                            CACHE   BOOL
         "Defaults to true. If false, built-in boxing of fundamental types is switched off. Allowed to be switched off only in 'ALib Boxing' module distribution!")
    set( ALIB_FEAT_BOXING_STD_VECTOR    "On"                                            CACHE   BOOL
         "Defaults to true. If false, built-in boxing of std::vector objects (to array types) is switched off. ")


    set( ALIB_AVOID_ANALYZER_WARNINGS   "Off"                                           CACHE   BOOL
         "Defaults to false. If true, minor code modifications are made to avoid unnecessary warnings with tools like 'valgrind'.")
    set( AWORX_COVERAGE_COMPILE         "Off"                                           CACHE   BOOL
         "Defaults to false. If true, option --coverag is added to GNU compiler command line.")


    if ( $ENV{CLION_IDE} )
        set( tmp_default_val   "On" )
    else()
        set( tmp_default_val   "Off" )
    endif()
    set( ALIB_GDB_PP_SUPPRESS_CHILDREN    ${tmp_default_val}                              CACHE   BOOL
         "Defaults to false. If true, a corresponding symbol gets set in debug compilations which is detected by GDB pretty printer scripts provided with ALib/ALox.")
    set( ALIB_GDB_PP_FIND_POINTER_TYPES ${tmp_default_val}                              CACHE   BOOL
         "Defaults to false. If true, a corresponding symbol gets set in debug compilations which is detected by GDB pretty printer scripts provided with ALib/ALox.")


    # use 'cotire'? (https://github.com/sakra/cotire/)
    if ( ${ALIB_CMAKE_COTIRE_DEFAULT} )
        set( tmp_default_val   "On" )
    else()
        set( tmp_default_val   "Off" )
    endif()
    set( ALIB_CMAKE_COTIRE              ${tmp_default_val}                                  CACHE   BOOL
         "If true, CMake compilation tool 'cotire' (https://github.com/sakra/cotire/) is downloaded and may be used to speedup builds. Set variable ALIB_CMAKE_COTIRE_DEFAULT prior to invoking 'ALib.cmake' to change default cached value." )



# --------------------------------------------------------------------------------------------------
# checks
# --------------------------------------------------------------------------------------------------

    # check
    if (tmp_alib_included_marker)
        message( "ALib.cmake: Already included (included twice!)" )
        return()
    endif()
    set(tmp_alib_included_marker "1")

    # convert given path to absolute path
    get_filename_component(ALIB_BASE_DIR ${ALIB_BASE_DIR} ABSOLUTE)

    # check
    if (NOT EXISTS "${ALIB_BASE_DIR}/src.cpp/" )
        message( "ALib.cmake: wrong ALIB_BASE_DIR given. Can't read sources" )
        return()
    endif()


    # build type defaults to "Debug"
    if ( "${CMAKE_BUILD_TYPE}" STREQUAL ""    )
        set( CMAKE_BUILD_TYPE "Debug" )
    endif()

    MESSAGE( STATUS "Build type: ${CMAKE_BUILD_TYPE}" )


# --------------------------------------------------------------------------------------------------
# source code definitions
# --------------------------------------------------------------------------------------------------

    set (              ALIB_SRC_DIR      ${ALIB_BASE_DIR}/src.cpp              )
    file( GLOB_RECURSE ALIB_INCS         ${ALIB_BASE_DIR}/src.cpp/alib/*.h*    )
    file( GLOB_RECURSE ALIB_SRCS         ${ALIB_BASE_DIR}/src.cpp/alib/*.cpp   )

    if ( ${APPLE} )
        file( GLOB_RECURSE ALIB_SRCS     ${ALIB_SRCS}    ${ALIB_BASE_DIR}/src.cpp/alib/*.mm   )
    endif()

# --------------------------------------------------------------------------------------------------
# compiler symbols
# --------------------------------------------------------------------------------------------------

    if ( ${ALIB_DEBUG} )
        set( ALIB_COMPILER_SYMBOLS  ${ALIB_COMPILER_SYMBOLS}    "ALIB_DEBUG_ON"          )
    else()
        set( ALIB_COMPILER_SYMBOLS  ${ALIB_COMPILER_SYMBOLS}    "ALIB_DEBUG_OFF"         )
    endif()
    if ( ${ALIB_DEBUG_STRINGS} )
        set( ALIB_COMPILER_SYMBOLS  ${ALIB_COMPILER_SYMBOLS}    "ALIB_DEBUG_STRINGS_ON"  )
    else()
        set( ALIB_COMPILER_SYMBOLS  ${ALIB_COMPILER_SYMBOLS}    "ALIB_DEBUG_STRINGS_OFF" )
    endif()
    if ( ${ALIB_DEBUG_GLIB} )
        set( ALIB_COMPILER_SYMBOLS  ${ALIB_COMPILER_SYMBOLS}    "_GLIBCXX_DEBUG"
                                                                "_GLIBCXX_DEBUG_PEDANTIC"
                                                                "_GLIBCPP_CONCEPT_CHECKS" )
    endif()

    if ( ${ALIB_FEAT_THREADS} )
        set( ALIB_COMPILER_SYMBOLS  ${ALIB_COMPILER_SYMBOLS}    "ALIB_FEAT_THREADS_ON"   )
    else()
        set( ALIB_COMPILER_SYMBOLS  ${ALIB_COMPILER_SYMBOLS}    "ALIB_FEAT_THREADS_OFF"  )
    endif()
    if ( ${ALIB_FEAT_SINGLETON_MAPPED} )
        set( ALIB_COMPILER_SYMBOLS  ${ALIB_COMPILER_SYMBOLS}    "ALIB_FEAT_SINGLETON_MAPPED_ON"   )
    else()
        set( ALIB_COMPILER_SYMBOLS  ${ALIB_COMPILER_SYMBOLS}    "ALIB_FEAT_SINGLETON_MAPPED_OFF"  )
    endif()
    if ( ${ALIB_FEAT_BOXING_FTYPES} )
        set( ALIB_COMPILER_SYMBOLS  ${ALIB_COMPILER_SYMBOLS}    "ALIB_FEAT_BOXING_FTYPES_ON"   )
    else()
        set( ALIB_COMPILER_SYMBOLS  ${ALIB_COMPILER_SYMBOLS}    "ALIB_FEAT_BOXING_FTYPES_OFF"  )
    endif()
    if ( ${ALIB_FEAT_BOXING_STD_VECTOR} )
        set( ALIB_COMPILER_SYMBOLS  ${ALIB_COMPILER_SYMBOLS}    "ALIB_FEAT_BOXING_STD_VECTOR_ON"   )
    else()
        set( ALIB_COMPILER_SYMBOLS  ${ALIB_COMPILER_SYMBOLS}    "ALIB_FEAT_BOXING_STD_VECTOR_OFF"  )
    endif()


    if ( ${ALIB_AVOID_ANALYZER_WARNINGS} )
        set( ALIB_COMPILER_SYMBOLS  ${ALIB_COMPILER_SYMBOLS}    "ALIB_AVOID_ANALYZER_WARNINGS_ON"  )
    else()
        set( ALIB_COMPILER_SYMBOLS  ${ALIB_COMPILER_SYMBOLS}    "ALIB_AVOID_ANALYZER_WARNINGS_OFF" )
    endif()

    if ( ${ALIB_GDB_PP_SUPPRESS_CHILDREN} )
        set( ALIB_COMPILER_SYMBOLS  ${ALIB_COMPILER_SYMBOLS}    "ALIB_GDB_PP_SUPPRESS_CHILDREN"  )
    endif()
    if ( ${ALIB_GDB_PP_FIND_POINTER_TYPES} )
        set( ALIB_COMPILER_SYMBOLS  ${ALIB_COMPILER_SYMBOLS}    "ALIB_GDB_PP_FIND_POINTER_TYPES"  )
    endif()



# --------------------------------------------------------------------------------------------------
# External libraries
# --------------------------------------------------------------------------------------------------

    set( ALIB_EXTERNAL_LIBS "" )

    # multithreading
    if ( ${ALIB_FEAT_THREADS} )

#! [DOXYGEN_CMAKE_FIND_THREADS]
find_package(Threads)
set( ALIB_EXTERNAL_LIBS ${ALIB_EXTERNAL_LIBS}         ${CMAKE_THREAD_LIBS_INIT} )
#! [DOXYGEN_CMAKE_FIND_THREADS]

    endif()

    if(APPLE)
        SET(ALIB_EXTERNAL_LIBS "${ALIB_EXTERNAL_LIBS} -framework Foundation")
    endif()



# --------------------------------------------------------------------------------------------------
# A-Worx compiler flags (can be optionally used by projects using ALib, of-course not mandatory!)
# --------------------------------------------------------------------------------------------------
    set( AWORX_LINK_FLAGS                     " " ) #avoids the need of an if() later

    if     ( ${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU"    )
        # add -H to generate output "!/x" for use of precompiled header
        set( AWORX_COMPILE_FLAGS "-Wall -Wextra -Werror -std=c++11 -fPIC" )

        # add coverage flags to GCC
        if( ${AWORX_COVERAGE_COMPILE} )
            set( AWORX_COMPILE_FLAGS "${AWORX_COMPILE_FLAGS} --coverage " )
            set( AWORX_LINK_FLAGS                           "--coverage " )
        endif()

    # Clang: We are using -Weverything, although this is not recommended. We think it should be
    #        recommmended. ALib for example does not use old-style casts and explicitly cast each
    #        and every type change! The benefit for ALib users is that ALib code can be used in very
    #        strict build environmnets without using special warning flags.
    #        Of-course, some very obvious things like C++98 compatibility warnings have to be
    #        removed explicitly:
    elseif ( ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang"     )
        set( AWORX_COMPILE_FLAGS "-std=c++11 -Weverything" )
        set( AWORX_COMPILE_FLAGS "${AWORX_COMPILE_FLAGS} -Wno-c++98-compat"                  )
        set( AWORX_COMPILE_FLAGS "${AWORX_COMPILE_FLAGS} -Wno-c++98-compat-pedantic"         )
        set( AWORX_COMPILE_FLAGS "${AWORX_COMPILE_FLAGS} -Wno-global-constructors"           )
        set( AWORX_COMPILE_FLAGS "${AWORX_COMPILE_FLAGS} -Wno-exit-time-destructors"         )
        set( AWORX_COMPILE_FLAGS "${AWORX_COMPILE_FLAGS} -Wno-padded"                        )
        set( AWORX_COMPILE_FLAGS "${AWORX_COMPILE_FLAGS} -Wno-weak-vtables"                  )
        set( AWORX_COMPILE_FLAGS "${AWORX_COMPILE_FLAGS} -Wno-documentation-unknown-command" )

        if ( ${ALIB_CMAKE_COTIRE} )
            # needs to be off of due to "unity builds" of cotire
            set( AWORX_COMPILE_FLAGS "${AWORX_COMPILE_FLAGS} -Wno-header-hygiene"                   )

            # Maybe a 'bug' in cotire. Was discussed and closed. Might be removed in the future
            # However: If removed, 'often' things still work, only sometimes compiler complains that
            #          trigraph settings are different in precompiled header and actual source
            set( AWORX_COMPILE_FLAGS "${AWORX_COMPILE_FLAGS} -trigraphs"                    )
        endif()



    #! NEVER TESTED YET !
    elseif ( ${CMAKE_CXX_COMPILER_ID} STREQUAL "Intel"  )
        set( AWORX_COMPILE_FLAGS "" )

    #! NEVER TESTED YET !
    elseif ( ${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC"   )
        set( AWORX_COMPILE_FLAGS "/W4 /WX /EHsc" )
    endif()

# ##################################################################################################
# --------------------------------------------------------------------------------------------------
# CMake Tools
# --------------------------------------------------------------------------------------------------
# ##################################################################################################

# -------------------------------------------------------------------------------------------------
# Precompiled headers and unity build with 'cotire' CMake script.
#    More Info at: https://github.com/sakra/cotire/
#
# Note:
#   To enable/disable change CMake cache variable ALIB_CMAKE_COTIRE.
#   To change the default value for this variable (on clean cmake builts), set non-cached CMake
#   variable ALIB_CMAKE_COTIRE_DEFAULT prior to invoking this script.
# -------------------------------------------------------------------------------------------------

# download cotire (once)
if ( ${ALIB_CMAKE_COTIRE} )

    message( STATUS  "Setting up 'cotire' for ALox library projects" )

    set( cotireFileName ${CMAKE_CURRENT_LIST_DIR}/cotire.cmake )
    if( NOT EXISTS  ${cotireFileName} )
        message( STATUS "  Downloading ${cotireFileName} from ${cotireFileUrl} ..." )
        file( DOWNLOAD "https://raw.githubusercontent.com/sakra/cotire/master/CMake/cotire.cmake" ${cotireFileName} )

        if( NOT EXISTS  ${cotireFileName} )
            message( "  ...Error: Download of 'cotire' failed. Continuing without cotire." )
            set( ALIB_CMAKE_COTIRE "Off" )
        else()
            message( STATUS "  ...success." )
        endif()
    endif()

    if ( ${ALIB_CMAKE_COTIRE} )
        include(${cotireFileName})
    endif()

endif()


# --------------------------------------------------------------------------------------------------
# CMake debugging  Uncomment a line to have CMake summarize information
# --------------------------------------------------------------------------------------------------
#set(CMAKE_DEBUG_TARGET_PROPERTIES  ${CMAKE_DEBUG_TARGET_PROPERTIES} INCLUDE_DIRECTORIES )
#set(CMAKE_DEBUG_TARGET_PROPERTIES  ${CMAKE_DEBUG_TARGET_PROPERTIES} SOURCES )
#set(CMAKE_DEBUG_TARGET_PROPERTIES  ${CMAKE_DEBUG_TARGET_PROPERTIES} COMPILE_DEFINITIONS )
#set(CMAKE_DEBUG_TARGET_PROPERTIES  ${CMAKE_DEBUG_TARGET_PROPERTIES} COMPILE_OPTIONS )
#set(CMAKE_DEBUG_TARGET_PROPERTIES  ${CMAKE_DEBUG_TARGET_PROPERTIES} COMPILE_FEATURES )
#set(CMAKE_DEBUG_TARGET_PROPERTIES  ${CMAKE_DEBUG_TARGET_PROPERTIES} AUTOUIC_OPTIONS )
#set(CMAKE_DEBUG_TARGET_PROPERTIES  ${CMAKE_DEBUG_TARGET_PROPERTIES} POSITION_INDEPENDENT_CODE )
#set(CMAKE_DEBUG_TARGET_PROPERTIES  ${CMAKE_DEBUG_TARGET_PROPERTIES} CONTAINER_SIZE_REQUIRED )
#set(CMAKE_DEBUG_TARGET_PROPERTIES  ${CMAKE_DEBUG_TARGET_PROPERTIES} LIB_VERSION )

#set(CMAKE_VERBOSE_MAKEFILE ON)


# --------------------------------------------------------------------------------------------------
# ALibCMake_DumpStatus() Writes out important CMake variables
# Taken from:  http://www.cmake.org/Wiki/CMake_Useful_Variables/Logging_Useful_Variables
# --------------------------------------------------------------------------------------------------
function (ALibCMake_DumpStatus)

    # /*	C++ comment style not allowed	*/
    MESSAGE( STATUS "\nALibCMake_DumpStatus:" )


    # if you are building in-source, this is the same as CMAKE_SOURCE_DIR, otherwise
    # this is the top level directory of your build tree
    MESSAGE( STATUS "  CMAKE_BINARY_DIR:                  " ${CMAKE_BINARY_DIR} )

    # if you are building in-source, this is the same as CMAKE_CURRENT_SOURCE_DIR, otherwise this
    # is the directory where the compiled or generated files from the current CMakeLists.txt will go to
    MESSAGE( STATUS "  CMAKE_CURRENT_BINARY_DIR:          " ${CMAKE_CURRENT_BINARY_DIR} )

    # this is the directory, from which cmake was started, i.e. the top level source directory
    MESSAGE( STATUS "  CMAKE_SOURCE_DIR:                  " ${CMAKE_SOURCE_DIR} )

    # this is the directory where the currently processed CMakeLists.txt is located in
    MESSAGE( STATUS "  CMAKE_CURRENT_SOURCE_DIR:          " ${CMAKE_CURRENT_SOURCE_DIR} )

    # contains the full path to the top level directory of your build tree
    MESSAGE( STATUS "  PROJECT_BINARY_DIR:                " ${PROJECT_BINARY_DIR} )

    # contains the full path to the root of your project source directory,
    # i.e. to the nearest directory where CMakeLists.txt contains the PROJECT() command
    MESSAGE( STATUS "  PROJECT_SOURCE_DIR:                " ${PROJECT_SOURCE_DIR} )

    # set this variable to specify a common place where CMake should put all executable files
    # (instead of CMAKE_CURRENT_BINARY_DIR)
    MESSAGE( STATUS "  EXECUTABLE_OUTPUT_PATH:            " ${EXECUTABLE_OUTPUT_PATH} )

    # set this variable to specify a common place where CMake should put all libraries
    # (instead of CMAKE_CURRENT_BINARY_DIR)
    MESSAGE( STATUS "  LIBRARY_OUTPUT_PATH:               " ${LIBRARY_OUTPUT_PATH} )

    # tell CMake to search first in directories listed in CMAKE_MODULE_PATH
    # when you use FIND_PACKAGE() or INCLUDE()
    MESSAGE( STATUS "  CMAKE_MODULE_PATH:                 " ${CMAKE_MODULE_PATH} )

    # this is the complete path of the cmake which runs currently (e.g. /usr/local/bin/cmake)
    MESSAGE( STATUS "  CMAKE_COMMAND:                     " ${CMAKE_COMMAND} )

    # this is the CMake installation directory
    MESSAGE( STATUS "  CMAKE_ROOT:                        " ${CMAKE_ROOT} )

    # this is the filename including the complete path of the file where this variable is used.
    MESSAGE( STATUS "  CMAKE_CURRENT_LIST_FILE:           " ${CMAKE_CURRENT_LIST_FILE} )

    # this is linenumber where the variable is used
    MESSAGE( STATUS "  CMAKE_CURRENT_LIST_LINE:           " ${CMAKE_CURRENT_LIST_LINE} )

    # this is used when searching for include files e.g. using the FIND_PATH() command.
    MESSAGE( STATUS "  CMAKE_INCLUDE_PATH:                " ${CMAKE_INCLUDE_PATH} )

    # this is used when searching for libraries e.g. using the FIND_LIBRARY() command.
    MESSAGE( STATUS "  CMAKE_LIBRARY_PATH:                " ${CMAKE_LIBRARY_PATH} )

    # the complete system name, e.g. "Linux-2.4.22", "FreeBSD-5.4-RELEASE" or "Windows 5.1"
    MESSAGE( STATUS "  CMAKE_SYSTEM:                      " ${CMAKE_SYSTEM} )

    # the short system name, e.g. "Linux", "FreeBSD" or "Windows"
    MESSAGE( STATUS "  CMAKE_SYSTEM_NAME:                 " ${CMAKE_SYSTEM_NAME} )

    # only the version part of CMAKE_SYSTEM
    MESSAGE( STATUS "  CMAKE_SYSTEM_VERSION:              " ${CMAKE_SYSTEM_VERSION} )

    # the processor name (e.g. "Intel(R) Pentium(R) M processor 2.00GHz")
    MESSAGE( STATUS "  CMAKE_SYSTEM_PROCESSOR:            " ${CMAKE_SYSTEM_PROCESSOR} )

    # is TRUE on all UNIX-like OS's, including Apple OS X and CygWin
    MESSAGE( STATUS "  UNIX:                              " ${UNIX} )

    # is TRUE on Windows, including CygWin
    MESSAGE( STATUS "  WIN32:                             " ${WIN32} )

    # is TRUE on Apple OS X
    MESSAGE( STATUS "  APPLE:                             " ${APPLE} )

    # is TRUE when using the MinGW compiler in Windows
    MESSAGE( STATUS "  MINGW:                             " ${MINGW} )

    # is TRUE on Windows when using the CygWin version of cmake
    MESSAGE( STATUS "  CYGWIN:                            " ${CYGWIN} )

    # is TRUE on Windows when using a Borland compiler
    MESSAGE( STATUS "  BORLAND:                           " ${BORLAND} )

    # Microsoft compiler
    MESSAGE( STATUS "  MSVC:                              " ${MSVC} )
    MESSAGE( STATUS "  MSVC_IDE:                          " ${MSVC_IDE} )
    MESSAGE( STATUS "  MSVC60:                            " ${MSVC60} )
    MESSAGE( STATUS "  MSVC70:                            " ${MSVC70} )
    MESSAGE( STATUS "  MSVC71:                            " ${MSVC71} )
    MESSAGE( STATUS "  MSVC80:                            " ${MSVC80} )
    MESSAGE( STATUS "  CMAKE_COMPILER_2005:               " ${CMAKE_COMPILER_2005} )


    # set this to true if you don't want to rebuild the object files if the rules have changed,
    # but not the actual source files or headers (e.g. if you changed the some compiler switches)
    MESSAGE( STATUS "  CMAKE_SKIP_RULE_DEPENDENCY:        " ${CMAKE_SKIP_RULE_DEPENDENCY} )

    # since CMake 2.1 the install rule depends on all, i.e. everything will be built before installing.
    # If you don't like this, set this one to true.
    MESSAGE( STATUS "  CMAKE_SKIP_INSTALL_ALL_DEPENDENCY: " ${CMAKE_SKIP_INSTALL_ALL_DEPENDENCY} )

    # If set, runtime paths are not added when using shared libraries. Default it is set to OFF
    MESSAGE( STATUS "  CMAKE_SKIP_RPATH:                  " ${CMAKE_SKIP_RPATH} )

    # set this to true if you are using makefiles and want to see the full compile and link
    # commands instead of only the shortened ones
    MESSAGE( STATUS "  CMAKE_VERBOSE_MAKEFILE:            " ${CMAKE_VERBOSE_MAKEFILE} )

    # this will cause CMake to not put in the rules that re-run CMake. This might be useful if
    # you want to use the generated build files on another machine.
    MESSAGE( STATUS "  CMAKE_SUPPRESS_REGENERATION:       " ${CMAKE_SUPPRESS_REGENERATION} )


    # A simple way to get switches to the compiler is to use ADD_DEFINITIONS().
    # But there are also two variables exactly for this purpose:

    # the compiler flags for compiling C sources
    MESSAGE( STATUS "  CMAKE_C_FLAGS:                     " ${CMAKE_C_FLAGS} )

    # the compiler flags for compiling C++ sources
    MESSAGE( STATUS "  CMAKE_CXX_FLAGS:                   " ${CMAKE_CXX_FLAGS} )


    # Choose the type of build.  Example: SET(CMAKE_BUILD_TYPE Debug)
    MESSAGE( STATUS "  CMAKE_BUILD_TYPE:                  " ${CMAKE_BUILD_TYPE} )

    # if this is set to ON, then all libraries are built as shared libraries by default.
    MESSAGE( STATUS "  BUILD_SHARED_LIBS:                 " ${BUILD_SHARED_LIBS} )

    # the compiler used for C files
    MESSAGE( STATUS "  CMAKE_C_COMPILER:                  " ${CMAKE_C_COMPILER} )

    # the compiler used for C++ files
    MESSAGE( STATUS "  CMAKE_CXX_COMPILER:                " ${CMAKE_CXX_COMPILER} )

    # if the compiler is a variant of gcc, this should be set to 1
    MESSAGE( STATUS "  CMAKE_COMPILER_IS_GNUCC:           " ${CMAKE_COMPILER_IS_GNUCC} )

    # if the compiler is a variant of g++, this should be set to 1
    MESSAGE( STATUS "  CMAKE_COMPILER_IS_GNUCXX :         " ${CMAKE_COMPILER_IS_GNUCXX} )

    # the tools for creating libraries
    MESSAGE( STATUS "  CMAKE_AR:                          " ${CMAKE_AR} )
    MESSAGE( STATUS "  CMAKE_RANLIB:                      " ${CMAKE_RANLIB} )

    #
    MESSAGE( STATUS "  : " ${} )
endfunction()

