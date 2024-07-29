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
#	Root CMake
#
#	DESCTIPTION: Root file, configures ion subfolder and write build files
#				 into build/ sibling folder
#
#
#

# Cmake min version
cmake_minimum_required(VERSION 3.25 FATAL_ERROR)

# C++ version
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)


file(MAKE_DIRECTORY lib)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}/lib)

set(CMAKE_PDB_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}/pdb)
set(CMAKE_PDB_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR}/pdb)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR}/lib)

link_directories(${CMAKE_CURRENT_BINARY_DIR}/lib)

# Solution name
project(IonEngine)

if(MSVC)
	add_link_options(/IGNORE:4099)
endif()


include(FetchContent)

FetchContent_Declare(
	mathlib
	GIT_REPOSITORY			https://github.com/torrra/mathlib		# Fetch our math library from github
	GIT_TAG					main									# Get main branch
	GIT_SHALLOW				ON										# Allow branch names as GIT_TAG argument
)


# Ensure mathlib is populated
FetchContent_MakeAvailable(mathlib)


add_subdirectory(dependencies)

add_subdirectory(resources)
add_subdirectory(renderer)
add_subdirectory(ECS)
add_subdirectory(editor)

if (MSVC)
	set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT editor)
endif()