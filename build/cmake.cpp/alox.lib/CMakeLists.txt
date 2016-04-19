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

    project("ALox_Static_Library")
    cmake_minimum_required( VERSION 3.1.0 ) ###FATAL_ERROR)

    # enable modules in project path #TODO: is this to be able to include ../*.cmake? test this and document it better
    set (CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/.")


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

    set ( ALOX_BASE_DIR   "../../.."  )
    include( ${ALOX_BASE_DIR}/build/cmake.cpp/ALox_Base.cmake )


# -------------------------------------------------------------------------------------------------
# cotire (set precompiled headers)
# -------------------------------------------------------------------------------------------------

    include(${ALIB_BASE_DIR}/build/cmake.cpp/cotire.cmake)

    set_target_properties( ALox_StaticLib           PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT
                                                    "${ALIB_SRC_DIR}/alib/stdafx_alib.h" )
    cotire               ( ALox_StaticLib )

    # cotire sets the following properties
    set ( _dumppname "ALox_StaticLib" )
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
#ALibCMake_DumpStatus()








