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
#	resources subfolder CMake file
#
#	DESCTIPTION: Configures the loadable assets used by the engine
#
#





cmake_minimum_required(VERSION 3.25 FATAL_ERROR)

get_filename_component(TARGET_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)


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

# Create UI static lib
add_library(${TARGET_NAME} SHARED)


# Add sources for compiling and filters
target_sources(${TARGET_NAME} PRIVATE ${TARGET_FILES})
target_compile_definitions(${TARGET_NAME} PRIVATE RES_EXPORTS=1)

#include(GenerateExportHeader)
#/generate_export_header(${TARGET_NAME})

# Public include directory to allow dependant projects to access headers
target_include_directories(${TARGET_NAME}
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
	PRIVATE ${CMAKE_SOURCE_DIR}/common)

# Link against dependencies for windowing and drawing
target_link_libraries(${TARGET_NAME}
	PRIVATE ${DEPENDENCIES_LIBRARY}
	PUBLIC mathlib
)

# Expose lib name for later linking
set(RESOURCES_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include PARENT_SCOPE)

if (MSVC)
	target_compile_options(${TARGET_NAME} PRIVATE /W4 /WX)
endif()