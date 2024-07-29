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
#	ion/engine/UI subfolder CMake file
#
#	DESCTIPTION: Configures the windowing and user interface part of the engine
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
add_library(${TARGET_NAME} STATIC)

# Add sources for compiling and filters
target_sources(${TARGET_NAME} PRIVATE ${TARGET_FILES})

# Public include directory to allow dependant projects to access headers
target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Link against dependencies for windowing and drawing
target_link_libraries(${TARGET_NAME} PRIVATE ${DEPENDENCIES_LIBRARY})

# Expose lib name for later linking
set(UI_LIBRARY ${TARGET_NAME} PARENT_SCOPE)

if (MSVC)
	target_compile_options(${TARGET_NAME} PRIVATE /W4 /WX)
endif()