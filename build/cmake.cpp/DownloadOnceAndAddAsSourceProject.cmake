# #################################################################################################
#  DownloadOnceAndAddAsSourceProject.cmake - ALox Logging Library
#
#  (c) 2015 A-Worx GmbH, Germany
#  Published under MIT License (Open Source License, see LICENSE.txt)
#
#  Description (the name says it all):
#    Downloads a source library, installs sources in our binary directory
#    and adds the library as an external source project.
#
#  This snippit and idea was originally taken from:
#     http://www.kaizou.org/2014/11/gtest-cmake/
# #################################################################################################

include(ExternalProject)			# Enable ExternalProject CMake module

macro ( DownloadOnceAndAddAsSourceProject	name	url		saveName )
    if( NOT EXISTS  ${saveName} )
        message( "Downloading ${name} from ${url}" )
        file(	DOWNLOAD ${url} ${saveName} )
    endif()

    # Build (but don't install) GoogleTest (from source dir)
    ExternalProject_Add			( ${name}	URL				file://${saveName}#
                                            PREFIX			${CMAKE_CURRENT_BINARY_DIR}/${name}
                                            INSTALL_COMMAND "" )		# Disable install step

    # Create a libgtest target to be used as a dependency by test programs
    add_library					( lib${name}	IMPORTED STATIC GLOBAL )
    add_dependencies			( lib${name}	${name} )

    # Set IMPORTED_LOCATION property (well, I have not 100% understood why this is needed)
    ExternalProject_Get_Property( ${name}		BINARY_DIR )
    set_target_properties		( lib${name}	PROPERTIES		"IMPORTED_LOCATION"			"${BINARY_DIR}/lib${name}.a" )

    # export the source dir as a variable
    ExternalProject_Get_Property( ${name} source_dir )
    set( ${name}_source_dir ${source_dir} )
    #dbg: message( STATUS "Include dir for project ${name} set to <${${name}_source_dir}>")

endmacro( DownloadOnceAndAddAsSourceProject )




