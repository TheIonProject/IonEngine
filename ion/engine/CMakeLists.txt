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
#	ion/engine subfolder CMake file
#
#	DESCTIPTION: this subfolder contains core modules for the engine executable
#
#
#

# Cmake min version
cmake_minimum_required(VERSION 3.25 FATAL_ERROR)

get_filename_component(TARGET_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

# Object and component hierarchies
#add_subdirectory(ECS)

# Windowing and user interface
add_subdirectory(UI)

# In-game renderer 
add_subdirectory(renderer)

# Main executable
add_subdirectory(application)

if (MSVC)
	set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT application)
endif()