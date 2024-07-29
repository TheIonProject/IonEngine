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
#	ion/engine/core subfolder CMake file
#
#	DESCTIPTION: Configures the engine's entity component system
#
#


cmake_minimum_required(VERSION 3.25 FATAL_ERROR)

get_filename_component(TARGET_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

message(STATUS "mathlib dir : ${MATHLIB_INCLUDE_DIR}")

# Source files

file(GLOB_RECURSE TARGET_HEADER_FILES
	${CMAKE_CURRENT_SOURCE_DIR}/*.h
	${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)

file(GLOB_RECURSE TARGET_SOURCE_FILES
	${CMAKE_CURRENT_SOURCE_DIR}/*.c
	${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

set(TARGET_FILES ${TARGET_HEADER_FILES} ${TARGET_SOURCE_FILES})

# Visual studio filters
source_group("Header" FILES ${TARGET_HEADER_FILES})
source_group("Source" FILES ${TARGET_SOURCE_FILES})


add_library(MATH SHARED IMPORTED)

set_target_properties(${MATH} PROPERTIES
	IMPORTED_LOCATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/mathlib.dll
	IMPORTED_IMPLIB  ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/mathlib.lib
)

# Create UI static lib
add_library(${TARGET_NAME} SHARED)

# Add sources for compiling and filters
target_sources(${TARGET_NAME} PRIVATE ${TARGET_FILES})

# Public include directory to allow dependant projects to access headers
target_include_directories(${TARGET_NAME}
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
	PRIVATE ${RENDERER_INCLUDE_DIR}
	PRIVATE ${RESOURCES_INCLUDE_DIR}
	PRIVATE ${CMAKE_SOURCE_DIR}/common
	#PRIVATE ${MATHLIB_INCLUDE_DIR}
)

# Link against dependencies for windowing and drawing
target_link_libraries(${TARGET_NAME}
	PRIVATE dependencies
	PRIVATE mathlib
)

# Expose lib name for later linking
set(ECS_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include PARENT_SCOPE)
set(ECS_LIBRARY ${TARGET_NAME} PARENT_SCOPE)

if (MSVC)
	target_compile_options(${TARGET_NAME} PRIVATE /W4 /WX)
endif()