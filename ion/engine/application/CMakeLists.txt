#	 _____                               _
#	|_   _|                             (_)
#	  | |  ___  _ __     ___ _ __   __ _ _ _ __   ___
#	  | | / _ \| '_ \   / _ \ '_ \ / _` | | '_ \ / _ \
#	 _| || (_) | | | | |  __/ | | | (_| | | | | |  __/
#	 \___/\___/|_| |_|  \___|_| |_|\__, |_|_| |_|\___|
#	                                __/ |
#	                               |___/
#
#
#	ion/engine/application subfolder CMake file
#
#	DESCTIPTION: Engine executable, gathering all previous modules together
#



# Cmake min version
cmake_minimum_required(VERSION 3.25 FATAL_ERROR)

get_filename_component(TARGET_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

#set(TARGET_NAME "IonEngine")

file(GLOB_RECURSE TARGET_HEADER_FILES
	${CMAKE_CURRENT_SOURCE_DIR}/*.h
	${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)

file(GLOB_RECURSE TARGET_SOURCE_FILES
	${CMAKE_CURRENT_SOURCE_DIR}/*.c
	${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)


# git and documentation files for easy access from VS solution
file(GLOB TARGET_EXTRA_FILES
	${CMAKE_SOURCE_DIR}/.gitignore
	${CMAKE_SOURCE_DIR}/.gitattributes
	${CMAKE_SOURCE_DIR}/*.md
)


# Shared files at the project's root
file(GLOB COMMON_FILES
	${CMAKE_SOURCE_DIR}/ion/*.hpp
	${CMAKE_SOURCE_DIR}/ion/*.h
	${CMAKE_SOURCE_DIR}/ion/CMakeLists.txt
	${CMAKE_SOURCE_DIR}/ion/engine/CMakeLists.txt
)

file(GLOB_RECURSE SHADER_FILES
	${CMAKE_CURRENT_BINARY_DIR}/*.shader
	${CMAKE_CURRENT_BINARY_DIR}/*.vert
	${CMAKE_CURRENT_BINARY_DIR}/*.frag
	${CMAKE_CURRENT_BINARY_DIR}/*.glsl
)

set (TARGET_FILES ${TARGET_HEADER_FILES} ${TARGET_SOURCE_FILES})

# VS filters
source_group("Header" ${CMAKE_CURRENT_SOURCE_DIR} FILES ${TARGET_HEADER_FILES})
source_group("Source" ${CMAKE_CURRENT_SOURCE_DIR} FILES ${TARGET_SOURCE_FILES})

# Useful files at the solution's root
source_group("Extra files" FILES ${TARGET_EXTRA_FILES})

# Files shared by several modules
source_group("Common" FILES ${COMMON_FILES})

source_group("Shaders" FILES ${SHADER_FILES})

# Create final application exe
add_executable(${TARGET_NAME})

# Add all gathered files as sources for compilation and VS filters
target_sources(${TARGET_NAME} PRIVATE ${TARGET_FILES} ${TARGET_EXTRA_FILES} ${COMMON_FILES} ${SHADER_FILES})

target_include_directories(${TARGET_NAME}
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
	PRIVATE ${CMAKE_SOURCE_DIR}/ion
)

# link against ALL previous libraries
target_link_libraries(${TARGET_NAME}
	PRIVATE mathlib
	PRIVATE ${DEPENDENCIES_LIBRARY}
	PRIVATE ${UI_LIBRARY}
	PRIVATE ${RENDERER_LIBRARY}
	PRIVATE ${CORE_LIBRARY}
)

if (MSVC)
	# Disable linker warning for glfw3's missing debug info
	target_link_options(${TARGET_NAME} PRIVATE /IGNORE:4099)
	target_compile_options(${TARGET_NAME} PRIVATE /W4 /WX)
endif()
