# #################################################################################################
#  CMakeLists.txt - ALox Tools: DoxygenGraphTemplateInstanceRemover
#
#  Copyright 2015 A-Worx GmbH, Germany
#  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
#
#  How to use:
#   1. Enter subdirectory 'debug'   and invoke:  `cmake ..`
#   2. Enter subdirectory 'release' and invoke:  `cmake -DCMAKE_BUILD_TYPE=Release ..`
#   3. Invoke `make` within any of these directories.
#   More information is found in ALox documentation.
# ##################################################################################################

# -------------------------------------------------------------------------------------------------
# Prior to setting CMake project
# -------------------------------------------------------------------------------------------------

    # uncomment to force a certain compiler (delete temporary output folder on change)

    #set(CMAKE_C_COMPILER    "/usr/bin/clang")
    #set(CMAKE_CXX_COMPILER  "/usr/bin/clang++")

    #set(CMAKE_C_COMPILER    "/usr/bin/gcc")
    #set(CMAKE_CXX_COMPILER  "/usr/bin/g++")

    # uncomment to force cotire on clean cmake built
    #set( ALIB_CMAKE_COTIRE_DEFAULT   "On" )

# -------------------------------------------------------------------------------------------------
# General
# -------------------------------------------------------------------------------------------------

    project( "DoxygenGraphTemplateInstanceRemover" )
    cmake_minimum_required(VERSION 2.8)

    # this defaults to a release version!
    if ( "${CMAKE_BUILD_TYPE}" STREQUAL ""    )
        MESSAGE( STATUS "Default build type 'Release' chosen" )
        set( CMAKE_BUILD_TYPE "Release" )
    endif()

## -------------------------------------------------------------------------------------------------
## find libraries
## -------------------------------------------------------------------------------------------------

    # Multithreading
    find_package(Threads REQUIRED)

## -------------------------------------------------------------------------------------------------
## include ALib/ALox base cmake file
## -------------------------------------------------------------------------------------------------

    include( ../../build/cmake.cpp/ALox.cmake )


# -------------------------------------------------------------------------------------------------
# sources
# -------------------------------------------------------------------------------------------------
aux_source_directory(. SRC_LIST)


# -------------------------------------------------------------------------------------------------
# The target
# -------------------------------------------------------------------------------------------------

    add_executable( dot ${SRC_LIST})

    set_target_properties     ( dot   PROPERTIES  COMPILE_FLAGS     ${AWORX_COMPILE_FLAGS}    )
    set_target_properties     ( dot   PROPERTIES  LINK_FLAGS        ${AWORX_LINK_FLAGS}       )
    target_link_libraries     ( dot   ${ALIB_EXTERNAL_LIBS}
                                      ${ALOX_EXTERNAL_LIBS}   )

#! [DOXYGEN_CMAKE_COTIRE_TARGET]
# link against unity-built version of library in case of cotire
if( ${ALIB_CMAKE_COTIRE} )
    target_link_libraries     ( dot   ALox_StaticLib_unity  )
else()
    target_link_libraries     ( dot   ALox_StaticLib        )
endif()
#! [DOXYGEN_CMAKE_COTIRE_TARGET]

    set( EXECUTABLE_OUTPUT_PATH       ${ALOX_BASE_DIR}/docs/doxygen)


# -------------------------------------------------------------------------------------------------
# Precompiled headers with 'cotire' CMake script.
# For more Info see 'ALox.cmake' which downloads the script and the cotire website at
# https://github.com/sakra/cotire/
# -------------------------------------------------------------------------------------------------
    if( ${ALIB_CMAKE_COTIRE} )
        set_target_properties( dot   PROPERTIES COTIRE_UNITY_SOURCE_MAXIMUM_NUMBER_OF_INCLUDES "-j" )
        set_target_properties( dot   PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT  "${ALIB_SRC_DIR}/alib/alib.hpp" )
        cotire( dot )
    endif()
