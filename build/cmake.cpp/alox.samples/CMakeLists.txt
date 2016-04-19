# #################################################################################################
#  CMakeLists.txt - ALox Samples
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

    project("ALox.Samples")
    cmake_minimum_required( VERSION 3.1.0 ) ###FATAL_ERROR)

    # enable modules in project path
    set (CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/.")


## -------------------------------------------------------------------------------------------------
## include ALib/ALox base cmake file
## -------------------------------------------------------------------------------------------------

#! [DOXYGEN_CMAKE_INCLUDE]
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

    set ( ALOX_BASE_DIR   "../../.."  )
    include( ${ALOX_BASE_DIR}/build/cmake.cpp/ALox_Base.cmake )
#! [DOXYGEN_CMAKE_INCLUDE]

# -------------------------------------------------------------------------------------------------
# Sample sources
# -------------------------------------------------------------------------------------------------
    file( GLOB_RECURSE   ALOX_SAMPLES_SOURCES   ${ALOX_BASE_DIR}/src.cpp/alox.samples/*.cpp       )

# -------------------------------------------------------------------------------------------------
# Target
# -------------------------------------------------------------------------------------------------

#! [DOXYGEN_CMAKE_SAMPLE_TARGET]
    add_executable            ( ALoxSamples   ${ALOX_SAMPLES_SOURCES}  )

    set_target_properties     ( ALoxSamples   PROPERTIES  COMPILE_FLAGS ${AWORX_COMPILE_FLAGS})
    set_target_properties     ( ALoxSamples   PROPERTIES  LINK_FLAGS    ${AWORX_LINK_FLAGS}   )

    target_link_libraries     ( ALoxSamples   ALox_StaticLib
                                              ${ALIB_EXTERNAL_LIBS}
                                              ${ALOX_EXTERNAL_LIBS}   )
#! [DOXYGEN_CMAKE_SAMPLE_TARGET]

# -------------------------------------------------------------------------------------------------
# End
# -------------------------------------------------------------------------------------------------

# uncomment for debug
#ALibCMake_DumpStatus()








