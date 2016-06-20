# #################################################################################################
#  CMakeALoxBase.txt - cmake file for projects using ALib/ALox
#
#  (c) 2016 A-Worx GmbH, Germany
#  Published under MIT License (Open Source License, see LICENSE.txt)
#
#  Note:
#    ALox_Base.cmake will include this file automatically.
#    Still ALib features may be chosen (set) before including ALox_Base.cmake.
#
#  In custom cmake file
#    - Set cmake variable "ALIB_BASE_DIR", e.g 'set ( ALIB_BASE_DIR  ~/mylibs/ALib/ )'
#      (make sure 'src.cpp' is a subfolder of the one given)
#    - Optionally set cmake variables matching the conditional compilation symbols as listed
#      in the ALib user manual to configure ALib features, e.g.  'set( ALIB_FEAT_THREADS "OFF" )'
#    - Include this cmake script using
#      include( ${ALIB_BASE_DIR}/build/cmake.cpp/ALib_Base.cmake )
#    - Add the sources / headers to your projects (currently there is no own target defined for
#      ALib as usually ALib is included in ALox)
#      Headers: ${ALIB_INCS}
#      Sources: ${ALIB_SRCS}
#      In this case, also append compiler and linker flags to your target as defined in this file.
# #################################################################################################

# -------------------------------------------------------------------------------------------------
# initialize things
# -------------------------------------------------------------------------------------------------
    # set version
    set( ALIB_VERSION       "1604R2"     )

    if (ALIB_SRC_DIR)
        message( "ALib_Base.cmake: Already included (included twice!)" )
        return()
    endif()

    # check given base directory
    if (NOT ALIB_BASE_DIR)
        message( "ALib_Base.cmake: ALIB_BASE_DIR not set" )
        return()
    endif()

    # convert given path to absolute path
    get_filename_component(ALIB_BASE_DIR ${ALIB_BASE_DIR} ABSOLUTE)

    # check
    if (NOT EXISTS "${ALIB_BASE_DIR}/src.cpp/" )
        message( "ALib_Base.cmake: wrong ALIB_BASE_DIR given. Can't read sources" )
        return()
    endif()


    # build type defaults to "Debug"
    if ( "${CMAKE_BUILD_TYPE}" STREQUAL ""    )
        set( CMAKE_BUILD_TYPE "Debug" )
    endif()

    MESSAGE( STATUS "Build type: ${CMAKE_BUILD_TYPE}" )


