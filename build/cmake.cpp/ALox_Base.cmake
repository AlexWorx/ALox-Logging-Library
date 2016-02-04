# #################################################################################################
#  CMakeALoxBase.txt - cmake file for projects using ALib/ALox
#
#  (c) 2016 A-Worx GmbH, Germany
#  Published under MIT License (Open Source License, see LICENSE.txt)
#
#  This includes ALib_Base.cmake and expects it in the same source folder
#
#  In custom cmake file
#    - Set cmake variable "ALOX_BASE_DIR", e.g   'set ( ALOX_BASE_DIR  ~/mylibs/ALox/ )'
#    - Optionally set cmake variables matching the conditional compilation symbols as listed
#      in the ALox user manual to configure ALib/ALox features, e.g.
#        'set( ALIB_FEAT_THREADS "OFF" )'
#        'set( ALOX_REL_LOG      "ON" )'
#    - Include this cmake script using
#      include( ${ALOX_BASE_DIR}/build/cmake.cpp/ALox_Base.cmake )
#    - Add the target of your choice to your project.
#    - Alternatively: Add the sources / headers to your projects
#      Headers: ${ALIB_INCS}, ${ALOX_INCS}
#      Sources: ${ALIB_SRCS}, ${ALOX_SRCS}
#      In this case, also append compiler and linker flags to your target as defined in this file.
#      (When using the target, these flags get automatically inherited)
# #################################################################################################

if (ALOX_SRC_DIR)
    message( "ALox_Base.cmake: Already included (included twice!)" )
    return()
endif()

# check given base directory
if (NOT ALOX_BASE_DIR)
    message( "ALox_Base.cmake: ALOX_BASE_DIR not set" )
    return()
endif()

# convert given path to absolute path
get_filename_component(ALOX_BASE_DIR ${ALOX_BASE_DIR} ABSOLUTE)

# check
if (NOT EXISTS "${ALOX_BASE_DIR}/src.cpp/" )
    message( "ALox_Base.cmake: wrong ALOX_BASE_DIR given. Can't read sources" )
    return()
endif()

# include ALib
set ( ALIB_BASE_DIR   ${ALOX_BASE_DIR} )
include( ${ALIB_BASE_DIR}/build/cmake.cpp/ALib_Base.cmake )

# copy version from ALib
set( ALOX_VERSION       "${ALIB_VERSION}"     )



