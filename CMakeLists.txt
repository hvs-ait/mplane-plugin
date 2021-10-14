# Add an option to CMake to control whether we build this plugin or not
option( PLUGIN_STANDARD_QMPLANE "Check to install QMPlane_PLUGIN plugin" OFF )

if ( PLUGIN_STANDARD_QMPLANE )

    project( QMPLANE_PLUGIN )
    include( CMakePolicies NO_POLICY_SCOPE )
    
    # Option for building TESTS
    option( COMPILE_QMPLANE_PLUGIN_TESTS "Check to enable REST support" OFF ) 
    
    # CloudCompare sources and headers
	file( GLOB CC_PLUGIN_CUSTOM_HEADER_LIST ${CloudCompare_SOURCE_DIR}/../common/ccOverlayDialog*.h )
	file( GLOB CC_PLUGIN_CUSTOM_SOURCE_LIST ${CloudCompare_SOURCE_DIR}/../common/ccOverlayDialog*.cpp )
    list( APPEND CC_PLUGIN_CUSTOM_HEADER_LIST ${CloudCompare_SOURCE_DIR}/../common/ccPickingListener.h )
	list( APPEND CC_PLUGIN_CUSTOM_HEADER_LIST ${CloudCompare_SOURCE_DIR}/../common/ccPickingHub.h )
	list( APPEND CC_PLUGIN_CUSTOM_SOURCE_LIST ${CloudCompare_SOURCE_DIR}/../common/ccPickingHub.cpp )
    
    # Set path to external dependencies
    SET( EXTERNAL_TOOLS ${CMAKE_CURRENT_SOURCE_DIR}/external/ )
    
    # Add plugin ui
    add_subdirectory( ui )
    
    include( ../../../CMakePluginTpl.cmake )

	target_sources( ${PROJECT_NAME}
		PRIVATE
			${CMAKE_CURRENT_SOURCE_DIR}/qMPlane.h
			${CMAKE_CURRENT_SOURCE_DIR}/qMPlane.cpp
			${CMAKE_CURRENT_SOURCE_DIR}/qMPlane.qrc
	)
    
    # Add plugin sources
	add_subdirectory( src )
    
    if ( COMPILE_QMPLANE_PLUGIN_TESTS )
        # Add plugin tests
        add_subdirectory(Tests)
    endif()
endif()
