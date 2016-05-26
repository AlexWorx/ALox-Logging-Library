# #################################################################################################
#  CMakeLists.txt - ALox Logging Library
#
#  (c) 2015 A-Worx GmbH, Germany
#  Published under MIT License (Open Source License, see LICENSE.txt)
#
#  How to use:
#   1. Enter subdirectory 'debug'   and invoke:  `cmake ..`
#   2. Enter subdirectory 'release' and invoke:  `cmake -DCMAKE_BUILD_TYPE=Release ..`
#   3. Invoke `make` within any of these directories.
#   More information is found in ALox documentation.
# #################################################################################################

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

    #-- optional compilation symbols (ALib/ALox features).
    #-- uncomment to set (the opposite value is their default, therefore commenting the lines switches them)
    #set( ALIB_DEBUG_GLIB                "On"  )
    #set( ALIB_AVOID_ANALYZER_WARNINGS   "On"  )
    #set( ALIB_DEBUG_STRINGS             "On"  )
    #set( ALIB_FEAT_THREADS              "Off" ) // disabling this does not work with gtest projects
    #set( ALOX_DBG_LOG                   "Off" )
    #set( ALOX_DBG_LOG_CI                "Off"  )
    #set( ALOX_REL_LOG                   "Off" )
    #set( ALOX_REL_LOG_CI                "On"  )



    #-- enable coverage compilation. Use script 'coverage-lcov.sh' after running the tests to create
    #-- coverage information
    #set( AWORX_COVERAGE_COMPILE "On" )

    set ( ALOX_BASE_DIR   "../../.."  )
    include( ${ALOX_BASE_DIR}/build/cmake.cpp/ALox_Base.cmake )

# -------------------------------------------------------------------------------------------------
# source code definitions
# -------------------------------------------------------------------------------------------------

    set (              ALIB_UTESTS_SRC_DIR  ${ALIB_BASE_DIR}/src.cpp/alib.unittests  )
    file( GLOB_RECURSE ALIB_UTESTS_INCS     ${ALIB_UTESTS_SRC_DIR}/*.h*              )
    file( GLOB_RECURSE ALIB_UTESTS_SRCS     ${ALIB_UTESTS_SRC_DIR}/*.cpp             )

    set (              ALOX_UTESTS_SRC_DIR  ${ALOX_BASE_DIR}/src.cpp/alox.unittests  )
    file( GLOB_RECURSE ALOX_UTESTS_INCS     ${ALOX_UTESTS_SRC_DIR}/*.h*              )
    file( GLOB_RECURSE ALOX_UTESTS_SRCS     ${ALOX_UTESTS_SRC_DIR}/*.cpp             )

## -------------------------------------------------------------------------------------------------
## find libraries
## -------------------------------------------------------------------------------------------------

    # Download (if not yet) and extract gtest/gmock
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/.")
    include( ../DownloadOnceAndAddAsSourceProject.cmake )
    DownloadOnceAndAddAsSourceProject( gtest
                                       "https://googletest.googlecode.com/files/gtest-1.7.0.zip"
                                       "${CMAKE_CURRENT_SOURCE_DIR}/gtest-1.7.0.zip"           )
    DownloadOnceAndAddAsSourceProject( gmock
                                       "https://googlemock.googlecode.com/files/gmock-1.7.0.zip"
                                       "${CMAKE_CURRENT_SOURCE_DIR}/gmock-1.7.0.zip"           )

# -------------------------------------------------------------------------------------------------
# Target
# -------------------------------------------------------------------------------------------------

    add_executable            ( ALib_ALox_UT    ${ALIB_INCS}         ${ALOX_INCS}
                                                ${ALIB_UTESTS_INCS}  ${ALOX_UTESTS_INCS}
                                                ${ALIB_UTESTS_SRCS}  ${ALOX_UTESTS_SRCS}      )

    set_target_properties     ( ALib_ALox_UT    PROPERTIES  COMPILE_FLAGS
                                                "${AWORX_COMPILE_FLAGS}  -Wno-conversion-null" ) # for GTEST

    target_compile_definitions( ALib_ALox_UT    PRIVATE  ${ALIB_COMPILER_SYMBOLS}
                                                         ${ALOX_COMPILER_SYMBOLS}        )
    target_compile_definitions( ALib_ALox_UT    PRIVATE  "ALIB_GTEST_ON"  )

    set_target_properties     ( ALib_ALox_UT    PROPERTIES  LINK_FLAGS   ${AWORX_LINK_FLAGS}   )

    target_include_directories( ALib_ALox_UT    PRIVATE   ${ALIB_UTESTS_SRC_DIR}
                                                          ${ALOX_UTESTS_SRC_DIR}
                                                          ${gtest_source_dir}/include )

    target_link_libraries     ( ALib_ALox_UT    ${ALIB_EXTERNAL_LIBS}
                                                ${ALOX_EXTERNAL_LIBS}
                                                ALox_StaticLib
                                                libgtest                                     )



# -------------------------------------------------------------------------------------------------
# cotire (set precompiled headers)
# -------------------------------------------------------------------------------------------------

#    include(cotire)
#
#    set_target_properties( alox           PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT
#                                          "${ALIB_SRC_DIR}/alib/stdafx_alib.h" )
#    cotire               ( alox )
#
#    set_target_properties( ALoxUnitTests  PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT
#                                          "${ALIB_SRC_DIR}/alib/stdafx_alib.h" )
#
#    cotire               ( ALoxUnitTests )
#
#
#    # cotire sets the following properties
#    set ( _dumppname "alox" )
#    get_target_property( _unitySource        ${_dumppname}    COTIRE_CXX_UNITY_SOURCE      )
#    get_target_property( _prefixHeader       ${_dumppname}    COTIRE_CXX_PREFIX_HEADER     )
#    get_target_property( _precompiledHeader  ${_dumppname}    COTIRE_CXX_PRECOMPILED_HEADER)
#    get_target_property( _unityTargetName    ${_dumppname}    COTIRE_UNITY_TARGET_NAME     )
#
#    message(STATUS "${_dumppname} unity source:       ${_unitySource}")
#    message(STATUS "${_dumppname} prefix header:      ${_prefixHeader}")
#    message(STATUS "${_dumppname} precompiled header: ${_precompiledHeader}")
#    message(STATUS "${_dumppname} unity target:       ${_unityTargetName}")
#

# -------------------------------------------------------------------------------------------------
# End
# -------------------------------------------------------------------------------------------------

# uncomment for debug
#ALibCMake_DumpStatus()








