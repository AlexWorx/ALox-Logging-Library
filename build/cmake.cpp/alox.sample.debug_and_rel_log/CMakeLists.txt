# #################################################################################################
#  CMakeLists.txt - ALox Sample: DebugAndReleaseLog
#
#  (c) 2015 A-Worx GmbH, Germany
#  Published under MIT License (Open Source License, see LICENSE.txt)
#
#  How to use:
#   1. Enter subdirectory debug and invoke:  `cmake -DCMAKE_BUILD_TYPE=Debug ..`
#   2. Enter subdirectory debug and invoke:  `cmake -DCMAKE_BUILD_TYPE=Release ..` TODO add other targets when available
#   3. Invoke `make` within any of these directories.
#   More information is found in README.md
# #################################################################################################

# -------------------------------------------------------------------------------------------------
# General
# -------------------------------------------------------------------------------------------------

    project("ALox.Sample.DebugAndReleaseLog")
    cmake_minimum_required( VERSION 3.1.0 ) ###FATAL_ERROR)

    # build type defaults to Debug
    if ( "${CMAKE_BUILD_TYPE}" STREQUAL ""    )
        set( CMAKE_BUILD_TYPE "Debug" )
    endif()

    # enable modules in project path
    set (CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/.")

    #--- CMake debugging ---
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

## -------------------------------------------------------------------------------------------------
## find libraries
## -------------------------------------------------------------------------------------------------

    # Multithreading
    find_package(Threads REQUIRED)

# -------------------------------------------------------------------------------------------------
# ALox directories and library files
# -------------------------------------------------------------------------------------------------

    # The ALox base directory (change this find to suit your project)
    set ( ALOX_BASE_DIR       ${CMAKE_SOURCE_DIR}/../../..                                 )

    # ALox include path and library file
    set ( AWXU_INC_DIR        ${ALOX_BASE_DIR}/src/cpp.aworx.util/                         )
    set ( ALOX_INC_DIR        ${ALOX_BASE_DIR}/src/cpp.alox/                               )

    set ( ALOX_LIB_DEBUG      ${ALOX_BASE_DIR}/build/cmake.cpp/alox.lib/debug/libalox.a    )
    set ( ALOX_LIB_RELEASE    ${ALOX_BASE_DIR}/build/cmake.cpp/alox.lib/release/libalox.a  )

# -------------------------------------------------------------------------------------------------
# Sample sources
# -------------------------------------------------------------------------------------------------
    set ( ALOX_SAMPLE_SOURCES  ${ALOX_BASE_DIR}/src/cpp.samples/debug_and_release_log/debug_and_release_log.cpp )

# -------------------------------------------------------------------------------------------------
# set output directory
# -------------------------------------------------------------------------------------------------

    set( EXECUTABLE_OUTPUT_PATH         ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})

# -------------------------------------------------------------------------------------------------
# set compiler specific flags
# -------------------------------------------------------------------------------------------------

    if     ( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU"    )
        # add -H to generate output "!/x" for use of precompiled header
        set( ALOX_COMPILE_FLAGS "-Wall -Wextra -Werror -std=c++11" )

    elseif ( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang"  )
        set( ALOX_COMPILE_FLAGS "-Weverything" )

    elseif ( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC"   )
        set( ALOX_COMPILE_FLAGS "/W4 /WX /EHsc" )
    endif()


# -------------------------------------------------------------------------------------------------
# Add Targets
# -------------------------------------------------------------------------------------------------

    add_executable            ( SampleDebugLogAndReleaseLog   ${ALOX_SAMPLE_SOURCES}     )

    set_target_properties     ( SampleDebugLogAndReleaseLog   PROPERTIES  COMPILE_FLAGS
                                                              ${ALOX_COMPILE_FLAGS}      )

    target_link_libraries     ( SampleDebugLogAndReleaseLog   ${CMAKE_THREAD_LIBS_INIT}  )

    target_include_directories( SampleDebugLogAndReleaseLog   PRIVATE ${AWXU_INC_DIR}   )
    target_include_directories( SampleDebugLogAndReleaseLog   PRIVATE ${ALOX_INC_DIR}  )

    # debug/release library
    if ( CMAKE_BUILD_TYPE STREQUAL "Debug" )
        target_link_libraries ( SampleDebugLogAndReleaseLog   ${ALOX_LIB_DEBUG}     )
    else()
        target_link_libraries ( SampleDebugLogAndReleaseLog   ${ALOX_LIB_RELEASE}   )
    endif()


# -------------------------------------------------------------------------------------------------
# Set preprocessor definitions for targets
# !Be sure to set same compile symbolds when compiling ALox!
# -------------------------------------------------------------------------------------------------

    ### uncomment this to use a single threaded version of AWXU/ALOX ---
    #target_compile_definitions( SampleDebugLogAndReleaseLog            PUBLIC  "AWXU_FEAT_THREADS_OFF" )

    ### uncomment this to enable caller information (source code info) for release logging
    #target_compile_definitions( SampleDebugLogAndReleaseLog  PRIVATE  "ALOX_REL_LOG_CI_ON" )

    ### uncomment this to prune release logging (Seldom useful, release logging should stay in releases)
    #target_compile_definitions( SampleDebugLogAndReleaseLog  PRIVATE  "ALOX_REL_LOG_OFF" )

    if( CMAKE_BUILD_TYPE STREQUAL "Debug" )

        ### uncomment this for extra debug code
        #target_compile_definitions( SampleDebugLogAndReleaseLog  PRIVATE  "_GLIBCXX_DEBUG" )
        #target_compile_definitions( SampleDebugLogAndReleaseLog  PRIVATE  "AWXU_DBG_ASTRING_ON" )

    endif()

# -------------------------------------------------------------------------------------------------
# End
# -------------------------------------------------------------------------------------------------

# uncomment for debug
#include( LogUsefulVariables )








