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
#	dependencies subfolder CMake file
#
#	DESCTIPTION: Configure third-party dependencies as static library
#
#
#

# Check minimum cmake version
cmake_minimum_required(VERSION 3.25 FATAL_ERROR)

get_filename_component(TARGET_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

# Get header files
file(GLOB_RECURSE TARGET_HEADER_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp
)

# Get source files
file(GLOB_RECURSE TARGET_SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/source/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp
)

# Get static library files
file(GLOB_RECURSE TARGET_STATIC_LIBS
    ${CMAKE_CURRENT_SOURCE_DIR}/library/*.lib
)

# Create VS filter
source_group("Dependencies" FILES ${TARGET_FILES})

# Set variable for compilation
set(TARGET_FILES ${TARGET_HEADER_FILES} ${TARGET_SOURCE_FILES})

# Create target library
add_library(${TARGET_NAME} STATIC)

# Add sources to target
target_sources(${TARGET_NAME} PRIVATE ${TARGET_FILES})

# Set public include directory for this and other projects
target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Link against necessary libraries
target_link_libraries(${TARGET_NAME} PRIVATE ${TARGET_STATIC_LIBS})

# Set name as exposed variable to build other   projects
set(DEPENDENCIES_LIBRARY ${TARGET_NAME} PARENT_SCOPE)