# -------------------------------------------------------------------------------------------------
# source code definitions
# -------------------------------------------------------------------------------------------------

    set (              ALOX_SRC_DIR      ${ALOX_BASE_DIR}/src.cpp/             )
    file( GLOB_RECURSE ALOX_INCS         ${ALOX_BASE_DIR}/src.cpp/alox/*.h*    )
    file( GLOB_RECURSE ALOX_SRCS         ${ALOX_BASE_DIR}/src.cpp/alox/*.cpp   )


# -------------------------------------------------------------------------------------------------
# Set ALox conditional compilation symbols
# -------------------------------------------------------------------------------------------------

    set( ALOX_COMPILER_SYMBOLS   "" )

    # Set default values for conditional compilation symbols
    if( NOT DEFINED  ALOX_DBG_LOG  )
        if ( CMAKE_BUILD_TYPE STREQUAL "Debug" )
            set( ALOX_DBG_LOG   "ON" )
        else()
            set( ALOX_DBG_LOG   "OFF" )
        endif()
    endif()

    if( NOT DEFINED  ALOX_DBG_LOG_CI  )
        set( ALOX_DBG_LOG_CI   "ON" )
    endif()

    if( NOT DEFINED  ALOX_REL_LOG  )
        set( ALOX_REL_LOG   "ON" )
    endif()

    if( NOT DEFINED  ALOX_REL_LOG_CI  )
        set( ALOX_REL_LOG_CI   "OFF" )
    endif()

    # write compilations symbols into ${ALOX_COMPILER_SYMBOLS}
    if ( ${ALOX_DBG_LOG} )
        set( ALOX_COMPILER_SYMBOLS  ${ALOX_COMPILER_SYMBOLS}    "ALOX_DBG_LOG_ON"          )
    else()
        set( ALOX_COMPILER_SYMBOLS  ${ALOX_COMPILER_SYMBOLS}    "ALOX_DBG_LOG_OFF"         )
    endif()
    if ( ${ALOX_DBG_LOG_CI} )
        set( ALOX_COMPILER_SYMBOLS  ${ALOX_COMPILER_SYMBOLS}    "ALOX_DBG_LOG_CI_ON"          )
    else()
        set( ALOX_COMPILER_SYMBOLS  ${ALOX_COMPILER_SYMBOLS}    "ALOX_DBG_LOG_CI_OFF"         )
    endif()
    if ( ${ALOX_REL_LOG} )
        set( ALOX_COMPILER_SYMBOLS  ${ALOX_COMPILER_SYMBOLS}    "ALOX_REL_LOG_ON"          )
    else()
        set( ALOX_COMPILER_SYMBOLS  ${ALOX_COMPILER_SYMBOLS}    "ALOX_REL_LOG_OFF"         )
    endif()
    if ( ${ALOX_REL_LOG_CI} )
        set( ALOX_COMPILER_SYMBOLS  ${ALOX_COMPILER_SYMBOLS}    "ALOX_REL_LOG_CI_ON"          )
    else()
        set( ALOX_COMPILER_SYMBOLS  ${ALOX_COMPILER_SYMBOLS}    "ALOX_REL_LOG_CI_OFF"         )
    endif()


# -------------------------------------------------------------------------------------------------
# Set filename of ALox library
# -------------------------------------------------------------------------------------------------

    # set name of ALox library
    set( ALOX_LIBRARY_FILENAME  "alox_${ALOX_VERSION}" )

    if ( CMAKE_BUILD_TYPE STREQUAL "Debug" )
        set ( ALOX_LIBRARY_FILENAME         ${ALOX_LIBRARY_FILENAME}_DBG        )
        if ( NOT ${ALIB_DEBUG} )
            set ( ALOX_LIBRARY_FILENAME     ${ALOX_LIBRARY_FILENAME}_NOALIBDBG  )
        endif()
    else()
        if ( NOT ${ALIB_DEBUG} )
            set ( ALOX_LIBRARY_FILENAME     ${ALOX_LIBRARY_FILENAME}_NODBG_ALIBDBG   )
        endif()
    endif()

    if ( ${ALIB_DEBUG_STRINGS} )
        set ( ALOX_LIBRARY_FILENAME         ${ALOX_LIBRARY_FILENAME}_STRDBG     )
    endif()

    if ( NOT ${ALIB_FEAT_THREADS} )
        set ( ALOX_LIBRARY_FILENAME         ${ALOX_LIBRARY_FILENAME}_NOTHRD     )
    endif()

    if ( CMAKE_BUILD_TYPE STREQUAL "Debug" )
        if ( NOT ${ALOX_DBG_LOG} )
            set ( ALOX_LIBRARY_FILENAME     ${ALOX_LIBRARY_FILENAME}_NODBGLOG   )
        endif()
    endif()

    if ( NOT ${ALOX_REL_LOG} )
        set ( ALOX_LIBRARY_FILENAME         ${ALOX_LIBRARY_FILENAME}_NORELLOG   )
    endif()


#set ( ALOX_STATIC_LIBRARY "${CMAKE_CURRENT_BINARY_DIR}/${ALOX_LIBRARY_FILENAME}" )
#message(${ALOX_STATIC_LIBRARY})
##ALibCMake_DumpStatus()


# -------------------------------------------------------------------------------------------------
# Targets
# -------------------------------------------------------------------------------------------------

    # sources
    add_library               ( ALox_StaticLib                               ${ALIB_INCS} ${ALOX_INCS}
                                                                             ${ALIB_SRCS} ${ALOX_SRCS}       )
    target_include_directories( ALox_StaticLib    PUBLIC                     ${ALIB_SRC_DIR} ${ALOX_SRC_DIR} )

    # compiler/linker flags
    set_target_properties     ( ALox_StaticLib    PROPERTIES  COMPILE_FLAGS  ${AWORX_COMPILE_FLAGS}          )

    target_compile_definitions( ALox_StaticLib    PUBLIC                     ${ALIB_COMPILER_SYMBOLS}
                                                                             ${ALOX_COMPILER_SYMBOLS}        )
    set_target_properties     ( ALox_StaticLib    PROPERTIES  LINK_FLAGS     ${AWORX_LINK_FLAGS}             )

    # library output path/name (for static libs this is 'ARCHIVE_...', for dynamic libs 'LIBRARY_...'
    set_target_properties     ( ALox_StaticLib    PROPERTIES  ARCHIVE_OUTPUT_NAME         ${ALOX_LIBRARY_FILENAME}        )

