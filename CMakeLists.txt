cmake_minimum_required( VERSION 3.1 )

project( GL3W-GLFW-CMake-Template )

# https://github.com/Dav1dde/glad/issues/174

# https://www.glfw.org/docs/latest/build_guide.html#build_link_cmake_source
set( GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set( GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set( GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory( external/glfw )

if( MSVC )
    SET( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup" )
endif()
	
# Add header files
file(GLOB_RECURSE HEADER_FILES 
	${CMAKE_SOURCE_DIR}/src/*.h
	${CMAKE_SOURCE_DIR}/src/*.hpp)
	
# Add source files
file(GLOB_RECURSE SOURCE_FILES 
	${CMAKE_SOURCE_DIR}/src/*.c
	${CMAKE_SOURCE_DIR}/src/*.cpp)
	
add_executable( ${CMAKE_PROJECT_NAME} WIN32 ${SOURCE_FILES} )


set(GLAD_DIR "${CMAKE_SOURCE_DIR}/external/glad")

# https://github.com/aaronmjacobs/InitGL
add_library("glad" "${GLAD_DIR}/src/glad.c")
target_include_directories("glad" PRIVATE "${GLAD_DIR}/include")
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE "${GLAD_DIR}/include")

target_include_directories( ${CMAKE_PROJECT_NAME} PRIVATE ${HEADER_FILES} )	
target_link_libraries( ${CMAKE_PROJECT_NAME} "glad" glfw )

if( MSVC )
    if( ${CMAKE_VERSION} VERSION_LESS "3.6.0" ) 
        message( "\n\t[ WARNING ]\n\n\tCMake version lower than 3.6.\n\n\t - Please update CMake and rerun; OR\n\t - Manually set '" + ${CMAKE_PROJECT_NAME} + "' as StartUp Project in Visual Studio.\n" )
    else()
        set_property( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${CMAKE_PROJECT_NAME} )
    endif()
endif()
