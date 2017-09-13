# #################################################################################################
#  CMakeLists.txt - ALox Samples
#
#  Copyright 2017 A-Worx GmbH, Germany
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
    # set( ALIB_CMAKE_COTIRE_DEFAULT   "On" )


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
    include( ../../../build/cmake.cpp/ALox.cmake )
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

    target_link_libraries     ( ALoxSamples   ALox_SharedLib
                                              ${ALIB_EXTERNAL_LIBS}
                                              ${ALOX_EXTERNAL_LIBS}   )
#! [DOXYGEN_CMAKE_SAMPLE_TARGET]

# -------------------------------------------------------------------------------------------------
# Precompiled headers with 'cotire' CMake script.
# For more Info see 'ALox.cmake' which downloads the script and the cotire website at
# https://github.com/sakra/cotire/
# -------------------------------------------------------------------------------------------------
    if( ${ALIB_CMAKE_COTIRE} )
        set_target_properties( ALoxSamples     PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT   "${ALIB_SRC_DIR}/alib/alib.hpp" )
        cotire( ALoxSamples )

        #--- dump cotire properties ---
        #set ( _dumppname "ALoxSamples" )
        #get_target_property( _unitySource        ${_dumppname}    COTIRE_CXX_UNITY_SOURCE      )
        #get_target_property( _prefixHeader       ${_dumppname}    COTIRE_CXX_PREFIX_HEADER     )
        #get_target_property( _precompiledHeader  ${_dumppname}    COTIRE_CXX_PRECOMPILED_HEADER)
        #get_target_property( _unityTargetName    ${_dumppname}    COTIRE_UNITY_TARGET_NAME     )
    
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