# -------------------------------------------------------------------------------------------------
# source code definitions
# -------------------------------------------------------------------------------------------------

    set (              ALIB_SRC_DIR      ${ALIB_BASE_DIR}/src.cpp              )
    file( GLOB_RECURSE ALIB_INCS         ${ALIB_BASE_DIR}/src.cpp/alib/*.h*    )
    file( GLOB_RECURSE ALIB_SRCS         ${ALIB_BASE_DIR}/src.cpp/alib/*.cpp   )


# -------------------------------------------------------------------------------------------------
# Set ALib conditional compilation symbols
# -------------------------------------------------------------------------------------------------

    # Set default values for conditional compilation symbols
    if( NOT DEFINED  ALIB_DEBUG )
        if( CMAKE_BUILD_TYPE STREQUAL "Debug" )
             set( ALIB_DEBUG   "ON" )
        else()
             set( ALIB_DEBUG   "OFF" )
        endif()
    endif()

    if( NOT DEFINED  ALIB_FEAT_THREADS  )
        set( ALIB_FEAT_THREADS   "ON" )
    endif()

    if( NOT DEFINED  ALIB_DEBUG_STRINGS )
        set( ALIB_DEBUG_STRINGS  "OFF" )
    endif()

    # write compilations symbols into ${ALIB_COMPILER_SYMBOLS}
    if ( ${ALIB_DEBUG} )
        set( ALIB_COMPILER_SYMBOLS  ${ALIB_COMPILER_SYMBOLS}    "ALIB_DEBUG_ON"          )
    else()
        set( ALIB_COMPILER_SYMBOLS  ${ALIB_COMPILER_SYMBOLS}    "ALIB_DEBUG_OFF"         )
    endif()

    if ( ${ALIB_AVOID_ANALYZER_WARNINGS} )
        set( ALIB_COMPILER_SYMBOLS  ${ALIB_COMPILER_SYMBOLS}    "ALIB_AVOID_ANALYZER_WARNINGS_ON"  )
    else()
        set( ALIB_COMPILER_SYMBOLS  ${ALIB_COMPILER_SYMBOLS}    "ALIB_AVOID_ANALYZER_WARNINGS_OFF" )
    endif()

    if ( ${ALIB_FEAT_THREADS} )
        set( ALIB_COMPILER_SYMBOLS  ${ALIB_COMPILER_SYMBOLS}    "ALIB_FEAT_THREADS_ON"   )
    else()
        set( ALIB_COMPILER_SYMBOLS  ${ALIB_COMPILER_SYMBOLS}    "ALIB_FEAT_THREADS_OFF"  )
    endif()

    if ( ${ALIB_DEBUG_STRINGS} )
        set( ALIB_COMPILER_SYMBOLS  ${ALIB_COMPILER_SYMBOLS}    "ALIB_DEBUG_STRINGS_ON"  )
    else()
        set( ALIB_COMPILER_SYMBOLS  ${ALIB_COMPILER_SYMBOLS}    "ALIB_DEBUG_STRINGS_OFF" )
    endif()

    if ( ${ALIB_DEBUG_GLIB} )
        set( ALIB_COMPILER_SYMBOLS  ${ALIB_COMPILER_SYMBOLS}    "_GLIBCXX_DEBUG" )
        set( ALIB_COMPILER_SYMBOLS  ${ALIB_COMPILER_SYMBOLS}    "_GLIBCXX_DEBUG_PEDANTIC" )
        set( ALIB_COMPILER_SYMBOLS  ${ALIB_COMPILER_SYMBOLS}    "_GLIBCPP_CONCEPT_CHECKS" )
    endif()

# -------------------------------------------------------------------------------------------------
# External libraries
# -------------------------------------------------------------------------------------------------

    set( ALIB_EXTERNAL_LIBS "" )

    # multithreading
    if ( ${ALIB_FEAT_THREADS} )
#! [DOXYGEN_CMAKE_FIND_THREADS]
find_package(Threads)
set( ALIB_EXTERNAL_LIBS ${ALIB_EXTERNAL_LIBS}         ${CMAKE_THREAD_LIBS_INIT} )
#! [DOXYGEN_CMAKE_FIND_THREADS]
    endif()




# ##################################################################################################
# --------------------------------------------------------------------------------------------------
# CMake Tools
# --------------------------------------------------------------------------------------------------
# ##################################################################################################


# -------------------------------------------------------------------------------------------------
# A-Worx compiler flags (can be optionally used by projects using ALib, of-course not mandatory!)
# -------------------------------------------------------------------------------------------------
    set( AWORX_LINK_FLAGS                     " " ) #avoids the need of an if() later

    if     ( ${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU"    )
        # add -H to generate output "!/x" for use of precompiled header
        set( AWORX_COMPILE_FLAGS "-Wall -Wextra -Werror -std=c++11 -fPIC" )

        # add coverage flags to GCC
        if( ${AWORX_COVERAGE_COMPILE} )
            if     ( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU"    )
                set( AWORX_COMPILE_FLAGS "${AWORX_COMPILE_FLAGS} --coverage " )
                set( AWORX_LINK_FLAGS                           "--coverage " )
            endif()
        endif()

    #! NEVER TESTED YET !
    elseif ( ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang"  )
        set( AWORX_COMPILE_FLAGS "-Weverything" )

    #! NEVER TESTED YET !
    elseif ( ${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC"   )
        set( AWORX_COMPILE_FLAGS "/W4 /WX /EHsc" )
    endif()

# -------------------------------------------------------------------------------------------------
# CMake debugging  Uncomment a line to have CMake summarize information
# -------------------------------------------------------------------------------------------------
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



# -------------------------------------------------------------------------------------------------
# ALibCMake_DumpStatus() Writes out important CMake variables
# Taken from:  http://www.cmake.org/Wiki/CMake_Useful_Variables/Logging_Useful_Variables
# -------------------------------------------------------------------------------------------------
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
