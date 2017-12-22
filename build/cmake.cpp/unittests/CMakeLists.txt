# #################################################################################################
#  CMakeLists.txt - ALox Logging Library
#
#  Copyright 2015 A-Worx GmbH, Germany
#  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
#
#  How to use:
#   1. Enter subdirectory 'debug'   and invoke:  `cmake ..`
#   2. Enter subdirectory 'release' and invoke:  `cmake -DCMAKE_BUILD_TYPE=Release ..`
#   3. Invoke `make` within any of these directories.
#   More information is found in ALox documentation.
# #################################################################################################

# -------------------------------------------------------------------------------------------------
# Prior to setting CMake project
# -------------------------------------------------------------------------------------------------

    ### uncomment to force cotire on clean cmake built
    #set( ALIB_CMAKE_COTIRE_DEFAULT   "On" )

# -------------------------------------------------------------------------------------------------
# General
# -------------------------------------------------------------------------------------------------

    project("ALib_ALox_UnitTests")
    cmake_minimum_required( VERSION 3.1.0 ) ###FATAL_ERROR)

    # enable modules in project path
    set (CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/.")


## -------------------------------------------------------------------------------------------------
## include ALox base cmake file
## -------------------------------------------------------------------------------------------------

    include( ../../../build/cmake.cpp/ALox.cmake )


# --------------------------------------------------------------------------------------------------
# set cache variables
# --------------------------------------------------------------------------------------------------
    set( ALIB_GTEST                 "On"                                                CACHE STRING
         "If true, unit tests are compiled for gtest library."   )


# -------------------------------------------------------------------------------------------------
# source code definitions
# -------------------------------------------------------------------------------------------------

    # ALib unit tests
    set (              ALIB_UTESTS_SRC_DIR  ${ALIB_BASE_DIR}/src.cpp/alib.unittests  )
    file( GLOB_RECURSE ALIB_UTESTS_INCS     ${ALIB_UTESTS_SRC_DIR}/*.h*              )
    file( GLOB_RECURSE ALIB_UTESTS_SRCS     ${ALIB_UTESTS_SRC_DIR}/*.cpp             )

    # ALox unit tests
    set (              ALOX_UTESTS_SRC_DIR  ${ALOX_BASE_DIR}/src.cpp/alox.unittests  )
    file( GLOB_RECURSE ALOX_UTESTS_INCS     ${ALOX_UTESTS_SRC_DIR}/*.h*              )
    file( GLOB_RECURSE ALOX_UTESTS_SRCS     ${ALOX_UTESTS_SRC_DIR}/*.cpp             )

## -------------------------------------------------------------------------------------------------
## find libraries
## -------------------------------------------------------------------------------------------------

    if ( ${ALIB_GTEST} )
        # GTest
        # For Google Test, we first download CMake tool "Crascit/DownloadProject" that allows
        # downloading and integrating projects 8-)
        if( NOT EXISTS  ${CMAKE_CURRENT_SOURCE_DIR}/DownloadProject.cmake )
            message( STATUS "Downloading 'DownloadProject.cmake' from github" )
            file( DOWNLOAD
                  "https://raw.githubusercontent.com/Crascit/DownloadProject/master/DownloadProject.cmake"
                  "${CMAKE_CURRENT_SOURCE_DIR}/DownloadProject.cmake" )
            file( DOWNLOAD
                  "https://raw.githubusercontent.com/Crascit/DownloadProject/master/DownloadProject.CMakeLists.cmake.in"
                  "${CMAKE_CURRENT_SOURCE_DIR}/DownloadProject.CMakeLists.cmake.in" )
        endif()

        if( NOT EXISTS  ${CMAKE_CURRENT_SOURCE_DIR}/DownloadProject.cmake )
            message( "Error downloading 'DownloadProject.cmake'")
        endif()

        # ...now we use the download tool on gtest
        include(DownloadProject.cmake)

        if (CMAKE_VERSION VERSION_LESS 3.2)
            set(UPDATE_DISCONNECTED_IF_AVAILABLE "")
        else()
            set(UPDATE_DISCONNECTED_IF_AVAILABLE "UPDATE_DISCONNECTED 1")
        endif()

        download_project(PROJ                googletest
                         GIT_REPOSITORY      https://github.com/google/googletest.git
                         GIT_TAG             master
                         ${UPDATE_DISCONNECTED_IF_AVAILABLE}                               )

        # Prevent GoogleTest from overriding our compiler/linker options
        # when building with Visual Studio
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

        add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})

        # When using CMake 2.8.11 or later, header path dependencies
        # are automatically added to the gtest and gmock targets.
        # For earlier CMake versions, we have to explicitly add the
        # required directories to the header search path ourselves.
        if (CMAKE_VERSION VERSION_LESS 2.8.11)
            include_directories("${gtest_SOURCE_DIR}/include"
                                "${gmock_SOURCE_DIR}/include")
        endif()


    endif()

    # QT
    find_package(Qt5Core)
    find_package(Qt5Widgets)

    # multithreading
    if ( NOT ${ALIB_FEAT_THREADS} )
        if ( ${ALIB_GTEST} )

        find_package(Threads)

        # we hack this into the existing alib variable...
        set( ALIB_EXTERNAL_LIBS ${ALIB_EXTERNAL_LIBS}         ${CMAKE_THREAD_LIBS_INIT} )

        endif()
    endif()



# -------------------------------------------------------------------------------------------------
# Target
# -------------------------------------------------------------------------------------------------

    add_executable             ( ALib_ALox_UT    ${ALIB_INCS}         ${ALOX_INCS}
                                                 ${ALIB_UTESTS_INCS}  ${ALOX_UTESTS_INCS}
                                                 ${ALIB_UTESTS_SRCS}  ${ALOX_UTESTS_SRCS}    )

    target_include_directories ( ALib_ALox_UT    PRIVATE   ${ALIB_UTESTS_SRC_DIR}
                                                           ${ALOX_UTESTS_SRC_DIR}            )
    ALoxCompilerAndLinkerFlags( ALib_ALox_UT )

    # for GTEST, option available only up to gcc 7.2
    if     ( ${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU"    )
      if   (CMAKE_CXX_COMPILER_VERSION VERSION_LESS "7.2")
        target_compile_options ( ALib_ALox_UT    PRIVATE "-Wno-gnu-statement-expression" )
      endif()
    endif()

    target_link_libraries      ( ALib_ALox_UT    ${ALIB_EXTERNAL_LIBS}
                                                 ${ALOX_EXTERNAL_LIBS}
                                                 ALox_SharedLib                              )

    if ( ${ALIB_GTEST} )
        target_compile_definitions( ALib_ALox_UT PRIVATE  "ALIB_GTEST_ON"                    )
        target_include_directories( ALib_ALox_UT    PRIVATE   ${gtest_source_dir}/include    )
        target_link_libraries     ( ALib_ALox_UT gtest                                       )
    endif()


    if ( Qt5Core_FOUND )
        target_include_directories( ALib_ALox_UT PRIVATE      ${Qt5Core_INCLUDE_DIRS}       )
        target_compile_definitions( ALib_ALox_UT PRIVATE      ${Qt5Core_DEFINITIONS}        )
        target_link_libraries     ( ALib_ALox_UT              ${Qt5Core_QTMAIN_LIBRARIES}   )
    endif()

    if ( Qt5Widgets_FOUND )
        target_include_directories( ALib_ALox_UT PRIVATE      ${Qt5Widgets_INCLUDE_DIRS}    )
        target_compile_definitions( ALib_ALox_UT PRIVATE      ${Qt5Widgets_DEFINITIONS}     )
        target_link_libraries     ( ALib_ALox_UT              ${Qt5Widgets_LIBRARIES}       )
    endif()

# -------------------------------------------------------------------------------------------------
# Precompiled headers with 'cotire' CMake script.
# For more Info see 'ALox.cmake' which downloads the script and the cotire website at
# https://github.com/sakra/cotire/
# -------------------------------------------------------------------------------------------------
if ( ${ALIB_CMAKE_COTIRE} )

    # use multiple processor cores
    set_target_properties( ALib_ALox_UT    PROPERTIES COTIRE_UNITY_SOURCE_MAXIMUM_NUMBER_OF_INCLUDES "-j" )

    # header for precomp is "alox/alox.hpp"
    set_target_properties( ALib_ALox_UT    PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT  "${ALIB_SRC_DIR}/alox/alox.hpp" )

    #set some other cotire specific settings
    set_source_files_properties( ${ALIB_SRC_DIR}/alox.unittests/ut_alox_log_scopes.cpp   PROPERTIES COTIRE_EXCLUDED "1"  )
    set_target_properties      ( ALib_ALox_UT PROPERTIES   COTIRE_UNITY_SOURCE_POST_UNDEFS "LOX_LOX;TESTCLASSNAME;cout" )

    # add cotire to project
    cotire               ( ALib_ALox_UT )


    #--- dump cotire properties ---
    # set ( _dumppname "ALib_ALox_UT" )
    # get_target_property( _unitySource        ${_dumppname}    COTIRE_CXX_UNITY_SOURCE      )
    # get_target_property( _prefixHeader       ${_dumppname}    COTIRE_CXX_PREFIX_HEADER     )
    # get_target_property( _precompiledHeader  ${_dumppname}    COTIRE_CXX_PRECOMPILED_HEADER)
    # get_target_property( _unityTargetName    ${_dumppname}    COTIRE_UNITY_TARGET_NAME     )
    #
    # message(STATUS "${_dumppname} unity source:       ${_unitySource}")
    # message(STATUS "${_dumppname} prefix header:      ${_prefixHeader}")
    # message(STATUS "${_dumppname} precompiled header: ${_precompiledHeader}")
    # message(STATUS "${_dumppname} unity target:       ${_unityTargetName}")

endif()

# -------------------------------------------------------------------------------------------------
# End
# -------------------------------------------------------------------------------------------------

# uncomment for debug
#ALibCMake_DumpStatus()








