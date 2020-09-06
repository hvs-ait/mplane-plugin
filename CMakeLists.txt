cmake_minimum_required( VERSION 3.0 )

# Add an option to CMake to control whether we build this plugin or not
option( INSTALL_QMPLANE_PLUGIN "Check to install QMPlane_PLUGIN plugin" OFF )

if ( INSTALL_QMPLANE_PLUGIN )

    project( QMPlane_PLUGIN )
    
    # Option for building TESTS
    option( COMPILE_QMPlane_PLUGIN_TESTS "Check to enable REST support" OFF ) 
    
	include_directories( ${CloudCompare_SOURCE_DIR} )
    
    # Set path to external dependencies
    SET(EXTERNAL_TOOLS ${CMAKE_CURRENT_SOURCE_DIR}/external/)
    
    #we need ccOverlay classes
	file( GLOB CC_PLUGIN_CUSTOM_HEADER_LIST ${CloudCompare_SOURCE_DIR}/../common/ccOverlayDialog*.h )
	file( GLOB CC_PLUGIN_CUSTOM_SOURCE_LIST ${CloudCompare_SOURCE_DIR}/../common/ccOverlayDialog*.cpp )
    
    #we also need picking hub classes
	list( APPEND CC_PLUGIN_CUSTOM_HEADER_LIST ${CloudCompare_SOURCE_DIR}/../common/ccPickingListener.h )
	list( APPEND CC_PLUGIN_CUSTOM_HEADER_LIST ${CloudCompare_SOURCE_DIR}/../common/ccPickingHub.h )
	list( APPEND CC_PLUGIN_CUSTOM_SOURCE_LIST ${CloudCompare_SOURCE_DIR}/../common/ccPickingHub.cpp )
    
    # Add plugin ui
    add_subdirectory( ui )
    
    # Add plugin sources
    include_directories( src )
	add_subdirectory( src )
    
    if ( COMPILE_QMPlane_PLUGIN_TESTS )
        # Add plugin tests
        add_subdirectory(Tests)
    endif()
    
    include( ../../CMakePluginTpl.cmake )
endif()
