# #################################################################################################
#  CMakeLists.txt - ALox Tools: DoxygenGraphTemplateInstanceRemover
#
#  (c) 2015 A-Worx GmbH, Germany
#  Published under MIT License (Open Source License, see LICENSE.txt)
#
#  How to use:
#   1. Enter subdirectory 'debug'   and invoke:  `cmake ..`
#   2. Enter subdirectory 'release' and invoke:  `cmake -DCMAKE_BUILD_TYPE=Release ..`
#   3. Invoke `make` within any of these directories.
#   More information is found in ALox documentation.
# ##################################################################################################

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

    #-- optional compilation symbols (ALib/ALox features).
    #-- uncomment to set (the opposite value is their default, therefore commenting the lines switches them)
    #set( ALIB_DEBUG_GLIB                "On"  )
    #set( ALIB_AVOID_ANALYZER_WARNINGS   "On"  )
    #set( ALIB_DEBUG_STRINGS             "On"  )
    #set( ALIB_FEAT_THREADS              "Off" )
    #set( ALOX_DBG_LOG                   "Off" )
    #set( ALOX_DBG_LOG_CI                "Off"  )
    #set( ALOX_REL_LOG                   "Off" )
    #set( ALOX_REL_LOG_CI                "On"  )

    set ( ALOX_BASE_DIR   "../.."  )
    include( ${ALOX_BASE_DIR}/build/cmake.cpp/ALox_Base.cmake )


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
    target_link_libraries     ( dot   ALox_StaticLib
                                      ${ALIB_EXTERNAL_LIBS}
                                      ${ALOX_EXTERNAL_LIBS}   )

    set( EXECUTABLE_OUTPUT_PATH       ${ALOX_BASE_DIR}/docs/doxygen)
