# #################################################################################################
#  CMakeLists.txt - ALox Logging Library
#
#  (c) 2015 A-Worx GmbH, Germany
#  Published under MIT License (Open Source License, see LICENSE.txt)
#
#  How to use:
#   1. Create/Enter subdirectory 'debug'   and invoke:  `cmake -DCMAKE_BUILD_TYPE=Debug ..`
#   2. Create/Enter subdirectory 'release' and invoke:  `cmake -DCMAKE_BUILD_TYPE=Release ..`
#   3. Invoke `make` within any of these directories.
#   More information is found in README.md
# #################################################################################################

# -------------------------------------------------------------------------------------------------
# General
# -------------------------------------------------------------------------------------------------

    project("ALox")
    cmake_minimum_required( VERSION 3.1.0 ) ###FATAL_ERROR)

    # build type defaults to "Debug"
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

    # multithreading
    find_package(Threads)

    # Download (if not yet) and extract gtest/gmock
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/.")
    include( DownloadOnceAndAddAsSourceProject )
    DownloadOnceAndAddAsSourceProject( gtest
                                       "https://googletest.googlecode.com/files/gtest-1.7.0.zip"
                                       "${CMAKE_CURRENT_SOURCE_DIR}/gtest-1.7.0.zip"           )
    DownloadOnceAndAddAsSourceProject( gmock
                                       "https://googlemock.googlecode.com/files/gmock-1.7.0.zip"
                                       "${CMAKE_CURRENT_SOURCE_DIR}/gmock-1.7.0.zip"           )

# -------------------------------------------------------------------------------------------------
# source code definitions
# -------------------------------------------------------------------------------------------------

    set ( SRC_D                ../../..                                          )

    # AWXU
    set (              AWXU_SRC_D        ${SRC_D}/src/cpp.aworx.util/            )
    file( GLOB_RECURSE AWXU_INCS         ${AWXU_SRC_D}/*.hpp                     )
    file( GLOB_RECURSE AWXU_SRCS         ${AWXU_SRC_D}/*.cpp                     )

    set (              AWXU_UTESTS_SRC_D ${SRC_D}/src/cpp.aworx.util.unittests/  )
    file( GLOB_RECURSE AWXU_UTESTS_INCS  ${AWXU_UTESTS_SRC_D}/*.h                )
    file( GLOB_RECURSE AWXU_UTESTS_SRCS  ${AWXU_UTESTS_SRC_D}/*.cpp              )

    # ALox
    set (              ALOX_SRC_D        ${SRC_D}/src/cpp.alox/                  )
    file( GLOB_RECURSE ALOX_INCS         ${ALOX_SRC_D}/*.h*                      )
    file( GLOB_RECURSE ALOX_SRCS         ${ALOX_SRC_D}/*.cpp                     )

    set (              ALOX_UTESTS_SRC_D ${SRC_D}/src/cpp.alox.unittests/        )
    file( GLOB_RECURSE ALOX_UTESTS_INCS  ${ALOX_UTESTS_SRC_D}/*.h*               )
    file( GLOB_RECURSE ALOX_UTESTS_SRCS  ${ALOX_UTESTS_SRC_D}/*.cpp              )

# -------------------------------------------------------------------------------------------------
# set output directory
# -------------------------------------------------------------------------------------------------

    set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}/lib)
    set( LIB_INSTALL_DIR                ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}/lib)
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


    # Target: ALox
    add_library               ( alox            ${AWXU_INCS} ${ALOX_INCS}
                                                ${AWXU_SRCS} ${ALOX_SRCS}     )

    target_include_directories( alox            PUBLIC
                                                ${AWXU_SRC_D} ${ALOX_SRC_D}   )

    set_target_properties     ( alox            PROPERTIES  COMPILE_FLAGS
                                                ${ALOX_COMPILE_FLAGS}         )

    # Target: ALoxUnitTests

    add_executable            ( ALoxUnitTests   ${AWXU_INCS}         ${ALOX_INCS}
                                                ${AWXU_UTESTS_INCS}  ${ALOX_UTESTS_INCS}
                                                ${AWXU_UTESTS_SRCS}  ${ALOX_UTESTS_SRCS}      )

    set_target_properties     ( ALoxUnitTests   PROPERTIES  COMPILE_FLAGS
                                                "${ALOX_COMPILE_FLAGS}  -Wno-conversion-null" )

    target_include_directories( ALoxUnitTests   PRIVATE
                                                ${AWXU_UTESTS_SRC_D} ${gtest_source_dir}/include )

    target_link_libraries     ( ALoxUnitTests   "${CMAKE_THREAD_LIBS_INIT}"
                                                libgtest   alox                                  )



# -------------------------------------------------------------------------------------------------
# Set preprocessor definitions for targets
# !Be sure to set same compile symbolds when compiling entities using ALox!
# -------------------------------------------------------------------------------------------------

    ### uncomment this to build a single threaded version of AWXU/ALOX ---
    #target_compile_definitions( alox            PUBLIC  "AWXU_FEAT_THREADS_OFF" )

    if( CMAKE_BUILD_TYPE STREQUAL "Debug" )

        ### uncomment this to add extra debug code
        #target_compile_definitions( alox         PUBLIC  "_GLIBCXX_DEBUG" )
        #target_compile_definitions( alox         PUBLIC  "_GLIBCXX_DEBUG_PEDANTIC" )
        #target_compile_definitions( alox         PUBLIC  "_GLIBCPP_CONCEPT_CHECKS" )

        #target_compile_definitions( alox         PUBLIC  "AWXU_DEBUG_OFF" )
        #target_compile_definitions( alox         PUBLIC  "AWXU_DEBUG_ASTRING_ON" )

    else()

    endif()

    target_compile_definitions( ALoxUnitTests   PRIVATE  "ALOX_GTEST"  )
    #target_compile_definitions( ALoxUnitTests   PRIVATE  "ALOX_DBG_LOG_CI_OFF" )


# -------------------------------------------------------------------------------------------------
# cotire (set precompiled headers)
# -------------------------------------------------------------------------------------------------

    include(cotire)

    set_target_properties( alox           PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT
                                          "${AWXU_SRC_D}/stdafx_awxu.h" )
    cotire               ( alox )

    set_target_properties( ALoxUnitTests  PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT
                                          "${AWXU_SRC_D}/stdafx_awxu.h" )

    cotire               ( ALoxUnitTests )


    # cotire sets the following properties
    set ( _dumppname "alox" )
    get_target_property( _unitySource        ${_dumppname}    COTIRE_CXX_UNITY_SOURCE      )
    get_target_property( _prefixHeader       ${_dumppname}    COTIRE_CXX_PREFIX_HEADER     )
    get_target_property( _precompiledHeader  ${_dumppname}    COTIRE_CXX_PRECOMPILED_HEADER)
    get_target_property( _unityTargetName    ${_dumppname}    COTIRE_UNITY_TARGET_NAME     )

    message(STATUS "${_dumppname} unity source:       ${_unitySource}")
    message(STATUS "${_dumppname} prefix header:      ${_prefixHeader}")
    message(STATUS "${_dumppname} precompiled header: ${_precompiledHeader}")
    message(STATUS "${_dumppname} unity target:       ${_unityTargetName}")


# -------------------------------------------------------------------------------------------------
# End
# -------------------------------------------------------------------------------------------------

# uncomment for debug
#include( LogUsefulVariables )








